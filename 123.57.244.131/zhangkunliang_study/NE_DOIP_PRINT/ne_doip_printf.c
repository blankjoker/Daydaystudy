


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void printf_time()
{
	char buff[100] = {0};
	// memset(buff, 0, 100);
	int size = 100;
	tzset();
    struct timespec tv = {0, 0};
    clock_gettime(CLOCK_REALTIME, &tv);
    time_t timep = tv.tv_sec;
    struct tm  ti_ptr;
    localtime_r(&timep, &ti_ptr);
    snprintf(buff, size, "[%04d/%02d/%02d %02d:%02d:%02d.%03ld]",
    ti_ptr.tm_year+1900,
    ti_ptr.tm_mon+1,
    ti_ptr.tm_mday,
    ti_ptr.tm_hour,
    ti_ptr.tm_min,
    ti_ptr.tm_sec,
    tv.tv_nsec / 1000);
    printf("%s", buff);
    // free(buff);
}

#define DOIP_PRINT (printf_time(), printf("[%s] line[%u]", __FILE__, __LINE__), printf)


int main()
{
	DOIP_PRINT("ssssssssssssssssss%d\n", 88);
	return 0;
}