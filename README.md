# BFME 1 Source Code
<img width="1000" height="125" alt="image" src="https://github.com/user-attachments/assets/d4ac956a-5221-42a6-aaf0-b0c0e41f6b8a" />

Reverse engineered with AI.

The goal is source code that can rebuild a byte-identical copy of BFME 1's executable. This is not a normal modding project.

## Target

Initial baseline:

```text
baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe
size:   16,433,152
md5:    34af1cded478f6f48b333db0b8d5f6d9
sha256: c1a907c44b84df129c1f18dc7365ea25ba438f9b8f39a374b86ed852936ff0a9
```

`worldbuilder.exe` is also tracked, but `lotrbfme.exe` is the first target.

Out of scope for source translation:

```text
asset.dat
*.big
launcher / ladder / WebView2 files
```

## Setup

Git LFS is required for committed executable baselines.

Windows:

```powershell
winget install Git.Git GitHub.GitLFS Python.Python.3.12
git lfs install
git lfs pull
.\build.ps1
```

Linux:

```bash
git lfs install
git lfs pull
./build.sh
```

## Build Status

`build.sh` / `build.ps1` currently verifies the checked-in executable baseline.

A compiler is not wired up yet because there is no reconstructed source target yet. As soon as the first function is added, the build should require a pinned compiler/toolchain. The likely long-term target is MSVC 7.1 / Visual Studio .NET 2003, because the baseline executable was linked with MSVC linker 7.10.

## Layout

```text
baselines/  Original executable baselines and manifests
reverse/    Function maps and reverse-engineering notes
src/        Reconstructed source
tools/      Build/verification scripts
```

## See Also

* https://bfmeladder.com/
* https://the3rdage.net/

