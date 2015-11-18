#include "myproject/newmath/newmath.h"
#include "myproject/newmath/internal/calc.h"

namespace myproject {
namespace newmath {

int Sum(int* array, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum = Add(sum, array[i]);
    }
    return sum;
}

double Average(int* array, int len) {
    int val = Sum(array, len);
    return Div(val, len);
}

} // namespace newmath
} // namespace myproject
