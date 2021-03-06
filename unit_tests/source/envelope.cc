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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <common/synth_config.h>
#include <envelope/envelope.h>
#include <oscillator/oscillator.h>
#include <cmath>

using namespace std;

//========================================================================
// UTILITIES
//========================================================================
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
    vector<int16_t> &samples_post_envelope) {
  // 1. Decalere the begining and end of the sustain segment
  vector<int16_t>::const_iterator sustain_segment_begin;
  vector<int16_t>::const_iterator sustain_segment_end;

  // 2. The 'sustain segment' of the original sound WITHOUT envelope
  sustain_segment_begin = samples_pre_envelope.begin() + attack_length;
  sustain_segment_end = samples_pre_envelope.end() - decay_length;
  vector<int16_t> sustain_segment_without_envelope(sustain_segment_begin,
                                                   sustain_segment_end);

  // 3. The 'sustain segment' of the original sound WITH envelope
  sustain_segment_begin = samples_post_envelope.begin() + attack_length;
  sustain_segment_end = samples_post_envelope.end() - decay_length;
  vector<int16_t> sustain_segment_with_envelope(sustain_segment_begin,
                                                sustain_segment_end);

  // 4. Compare the sustain segments - should be identical
  EXPECT_THAT(sustain_segment_with_envelope,
              ::testing::ContainerEq(sustain_segment_without_envelope));

  // 5. The first and the last element of 'enveloped' samples should be
  // identical and equal to 0.
  //
  // NOTE: This test makes only sense for AR envelopes with the attack and decay
  // segments
  //        longer than 0 samples
  if ((decay_length > 0) && (attack_length > 0)) {
    EXPECT_EQ(samples_post_envelope.front(), samples_post_envelope.back());
    EXPECT_EQ(samples_post_envelope.front(), 0);
  }

  // 6. The sample at the end of attack should be equal to the original one
  EXPECT_EQ(*(samples_post_envelope.begin() + attack_length - 1),
            *(samples_pre_envelope.begin() + attack_length - 1));

  // 7. The element at the beginning of decay should be equal to the original
  // one
  if (decay_length > 0)
    EXPECT_EQ(*(samples_post_envelope.end() - decay_length),
              *(samples_pre_envelope.end() - decay_length));

  // 8. The second element in the attack segment should be different from the
  // original one. Note that special care have to be taken if the original
  // sample was equal to 0. To be more precise, if the 2nd element in the attack
  // segment (original samples), (samples_pre_envelope.begin() + 1), is equal to
  // 0 then we have to take (samples_post_envelope.begin() + 2) instead. If the
  // second pick is also 0 then assume that the whole vector is filled with
  // zeros and there's no point asserting for 'not equal'.
  //
  // NOTE: This test makes only sense for AR envelopes with the attack segment
  // longer than 0 samples
  if (attack_length > 0) {
    if (*(samples_pre_envelope.begin() + 1) != 0) {
      EXPECT_NE(*(samples_post_envelope.begin() + 1),
                *(samples_pre_envelope.begin() + 1));
    } else if (*(samples_pre_envelope.begin() + 2) != 0) {
      EXPECT_NE(*(samples_post_envelope.begin() + 2),
                *(samples_pre_envelope.begin() + 2));
    }
  }

  // 9. The second element in the decay segment should be different from the
  // original one. Note that special care have to be taken if the original
  // sample was equal to 0. To be more precise, if the 2nd element in the attack
  // segment (original samples), (samples_pre_envelope.end() - decay_length +
  // 1), is equal to 0 then we have to take (samples_post_envelope.end() -
  // decay_length + 2) instead. If the second pick is also 0 then assume that
  // the whole vector is filled with zeros and there's no point asserting for
  // 'not equal'.
  //
  // NOTE: This test makes only sense for AR envelopes with the decay segment
  // longer than 0 samples
  if (decay_length > 0) {
    if (*(samples_pre_envelope.end() - decay_length + 1) != 0) {
      EXPECT_NE(*(samples_post_envelope.end() - decay_length + 1),
                *(samples_pre_envelope.end() - decay_length + 1));
    } else if (*(samples_pre_envelope.end() - decay_length + 2) != 0) {
      EXPECT_NE(*(samples_post_envelope.end() - decay_length + 2),
                *(samples_pre_envelope.end() - decay_length + 2));
    }
  }
}

