#pragma once
// Minimal process.h for ZH sweep (_spawnl sites in MainMenu etc.)
#ifndef _P_WAIT
#define _P_WAIT 0
#define _P_NOWAIT 1
#define _P_OVERLAY 2
#define _P_NOWAITO 3
#define _P_DETACH 4
#endif
#ifdef __cplusplus
extern "C" {
#endif
int __cdecl _spawnl(int mode, const char *cmdname, const char *arg0, ...);
int __cdecl _spawnlp(int mode, const char *cmdname, const char *arg0, ...);
int __cdecl _spawnv(int mode, const char *cmdname, const char *const *argv);
int __cdecl _spawnvp(int mode, const char *cmdname, const char *const *argv);
#ifdef __cplusplus
}
#endif
