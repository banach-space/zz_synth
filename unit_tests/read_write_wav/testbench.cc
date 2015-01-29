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
#include <cmath>
#include <iostream>
#include <string>

#include "common/zz_global.h"
#include "common/wave_file.h"
#include "common/synth_config.h"
#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

//=============================================================
// Namespaces 
//=============================================================
using namespace::std;

//=============================================================
// UTILITIES 
//=============================================================
vector<int16_t> generate_samples(
        int32_t volume, 
        size_t pitch,
        size_t number_of_seconds)
{

    double frequency, phase_increment, phase;
    size_t number_of_samples;

    // 1. Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    // 2. Physical properties of the signal 
    frequency = synthesiser.frequency_table(pitch);
    phase = 0;

    phase_increment = synthesiser.phase_increment_per_sample() * frequency;
    number_of_samples = 
        (size_t) (synthesiser.sampling_rate() * number_of_seconds);

    vector<int16_t> generated_samples(number_of_samples);
    for (size_t n = 0; n < number_of_samples; n++)
    {
        generated_samples[n] = volume * sin(phase);

        if ((phase += phase_increment) >= kTwoPi)
            phase -= kTwoPi;
    }

    return generated_samples;
}

void compare_wave_headers(WaveFileOut &wf_out, WaveFileIn &wf_in)
{
        EXPECT_EQ(wf_out.chunk_id(), wf_in.chunk_id());
        EXPECT_EQ(wf_out.chunk_size(), wf_in.chunk_size());
        EXPECT_EQ(wf_out.format(), wf_in.format());
        EXPECT_EQ(wf_out.subchunk_1_id(), wf_in.subchunk_1_id());
        EXPECT_EQ(wf_out.subchunk_1_size(), wf_in.subchunk_1_size());
        EXPECT_EQ(wf_out.audio_format(), wf_in.audio_format());
        EXPECT_EQ(wf_out.num_channels(), wf_in.num_channels());
        EXPECT_EQ(wf_out.sample_rate(), wf_in.sample_rate());
        EXPECT_EQ(wf_out.byte_rate(), wf_in.byte_rate());
        EXPECT_EQ(wf_out.block_align(), wf_in.block_align());
        EXPECT_EQ(wf_out.bits_per_sample(), wf_in.bits_per_sample());
        EXPECT_EQ(wf_out.subchunk_2_id(), wf_in.subchunk_2_id());
        EXPECT_EQ(wf_out.subchunk_2_size(), wf_in.subchunk_2_size());
        EXPECT_EQ(wf_out.subchunk_2_size(), wf_in.subchunk_2_size());

}

//=============================================================
// TESTS
//=============================================================
TEST(ReadWriteWaveFileTest, HandleDifferentPitches)
{
    size_t pitch[] = {0, kNumberOfFrequencies/size_t(2), kNumberOfFrequencies}; 
    int32_t volume = 1 << 15;
    int8_t number_of_seconds = 5;
    const string file_name("test_pitch.wav");


    for (size_t pitch_id = 0; pitch_id < 3; pitch_id++)
    {
        // 1. Generate the desired signal and save it to the output file
        WaveFileOut wf_out(number_of_seconds);

        // 2. Save to a WaveFileOut file
        vector<int16_t> samples_out = generate_samples(
                volume,
                pitch[pitch_id],
                number_of_seconds);

        wf_out.SaveBufferToFile(file_name, samples_out);

        // 3. Read the file saved in Step 2 into a WaveFileIn file
        vector<int16_t> samples_in;
        WaveFileIn wf_in;
        samples_in = wf_in.ReadBufferFromFile(file_name);

        // 4. Validate by comparing input and output
        compare_wave_headers(wf_out, wf_in);
        EXPECT_THAT(samples_in, ::testing::ContainerEq(samples_out));
    }
}

TEST(ReadWriteWaveFileTest, HandleDifferentVolumes)
{
    int pitch = 48; 
    int32_t volume[] = {0, 1 << 7, 1 << 15};
    int8_t number_of_seconds = 5;
    const string file_name("test_volume.wav");


    for (size_t volume_id = 0; volume_id < 3; volume_id++)
    {
        // 1. Generate the desired signal and save it to the output file
        WaveFileOut wf_out(number_of_seconds);

        // 2. Save to a WaveFileOut file
        vector<int16_t> samples_out = generate_samples(
                volume[volume_id],
                pitch,
                number_of_seconds);

        wf_out.SaveBufferToFile(file_name, samples_out);

        // 3. Read the file saved in Step 2 into a WaveFileIn file
        vector<int16_t> samples_in;
        WaveFileIn wf_in;
        samples_in = wf_in.ReadBufferFromFile(file_name);

        // 4. Validate by comparing input and output
        compare_wave_headers(wf_out, wf_in);
        EXPECT_THAT(samples_in, ::testing::ContainerEq(samples_out));
    }
}

TEST(ReadWriteWaveFileTest, HandleDifferentDuration)
{
    int pitch = 48; 
    int32_t volume = 1 << 15;
    size_t number_of_seconds[] = {0, 1, 5};
    const string file_name("test_duration.wav");


    for (size_t duration_idx = 0; duration_idx < 3; duration_idx++)
    {
        // 1. Generate the desired signal and save it to the output file
        WaveFileOut wf_out(number_of_seconds[duration_idx]);

        // 2. Save to a WaveFileOut file
        vector<int16_t> samples_out = generate_samples(
                volume,
                pitch,
                number_of_seconds[duration_idx]);

        wf_out.SaveBufferToFile(file_name, samples_out);

        // 3. Read the file saved in Step 2 into a WaveFileIn file
        vector<int16_t> samples_in;
        WaveFileIn wf_in;
        samples_in = wf_in.ReadBufferFromFile(file_name);

        // 4. Validate by comparing input and output
        compare_wave_headers(wf_out, wf_in);
        EXPECT_THAT(samples_in, ::testing::ContainerEq(samples_out));
    }
}

//=============================================================
// MAIN 
//=============================================================
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
