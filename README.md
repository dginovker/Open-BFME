# BFME 1 Source Code
<img width="1000" height="125" alt="image" src="https://github.com/user-attachments/assets/d4ac956a-5221-42a6-aaf0-b0c0e41f6b8a" />

Reverse engineered with AI.

Goal: source code that rebuilds BFME 1's executable byte-for-byte.

## What?

* If you take a part of the BFME binary, recreate the exact source code that would make that part of the binary, then compile the source code and inject it into the binary, you get the same binary
* Doing this piece by piece will eventually give you a full, open source recreation of BFME, and enable some (insane) mods
* The goal of this project _is not_ to mod the game. The point of the project is to get source code that can be compiled into a 1:1, bit by bit replica of BFME 1's binary. This ensures 100% accuracy and will enable future (insane) modifications

## Status

We currently have C++ functions in `src/` and a patcher which can patch same-size custom functions into `lotrbfme.exe`. This is useful for modding.

## How You Can Help

Just tell your favorite AI agent to make a PR in this repo, where each commit in the PR is an individual contribution. Your agent will know what to do from there (just make sure it keeps looping and making more commits), and I will be able to merge your PR.

!! All such AI-generated PRs are appreciated !!

## Build

Baseline executables and the MSVC 7.1 toolchain are stored with Git LFS. After cloning, run:

```bash
git lfs pull
./tools/setup_hooks.sh
```

Git does not auto-enable versioned hooks from a clone. `setup_hooks.sh` points this checkout at the
tracked pre-commit hook, which rejects new source functions unless they are listed in
`reverse/functions.csv` and pass the byte comparison.

```bash
./build.sh
# (or on Windows)
# .\build.ps1
```

The build verifies the baseline, byte-compares tracked source against the original executable, and checks that a no-op patched copy hashes identically. While iterating on one function, verify just its source in a few seconds by passing in the path:

```bash
./build.sh src/math/color.cpp   # or a function name
```
