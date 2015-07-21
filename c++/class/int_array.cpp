#include "int_array.h"
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

IntArray::IntArray() {
    init(10);
}

IntArray::IntArray(int size) {
    init(size);
}

void IntArray::init(int size) {
    m_array = new int[size];
    m_size = size;
}

IntArray::~IntArray() {
    delete[] m_array;
}

int IntArray::get(int index) {
    checkIndex(index, m_size);
    return m_array[index];
}

void IntArray::set(int index, int element) {
    checkIndex(index, m_size);
    m_array[index] = element;
}
