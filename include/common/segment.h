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

enum SegmentType
{
    kDecline = 0,
    kIncline = 1
};

//========================================================================
// CLASS: Segment
//
// DESCRIPTION:
//      A segment in an envelope - the most  basic building block. Abstract
//      base class. 
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
    virtual std::vector<float> GetSegment() = 0;
    virtual const float& operator[](const std::size_t position) const = 0;
    virtual float& operator[](const std::size_t position) = 0;
    virtual bool IsEmpty() const = 0;

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    // None

private:
    //--------------------------------------------------------------------
    // 4. PRIVATE METHODS 
    //--------------------------------------------------------------------

    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
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
    explicit LinearSegment(
            float peak_amplitude_arg, 
            size_t number_of_steps_arg,
            SegmentType seg_type_arg);
    ~LinearSegment();

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    std::vector<float> GetSegment();
    const float& operator[](const std::size_t position) const;
    float& operator[](const std::size_t position);
    SegmentType seg_type() {return seg_type_;};
    bool IsEmpty() const;
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
    SegmentType seg_type_;
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
