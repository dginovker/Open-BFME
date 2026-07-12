#pragma once
#include "ascii_string.h"
class VideoBuffer {
public:
	int allocate(unsigned int w, unsigned int h);
	void close(void);
	unsigned int width(void);
	unsigned int height(void);
};
class VideoStreamInterface {
public:
	void close(void);
	void update(void);
	int isFrameReady(void);
	void frameDecompress(void);
	void frameRender(VideoBuffer*);
	void frameNext(void);
	int frameIndex(void);
	unsigned int width(void);
	unsigned int height(void);
};
class VideoPlayerInterface { public: VideoStreamInterface* open(AsciiString); VideoStreamInterface* load(AsciiString); };
extern VideoPlayerInterface* TheVideoPlayer;
