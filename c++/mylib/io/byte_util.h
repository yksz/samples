#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

enum ByteOrder {
    ByteOrder_BIG_ENDIAN,
    ByteOrder_LITTLE_ENDIAN
};

ByteOrder NativeOrder();

class ByteBuffer final {
public:
    ByteBuffer(char* buf, size_t len, ByteOrder order);
    ~ByteBuffer() = default;
    ByteBuffer(const ByteBuffer&) = delete;
    void operator=(const ByteBuffer&) = delete;

    void     Get(char* dst, size_t len);
    uint8_t  GetUint8();
    uint16_t GetUint16();
    uint32_t GetUint32();
    uint64_t GetUint64();
    float    GetFloat();
    double   GetDouble();

    void Put(const char* dst, size_t len);
    void PutUint8(uint8_t value);
    void PutUint16(uint16_t value);
    void PutUint32(uint32_t value);
    void PutUint64(uint64_t value);
    void PutFloat(float value);
    void PutDouble(double value);

private:
    char* m_buf;
    size_t m_len;
    int m_offset;
    bool m_shouldConvertEndian;

    void check(size_t size);
};
