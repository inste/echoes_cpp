//============================================================================
// Name        : echoes.cpp
// Author      : Ilya Ponetayev
// Version     :
// Copyright   : Research and development version

//============================================================================

#include <iostream>
#include <cmath>
#include <vector>
#include "WavFile.h"
#include "libao_out.h"
#include "fftw.h"

using namespace std;


/* Notes
 * C - 0 C# - 1
 * D - 2 D# - 3
 * E - 4 E# - 5
 * F - 6 G - 7 G# - 8
 * A - 9 A# - 10
 * H - 11
 */

/*
 *	Octaves:
 * 	0 - subcontr
 * 	1 - contr
 * 	2 - large
 * 	3 - small
 * 	4 - first
 *  5 - second
 *  ...
 */

double compute_freq(int note, int octave) {
	return 27.5 * pow(2, (octave * 12 + note) / 12.0L);
}


int main() {

	std::vector<double> chord;

	WavInFile wfd("test.wav");
	libAo_Out out;
	FFTW_Direct fftw;

	double freq, multiplier;
	unsigned int i, pos;
	int time = 100; // Size of sample, msec
	int samplesize = wfd.getSampleRate() * wfd.getNumChannels() * time / 1000;
	short * buffer, * monobuffer;
	Harmonic * harmonics;

	buffer = new short[samplesize];
	monobuffer = new short[samplesize / wfd.getNumChannels()];
	harmonics  = new Harmonic[samplesize / (2 * wfd.getNumChannels())];

	out.Init(wfd.getSampleRate(), wfd.getNumBits(), wfd.getNumChannels());
	fftw.Init(samplesize / wfd.getNumChannels());

	while(!wfd.eof()) {
		wfd.read(buffer, samplesize);
		// Process Left Channel only now
		for (i = 0; i < samplesize / 2; ++i)
			monobuffer[i] = buffer[2 * i];
		fftw.putData(monobuffer);
		fftw.Run();
		fftw.getData(harmonics);
		freq = harmonics[0][pos = 0];
		for (i = 0; i < samplesize / (2 * wfd.getNumChannels()); ++i)
			if (harmonics[i][0] > freq) {
				freq = harmonics[i][0];
				pos = i;
			}
		freq = pos * 1000.0L / time;
		cout << "Frequency: " << freq << "Hz" << endl;
	}

	cout << "Test" << endl;
	return 0;
}
