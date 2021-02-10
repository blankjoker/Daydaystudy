/*===============================================================
*   Copyright (C) 2020 All rights reserved.
*   
*   文件名称：my_array.cpp
*   创 建 者：zhangkunliang
*   创建日期：2020年10月26日
*   描    述：
*
*   更新日志：
*
================================================================*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int len_array = 0;
    int array_num = 0;
    scanf("%d", &len_array);
    scanf("%d", &array_num);
    int *my_array[array_num];
    int i = 0, j = 0;

    for (i = 0; i < array_num; i++) {
        while (scanf("%d", my_array[i] + j) != EOF) {
            j++;
        }
        i++;
        j = 0;
    }
    return 0;
}

