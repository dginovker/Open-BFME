# How to Contribute

* First read `docs/matching.md` — the core workflow (C++ in `src/`, row in `reverse/functions.csv`, `./build.sh` byte-verifies; nothing lands without passing it)
* Progress = matched functions.csv rows, nothing else. Report your session's results with `python3 tools/progress.py <start-ref>` output — landing files of `present-unmatched` markers is not work, and the gates reject sources with zero matched rows
* Highest yield: the ZH sweep pipeline (`docs/zh_sweep.md`) — batch-port Zero Hour reference sources that still match BFME verbatim
* Start easy - Find a small function you can generate the C++ code for, or translate __asm to C++
* If confident, go harder - Check docs/ for more ambitious things to do

# Rules

* Keep shit lean. It's very easy to generate verbose code and verbose docs with AI. Always ask yourself if you're being helpful by generating it. Temporary scripts and tests are fine if you clean them up. Really ask yourself a question if your commit is larger than 33% of the median of previous commits in the project.
* Don't add fallback code paths as a convenience. They hide mismatches and create subtle bugs that cost more time than they save. If the original toolchain matters, use the original toolchain.