//------------------------------------------------------------------------
//  NAME:
//      ComparePreAndPostAdsrEnvelope
//
//  DESCRIPTION:
//      By comparing the pre- and post- envelope samples, this function
//      verifies that conditions that have to be satisfied for an ADSR
//      envelope are indeed met.
//
//      The following assumptions about the envelope are made:
//      1) The sustain segment is constant with amplitude set to 1.0f
//      2) There are no discontinuities
//      3) The end amplitude for attack is 1.0f
//      4) The start ampltiude for decay is 1.0f
//      5) The
//  INPUT:
//      attack_length         - the length of the attack segment
//      decay_length          - the length of the decay segment
//      sustain_length        - the length of the sustain segment
//      release_length        - the length of the release segment
//      sustain_level         - amplitude of the sustain level
//      samples_pre_envelope  - samples before applying the envelope
//      samples_post_envelope - samples after applying the envelope
//  OUTPUT:
//      None
//------------------------------------------------------------------------
static void ComparePreAndPostAdsrEnvelope(
    vector<int16_t>::difference_type attack_length,
    vector<int16_t>::difference_type decay_length,
    vector<int16_t>::difference_type sustain_length,
    vector<int16_t>::difference_type release_length, double sustain_level,
    vector<int16_t> &samples_pre_envelope,
    vector<int16_t> &samples_post_envelope) {
  // 1. Decalere the begining and end of the sustain segment
  vector<int16_t>::const_iterator sustain_segment_begin;
  vector<int16_t>::const_iterator sustain_segment_end;

  // 2. The 'sustain segment' of the original sound WITHOUT envelope
  sustain_segment_begin =
      samples_pre_envelope.begin() + attack_length + decay_length;
  sustain_segment_end = samples_pre_envelope.begin() + attack_length +
                        decay_length + sustain_length;
  vector<int16_t> sustain_segment_without_envelope(sustain_segment_begin,
                                                   sustain_segment_end);

  // 3. The sustain segment is assumed to be constant, so by multiplying the
  // original signal by constant we should get the same values as by using the
  // envelope.
  for (auto &value : sustain_segment_without_envelope)
    value = static_cast<int16_t>(value * sustain_level);

  // 4. The 'sustain segment' of the original sound WITH envelope
  sustain_segment_begin =
      samples_post_envelope.begin() + attack_length + decay_length;
  sustain_segment_end = samples_post_envelope.begin() + attack_length +
                        decay_length + sustain_length;

  vector<int16_t> sustain_segment_with_envelope(sustain_segment_begin,
                                                sustain_segment_end);

  // 5. Compare the sustain segments - should be identical
  EXPECT_THAT(sustain_segment_with_envelope,
              ::testing::ContainerEq(sustain_segment_without_envelope));

  // 6. The first and the last element of 'enveloped' samples should be
  // identical and equal to 0.
  //
  // NOTE: This test makes only sense for AR envelopes with the attack and decay
  // segments
  //        longer than 0 samples
  if ((decay_length > 0) && (attack_length > 0)) {
    EXPECT_EQ(samples_post_envelope.front(), samples_post_envelope.back());
    EXPECT_EQ(samples_post_envelope.front(), 0);
  }

  // 7. The sample at the end of attack should be equal to the original one
  EXPECT_EQ(*(samples_post_envelope.begin() + attack_length - 1),
            *(samples_pre_envelope.begin() + attack_length - 1));

  // 8. The element at the beginning of release should be equal to the original
  // one
  if (release_length > 0)
    EXPECT_EQ(
        *(samples_post_envelope.end() - release_length),
        static_cast<int16_t>(sustain_level *
                             (*(samples_pre_envelope.end() - release_length))));

  // 9. The second element in the attack segment should be different from the
  // original one. Note that special care have to be taken if the original
  // sample was equal to 0. To be more precise, if the 2nd element in the attack
  // segment (original samples), (samples_pre_envelope.begin() + 1), is equal to
  // 0 then we have to take (samples_post_envelope.begin() + 2) instead. If the
  // second pick is also 0 then assume that the whole vector is filled with
  // zeros and there's no point asserting for 'not equal'.
  //
  // NOTE: This test makes only sense for AR envelopes with the attack segment
  // longer than 0 samples
  if (attack_length > 0) {
    if (*(samples_pre_envelope.begin() + 1) != 0) {
      EXPECT_NE(*(samples_post_envelope.begin() + 1),
                *(samples_pre_envelope.begin() + 1));
    } else if (*(samples_pre_envelope.begin() + 2) != 0) {
      EXPECT_NE(*(samples_post_envelope.begin() + 2),
                *(samples_pre_envelope.begin() + 2));
    }
  }

  // 10. The second element in the release segment should be different from the
  // original one. Note that special care have to be taken if the original
  // sample was equal to 0. To be more precise, if the 2nd element in the relese
  // segment (original samples), (samples_pre_envelope.end() - release_length +
  // 1), is equal to 0 then we have to take (samples_post_envelope.end() -
  // relese_length + 2) instead. If the second pick is also 0 then assume that
  // the whole vector is filled with zeros and there's no point asserting for
  // 'not equal'.
  //
  // NOTE: This test makes only sense for AR envelopes with the release segment
  // longer than 0 samples
  if (decay_length > 0) {
    if (*(samples_pre_envelope.end() - release_length + 1) != 0) {
      EXPECT_NE(*(samples_post_envelope.end() - release_length + 1),
                *(samples_pre_envelope.end() - release_length + 1));
    } else if (*(samples_pre_envelope.end() - release_length + 2) != 0) {
      EXPECT_NE(*(samples_post_envelope.end() - release_length + 2),
                *(samples_pre_envelope.end() - release_length + 2));
    }
  }
}

