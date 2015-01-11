//=============================================================
// FILE:
//   src/unit_tests/read_write_wav/testbench.c
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//   Tests reading and writing WAVE files.
//
// License: GNU GPL v2.0 
//=============================================================

//=============================================================
// Includes
//=============================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//#include "common/zz_global.h"
#include "common/zz_WavFile.h"
#include "common/zz_SynthConfig.h"

int main(int argc, char *argv[])
{
	int pitch = 48;  // Middle C
	int32_t duration = 1;
	int32_t volume = 1;

	if (argc > 1)
		duration = atof(argv[1]);
	if (argc > 2)
		pitch = atoi(argv[2]);
	if (argc > 3)
		volume = atof(argv[3]);

	zz_SynthConfig &synthesiser  = zz_SynthConfig::getInstance();
	double frequency = synthesiser.frequency_table(pitch);

	//PhsAccum phaseIncr = synthParams.frqRad * frequency;
	//PhsAccum phase = 0;

	//long totalSamples = (long) ((synthParams.sampleRate * duration) + 0.5);

	//WaveFile wf;
	//if (wf.OpenWaveFile("example01.wav", 1))
	//{
		//printf("Cannot open wavefile for output\n");
		//exit(1);
	//}

	//for (long n = 0; n < totalSamples; n++)
	//{
		//wf.Output1(volume * sinv(phase));
		//if ((phase += phaseIncr) >= twoPI)
			//phase -= twoPI;
	//}

	//wf.CloseWaveFile();

	return 0;
}
