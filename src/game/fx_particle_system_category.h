#pragma once

namespace FXParticleSystem {

template <int Category>
class CategoryModuleClass;

template <int Category, int SubCategory = 1>
class CategoryModuleClassBase {
public:
    virtual ~CategoryModuleClassBase() {}
    CategoryModuleClassBase &operator=(const CategoryModuleClassBase &that) { return *this; }

    static const CategoryModuleClass<Category> &getDefault();

protected:
    static CategoryModuleClass<Category> *s_defaultModule;
};

template <int Category>
class CategoryModuleClass : public CategoryModuleClassBase<Category> {
public:
    const char *getKey() const { return m_key; }
    const char *getName() const { return m_name; }
    const CategoryModuleClass *getNext() const { return m_next; }

    static const CategoryModuleClass *getFirst() { return s_firstList; }

protected:
    ~CategoryModuleClass();
    CategoryModuleClass(bool setDefault, const char *key, const char *name);

    const char *m_key;
    const char *m_name;
    CategoryModuleClass *m_next;
    static CategoryModuleClass *s_firstList;
};

template <int Category>
CategoryModuleClass<Category> *CategoryModuleClass<Category>::s_firstList = 0;

template <int Category, int SubCategory>
CategoryModuleClass<Category> *CategoryModuleClassBase<Category, SubCategory>::s_defaultModule = 0;

template <int Category, int SubCategory>
const CategoryModuleClass<Category> &CategoryModuleClassBase<Category, SubCategory>::getDefault()
{
    return *s_defaultModule;
}

}
