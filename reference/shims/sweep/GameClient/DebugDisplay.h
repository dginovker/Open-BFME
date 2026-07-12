#pragma once
// Minimal DebugDisplay for ZH sweep — real header missing from the open-source tree.
// Provides DebugDisplayInterface (used by ParticleSys etc.) and DebugDisplay
// (base of W3DDebugDisplay).

#ifndef __DEBUGDISPLAY_H__
#define __DEBUGDISPLAY_H__

#include "Lib/Basetype.h"
#include <stdio.h>
#include <stdarg.h>

class DebugDisplayInterface {
public:
	virtual ~DebugDisplayInterface() {}
	virtual void printf(const char* fmt, ...) = 0;
	virtual void setCursorPos(Int x, Int y) = 0;
	virtual void setRightMargin(Int m) = 0;
	virtual void setLeftMargin(Int m) = 0;
	virtual void setTopMargin(Int m) = 0;
	virtual void setBottomMargin(Int m) = 0;
	virtual Int getWidth() const = 0;
	virtual Int getHeight() const = 0;
	virtual Int getCursorX() const = 0;
	virtual Int getCursorY() const = 0;
};

// Concrete base that W3DDebugDisplay inherits; drawText is the render hook.
class DebugDisplay : public DebugDisplayInterface {
public:
	DebugDisplay()
		: m_x(0), m_y(0), m_left(0), m_top(0), m_right(0), m_bottom(0),
		  m_width(0), m_height(0) {}
	virtual ~DebugDisplay() {}

	virtual void printf(const char* fmt, ...) {
		char buf[512];
		va_list args;
		va_start(args, fmt);
		_vsnprintf(buf, sizeof(buf), fmt, args);
		va_end(args);
		buf[sizeof(buf) - 1] = 0;
		// walk string and draw; newlines advance cursor
		for (char* p = buf; *p; ++p) {
			if (*p == '\n') {
				m_x = m_left;
				++m_y;
			} else {
				char ch[2] = { *p, 0 };
				drawText(m_x, m_y, ch);
				++m_x;
			}
		}
	}
	virtual void setCursorPos(Int x, Int y) { m_x = x; m_y = y; }
	virtual void setRightMargin(Int m) { m_right = m; }
	virtual void setLeftMargin(Int m) { m_left = m; }
	virtual void setTopMargin(Int m) { m_top = m; }
	virtual void setBottomMargin(Int m) { m_bottom = m; }
	virtual Int getWidth() const { return m_width; }
	virtual Int getHeight() const { return m_height; }
	virtual Int getCursorX() const { return m_x; }
	virtual Int getCursorY() const { return m_y; }

protected:
	virtual void drawText(Int x, Int y, Char *text) = 0;
	Int m_x, m_y;
	Int m_left, m_top, m_right, m_bottom;
	Int m_width, m_height;
};

#endif
