/*
 * Transpose.cpp
 *
 *  Created on: 06.10.2010
 *      Author: ilya
 */

#include "Transpose.h"

Transpose::Transpose(void) {
	dsp = new soundtouch::SoundTouch;
}

void Transpose::Init(int samplerate, int channels, int samplesize) {
	dsp->setSampleRate(samplerate);
	dsp->setChannels(channels);
	dsp->setSetting(SETTING_USE_AA_FILTER, 1);
	_samplesize = samplesize;
	_samplerate = samplerate;
	_channels = channels;
}

void Transpose::Process(short * srcdata, short * outdata, double rfreq, std::vector<double> chord) {
	int size = (_samplerate * _channels) * _samplesize / 1000;
	short * tmpbuffer = new short [size];
	short * buffer = new short [size];
	float multiplier;
	int pos, p;

	memset(tmpbuffer, 0, size * sizeof(short));
	for (std::vector<double>::iterator it = chord.begin(); it != chord.end(); ++it) {
		multiplier = (float)(*it / rfreq); // Multiplier for changing pitch
		dsp->setPitch(multiplier);
		pos = p = 0;
		dsp->putSamples((soundtouch::SAMPLETYPE*)srcdata, size);
		do {
			pos = dsp->receiveSamples((soundtouch::SAMPLETYPE*)outdata, size);
			p += pos;
			//memcpy(tmpbuffer + p, buffer, pos);
		} while (pos != 0);
	}
	//memcpy(outdata, tmpbuffer, size);
	//delete tmpbuffer;
	//delete buffer;
}

Transpose::~Transpose(void) {
	delete dsp;
}
