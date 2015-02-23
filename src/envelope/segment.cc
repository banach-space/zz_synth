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

#include <envelope/segment.h>

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
        SegmentGradient seg_gradient_arg) :
    Segment(),
    number_of_steps_(number_of_steps_arg),
    peak_amplitude_(peak_amplitude_arg),
    seg_gradient_(seg_gradient_arg),
    segment_(0)
{
    double volume = 0;
    double increment = 0; 
    segment_.reserve(number_of_steps_);

    // Step 1: Calculate the starting value and the increment that will be used
    //         to step through the segment.
    if (seg_gradient_ == SegmentGradient::kIncline)
    {
        increment = static_cast<double>(peak_amplitude_) / static_cast<double>(number_of_steps_ - 1);
        volume = 0;
    } else
    {
        increment = - static_cast<double>(peak_amplitude_) / static_cast<double>(number_of_steps_ - 1);
        volume = peak_amplitude_;
    }

    // Step 2: Walk through the segment and propagate with the right values
    for (size_t idx = 0; idx < number_of_steps_; idx++)
    {
        segment_.push_back(volume);
        volume += increment;
    }

    // Step 3: Fix what's at the beginning/end as due to rounding error
    //         the last/first (incline/decline) entry might be different from
    //         peak_amplitude. Force it to be equal.
    if (number_of_steps_ > 0)
    {
        if (seg_gradient_ == SegmentGradient::kIncline)
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

//========================================================================
// CLASS: ExponentialSegment
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
ExponentialSegment::ExponentialSegment(
        float amplitude_start_arg, 
        float amplitude_end_arg, 
        float exponent_arg, 
        size_t number_of_steps_arg) :
    Segment(),
    number_of_steps_(number_of_steps_arg),
    amplitude_start_(amplitude_start_arg),
    amplitude_end_(amplitude_end_arg),
    exponent_(exponent_arg),
    segment_(0)
{
    double volume = 0;
    double time = 0;
    double time_increment = 0;

    segment_.reserve(number_of_steps_);

    // Algorithm: This segment is calculated using the y = x^b equation, i.e.
    //            'a' and 'c' are assummed to be 1 and 0, respectively. The time
    //            variable, 'x', is assumed to be in the range [0, 1]. This way
    //            the starting amplitude is guaranteed to be 0, and the value
    //            at the end will be 1.
    //
    // TODO: Extend this so that the starting and ending values are arbitrary.
    time_increment = 1.0 / number_of_steps_;

    for (size_t idx = 0; idx < number_of_steps_; idx++)
    {
        volume = std::pow(time, exponent_);
        segment_.push_back(volume);

        time += time_increment;
    }

    segment_[number_of_steps_-1] = 1;
}

ExponentialSegment::~ExponentialSegment() 
{}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
const float& ExponentialSegment::operator[](const size_t position) const
{
    assert(position <= number_of_steps_);

    return segment_[position];
}

float& ExponentialSegment::operator[](const size_t position)
{
    assert(position <= number_of_steps_);

    return segment_[position];
}

vector<float> ExponentialSegment::GetSegment()
{
    return segment_; 
}

bool ExponentialSegment::IsEmpty() const
{
    return segment_.empty();
}

size_t ExponentialSegment::number_of_steps() const
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
