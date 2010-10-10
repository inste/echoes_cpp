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
#include "transposer.h"
#include "samples.h"
#include "mixer.h"


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
	return 27.5 * pow(2, (octave * 12 + note - 9) / 12.0L);
}


int main() {

	std::vector<double> chord;

	WavInFile wfd("test.wav");
	libAo_Out out;
	FFTW_Direct fftw;
	Transposer proc;
	Mixer mixer;

	double freq;
	unsigned int i, pos;
	int time = 100; // Size of sample, msec
	int samplesize = wfd.getSampleRate() * wfd.getNumChannels() * time / 1000;
	short * buffer, * monobuffer;
	struct fsm * fs;
	Harmonic * harmonics;

	buffer = new short[samplesize];
	monobuffer = new short[samplesize / wfd.getNumChannels()];
	fs = fsm_alloc(samplesize / wfd.getNumChannels());
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

		chord.push_back(compute_freq(0,4));
//		chord.push_back(compute_freq(0,4));
//		chord.push_back(compute_freq(0,4));


		freq = pos * 1000.0L / time;


		cout << compute_freq(9, 4) << endl;
		cout << compute_freq(9, 4) / freq <<endl;

		if (freq < 20)
			freq = 20;

		proc.setParams(wfd.getSampleRate(), compute_freq(7, 3) / freq);
		mixer.putSample(proc.processData(monobuffer, samplesize / wfd.getNumChannels()));
	
	//	proc.setParams(wfd.getSampleRate(), compute_freq(0, 3) / freq);
	//	mixer.putSample(proc.processData(monobuffer, samplesize / wfd.getNumChannels()));	
		
		proc.setParams(wfd.getSampleRate(), compute_freq(4, 3) / freq);
		mixer.putSample(proc.processData(monobuffer, samplesize / wfd.getNumChannels()));
		
		fs = mixer.getMixed();
		
		mixer.Clean();

		for (i = 0; i < samplesize / 2; ++i)
			buffer[2 * i] = buffer[2 * i + 1] = fs->data[i];
//
		out.PlayBuffer(buffer, samplesize);

		cout << "Frequency: " << freq << "Hz" << endl;
	}

	cout << "Test" << endl;
	return 0;
}
