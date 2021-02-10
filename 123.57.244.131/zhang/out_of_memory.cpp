
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    
    int *out_of_memory = (int*)malloc(1024*1024);
    printf("sizeof(out_of_memory) = %d\n", (unsigned int)sizeof(*out_of_memory));
    return 0;
}
