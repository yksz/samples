#include <cstdio>
#include <memory>

namespace {

void printArray(int* array, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d\n", array[i]);
    }
}

}

int main(void) {
    int len = 10;
    std::unique_ptr<int[]> array(new int[len]);
    for (int i = 0; i < len; i++) {
        array[i] = i;
    }
    printArray(array.get(), len);
    return 0;
}
