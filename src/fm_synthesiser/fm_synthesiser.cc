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
        std::size_t pitch_id_modulator_arg,
        double frequency_deviation):
    peak_amplitude_(peak_amplitude_arg),
    frequency_carrier_(synthesiser.frequency_table(pitch_id_carrier_arg)),
    frequency_modulator_(synthesiser.frequency_table(pitch_id_modulator_arg)),
    initial_phase_(initial_phase_arg),
    sampling_rate_(synthesiser.sampling_rate()),
    frequency_deviation_(frequency_deviation),
    phase_increment_per_sample_at_sampling_rate_(synthesiser.phase_increment_per_sample())
{

}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
vector<int16_t> FmSynthesiser::operator()(uint32_t number_of_seconds)
{
    size_t number_of_samples         = (sampling_rate_ * number_of_seconds);
    double phase_modulator           = 0.0;
    double modulator_current_value   = 0.0;
    double phase_increment_modulator = sampling_rate_ * frequency_modulator_
        * phase_increment_per_sample_at_sampling_rate_;

    vector<int16_t> samples(number_of_samples);

    for (auto& it : samples)
    {
        modulator_current_value = frequency_deviation_ * sin(phase_modulator);
        it = static_cast<int16_t>(
                phase_increment_per_sample_at_sampling_rate_
                * (modulator_current_value + frequency_carrier_)
                + initial_phase_);

        phase_modulator += phase_increment_modulator;
        if (phase_modulator >= kTwoPi)
        {
            phase_modulator -= kTwoPi;
        }
    }

    return samples;
}

//------------------------------------------------------------------------
// 3. ACCESSORS
//------------------------------------------------------------------------
// None

//------------------------------------------------------------------------
// 4. MUTATORS
//------------------------------------------------------------------------
// None
