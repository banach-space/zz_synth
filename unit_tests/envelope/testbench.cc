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
        vector<int16_t>::difference_type attack_length, 
        vector<int16_t>::difference_type decay_length,
        vector<int16_t> &samples_pre_envelope,
        vector<int16_t> &samples_post_envelope);
void ComparePreAndPostEnvelope(
        vector<int16_t>::difference_type attack_length, 
        vector<int16_t>::difference_type decay_length,
        vector<int16_t> &samples_pre_envelope,
        vector<int16_t> &samples_post_envelope)
{
    // 1. Decalere the begining and end of the sustain segment
    vector<int16_t>::const_iterator sustain_segment_begin;
    vector<int16_t>::const_iterator sustain_segment_end; 

    // 2. The 'sustain segment' of the original sound WITHOUT envelope
    sustain_segment_begin = samples_pre_envelope.begin() + attack_length;
    sustain_segment_end   = samples_pre_envelope.end() - decay_length;
    vector<int16_t> sustain_segment_without_envelope(sustain_segment_begin, sustain_segment_end);

    // 3. The 'sustain segment' of the original sound WITH envelope
    sustain_segment_begin = samples_post_envelope.begin() + attack_length;
    sustain_segment_end   = samples_post_envelope.end() - decay_length;
    vector<int16_t> sustain_segment_with_envelope(sustain_segment_begin, sustain_segment_end);

    // 4. Compare the sustain segments - should be identical
    EXPECT_THAT(sustain_segment_with_envelope, 
            ::testing::ContainerEq(sustain_segment_without_envelope));

    // 5. The first and the last element of the 'enveloped' should be identical
    // and equal to 0.
    EXPECT_EQ(samples_post_envelope.front(), samples_post_envelope.back());
    EXPECT_EQ(samples_post_envelope.front(), 0);

    // 6. The element at the end of attack should be equal to the original one
    EXPECT_EQ(*(samples_post_envelope.begin() + attack_length), *(samples_pre_envelope.begin() + attack_length));

    // 7. The element at the beginning of decay should be equal to the original one
    EXPECT_EQ(*(samples_post_envelope.end() - decay_length), *(samples_pre_envelope.end() - decay_length));

    // 8. The second element in the attack segment should be different from the original one.
    // Note that this element is (samples_post_envelope.begin() + 1), but if this element 
    // is equal to 0 then we have to take (samples_post_envelope.begin() + 2) instead. If
    // the second pick is also 0 then assume that the whole vector is filled with zeros
    // and there's no point checking 'not equal'.
    if (*(samples_pre_envelope.begin() + 1) != 0)
    {
        EXPECT_NE(*(samples_post_envelope.begin() + 1), *(samples_pre_envelope.begin() + 1));
    }else if(*(samples_pre_envelope.begin() + 2) != 0 )
    {
        EXPECT_NE(*(samples_post_envelope.begin() + 2), *(samples_pre_envelope.begin() + 2));
    }

    // 9. The second element in the decay segment should be different from the original one.
    // Note that this element is (samples_post_envelope.end() - decay_length + 1), but if 
    // this element is equal to 0 then we have to take (samples_post_envelope.end() - decay_length + 2)
    // instead. If the second pick is also 0 then assume that the whole vector is filled with zeros
    // and there's no point checking 'not equal'.
    if (*(samples_pre_envelope.end() - decay_length + 1) != 0)
    {
        EXPECT_NE(
                *(samples_post_envelope.end() - decay_length + 1), 
                *(samples_pre_envelope.end() - decay_length + 1));
    }else if(*(samples_pre_envelope.end() - decay_length + 2) != 0 )
    {
        EXPECT_NE(
                *(samples_post_envelope.end() - decay_length + 2), 
                *(samples_pre_envelope.end() - decay_length + 2));
    }

}

