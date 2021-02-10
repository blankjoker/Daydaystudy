#ifndef DOIPMANAGERLOG_H
#define DOIPMANAGERLOG_H

#include "cutils/log.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "doip"

#define TLOGE(...) ALOGE(__VA_ARGS__)
#define TLOGW(...) ALOGE(__VA_ARGS__)
#define TLOGD(...) ALOGE(__VA_ARGS__)
#define TLOGI(...) ALOGE(__VA_ARGS__)
#define TLOGT(...) ALOGE(__VA_ARGS__)

#define ULOGASSERT(cond, ...) ALOG_ASSERT(cond, ## __VA_ARGS__)


#endif // DOIPMANAGERLOG_H
