#include "fx_particle_system_category.h"

namespace FXParticleSystem {

// Category 0 (draw)
template <> CategoryModuleClass<0>::CategoryModuleClass(bool, const char *, const char *) {}
template <> CategoryModuleClass<0>::~CategoryModuleClass() { *(void **)this = (void *)0x01110838; }

// Category 1 (update)
template <> CategoryModuleClass<1>::CategoryModuleClass(bool, const char *, const char *) {}
template <> CategoryModuleClass<1>::~CategoryModuleClass() { *(void **)this = (void *)0x0111085C; }

// Category 2 (emission)
template <> CategoryModuleClass<2>::CategoryModuleClass(bool, const char *, const char *) {}
template <> CategoryModuleClass<2>::~CategoryModuleClass() { *(void **)this = (void *)0x01110850; }

// Category 3 (velocity)
template <> CategoryModuleClass<3>::CategoryModuleClass(bool, const char *, const char *) {}
template <> CategoryModuleClass<3>::~CategoryModuleClass() { *(void **)this = (void *)0x01110880; }

// Category 4 (volume)
template <> CategoryModuleClass<4>::CategoryModuleClass(bool, const char *, const char *) {}
template <> CategoryModuleClass<4>::~CategoryModuleClass() { *(void **)this = (void *)0x0111088C; }

// Category 5 (life event)
template <> CategoryModuleClass<5>::CategoryModuleClass(bool, const char *, const char *) {}
template <> CategoryModuleClass<5>::~CategoryModuleClass() { *(void **)this = (void *)0x01110820; }

// Category 6 (collision)
template <> CategoryModuleClass<6>::CategoryModuleClass(bool, const char *, const char *) {}
template <> CategoryModuleClass<6>::~CategoryModuleClass() { *(void **)this = (void *)0x01110868; }

// Category 7 (wind)
template <> CategoryModuleClass<7>::CategoryModuleClass(bool, const char *, const char *) {}
template <> CategoryModuleClass<7>::~CategoryModuleClass() { *(void **)this = (void *)0x01110874; }

// Category 8 (default/particle)
template <> CategoryModuleClass<8>::CategoryModuleClass(bool, const char *, const char *) {}
template <> CategoryModuleClass<8>::~CategoryModuleClass() { *(void **)this = (void *)0x01110844; }

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
