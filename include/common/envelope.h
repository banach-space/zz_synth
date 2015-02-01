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
    // Make this class pure abstract and block copy constructor, assignment
    // operator and the corresponding move operators.
    explicit Envelope(
            SynthConfig& synthesiser,
            int32_t peak_amplitude_arg,
            uint32_t attack_duration_arg,
            uint32_t decay_duration_arg
            );
    virtual ~Envelope() = 0;
    explicit Envelope(const Envelope& rhs) = delete;
    explicit Envelope(Envelope&& rhs) = delete;
    Envelope& operator=(const Envelope &rhs) = delete;
    Envelope& operator=(Envelope&& rhs) = delete;

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    virtual vector<float> GenerateAttack() const;
    virtual vector<float> GenerateDecay() const;

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    float peak_amplitude() const;
    size_t attack_number_of_samples() const;
    size_t decay_number_of_samples() const;

protected:
    //--------------------------------------------------------------------
    // 4. MUTATORS
    //--------------------------------------------------------------------
    // None

private:
    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
    int32_t peak_amplitude_;
    uint32_t attack_duration_;
    uint32_t decay_duration_;
    size_t attack_number_of_samples_; 
    size_t decay_number_of_samples_; 
    
};

//========================================================================
// CLASS: LinearEnvelope
//
// DESCRIPTION:
//      Linear envelope (linear attack and decay).
//========================================================================
class LinearEnvelope : public Envelope
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    // Make this class pure abstract and block copy constructor, assignment
    // operator and the corresponding move operators.
    explicit LinearEnvelope(
            SynthConfig& synthesiser,
            int32_t peak_amplitude_arg,
            uint32_t attack_duration_arg,
            uint32_t decay_duration_arg
            );
    virtual ~LinearEnvelope() = default;

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
    float attack_increment_;
    float decay_decrement_;
    
};

#endif /* #define _ENVELOPE_H_ */
