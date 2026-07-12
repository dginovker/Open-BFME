#pragma once
// Minimal direct.h for ZH sweep
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
char * __cdecl getcwd(char *buffer, int maxlen);
char * __cdecl _getcwd(char *buffer, int maxlen);
int __cdecl chdir(const char *path);
int __cdecl _chdir(const char *path);
int __cdecl mkdir(const char *path);
int __cdecl _mkdir(const char *path);
#ifdef __cplusplus
}
#endif
#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif
