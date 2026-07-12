#pragma once
#include "ascii_string.h"
class INI {
public:
	const char* getNextToken(const char* seps = 0);
	const char* getNextTokenOrNull(const char* seps = 0);
	static float scanReal(const char* token);
	static int scanInt(const char* token);
	static int scanBool(const char* token);
	static int scanIndexList(const char* token, const char* const* names);
};
typedef void (*INIFieldParseProc)(INI*, void*, void*, const void*);
struct FieldParse { const char* token; INIFieldParseProc parse; const void* userData; int offset; };
