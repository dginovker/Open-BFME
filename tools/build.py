#!/usr/bin/env python3
import concurrent.futures
import csv
import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "baselines" / "bfme1" / "workshop-vanilla-1.03" / "manifest.json"
EXE = ROOT / "baselines" / "bfme1" / "workshop-vanilla-1.03" / "files" / "lotrbfme.exe"
FUNCTIONS = ROOT / "reverse" / "functions.csv"
SYMBOLS = ROOT / "reverse" / "symbols.csv"
BUILD_DIR = ROOT / "build" / "match"
PATCH_DIR = ROOT / "build" / "patch"
NOOP_EXE = PATCH_DIR / "lotrbfme.noop.exe"
DEFAULT_VC71_ROOT = (
    ROOT
    / "build"
    / "toolchains"
    / "vs2003"
    / "Program Files"
    / "Microsoft Visual Studio .NET 2003"
)


def u16(data, offset):
    return struct.unpack_from("<H", data, offset)[0]


def u32(data, offset):
    return struct.unpack_from("<I", data, offset)[0]


def hash_file(path, algorithm):
    digest = hashlib.new(algorithm)
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def verify_baseline():
    with MANIFEST.open("r", encoding="utf-8") as handle:
        manifest = json.load(handle)

    baseline_dir = MANIFEST.parent
    verified = 0

    for entry in manifest["files"]:
        path = baseline_dir / entry["path"]
        if not path.exists():
            raise SystemExit(f"missing baseline file: {path}")

        size = path.stat().st_size
        if size != entry["size"]:
            raise SystemExit(f"{entry['path']}: size {size} != {entry['size']}")

        sha256 = hash_file(path, "sha256")
        if sha256 != entry["sha256"]:
            raise SystemExit(f"{entry['path']}: sha256 mismatch")

        md5 = hash_file(path, "md5")
        if md5 != entry["md5"]:
            raise SystemExit(f"{entry['path']}: md5 mismatch")

        verified += 1

    print(f"Baseline: OK {verified} file(s) ({manifest['id']})")


def pe_sections(data):
    pe_offset = u32(data, 0x3C)
    coff = pe_offset + 4
    section_count = u16(data, coff + 2)
    optional_size = u16(data, coff + 16)
    section_table = coff + 20 + optional_size

    sections = []
    for index in range(section_count):
        offset = section_table + index * 40
        name = data[offset : offset + 8].rstrip(b"\0").decode("ascii", errors="replace").strip()
        virtual_size = u32(data, offset + 8)
        virtual_address = u32(data, offset + 12)
        raw_size = u32(data, offset + 16)
        raw_pointer = u32(data, offset + 20)
        sections.append(
            {
                "name": name,
                "rva": virtual_address,
                "size": max(virtual_size, raw_size),
                "raw_pointer": raw_pointer,
            }
        )
    return sections


def rva_to_file_offset(sections, rva):
    for section in sections:
        start = section["rva"]
        end = start + section["size"]
        if start <= rva < end:
            return section["raw_pointer"] + (rva - start)
    raise ValueError(f"RVA 0x{rva:08X} is outside all PE sections")


def read_target_bytes(rva, size):
    data = EXE.read_bytes()
    offset = rva_to_file_offset(pe_sections(data), rva)
    return data[offset : offset + size]


def coff_name(data, symbol_offset, string_table):
    short_name = data[symbol_offset : symbol_offset + 8]
    if short_name[:4] == b"\0\0\0\0":
        string_offset = u32(short_name, 4)
        end = string_table.index(b"\0", string_offset)
        return string_table[string_offset:end].decode("ascii", errors="replace")
    return short_name.rstrip(b"\0").decode("ascii", errors="replace")


