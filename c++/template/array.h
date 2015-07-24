#ifndef ARRAY_H
#define ARRAY_H

template<typename T>
class Array {
public:
    Array();
    explicit Array(int size);
    ~Array();
    T operator[](int index) const;

    int size() const;
    T get(int index) const;
    void set(int index, const T& element);

private:
    Array(const Array&);
    void operator=(const Array&);

    void init(int size);

    T* m_array;
    int m_size;
};

#include "details/array.h"

#endif // ARRAY_H
