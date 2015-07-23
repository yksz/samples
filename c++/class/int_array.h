#ifndef INT_ARRAY_H
#define INT_ARRAY_H

class IntArray {
public:
    IntArray();
    explicit IntArray(int size);
    ~IntArray();

    int get(int index) const;
    void set(int index, int element);

private:
    IntArray(const IntArray&);
    void operator=(const IntArray&);

    void init(int size);

    int* m_array;
    int m_size;
};

#endif // INT_ARRAY_H
