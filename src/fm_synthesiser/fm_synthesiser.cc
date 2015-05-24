//========================================================================
// FILE:
//      src/fm_synthesiser/fm_synthesiser.cc 
//
// AUTHOR:
//      zimzum@github 
//
// DESCRIPTION:
//      TODO!!!
//
//  License: GNU GPL v2.0 
//========================================================================

#include <fm_synthesiser/fm_synthesiser.h>
#include <oscillator/oscillator.h>
#include <common/synth_config.h>

using namespace std;

//========================================================================
// CLASS: FmSynthesiser
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
FmSynthesiser::FmSynthesiser(
        const SynthConfig& synthesiser,
        int16_t peak_amplitude_arg, 
        double initial_phase_arg,
        std::size_t pitch_id_carrier_arg,
        std::size_t pitch_id_modulator_arg):
    synthesiser_(synthesiser),
    peak_amplitude_(peak_amplitude_arg),
    frequency_carrier_(synthesiser.frequency_table(pitch_id_carrier_arg)),
    frequency_modulator_(synthesiser.frequency_table(pitch_id_modulator_arg)),
    initial_phase_(initial_phase_arg)
{

}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
vector<int16_t> FmSynthesiser::operator()(uint32_t number_of_seconds) const
{
    size_t number_of_samples         = (synthesiser_.sampling_rate() * number_of_seconds);
    double phase_modulator           = 0.0;
    double modulator_current_value   = 0.0;
    vector<int16_t> samples_output(number_of_samples);
    vector<int16_t> samples_modulator(number_of_samples);

    // Use Oscillator to get the modulating signal
    SynthConfig &synthesiser = SynthConfig::getInstance();
    SineWaveform osc(synthesiser, 50, initial_phase_, frequency_modulator_);
    samples_modulator = osc(number_of_seconds);

    for (auto it = samples_output.begin(), it2 = samples_modulator.begin(); it != samples_output.end(); it++)
    {
        //modulator_current_value = frequency_deviation_ * sin(phase_modulator);
        //it = static_cast<int16_t>(
                //phase_increment_per_sample_at_sampling_rate_
                //* (modulator_current_value + frequency_carrier_)
                //+ initial_phase_);

        //phase_modulator += phase_increment_modulator;
        //if (phase_modulator >= kTwoPi)
        //{
            //phase_modulator -= kTwoPi;
        //}
    }

    return samples_output;
}

//------------------------------------------------------------------------
// 3. ACCESSORS
//------------------------------------------------------------------------
// None

//------------------------------------------------------------------------
// 4. MUTATORS
//------------------------------------------------------------------------
// None
