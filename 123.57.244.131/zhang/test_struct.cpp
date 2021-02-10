
#include <stdio.h>

class test_struct
{
private:
    /* data */

    int a;
    int b;
    struct test {
        int a;
        int b;
    };
public:
    test_struct(/* args */);
    virtual ~test_struct();
};


int main(int argc, char const *argv[])
{
    /* code */
    // test_struct *my = new test_struct();
    // printf("class test_struct size is = %d\n", (int)sizeof(*my));
    printf("%d\n", (int)sizeof(test_struct));
    return 0;
}




