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
    sampling_rate_(synthesiser.sampling_rate())
{

}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
vector<int16_t> FmSynthesiser::operator()(uint32_t number_of_seconds)
{
    size_t number_of_samples = (sampling_rate_ * number_of_seconds);

    return GenWaveform(
            number_of_samples, 
            peak_amplitude_, 
            initial_phase_, 
            frequency_carrier_,
            frequency_modulator_);
}

//------------------------------------------------------------------------
// 2. INTERFACE DEFINITION: private
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//  NAME:
//      FmSynthesiser::GenWaveform
//  
//  DESCRIPTION:
//      Function that synthesises a frequency mdoulated waveform and which
//      is used by FmSynthesiser::operator(). 
//  INPUT:
//      number_of_samples   - number of samples in the waveform
//                            (TODO!!! min and max value)
//      peak_amplitude      - peak amplitude of the waveform
//                            (range: [0, 2^15-1]). 
//      initial_phase       - initial phase of the waveform
//                            (range: [0, kTwoPi))
//      frequency_carrier   -
//      frequency_modulator -
//  RETURN:
//      Vector of samples for the requested waveform
//------------------------------------------------------------------------
std::vector<int16_t> FmSynthesiser::GenWaveform(
            size_t number_of_samples,
            int16_t peak_amplitude,
            double initial_phase,
            double frequency_carrier,
            double frequency_modulator 
            ) const
{
    
    double phase = initial_phase;

    vector<int16_t> samples(number_of_samples);

    for (auto& it : samples)
    {
        //it = static_cast<int16_t>(peak_amplitude * sin(phase));

        //if ((phase += phase_increment) >= kTwoPi)
        //phase -= kTwoPi;
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
