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

#ifndef _SEGMENT_H_
#define _SEGMENT_H_

#include <common/zz_global_include.h>


//========================================================================
// PRIVATE DATA TYPES
//========================================================================
//------------------------------------------------------------------------
//  NAME: 
//      LinearSegmentType
//
//  DESCRIPTION:
//      Enum used for differentiating between two types of linear
//      segments:
//          - kIncline represents attack (positive 'a')
//          - kDecline represents decay (negative 'a')
//------------------------------------------------------------------------
enum LinearSegmentType
{
    kDecline = 0,
    kIncline = 1
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
    //      seg_type_arg        - either kDecline or kIncline
    //--------------------------------------------------------------------
    explicit LinearSegment(
            float peak_amplitude_arg, 
            size_t number_of_steps_arg,
            LinearSegmentType seg_type_arg);
    ~LinearSegment();

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    // Virtual functions/operators
    //--------------------------------------------------------------------
    std::vector<float> GetSegment();
    const float& operator[](const std::size_t position) const;
    float& operator[](const std::size_t position);
    bool IsEmpty() const;

    //--------------------------------------------------------------------
    //  NAME:
    //      number_of_steps() 
    //  
    //  DESCRIPTION:
    //      Accessors
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
    float peak_amplitude_;
    LinearSegmentType seg_type_;
    std::vector<float> segment_;
};

//========================================================================
//  CLASS: SegmentInitialisationException 
//
// DESCRIPTION:
//  Exception thrown when the corresponding segment is not initialised
//  correctly. This can be detected by checking init_ agains the 'emptiness' 
//  of the segment.
//========================================================================
class SegmentInitialisationException : public exception
{
    virtual const char* what() const throw();
};

#endif /* #define _SEGMENT_H_ */