def read_object_symbols(data):
    symbol_table = u32(data, 8)
    symbol_count = u32(data, 12)
    string_table = data[symbol_table + symbol_count * 18 :]
    symbols = []
    index = 0
    while index < symbol_count:
        offset = symbol_table + index * 18
        name = coff_name(data, offset, string_table)
        value = u32(data, offset + 8)
        section_number = struct.unpack_from("<h", data, offset + 12)[0]
        aux_count = data[offset + 17]
        symbols.append({"name": name, "value": value, "section": section_number, "aux": aux_count})
        for _ in range(aux_count):
            index += 1
            offset = symbol_table + index * 18
            symbols.append({"name": "", "value": 0, "section": 0, "aux": 0})
        index += 1
    return symbols


def read_object_symbol_bytes(path, symbol_name):
    data = path.read_bytes()
    section_count = u16(data, 2)
    section_table = 20

    sections = []
    for index in range(section_count):
        offset = section_table + index * 40
        sections.append(
            {
                "name": data[offset : offset + 8].rstrip(b"\0").decode("ascii", errors="replace"),
                "raw_size": u32(data, offset + 16),
                "raw_pointer": u32(data, offset + 20),
                "reloc_count": u16(data, offset + 32),
                "reloc_pointer": u32(data, offset + 24),
            }
        )

    symbols = read_object_symbols(data)
    index = 0
    while index < len(symbols):
        symbol = symbols[index]
        # the same name can appear as a sectionless entry (e.g. weak external)
        # before its real definition; keep scanning for the defined one
        if symbol["name"] == symbol_name and symbol["section"] > 0:
            section = sections[symbol["section"] - 1]
            value = symbol["value"]
            start = section["raw_pointer"] + value
            end = section["raw_pointer"] + section["raw_size"]
            bytes_data = data[start:end]

            relocs = []
            for r in range(section["reloc_count"]):
                ro = section["reloc_pointer"] + r * 10
                rva = u32(data, ro)
                sym_idx = u32(data, ro + 4)
                rtype = u16(data, ro + 8)
                if value <= rva < value + len(bytes_data):
                    relocs.append((rva - value, rtype, symbols[sym_idx]["name"]))

            return bytes_data, relocs

        index += 1

    raise ValueError(f"symbol not found in object: {symbol_name}")


def vc71_root():
    root = Path(os.environ.get("VC71_ROOT", DEFAULT_VC71_ROOT))
    compiler = root / "Vc7" / "bin" / "cl.exe"
    if not compiler.exists():
        raise SystemExit(
            "MSVC 7.1 cl.exe not found. Set VC71_ROOT to a Visual Studio .NET 2003 "
            f"install root, or place it at {DEFAULT_VC71_ROOT.relative_to(ROOT)}."
        )
    return root


def wine_path(path):
    winepath = shutil.which("winepath")
    if winepath is None:
        raise SystemExit("winepath not found. Install Wine to run MSVC 7.1 on this host.")
    return subprocess.check_output([winepath, "-w", str(path)], text=True).strip()


def stlport_include_dir():
    """Directory of STLport 4.5.3 headers, or None. The game linked STLport, so
    files using std:: containers must compile against it to byte-match (MSVC's own
    STL emits different code). Prefer a vendored copy; fall back to an env var."""
    candidates = [ROOT / "vendor" / "stlport"]
    env_root = os.environ.get("STLPORT_ROOT")
    if env_root:
        candidates.append(Path(env_root))
    for path in candidates:
        if (path / "list").exists():
            return path
    return None


def source_needs_stlport(source):
    """A source declares it needs STLport with a `// stlport` line near the top.
    STLport shadows standard headers (<cmath>, <cstring>, ...), so it must be
    opt-in per file — never on the global include path for STL-free matched files."""
    if source is None:
        return False
    try:
        with Path(source).open("r", encoding="utf-8", errors="replace") as handle:
            head = handle.read(2048)
    except OSError:
        return False
    return "// stlport" in head


