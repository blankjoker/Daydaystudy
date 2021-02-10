


#include <stdio.h>

struct A {
    /* data */
    int a;
    char b;
};

struct B {
    /* data */
    char a;
    short b;
    int c;
};



int main(int argc, char const *argv[])
{
    /* code */
    printf("struct A = %d\n", sizeof(struct A));
    printf("struct B = %d\n", sizeof(struct B));
    return 0;
}
