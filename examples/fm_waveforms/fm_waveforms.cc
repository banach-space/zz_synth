//========================================================================
// FILE:
//   examples/fm_waveforms/fm_waveforms.cc
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//  TODO!!!
//   This demonstrates how to generate different waveforms (sine wave,
//   saw-tooth, square wave and triangle wave)  and save them
//   to WAVE files using the zz-synthesiser. A number of files with plain
//   sounds (no envelope, etc.) are generated. There are four hard-coded
//   parameters that determine the sounds being produced. These are marked
//   with 'Param #:' and can be freely modified to experiment.
//
// License: GNU GPL v2.0 
//========================================================================

#include <global/global_variables.h>
#include <common/wave_file.h>
#include <common/synth_config.h>
#include <fm_synthesiser/fm_synthesiser.h>

using namespace std;

//========================================================================
// MAIN 
//========================================================================
int main()
{
    // Param 1: Pitch
    vector<size_t> pitch = {45};
    size_t pitch_modulator = {10};
    double frequency_deviation = 20; 
    // Param 2: Volume
    int16_t volume       = 1 << 14;
    // Param 3: Duration
    uint32_t duration    = 5;
    // Param 4: Initial phase
    double initial_phase = 0;

    uint32_t file_idx    = 0;
    char file_name[200];

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = pitch.begin(); it != pitch.end(); it++)
    {
        //----------------------------------------------------------------
        // Sine-wave
        //----------------------------------------------------------------
        // 1. Generate filename
        sprintf(file_name, "examples/fm_waveforms/sounds/fm_wave_%d.wav", file_idx);

        // 2. Generate the samples 
        SineWaveform osc_sine(synthesiser, volume, initial_phase, *it, pitch_id_modulator, frequency_deviation);
        vector<int16_t> samples_out_sine = osc_sine(duration);

        // 3. Save the samples to the file 
        WaveFileOut wf_out_sine(duration);
        wf_out_sine.SaveBufferToFile(file_name, samples_out_sine);
    }

	return 0;
}
