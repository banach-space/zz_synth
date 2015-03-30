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
// PRIVATE FUNCTIONS DECLARATIONS
//========================================================================
static void GenWaveformAssertions(
            int16_t peak_amplitude,
            double initial_phase,
            double phase_increment
);

//========================================================================
// PRIVATE FUNCTIONS DEFINITIONS
//========================================================================
static void GenWaveformAssertions(
            int16_t peak_amplitude,
            double initial_phase,
            double phase_increment
)
{
    assert((initial_phase >= 0) && (initial_phase <= kTwoPi));
    assert((phase_increment >= -kPi) && (phase_increment <= kPi));
    assert((peak_amplitude >= 0) && (peak_amplitude <= 0x7fff));

}

//========================================================================
// CLASS: Oscillator
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
Oscillator::Oscillator(
        const SynthConfig& synthesiser,
        int16_t peak_amplitude_arg, 
        double initial_phase_arg,
        size_t pitch_id_arg):
    peak_amplitude_(peak_amplitude_arg),
    frequency_(synthesiser.frequency_table(pitch_id_arg)),
    initial_phase_(initial_phase_arg),
    sampling_rate_(synthesiser.sampling_rate())
{
    /* Verify the correctness of input */
    assert((peak_amplitude_arg >= 0) && (peak_amplitude_arg <= 0x7fff));
    assert((initial_phase_arg >= 0) && (initial_phase_arg <= kTwoPi));
    assert((pitch_id_arg >= 0) && (pitch_id_arg <= kNumberOfFrequencies));

    /* Calculate phase increment. Make sure it falls into the [0, kPi) range. */
    phase_increment_ = synthesiser.phase_increment_per_sample() * frequency_;
    phase_increment_ = fmod(phase_increment_, kPi);

}

Oscillator::~Oscillator() = default;

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
vector<int16_t> Oscillator::operator()(uint32_t number_of_seconds)
{
    size_t number_of_samples = (sampling_rate_ * number_of_seconds);

    return GenWaveform(
            number_of_samples, 
            peak_amplitude_, 
            initial_phase_, 
            phase_increment_);
}

//========================================================================
// CLASS: SineWaveForm
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
SineWaveform::SineWaveform(
        const SynthConfig& synthesiser,
        int16_t peak_amplitude, 
        double initial_phase ,
        std::size_t pitch_id):
    Oscillator(synthesiser, peak_amplitude, initial_phase, pitch_id)
{
}

//--------------------------------------------------------------------
// 2. INTERFACE DEFINITION 
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//  NAME:
//      SineWaveform::GenWaveform
//  
//  DESCRIPTION:
//      Function that implements the waveform generation and which is
//      used by Oscillator::operator(). 
//  INPUT:
//      number_of_samples   - number of samples in the waveform
//                            (TODO!!! min and max value)
//      peak_amplitude      - peak amplitude of the waveform
//                            (range: [0, 2^15-1]). 
//      initial_phase       - initial phase of the waveform
//                            (range: [0, kTwoPi))
//      phase_increment     - phase increment per sample, i.e.
//                            kTwoPi/sampling_rate * frequency
//                            (range: [-kPi, kPi))
//  RETURN:
//      Vector of samples for the requested waveform
//--------------------------------------------------------------------
std::vector<int16_t> SineWaveform::GenWaveform(
            size_t number_of_samples,
            int16_t peak_amplitude,
            double initial_phase,
            double phase_increment
            ) const 
{
    // Assertions before it makes sense to proceeds
    GenWaveformAssertions(peak_amplitude, initial_phase, phase_increment);
    
    double phase = initial_phase;

    vector<int16_t> samples(number_of_samples);

    for (auto& it : samples)
    {
        it = static_cast<int16_t>(peak_amplitude * sin(phase));

        if ((phase += phase_increment) >= kTwoPi)
            phase -= kTwoPi;
    }

    return samples;
}

//========================================================================
// CLASS: SawtoothWaveForm
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
SawtoothWaveform::SawtoothWaveform(
        const SynthConfig& synthesiser,
        int16_t peak_amplitude, 
        double initial_phase ,
        std::size_t pitch_id):
    Oscillator(synthesiser, peak_amplitude, initial_phase, pitch_id)
{
}

