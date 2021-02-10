#ifndef DIAGDLOG_H
#define DIAGDLOG_H

#include "cutils/log.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "diagd"

#define DIAGDLOGE(...) ALOGE(__VA_ARGS__)
#define DIAGDLOGW(...) ALOGE(__VA_ARGS__)
#define DIAGDLOGD(...) ALOGE(__VA_ARGS__)
#define DIAGDLOGI(...) ALOGE(__VA_ARGS__)
#define DIAGDLOGT(...) ALOGE(__VA_ARGS__)

#define ULOGASSERT(cond, ...) ALOG_ASSERT(cond, ## __VA_ARGS__)




#endif // DIAGDLOG_H
