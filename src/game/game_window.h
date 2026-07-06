#pragma once
class VideoBuffer;
class WinInstanceData { public: void setVideoBuffer(VideoBuffer*); };
class GameWindow {
public:
	WinInstanceData* winGetInstanceData(void);
	int winIsHidden(void);
};
