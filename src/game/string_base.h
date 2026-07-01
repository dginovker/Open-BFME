#pragma once

template <typename T>
class StringBase {
    friend class AsciiString;

public:
    void debugIgnoreLeaks();
    bool isEmpty() const;
    bool isNotEmpty() const;
    bool isNone() const;
    bool isNotNone() const;
    int getLength() const;
    const T *str() const;
    const T *find(T c) const;
    T getCharAt(int index) const;
    StringBase<T> &operator=(const StringBase<T> &src);
    int compare(const StringBase<T> &str) const;
    int compare(const T *str) const;
    int compare(const T *str, int len) const;
    int compareNoCase(const StringBase<T> &str) const;
    int compareNoCase(const T *str) const;
    int compareNoCase(const T *str, int len) const;
    void concat(const StringBase<T> &str);
    void concat(T c);
    void concat(const T *str);
    void concat(const T *str, int len);
    const T *reverseFind(T c) const;
    bool startsWith(const StringBase<T> &str) const;
    bool startsWith(const T *str) const;
    bool startsWith(const T *str, int len) const;
    bool startsWithNoCase(const StringBase<T> &str) const;
    bool startsWithNoCase(const T *str) const;
    bool startsWithNoCase(const T *str, int len) const;
    bool endsWith(const StringBase<T> &str) const;
    bool endsWith(const T *str) const;
    bool endsWith(const T *str, int len) const;
    bool endsWithNoCase(const StringBase<T> &str) const;
    bool endsWithNoCase(const T *str) const;
    bool endsWithNoCase(const T *str, int len) const;
    void set(const StringBase<T> &src);
    void set(const StringBase<T> &src, int start, int len);
    void set(T c);
    void set(const T *str);
    void set(const T *str, int len);
    void swap(StringBase<T> &other);
    void clear();
    void __cdecl format(const T *fmt, ...);
    void format_va(const StringBase<T> &fmt, char *args);
    void format_va(const T *fmt, char *args);
    T *getBufferForRead(int len);
    bool nextToken(StringBase<T> *out, const T *delimiters);
    void removeLastChar();
    void toLower();
    void toUpper();
    void trim();

private:
    StringBase();
    StringBase(T c);
    StringBase(const T *str);
    StringBase(const T *str, int len);
    StringBase(const StringBase<T> &src);
    StringBase(const StringBase<T> &src, int start, int len);
    ~StringBase();
    void validate() const;
    T *peek() const;
    void releaseBuffer();
    void ensureUniqueBufferOfSize(int newLen, bool keepData, const T *src1, int src1Len, const T *src2, int src2Len);

private:
    struct Header {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

template <typename T>
bool operator<(const StringBase<T> &left, const StringBase<T> &right);

template <typename T>
bool operator==(const StringBase<T> &left, const StringBase<T> &right);

template <typename T>
bool operator!=(const StringBase<T> &left, const StringBase<T> &right);

template <typename T>
bool operator!=(const StringBase<T> &left, const T *right);

class Debug;
Debug &operator<<(Debug &debug, const StringBase<char> &str);

template <typename T>
bool operator!=(const T *left, const StringBase<T> &right);