//========================================================================
// TESTS
//========================================================================
//------------------------------------------------------------------------
//  AR envelope
//------------------------------------------------------------------------
TEST(ArEnvelopeGenerationTest, HandleDifferentPitches) {
  vector<size_t> pitch = {0, kNumberOfFrequencies / size_t(2),
                          kNumberOfFrequencies - 1};
  int16_t volume = 1 << 14;
  uint32_t duration = 5;
  double initial_phase = 0;
  float peak_amplitude = 1;
  double decay_duration = 1;
  double attack_duration = 1;
  const string file_name("test_pitch.wav");

  // Initialise the synthesiser
  SynthConfig &synthesiser = SynthConfig::getInstance();
  synthesiser.Init();

  // Initialise the envelope
  ArEnvelope envelope(synthesiser, peak_amplitude, attack_duration,
                      decay_duration);

  // The length of attack and decay
  vector<int16_t>::difference_type attack_length =
      static_cast<vector<int16_t>::difference_type>(
          attack_duration * synthesiser.sampling_rate());
  vector<int16_t>::difference_type decay_length =
      static_cast<vector<int16_t>::difference_type>(
          decay_duration * synthesiser.sampling_rate());

  for (auto it = pitch.begin(); it != pitch.end(); it++) {
    // 1. Generate the samples and apply the envelope
    SineWaveform osc(synthesiser, volume, initial_phase, *it);
    vector<int16_t> samples_pre_envelope = osc(duration);

    // 2. Create a copy of the generated samples and apply the envelope
    vector<int16_t> samples_post_envelope = samples_pre_envelope;
    envelope.ApplyEnvelope(samples_post_envelope);

    // 3. Validate the application of the envelope by comapring the pre-
    // and post- enevelope samples
    ComparePreAndPostEnvelopeBasic(attack_length, decay_length,
                                   samples_pre_envelope, samples_post_envelope);
  }
}

