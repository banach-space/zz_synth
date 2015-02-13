//========================================================================
// FILE:
//		unit_tests/envelope_generation/testbench.cc
//
// AUTHOR:
//		zimzum@github 
//
// DESCRIPTION:
//		Testbench for the Envelope class.	
//
// License: GNU GPL v2.0 
//========================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <common/envelope.h>
#include <common/synth_config.h>
#include <common/oscillator.h>

//========================================================================
// UTILITIES 
//========================================================================
void ComparePreAndPostEnvelope(
        ArEnvelope &envelope,
        vector<int16_t>::difference_type attack_length, 
        vector<int16_t>::difference_type decay_length,
        vector<int16_t> &samples);
void ComparePreAndPostEnvelope(
        ArEnvelope &envelope,
        vector<int16_t>::difference_type attack_length, 
        vector<int16_t>::difference_type decay_length,
        vector<int16_t> &samples)
{
    // 0. Begining and end of the sustain segment
    vector<int16_t>::const_iterator sustain_segment_begin;
    vector<int16_t>::const_iterator sustain_segment_end; 

    // 1. Generate the samples and create a copy for later reference
    //Oscillator osc(synthesiser, volume , initial_phase, pitch);
    //vector<int16_t> samples      = osc(number_of_seconds);
    vector<int16_t> samples_copy = samples;

    // 2. Apply envelope
    envelope.ApplyEnvelope(samples);

    // 3. The 'sustain segment' of the original sound WITHOUT envelope
    sustain_segment_begin = samples_copy.begin() + attack_length;
    sustain_segment_end   = samples_copy.end() - decay_length;
    vector<int16_t> sustain_segment_without_envelope(sustain_segment_begin, sustain_segment_end);

    // 4. The 'sustain segment' of the original sound WITH envelope
    sustain_segment_begin = samples.begin() + attack_length;
    sustain_segment_end   = samples.end() - decay_length;
    vector<int16_t> sustain_segment_with_envelope(sustain_segment_begin, sustain_segment_end);

    // 5. Compare the sustain segments - should be identical
    EXPECT_THAT(sustain_segment_with_envelope, 
            ::testing::ContainerEq(sustain_segment_without_envelope));

    // 6. The first and the last element of the 'enveloped' should be identical
    // and equal to 0.
    EXPECT_EQ(samples.front(), samples.back());
    EXPECT_EQ(samples.front(), 0);

    // 7. The element at the end of attack should be equal to the original one
    EXPECT_EQ(*(samples.begin() + attack_length), *(samples_copy.begin() + attack_length));

    // 8. The element at the beginning of decay should be equal to the original one
    EXPECT_EQ(*(samples.end() - decay_length), *(samples_copy.end() - decay_length));

    // 9. The second element in the attack segment should be different from the original one.
    // Note that this element is (samples.begin() + 1), but if (samples_copy.begin() + 1) 
    // is equal to 0 then we have to take (samples.begin() + 2) instead.
    int32_t n;
    if (*(samples_copy.begin() + 1) != 0)
    {
        n = 1;
    }else
    {
        n = 2;
    }
    EXPECT_NE(*(samples.begin() + n), *(samples_copy.begin() + n));

    // 10. The second element in the decay segment should be different from the original one.
    // Note that this element is (samples.end() - decay_length + 1), but if 
    // (samples_copy.end() - decay_length + 1) is equal to 0 then we have to take 
    // (samples.end() - decay_length + 2) instead.
    if (*(samples_copy.end() - decay_length + 1) != 0)
    {
        n = 1;
    }else
    {
        n = 2;
    }
    EXPECT_NE(*(samples.end() - decay_length + n), *(samples_copy.end() - decay_length + n));

}

//========================================================================
// TESTS
//========================================================================
TEST(ArEnvelopeGenerationTest, HandleDifferentPitches)
{
    size_t pitch[]             = {0, kNumberOfFrequencies/size_t(2)};
    int32_t volume             = 1 << 15;
    uint32_t number_of_seconds = 5;
    double initial_phase       = 0;
    double peak_amplitude      = 1;
    double decay_duration      = 1;
    double attack_duration     = 1;
    const string file_name("test_pitch.wav");

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    // Initialise the envelope
    ArEnvelope envelope(synthesiser, peak_amplitude, attack_duration, decay_duration);

    // The length (in samples) of attack and decay
    vector<int16_t>::difference_type attack_length = 
        static_cast<vector<int16_t>::difference_type>(attack_duration * synthesiser.sampling_rate());
    vector<int16_t>::difference_type decay_length  = 
        static_cast<vector<int16_t>::difference_type>(decay_duration * synthesiser.sampling_rate());

    for (size_t pitch_id = 0; pitch_id < 2; pitch_id++)
    {
        // 1. Generate the samples and create a copy for later reference
        Oscillator osc(synthesiser, volume , initial_phase, pitch[pitch_id]);
        vector<int16_t> samples  = osc(number_of_seconds);

        ComparePreAndPostEnvelope(
                envelope,
                attack_length, 
                decay_length,
                samples);


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
