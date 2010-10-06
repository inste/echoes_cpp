/*
 * libao_out.h
 *
 *  Created on: 06.10.2010
 *      Author: ilya
 */

#ifndef LIBAO_OUT_H_
#define LIBAO_OUT_H_

#include <string>
#include <stdexcept>

extern "C" {
#include "ao/ao.h"
}

class libAo_Out {

private:
	ao_device *device;
	ao_sample_format format;
	int default_driver;

public:
	libAo_Out(void);
	int Init(int samplerate, int bits, int channels);
	void PlayBuffer(char * buffer, int size);
	void PlayBuffer(short * buffer, int size);
	~libAo_Out(void);

};

#endif /* LIBAO_OUT_H_ */