def compiler_environment(root, source=None):
    env = os.environ.copy()
    bin_dir = root / "Vc7" / "bin"
    ide_dir = root / "Common7" / "IDE"
    base_dir = root.parents[1]

    stlport = stlport_include_dir() if source_needs_stlport(source) else None

    if os.name == "nt":
        include = str(root / "Vc7" / "include")
        if stlport:
            include = str(stlport) + os.pathsep + include
        env["INCLUDE"] = include
        env["LIB"] = str(root / "Vc7" / "lib")
        env["PATH"] = os.pathsep.join([str(bin_dir), str(ide_dir), env.get("PATH", "")])
        return env

    include = wine_path(root / "Vc7" / "include")
    if stlport:
        include = wine_path(stlport) + ";" + include
    env["INCLUDE"] = include
    env["LIB"] = wine_path(root / "Vc7" / "lib")
    env["WINEPATH"] = ";".join(
        path
        for path in [wine_path(bin_dir), wine_path(ide_dir), wine_path(base_dir), env.get("WINEPATH", "")]
        if path
    )
    return env


def source_extra_flags(source):
    # A source that needs different compiler flags (e.g. /EHsc for functions the
    # original built with exception handling) declares them in its first lines:
    #   // cl: /EHsc
    with source.open("r", encoding="utf-8", errors="replace") as handle:
        for line in handle.read(2048).splitlines():
            if line.startswith("// cl:"):
                return line[len("// cl:") :].split()
    return []


def compiler_command(source, output):
    root = vc71_root()
    compiler = root / "Vc7" / "bin" / "cl.exe"
    source_arg = source.relative_to(ROOT).as_posix()
    output_arg = output.relative_to(ROOT).as_posix()

    command = []
    if os.name != "nt":
        wine = shutil.which("wine")
        if wine is None:
            raise SystemExit("wine not found. Install Wine to run MSVC 7.1 on this host.")
        command.append(wine)

    command += [
        str(compiler),
        "/nologo",
        "/c",
        "/O2",
        "/GR-",
        "/EHsc-",
    ]
    command += source_extra_flags(source)
    command += [
        f"/Fo{output_arg}",
        source_arg,
    ]
    return command, compiler_environment(root, source)


def format_bytes(data):
    return " ".join(f"{byte:02x}" for byte in data)


def load_all_function_rows():
    with FUNCTIONS.open("r", encoding="utf-8", newline="") as handle:
        return list(csv.DictReader(handle))


def load_function_rows():
    return [row for row in load_all_function_rows() if row["status"] == "matched"]


def build_call_thunks():
    # Intra-module calls don't target a function's body directly -- they go through
    # the incremental-link thunk table, a block of 5-byte `jmp body` entries near the
    # start of .text. Map each body to its (lowest-addressed = ILT) thunk so that a
    # call to a matched function resolves to the address the original code called.
    data = EXE.read_bytes()
    text = next(section for section in pe_sections(data) if section["name"] == ".text")
    lo, size, raw = text["rva"], text["size"], text["raw_pointer"]
    body_to_thunks = {}
    pos, end = raw, raw + size - 5
    while True:
        pos = data.find(b"\xe9", pos, end)
        if pos == -1:
            break
        thunk_rva = (pos - raw) + lo
        target = thunk_rva + 5 + struct.unpack_from("<i", data, pos + 1)[0]
        if lo <= target < lo + size:
            # incremental linking creates one thunk block per re-link; a body can
            # have several thunks and different call sites use different ones
            body_to_thunks.setdefault(target, []).append(thunk_rva)
        pos += 1
    return body_to_thunks


def load_symbol_map():
    # Candidate addresses for resolving relative calls (REL32), most-likely first.
    # Incremental linking makes the callee encoding site-specific: objs linked
    # earlier call a matched function through its incremental-link thunk, objs
    # re-linked in place call the body directly. Both are legitimate, so a matched
    # function maps to [thunk, body] and the comparison picks whichever the target
    # actually used; anything else still fails the byte comparison loudly.
    # reverse/symbols.csv holds callees we do not own source for yet (CRT helpers
    # like __ftol2) at their exact call-target address, plus specific incremental-
    # link thunks build_call_thunks does not auto-discover. It is ADDITIVE: each
    # pinned address becomes one more candidate, so a matched name and a hand-pinned
    # thunk for the same name coexist and each call site picks whichever it encodes.
    thunks = build_call_thunks()
    symbol_map = {}
    for row in load_all_function_rows():
        body = int(row["target_rva"], 16)
        symbol_map[row["name"]] = thunks.get(body, []) + [body]
    if SYMBOLS.exists():
        with SYMBOLS.open("r", encoding="utf-8", newline="") as handle:
            for row in csv.DictReader(handle):
                address = int(row["address"], 16)
                candidates = symbol_map.setdefault(row["name"], [])
                if address not in candidates:
                    candidates.append(address)
    return symbol_map


