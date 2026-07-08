# PROGRESS: port-wwlib-1

## Done (pre-existing on branch)
DONE crc.cpp
DONE gcd_lcm.cpp

## Skipped
SKIP _convert.cpp — 0 located; not in binary
SKIP _mono.cpp — 0 located; not in binary
SKIP _timer.cpp — 0 located; timer ctors absent
SKIP argv.cpp — 0 located; not in binary
SKIP bfiofile.cpp — 0 located after errno fix; not in binary
SKIP blit.cpp — 0 located; surface functions absent
SKIP blowfish.cpp — 0 located; not in binary
SKIP blowpipe.cpp — 0 located; not in binary
SKIP blwstraw.cpp — 0 located; not in binary
SKIP convert.cpp — dsurface.h includes ddraw.h
SKIP cpudetect.cpp — includes windows.h / wwdebug.h
SKIP crcpipe.cpp — 0 located; not in binary
SKIP crcstraw.cpp — 0 located; not in binary
SKIP critsection.cpp — 0 located; not in binary
SKIP data.cpp — uses Win32 resource APIs (LoadString/FindResource/etc.)
SKIP ddraw.cpp — dsurface.h leads to ddraw.h
SKIP dib.cpp — uses Win32 GDI APIs
SKIP draw.cpp — dsurface.h leads to ddraw.h
SKIP dsurface.cpp — dsurface.h leads to ddraw.h
SKIP Except.cpp — includes windows.h / imagehlp.h / wwdebug.h
SKIP FastAllocator.cpp — shared fastallocator.h missing FastCriticalSectionClass
SKIP fixed.cpp — 0 located; not in binary
SKIP hsv.cpp — 0 located; not in binary
SKIP jshell.cpp — 0 located; not in binary
SKIP keyboard.cpp — msgloop.h includes windows.h
