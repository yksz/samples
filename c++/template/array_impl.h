#include "array.h"
#include <sstream>
#include <stdexcept>

template<typename T>
Array<T>::Array() : m_size(10) {
    init(m_size);
}

template<typename T>
Array<T>::Array(int size) : m_size(size) {
    init(size);
}

template<typename T>
void Array<T>::init(int size) {
    m_array = new T[size];
}

template<typename T>
Array<T>::~Array() {
    delete[] m_array;
}

template<typename T>
T& Array<T>::operator[](int index) const {
    return Get(index);
}

template<typename T>
int Array<T>::Size() const {
    return m_size;
}

static void checkIndex(int index, int size) {
    if (index < 0 || index >= size) {
        std::stringstream msg;
        msg << "checkIndex: index=" << index << ", size=" << size;
        throw std::out_of_range(msg.str());
    }
}

template<typename T>
T& Array<T>::Get(int index) const {
    checkIndex(index, m_size);
    return m_array[index];
}

template<typename T>
void Array<T>::Set(int index, const T& element) {
    checkIndex(index, m_size);
    m_array[index] = element;
}
