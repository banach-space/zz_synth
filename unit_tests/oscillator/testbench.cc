//========================================================================
// FILE:
//		unit_tests/oscillator/testbench.cc
//
// AUTHOR:
//		zimzum@github 
//
// DESCRIPTION:
//      Testbench for the Oscillator class.	
//
// License: GNU GPL v2.0 
//========================================================================

#include <algorithm>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <common/synth_config.h>
#include <oscillator/oscillator.h>

using namespace std;

//========================================================================
// UTILITIES 
//========================================================================

//========================================================================
// TESTS
//========================================================================
TEST(YourTestNameTest, SubtestName)
{
    size_t pitch           = kNumberOfFrequencies/size_t(2);
    vector<int16_t> volume = {0, 1 << 7, 1 << 14};
    uint32_t duration      = 1;
    double initial_phase   = 0;
    float peak_amplitude   = 1;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    
    for (auto it = volume.begin(); it != volume.end(); it++)
    {
        auto outside_bounds = [=](int16_t sample) 
        {
            return (sample > *it) && (sample < -*it);
        };

        // 1. Generate the oscillator and the sound-wave
        SineWaveform osc(synthesiser, *it , initial_phase, pitch);
        vector<int16_t> samples = osc(duration);

        EXPECT_EQ(samples.size(), duration * synthesiser.sampling_rate());
        auto n_outside_bounds = count_if(samples.begin(), samples.end(), outside_bounds);

        EXPECT_EQ(n_outside_bounds, 0);
    }
}

//========================================================================
// MAIN 
//========================================================================
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

//========================================================================
// End of file
//========================================================================
