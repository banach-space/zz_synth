//========================================================================
// FILE:
//      src/common/segment.cc
//
// AUTHOR:
//      banach-space@github
//
// DESCRIPTION:
//      Classes representing enevelope segments.
//
//  License: GNU GPL v2.0
//========================================================================

#include <envelope/segment.h>

#include <global/global_include.h>

using namespace std;

//========================================================================
// CLASS: Segment
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
Segment::Segment(size_t number_of_samples_arg)
    : samples_(0),
      generated_(false),
      number_of_samples_(number_of_samples_arg) {}
Segment::~Segment() {}

const float& Segment::operator[](const size_t position) const
{
    assert(position <= number_of_samples_);
    assert(generated_ && "Samples not generated!");

    return samples_[position];
}

float& Segment::operator[](const size_t position)
{
    assert(position <= number_of_samples_);
    assert(generated_ && "Samples not generated!");

    return samples_[position];
}

//========================================================================
// CLASS: ConstantSegment
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
ConstantSegment::ConstantSegment(
            float amplitude_arg,
            size_t number_of_samples_arg):
    Segment(number_of_samples_arg),
    amplitude_(amplitude_arg)
{
}

ConstantSegment::~ConstantSegment()
{}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE
//------------------------------------------------------------------------
void ConstantSegment::GenerateSamples()
{
    samples_.clear();
    samples_ = vector<float>(number_of_samples_, amplitude_);
    generated_ = true;
}

bool ConstantSegment::IsEmpty() const
{
    return (number_of_samples_ == 0);
}

size_t ConstantSegment::GetLength() const
{
    return number_of_samples_;
}

//========================================================================
// CLASS: LinearSegment
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
LinearSegment::LinearSegment(
        float peak_amplitude_arg,
        size_t number_of_samples_arg,
        SegmentGradient seg_gradient_arg) :
    Segment(number_of_samples_arg),
    peak_amplitude_(peak_amplitude_arg),
    seg_gradient_(seg_gradient_arg)
{
    GenerateSamples();
}

void LinearSegment::GenerateSamples()
{
    double volume = 0;
    double increment = 0;
    samples_.clear();

    samples_.reserve(number_of_samples_);

    // Step 1: Calculate the starting value and the increment that will be used
    //         to step through the segment.
    if (seg_gradient_ == SegmentGradient::kIncline)
    {
        increment = static_cast<double>(peak_amplitude_) / static_cast<double>(number_of_samples_ - 1);
        volume = 0;
    } else
    {
        increment = - static_cast<double>(peak_amplitude_) / static_cast<double>(number_of_samples_ - 1);
        volume = peak_amplitude_;
    }

    // Step 2: Walk through the segment and propagate with the right values
    for (size_t idx = 0; idx < number_of_samples_; idx++)
    {
        samples_.push_back(static_cast<float>(volume));
        volume += increment;
    }

    // Step 3: Fix what's at the beginning/end as due to rounding error
    //         the last/first (incline/decline) entry might be different from
    //         peak_amplitude. Force it to be equal.
    if (number_of_samples_ > 0)
    {
        if (seg_gradient_ == SegmentGradient::kIncline)
        {
            samples_[number_of_samples_-1] = peak_amplitude_;
        } else
        {
            samples_[number_of_samples_-1] = 0;
        }
    }

    generated_ = true;
}

LinearSegment::~LinearSegment()
{}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE
//------------------------------------------------------------------------
bool LinearSegment::IsEmpty() const
{
    return samples_.empty();
}

size_t LinearSegment::GetLength() const
{
    return number_of_samples_;
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
        size_t number_of_samples_arg) :
    Segment(number_of_samples_arg),
    amplitude_start_(amplitude_start_arg),
    amplitude_end_(amplitude_end_arg),
    exponent_(exponent_arg)
{
  GenerateSamples();
}

void ExponentialSegment::GenerateSamples() {
    // ALGORITHM: This segment is calculated using the following equation:
    //      y = a*x^b + c
    //  The 'a' and 'c' coefficients are calculated using the value for
    //  the starting and the final amplitude: amplitude_start_ and amplitude_end_.
    //  The time variable, 'x', is assumed to be in the range [0, 1]. This way
    //  the starting amplitude is guaranteed to be amplitude_start_, and the value
    //  at the end will be amplitude_end_.
    double volume         = 0;
    double time           = 0;
    double time_increment = 0;

    samples_.clear();
    samples_.reserve(number_of_samples_);

    // Step 1: Calculate 'a' and 'c'. This is based on rather straighforward
    //         Maths.
    double coefficient_c = amplitude_start_;
    double coefficient_a = amplitude_end_ - amplitude_start_;

    // Step 2: Time step-size. Recall that time is assumed to vary from 0 to 1
    //         and that it's split into number_of_samples_ steps.
    time_increment = 1.0 / (number_of_samples_ - 1);

    // Step 3: Walk through the segment and propagate it with the right values
    if (number_of_samples_ != 0)
    {
        /* Need to take special care when calculating 0^0. Here it is assumed that 0^0 = 1.*/
        if (fabs(exponent_) > kEps)
        {
            volume = coefficient_a*pow(time, exponent_) + coefficient_c;

        } else
        {
            volume = coefficient_a + coefficient_c;
        }

        samples_.push_back(static_cast<float>(volume));
        time += time_increment;


        /* The rest of the segment is calculate using the following generic algorithm.*/
        for (size_t idx = 1; idx < number_of_samples_; idx++)
        {
            volume = coefficient_a*pow(time, exponent_) + coefficient_c;
            samples_.push_back(static_cast<float>(volume));

            time += time_increment;
        }

        // Fix what's at the beginning/end as due to rounding error
        // the first/last entry might be different from amplitude_start and
        // amplitude_end, respecitvely. Force it to be equal.
        if (fabs(exponent_) > kEps)
        {
            samples_[0] = amplitude_start_;
            samples_[number_of_samples_-1] = amplitude_end_;
        }
    }

    generated_ = true;

}

ExponentialSegment::~ExponentialSegment()
{}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE
//------------------------------------------------------------------------
bool ExponentialSegment::IsEmpty() const
{
    return samples_.empty();
}

size_t ExponentialSegment::GetLength() const
{
    return number_of_samples_;
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
const char* SegmentInitialisationException::what() const noexcept
{
    return "Segment initialised inccorectly.";
}
