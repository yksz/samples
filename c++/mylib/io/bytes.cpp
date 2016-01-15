#include "bytes.h"
#include <cstring>
#include <stdexcept>

static bool isLittleEndian() {
#if defined(__LITTLE_ENDIAN__)
    return true;
#elif defined(__BIG_ENDIAN__)
    return false;
#else
    uint16_t b = 1;
    return *(uint8_t*)&b == 1;
#endif
}

ByteOrder NativeOrder() {
    return isLittleEndian() ? ByteOrder_LITTLE_ENDIAN : ByteOrder_BIG_ENDIAN;
}

ByteBuffer::ByteBuffer(char* buf, size_t len, ByteOrder order)
        : m_buf(buf), m_len(len), m_offset(0) {
    m_shouldConvertEndian = NativeOrder() != order;
}

static uint16_t byteSwap16(uint16_t x) {
    return ((x & 0x00ffU) << 8) |
           ((x & 0xff00U) >> 8);
}

static uint32_t byteSwap32(uint32_t x) {
    return ((x & 0x000000ffUL) << 24) |
           ((x & 0x0000ff00UL) <<  8) |
           ((x & 0x00ff0000UL) >>  8) |
           ((x & 0xff000000UL) >> 24);
}

static uint64_t byteSwap64(uint64_t x) {
    return ((x & 0x00000000000000ffULL) << 56) |
           ((x & 0x000000000000ff00ULL) << 40) |
           ((x & 0x0000000000ff0000ULL) << 24) |
           ((x & 0x00000000ff000000ULL) <<  8) |
           ((x & 0x000000ff00000000ULL) >>  8) |
           ((x & 0x0000ff0000000000ULL) >> 24) |
           ((x & 0x00ff000000000000ULL) >> 40) |
           ((x & 0xff00000000000000ULL) >> 56);
}

void ByteBuffer::check(size_t size) {
    if (m_offset + size > m_len) {
        throw std::out_of_range("ByteBuffer");
    }
}

void ByteBuffer::Get(char* dst, size_t len) {
    check(len);
    memcpy(dst, &m_buf[m_offset], len);
    m_offset += len;
}

uint8_t ByteBuffer::GetUint8() {
    size_t size = sizeof(uint8_t);
    check(size);
    uint8_t* p = reinterpret_cast<uint8_t*>(&m_buf[m_offset]);
    m_offset += size;
    return *p;
}

uint16_t ByteBuffer::GetUint16() {
    size_t size = sizeof(uint16_t);
    check(size);
    uint16_t* p = reinterpret_cast<uint16_t*>(&m_buf[m_offset]);
    if (m_shouldConvertEndian) {
        *p = byteSwap16(*p);
    }
    m_offset += size;
    return *p;
}

uint32_t ByteBuffer::GetUint32() {
    size_t size = sizeof(uint32_t);
    check(size);
    uint32_t* p = reinterpret_cast<uint32_t*>(&m_buf[m_offset]);
    if (m_shouldConvertEndian) {
        *p = byteSwap32(*p);
    }
    m_offset += size;
    return *p;
}

uint64_t ByteBuffer::GetUint64() {
    size_t size = sizeof(uint64_t);
    check(size);
    uint64_t* p = reinterpret_cast<uint64_t*>(&m_buf[m_offset]);
    if (m_shouldConvertEndian) {
        *p = byteSwap64(*p);
    }
    m_offset += size;
    return *p;
}

float ByteBuffer::GetFloat() {
    size_t size = sizeof(uint32_t);
    check(size);
    uint32_t* p = reinterpret_cast<uint32_t*>(&m_buf[m_offset]);
    if (m_shouldConvertEndian) {
        *p = byteSwap32(*p);
    }
    m_offset += size;
    return *(reinterpret_cast<float*>(p));
}

double ByteBuffer::GetDouble() {
    size_t size = sizeof(uint64_t);
    check(size);
    uint64_t* p = reinterpret_cast<uint64_t*>(&m_buf[m_offset]);
    if (m_shouldConvertEndian) {
        *p = byteSwap64(*p);
    }
    m_offset += size;
    return *(reinterpret_cast<double*>(p));
}

void ByteBuffer::Put(const char* dst, size_t len) {
    check(len);
    memcpy(&m_buf[m_offset], dst, len);
    m_offset += len;
}

void ByteBuffer::PutUint8(uint8_t value) {
    size_t size = sizeof(uint8_t);
    check(size);
    char* p = reinterpret_cast<char*>(&value);
    memcpy(&m_buf[m_offset], p, size);
    m_offset += size;
}

void ByteBuffer::PutUint16(uint16_t value) {
    size_t size = sizeof(uint16_t);
    check(size);
    if (m_shouldConvertEndian) {
        value = byteSwap16(value);
    }
    char* p = reinterpret_cast<char*>(&value);
    memcpy(&m_buf[m_offset], p, size);
    m_offset += size;
}

void ByteBuffer::PutUint32(uint32_t value) {
    size_t size = sizeof(uint32_t);
    check(size);
    if (m_shouldConvertEndian) {
        value = byteSwap32(value);
    }
    char* p = reinterpret_cast<char*>(&value);
    memcpy(&m_buf[m_offset], p, size);
    m_offset += size;
}

void ByteBuffer::PutUint64(uint64_t value) {
    size_t size = sizeof(uint64_t);
    check(size);
    if (m_shouldConvertEndian) {
        value = byteSwap64(value);
    }
    char* p = reinterpret_cast<char*>(&value);
    memcpy(&m_buf[m_offset], p, size);
    m_offset += size;
}

void ByteBuffer::PutFloat(float value) {
    uint32_t* p = reinterpret_cast<uint32_t*>(&value);
    PutUint32(*p);
}

void ByteBuffer::PutDouble(double value) {
    uint64_t* p = reinterpret_cast<uint64_t*>(&value);
    PutUint64(*p);
}
