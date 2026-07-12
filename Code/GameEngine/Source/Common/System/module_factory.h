#pragma once

// ModuleFactory shim for matching ModuleFactory::init (0x0012C2E0, the binary's
// largest function). init() registers 247 module templates. The registration
// helper addModuleInternal is defined out-of-line so MSVC inlines it into init()
// for the early registrations (matching the target) and emits the shared body
// for the rest; makeDecoratedNameKey and the template-map operator[] are the
// out-of-line helpers the target calls (pinned in reverse/symbols.csv).
#include "string_base.h"

typedef int NameKeyType;
typedef int ModuleType;

// A temporary AsciiString whose ctor/dtor inline to the (already matched)
// StringBase<char> machinery, so each `AsciiString("Name")` compiles to the
// target's StringBase ctor (0x888bc0) + releaseBuffer (0x887940) pair.
class AsciiString {
public:
    AsciiString(const char *str) { ((StringBase<char> *)this)->StringBase<char>::StringBase(str); }
    ~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

private:
    char *m_text;
};

class ModuleFactory {
public:
    virtual void init(void);

protected:
    class ModuleTemplate {
    public:
        const void *m_createProc;      // +0x0
        const void *m_createDataProc;  // +0x4
        const void *m_data;            // +0x8
        int m_whichInterfaces;         // +0xC
    };

    class ModuleTemplateMap {
    public:
        ModuleTemplate &operator[](const NameKeyType &key);

    private:
        void *m_rep[3];
    };

    // The registration helper (shared body at 0x00129AC0). The target inlines it
    // for the first 101 modules and calls it out-of-line for the remaining 146
    // (MSVC's inline budget); init() hand-inlines the early ones and marks this
    // noinline so the tail registrations stay as out-of-line calls.
    __declspec(noinline) void addModuleInternal(const void *proc, const void *dataproc, const void *data,
                                                ModuleType type, const AsciiString &name, int whichIntf);
    static NameKeyType makeDecoratedNameKey(const AsciiString &name, ModuleType type);

    // vptr@0 + 8 bytes -> m_moduleTemplateMap lands at this+0xC, as the target's
    // `lea ebx,[esi+0xc]` (SubsystemInterface + Snapshot subobjects) requires.
    void *m_pad1;
    void *m_pad2;
    ModuleTemplateMap m_moduleTemplateMap;
};
