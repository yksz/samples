#include <cstdio>
#include <memory>

static void printArray(int* array, int len) {
    printf("[%d", array[0]);
    for (int i = 1; i < len; i++) {
        printf(", %d", array[i]);
    }
    printf("]\n");
}

static void printArray(std::unique_ptr<int[]> array, int len) {
    printf("[%d", array[0]);
    for (int i = 1; i < len; i++) {
        printf(", %d", array[i]);
    }
    printf("]\n");
}

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
