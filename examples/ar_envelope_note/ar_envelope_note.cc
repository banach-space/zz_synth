//========================================================================
// FILE:
//   examples/ar_envelope_note/ar_envelope_note.cc
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//   This file is intended to demonstrate how to generate notes with
//   AR envelopes and to save them to WAVE files using the zz-synthesiser. A number
//   of files with enveloped plain sound  are generated. There
//   are seven hard-coded parameters that determine the sounds being
//   produced. These are marked with 'Param #:' and can be freely
//   modified to experiment.
//
// License: GNU GPL v2.0 
//========================================================================

#include <global/global_variables.h>
#include <common/wave_file.h>
#include <common/synth_config.h>
#include <common/oscillator.h>
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
    uint32_t duration    = 5;
    // Param 4: Initial phase
    double initial_phase = 0;
    // Param 5: Peak amplitude in the envelope (1 corresponds to 100%)
    float peak_amplitude   = 1;
    // Param 6: The length of decay segment (in seconds)
    double decay_duration  = 1;
    // Param 7: The length of attack segment (in seconds)
    double attack_duration = 1;

    uint32_t file_idx    = 0;
    char file_name[200];

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    // Initialise the envelope
    ArEnvelope envelope(synthesiser, peak_amplitude, attack_duration, decay_duration);

    for (auto it = pitch.begin(); it != pitch.end(); it++)
    {
        // 1. Generate filename
        sprintf(file_name, "examples/ar_envelope_note/sounds/ar_envelope_note_%d.wav", file_idx);
        file_idx++;

        // 2. Generate the samples 
        Oscillator osc(synthesiser, volume, initial_phase, *it);
        vector<int16_t> samples_out = osc(duration);
        envelope.ApplyEnvelope(samples_out);

        // 3. Save the samples to the file 
        WaveFileOut wf_out(duration);
        wf_out.SaveBufferToFile(file_name, samples_out);
    }

	return 0;
}
