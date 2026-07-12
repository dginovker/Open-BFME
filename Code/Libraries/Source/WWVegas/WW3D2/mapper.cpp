// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep


#include "mapper.h"
#include "ini.h"
#include "ww3d.h"
#include "meshmatdesc.h"
#include "wwmath.h"
#include "random.h"
#include <stdlib.h>

Random4Class rand4;

TextureMapperClass::TextureMapperClass(unsigned int stage)
{
	Stage = stage;
	if (Stage >= MeshMatDescClass::MAX_TEX_STAGES) Stage = MeshMatDescClass::MAX_TEX_STAGES - 1;
}

ScaleTextureMapperClass::ScaleTextureMapperClass(const Vector2 &scale, unsigned int stage) :
	TextureMapperClass(stage),
	Scale(scale)
{
}

ScaleTextureMapperClass::ScaleTextureMapperClass(const INIClass &ini, const char *section, unsigned int stage) :
	TextureMapperClass(stage)	
{
	Scale.U = ini.Get_Float(section, "UScale", 1.0f);
	Scale.V = ini.Get_Float(section, "VScale", 1.0f);	
}

ScaleTextureMapperClass::ScaleTextureMapperClass(const ScaleTextureMapperClass & src) :
	TextureMapperClass(src),
	Scale(src.Scale)
{
}

LinearOffsetTextureMapperClass::LinearOffsetTextureMapperClass(const Vector2 &offset_per_sec,
		const Vector2 & start_offset, bool clamp_fix, const Vector2 &scale, unsigned int stage) :
	ScaleTextureMapperClass(scale, stage),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	StartingUVOffset(start_offset),
	ClampFix(clamp_fix)
{
	CurrentUVOffset = StartingUVOffset;

	// HY 5/16/01
	// This is horrible disgusting legacy from the unmentionable API we used before
	// leaving it unchanged because the artists have worked around it
	UVOffsetDeltaPerMS = offset_per_sec * -0.001f;
}

LinearOffsetTextureMapperClass::LinearOffsetTextureMapperClass(const INIClass &ini, const char *section, unsigned int stage) :
	ScaleTextureMapperClass(ini,section,stage),
	LastUsedSyncTime(WW3D::Get_Sync_Time())
{
	float u_offset_per_sec = ini.Get_Float(section, "UPerSec", 0.0f);
	float v_offset_per_sec = ini.Get_Float(section, "VPerSec", 0.0f);
	UVOffsetDeltaPerMS = Vector2(u_offset_per_sec, v_offset_per_sec) * -0.001f;

	float u_start_offset = ini.Get_Float(section, "UOffset", 0.0f);
	float v_start_offset = ini.Get_Float(section, "VOffset", 0.0f);
	StartingUVOffset.Set(u_start_offset,	v_start_offset);
	CurrentUVOffset = StartingUVOffset;

	ClampFix = ini.Get_Bool(section, "ClampFix", false);
}

LinearOffsetTextureMapperClass::LinearOffsetTextureMapperClass(const LinearOffsetTextureMapperClass & src) :
	ScaleTextureMapperClass(src),
	UVOffsetDeltaPerMS(src.UVOffsetDeltaPerMS),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	StartingUVOffset(src.StartingUVOffset),
	ClampFix(src.ClampFix)
{
	CurrentUVOffset = StartingUVOffset;	// Reset a mapper as it is created
}

void LinearOffsetTextureMapperClass::Reset(void)
{
	Set_Current_UV_Offset(Vector2(0.0f, 0.0f));
	LastUsedSyncTime = WW3D::Get_Sync_Time();
}

GridTextureMapperClass::GridTextureMapperClass(float fps, unsigned int gridwidth_log2, unsigned int last_frame, unsigned int offset, unsigned int stage) :
	TextureMapperClass(stage),
	LastFrame(last_frame),
	Offset(offset)
{
	initialize(fps, gridwidth_log2);
}

