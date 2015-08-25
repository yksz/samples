#include <cstdio>
#include <memory>

namespace {

void printArray(int* array, int len) {
    printf("[%d", array[0]);
    for (int i = 1; i < len; i++) {
        printf(", %d", array[i]);
    }
    printf("]\n");
}

void printArray(std::unique_ptr<int[]> array, int len) {
    printf("[%d", array[0]);
    for (int i = 1; i < len; i++) {
        printf(", %d", array[i]);
    }
    printf("]\n");
}

} // unnamed namespace

int main(void) {
    int len = 10;
    std::unique_ptr<int[]> array(new int[len]);
    for (int i = 0; i < len; i++) {
        array[i] = i;
    }
    printArray(array.get(), len);
    printArray(std::move(array), len);
    return 0;
}
