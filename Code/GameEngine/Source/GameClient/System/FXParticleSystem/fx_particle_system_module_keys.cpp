// cl: /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// FXParticleSystem::DefaultModuleKey<N>::GetValue — the module key strings. Each is
// a function-local static AsciiString initialized to "Default" then extended once
// with the category key (GetKey), returning str(). One template body, instantiated
// per category N (0,1,2,3,6,7). All object/guard/literal addresses are DIR32 (masked).
#include "string_base.h"

extern "C" unsigned int __cdecl strlen(const char *str);

// Inline AsciiString: ctor/concat inline to the matched StringBase<char> machinery
// (ctor 0x888bc0, concat 0x887d60), str() folds to the m_data+8 / "" the target uses.
class AsciiString {
public:
    AsciiString(const char *s) { ((StringBase<char> *)this)->StringBase<char>::StringBase(s); }
    ~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
    void concat(const char *s) { ((StringBase<char> *)this)->concat(s, s ? strlen(s) : 0); }
    const char *str() const { return m_text ? m_text + 8 : ""; }

private:
    char *m_text;
};

namespace FXParticleSystem {

enum ModuleCategory {};
const char *GetKey(ModuleCategory category);

template <int N>
struct DefaultModuleKey {
private:
    static const char *GetValue();
};

template <int N>
const char *DefaultModuleKey<N>::GetValue()
{
    static AsciiString value("Default");
    static bool once;
    if (!once) {
        value.concat(GetKey((ModuleCategory)N));
        once = true;
    }
    return value.str();
}

template const char *DefaultModuleKey<0>::GetValue();
template const char *DefaultModuleKey<1>::GetValue();
template const char *DefaultModuleKey<2>::GetValue();
template const char *DefaultModuleKey<3>::GetValue();
template const char *DefaultModuleKey<6>::GetValue();
template const char *DefaultModuleKey<7>::GetValue();

}  // namespace FXParticleSystem
