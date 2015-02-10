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
        float peak_amplitude_arg,
        double attack_duration_arg,
        double decay_duration_arg
        ) :
    Envelope(),
    decay_segment_(
            peak_amplitude_arg, 
            static_cast<size_t>(synthesiser.sampling_rate() * decay_duration_arg + 0.5),
            kDecline),
    attack_segment_(
            peak_amplitude_arg, 
            static_cast<size_t>(synthesiser.sampling_rate() * attack_duration_arg + 0.5),
            kIncline)
{
}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
void ArEnvelope::ApplyEnvelope(std::vector<int16_t> &samples) const
{
    // 1. Attack
    vector<float>::const_iterator it = attack_segment_.segment_.begin();
    vector<float>::const_iterator it_end = attack_segment_.segment_.end();

    for ( it; it != it_end; it++)
    {
       // TODO 
    }

    // 2. Decay
    it = decay_segment_.segment_.begin();
    it_end = decay_segment_.segment_.end();

    for ( it; it != it_end; it++)
    {
       // TODO 
    }
}

//------------------------------------------------------------------------
// 3. ACCESSORS
//------------------------------------------------------------------------
// None

//------------------------------------------------------------------------
// 4. MUTATORS
//------------------------------------------------------------------------
// None
