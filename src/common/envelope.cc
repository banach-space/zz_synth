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
Envelope::Envelope(
        SynthConfig& synthesiser,
        int32_t peak_amplitude_arg,
        uint32_t attack_duration_arg,
        uint32_t decay_duration_arg
        ) :
    peak_amplitude_(peak_amplitude_arg),
    attack_duration_(attack_duration_arg),
    decay_duration_(decay_duration_arg),
    attack_number_of_samples_(0),
    decay_number_of_samples_(0),
    attack_(0),
    decay_(0)
{

    attack_number_of_samples_ = attack_duration_ * synthesiser.sampling_rate();
    decay_number_of_samples_ = decay_duration_ * synthesiser.sampling_rate();
}

Envelope::~Envelope() {}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
vector<float> Envelope::GenerateAttack() const {};
vector<float> Envelope::GenerateDecay() const {};

//------------------------------------------------------------------------
// 3. ACCESSORS
//------------------------------------------------------------------------
float Envelope::peak_amplitude() const {return peak_amplitude_;}
size_t Envelope::attack_number_of_samples() const{return attack_number_of_samples_;}
size_t Envelope::decay_number_of_samples() const{return decay_number_of_samples_;}

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
        * synthesiser.sampling.rate();
    size_t attack_number_of_samples = attack_duration_arg 
        * synthesiser.sampling.rate();
    
    decay_segment_.Init(decay_number_of_samples);
    attack_segment_.Init(attack_number_of_samples);
}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
vector<float> LinearEnvelope::GenerateAttack() const
{
    vector<float> amplitudes;
    amplitudes.reserve(attack_number_of_samples());
    float volume = 0;
    vector<float>::iterator it;

    for (it = amplitudes.begin();
            it != amplitudes.end();
            it++)
    {
        *it = volume;
        volume += attack_increment_;
    }

    // Due to rounding error the last entry might be different from 
    // peak_amplitude_. Force it to be equal.
    *it = peak_amplitude();

    return amplitudes;
}

vector<float> LinearEnvelope::GenerateDecay() const
{
    vector<float> amplitudes;
    amplitudes.reserve(decay_number_of_samples());
    float volume = peak_amplitude();
    vector<float>::iterator it;

    for (it = amplitudes.begin();
            it != amplitudes.end();
            it++)
    {
        *it = volume;
        volume += decay_decrement_;
    }

    // Due to rounding error the last entry might be different from 
    // peak_amplitude_. Force it to be equal.
    *it = 0;

    return amplitudes;

}

//------------------------------------------------------------------------
// 3. ACCESSORS
//------------------------------------------------------------------------
// None

//------------------------------------------------------------------------
// 4. MUTATORS
//------------------------------------------------------------------------
// None