TEST(ArEnvelopeGenerationTest, BasicTest) {
  size_t pitch = kNumberOfFrequencies / size_t(2);
  vector<int16_t> volume = {0, 1 << 7, 1 << 14};
  uint32_t duration = 5;
  double initial_phase = 0;
  float peak_amplitude = 1;
  double decay_duration = 1;
  double attack_duration = 1;
  const string file_name("test_pitch.wav");

  // Initialise the synthesiser
  SynthConfig &synthesiser = SynthConfig::getInstance();
  synthesiser.Init();

  // Initialise the envelope
  ArEnvelope envelope(synthesiser, peak_amplitude, attack_duration,
                      decay_duration);

  // The length of attack and decay
  vector<int16_t>::difference_type attack_length =
      static_cast<vector<int16_t>::difference_type>(
          attack_duration * synthesiser.sampling_rate());
  vector<int16_t>::difference_type decay_length =
      static_cast<vector<int16_t>::difference_type>(
          decay_duration * synthesiser.sampling_rate());

  for (auto it = volume.begin(); it != volume.end(); it++) {
    // 1. Generate the samples and apply the envelope
    SineWaveform osc(synthesiser, *it, initial_phase, pitch);
    vector<int16_t> samples_pre_envelope = osc(duration);

    // 2. Create a copy of the generated samples and apply the envelope
    vector<int16_t> samples_post_envelope = samples_pre_envelope;
    envelope.ApplyEnvelope(samples_post_envelope);

    // 3. Validate the application of the envelope by comapring the pre-
    // and post- enevelope samples
    ComparePreAndPostEnvelopeBasic(attack_length, decay_length,
                                   samples_pre_envelope, samples_post_envelope);
  }
}

TEST(ArEnvelopeGenerationTest, HandleDifferentOveralDuration) {
  size_t pitch = kNumberOfFrequencies / size_t(2);
  int16_t volume = 1 << 7;
  vector<uint32_t> duration = {2, 5, 10};
  double initial_phase = 0;
  float peak_amplitude = 1;
  double decay_duration = 1;
  double attack_duration = 1;
  const string file_name("test_pitch.wav");

  // Initialise the synthesiser
  SynthConfig &synthesiser = SynthConfig::getInstance();
  synthesiser.Init();

  // Initialise the envelope
  ArEnvelope envelope(synthesiser, peak_amplitude, attack_duration,
                      decay_duration);

  // The length of attack and decay
  vector<int16_t>::difference_type attack_length =
      static_cast<vector<int16_t>::difference_type>(
          attack_duration * synthesiser.sampling_rate());
  vector<int16_t>::difference_type decay_length =
      static_cast<vector<int16_t>::difference_type>(
          decay_duration * synthesiser.sampling_rate());

  for (auto it = duration.begin(); it != duration.end(); it++) {
    // 1. Generate the samples and apply the envelope
    SineWaveform osc(synthesiser, volume, initial_phase, pitch);
    vector<int16_t> samples_pre_envelope = osc(*it);

    // 2. Create a copy of the generated samples and apply the envelope
    vector<int16_t> samples_post_envelope = samples_pre_envelope;
    envelope.ApplyEnvelope(samples_post_envelope);

    // 3. Validate the application of the envelope by comapring the pre-
    // and post- enevelope samples
    if ((samples_pre_envelope.begin() == samples_pre_envelope.end()) &&
        (samples_post_envelope.begin() == samples_post_envelope.end()) &&
        (*it == 0)) {
      continue;
    }
    ComparePreAndPostEnvelopeBasic(attack_length, decay_length,
                                   samples_pre_envelope, samples_post_envelope);
  }
}

