#ifndef INT_ARRAY_H
#define INT_ARRAY_H

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);               \
    void operator=(const TypeName&)

class IntArray {
public:
    IntArray();
    explicit IntArray(int size);
    ~IntArray();

    int get(int index);
    void set(int index, int element);

private:
    void init(int size);

    int* m_array;
    int m_size;
    DISALLOW_COPY_AND_ASSIGN(IntArray);
};

#endif // INT_ARRAY_H
