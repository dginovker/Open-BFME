// cl: /EHsc /ICode/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

typedef float Real;
typedef int Bool;

struct RGBColor { Real red, green, blue; };

class Overridable {
public:
	void *m_overridePtr;
	char m_isOverridden;
	virtual ~Overridable() {}
};

class WaterTransparencySetting : public Overridable {
public:
	Real m_transparentWaterDepth;
	Real m_minWaterOpacity;
	RGBColor m_standingWaterColor;
	RGBColor m_radarColor;
	Bool m_additiveBlend;
	AsciiString m_standingWaterTexture;

	WaterTransparencySetting();
};

// ??0WaterTransparencySetting@@QAE@XZ present-unmatched 139/139 size, register allocation diff
WaterTransparencySetting::WaterTransparencySetting()
{
	m_transparentWaterDepth = 3.0f;
	m_minWaterOpacity = 1.0f;
	m_standingWaterColor.red = 1.0f;
	m_standingWaterColor.green = 1.0f;
	m_standingWaterColor.blue = 1.0f;
	m_radarColor.red = 140;
	m_radarColor.green = 140;
	m_radarColor.blue = 255;
	m_standingWaterTexture.set("TWWater01.tga");
	m_additiveBlend = 0;
}
