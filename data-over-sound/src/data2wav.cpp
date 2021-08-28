#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h>

#include "dlog.h"
#include "data2wav.h"
#include "ggwave.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void createWaveFile (char *message) {
	/*
	char buf[BUFSIZ];
	sprintf(buf,"/usr/bin/curl -sS 'https://ggwave-to-file.ggerganov.com/?m=%s!&p=4' --output hello.wav", message);
	system(buf);
	*/
    char url[BUFSIZ] = "http://ggwave-to-file.ggerganov.com/?m=Hello world!&p=4";
    char outfilename[FILENAME_MAX] = "/tmp/hello.wav";

    CURL *curl;
    FILE *fp;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(outfilename,"wb");
        if (fp == NULL) {
        	dlog_print(DLOG_DEBUG, LOG_TAG, "fopen error \n");
        }
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);
    }

    /*
	ggwave_Parameters parameters = ggwave_getDefaultParameters();
    parameters.sampleFormatInp = GGWAVE_SAMPLE_FORMAT_I16;
    parameters.sampleFormatOut = GGWAVE_SAMPLE_FORMAT_I16;

    ggwave_Instance g_ggwave = ggwave_init(parameters);

    int n = ggwave_encode(g_ggwave, message, strlen(message), GGWAVE_TX_PROTOCOL_ULTRASOUND_NORMAL, 10, NULL, 1);
    char waveform[BUFSIZ];
    int nbyte = ggwave_encode(g_ggwave, message, strlen(message), GGWAVE_TX_PROTOCOL_ULTRASOUND_NORMAL, 10, waveform, 0);

    drwav_data_format format;
    format.container = drwav_container_riff;
    format.format = DR_WAVE_FORMAT_PCM;
    format.channels = 1;
    format.sampleRate = 48000.0f;
    format.bitsPerSample = 16;


    drwav wav;
    drwav_init_file_write(&wav, "/dev/stdout", &format, NULL);
    drwav_uint64 framesWritten = drwav_write_pcm_frames(&wav, nbyte/2, waveform);
    drwav_uninit(&wav);
	*/
}
