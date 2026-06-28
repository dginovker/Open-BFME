# BFME 1 Source Code
<img width="1000" height="125" alt="image" src="https://github.com/user-attachments/assets/d4ac956a-5221-42a6-aaf0-b0c0e41f6b8a" />

Reverse engineered with AI.

Goal: source code that rebuilds BFME 1's executable byte-for-byte.

## What?

* If you take a part of the BFME binary, recreate the exact source code that would make that part of the binary, then compile the source code and inject it into the binary, you get the same binary
* Doing this piece by piece will eventually give you a full, open source recreation of BFME, and enable some (insane) mods
* The goal of this project _is not_ to mod the game. The point of the project is to get source code that can be compiled into a 1:1, bit by bit replica of BFME 1's binary. This ensures 100% accuracy and will enable future (insane) modifications

## Baseline

```text
baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe
sha256: c1a907c44b84df129c1f18dc7365ea25ba438f9b8f39a374b86ed852936ff0a9
```

## Build

```bash
./build.sh
```

On Windows:

```powershell
.\build.ps1
```

The build verifies the baseline and byte-compares tracked source against the original executable.
