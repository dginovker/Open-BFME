#pragma once

typedef void* HBINK;

void BinkClose(void* bnk);
int BinkWait(void* bnk);
void BinkDoFrame(void* bnk);
void BinkSetVolume(void* bnk, int trackid, int volume);
void BinkCopyToBuffer(void* bnk, void* dest, int destpitch, int destheight, int destx, int desty, unsigned int flags);
void* BinkOpen(const char* name, unsigned int flags);
void BinkSetSoundTrack(int track, int count);
void BinkSoundUseDirectSound(void* dsound);
int BinkGoto(void* bnk, unsigned int frame, int flags);
int BinkNextFrame(void* bnk);

#define BINKPRELOADALL 0
#define BINKSURFACE32  0
#define BINKSURFACE24  1
#define BINKSURFACE565 2
#define BINKSURFACE555 3
