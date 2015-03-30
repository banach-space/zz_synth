//========================================================================
// FILE:
//   examples/plain_note/waveforms.cc
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
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
#include <oscillator/oscillator.h>

using namespace std;

//========================================================================
// MAIN 
//========================================================================
int main()
{
    // Param 1: Pitch
    vector<size_t> pitch = {45};
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
        sprintf(file_name, "examples/waveforms/sounds/sine_wave_%d.wav", file_idx);

        // 2. Generate the samples 
        SineWaveform osc_sine(synthesiser, volume, initial_phase, *it);
        vector<int16_t> samples_out_sine = osc_sine(duration);

        // 3. Save the samples to the file 
        WaveFileOut wf_out_sine(duration);
        wf_out_sine.SaveBufferToFile(file_name, samples_out_sine);

        //----------------------------------------------------------------
        // Sawtooth
        //----------------------------------------------------------------
        // 1. Generate filename
        sprintf(file_name, "examples/waveforms/sounds/saw_tooth_%d.wav", file_idx);

        // 2. Generate the samples 
        SawtoothWaveform osc_sawtooth(synthesiser, volume, initial_phase, *it);
        vector<int16_t> samples_out_sawtooth = osc_sawtooth(duration);

        // 3. Save the samples to the file 
        WaveFileOut wf_out_sawtooth(duration);
        wf_out_sawtooth.SaveBufferToFile(file_name, samples_out_sawtooth);

        //----------------------------------------------------------------
        // Square wave
        //----------------------------------------------------------------
        // 1. Generate filename
        sprintf(file_name, "examples/waveforms/sounds/square_%d.wav", file_idx);

        // 2. Generate the samples 
        SquareWaveform osc_square(synthesiser, volume, initial_phase, *it);
        vector<int16_t> samples_out_square = osc_square(duration);

        // 3. Save the samples to the file 
        WaveFileOut wf_out_square(duration);
        wf_out_square.SaveBufferToFile(file_name, samples_out_square);

        //----------------------------------------------------------------
        // Triangle wave
        //----------------------------------------------------------------
        // 1. Generate filename
        sprintf(file_name, "examples/waveforms/sounds/triangle_%d.wav", file_idx);

        // 2. Generate the samples 
        TriangleWaveform osc_triangle(synthesiser, volume, initial_phase, *it);
        vector<int16_t> samples_out_triangle = osc_triangle(duration);

        // 3. Save the samples to the file 
        WaveFileOut wf_out_triangle(duration);
        wf_out_triangle.SaveBufferToFile(file_name, samples_out_triangle);
    }

	return 0;
}
