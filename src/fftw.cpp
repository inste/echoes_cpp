/*
 * fftw.cpp
 *
 *  Created on: 06.10.2010
 *      Author: ilya
 */

#include "fftw.h"

FFTW_Direct::FFTW_Direct(void) {
	in = out = NULL;
}

void FFTW_Direct::Init(int samplesize) {

	if ((in != NULL) || (out != NULL)) {
		std::string err = "Double initialization of FFTW_Direct\n";
		throw std::runtime_error(err);
	}

	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * samplesize);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * samplesize);
	p = fftw_plan_dft_1d(samplesize, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	_samplesize = samplesize;
}


void FFTW_Direct::putData(short * data, int count) {
	int i;

	for (i = 0; i < count; ++i) {
		in[i][0] = data[i];
		in[i][1] = 0;
	}
}

void FFTW_Direct::putData(short * data) {
	putData(data, _samplesize);
}

void FFTW_Direct::getData(Harmonic * data, int count) {
	int i;

	for (i = 0; i < count / 2; ++i) {
		data[i][0] = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]) / _samplesize;
		data[i][1] = atan2(out[i][1], out[i][0]);
	}
}

void FFTW_Direct::getData(Harmonic * data) {
	getData(data, _samplesize);
}

void FFTW_Direct::Run(void) {
	fftw_execute(p);
}


FFTW_Direct::~FFTW_Direct(void) {
	if ((in == NULL) || (out == NULL)) {
		std::string err = "Double freed of FFTW_Direct\n";
		throw std::runtime_error(err);
	}

	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
}


