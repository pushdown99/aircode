#ifndef __DATA_OVER_SOUND_H__
#define __DATA_OVER_SOUND_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <dlog.h>
#include <app_common.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <tizen.h>
#include <Ecore.h>
#include <curl/curl.h>
#include <peripheral_io.h>
#include <player.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "data-over-sound"

#if !defined(PACKAGE)
#define PACKAGE "org.example.data-over-sound"
#endif

#define _E(fmt, args...) dlog_print(DLOG_ERROR, LOG_TAG, "%s : %s(%d) > "fmt"\n", rindex(__FILE__, '/') + 1, __func__, __LINE__, ##args)
#define _D(fmt, args...) dlog_print(DLOG_DEBUG, LOG_TAG, "%s : %s(%d) > "fmt"\n", rindex(__FILE__, '/') + 1, __func__, __LINE__, ##args)
#define retv_if(expr, val) do { if (expr) { _E("(%s) -> %s() return", #expr, __FUNCTION__); return (val); } } while (0)

#define FAILURE  		0
#define SUCCESS  		1

#define FOREVER			1

typedef struct appdata {
	int 		verbose;						// verbose
	player_h    player;
	Ecore_Timer *timer;
} appdata_t;

#ifdef __cplusplus
}
#endif

#endif /* __DATA_OVER_SOUND_H__ */
