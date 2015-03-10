//========================================================================
// FILE:
//   examples/plain_note/plain_note.cc
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//   Generates WAVE files with plain sound (no envelope, etc.). There
//   are four hard-coded parameters that determine the sounds being
//   generated. These are marked with 'Param #:' and can be freely
//   modified.
//
// License: GNU GPL v2.0 
//========================================================================

#include <global/global_variables.h>
#include <common/wave_file.h>
#include <common/synth_config.h>
#include <common/oscillator.h>

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

    uint32_t file_idx    = 0;
    char file_name[200];

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = pitch.begin(); it != pitch.end(); it++)
    {
        // 1. Generate filename
        sprintf(file_name, "examples/plain_note/sounds/plain_note_%d.wav", file_idx);
        file_idx++;

        // 1. Generate the samples 
        Oscillator osc(synthesiser, volume, initial_phase, *it);
        vector<int16_t> samples_out = osc(duration);

        // 2. Save the generated samples to the file 
        WaveFileOut wf_out(duration);
        wf_out.SaveBufferToFile(file_name, samples_out);
    }

	return 0;
}
