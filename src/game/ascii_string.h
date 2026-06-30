#pragma once

class AsciiString {
public:
    AsciiString();
    AsciiString(char c);
    AsciiString(const AsciiString &that);
    AsciiString(const char *str, int len);
    ~AsciiString();
    AsciiString &operator=(const AsciiString &that);
    AsciiString &operator=(const char *str);
    AsciiString &operator+=(const AsciiString &that);
    AsciiString &operator+=(char c);
    AsciiString &operator+=(const char *str);

private:
    char *m_text;
};
