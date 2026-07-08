# PROGRESS: port-wwlib-2

## Done (pre-existing on branch)
DONE md5.cpp
DONE nstrdup.cpp

## Skipped
SKIP LaunchWeb.cpp — includes windows.h / shellapi.h
SKIP lcw.cpp — 0 located; not in binary
SKIP lcwpipe.cpp — 0 located; not in binary
SKIP load.cpp — shared iff.h issues + missing CompressionType enum
SKIP lzo.cpp — includes wwdebug.h
SKIP lzo1x_c.cpp — includes wwdebug.h
SKIP lzo1x_d.cpp — 0 located; not in binary
SKIP lzopipe.cpp — lzo.h pulls in wwdebug.h
SKIP lzostraw.cpp — lzo.h pulls in wwdebug.h
SKIP mixfile.cpp — includes wwdebug.h
SKIP mono.cpp — shared iff.h / data.h issues
SKIP mpu.cpp — uses Win32 thread/priority APIs
SKIP msgloop.cpp — uses HWND/HACCEL/MSG Win32 types
SKIP mutex.cpp — includes wwdebug.h / windows.h
SKIP obscure.cpp — 0 located; not in binary
SKIP palette.cpp — 0 located; not in binary
SKIP pcx.cpp — pcx.h missing from reference
SKIP pkpipe.cpp — 0 located; crypto functions absent
SKIP pkstraw.cpp — 0 located; crypto functions absent
SKIP point.cpp — 0 located; not in binary
SKIP ramfile.cpp — 0 located; not in binary
SKIP rc4.cpp — 0 located; not in binary
SKIP rcfile.cpp — rcfile.h uses Win32 HMODULE
SKIP refcount.cpp — includes windows.h
SKIP regexpr.cpp — gnu_regex.h missing from reference
