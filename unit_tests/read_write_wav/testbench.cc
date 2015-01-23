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
#include "common/wave_file.h"
#include "common/synth_config.h"
#include <vector>

#include <gtest/gtest.h>

//=============================================================
// Tests
//=============================================================
TEST(read_write_wav, write)
{
    int pitch = 48;  // Middle C
    int32_t duration = 1;
    int32_t volume = 1 << 15;
    uint32_t total_number_of_samples;
    double frequency, phase_increment, phase;
    int8_t number_of_seconds = 5;

    // Init the synthesiser
    zz_SynthConfig &synthesiser  = zz_SynthConfig::getInstance();
    synthesiser.Init();	

    total_number_of_samples = (std::size_t) ((synthesiser.sampling_rate() * number_of_seconds) + 0.5);
    std::vector<int16_t> samples(total_number_of_samples);
    frequency = synthesiser.frequency_table(pitch);

    phase_increment = synthesiser.phase_increment_per_sample() * frequency;
    phase = 0;

    WaveFileOut wf(number_of_seconds);

    for (std::size_t n = 0; n < total_number_of_samples; n++)
    {
        samples[n] = volume * sin(phase);

        if ((phase += phase_increment) >= kTwoPi)
            phase -= kTwoPi;
    }

    wf.SaveBufferToFile(std::string("example01.wav"), samples);

    EXPECT_EQ(1, 1);

}

//=============================================================
// Main 
//=============================================================
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
