#include "fx_particle_system_category.h"

namespace FXParticleSystem {

#define CAT_BASE(N)                                                                                 \
    template <> CategoryModuleClassBase<N>::CategoryModuleClassBase(const CategoryModuleClass<N> &module, bool setDefault) \
    {                                                                                               \
        if (setDefault)                                                                             \
            s_defaultModule = const_cast<CategoryModuleClass<N> *>(&module);                        \
    }

#define CAT_DERIVED(N)                                                                              \
    template <> CategoryModuleClass<N>::CategoryModuleClass(bool setDefault, const char *key, const char *name) \
        : CategoryModuleClassBase<N>(*this, setDefault)                                             \
    {                                                                                               \
        m_key = key;                                                                                \
        m_name = name;                                                                              \
        m_next = s_firstList;                                                                       \
        s_firstList = this;                                                                         \
    }

// Categories 0..7 have a default module; the base constructor records it.
CAT_BASE(0)
CAT_BASE(1)
CAT_BASE(2)
CAT_BASE(3)
CAT_BASE(4)
CAT_BASE(5)
CAT_BASE(6)
CAT_BASE(7)

// Category 0 here maps to the binary's category 8 (default/particle), which has a default.
CAT_DERIVED(0)
// Categories 1..7 map to binary categories 0..6, all of which have defaults.
CAT_DERIVED(1)
CAT_DERIVED(2)
CAT_DERIVED(3)
CAT_DERIVED(4)
CAT_DERIVED(5)
CAT_DERIVED(6)
CAT_DERIVED(7)

// Category 8 here maps to the binary's category 7 (wind), which has no default module.
template <> CategoryModuleClass<8>::CategoryModuleClass(bool, const char *key, const char *name)
{
    m_key = key;
    m_name = name;
    m_next = s_firstList;
    s_firstList = this;
}

// Destructors: the compiler emits the vtable reset automatically because
// CategoryModuleClass has a virtual destructor; the exact vtable address is
// filled in by the patcher from the original binary.
template <> CategoryModuleClass<0>::~CategoryModuleClass() {}
template <> CategoryModuleClass<1>::~CategoryModuleClass() {}
template <> CategoryModuleClass<2>::~CategoryModuleClass() {}
template <> CategoryModuleClass<3>::~CategoryModuleClass() {}
template <> CategoryModuleClass<4>::~CategoryModuleClass() {}
template <> CategoryModuleClass<5>::~CategoryModuleClass() {}
template <> CategoryModuleClass<6>::~CategoryModuleClass() {}
template <> CategoryModuleClass<7>::~CategoryModuleClass() {}
template <> CategoryModuleClass<8>::~CategoryModuleClass() {}

// Explicitly instantiate the simple accessor methods for every module category
// used by the original binary. The literals are shifted because MSVC 7.1 encodes
// template non-type arguments differently depending on the values present in the
// translation unit; 0 maps to category 10 ($0A@) and 1..8 map to categories 0..7.
template class CategoryModuleClass<0>;
template class CategoryModuleClass<1>;
template class CategoryModuleClass<2>;
template class CategoryModuleClass<3>;
template class CategoryModuleClass<4>;
template class CategoryModuleClass<5>;
template class CategoryModuleClass<6>;
template class CategoryModuleClass<7>;
template class CategoryModuleClass<8>;

}
