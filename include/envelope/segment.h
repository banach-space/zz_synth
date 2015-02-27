//========================================================================
//  FILE:
//      include/common/segment.h 
//
//  AUTHOR:
//      zimzum@github 
//
//  DESCRIPTION:
//      Classes representing enevelop segments. 
//
//  License: GNU GPL v2.0 
//========================================================================

#ifndef SEGMENT_H
#define SEGMENT_H

#include <common/zz_global_include.h>


//========================================================================
// FORWARD DECLARATIONS 
//========================================================================
class ArEnvelope;
class AdsrEnvelope;

//========================================================================
// PRIVATE DATA TYPES
//========================================================================
//------------------------------------------------------------------------
//  NAME: 
//      SegmentGradient
//
//  DESCRIPTION:
//      Enum used for differentiating between two types of linear
//      segments:
//          - kIncline represents attack (positive gradient, i.e. 'a')
//          - kDecline represents decay (negative gradient, i.e. 'a')
//------------------------------------------------------------------------
enum class SegmentGradient
{
    kDecline,
    kIncline
};

//========================================================================
// CLASS: Segment
//
// DESCRIPTION:
//      A segment in an envelope - the most  basic building block. Abstract
//      base class tha defines the basic interface.
//========================================================================
class Segment
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    explicit Segment();
    virtual ~Segment() = 0;
    explicit Segment(const Segment& rhs) = delete;
    explicit Segment(Segment&& rhs) = delete;
    Segment& operator=(const Segment &rhs) = delete;
    Segment& operator=(Segment&& rhs) = delete;

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      GetSegment()
    //  
    //  DESCRIPTION:
    //      Returns a copy of the segment in form of vector of float.
    //      Note that derived classes are not forced to internally store
    //      their segments as vectors of floats and that this function
    //      only returns a copy.
    //  INPUT:
    //      None
    //  OUTPUT:
    //      The segment
    //--------------------------------------------------------------------
    virtual std::vector<float> GetSegment() = 0;

    //--------------------------------------------------------------------
    //  NAME:
    //      operator[] 
    //  
    //  DESCRIPTION:
    //      Return the n-th element in the segment.
    //  INPUT:
    //      Index of the segment element to be returned. 
    //  OUTPUT:
    //      The value of the segment at the specified position
    //--------------------------------------------------------------------
    virtual const float& operator[](const std::size_t position) const = 0;
    virtual float& operator[](const std::size_t position) = 0;

    //--------------------------------------------------------------------
    //  NAME:
    //      IsEmpty() 
    //  
    //  DESCRIPTION:
    //      Check whether the segment is empty
    //  INPUT:
    //      None
    //  OUTPUT:
    //      True if the segment is empty, false otherwise. 
    //--------------------------------------------------------------------
    virtual bool IsEmpty() const = 0;

    //--------------------------------------------------------------------
    //  NAME:
    //      Length() 
    //  
    //  DESCRIPTION:
    //      Returns the length of this Segment expressed in samples.
    //  INPUT:
    //      None
    //  OUTPUT:
    //      The length of this Segment expressed in samples.
    //--------------------------------------------------------------------
    virtual std::size_t Length() const = 0;

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    // None

private:
    //--------------------------------------------------------------------
    // 4. PRIVATE METHODS 
    //--------------------------------------------------------------------
    // None

    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
    // None
};

//========================================================================
// CLASS: ConstantSegment
//
// DESCRIPTION:
//      A constant segment in an envelope. Mathematically it is defined
//      by: y = a, where 'a' is the amplitude_. Due to its simplicity,
//      there's no need to pre-calculate and store the values of
//      this segment. This will improve memory footprint.
//========================================================================
class ConstantSegment : public Segment
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      ConstantSegment()
    //  
    //  DESCRIPTION:
    //      Constructor
    //  INPUT:
    //      amplitude_arg       - the value of the segment
    //      number_of_steps_arg - the total number of steps/samples in this
    //                            segment 
    //--------------------------------------------------------------------
    explicit ConstantSegment(
            float amplitude_arg, 
            size_t number_of_steps_arg);
    ~ConstantSegment();

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    // Virtual functions/operators
    //--------------------------------------------------------------------
    std::vector<float> GetSegment() override;
    const float& operator[](const std::size_t position) const override;
    float& operator[](const std::size_t position) override;
    bool IsEmpty() const override;
    std::size_t Length() const override;

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    std::size_t number_of_steps() const;

