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

#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <common/zz_global_include.h>
#include <envelope/segment.h>

//========================================================================
// CLASS: Envelope
//
// DESCRIPTION:
//      Base class. Pure abstract class.
//========================================================================
class Envelope 
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    explicit Envelope();
    virtual ~Envelope();
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
//      AR envelope (Aattack/Release). It also contains a sustain segment
//      in between the attack and release segments, and which is
//      automatically set to 100%. In other words, this envelope doesn't
//      modify what's outside the attack and release segments.
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

//========================================================================
// CLASS: AdsrEnvelope
//
// DESCRIPTION:
//      ADSR (Attack/Decay/Sustain/Release) envelope. Every segment 
//      within this envelope can be of any available type (i.e. constant,
//      linear or exponential). Note that for this type of envelopes
//      there are no gaps between segments and hence it can't be applied
//      to signals the length of which isn't equal to the sum of lengths
//      of the segments. 
//========================================================================
class AdsrEnvelope : public Envelope
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      AdsrEnvelope()
    //  
    //  DESCRIPTION:
    //      Constructor. Note that all of the member segments have to
    //      constructed before calling this constructor.
    //  INPUT:
    //      synthesiser          -A reference to the current synthesiser
    //      attack_segment_arg   -Pointer to the attack segment
    //      decay_segment_arg    -Pointer to the decay segment
    //      sustatin_segment_arg -Pointer to the sustain segment
    //      release_segment_arg  -Pointer to the release segment
    //--------------------------------------------------------------------
    explicit AdsrEnvelope(
            std::unique_ptr<Segment> attack_segment_arg,
            std::unique_ptr<Segment> decay_segment_arg,
            std::unique_ptr<Segment> sustain_segment_arg,
            std::unique_ptr<Segment> release_segment_arg
            );
    virtual ~AdsrEnvelope() = default;

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
    std::unique_ptr<Segment> attack_segment_;
    std::unique_ptr<Segment> decay_segment_;
    std::unique_ptr<Segment> sustain_segment_;
    std::unique_ptr<Segment> release_segment_;
    std::size_t length_;
    
};


#endif /* #define _ENVELOPE_H_ */
