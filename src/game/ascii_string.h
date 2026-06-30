#pragma once

class AsciiString {
public:
    AsciiString();
    AsciiString(char c);
    AsciiString(const AsciiString &that);
    AsciiString(const char *str);
    AsciiString(const char *str, int len);
    AsciiString(const AsciiString &that, int start, int len);
    ~AsciiString();
    AsciiString &operator=(const AsciiString &that);
    AsciiString &operator=(char c);
    AsciiString &operator=(const char *str);
    AsciiString &operator+=(const AsciiString &that);
    AsciiString &operator+=(char c);
    AsciiString &operator+=(const char *str);

    friend AsciiString operator+(AsciiString left, const char *right);
    friend AsciiString operator+(AsciiString left, const AsciiString &right);
    friend AsciiString operator+(AsciiString left, char right);

private:
    char *m_text;
};
