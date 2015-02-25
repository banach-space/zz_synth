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
// CLASS: ConstantSegment
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
ConstantSegment::ConstantSegment(
            float amplitude_arg, 
            size_t number_of_steps_arg):
    Segment(),
    number_of_steps_(number_of_steps_arg),
    amplitude_(amplitude_arg)
{
}

ConstantSegment::~ConstantSegment() 
{}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
const float& ConstantSegment::operator[](const size_t position) const
{
    assert(position <= number_of_steps_);

    return amplitude_;
}

float& ConstantSegment::operator[](const size_t position)
{
    assert(position <= number_of_steps_);

    return amplitude_;
}

vector<float> ConstantSegment::GetSegment()
{
    vector<float> segment(number_of_steps_, amplitude_);
    return segment; 
}

bool ConstantSegment::IsEmpty() const
{
    return (number_of_steps_ == 0);
}

size_t ConstantSegment::number_of_steps() const
{
    return number_of_steps_;
}

size_t ConstantSegment::Length() const
{
    return number_of_steps();
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

size_t LinearSegment::Length() const
{
    return number_of_steps();
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
    // ALGORITHM: This segment is calculated using the following equation:
    //      y = a*x^b + c 
    //  The 'a' and 'c' coefficients are calculated using the value for 
    //  the starting and the final amplitude: amplitude_start_ and amplitude_end_.
    //  The time variable, 'x', is assumed to be in the range [0, 1]. This way
    //  the starting amplitude is guaranteed to be amplitude_start_, and the value
    //  at the end will be amplitude_end_.
    double volume = 0;
    double time = 0;
    double time_increment = 0;

    segment_.reserve(number_of_steps_);

    // Step 1: Calculate 'a' and 'c'. This is based on rather straighforward
    //         Maths.
    double coefficient_c = amplitude_start_;
    double coefficient_a = amplitude_end_ - amplitude_start_;

    // Step 2: Time step-size. Recall that time is assumed to vary from 0 to 1
    //         and that it's split into number_of_steps_ steps.
    time_increment = 1.0 / (number_of_steps_ - 1);

    // Step 3: Walk through the segment and propagate it with the right values
    if (number_of_steps_ != 0)
    {
        /* Need to take special care when calculating 0^0. Here it is assumed that 0^0 = 1.*/
        if (exponent_ != 0)
        {
            volume = coefficient_a*pow(time, exponent_) + coefficient_c;

        } else
        {
            volume = coefficient_a + coefficient_c;
        }

        segment_.push_back(volume);
        time += time_increment;


        /* The rest of the segment is calculate using the following generic algorithm.*/
        for (size_t idx = 1; idx < number_of_steps_; idx++)
        {
            volume = coefficient_a*pow(time, exponent_) + coefficient_c;
            segment_.push_back(volume);

            time += time_increment;
        }

        // Fix what's at the beginning/end as due to rounding error
        // the first/last entry might be different from amplitude_start and
        // amplitude_end, respecitvely. Force it to be equal.
        if (exponent_ != 0)
        {
            segment_[0] = amplitude_start_;
            segment_[number_of_steps_-1] = amplitude_end_;
        }
    }
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

size_t ExponentialSegment::Length() const
{
    return number_of_steps();
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
