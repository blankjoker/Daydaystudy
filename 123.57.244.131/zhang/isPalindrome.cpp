

#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647
#define INT_MIN -2147483648


class Solution {
public:
    bool isPalindrome(int x) {
        int num = 0;
        int temp = 0;
        int temp_x = x;
        while (x) {
            temp = x % 10;
            x = x / 10;
            if (num1 > INT_MAX / 10 || (num1 == INT_MAX / 10 && pop > 7)) {
                return 0;
            }
            if (num1 < INT_MIN / 10 || (num1 == INT_MIN / 10 && pop < -8)) {
                return 0;
            }
            num = num * 10 + temp;
        }
        if (temp_x == num && num => 0) {
            return true;
        }
        else {
            return false;
        }
    }
};


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
