//========================================================================
// FILE:
//		unit_tests/envelope_generation/testbench.cc
//
// AUTHOR:
//		zimzum@github 
//
// DESCRIPTION:
//		Template testbench file.	
//
// License: GNU GPL v2.0 
//========================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <common/envelope.h>
#include <common/wave_file.h>
#include <common/synth_config.h>
#include <common/oscillator.h>

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
TEST(EnvelopeGenerationTest, ArEnvelope)
{
    size_t pitch[] = {0, kNumberOfFrequencies/size_t(2)}; 
    int32_t volume = 1 << 15;
    uint32_t number_of_seconds = 5;
    const string file_name("test_pitch.wav");
    double initial_phase = 0;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    // Initialise the envelope
    ArEnvelope envelope(synthesiser, 1, 1, 1);

    for (size_t pitch_id = 0; pitch_id < 2; pitch_id++)
    {
        // 1. Generate the samples 
        Oscillator osc(synthesiser, volume , initial_phase, pitch[pitch_id]);
        vector<int16_t> samples_out = osc(number_of_seconds);

        // Apply envelope
        envelope.ApplyEnvelope(samples_out);

        // 2. Save the generated samples to the file 
        WaveFileOut wf_out(number_of_seconds);
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
