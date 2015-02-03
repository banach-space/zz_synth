//========================================================================
// FILE:
//      src/common/envelope.cc
//
// AUTHOR:
//      zimzum@github 
//
// DESCRIPTION:
//      Classes for envelope generation
//
//  License: GNU GPL v2.0 
//========================================================================

#include <common/envelope.h>

//========================================================================
// CLASS: Segment
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
Segment::Segment(float peak_amplitude_arg, size_t number_of_steps_arg) :
    peak_amplitude_(peak_amplitude_arg),
    number_of_steps_(number_of_steps_arg),
    init_(false)
{}

Segment::~Segment() {};

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
bool Segment::Init(size_t number_of_samples)
{

}
const vector<float> Segment::GetSegment()
{
    if (!init_)
    {
        segment_ = GenerateSegment(number_of_steps_, peak_amplitude_);
        init_ = true;
    }

    return segment_; 
}

//========================================================================
// CLASS: LinearSegment
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
LinearSegment::LinearSegment(
        float peak_amplitude_arg, 
        size_t number_of_steps_arg) :
    Segment(peak_amplitude_arg, number_of_steps_arg)
{}

LinearSegment::~LinearSegment() 
{}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
const vector<float> LinearSegment::GenerateSegment(
        size_t number_of_samples,
        float peak_amplitude)
{
    vector<float> amplitudes;
    amplitudes.reserve(number_of_samples);
    float volume = 0;
    float increment = peak_amplitude / number_of_samples;
    vector<float>::iterator it;

    for (it = amplitudes.begin();
            it != amplitudes.end();
            it++)
    {
        *it = volume;
        volume += increment;
    }

    // Due to rounding error the last entry might be different from 
    // peak_amplitude. Force it to be equal.
    *it = peak_amplitude;

    return amplitudes;

}

//========================================================================
// CLASS: Envelope
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
Envelope::Envelope()
{
}

Envelope::~Envelope() {}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// 3. ACCESSORS
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// 4. MUTATORS
//------------------------------------------------------------------------
// None


//========================================================================
// CLASS: ArEnvelope
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
ArEnvelope::ArEnvelope(
        SynthConfig& synthesiser,
        int32_t peak_amplitude_arg,
        uint32_t attack_duration_arg,
        uint32_t decay_duration_arg
        ) : 
    Envelope(),
    decay_segment_(peak_amplitude_arg, 0),
    attack_segment_(peak_amplitude_arg, 0)
{
    size_t decay_number_of_samples = decay_duration_arg 
        * synthesiser.sampling_rate();
    size_t attack_number_of_samples = attack_duration_arg 
        * synthesiser.sampling_rate();
    
    decay_segment_.Init(decay_number_of_samples);
    attack_segment_.Init(attack_number_of_samples);
}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// 3. ACCESSORS
//------------------------------------------------------------------------
// None

//------------------------------------------------------------------------
// 4. MUTATORS
//------------------------------------------------------------------------
// None

