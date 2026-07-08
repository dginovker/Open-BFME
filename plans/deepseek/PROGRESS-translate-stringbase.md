# PROGRESS: translate-stringbase

Agent: translate-stringbase
Territory: src/game/string_base.cpp

## Done
- `StringBase<char>::startsWith(const char *str, int len)` — translated to C++ and byte-matches.
- `StringBase<char>::startsWith(const char *str)` — translated to C++ and byte-matches.
- `StringBase<char>::startsWith(const StringBase<char> &str)` — translated to C++ and byte-matches.

## Skipped
- operator=(const StringBase<T>&) at lines 2024/2049: compiler keeps `this` in ECX; target uses ESI. Register-choice wall.
- StringBase<T>(T c) constructors at lines 1532/1842: same ESI-for-`this` wall.
- `StringBase<wchar_t>::startsWith(const wchar_t *str, int len)`: needs `wcsncmp` called via direct relative call (E8) like the original thunk, but MSVC 7.1 emits `call [__imp__wcsncmp]` (FF 15) under /MD. Could not force matching instruction bytes.
- `StringBase<char>::endsWith(const char *str, int len)`: compiler avoids the redundant `m_data->length` reload and different LEA that the target uses. Close but not byte-identical.
- compare(const char*) at line 86 is a 10-byte double-jmp thunk; not expressible as matching C++.

## Pending / Notes
- Continue looking for naked blocks that don't rely on ESI-for-`this` or dllimport CRT calls.
