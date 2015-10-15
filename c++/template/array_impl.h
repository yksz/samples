#include "array.h"
#include <sstream>
#include <stdexcept>

namespace {

void checkIndex(int index, int size) {
    if (index < 0 || index >= size) {
        std::stringstream msg;
        msg << "checkIndex: index=" << index << ", size=" << size;
        throw std::out_of_range(msg.str());
    }
}

} // unnamed namespace

template<typename T>
Array<T>::Array() {
    init(10);
}

template<typename T>
Array<T>::Array(int size) {
    init(size);
}

template<typename T>
void Array<T>::init(int size) {
    m_array = new T[size];
    m_size = size;
}

template<typename T>
Array<T>::~Array() {
    delete[] m_array;
}

template<typename T>
T& Array<T>::operator[](int index) const {
    return get(index);
}

template<typename T>
int Array<T>::size() const {
    return m_size;
}

template<typename T>
T& Array<T>::get(int index) const {
    checkIndex(index, m_size);
    return m_array[index];
}

template<typename T>
void Array<T>::set(int index, const T& element) {
    checkIndex(index, m_size);
    m_array[index] = element;
}
