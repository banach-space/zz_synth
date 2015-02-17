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

#include <envelope/envelope.h>
#include <common/synth_config.h>
#include <common/oscillator.h>

//========================================================================
// UTILITIES 
//========================================================================
//------------------------------------------------------------------------
//  NAME:
//      ComparePreAndPostEnvelopeBasic
//  
//  DESCRIPTION:
//      Compares the pre- and post- envelope samples and checks conditions
//      that have to be satisfied for every AR envelope. 
//  INPUT:
//      attack_length         - the length of the attack segment
//      decay_length          - the length of the decay segment
//      samples_pre_envelope  - samples before applying the envelope
//      samples_post_envelope - samples after applying the envelope
//  OUTPUT:
//      None
//------------------------------------------------------------------------
static void ComparePreAndPostEnvelopeBasic(
        vector<int16_t>::difference_type attack_length, 
        vector<int16_t>::difference_type decay_length,
        vector<int16_t> &samples_pre_envelope,
        vector<int16_t> &samples_post_envelope);
//------------------------------------------------------------------------
//  NAME:
//      ComparePreAndPostEnvelopeBasic
//  
//  DESCRIPTION:
//      By comparing the pre- and post- envelope samples, this function
//      verifies that conditions that have to be satisfied for an AR
//      envelope are indeed met.
//  INPUT:
//      attack_length         - the length of the attack segment
//      decay_length          - the length of the decay segment
//      samples_pre_envelope  - samples before applying the envelope
//      samples_post_envelope - samples after applying the envelope
//  OUTPUT:
//      None
//------------------------------------------------------------------------
static void ComparePreAndPostEnvelopeBasic(
        vector<int16_t>::difference_type attack_length, 
        vector<int16_t>::difference_type decay_length,
        vector<int16_t> &samples_pre_envelope,
        vector<int16_t> &samples_post_envelope);
