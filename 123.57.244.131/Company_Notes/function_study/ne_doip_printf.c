


//发现了宏定义的新写法，和使用方法

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <stdio.h>

#define NE_DOIP_PRINT (ne_doip_printf_time(), printf)

DOIP_EXPORT void 
ne_doip_printf_time()
{
    char buff[100] = {0};
    int size = 100;
    tzset();
    struct timespec tv = {0, 0};
    clock_gettime(CLOCK_REALTIME, &tv);
    time_t timep = tv.tv_sec;
    struct tm  ti_ptr;
    localtime_r(&timep, &ti_ptr);
    snprintf(buff, size, "[%04d/%02d/%02d %02d:%02d:%02d.%05ld line:%04u]",
    ti_ptr.tm_year+1900,
    ti_ptr.tm_mon+1,
    ti_ptr.tm_mday,
    ti_ptr.tm_hour,
    ti_ptr.tm_min,
    ti_ptr.tm_sec,
    tv.tv_nsec / 10000,
	__LINE__);
    printf("%s ", buff);
	// printf("%s %04u] ", buff, __LINE__);
}