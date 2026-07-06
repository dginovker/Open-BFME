#pragma once
#include "ascii_string.h"
class SubsystemInterface {
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void postProcessLoad() { }
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw( void ) {}
	inline void UPDATE(void) { update(); }
	inline void DRAW(void) { draw(); }
	void setName(AsciiString name);
	AsciiString getName(void);
protected:
	AsciiString m_name;
};
