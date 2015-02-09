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
#include <common/segment.h>

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
    // None

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
    explicit ArEnvelope(
            SynthConfig& synthesiser,
            int32_t peak_amplitude_arg,
            uint32_t attack_duration_arg,
            uint32_t decay_duration_arg
            );
    virtual ~ArEnvelope() = default;

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    vector<float> GenerateAttack() const;
    vector<float> GenerateDecay() const;

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
    size_t attack_number_of_samples_;
    size_t decay_number_of_samples_;
    LinearSegment decay_segment_;
    LinearSegment attack_segment_;
    
};


#endif /* #define _ENVELOPE_H_ */