GridTextureMapperClass::GridTextureMapperClass(const INIClass &ini, const char *section, unsigned int stage) :
	TextureMapperClass(stage)
{
	float fps = ini.Get_Float(section, "FPS", 1.0f);
	unsigned int gridwidth_log2 = ini.Get_Int(section, "Log2Width", 1);
	LastFrame = ini.Get_Int(section, "Last", 0);
	Offset = ini.Get_Int(section, "Offset", 0);
	initialize(fps, gridwidth_log2);
}

GridTextureMapperClass::GridTextureMapperClass(const GridTextureMapperClass & src) :
	TextureMapperClass(src),	
	Sign(src.Sign),
	MSPerFrame(src.MSPerFrame),
	OOGridWidth(src.OOGridWidth),
	GridWidthLog2(src.GridWidthLog2),
	LastFrame(src.LastFrame),
	Offset(src.Offset)
{
	Reset();
}

void GridTextureMapperClass::Reset(void)
{
	Remainder = 0;
	if (Sign >= 0) {
		CurrentFrame = Offset;
	} else {
		CurrentFrame = (LastFrame - 1) - Offset;
	}
	LastUsedSyncTime = WW3D::Get_Sync_Time();
}

void GridTextureMapperClass::Set_Frame_Per_Second(float fps)
{
	initialize(fps, GridWidthLog2);
}

void GridTextureMapperClass::initialize(float fps, unsigned int gridwidth_log2)
{
	unsigned int grid_width = (1 << gridwidth_log2);

	if (LastFrame == 0) LastFrame = (grid_width * grid_width);
	Offset = Offset % LastFrame;
	LastUsedSyncTime = WW3D::Get_Sync_Time();
	GridWidthLog2 = gridwidth_log2;
	OOGridWidth = 1.0f / (float)(grid_width);
	if (fps == 0.0f) {
		// Value of MSPerFrame does not matter as long as it is not 0 - sign will multiply results,
		// zeroing them out.
		Sign = 0;
		MSPerFrame = 1;
		CurrentFrame = Offset;
	} else if (fps < 0.0f) {
		Sign = -1;
		MSPerFrame = (unsigned int)(1000.0f / fabs(fps));
		CurrentFrame = (LastFrame - 1) - Offset;
	} else {
		Sign = 1;
		MSPerFrame = (unsigned int)(1000.0f / fabs(fps));
		CurrentFrame = Offset;
	}
	Remainder = 0;
}

void GridTextureMapperClass::update_temporal_state(void)
{
	unsigned int now = WW3D::Get_Sync_Time();
	unsigned int delta = now - LastUsedSyncTime;
	Remainder += delta;
	LastUsedSyncTime = now;

	int new_frame = (int)CurrentFrame + ((int)(Remainder / MSPerFrame) * Sign);
	new_frame=new_frame % LastFrame;

	if (new_frame<0) {
		CurrentFrame=LastFrame+new_frame;
	} else {
		CurrentFrame=(unsigned int) new_frame;
	}
	Remainder = Remainder % MSPerFrame;
}

void GridTextureMapperClass::calculate_uv_offset(float * u_offset, float * v_offset)
{
	unsigned int row_mask = ~(0xFFFFFFFF << GridWidthLog2);
	unsigned int col_mask = row_mask << GridWidthLog2;
	unsigned int x = CurrentFrame & row_mask;
	unsigned int y = (CurrentFrame & col_mask) >> GridWidthLog2;
	*u_offset = x * OOGridWidth;
	*v_offset = y * OOGridWidth;
}

RotateTextureMapperClass::RotateTextureMapperClass(float rad_per_sec, const Vector2 &center, const Vector2 &scale, unsigned int stage) :
	ScaleTextureMapperClass(scale, stage),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	CurrentAngle(0.0f),
	RadiansPerMilliSec(rad_per_sec/1000.0f),
	Center(center)
{
}

