#pragma once

template <typename T>
class StringBase {
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
    int compare(const T *str) const;
    void clear();

private:
    StringBase();
    void validate() const;
    T *peek() const;

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
