


#include <stdio.h>

int main(int argc, char const *argv[])
{
    /* code */
    char (*p)[10];
    char *q[10];
    char str1[] = "asdasdasd";
    char str2[] = "wdbhf";
    char str3[] = "123dfhf";
    q[0] = str1;
    q[1] = str2;
    q[2] = str3;
    printf("str1 = %s\n", q[0]);
    printf("str2 = %s\n", q[1]);
    printf("str3 = %s\n", q[2]);

    char *cr = "张";
    printf("张 sizeof is %d\n", sizeof(*cr));

    return 0;
}