//--------------------------------------------------------------------
// 2. INTERFACE DEFINITION 
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//  NAME:
//      SawtoothWaveform::GenWaveform
//  
//  DESCRIPTION:
//      Function that implements the waveform generation and which is
//      used by Oscillator::operator(). 
//  INPUT:
//      number_of_samples   - number of samples in the waveform
//                            (TODO!!! min and max value)
//      peak_amplitude      - peak amplitude of the waveform
//                            (range: [0, 2^15-1]). 
//      initial_phase       - initial phase of the waveform
//                            (range: [0, kTwoPi))
//      phase_increment     - phase increment per sample, i.e.
//                            kTwoPi/sampling_rate * frequency
//                            (range: [-kPi, kPi))
//  RETURN:
//      Vector of samples for the requested waveform
//--------------------------------------------------------------------
std::vector<int16_t> SawtoothWaveform::GenWaveform(
            size_t number_of_samples,
            int16_t peak_amplitude,
            double initial_phase,
            double phase_increment
            ) const 
{
    // Assertions before it makes sense to proceeds
    GenWaveformAssertions(peak_amplitude, initial_phase, phase_increment);
    
    // saw_tooth_value is a floating point in the [-1, 1] range. 
    // (For consistency with sin()).
    double saw_tooth_value = initial_phase / kTwoPi;
    // saw_tooth_increment is a floating point in the [-1, 1] range.
    double saw_tooth_increment = phase_increment / kPi;

    vector<int16_t> samples(number_of_samples);

    for (auto& it : samples)
    {
        it = static_cast<int16_t>(peak_amplitude * saw_tooth_value);

        if ((saw_tooth_value += saw_tooth_increment) >= 1)
            saw_tooth_value -= 2;
    }

    return samples;
}

//========================================================================
// CLASS: SquareWaveForm
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
SquareWaveform::SquareWaveform(
        const SynthConfig& synthesiser,
        int16_t peak_amplitude, 
        double initial_phase ,
        std::size_t pitch_id):
    Oscillator(synthesiser, peak_amplitude, initial_phase, pitch_id)
{
}

//--------------------------------------------------------------------
// 2. INTERFACE DEFINITION 
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//  NAME:
//      SquareWaveform::GenWaveform
//  
//  DESCRIPTION:
//      Function that implements the waveform generation and which is
//      used by Oscillator::operator(). 
//  INPUT:
//      number_of_samples   - number of samples in the waveform
//                            (TODO!!! min and max value)
//      peak_amplitude      - peak amplitude of the waveform
//                            (range: [0, 2^15-1]). 
//      initial_phase       - initial phase of the waveform
//                            (range: [0, kTwoPi))
//      phase_increment     - phase increment per sample, i.e.
//                            kTwoPi/sampling_rate * frequency
//                            (range: [-kPi, kPi))
//  RETURN:
//      Vector of samples for the requested waveform
//--------------------------------------------------------------------
std::vector<int16_t> SquareWaveform::GenWaveform(
            size_t number_of_samples,
            int16_t peak_amplitude,
            double initial_phase,
            double phase_increment
            ) const 
{
    // Assertions before it makes sense to proceeds
    GenWaveformAssertions(peak_amplitude, initial_phase, phase_increment);
    
    double phase = initial_phase;
    double value = 0;

    vector<int16_t> samples(number_of_samples);

    for (auto& it : samples)
    {
        value = phase > kPi ? 1.0 : -1.0;
        it = static_cast<int16_t>(peak_amplitude * value);

        if ((phase += phase_increment) >= kTwoPi)
            phase -= kTwoPi;
    }

    return samples;
}

//========================================================================
// CLASS: TriangleWaveForm
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
TriangleWaveform::TriangleWaveform(
        const SynthConfig& synthesiser,
        int16_t peak_amplitude, 
        double initial_phase ,
        std::size_t pitch_id):
    Oscillator(synthesiser, peak_amplitude, initial_phase, pitch_id)
{
}

//--------------------------------------------------------------------
// 2. INTERFACE DEFINITION 
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//  NAME:
//      TriangleWaveform::GenWaveform
//  
//  DESCRIPTION:
//      Function that implements the waveform generation and which is
//      used by Oscillator::operator(). 
//  INPUT:
//      number_of_samples   - number of samples in the waveform
//                            (TODO!!! min and max value)
//      peak_amplitude      - peak amplitude of the waveform
//                            (range: [0, 2^15-1]). 
//      initial_phase       - initial phase of the waveform
//                            (range: [0, kTwoPi))
//      phase_increment     - phase increment per sample, i.e.
//                            kTwoPi/sampling_rate * frequency
//                            (range: [-kPi, kPi))
//  RETURN:
//      Vector of samples for the requested waveform
//--------------------------------------------------------------------
std::vector<int16_t> TriangleWaveform::GenWaveform(
            size_t number_of_samples,
            int16_t peak_amplitude,
            double initial_phase,
            double phase_increment
            ) const 
{
    // Assertions before it makes sense to proceeds
    GenWaveformAssertions(peak_amplitude, initial_phase, phase_increment);
    
    const double one_div_pi = 1.0/ kPi;
    double triangle_wave_value;
    double phase = initial_phase;

    vector<int16_t> samples(number_of_samples);

    for (auto& it : samples)
    {
        triangle_wave_value = 1.0 - one_div_pi * fabs(phase - kTwoPi);
        it = static_cast<int16_t>(peak_amplitude * triangle_wave_value);

        phase = phase + phase_increment;

        if ((phase >= kTwoPi) || (phase <= 0))
        {
            phase = phase - phase_increment;
            phase_increment = -phase_increment;
        }

    }

    return samples;
}

//========================================================================
// End of file
//========================================================================