RotateTextureMapperClass::RotateTextureMapperClass(const INIClass &ini, const char *section, unsigned int stage) :	
	ScaleTextureMapperClass(ini, section, stage),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	CurrentAngle(0.0f)
{
	RadiansPerMilliSec=2*WWMATH_PI*ini.Get_Float(section,"Speed",0.1f)/1000.0f;
	Center.U=ini.Get_Float(section,"UCenter",0.0f);
	Center.V=ini.Get_Float(section,"VCenter",0.0f);
}

RotateTextureMapperClass::RotateTextureMapperClass(const RotateTextureMapperClass & src) :
	ScaleTextureMapperClass(src),	
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	RadiansPerMilliSec(src.RadiansPerMilliSec),
	CurrentAngle(0.0f),
	Center(src.Center)
{
}

void RotateTextureMapperClass::Reset(void)
{
	CurrentAngle = 0.0f;
	LastUsedSyncTime = WW3D::Get_Sync_Time();
}

SineLinearOffsetTextureMapperClass::SineLinearOffsetTextureMapperClass(const Vector3 &uafp, const Vector3 &vafp, const Vector2 &scale, unsigned int stage) :
	ScaleTextureMapperClass(scale, stage),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	UAFP(uafp),
	VAFP(vafp),
	CurrentAngle(0.0f)
{
}

SineLinearOffsetTextureMapperClass::SineLinearOffsetTextureMapperClass(const INIClass &ini, const char *section, unsigned int stage) :
	ScaleTextureMapperClass(ini, section, stage),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	CurrentAngle(0.0f)
{
	UAFP.X = ini.Get_Float(section, "UAmp", 1.0f);	
	UAFP.Y = ini.Get_Float(section, "UFreq", 1.0f);
	UAFP.Z = ini.Get_Float(section, "UPhase", 0.0f);	

	VAFP.X = ini.Get_Float(section, "VAmp", 1.0f);	
	VAFP.Y = ini.Get_Float(section, "VFreq", 1.0f);
	VAFP.Z = ini.Get_Float(section, "VPhase", 0.0f);
}

SineLinearOffsetTextureMapperClass::SineLinearOffsetTextureMapperClass(const SineLinearOffsetTextureMapperClass & src) :
	ScaleTextureMapperClass(src),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	UAFP(src.UAFP),
	VAFP(src.VAFP),
	CurrentAngle(0.0f)
{	
}

void SineLinearOffsetTextureMapperClass::Reset(void)
{
	CurrentAngle = 0.0f;
	LastUsedSyncTime = WW3D::Get_Sync_Time();
}

StepLinearOffsetTextureMapperClass::StepLinearOffsetTextureMapperClass(const Vector2 &step,
		float steps_per_sec, bool clamp_fix, const Vector2 &scale, unsigned int stage) :
	ScaleTextureMapperClass(scale, stage),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	Step(step),
	StepsPerMilliSec(steps_per_sec/1000.0f),
	CurrentStep(0.0f,0.0f),
	Remainder(0),
	ClampFix(clamp_fix)
{
}

StepLinearOffsetTextureMapperClass::StepLinearOffsetTextureMapperClass(const INIClass &ini, const char *section, unsigned int stage) :
	ScaleTextureMapperClass(ini, section, stage),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	CurrentStep(0.0f,0.0f),
	Remainder(0)
{
	Step.U = ini.Get_Float(section, "UStep", 0.0f);	
	Step.V = ini.Get_Float(section, "VStep", 0.0f);	
	StepsPerMilliSec = ini.Get_Float(section, "SPS", 0.0f)/1000.0f;
	ClampFix = ini.Get_Bool(section, "ClampFix", false);
}

StepLinearOffsetTextureMapperClass::StepLinearOffsetTextureMapperClass(const StepLinearOffsetTextureMapperClass & src) :
	ScaleTextureMapperClass(src),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	Step(src.Step),
	StepsPerMilliSec(src.StepsPerMilliSec),
	CurrentStep(0.0f,0.0f),
	Remainder(0),
	ClampFix(src.ClampFix)
{	
}

void StepLinearOffsetTextureMapperClass::Reset(void)
{
	LastUsedSyncTime = WW3D::Get_Sync_Time();
	CurrentStep.Set(0.0f,0.0f);
	Remainder=0;
}

