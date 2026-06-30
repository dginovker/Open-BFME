#!/usr/bin/env python3
import csv
import hashlib
import json
import os
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
    print(f"Baseline: {manifest['id']}")

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

        print(f"  OK {entry['path']}")


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
        if symbol["name"] == symbol_name:
            if symbol["section"] <= 0:
                raise ValueError(f"{symbol_name} is not defined in a section")
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


def compiler_environment(root):
    env = os.environ.copy()
    bin_dir = root / "Vc7" / "bin"
    ide_dir = root / "Common7" / "IDE"
    base_dir = root.parents[1]

    if os.name == "nt":
        env["INCLUDE"] = str(root / "Vc7" / "include")
        env["LIB"] = str(root / "Vc7" / "lib")
        env["PATH"] = os.pathsep.join([str(bin_dir), str(ide_dir), env.get("PATH", "")])
        return env

    env["INCLUDE"] = wine_path(root / "Vc7" / "include")
    env["LIB"] = wine_path(root / "Vc7" / "lib")
    env["WINEPATH"] = ";".join(
        path
        for path in [wine_path(bin_dir), wine_path(ide_dir), wine_path(base_dir), env.get("WINEPATH", "")]
        if path
    )
    return env


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
        f"/Fo{output_arg}",
        source_arg,
    ]
    return command, compiler_environment(root)


def format_bytes(data):
    return " ".join(f"{byte:02x}" for byte in data)


def load_function_rows():
    with FUNCTIONS.open("r", encoding="utf-8", newline="") as handle:
        return list(csv.DictReader(handle))


def build_call_thunks():
    # Intra-module calls don't target a function's body directly -- they go through
    # the incremental-link thunk table, a block of 5-byte `jmp body` entries near the
    # start of .text. Map each body to its (lowest-addressed = ILT) thunk so that a
    # call to a matched function resolves to the address the original code called.
    data = EXE.read_bytes()
    text = next(section for section in pe_sections(data) if section["name"] == ".text")
    lo, size, raw = text["rva"], text["size"], text["raw_pointer"]
    body_to_thunk = {}
    pos, end = raw, raw + size - 5
    while True:
        pos = data.find(b"\xe9", pos, end)
        if pos == -1:
            break
        thunk_rva = (pos - raw) + lo
        target = thunk_rva + 5 + struct.unpack_from("<i", data, pos + 1)[0]
        if lo <= target < lo + size:
            body_to_thunk.setdefault(target, thunk_rva)
        pos += 1
    return body_to_thunk


def load_symbol_map():
    # Addresses for resolving relative calls (REL32). A call to a matched function
    # goes through its incremental-link thunk, not its body; reverse/symbols.csv
    # holds callees we do not own source for yet (CRT helpers like __ftol2).
    thunks = build_call_thunks()
    symbol_map = {}
    for row in load_function_rows():
        body = int(row["target_rva"], 16)
        symbol_map[row["name"]] = thunks.get(body, body)
    if SYMBOLS.exists():
        with SYMBOLS.open("r", encoding="utf-8", newline="") as handle:
            for row in csv.DictReader(handle):
                symbol_map[row["name"]] = int(row["address"], 16)
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
                target_address = symbol_map[sym_name]
                next_address = target_rva + offset + 4
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
    symbol_map = load_symbol_map()

    print("Functions:")
    failures = 0
    patches = []
    source_outputs = {}
    for row in rows:
        source = ROOT / row["source"]
        if source not in source_outputs:
            output = BUILD_DIR / (source.stem + ".obj")
            compile_source(source, output)
            source_outputs[source] = output

        patch = compile_function(row, symbol_map, source_outputs[source])
        target = patch["target"]
        compiled = patch["bytes"]

        if compiled == target:
            print(f"  OK {row['name']} ({row['source']})")
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
        print(f"{failures} function(s) failed byte comparison")
        raise SystemExit(1)

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

    print("No-op patch:")
    if patched_sha256 != original_sha256:
        raise SystemExit(
            f"  FAIL {NOOP_EXE.relative_to(ROOT)} sha256 {patched_sha256} != {original_sha256}"
        )
    print(f"  OK {NOOP_EXE.relative_to(ROOT)}")


def main(only=None):
    if only:
        # Fast path: compile and byte-compare only the matching sources/functions
        # (a few seconds), skipping the baseline hash and no-op patch. Use this to
        # iterate; run with no arguments for the full check before committing.
        verify_functions(only)
        return
    verify_baseline()
    patches = verify_functions()
    verify_noop_patch(patches)


if __name__ == "__main__":
    main(sys.argv[1:])
