#pragma once
// ScriptEngine::init registers all script action templates. Landed as naked asm (whale):
// C++ capped at ~44% by global regalloc across 537 blocks. See reverse/whale_scriptengine/.
class ScriptEngine {
public:
	virtual void init();
};