ZigZagLinearOffsetTextureMapperClass::ZigZagLinearOffsetTextureMapperClass(const Vector2 &speed, float period, const Vector2 &scale, unsigned int stage) :
	ScaleTextureMapperClass(scale, stage),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	Speed(speed/1000.0f),
	Period(period*1000.0f),
	Remainder(0)
{
	// since we're zigzagging, a negative period is the same as a positive one
	if (Period<0.0f) Period=-Period;
	Half_Period=0.5f*Period;
}

ZigZagLinearOffsetTextureMapperClass::ZigZagLinearOffsetTextureMapperClass(const INIClass &ini, const char *section, unsigned int stage) :
	ScaleTextureMapperClass(ini, section, stage),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	Remainder(0)
{
	Speed.U = ini.Get_Float(section, "UPerSec", 0.0f)/1000.0f;
	Speed.V = ini.Get_Float(section, "VPerSec", 0.0f)/1000.0f;
	Period = ini.Get_Float(section, "Period", 0.0f)*1000.0f;
	if (Period<0.0f) Period=-Period;
	Half_Period=0.5f*Period;
}

ZigZagLinearOffsetTextureMapperClass::ZigZagLinearOffsetTextureMapperClass(const ZigZagLinearOffsetTextureMapperClass & src) :
	ScaleTextureMapperClass(src),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),	
	Speed(src.Speed),
	Period(src.Period),
	Half_Period(src.Half_Period),
	Remainder(0)
{		
}

void ZigZagLinearOffsetTextureMapperClass::Reset(void)
{
	LastUsedSyncTime = WW3D::Get_Sync_Time();
	Remainder=0;
}

EdgeMapperClass::EdgeMapperClass(unsigned int stage) :
	TextureMapperClass(stage),
	VSpeed(0.0f),
	UseReflect(false),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	VOffset(0.0f)
{
}

EdgeMapperClass::EdgeMapperClass(const INIClass &ini, const char *section, unsigned int stage) :
	TextureMapperClass(stage),
	VSpeed(0.0f),
	UseReflect(false),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	VOffset(0.0f)
{
	VSpeed=ini.Get_Float(section, "VPerSec", 0.0f);
	VOffset=ini.Get_Float(section, "VStart", 0.0f);
	UseReflect=ini.Get_Bool(section, "UseReflect", false);
}

EdgeMapperClass::EdgeMapperClass(const EdgeMapperClass & src):
	TextureMapperClass(src.Stage),
	VSpeed(src.VSpeed),
	UseReflect(src.UseReflect),
	VOffset(src.VOffset),
	LastUsedSyncTime(WW3D::Get_Sync_Time())
{
}

void EdgeMapperClass::Reset(void)
{
	LastUsedSyncTime = WW3D::Get_Sync_Time();
	VOffset = 0.0f;
}

WSEnvMapperClass::WSEnvMapperClass(const INIClass &ini, const char *section, unsigned int stage) :
	TextureMapperClass(stage),
	Axis(AXISTYPE_Z)
{
	char temp[2];
	ini.Get_String(section, "Axis", "Z", &temp[0], 2);
	switch(temp[0]) {
		case 'X':
		case 'x':
			Axis = AXISTYPE_X;
			break;
		case 'Y':
		case 'y':
			Axis = AXISTYPE_Y;
			break;
		case 'Z':
		case 'z':
			Axis = AXISTYPE_Z;
			break;
		default:
			Axis = AXISTYPE_Z;
			break;
	}
}

RandomTextureMapperClass::RandomTextureMapperClass(float fps, const Vector2 &scale, unsigned int stage):
	ScaleTextureMapperClass(scale, stage),
	FPMS(fps/1000.0f),	
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	Speed(0.0f,0.0f),
	Remainder(0)
{
	randomize();
}

