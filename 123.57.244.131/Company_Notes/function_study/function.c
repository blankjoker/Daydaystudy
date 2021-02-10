

	
C语言精髓

1.打印时间，包装自己的printf{
	#define DBG_PRINT (printf("%s:%u %s:%s:\t", __FILE__, __LINE__, __DATE__, __TIME__), printf) 
}

2.打印时间，包装自己的printf 2{
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void printf_time()
{
	char buff[100] = {0};
	int size = 100;
	tzset();
    struct timespec tv = {0, 0};
    clock_gettime(CLOCK_REALTIME, &tv);
    time_t timep = tv.tv_sec;
    struct tm  ti_ptr;
    localtime_r(&timep, &ti_ptr);
    snprintf(buff, size, "[%04d/%02d/%02d %02d:%02d:%02d.%06ld]",
    ti_ptr.tm_year+1900,
    ti_ptr.tm_mon+1,
    ti_ptr.tm_mday,
    ti_ptr.tm_hour,
    ti_ptr.tm_min,
    ti_ptr.tm_sec,
    tv.tv_nsec / 1000);
    printf("%s", buff);
}

#define DOIP_PRINT (printf_time(), printf("[%s] line[%u]", __FILE__, __LINE__), printf)


int main()
{
	DOIP_PRINT("ssssssssssssssssss%d\n", 88);
	return 0;
}
}




my_debug(format,...)  my_syslog(LOG_DEBUG, PROGRAM  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)

void my_syslog(unsigned int lev,const char *msg,...);



(void)ne_doip_log_output(__FUNCTION__, __FILE__, __LINE__, "<doip pack step> get tcp_table is failed! by fd[%d].\n", link_data->fd)

#define x86 1
 
#define PROGRAM "[process name] "
 
void my_syslog(unsigned int lev,const char *msg,...);
 
#define mypfdbg
#ifdef mypfdbg
#define my_debug(format,...)  my_syslog(LOG_DEBUG, "[process name] "  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#else
#define my_debug(format,...)
#endif
 
#define my_info(format,...)  my_syslog(LOG_INFO, PROGRAM  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)








#define LOG_TYPE1(format, ...)  printf(format, __VA_ARGS__)


#define LOG_TYPE2(format, args...) printf(format, args)      


#define LOG_TYPE3(format, ...) printf(format, ##__VA_ARGS__)


#define LOG_TYPE4(format, args...) printf(format, ##args)     












