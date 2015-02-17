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
    attack_number_of_samples_(
            static_cast<size_t>(synthesiser.sampling_rate() * attack_duration_arg)),
    decay_number_of_samples_(
            static_cast<size_t>(synthesiser.sampling_rate() * decay_duration_arg)),
    decay_segment_(
            peak_amplitude_arg, 
            decay_number_of_samples_,
            kDecline),
    attack_segment_(
            peak_amplitude_arg, 
            attack_number_of_samples_,
            kIncline)
{
}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
void ArEnvelope::ApplyEnvelope(std::vector<int16_t> &samples) const
{
    assert(samples.size() >= (attack_number_of_samples_ + decay_number_of_samples_));
    assert(!samples.empty());

    // 1. Apply attack
    vector<float>::const_iterator it_seg = attack_segment_.segment_.begin();
    vector<float>::const_iterator it_seg_end = attack_segment_.segment_.end();
    vector<int16_t>::iterator it_data = samples.begin();
    vector<int16_t>::const_iterator it_data_end = samples.begin() 
        + static_cast<vector<int16_t>::difference_type>(attack_number_of_samples_);

    for ( ; it_seg != it_seg_end && it_data != it_data_end; it_seg++, it_data++)
    {

       *it_data = (*it_seg * *it_data); 
    }

    // 2. Apply decay
    it_seg = decay_segment_.segment_.begin();
    it_seg_end = decay_segment_.segment_.end();
    it_data = samples.end()
        - static_cast<vector<int16_t>::difference_type>(decay_number_of_samples_);
    it_data_end = samples.end();


    for ( ; it_seg != it_seg_end && it_data != it_data_end; it_seg++, it_data++)
    {
       *it_data = (*it_seg * *it_data); 
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
