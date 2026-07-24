#pragma once
#include "ascii_string.h"

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

struct Coord3D;
struct ICoord2D;
struct IRegion2D;

class GameMessage {
public:
	enum Type { MSG_INVALID = 0 };
	AsciiString getCommandTypeAsAsciiString(Type t);

	// Argument-list mutators: each allocates a new GameMessageArgument (via the
	// not-yet-converted allocArg(), REL32-pinned in reverse/symbols.csv) and
	// stores the value at m_data@+0x8 / m_type@+0x18 of the returned argument.
	void appendIntegerArgument(Int arg);
	void appendRealArgument(Real arg);
	void appendBooleanArgument(Bool arg);
	void appendObjectIDArgument(UnsignedInt arg);
	void appendDrawableIDArgument(UnsignedInt arg);
	void appendTeamIDArgument(UnsignedInt arg);
	void appendLocationArgument(const Coord3D &arg);
	void appendPixelArgument(const ICoord2D &arg);
	void appendPixelRegionArgument(const IRegion2D &arg);
	void appendTimestampArgument(UnsignedInt arg);
	void appendWideCharArgument(const WideChar &arg);

private:
	struct Argument;
	Argument *allocArg();
};
