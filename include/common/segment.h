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
    // TODO!!! This constructor will only work for linear segments. Need to
    // come back here later.
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

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    // None

private:
    //--------------------------------------------------------------------
    // 4. PRIVATE METHODS 
    //--------------------------------------------------------------------
    virtual void GenerateSegment(
        size_t number_of_samples,
        float peak_amplitude,
        vector<float> &output_segment) = 0;

    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
    size_t number_of_steps_;
    float peak_amplitude_;
    // The init_ variable is set by default set to 'false' and then changed to
    // 'true' once the segment_ vector is set. This is done by the Init()
    // function.
    bool init_;
    vector<float> segment_;
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
    void GenerateSegment(
        size_t number_of_samples,
        float peak_amplitude,
        vector<float> &output_segment);

    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
    size_t number_of_steps_;
    float peak_amplitude_;
};

//========================================================================
//  CLASS: SegmentInitialisationException 
//
// DESCRIPTION:
//  Exception class. Thrown when the corresponding segment is not initialised
//  correctly. This can be detected by checking init_ agains the 'emptiness' 
//  of the segment.
//========================================================================
class SegmentInitialisationException : public exception
{
    virtual const char* what() const throw();
};

#endif /* #define _SEGMENT_H_ */
