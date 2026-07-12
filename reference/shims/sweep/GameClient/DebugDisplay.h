#pragma once
// Minimal DebugDisplay interface for ZH particle debug code
class DebugDisplayInterface {
public:
  virtual ~DebugDisplayInterface() {}
  virtual void printf(const char* fmt, ...) {}
  virtual void setCursorPos(int x, int y) {}
  virtual void setRightMargin(int m) {}
  virtual void setLeftMargin(int m) {}
  virtual void setTopMargin(int m) {}
  virtual void setBottomMargin(int m) {}
  virtual int getWidth() const { return 0; }
  virtual int getHeight() const { return 0; }
  virtual int getCursorX() const { return 0; }
  virtual int getCursorY() const { return 0; }
};
