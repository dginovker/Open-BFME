#pragma once
class VideoBuffer;
class DisplayInterface { public: VideoBuffer* createVideoBuffer(void); };
extern DisplayInterface* TheDisplay;
