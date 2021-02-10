



#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[])
{
    char *str = "你";
    printf("str size = %d\n", sizeof(*str));
    printf("str strlen = %d\n", strlen(str));
    return 0;
}