private:
    //--------------------------------------------------------------------
    // 4. PRIVATE METHODS 
    //--------------------------------------------------------------------
    // None

    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
    std::size_t number_of_steps_;
    float amplitude_;
    friend AdsrEnvelope;
    friend ArEnvelope;
};
//========================================================================
// CLASS: LinearSegment
//
// DESCRIPTION:
//      A linear segment in an envelope. Mathematically it is defined
//      by: y = a*x + b. The segment is guaranteed to be 0 at one end and
//      the specified peak amplitude at the other. 
//========================================================================
class LinearSegment : public Segment
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      LinearSegment()
    //  
    //  DESCRIPTION:
    //      Constructor
    //  INPUT:
    //      peak_amplitude_arg  - the peak amplitude value (guaranteed to be
    //                            reached) which is either the first value
    //                            (kDecline) or the last value (kIncline)
    //      number_of_steps_arg - the total number of steps/samples in this
    //                            segment (including the peak value and 0)
    //      seg_gradient_arg        - either kDecline or kIncline
    //--------------------------------------------------------------------
    explicit LinearSegment(
            float peak_amplitude_arg, 
            size_t number_of_steps_arg,
            SegmentGradient seg_gradient_arg);
    ~LinearSegment();

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    // Virtual functions/operators
    //--------------------------------------------------------------------
    std::vector<float> GetSegment() override;
    const float& operator[](const std::size_t position) const override;
    float& operator[](const std::size_t position) override;
    bool IsEmpty() const override;
    std::size_t Length() const override;

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    std::size_t number_of_steps() const;

private:
    //--------------------------------------------------------------------
    // 4. PRIVATE METHODS 
    //--------------------------------------------------------------------
    // None

    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
    std::size_t number_of_steps_;
    float peak_amplitude_;
    SegmentGradient seg_gradient_;
    std::vector<float> segment_;
    friend ArEnvelope;
};

//========================================================================
// CLASS: ExponentialSegment
//
// DESCRIPTION:
//      An exponential segment in an envelope. Mathematically it is defined
//      by: y = a*x^b + c. The segment is guaranteed to be 0 at one end and
//      the specified peak amplitude at the other.
//========================================================================
class ExponentialSegment : public Segment
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      ExponentialSegment()
    //  
    //  DESCRIPTION:
    //      Constructor
    //  INPUT:
    //      amplitude_start_arg - amplitude at the start of the segment
    //      amplitude_end_arg   - amplitude at the end of the segment
    //      number_of_steps_arg - the total number of steps/samples in this
    //                            segment
    //--------------------------------------------------------------------
    explicit ExponentialSegment(
            float amplitude_start_arg, 
            float amplitude_end_arg, 
            float exponent_arg, 
            size_t number_of_steps_arg);
    ~ExponentialSegment();

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    // Virtual functions/operators
    //--------------------------------------------------------------------
    std::vector<float> GetSegment() override;
    const float& operator[](const std::size_t position) const override;
    float& operator[](const std::size_t position) override;
    bool IsEmpty() const override;
    std::size_t Length() const override;

    //--------------------------------------------------------------------
    //  NAME:
    //      number_of_steps() 
    //  
    //  DESCRIPTION:
    //      Accessor
    //  INPUT:
    //      None
    //  OUTPUT:
    //      number_of_steps_ 
    //--------------------------------------------------------------------
    std::size_t number_of_steps() const;

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    // None

private:
    //--------------------------------------------------------------------
    // 4. PRIVATE METHODS 
    //--------------------------------------------------------------------
    // None

    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
    std::size_t number_of_steps_;
    float amplitude_start_; 
    float amplitude_end_; 
    float exponent_; 
    std::vector<float> segment_;
    friend AdsrEnvelope;
};

//========================================================================
//  CLASS: SegmentInitialisationException 
//
// DESCRIPTION:
//  Exception thrown when the corresponding segment is not initialised
//  correctly. This can be detected by checking init_ agains the 'emptiness' 
//  of the segment.
//========================================================================
class SegmentInitialisationException : public std::exception
{
    virtual const char* what() const noexcept;
};

#endif /* #define _SEGMENT_H_ */