TEST(ArEnvelopeGenerationTest, HandleDifferentDecayDuration) {
  size_t pitch = kNumberOfFrequencies / size_t(2);
  int16_t volume = 1 << 7;
  uint32_t duration = 5;
  double initial_phase = 0;
  float peak_amplitude = 1;
  double attack_duration = 1;
  vector<double> decay_duration = {0, 1, 2.3, 3, 4};
  const string file_name("test_pitch.wav");

  // Initialise the synthesiser
  SynthConfig &synthesiser = SynthConfig::getInstance();
  synthesiser.Init();

  for (auto it = decay_duration.begin(); it != decay_duration.end(); it++) {
    // 1. Initialise the envelope
    ArEnvelope envelope(synthesiser, peak_amplitude, attack_duration, *it);

    // The length of attack and decay
    vector<int16_t>::difference_type attack_length =
        static_cast<vector<int16_t>::difference_type>(
            attack_duration * synthesiser.sampling_rate());
    vector<int16_t>::difference_type decay_length =
        static_cast<vector<int16_t>::difference_type>(
            *it * synthesiser.sampling_rate());

    // 2. Generate the samples and apply the envelope
    SineWaveform osc(synthesiser, volume, initial_phase, pitch);
    vector<int16_t> samples_pre_envelope = osc(duration);

    // 3. Create a copy of the generated samples and apply the envelope
    vector<int16_t> samples_post_envelope = samples_pre_envelope;
    envelope.ApplyEnvelope(samples_post_envelope);

    // 4. Validate the application of the envelope by comapring the pre-
    // and post- enevelope samples
    if ((samples_pre_envelope.begin() == samples_pre_envelope.end()) &&
        (samples_post_envelope.begin() == samples_post_envelope.end()) &&
        (fabs(*it) < kEps)) {
      continue;
    }
    ComparePreAndPostEnvelopeBasic(attack_length, decay_length,
                                   samples_pre_envelope, samples_post_envelope);
  }
}

TEST(ArEnvelopeGenerationTest, HandleDifferentAttackDuration) {
  size_t pitch = kNumberOfFrequencies / size_t(2);
  int16_t volume = 1 << 7;
  uint32_t duration = 5;
  double initial_phase = 0;
  float peak_amplitude = 1;
  double decay_duration = 1;
  vector<double> attack_duration = {0, 1, 2.3, 3, 4};
  const string file_name("test_pitch.wav");

  // Initialise the synthesiser
  SynthConfig &synthesiser = SynthConfig::getInstance();
  synthesiser.Init();

  for (auto it = attack_duration.begin(); it != attack_duration.end(); it++) {
    // 1. Initialise the envelope
    ArEnvelope envelope(synthesiser, peak_amplitude, *it, decay_duration);

    // The length of attack and decay
    vector<int16_t>::difference_type attack_length =
        static_cast<vector<int16_t>::difference_type>(
            *it * synthesiser.sampling_rate());
    vector<int16_t>::difference_type decay_length =
        static_cast<vector<int16_t>::difference_type>(
            decay_duration * synthesiser.sampling_rate());

    // 2. Generate the samples and apply the envelope
    SineWaveform osc(synthesiser, volume, initial_phase, pitch);
    vector<int16_t> samples_pre_envelope = osc(duration);

    // 3. Create a copy of the generated samples and apply the envelope
    vector<int16_t> samples_post_envelope = samples_pre_envelope;
    envelope.ApplyEnvelope(samples_post_envelope);

    // 4. Validate the application of the envelope by comapring the pre-
    // and post- enevelope samples
    if ((samples_pre_envelope.begin() == samples_pre_envelope.end()) &&
        (samples_post_envelope.begin() == samples_post_envelope.end()) &&
        (fabs(*it) < kEps)) {
      continue;
    }
    ComparePreAndPostEnvelopeBasic(attack_length, decay_length,
                                   samples_pre_envelope, samples_post_envelope);
  }
}

