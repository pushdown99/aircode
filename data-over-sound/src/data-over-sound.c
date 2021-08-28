#include <dr_wav.h>
#include <tizen.h>
#include <service_app.h>
#include "data-over-sound.h"
#include "ggwave.h"
#include "misc.h"
#include "thread.h"
#include <curl/curl.h>

bool service_app_create(void *data)
{
	appdata_t *ad = (appdata_t*)data;

	curl_global_init (CURL_GLOBAL_ALL);
	initThread (data);
    return true;
}

void service_app_terminate(void *data)
{
    // Todo: add your code here.
	curl_global_cleanup ();
    return;
}

void service_app_control(app_control_h app_control, void *data)
{
    // Todo: add your code here.
    return;
}


int main(int argc, char* argv[])
{
	_D("\n\n\n\n");
	_D("==============================================");
	_D("DATA-OVER-SOUND, WNB-TEAM                     ");
	_D("- started : %s", getTime ()                    );
	_D("- timstamp: %d", getUnixtime ()                );
	_D("==============================================");

	appdata_t ad;
	service_app_lifecycle_callback_s event_callback;

	event_callback.create 		= service_app_create;
	event_callback.terminate 	= service_app_terminate;
	event_callback.app_control 	= service_app_control;

	return service_app_main(argc, argv, &event_callback, &ad);
}
