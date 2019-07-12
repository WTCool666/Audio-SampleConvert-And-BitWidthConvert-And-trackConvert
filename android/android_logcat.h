#ifndef _ANDROID_H_
#define _ANDROID_H_

#include <android/log.h>
#undef  LOG_TAG
#define LOG_TAG    "KW_LOG"
#if 1
#define  LOGDD(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#else
#define  LOGDD(...)
#endif
#define  LOGDV(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#endif