static void ComparePreAndPostEnvelopeBasic(
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

    // 5. The first and the last element of 'enveloped' samples should be identical and equal to 0.
    //
    // NOTE: This test makes only sense for AR envelopes with the attack and decay segments 
    //        longer than 0 samples
    if ((decay_length > 0) && (attack_length > 0))
    {
        EXPECT_EQ(samples_post_envelope.front(), samples_post_envelope.back());
        EXPECT_EQ(samples_post_envelope.front(), 0);
    }

    // 6. The sample at the end of attack should be equal to the original one
    EXPECT_EQ(*(samples_post_envelope.begin() + attack_length), *(samples_pre_envelope.begin() + attack_length));

    // 7. The element at the beginning of decay should be equal to the original one
    if (decay_length > 0)
        EXPECT_EQ(*(samples_post_envelope.end() - decay_length), *(samples_pre_envelope.end() - decay_length));

    // 8. The second element in the attack segment should be different from the original one. Note that 
    // special care have to be taken if the original sample was equal to 0. To be more precise, if 
    // the 2nd element in the attack segment (original samples), (samples_pre_envelope.begin() + 1), is equal
    // to 0 then we have to take (samples_post_envelope.begin() + 2) instead. If the second pick is also 0
    // then assume that the whole vector is filled with zeros and there's no point asserting for 'not equal'.
    //
    // NOTE: This test makes only sense for AR envelopes with the attack segment longer than 0 samples
    if (attack_length > 0)
    {
        if (*(samples_pre_envelope.begin() + 1) != 0)
        {
            EXPECT_NE(*(samples_post_envelope.begin() + 1), *(samples_pre_envelope.begin() + 1));
        }else if(*(samples_pre_envelope.begin() + 2) != 0 )
        {
            EXPECT_NE(*(samples_post_envelope.begin() + 2), *(samples_pre_envelope.begin() + 2));
        }
    }

    // 9. The second element in the decay segment should be different from the original one. Note that 
    // special care have to be taken if the original sample was equal to 0. To be more precise, if 
    // the 2nd element in the attack segment (original samples), (samples_pre_envelope.end() - decay_length + 1),
    // is equal to 0 then we have to take (samples_post_envelope.end() - decay_length + 2) instead. If the
    // second pick is also 0 then assume that the whole vector is filled with zeros and there's no point
    // asserting for 'not equal'.
    //
    // NOTE: This test makes only sense for AR envelopes with the decay segment longer than 0 samples
    if (decay_length > 0)
    {
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

}

static void ComparePreAndPostEnvelopeNonZeroAttack(
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


}

//========================================================================
// TESTS
//========================================================================
TEST(ArEnvelopeGenerationTest, HandleDifferentPitches)
{
    vector<size_t> pitch   = {0, kNumberOfFrequencies/size_t(2), kNumberOfFrequencies - 1};
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

    for (vector<size_t>::iterator it = pitch.begin(); it != pitch.end(); it++)
    {
        // 1. Generate the samples and apply the envelope
        Oscillator osc(synthesiser, volume , initial_phase, *it);
        vector<int16_t> samples_pre_envelope  = osc(duration);

        // 2. Create a copy of the generated samples and apply the envelope
        vector<int16_t> samples_post_envelope  = samples_pre_envelope;
        envelope.ApplyEnvelope(samples_post_envelope);

        // 3. Validate the application of the envelope by comapring the pre- 
        // and post- enevelope samples
        ComparePreAndPostEnvelopeBasic(
                attack_length, 
                decay_length,
                samples_pre_envelope,
                samples_post_envelope);
    }

}

TEST(ArEnvelopeGenerationTest, HandleDifferentVolumes)
{
    size_t pitch           = kNumberOfFrequencies/size_t(2);
    vector<int32_t> volume = {0, 1 << 7, 1 << 15};
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

    for (vector<int32_t>::iterator it = volume.begin(); it != volume.end(); it++)
    {
        // 1. Generate the samples and apply the envelope
        Oscillator osc(synthesiser, *it , initial_phase, pitch);
        vector<int16_t> samples_pre_envelope  = osc(duration);

        // 2. Create a copy of the generated samples and apply the envelope
        vector<int16_t> samples_post_envelope  = samples_pre_envelope;
        envelope.ApplyEnvelope(samples_post_envelope);

        // 3. Validate the application of the envelope by comapring the pre- 
        // and post- enevelope samples
        ComparePreAndPostEnvelopeBasic(
                attack_length, 
                decay_length,
                samples_pre_envelope,
                samples_post_envelope);
    }
}

TEST(ArEnvelopeGenerationTest, HandleDifferentOveralDuration)
{
    size_t pitch              = kNumberOfFrequencies/size_t(2);
    int32_t volume            = 1 << 7;
    vector<uint32_t> duration = {2, 5, 10};
    double initial_phase      = 0;
    double peak_amplitude     = 1;
    double decay_duration     = 1;
    double attack_duration    = 1;
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

    for (vector<uint32_t>::iterator it = duration.begin(); it != duration.end(); it++)
    {
        // 1. Generate the samples and apply the envelope
        Oscillator osc(synthesiser, volume , initial_phase, pitch);
        vector<int16_t> samples_pre_envelope  = osc(*it);

        // 2. Create a copy of the generated samples and apply the envelope
        vector<int16_t> samples_post_envelope  = samples_pre_envelope;
        envelope.ApplyEnvelope(samples_post_envelope);

        // 3. Validate the application of the envelope by comapring the pre- 
        // and post- enevelope samples
        if (
                (samples_pre_envelope.begin() == samples_pre_envelope.end()) 
                && (samples_post_envelope.begin() == samples_post_envelope.end())
                && (*it == 0))
        {
            continue;
        }
        ComparePreAndPostEnvelopeBasic(
                attack_length, 
                decay_length,
                samples_pre_envelope,
                samples_post_envelope);
    }
}

TEST(ArEnvelopeGenerationTest, HandleDifferentDecayDuration)
{
    size_t pitch                  = kNumberOfFrequencies/size_t(2);
    int32_t volume                = 1 << 7;
    uint32_t duration             = 5;
    double initial_phase          = 0;
    double peak_amplitude         = 1;
    double attack_duration        = 1;
    vector<double> decay_duration = {0, 1, 2.3, 3, 4};
    const string file_name("test_pitch.wav");

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	


    for (vector<double>::iterator it = decay_duration.begin(), it_end = decay_duration.end(); 
            it != it_end; 
            it++)
    {
        // 1. Initialise the envelope
        ArEnvelope envelope(synthesiser, peak_amplitude, attack_duration, *it);

        // The length of attack and decay
        vector<int16_t>::difference_type attack_length = 
            static_cast<vector<int16_t>::difference_type>(attack_duration * synthesiser.sampling_rate());
        vector<int16_t>::difference_type decay_length  = 
            static_cast<vector<int16_t>::difference_type>(*it * synthesiser.sampling_rate());

        // 2. Generate the samples and apply the envelope
        Oscillator osc(synthesiser, volume , initial_phase, pitch);
        vector<int16_t> samples_pre_envelope  = osc(duration);

        // 3. Create a copy of the generated samples and apply the envelope
        vector<int16_t> samples_post_envelope  = samples_pre_envelope;
        envelope.ApplyEnvelope(samples_post_envelope);

        // 4. Validate the application of the envelope by comapring the pre- 
        // and post- enevelope samples
        if (
                (samples_pre_envelope.begin() == samples_pre_envelope.end()) 
                && (samples_post_envelope.begin() == samples_post_envelope.end())
                && (*it == 0))
        {
            continue;
        }
        ComparePreAndPostEnvelopeBasic(
                attack_length, 
                decay_length,
                samples_pre_envelope,
                samples_post_envelope);
    }
}

TEST(ArEnvelopeGenerationTest, HandleDifferentAttackDuration)
{
    size_t pitch                   = kNumberOfFrequencies/size_t(2);
    int32_t volume                 = 1 << 7;
    uint32_t duration              = 5;
    double initial_phase           = 0;
    double peak_amplitude          = 1;
    double decay_duration          = 1;
    vector<double> attack_duration = {0, 1, 2.3, 3, 4};
    const string file_name("test_pitch.wav");

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	


    for (vector<double>::iterator it = attack_duration.begin(), it_end = attack_duration.end(); 
            it != it_end; 
            it++)
    {
        // 1. Initialise the envelope
        ArEnvelope envelope(synthesiser, peak_amplitude, *it, decay_duration);

        // The length of attack and decay
        vector<int16_t>::difference_type attack_length = 
            static_cast<vector<int16_t>::difference_type>(*it * synthesiser.sampling_rate());
        vector<int16_t>::difference_type decay_length  = 
            static_cast<vector<int16_t>::difference_type>(decay_duration * synthesiser.sampling_rate());

        // 2. Generate the samples and apply the envelope
        Oscillator osc(synthesiser, volume , initial_phase, pitch);
        vector<int16_t> samples_pre_envelope  = osc(duration);

        // 3. Create a copy of the generated samples and apply the envelope
        vector<int16_t> samples_post_envelope  = samples_pre_envelope;
        envelope.ApplyEnvelope(samples_post_envelope);

        // 4. Validate the application of the envelope by comapring the pre- 
        // and post- enevelope samples
        if (
                (samples_pre_envelope.begin() == samples_pre_envelope.end()) 
                && (samples_post_envelope.begin() == samples_post_envelope.end())
                && (*it == 0))
        {
            continue;
        }
        ComparePreAndPostEnvelopeBasic(
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
