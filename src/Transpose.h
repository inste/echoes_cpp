/*
 * Transpose.h
 *
 *  Created on: 06.10.2010
 *      Author: ilya
 */

#ifndef TRANSPOSE_H_
#define TRANSPOSE_H_


#include <vector>
#include <cstring>
#include <soundtouch/SoundTouch.h>
#include <soundtouch/STTypes.h>

using namespace soundtouch;



class Transpose {
private:
	soundtouch::SoundTouch * dsp;
	int _samplesize;
	int _samplerate;
	int _channels;
public:
	Transpose(void);
	void Init(int samplerate, int channels, int samplesize);
	void Process(short * srcdata, short * outdata, double rfreq, std::vector<double> chord);
	~Transpose(void);
};

#endif /* TRANSPOSE_H_ */
