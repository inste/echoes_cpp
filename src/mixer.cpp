//      mixer.cpp
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


#include "mixer.h"


Mixer::Mixer(void) {
	s_count = 0;
	samples = NULL;
}

Mixer::~Mixer(void) {
	Clean();
}

void Mixer::putSample(struct fsm * sample) {
	samples = (struct fsm **) realloc(samples, ++s_count * sizeof(struct fsm *));
	samples[s_count - 1] = sample;
}

struct fsm * Mixer::getMixed(void) {
	struct fsm * ret = fsm_alloc(samples[0]->size);
	int i, j;
	
	for (i = 0; i < samples[0]->size; ++i) {
		ret->data[i] = 0;
		for (j = 0; j < s_count; ++j)
			ret->data[i] += samples[j]->data[i];
		ret->data[i] /= s_count;
	}
	
	return ret;
}

void Mixer::Clean(void) {
	int i;
	
	for (i = 0; i < s_count; ++i)
		fsm_free(samples[i]);
	free(samples);
	s_count = 0;
	samples = NULL;
}

struct fsm * Mixer::operator = (Mixer param) {
	return param.getMixed();
}
