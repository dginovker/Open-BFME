#pragma once

#include <objbase.h>

// Minimal ATL CComModule for ZH sweep — only methods call sites use.
class CComModule {
public:
	HRESULT Init(void* /*pObjMap*/, HINSTANCE /*h*/) { return S_OK; }
	void Term() {}
	HINSTANCE GetModuleInstance() { return 0; }
	HINSTANCE m_hInst;
};
extern CComModule _Module;
