

#include <stdio.h>

int binary(int x)
{
    if (x == 0) {
        return 0;
    }
    else {
        binary(x/2);
        printf("%d", x%2);
        return 0;
    }
}


// int num64(int x, int count)
// {
//     if (count == 0) {
//         return 0;
//     }
//     else {
//         return
//     }
    
// }

int main(int argc, char const *argv[])
{
    // binary(4);
    // printf("\n");
    // return 0;
    int num = 29;
    int x = 2;
    while(num--)
    {
        x = x * 2;
    }
    printf("x = %d\n", x);
}
