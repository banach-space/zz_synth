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
// CLASS: Segment
//
// DESCRIPTION:
//      A segment in an envelope. Abstract base class.
//========================================================================
class Segment
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    explicit Segment(float peak_amplitude_arg, size_t number_of_steps_arg);
    virtual ~Segment() = 0;
    explicit Segment(const Segment& rhs) = delete;
    explicit Segment(Segment&& rhs) = delete;
    Segment& operator=(const Segment &rhs) = delete;
    Segment& operator=(Segment&& rhs) = delete;

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    const vector<float> GetSegment();
    bool Init(size_t number_of_steps_arg);

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    // None

private:
    //--------------------------------------------------------------------
    // 4. PRIVATE METHODS 
    //--------------------------------------------------------------------
    virtual const vector<float> GenerateSegment(
        size_t number_of_samples,
        float peak_amplitude) = 0;

    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
    size_t number_of_steps_;
    vector<float> segment_;
    float peak_amplitude_;
    // The init_ variable is set by default to 'false' and then changed to
    // 'true' once the segment_ vector is set. This is done by the Init()
    // function.
    bool init_;
};

//========================================================================
// CLASS: LinearSegment
//
// DESCRIPTION:
//      A linear segment in an envelope: y = a*x + b
//========================================================================
class LinearSegment : public Segment
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    explicit LinearSegment(float peak_amplitude_arg, size_t number_of_steps_arg);
    ~LinearSegment();

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    // None

private:
    //--------------------------------------------------------------------
    // 4. PRIVATE METHODS 
    //--------------------------------------------------------------------
    const vector<float> GenerateSegment(
        size_t number_of_samples,
        float peak_amplitude);

    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
    size_t number_of_steps_;
    vector<float> segment_;
    float peak_amplitude_;
};

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
