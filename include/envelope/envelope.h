//========================================================================
//  FILE:
//      include/common/envelope.h 
//
//  AUTHOR:
//      zimzum@github 
//
//  DESCRIPTION:
//      Classes for enevelope generation. 
//
//  License: GNU GPL v2.0 
//========================================================================

#ifndef _ENVELOPE_H_
#define _ENVELOPE_H_

#include <common/zz_global_include.h>
#include <envelope/segment.h>

//========================================================================
// CLASS: Envelope
//
// DESCRIPTION:
//      Base class.
//========================================================================
class Envelope 
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    explicit Envelope();
    virtual ~Envelope() = 0;
    explicit Envelope(const Envelope& rhs) = delete;
    explicit Envelope(Envelope&& rhs) = delete;
    Envelope& operator=(const Envelope &rhs) = delete;
    Envelope& operator=(Envelope&& rhs) = delete;

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      ApplyEnvelope()
    //  
    //  DESCRIPTION:
    //      Apply the envelope represented by this object to the signal
    //      passed as input.
    //  INPUT:
    //      Vector of samples on which the envelope will be applied.
    //      This input vector has to be longer or equal to the sum
    //      of lengths of segments correspoding to this envelope and
    //      has to be non-empty.
    //  OUTPUT:
    //      None
    //--------------------------------------------------------------------
    virtual void ApplyEnvelope(std::vector<int16_t> &samples) const = 0;

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    // None

protected:
    //--------------------------------------------------------------------
    // 4. MUTATORS
    //--------------------------------------------------------------------
    // None

private:
    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
    //
    
};

//========================================================================
// CLASS: ArEnvelope
//
// DESCRIPTION:
//      AR envelope (attack/sustain/release) with the sustain level set
//      automatically to 100%.
//========================================================================
class ArEnvelope : public Envelope
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      ArEnvelope()
    //  
    //  DESCRIPTION:
    //      Constructor
    //  INPUT:
    //      synthesiser         - A reference to the current synthesiser
    //      peak_amplitude_arg  - The peak amplitude value (the level value
    //                            during the 'sustain' stage) 
    //      attack_duration_arg - Duration of the attack in seconds. Has 
    //                            to be non-negative.
    //      decay_duration_arg  - Duration of the decay in seconds. Has 
    //                            to be non-negative.
    //--------------------------------------------------------------------
    explicit ArEnvelope(
            SynthConfig& synthesiser,
            float peak_amplitude_arg,
            double attack_duration_arg,
            double decay_duration_arg
            );
    virtual ~ArEnvelope() = default;

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    void ApplyEnvelope(std::vector<int16_t> &samples) const;

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    // None

protected:
    //--------------------------------------------------------------------
    // 4. MUTATORS
    //--------------------------------------------------------------------
    // None

private:
    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
    std::size_t attack_number_of_samples_;
    std::size_t decay_number_of_samples_;
    LinearSegment decay_segment_;
    LinearSegment attack_segment_;
    
};


#endif /* #define _ENVELOPE_H_ */