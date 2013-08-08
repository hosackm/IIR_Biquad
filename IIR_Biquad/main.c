//
//  main.c
//  IIR_Biquad
//
//  Created by Matthew Hosack on 8/8/13.
//  Copyright (c) 2013 Matthew Hosack. All rights reserved.
//

//
//  main.c
//  AudioDelay
//
//  Created by Matthew Hosack on 8/4/13.
//  Copyright (c) 2013 Matthew Hosack. All rights reserved.
//


#include "IIRFilter.h"
#include "portaudio.h"
#include <stdio.h>
#include <stdlib.h>

#define SAMPLE_RATE (44100)
#define NUM_SECONDS (20)
#define NUM_COEFFS 5

BIQUADREF bq;
static PaStream *stream;
static PaError err;

static int callback(const void* input,
					void* output,
					unsigned long framesPerBuffer,
					const PaStreamCallbackTimeInfo* time_info,
					PaStreamCallbackFlags flags,
					void* userData)
{
	float* in = (float*)input;
	float* out = (float*)output;
    bq_tick(bq, in, out, framesPerBuffer);
	return 0;
}

void print_error(PaError err){
	printf("Error: %s\n",Pa_GetErrorText(err));
}

void pa_init(){
    printf("Opening Portaudio stream\n");
	//
	// Initialize PortAudio
	////////////////////////
	err = Pa_Initialize();
	if (err != paNoError){
		print_error(err);
	}
    
	//
	// Open a stream
	////////////////
	err = Pa_OpenDefaultStream(	&stream,
                               1,
                               1,
                               paFloat32,
                               SAMPLE_RATE,
                               64,//256,
                               callback,
                               NULL);
	if (err != paNoError){
		print_error(err);
	}
    
	//
	// Start the stream
	///////////////////
	err = Pa_StartStream(stream);
	if (err != paNoError){
		print_error(err);
	}
    
	const PaStreamInfo* info = Pa_GetStreamInfo(stream);
	printf("\nStream Information:\n");
	printf("StructVersion: %d\n",info->structVersion);
	printf("inputLatency: %f\n",info->inputLatency);
	printf("outputLatency: %f\n",info->outputLatency);
	printf("Sample Rate: %f\n\n",info->sampleRate);
}

void pa_close(){
    printf("Closing Portaudio\n");
    err = Pa_CloseStream(stream);
	if (err != paNoError){
		print_error(err);
	}
    
	//
	// Terminate Port Audio. We're done!
	////////////////////////////////////
	err = Pa_Terminate();
	if (err != paNoError){
		print_error(err);
	}
}

int main(int argc, const char * argv[])
{
    float coeffs[NUM_COEFFS] = {0.00460399444634034,
                                0.00920798889268068,
                                0.00460399444634034,
                                -1.7990948352036205,
                                0.8175108129889816};
    bq = bq_new(coeffs);
    pa_init();
    getchar();
    pa_close();
    free(bq);
    return 0;
}