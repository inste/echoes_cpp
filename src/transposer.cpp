//      transposer.cpp
//      
//      Copyright 2010 Ilya <ilya@laptop>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include "transposer.h"

Transposer::Transposer(void) {
}

Transposer::~Transposer(void) {
}

void Transposer::setParams(int srate, float fpitch) {
	samplerate = srate;
	pitch = fpitch;
	dsp.setSampleRate(srate);
	dsp.setChannels(1);
	dsp.setPitch(fpitch);
	dsp.setSetting(SETTING_USE_AA_FILTER, 1);
}

void Transposer::processData(short * src, short * out, int size) {
	float * fbuffer = new float[size];
	int i;
	
	for (i = 0; i < size; ++i)
		fbuffer[i] = src[i];
	
	dsp.putSamples(fbuffer, size);
	dsp.receiveSamples(fbuffer, size);
	
	for (i = 0; i < size; ++i)
		out[i] = fbuffer[i];
	
	delete fbuffer;
}

struct fsm * Transposer::processData(short * src, int size) {
	float * fbuffer = new float[size];
	struct fsm * out = fsm_alloc(size);
	int i;
	
	for (i = 0; i < size; ++i)
		fbuffer[i] = src[i];
	
	dsp.putSamples(fbuffer, size);
	dsp.receiveSamples(out->data, size);
	
	delete fbuffer;
	return out;
}
