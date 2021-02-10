

#include <stdio.h>
#include <algorithm>

#define INT_MAX 2147483647
#define INT_MIN -2147483648

int reverse(int x)
{

    int num1 = 0;
    while (x != 0) {
        int pop = x % 10;
        x /= 10;
        if (num1 > INT_MAX/10 || (num1 == INT_MAX / 10 && pop > 7)) 
            return 0;
        if (num1 < INT_MIN/10 || (num1 == INT_MIN / 10 && pop < -8)) 
            return 0;
        num1 = num1 * 10 + pop;
    }
    return num1;
}

int main(int argc, char const *argv[])
{
    bool num1 = false;
    int num2 = 2;
    printf("num1 + num2 = %d\n", num1 + num2);
    int x = reverse(123456789);
    printf("===============%d\n", x);
    return 0;
}
