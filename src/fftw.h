/*
 * fftw.h
 *
 *  Created on: 06.10.2010
 *      Author: ilya
 */

#ifndef FFTW_H_
#define FFTW_H_

#include <string>
#include <stdexcept>
#include <cmath>

extern "C" {

#include <fftw3.h>

}

typedef double Harmonic[2];

class FFTW_Direct {
protected:
	fftw_complex *in, *out;
	fftw_plan p;
	int _samplesize;
public:
	FFTW_Direct(void);
	void Init(int samplesize);

	void putData(short * data, int count);
	void putData(short * data);
	void getData(Harmonic * data, int count);
	void getData(Harmonic * data);

	void Run(void);

	~FFTW_Direct(void);

};


#endif /* FFTW_H_ */