//------------------------------------------------------------------------
//  ADSR envelope
//------------------------------------------------------------------------
TEST(AdsrEnvelopeGenerationTest, HandleDifferentSustainLevels) {
  size_t pitch = kNumberOfFrequencies / size_t(2);
  int16_t volume = 1 << 7;
  uint32_t duration = 4;
  float exponent_adr = 1.0f;
  float exponent_s = 0.0f;
  double initial_phase = 0;
  float start_amplitude_attack = 0.0;
  float end_amplitude_attack = 1.0;
  float start_amplitude_decay = end_amplitude_attack;
  vector<float> end_amplitude_decay = {0.0, 0.001953125f, 0.5, 1,
                                       2,   100};  //, 1000.13f};
  float start_amplitude_sustain = 0;
  float end_amplitude_release = 0.0;
  double adsr_segment_duration = 1.0;
  float end_amplitude_sustain;
  float start_amplitude_release;
  size_t number_of_samples;

  // NOTE: Amplitudes are defined so that there are no discontinuities.
  //       All segments are identical length. The attack, decay and
  //       release segments are linear (exponent equal to 1), and
  //       the sustain segment is constant. This is to satisfy the
  //       requirements of ComparePreAndPostAdsrEnvelope. Note that
  //       with this restrictions modifying the end_amplitude_decay
  //       is equivalent to setting the sustain segment level.

  // Initialise the synthesiser
  SynthConfig &synthesiser = SynthConfig::getInstance();
  synthesiser.Init();

  // Number of samples in every segment
  adsr_segment_duration = duration / 4.0;
  number_of_samples =
      static_cast<size_t>(synthesiser.sampling_rate() * adsr_segment_duration);

  for (auto it : end_amplitude_decay) {
    // 1. Finish defining amplitudes
    end_amplitude_sustain = it;
    start_amplitude_release = it;

    // 2. Create the attack segment
    auto segment_attack = unique_ptr<Segment>(
        new ExponentialSegment(start_amplitude_attack, end_amplitude_attack,
                               exponent_adr, number_of_samples));

    // 3. Create the decay segment
    auto segment_decay = unique_ptr<Segment>(new ExponentialSegment(
        start_amplitude_decay, it, exponent_adr, number_of_samples));

    // 3. Create the sustain segment
    auto segment_sustain = unique_ptr<Segment>(new ExponentialSegment(
        start_amplitude_sustain, it, exponent_s, number_of_samples));

    // 4. Create the release segment
    auto segment_release = unique_ptr<Segment>(
        new ExponentialSegment(start_amplitude_release, end_amplitude_release,
                               exponent_adr, number_of_samples));

    // 5. Create the envelope
    AdsrEnvelope envelope(segment_attack, segment_decay, segment_sustain,
                          segment_release);

    // 6. Calculate the length of attack, decay, sustain and release segments
    vector<int16_t>::difference_type attack_length =
        static_cast<vector<int16_t>::difference_type>(
            adsr_segment_duration * synthesiser.sampling_rate());
    vector<int16_t>::difference_type decay_length =
        static_cast<vector<int16_t>::difference_type>(
            adsr_segment_duration * synthesiser.sampling_rate());
    vector<int16_t>::difference_type sustain_length =
        static_cast<vector<int16_t>::difference_type>(
            adsr_segment_duration * synthesiser.sampling_rate());
    vector<int16_t>::difference_type release_length =
        static_cast<vector<int16_t>::difference_type>(
            adsr_segment_duration * synthesiser.sampling_rate());

    // 7. Generate the samples and apply the envelope
    SineWaveform osc(synthesiser, volume, initial_phase, pitch);
    vector<int16_t> samples_pre_envelope = osc(duration);

    // 8. Create a copy of the generated samples and apply the envelope
    vector<int16_t> samples_post_envelope = samples_pre_envelope;
    envelope.ApplyEnvelope(samples_post_envelope);

    // 9. Validate the application of the envelope by comparing the pre-
    // and post- envelope samples
    ComparePreAndPostAdsrEnvelope(attack_length, decay_length, sustain_length,
                                  release_length, it, samples_pre_envelope,
                                  samples_post_envelope);
  }
}
//========================================================================
// End of file
//========================================================================
