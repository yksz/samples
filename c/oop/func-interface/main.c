#include <stdio.h>
#include "interface.h"

#define len(x) (sizeof(x)/sizeof(x[0]))

void assignment()
{
    printf("[assignment] begin\n");

    ICalculate calc;
    int a = 10, b = 5;
    int ans;

    calc = multiply;
    ans = (calc)(a, b);
    printf("%d * %d = %d\n", a, b, ans);

    calc = divide;
    ans = (calc)(a, b);
    printf("%d / %d = %d\n", a, b, ans);

    printf("[assignment] end\n\n");
}

void array()
{
    printf("[array] begin\n");

    ICalculate calc[] = { multiply, divide };
    char op[] = { '*', '/' };
    int a = 10, b = 5;
    int ans;

    for (int i = 0; i < len(calc); i++) {
        ans = (calc[i])(a, b);
        printf("%d %c %d = %d\n", a, op[i], b, ans);
    }

    printf("[array] end\n\n");
}

int main()
{
    assignment();
    array();
    return 0;
}
