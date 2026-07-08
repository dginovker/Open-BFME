# PROGRESS: port-wwlib-3

## Done (pre-existing on branch)
DONE strtok_r.cpp

## Done (this pass)
DONE stimer.cpp

## Skipped
SKIP registry.cpp — includes windows.h
SKIP rgb.cpp — 0 located; not in binary
SKIP rle.cpp — 0 located; not in binary
SKIP rndstraw.cpp — 0 located; not in binary
SKIP rndstrng.cpp — 0 located; not in binary
SKIP sampler.cpp — 0 located; not in binary
SKIP sha.cpp — requires old-style iostream.h
SKIP shapipe.cpp — 0 located; not in binary
SKIP shastraw.cpp — 0 located; not in binary
SKIP slnode.cpp — 0 located; not in binary
SKIP srandom.cpp — linux/win platform-specific includes
SKIP surface.cpp — 0 located; not in binary
SKIP tagblock.cpp — 0 located; not in binary
SKIP textfile.cpp — StringClass::Erase missing from shared wwstring.h
SKIP tgatodxt.cpp — nvdxtlib.h + wwdebug.h
SKIP thread.cpp — includes windows.h / wwdebug.h
SKIP vector.cpp — 0 located; not in binary
SKIP verchk.cpp — includes windows.h / winnt.h
SKIP widestring.cpp — shared widestring.h WCHAR redefinition
SKIP win.cpp — includes wwdebug.h
SKIP WWCOMUtil.cpp — requires oaidl.h (COM)
SKIP wwfile.cpp — 0 located; not in binary
SKIP wwfont.cpp — 0 located; not in binary
SKIP wwmouse.cpp — surface/draw header chain
SKIP xsurface.cpp — blit.h missing, surface chain
