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
// CLASS: Envelope
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
Envelope::Envelope(
        SynthConfig& synthesiser,
        int32_t volume_arg, 
        int32_t peak_amplitude_arg,
        uint32_t attack_duration_arg,
        uint32_t decay_duration_arg,
        uint32_t decay_start_arg
        ) :
    volume_(volume_arg),
    peak_amplitude_(peak_amplitude_arg),
    attack_duration_(attack_duration_arg),
    decay_duration_(decay_duration_arg),
    decay_start_(decay_start_arg),
    attack_number_of_samples_(0),
    decay_number_of_samples_(0)
{

    attack_number_of_samples_ = attack_duration_ * synthesiser.sampling_rate();
    decay_number_of_samples_ = decay_duration_ * synthesiser.sampling_rate();
}

Envelope::~Envelope() {}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
// None

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
// CLASS: LinearEnvelope
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
LinearEnvelope::LinearEnvelope(
        SynthConfig& synthesiser,
        int32_t volume_arg, 
        int32_t peak_amplitude_arg,
        uint32_t attack_duration_arg,
        uint32_t decay_duration_arg,
        uint32_t decay_start_arg
        ) : 
    Envelope(
            synthesiser,
            volume_arg, 
            peak_amplitude_arg, 
            attack_duration_arg,
            decay_duration_arg,
            decay_start_arg)
{
    attack_increment_ = peak_amplitude() / attack_number_of_samples();
    decay_decrement_ = peak_amplitude() / decay_number_of_samples();
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
