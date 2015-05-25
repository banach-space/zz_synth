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
    size_t pitch_carrier = 64;
    vector<size_t> pitch_modulator = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
    vector<double> index_of_modulation = {1 << 3, 1 << 5, 1 << 8};
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

    for (auto it : pitch_modulator)
    {
        for (auto it2 : index_of_modulation)
        {
            //----------------------------------------------------------------
            // Sine-wave
            //----------------------------------------------------------------
            // 1. Generate filename
            sprintf(
                    file_name, 
                    "examples/fm_waveforms/sounds/fm_wave_pitch_id_%lu_iom_%lu.wav", 
                    it, 
                    static_cast<size_t>(it2));

            // 2. Generate the samples 
            FmSynthesiser fm_synthesiser(
                    synthesiser, 
                    volume, 
                    initial_phase, 
                    pitch_carrier, 
                    it, 
                    it2);
            vector<int16_t> samples_output = fm_synthesiser(duration);

            // 3. Save the samples to the file 
            WaveFileOut wf_out_sine(duration);
            wf_out_sine.SaveBufferToFile(file_name, samples_output);
        }
    }

	return 0;
}
