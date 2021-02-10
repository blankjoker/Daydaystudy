#ifndef DIAGDLOG_H
#define DIAGDLOG_H

#include "ncore/NCTimeDefine.h"

namespace nutshell
{
    #ifdef LOG_TAG
    #undef LOG_TAG
    #endif
    #define LOG_TAG "diagd"
    #define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)

    #define DIAGD_DG(format, ...) \
    { \
        printf("[TID:%d] [TC:%" PRId64 "] [diagd]\t%s\t%d\t" format"\n", gettid(), GetTickCount(), __FILENAME__, __LINE__, ##__VA_ARGS__); \
    }

    #define DIAGD_ERROR(format, ...) \
    { \
        printf("\033[;31m[TID:%d] [TC:%" PRId64 "] [diagd]\t%s\t%d\t" format"\033[m\n", gettid(), GetTickCount(), __FILENAME__, __LINE__, ##__VA_ARGS__); \
    }
}  // namespace nutshell

#endif // DIAGDLOG_H
