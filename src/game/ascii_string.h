#pragma once

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
    const char *str() const { return m_text; }

    friend AsciiString operator+(AsciiString left, const char *right);
    friend AsciiString operator+(AsciiString left, const AsciiString &right);
    friend AsciiString operator+(AsciiString left, char right);

private:
    char *m_text;
};
