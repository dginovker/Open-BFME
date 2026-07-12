#pragma once
#include "ascii_string.h"
class GameMessage {
public:
	enum Type { MSG_INVALID = 0 };
	AsciiString getCommandTypeAsAsciiString(Type t);
};
