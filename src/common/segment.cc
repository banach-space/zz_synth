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
Segment::Segment() {}
Segment::~Segment() {}


//========================================================================
// CLASS: LinearSegment
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
LinearSegment::LinearSegment(
        float peak_amplitude_arg, 
        size_t number_of_steps_arg,
        LinearSegmentType seg_type_arg) :
    number_of_steps_(number_of_steps_arg),
    peak_amplitude_(peak_amplitude_arg),
    seg_type_(seg_type_arg),
    segment_(0)
{
    double volume = 0;
    double increment = 0; 
    segment_.reserve(number_of_steps_);

    if (seg_type_ == kIncline)
    {
        increment = static_cast<double>(peak_amplitude_) / static_cast<double>(number_of_steps_ - 1);
        volume = 0;
    } else
    {
        increment = - static_cast<double>(peak_amplitude_) / static_cast<double>(number_of_steps_ - 1);
        volume = peak_amplitude_;
    }

    vector<float>::iterator it;

    for (size_t idx = 0; idx < number_of_steps_; idx++)
    {
        segment_.push_back(volume);
        volume += increment;
    }

    // Due to rounding error the last entry might be different from 
    // peak_amplitude. Force it to be equal.
    if (number_of_steps_ > 0)
    {
        if (seg_type_ == kIncline)
        {
            segment_[number_of_steps_-1] = peak_amplitude_;
        } else
        {
            segment_[number_of_steps_-1] = 0;
        }
    }
}

LinearSegment::~LinearSegment() 
{}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
const float& LinearSegment::operator[](const size_t position) const
{
    assert(position <= number_of_steps_);

    return segment_[position];
}

float& LinearSegment::operator[](const size_t position)
{
    assert(position <= number_of_steps_);

    return segment_[position];
}

vector<float> LinearSegment::GetSegment()
{
    return segment_; 
}

bool LinearSegment::IsEmpty() const
{
    return segment_.empty();
}

size_t LinearSegment::number_of_steps() const
{
    return number_of_steps_;
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
