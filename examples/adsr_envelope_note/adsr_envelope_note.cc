//========================================================================
// FILE:
//   examples/adsr_envelope_note/adsr_envelope_note.cc
//
// AUTHOR:
//   zimzum@github
//
// DESCRIPTION:
//   This file is intended to demonstrate how to generate notes with
//   ADSR envelopes and to save them to WAVE files using the zz-synthesiser.
//   A number of files with enveloped plain sound are generated. There
//   are 20 hard-coded parameters that determine the sounds being
//   produced. These are marked with 'Param #:' and can be freely
//   modified to experiment.
//
// License: GNU GPL v2.0
//========================================================================

#include <global/global_variables.h>
#include <common/wave_file.h>
#include <common/synth_config.h>
#include <oscillator/oscillator.h>
#include <envelope/envelope.h>

using namespace std;

//========================================================================
// MAIN
//========================================================================
int main()
{
    // Param 1: Pitch
    vector<size_t> pitch = {20, 40, 60, 80, 100};
    // Param 2: Volume
    int16_t volume       = 1 << 14;
    // Param 3: Duration
    uint32_t duration    = 10;
    // Param 4: Initial phase
    double initial_phase = 0;
    // Params 5-8: Exponent for attack (a), decay (d), release (r) and sustain (s)
    float exponent_a = 2.0f;
    float exponent_d = 1.0f;
    float exponent_r = 1.5f;
    float exponent_s = 0.0f;
    // Params 9-16: Starting and final amplitude for attack, decay, sustain and release
    float start_amplitude_attack  = 0.0;
    float end_amplitude_attack    = 2.0;
    float start_amplitude_decay   = end_amplitude_attack;
    float end_amplitude_decay     = 1;
    float start_amplitude_sustain = 0; // Has to be '0' if exponent is 0
    float end_amplitude_sustain   = end_amplitude_decay;
    float start_amplitude_release = end_amplitude_decay;
    float end_amplitude_release   = 0.0;
    // Params: 17-20: Segments' length (the sum of the following 4 parameters must equal to duration)
    double a_segment_duration = 2.0;
    double d_segment_duration = 1.0;
    double s_segment_duration = 4.0;
    double r_segment_duration = 3.0;

    size_t number_of_samples;
    uint32_t file_idx = 0;
    char file_name[200];

    // NOTE: Amplitudes are defined so that there are no discontinuities.
    //       All segments are identical length. The attack, decay and
    //       release segments are linear (exponent equal to 1), and
    //       the sustain segment is constant. This is to satisfy the
    //       requirements of ComparePreAndPostAdsrEnvelope. Note that
    //       with this restrictions modifying the end_amplitude_decay
    //       is equivalent to setting the sustain segment level.
    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();

    for (auto it : pitch)
    {
        // 1. Generate filename
        sprintf(file_name, "examples/adsr_envelope_note/sounds/adsr_envelope_note_%d.wav", file_idx);
        file_idx++;

        // 2. Create the attack segment
        number_of_samples = static_cast<size_t>(synthesiser.sampling_rate() * a_segment_duration);
        auto segment_attack =
            unique_ptr<Segment>(new ExponentialSegment(
                        start_amplitude_attack,
                        end_amplitude_attack,
                        exponent_a,
                        number_of_samples));

        // 3. Create the decay segment
        number_of_samples = static_cast<size_t>(synthesiser.sampling_rate() * d_segment_duration);
        auto segment_decay =
            unique_ptr<Segment>(new ExponentialSegment(
                        start_amplitude_decay,
                        end_amplitude_decay,
                        exponent_d,
                        number_of_samples));

        // 3. Create the sustain segment
        number_of_samples = static_cast<size_t>(synthesiser.sampling_rate() * s_segment_duration);
        auto segment_sustain =
            unique_ptr<Segment>(new ExponentialSegment(
                        start_amplitude_sustain,
                        end_amplitude_sustain,
                        exponent_s,
                        number_of_samples));

        // 4. Create the release segment
        number_of_samples = static_cast<size_t>(synthesiser.sampling_rate() * r_segment_duration);
        auto segment_release =
            unique_ptr<Segment>(new ExponentialSegment(
                        start_amplitude_release,
                        end_amplitude_release,
                        exponent_r,
                        number_of_samples));

        // 5. Create the envelope
        AdsrEnvelope envelope(segment_attack, segment_decay, segment_sustain, segment_release);

        // 6. Generate the samples and apply the envelope
        SineWaveform osc(synthesiser, volume , initial_phase, it);
        vector<int16_t> samples  = osc(duration);

        // 7.  Apply the envelope
        envelope.ApplyEnvelope(samples);

        // 8. Save the samples to the file
        WaveFileOut wf_out(duration);
        wf_out.SaveBufferToFile(file_name, samples);
    }

	return 0;
}
