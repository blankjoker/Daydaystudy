

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    /********************************************************************/
    // char str[] = "123456789";
    // char *str1 = (char *)malloc(sizeof(str));
    // strcpy(str1, str);
    // printf("str = %s\n", str);
    // printf("str1 = %s\n", str1);
    /********************************************************************/
    // char s[] = "1234567890";
    // char* p1 = s;
    // char* p2 = s+2;
    // memcpy(p2, p1, 5);
    // printf("s = %s\n", s);
    // printf("p2 = %s\n", p2);
    // memcpy(p2, p1, 5);
    // printf("s = %s\n", s);
    // printf("p2 = %s\n", p2);
    /********************************************************************/
    // char *p = NULL;
    // p = (char *)malloc(10);
    // memcpy(p, "abcd", strlen("abcd"));
    // printf("before p = %s\n", p);
    // strcpy(p + 1, p);//这重叠了
    // // strcpy(p, p + 1);//这重叠了
    // printf("after p = %s\n", p);
    // free(p);
    /********************************************************************/
    char s[] = "1234567890";
    char* p1 = s;
    char* p2 = s + 2;
    // memcpy(p2, p1, 8);
    memmove(p1, p2, 5);
    printf("p1 = %s\n", p1);
    printf("p2 = %s\n", p2);
    /********************************************************************/
    return 0;
}
