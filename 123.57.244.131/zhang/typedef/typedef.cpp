

#include <stdio.h>
#include <stdlib.h>

struct test {
    struct test *p;
    struct test *n;
};

typedef struct test test_t;

typedef struct my_A {
    test_t base;
    int a;
    int b;
}my_AA;

test_t* test_init(test_t *list)
{
    list->p = list;
    list->n = list;
    printf("my_AA = %p\n", (my_AA *)list);
    printf("my_AA->a = %d\n", ((my_AA *)list)->a);
    printf("my_AA->b = %d\n", ((my_AA *)list)->b);
}

int main(int argc, char const *argv[])
{
    my_AA *num = (my_AA *)malloc(sizeof(struct my_A));
    num->a = 12;
    num->b = 13;
    test_init((test_t *)num);
    printf("num   = %p\n", num); 
    // printf("node = %p\n", my_test); 

    return 0;
}
