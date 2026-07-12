#pragma once
// Minimal BFME/ZH profile stubs for sweep/land compile
#ifndef PROFILE_H_SHIM
#define PROFILE_H_SHIM
inline void ProfileInit() {}
inline void ProfileShutdown() {}
inline void ProfileStart(const char*) {}
inline void ProfileStop(const char*) {}
#define PROFILE(name) ((void)0)
#endif
