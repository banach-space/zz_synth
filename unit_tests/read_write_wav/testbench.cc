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


#include "common/zz_global.h"
#include "common/zz_WaveFile.h"
#include "common/zz_SynthConfig.h"

int main(int argc, char *argv[])
{
	int pitch = 48;  // Middle C
	int32_t duration = 1;
	int32_t volume = 1;
    uint32_t totalSamples;
    double frequency, phase_increment, phase;
    int8_t number_of_seconds = 5;

	if (argc > 1)
		duration = atof(argv[1]);
	if (argc > 2)
		pitch = atoi(argv[2]);
	if (argc > 3)
		volume = atof(argv[3]);

	zz_SynthConfig &synthesiser  = zz_SynthConfig::getInstance();
	frequency = synthesiser.frequency_table(pitch);

    phase_increment = synthesiser.phase_increment_per_sample() * frequency;
	phase = 0;

	totalSamples = (std::size_t) ((synthesiser.sample_rate() * duration) + 0.5);

    WaveFile wf(number_of_seconds);
    for (std::size_t n = 0; n < totalSamples; n++)
    {
        wf.sample_buffer_[n] = volume * sin(phase);
        if ((phase += phase_increment) >= kTwoPi)
            phase -= kTwoPi;
    }

    wf.SaveBufferToFile(std::string("example01.wav"));

	return 0;
}