//========================================================================
// TESTS
//========================================================================
TEST(ArEnvelopeGenerationTest, HandleDifferentPitches)
{
    size_t pitch[]         = {0, kNumberOfFrequencies/size_t(2), kNumberOfFrequencies - 1};
    int32_t volume         = 1 << 15;
    uint32_t duration      = 5;
    double initial_phase   = 0;
    double peak_amplitude  = 1;
    double decay_duration  = 1;
    double attack_duration = 1;
    const string file_name("test_pitch.wav");

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    // Initialise the envelope
    ArEnvelope envelope(synthesiser, peak_amplitude, attack_duration, decay_duration);

    // The length of attack and decay
    vector<int16_t>::difference_type attack_length = 
        static_cast<vector<int16_t>::difference_type>(attack_duration * synthesiser.sampling_rate());
    vector<int16_t>::difference_type decay_length  = 
        static_cast<vector<int16_t>::difference_type>(decay_duration * synthesiser.sampling_rate());

    for (size_t pitch_id = 0; pitch_id < 3; pitch_id++)
    {
        // 1. Generate the samples and apply the envelope
        Oscillator osc(synthesiser, volume , initial_phase, pitch[pitch_id]);
        vector<int16_t> samples_pre_envelope  = osc(duration);

        // 2. Create a copy of the generated samples and apply the envelope
        vector<int16_t> samples_post_envelope  = samples_pre_envelope;
        envelope.ApplyEnvelope(samples_post_envelope);

        // 3. Validate the application of the envelope by comapring the pre- 
        // and post- enevelope samples
        ComparePreAndPostEnvelope(
                attack_length, 
                decay_length,
                samples_pre_envelope,
                samples_post_envelope);
    }

}

TEST(ArEnvelopeGenerationTest, HandleDifferentVolumes)
{
    size_t pitch           = kNumberOfFrequencies/size_t(2);
    int32_t volume[]       = {0, 1 << 7, 1 << 15};
    uint32_t duration      = 5;
    double initial_phase   = 0;
    double peak_amplitude  = 1;
    double decay_duration  = 1;
    double attack_duration = 1;
    const string file_name("test_pitch.wav");

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    // Initialise the envelope
    ArEnvelope envelope(synthesiser, peak_amplitude, attack_duration, decay_duration);

    // The length of attack and decay
    vector<int16_t>::difference_type attack_length = 
        static_cast<vector<int16_t>::difference_type>(attack_duration * synthesiser.sampling_rate());
    vector<int16_t>::difference_type decay_length  = 
        static_cast<vector<int16_t>::difference_type>(decay_duration * synthesiser.sampling_rate());

    for (size_t volume_id = 0; volume_id < 3; volume_id++)
    {
        // 1. Generate the samples and apply the envelope
        Oscillator osc(synthesiser, volume[volume_id] , initial_phase, pitch);
        vector<int16_t> samples_pre_envelope  = osc(duration);

        // 2. Create a copy of the generated samples and apply the envelope
        vector<int16_t> samples_post_envelope  = samples_pre_envelope;
        envelope.ApplyEnvelope(samples_post_envelope);

        // 3. Validate the application of the envelope by comapring the pre- 
        // and post- enevelope samples
        ComparePreAndPostEnvelope(
                attack_length, 
                decay_length,
                samples_pre_envelope,
                samples_post_envelope);
    }
}

TEST(ArEnvelopeGenerationTest, HandleDifferentOveralDuration)
{
    size_t pitch           = kNumberOfFrequencies/size_t(2);
    int32_t volume         = 1 << 7;
    uint32_t duration[]    = {0, 5, 10};
    double initial_phase   = 0;
    double peak_amplitude  = 1;
    double decay_duration  = 1;
    double attack_duration = 1;
    const string file_name("test_pitch.wav");

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    // Initialise the envelope
    ArEnvelope envelope(synthesiser, peak_amplitude, attack_duration, decay_duration);

    // The length of attack and decay
    vector<int16_t>::difference_type attack_length = 
        static_cast<vector<int16_t>::difference_type>(attack_duration * synthesiser.sampling_rate());
    vector<int16_t>::difference_type decay_length  = 
        static_cast<vector<int16_t>::difference_type>(decay_duration * synthesiser.sampling_rate());

    for (size_t duration_id = 0; duration_id < 3; duration_id++)
    {
        // 1. Generate the samples and apply the envelope
        Oscillator osc(synthesiser, volume , initial_phase, pitch);
        vector<int16_t> samples_pre_envelope  = osc(duration[duration_id]);

        // 2. Create a copy of the generated samples and apply the envelope
        vector<int16_t> samples_post_envelope  = samples_pre_envelope;
        envelope.ApplyEnvelope(samples_post_envelope);

        // 3. Validate the application of the envelope by comapring the pre- 
        // and post- enevelope samples
        if (
                (samples_pre_envelope.begin() == samples_pre_envelope.end()) 
                && (samples_post_envelope.begin() == samples_post_envelope.end())
                && (duration[duration_id] == 0))
        {
            continue;
        }
        ComparePreAndPostEnvelope(
                attack_length, 
                decay_length,
                samples_pre_envelope,
                samples_post_envelope);
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
