#include "data2wav.h"

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
#include <service_app.h>

#include "lcd.h"

typedef struct appdata {
	int 		verbose;						// verbose
	player_h    player;
	Ecore_Timer *timer;
} appdata_t;

/*
typedef void(* wav_player_playback_completed_cb)(int id, void *user_data);
int wav_player_start(const char* path, sound_stream_info_h stream_info, wav_player_playback_completed_cb callback, void * 	user_data, int* id );


static void _playback_completed_cb(int id, void *user_data)
{
    const char* path = (const char*)user_data;
    dlog_print(DLOG_INFO, "WAV Player", "Completed! [id:%d, path:%s]", id, path);
}
*/



#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "data-over-sound"

#if !defined(PACKAGE)
#define PACKAGE "org.example.data-over-sound"
#endif

static void setLed(int status)
{
    int pin = 26;
    int ret;
    peripheral_gpio_h gpio = NULL;

	ret = peripheral_gpio_open(pin, &gpio);
	if (ret) {
		peripheral_gpio_close(gpio);
		//dlog_print(DLOG_DEBUG, LOG_TAG, "%s, "peripheral_gpio_open failed.");
		return;
	}

	ret = peripheral_gpio_set_direction(gpio, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW);
	if (ret) {
		peripheral_gpio_close(gpio);
		//dlog_print(DLOG_DEBUG, LOG_TAG, "%s, "peripheral_gpio_set_direction failed.");
		return;
	}
	peripheral_gpio_write(gpio, status);
	peripheral_gpio_close(gpio);
}

static void _player_completed_cb(void *data)
{

	appdata_t *ad = (appdata_t*)data;
	char pathWav[BUFSIZ];
	sprintf(pathWav, "%s%s", 	app_get_shared_resource_path(), "speak.wav");

	setLed (0);
	setLcd ("Code@air","Sound stop!");

	int error_code = 0;
    dlog_print(DLOG_INFO, LOG_TAG, "Playback End");

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_unprepare");
	error_code = player_unprepare(ad->player);
	if (error_code != PLAYER_ERROR_NONE)
	    dlog_print(DLOG_ERROR, LOG_TAG, "fail to destroy player: error code = %d", error_code);

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_destroy");
	error_code = player_destroy(ad->player);
	if (error_code != PLAYER_ERROR_NONE)
	    dlog_print(DLOG_ERROR, LOG_TAG, "fail to destroy player: error code = %d", error_code);

	////////////////////////////////////////////////////////////

    usleep(2000000);

	setLed (1);
	//                 1234567890123456
	setLcd ("Code@air","Emit Sound!!!");

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_create");
    error_code = player_create(&ad->player);
    if (error_code != PLAYER_ERROR_NONE)
        dlog_print(DLOG_ERROR, LOG_TAG, "failed to create");

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_create");
    error_code = player_set_uri(ad->player, pathWav);
    if (error_code != PLAYER_ERROR_NONE)
        dlog_print(DLOG_ERROR, LOG_TAG, "failed to set URI: error code = %d", error_code);

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_prepare");
    error_code = player_prepare(ad->player);
	if (error_code != PLAYER_ERROR_NONE)
	    dlog_print(DLOG_ERROR, LOG_TAG, "failed to prepare player: error code = %d", error_code);

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_set_completed_cb");
    error_code = player_set_completed_cb(ad->player, _player_completed_cb, ad);
    if (error_code != PLAYER_ERROR_NONE)
        dlog_print(DLOG_ERROR, LOG_TAG, "failed to set completed cb");

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_start");
	error_code = player_start(ad->player);
	if (error_code != PLAYER_ERROR_NONE)
	    dlog_print(DLOG_ERROR, LOG_TAG, "failed to start player: error code = %d", error_code);

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_set_completed_cb");
    error_code = player_set_completed_cb(ad->player, _player_completed_cb, ad);
    if (error_code != PLAYER_ERROR_NONE)
        dlog_print(DLOG_ERROR, LOG_TAG, "failed to set completed cb");

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_start");
	error_code = player_start(ad->player);
	if (error_code != PLAYER_ERROR_NONE)
	    dlog_print(DLOG_ERROR, LOG_TAG, "failed to start player: error code = %d", error_code);
}

void cbThread (void *data EINA_UNUSED, Ecore_Thread *th)
{
	dlog_print(DLOG_ERROR, LOG_TAG, "cbThread started.");
	initLcd ();

	appdata_t *ad = (appdata_t*)data;
	char pathWav[BUFSIZ];
	sprintf(pathWav, "%s%s", 	app_get_shared_resource_path(), "speak.wav");

	//createWaveFile ("Hello");

	int error_code = 0;

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_create");
    error_code = player_create(&ad->player);
    if (error_code != PLAYER_ERROR_NONE)
        dlog_print(DLOG_ERROR, LOG_TAG, "failed to create");

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_create");
    error_code = player_set_uri(ad->player, pathWav);
    if (error_code != PLAYER_ERROR_NONE)
        dlog_print(DLOG_ERROR, LOG_TAG, "failed to set URI: error code = %d", error_code);

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_prepare");
    error_code = player_prepare(ad->player);
	if (error_code != PLAYER_ERROR_NONE)
	    dlog_print(DLOG_ERROR, LOG_TAG, "failed to prepare player: error code = %d", error_code);

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_set_completed_cb");
    error_code = player_set_completed_cb(ad->player, _player_completed_cb, ad);
    if (error_code != PLAYER_ERROR_NONE)
        dlog_print(DLOG_ERROR, LOG_TAG, "failed to set completed cb");

	dlog_print(DLOG_DEBUG, LOG_TAG, "player_start");
	error_code = player_start(ad->player);
	if (error_code != PLAYER_ERROR_NONE)
	    dlog_print(DLOG_ERROR, LOG_TAG, "failed to start player: error code = %d", error_code);

	while(1) {


		if (ecore_thread_check(th)) break;
		usleep(5000000);
	}
}

/* Callback <end> function */
void
cbThreadEnd (void *data, Ecore_Thread *th)
{
}

/* Callback <cancel> function */
void
cbThreadCancel (void *data, Ecore_Thread *th)
{
}


void initThread (void *data)
{
	appdata_t *ad = (appdata_t*)data;
	dlog_print(DLOG_ERROR, LOG_TAG, "max #threads = %d", ecore_thread_max_get());

	ecore_thread_run(cbThread, cbThreadEnd, cbThreadCancel, data);
}

void termThread (void *data)
{
}
