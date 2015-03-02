//========================================================================
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
//========================================================================

#include <global/global_variables.h>
#include <common/wave_file.h>
#include <common/synth_config.h>
#include <common/oscillator.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;

//========================================================================
// UTILITIES 
//========================================================================
void CompareWaveHeaders(WaveFileOut &wf_out, WaveFileIn &wf_in);
void CompareWaveHeaders(WaveFileOut &wf_out, WaveFileIn &wf_in)
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

//========================================================================
// TESTS
//========================================================================
TEST(ReadWriteWaveFileTest, HandleDifferentPitches)
{
    vector<size_t> pitch = {0, kNumberOfFrequencies/size_t(2), kNumberOfFrequencies - 1};
    int16_t volume       = 1 << 14;
    uint32_t duration    = 5;
    double initial_phase = 0;
    const string file_name("test_pitch.wav");

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = pitch.begin(); it != pitch.end(); it++)
    {
        // 1. Generate the samples 
        Oscillator osc(synthesiser, volume, initial_phase, *it);
        vector<int16_t> samples_out = osc(duration);

        // 2. Save the generated samples to the file 
        WaveFileOut wf_out(duration);
        wf_out.SaveBufferToFile(file_name, samples_out);

        // 3. Read the file saved in Step 2 into a WaveFileIn file
        vector<int16_t> samples_in;
        WaveFileIn wf_in;
        samples_in = wf_in.ReadBufferFromFile(file_name);

        // 4. Validate by comparing input and output
        CompareWaveHeaders(wf_out, wf_in);
        EXPECT_THAT(samples_in, ::testing::ContainerEq(samples_out));
    }
}

TEST(ReadWriteWaveFileTest, HandleDifferentVolumes)
{
    uint32_t pitch             = 48;
    vector<int16_t> volume     = {0, 1 << 7, 1 << 14};
    uint32_t duration = 5;
    double initial_phase       = 0;
    const string file_name("test_volume.wav");

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = volume.begin(); it != volume.end(); it++)
    {
        // 1. Generate the samples 
        Oscillator osc(synthesiser,*it, initial_phase, pitch);
        vector<int16_t> samples_out = osc(duration);

        // 2. Save the generated samples to the file 
        WaveFileOut wf_out(duration);
        wf_out.SaveBufferToFile(file_name, samples_out);

        // 3. Read the file saved in Step 2 into a WaveFileIn file
        vector<int16_t> samples_in;
        WaveFileIn wf_in;
        samples_in = wf_in.ReadBufferFromFile(file_name);

        // 4. Validate by comparing input and output
        CompareWaveHeaders(wf_out, wf_in);
        EXPECT_THAT(samples_in, ::testing::ContainerEq(samples_out));
    }
}

TEST(ReadWriteWaveFileTest, HandleDifferentDuration)
{
    uint32_t pitch            = 48;
    int16_t volume            = 1 << 14;
    vector<uint32_t> duration = {0, 5, 10};
    double initial_phase      = 0;
    const string file_name("test_duration.wav");

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = duration.begin(); it != duration.end(); it++)
    {
        // 1. Generate the samples 
        Oscillator osc(synthesiser, volume, initial_phase, pitch);
        vector<int16_t> samples_out = osc(*it);

        // 2. Save the generated samples to the file 
        WaveFileOut wf_out(*it);
        wf_out.SaveBufferToFile(file_name, samples_out);

        // 3. Read the file saved in Step 2 into a WaveFileIn file
        vector<int16_t> samples_in;
        WaveFileIn wf_in;
        samples_in = wf_in.ReadBufferFromFile(file_name);

        // 4. Validate by comparing input and output
        CompareWaveHeaders(wf_out, wf_in);
        EXPECT_THAT(samples_in, ::testing::ContainerEq(samples_out));
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
