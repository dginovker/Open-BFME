"""Cross-platform advisory file lock (POSIX fcntl / Windows msvcrt).

build.py and add_match.py serialize concurrent clones/agents with an advisory
lock on a lock file. `fcntl` is POSIX-only, so on Windows (`py -3 tools\\build.py`)
importing it died with `ModuleNotFoundError: No module named 'fcntl'`. This module
provides the same advisory lock on both platforms.

Windows note: msvcrt has no shared-lock mode, so an *exclusive* lock is always
taken there regardless of `exclusive=`. That is fail-safe — it serializes small
per-file verifies that would run concurrently on Linux, never the reverse — so a
Windows build is correct, just less parallel across simultaneous invocations.
"""
import os
import time

_WINDOWS = os.name == "nt"

if _WINDOWS:
    import msvcrt
else:
    import fcntl

# Windows msvcrt locks a byte range from the current file offset; lock and unlock
# must name the same region, so we always seek(0) and lock a single byte there.
_WIN_RANGE = 1


def lock(handle, *, exclusive, wait_notice=None):
    """Acquire an advisory lock on the open file `handle`, blocking until held.

    Tries non-blocking first; if the lock is contended, prints `wait_notice`
    once (when given) so the wait is visible, then blocks until acquired.
    """
    if _WINDOWS:
        _lock_windows(handle, wait_notice)
    else:
        _lock_posix(handle, exclusive, wait_notice)


def unlock(handle):
    """Release a lock previously taken with lock()."""
    if _WINDOWS:
        handle.seek(0)
        msvcrt.locking(handle.fileno(), msvcrt.LK_UNLCK, _WIN_RANGE)
    else:
        fcntl.flock(handle, fcntl.LOCK_UN)


def _lock_posix(handle, exclusive, wait_notice):
    mode = fcntl.LOCK_EX if exclusive else fcntl.LOCK_SH
    try:
        fcntl.flock(handle, mode | fcntl.LOCK_NB)
    except OSError:
        if wait_notice:
            print(wait_notice)
        fcntl.flock(handle, mode)


def _lock_windows(handle, wait_notice):
    handle.seek(0)
    fd = handle.fileno()
    try:
        msvcrt.locking(fd, msvcrt.LK_NBLCK, _WIN_RANGE)
        return
    except OSError:
        pass
    if wait_notice:
        print(wait_notice)
    # LK_LOCK gives up after ~10s; poll LK_NBLCK instead so we truly block.
    while True:
        try:
            handle.seek(0)
            msvcrt.locking(fd, msvcrt.LK_NBLCK, _WIN_RANGE)
            return
        except OSError:
            time.sleep(0.5)
