#ifndef ARRAY_H
#define ARRAY_H

template<typename T>
class Array {
public:
    Array();
    explicit Array(int size);
    ~Array();
    T& operator[](int index) const;

    int Size() const;
    T& Get(int index) const;
    void Set(int index, const T& element);

private:
    Array(const Array&);
    void operator=(const Array&);

    void init(int size);

    const int m_size;
    T* m_array;
};

#include "array_impl.h"

#endif // ARRAY_H