def compile_source(source, output):
    output.parent.mkdir(parents=True, exist_ok=True)
    command, env = compiler_command(source, output)
    result = subprocess.run(
        command,
        cwd=ROOT,
        env=env,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    if result.returncode != 0:
        print(result.stdout, end="")
        raise SystemExit(result.returncode)


def compile_function(row, symbol_map, output):
    target_rva = int(row["target_rva"], 16)
    target_size = int(row["target_size"])
    target = read_target_bytes(target_rva, target_size)
    compiled, relocs = read_object_symbol_bytes(output, row["name"])

    resolved = bytearray(compiled[:target_size])
    unresolved = []
    for offset, rtype, sym_name in relocs:
        if offset >= target_size:
            continue  # reloc belongs to a later function sharing the COMDAT section
        if rtype == 0x0006:  # IMAGE_REL_I386_DIR32
            resolved[offset : offset + 4] = target[offset : offset + 4]
        elif rtype == 0x0014:  # IMAGE_REL_I386_REL32
            if sym_name in symbol_map:
                next_address = target_rva + offset + 4
                candidates = symbol_map[sym_name]
                displacement = struct.pack("<i", candidates[0] - next_address)
                for target_address in candidates[1:]:
                    if target[offset : offset + 4] == displacement:
                        break
                    displacement = struct.pack("<i", target_address - next_address)
                resolved[offset : offset + 4] = displacement
            else:
                unresolved.append(sym_name)

    return {
        "name": row["name"],
        "target_rva": target_rva,
        "target": target,
        "bytes": bytes(resolved),
        "source": row["source"],
        "unresolved": unresolved,
    }


def verify_functions(only=None):
    rows = load_function_rows()
    if only:
        rows = [row for row in rows if any(sel in row["source"] or sel in row["name"] for sel in only)]
        if not rows:
            raise SystemExit("no functions match: " + ", ".join(only))
    total = len(rows)
    symbol_map = load_symbol_map()

    sources = []
    seen = set()
    for row in rows:
        source = ROOT / row["source"]
        if source not in seen:
            seen.add(source)
            sources.append(source)
    missing = [s for s in sources if not s.exists()]
    if missing:
        raise SystemExit("functions.csv references missing source file(s): "
                         + ", ".join(str(m) for m in missing)
                         + " - a commit added rows without adding the file")
    source_outputs = {s: BUILD_DIR / (s.stem + ".obj") for s in sources}
    if len(set(source_outputs.values())) != len(source_outputs):
        raise SystemExit("obj stem collision between sources; refusing parallel compile")
    # wine cl.exe instances are independent processes; compile is the wall-clock
    # hog (byte comparison below is pure reads), so parallelize only this phase
    # Incremental mode (BUILD_RECOMPILE_ONLY="a.cpp;b.cpp"): reuse existing .obj
    # files for every source NOT listed - valid only when the caller proves the
    # unlisted sources and all headers are identical to the previous verified
    # build in this same tree (the fleet verifier does, via git diff). A missing
    # .obj is compiled regardless; never silently reused when absent.
    recompile_only = os.environ.get("BUILD_RECOMPILE_ONLY")
    if recompile_only is not None:
        wanted = {w for w in recompile_only.split(";") if w}
        to_compile = [s for s in sources
                      if str(s.relative_to(ROOT)) in wanted or not source_outputs[s].exists()]
        print(f"Incremental compile: {len(to_compile)} of {len(sources)} source(s)")
    else:
        to_compile = sources
    # BUILD_POOL controls compile parallelism. Default 1: a single build.py call
    # (a worker verifying its own 1-2 files, or the fleet's per-task fast verify)
    # must NOT fork an 8-way wine pool - dozens of concurrent callers would then
    # oversubscribe the cores into a stall. Only the full-suite periodic audit,
    # which runs alone, sets BUILD_POOL=8 to compile all 260+ TUs in parallel.
    pool_size = max(1, min(int(os.environ.get("BUILD_POOL", "1")), os.cpu_count() or 1))
    if pool_size == 1 or len(to_compile) <= 1:
        for s in to_compile:
            compile_source(s, source_outputs[s])
    else:
        with concurrent.futures.ThreadPoolExecutor(pool_size) as pool:
            futures = {pool.submit(compile_source, s, source_outputs[s]): s for s in to_compile}
            for future in concurrent.futures.as_completed(futures):
                future.result()

    failures = 0
    patches = []
    for row in rows:
        source = ROOT / row["source"]
        patch = compile_function(row, symbol_map, source_outputs[source])
        target = patch["target"]
        compiled = patch["bytes"]

        if compiled == target:
            patches.append(patch)
            continue

        failures += 1
        print(f"  FAIL {row['name']} ({row['source']})")
        if patch["unresolved"]:
            calls = ", ".join(sorted(set(patch["unresolved"])))
            print(f"    unresolved call(s): {calls} (add to reverse/symbols.csv)")
        print(f"    target:   {format_bytes(target)}")
        print(f"    compiled: {format_bytes(compiled)}")

    if failures:
        print(f"Functions: FAIL {failures}/{total}")
        print(f"{failures} function(s) failed byte comparison")
        raise SystemExit(1)

    source_count = len({row["source"] for row in rows})
    if total == 1:
        row = rows[0]
        print(f"Functions: OK 1/1 matched")
        print(f"  {row['name']} ({row['source']})")
    else:
        print(f"Functions: OK {total}/{total} matched across {source_count} source file(s)")

    return patches


def patch_exe(patches, output):
    output.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(EXE, output)

    data = bytearray(output.read_bytes())
    sections = pe_sections(data)
    ranges = []
    for patch in sorted(patches, key=lambda entry: entry["target_rva"]):
        offset = rva_to_file_offset(sections, patch["target_rva"])
        end = offset + len(patch["bytes"])
        if data[offset:end] != patch["target"]:
            raise SystemExit(f"{patch['name']}: target bytes changed before patching")
        if ranges and offset < ranges[-1][1]:
            raise SystemExit(f"{patch['name']}: patch overlaps previous patch")
        ranges.append((offset, end))
        data[offset:end] = patch["bytes"]

    output.write_bytes(data)
    return output


def verify_noop_patch(patches):
    patch_exe(patches, NOOP_EXE)

    original_sha256 = hash_file(EXE, "sha256")
    patched_sha256 = hash_file(NOOP_EXE, "sha256")

    if patched_sha256 != original_sha256:
        raise SystemExit(
            f"No-op patch: FAIL {NOOP_EXE.relative_to(ROOT)} sha256 {patched_sha256} != {original_sha256}"
        )
    print(f"No-op patch: OK {NOOP_EXE.relative_to(ROOT)}")


def verify_string_refs(rows):
    """Independently VERIFY (not mask) every DIR32 relocation that points at a string literal:
    read the address the compiled code references, and confirm the string AT that address in the
    binary byte-equals the compiled literal. Self-verifying (no pins) — catches source/binary string
    discrepancies that compile_function's DIR32 masking otherwise hides (e.g. "%S" vs "%ls",
    "ParticleSystemInfo" vs "FXParticleSystemInfo"). Reuses the objs already built by verify_functions."""
    exe = EXE.read_bytes()
    pe = pe_sections(exe)
    mismatches = []
    checked = 0
    empty_ok = 0
    for row in rows:
        obj = BUILD_DIR / ((ROOT / row["source"]).stem + ".obj")
        if not obj.exists():
            continue
        target_rva = int(row["target_rva"], 16)
        target_size = int(row["target_size"])
        target = read_target_bytes(target_rva, target_size)
        try:
            _, relocs = read_object_symbol_bytes(obj, row["name"])
        except ValueError:
            continue
        for offset, rtype, sym in relocs:
            if rtype != 0x0006 or offset + 4 > target_size or not sym.startswith("??_C@"):
                continue
            # No silent skip: a string reference we cannot verify is a hole in the guarantee, so a
            # genuine extraction/RVA failure is surfaced as a mismatch (fail loudly), not swallowed.
            try:
                cs, _ = read_object_symbol_bytes(obj, sym)
                str_rva = struct.unpack_from("<I", target, offset)[0] - 0x400000
                file_off = rva_to_file_offset(pe, str_rva)
            except (ValueError, struct.error) as exc:
                mismatches.append((row["name"], f"<unverifiable {sym[:24]}: {exc}>".encode(), b""))
                continue
            content = cs.rstrip(b"\x00")
            if not content:
                # empty string literal "": no content to match, but confirm the referenced location
                # really is an empty string (a null byte) and not a stale/wrong pointer.
                if exe[file_off] != 0:
                    mismatches.append((row["name"], b'"" (empty)', exe[file_off : file_off + 4]))
                else:
                    empty_ok += 1
                continue
            if exe[file_off : file_off + len(content)] != content:
                mismatches.append((row["name"], content, exe[file_off : file_off + len(content)]))
            else:
                checked += 1
    if mismatches:
        print(f"String-ref verify: FAIL {len(mismatches)} mismatch(es) (source string != binary string)")
        for name, src_s, bin_s in mismatches[:12]:
            print(f"    {name}: source={src_s!r} binary={bin_s!r}")
        raise SystemExit(1)
    print(f"String-ref verify: OK ({checked} literals + {empty_ok} empty-string refs verified, 0 unverified/skipped)")


def verify_dir32_consistency(rows):
    """Regression gate for the non-string DIR32s (globals/vtables/func-addrs) build.py masks. A symbol
    has one address, so every reference must resolve to the same base once the addend is subtracted
    (base = binary_addr - compiled_addend). A symbol with >1 base is a candidate hidden discrepancy.
    Whitelist (reverse/dir32_consistency_whitelist.txt) holds the CURRENT known-legitimate cases
    (double-linked TUs CRC32_Table/_COLLISION_EPSILON; the investigated FX ctor/dtor vtable artifacts).
    Self-bootstrapping: writes the whitelist on first run; afterwards any NEW inconsistency FAILS."""
    from collections import defaultdict
    whitelist_path = ROOT / "reverse" / "dir32_consistency_whitelist.txt"
    sym2base = defaultdict(set)
    for row in rows:
        obj = BUILD_DIR / ((ROOT / row["source"]).stem + ".obj")
        if not obj.exists():
            continue
        trva, tsz = int(row["target_rva"], 16), int(row["target_size"])
        target = read_target_bytes(trva, tsz)
        try:
            body, relocs = read_object_symbol_bytes(obj, row["name"])
        except ValueError:
            continue
        for off, rtype, sym in relocs:
            if rtype != 0x0006 or off + 4 > tsz or off + 4 > len(body) or sym.startswith("??_C@"):
                continue
            final = struct.unpack_from("<I", target, off)[0]
            addend = struct.unpack_from("<I", body, off)[0]
            sym2base[sym].add((final - addend) & 0xFFFFFFFF)
    inconsistent = sorted(s for s, b in sym2base.items() if len(b) > 1)
    if not whitelist_path.exists():
        whitelist_path.write_text("# DIR32 consistency whitelist — symbols with >1 resolved base that are\n"
            "# KNOWN-legitimate (doubly-linked TUs / investigated FX vtable artifacts). Any symbol NOT\n"
            "# listed here that becomes inconsistent is a NEW candidate bug and fails the build.\n"
            + "".join(s + "\n" for s in inconsistent))
        print(f"DIR32 consistency: wrote whitelist ({len(inconsistent)} known cases) — review reverse/dir32_consistency_whitelist.txt")
        return
    whitelist = {l.strip() for l in whitelist_path.read_text().splitlines() if l.strip() and not l.startswith("#")}
    new = [s for s in inconsistent if s not in whitelist]
    if new:
        print(f"DIR32 consistency: FAIL {len(new)} NEW inconsistent symbol(s) (candidate hidden bug — same symbol, multiple addresses)")
        for s in new[:12]:
            print(f"    {s}: bases {[hex(b) for b in sorted(sym2base[s])]}")
        raise SystemExit(1)
    print(f"DIR32 consistency: OK ({len(sym2base)} symbols; {len(inconsistent)} whitelisted, 0 new)")


CLAIMS_WHITELIST = ROOT / "reverse" / "unclaimed_sources_whitelist.txt"
UNMATCHED_MARKER_RE = re.compile(
    r"^\s*//\s*(\S+)\s+(?:present-unmatched|absent-from-retail)\b", re.MULTILINE
)


def load_claims_whitelist():
    if not CLAIMS_WHITELIST.exists():
        return set()
    return {
        line.strip()
        for line in CLAIMS_WHITELIST.read_text(encoding="utf-8").splitlines()
        if line.strip() and not line.lstrip().startswith("#")
    }


def verify_source_claims():
    """Progress is matched rows, nothing else: every src .cpp must own at least
    one byte-verified matched row (parked exceptions live in the whitelist, with
    reasons), and no marker may contradict the ledger (a symbol both matched and
    marked unmatched is a stale annotation lying about state). This closes the
    'land a file of present-unmatched markers and call it work' path."""
    matched_by_source = {}
    matched_sources = {}
    for row in load_function_rows():
        matched_by_source[row["source"]] = matched_by_source.get(row["source"], 0) + 1
        matched_sources.setdefault(row["name"], set()).add(row["source"])
    whitelist = load_claims_whitelist()

    problems = []
    sources = sorted((ROOT / "src").rglob("*.cpp"))
    for path in sources:
        rel = path.relative_to(ROOT).as_posix()
        text = path.read_text(encoding="utf-8", errors="replace")
        for label in UNMATCHED_MARKER_RE.findall(text):
            # a marker on a symbol matched from ANOTHER file is correct bookkeeping
            # (e.g. the ZH copy of a function landed via an asm-whale scaffold);
            # matched from THIS file, the marker is a stale lie about its state
            if rel in matched_sources.get(label, ()):
                problems.append(
                    f"{rel}: {label} is byte-verified matched from this file but still "
                    f"carries an unmatched marker (stale annotation)"
                )
        if matched_by_source.get(rel, 0) == 0 and rel not in whitelist:
            problems.append(
                f"{rel}: ZERO matched rows — source presence is not progress; match at "
                f"least one function or whitelist it with a reason "
                f"({CLAIMS_WHITELIST.relative_to(ROOT)})"
            )
    for entry in sorted(whitelist):
        if not (ROOT / entry).exists():
            problems.append(f"whitelist: {entry} no longer exists — remove the entry")
        elif matched_by_source.get(entry, 0):
            problems.append(f"whitelist: {entry} now has matched rows — remove the stale entry")

    if problems:
        print(f"Source claims: FAIL ({len(problems)} problem(s))")
        for problem in problems[:20]:
            print(f"    {problem}")
        raise SystemExit(1)
    print(f"Source claims: OK ({len(sources)} sources, {len(whitelist)} whitelisted unclaimed)")


def main(only=None):
    if only:
        # Fast path: compile and byte-compare only the matching sources/functions
        # (a few seconds), skipping the baseline hash and no-op patch. Use this to
        # iterate; run with no arguments for the full check before committing.
        verify_functions(only)
        return
    print("Full verification")
    verify_baseline()
    patches = verify_functions()
    verify_string_refs(load_function_rows())
    verify_dir32_consistency(load_function_rows())
    verify_source_claims()
    verify_noop_patch(patches)


if __name__ == "__main__":
    main(sys.argv[1:])
