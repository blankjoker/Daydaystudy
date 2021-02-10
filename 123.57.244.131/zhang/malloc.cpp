
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char *str = (char *)malloc(10);
    strcpy(str, "zhang");
    printf("str = %s\n", str);
    free(str);
    free(str);

    return 0;
}
