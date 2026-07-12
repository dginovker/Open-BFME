#pragma once

#include "string_base.h"

class UnicodeString;

class AsciiString {
public:
    AsciiString();
    AsciiString(char c);
    AsciiString(const AsciiString &that);
    AsciiString(const char *str);
    AsciiString(const char *str, int len);
    AsciiString(const AsciiString &that, int start, int len);
    AsciiString(const UnicodeString &that);
    ~AsciiString();
    AsciiString &operator=(const AsciiString &that);
    AsciiString &operator=(char c);
    AsciiString &operator=(const char *str);
    AsciiString &operator=(const UnicodeString &that);
    AsciiString &operator+=(const AsciiString &that);
    AsciiString &operator+=(char c);
    AsciiString &operator+=(const char *str);
    AsciiString &operator+=(const UnicodeString &that);
    void __cdecl format(AsciiString fmt, ...);
    void translate(const UnicodeString &that);
    // BFME's AsciiString exposes StringBase<char>'s methods (they mangle
    // @StringBase@D and are matched in string_base.cpp). Delegate so a caller
    // inlines a `call StringBase<char>::method` to the matched implementation.
    const char *str() const { return ((const StringBase<char>*)this)->str(); }
    int getLength() const { return ((const StringBase<char>*)this)->getLength(); }
    char getCharAt(int i) const { return ((const StringBase<char>*)this)->getCharAt(i); }
    bool isEmpty() const { return ((const StringBase<char>*)this)->isEmpty(); }
    bool isNotEmpty() const { return ((const StringBase<char>*)this)->isNotEmpty(); }
    bool isNone() const { return ((const StringBase<char>*)this)->isNone(); }
    bool isNotNone() const { return ((const StringBase<char>*)this)->isNotNone(); }
    const char *reverseFind(char c) const { return ((const StringBase<char>*)this)->reverseFind(c); }
    bool nextToken(AsciiString *tok, const char *delims=0) { return ((StringBase<char>*)this)->nextToken((StringBase<char>*)tok, delims); }
    void clear() { ((StringBase<char>*)this)->clear(); }
    void set(const char *s) { ((StringBase<char>*)this)->set(s); }
    void set(const AsciiString &s) { ((StringBase<char>*)this)->set(*(const StringBase<char>*)&s); }
    void concat(const char *s) { ((StringBase<char>*)this)->concat(s); }
    void concat(char c) { ((StringBase<char>*)this)->concat(c); }
    void concat(const AsciiString &s) { ((StringBase<char>*)this)->concat(*(const StringBase<char>*)&s); }
    void toLower() { ((StringBase<char>*)this)->toLower(); }
    void toUpper() { ((StringBase<char>*)this)->toUpper(); }
    void trim() { ((StringBase<char>*)this)->trim(); }
    void removeLastChar() { ((StringBase<char>*)this)->removeLastChar(); }
    const char *find(char c) const { return ((const StringBase<char>*)this)->find(c); }
    bool startsWith(const char *p) const { return ((const StringBase<char>*)this)->startsWith(p); }
    bool startsWithNoCase(const char *p) const { return ((const StringBase<char>*)this)->startsWithNoCase(p); }
    bool endsWith(const char *p) const { return ((const StringBase<char>*)this)->endsWith(p); }
    bool endsWithNoCase(const char *p) const { return ((const StringBase<char>*)this)->endsWithNoCase(p); }
    int compare(const char *p) const { return ((const StringBase<char>*)this)->compare(p); }
    int compareNoCase(const char *p) const { return ((const StringBase<char>*)this)->compareNoCase(p); }
    int compare(const AsciiString &s) const { return ((const StringBase<char>*)this)->compare(*(const StringBase<char>*)&s); }
    int compareNoCase(const AsciiString &s) const { return ((const StringBase<char>*)this)->compareNoCase(*(const StringBase<char>*)&s); }

    friend AsciiString operator+(AsciiString left, const char *right);
    friend AsciiString operator+(AsciiString left, const AsciiString &right);
    friend AsciiString operator+(AsciiString left, char right);

private:
    char *m_text;
};

inline bool operator==(const AsciiString &a, const AsciiString &b) { return *(const StringBase<char>*)&a == *(const StringBase<char>*)&b; }
inline bool operator!=(const AsciiString &a, const AsciiString &b) { return *(const StringBase<char>*)&a != *(const StringBase<char>*)&b; }
inline bool operator<(const AsciiString &a, const AsciiString &b) { return *(const StringBase<char>*)&a < *(const StringBase<char>*)&b; }