RandomTextureMapperClass::RandomTextureMapperClass(const INIClass &ini, const char *section, unsigned int stage):
	ScaleTextureMapperClass(ini, section, stage),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	Remainder(0)
{
	FPMS = ini.Get_Float(section, "FPS", 0.0f)/1000.0f;
	Speed.U = ini.Get_Float(section, "UPerSec", 0.0f)/1000.0f;
	Speed.V = ini.Get_Float(section, "VPerSec", 0.0f)/1000.0f;
	randomize();
}

RandomTextureMapperClass::RandomTextureMapperClass(const RandomTextureMapperClass & src):
	ScaleTextureMapperClass(src),
	FPMS(src.FPMS),	
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	Speed(src.Speed),
	Remainder(0)
{
	randomize();
}

// ?randomize@RandomTextureMapperClass@@IAEXXZ absent-from-retail
// Kept so the Random ctors above inline it byte-identically; the retail image has no
// standalone copy (fully inlined, address never taken).
void RandomTextureMapperClass::randomize(void)
{
	CurrentAngle=2*WWMATH_PI*rand4.Get_Float();
	Center.U=rand4.Get_Float();
	Center.V=rand4.Get_Float();
}

void RandomTextureMapperClass::Reset(void)
{
	LastUsedSyncTime = WW3D::Get_Sync_Time();
	Remainder=0;
}

BumpEnvTextureMapperClass::BumpEnvTextureMapperClass(float rad_per_sec, float scale_factor,
		const Vector2 & offset_per_sec, const Vector2 & start_offset, bool clamp_fix,
		const Vector2 &scale, unsigned int stage) :
	LinearOffsetTextureMapperClass(offset_per_sec, start_offset, clamp_fix, scale, stage),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	CurrentAngle(0.0f),
	RadiansPerSecond(rad_per_sec),
	ScaleFactor(scale_factor)
{
}

BumpEnvTextureMapperClass::BumpEnvTextureMapperClass(INIClass &ini, char *section, unsigned int stage) :	
	LinearOffsetTextureMapperClass(ini, section, stage),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	CurrentAngle(0.0f)
{
	RadiansPerSecond = 2*WWMATH_PI*ini.Get_Float(section,"BumpRotation",0.0f);	
	ScaleFactor = ini.Get_Float(section,"BumpScale",1.0f);
}

BumpEnvTextureMapperClass::BumpEnvTextureMapperClass(const BumpEnvTextureMapperClass & src) :
	LinearOffsetTextureMapperClass(src),	
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	CurrentAngle(0.0f),
	RadiansPerSecond(src.RadiansPerSecond),
	ScaleFactor(src.ScaleFactor)
{
}

GridWSEnvMapperClass::GridWSEnvMapperClass(float fps, unsigned int gridwidth_log2, unsigned int last_frame, unsigned int offset, AxisType axis, unsigned int stage):
	GridTextureMapperClass(fps, gridwidth_log2, last_frame, offset, stage),
	Axis(axis)
{
}

GridWSEnvMapperClass::GridWSEnvMapperClass(const GridWSEnvMapperClass & src) :
	GridTextureMapperClass(src),
	Axis(src.Axis)
{
}

GridWSEnvMapperClass::GridWSEnvMapperClass(const INIClass &ini, const char *section, unsigned int stage) :
	GridTextureMapperClass(ini, section, stage),
	Axis(AXISTYPE_Z)
{
	char temp[2];
	ini.Get_String(section, "Axis", "Z", &temp[0], 2);
	switch(temp[0]) {
		case 'X':
		case 'x':
			Axis = AXISTYPE_X;
			break;
		case 'Y':
		case 'y':
			Axis = AXISTYPE_Y;
			break;
		case 'Z':
		case 'z':
			Axis = AXISTYPE_Z;
			break;
		default:
			Axis = AXISTYPE_Z;
			break;
	}
}

// GridWSClassicEnvironmentMapperClass / GridWSEnvironmentMapperClass forwarding ctors are
// omitted: they are trivial base-class forwarders that the retail build inlined at their
// NEW_REF sites (not emitted as standalone functions), so there is nothing to byte-match.
