/*
 * libao_out.cpp
 *
 *  Created on: 06.10.2010
 *      Author: ilya
 */

#include "libao_out.h"

libAo_Out::libAo_Out(void) {
	device = NULL;
	default_driver = 0;
}

int libAo_Out::Init(int samplerate, int bits, int channels) {
	if (device != NULL) {
		std::string err = "Device already initialized!\n";
		throw std::runtime_error(err);
	}

	ao_initialize();
	default_driver = ao_default_driver_id();
	format.bits = bits;
	format.channels = channels;
	format.rate = samplerate;
	format.byte_format = AO_FMT_LITTLE;
	format.matrix = "L,R";
	device = ao_open_live(default_driver, &format, NULL);

	if (device != 0)
		return 0;
	else
		return -1;
}

void libAo_Out::PlayBuffer(char * buffer, int size) {
	if (device == NULL) {
		std::string err = "Output device doesn't initialized!\n";
		throw std::runtime_error(err);
	}
	ao_play(device, buffer, size);
}

void libAo_Out::PlayBuffer(short * buffer, int size) {
	if (device == NULL) {
		std::string err = "Output device doesn't initialized!\n";
		throw std::runtime_error(err);
	}
	ao_play(device, (char *)buffer, size * 2);
}

libAo_Out::~libAo_Out(void) {
	if (device != NULL)
		ao_close(device);
	ao_shutdown();
}


