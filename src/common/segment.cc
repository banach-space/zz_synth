//========================================================================
// FILE:
//      src/common/segment.cc
//
// AUTHOR:
//      zimzum@github 
//
// DESCRIPTION:
//      Classes representing enevelop segments. 
//
//  License: GNU GPL v2.0 
//========================================================================

#include <common/segment.h>

#include <common/zz_global_include.h>

using namespace std;

//========================================================================
// CLASS: Segment
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
Segment::Segment(
        float peak_amplitude_arg, 
        size_t number_of_steps_arg,
        SegmentType seg_type_arg) :
    number_of_steps_(number_of_steps_arg),
    peak_amplitude_(peak_amplitude_arg),
    init_(false),
    seg_type_(seg_type_arg),
    segment_(0)
{}

Segment::~Segment() {}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
vector<float> Segment::GetSegment()
{
    // No need to reinitialise.
    if (!segment_.empty() && init_)
    {
        return segment_;
    }

    // If the segment_ is empty but init_ is true then something is wrong
    if (segment_.empty() && init_)
    {
        throw SegmentInitialisationException();
    }

    GenerateSegment(peak_amplitude_, segment_);

    init_ = true;

    return segment_; 
}

const float& Segment::operator[](const size_t position) const
{
    assert(position <= number_of_steps_);

    return segment_[position];
}

float& Segment::operator[](const size_t position)
{
    assert(position <= number_of_steps_);
    if (!init_)
    {
        GenerateSegment(peak_amplitude_, segment_);
        init_ = true;
        
    }
    return segment_[position];
}

bool Segment::IsEmpty() const
{
    return segment_.empty();
}

size_t Segment::number_of_steps() const
{
    return number_of_steps_;
}

//========================================================================
// CLASS: LinearSegment
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
LinearSegment::LinearSegment(
        float peak_amplitude_arg, 
        size_t number_of_steps_arg,
        SegmentType seg_type_arg) :
    Segment(peak_amplitude_arg, number_of_steps_arg, seg_type_arg)
{}

LinearSegment::~LinearSegment() 
{}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
void LinearSegment::GenerateSegment(
        float peak_amplitude,
        vector<float> &output_segment)
{
    output_segment.reserve(number_of_steps() + 1);
    double volume = 0;
    double increment = 0; 

    if (seg_type() == kIncline)
    {
        increment = peak_amplitude / number_of_steps();
        volume = 0;
    } else
    {
        increment = -(static_cast<double>(peak_amplitude) / number_of_steps());
        volume = peak_amplitude;
    }

    vector<float>::iterator it;

    for (size_t idx = 0; idx < number_of_steps(); idx++)
    {
        output_segment.push_back(volume);
        volume += increment;
    }

    // Due to rounding error the last entry might be different from 
    // peak_amplitude. Force it to be equal.
    if (number_of_steps() > 0)
    {
        if (seg_type() == kIncline)
        {
            output_segment.push_back(peak_amplitude);
        } else
        {
            output_segment.push_back(0);
        }
    }
}

const float& LinearSegment::operator[](const size_t position) const
{
    return Segment::operator[](position);
}

float& LinearSegment::operator[](const size_t position)
{
    return Segment::operator[](position);
}

//=============================================================
//  CLASS: SegmentInitialisationException 
//=============================================================
//--------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//--------------------------------------------------------------
// None 

//--------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//--------------------------------------------------------------
// None
const char* SegmentInitialisationException::what() const throw()
{
    return "Segment initialised inccorectly.";
}
