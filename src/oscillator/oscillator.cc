//========================================================================
// FILE:
//      src/oscillator/oscillator.cc
//
// AUTHOR:
//      zimzum@github 
//
// DESCRIPTION:
//		Implements classes representing basic waveforms.
//
//  License: GNU GPL v2.0 
//========================================================================

#include <oscillator/oscillator.h>

using namespace std;

//========================================================================
// CLASS: ClassName
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
Oscillator::Oscillator(
        const SynthConfig& synthesiser,
        int16_t peak_amplitude, 
        double initial_phase,
        size_t pitch_id):
    peak_amplitude_(peak_amplitude),
    frequency_(synthesiser.frequency_table(pitch_id)),
    initial_phase_(initial_phase),
    sampling_rate_(synthesiser.sampling_rate())
{
    phase_increment_ = synthesiser.phase_increment_per_sample() * frequency_;

}

Oscillator::~Oscillator() = default;

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
vector<int16_t> Oscillator::operator()(uint32_t number_of_seconds)
{
    double phase = initial_phase_;
    size_t number_of_samples 
        = (sampling_rate_ * number_of_seconds);

    vector<int16_t> samples(number_of_samples);

    for (vector<int16_t>::iterator it = samples.begin(); 
            it != samples.end(); 
            it++)
    {
        *it = static_cast<int16_t>(peak_amplitude_ * sin(phase));

        if ((phase += phase_increment_) >= kTwoPi)
            phase -= kTwoPi;
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
