//========================================================================
// FILE:
//		unit_tests/segment/testbench.cc
//
// AUTHOR:
//		zimzum@github 
//
// DESCRIPTION:
//      Testbench for testing the Segment class.
//
// License: GNU GPL v2.0 
//========================================================================

#include <gtest/gtest.h>

#include <envelope/segment.h>
#include <global/global_variables.h>

using namespace std;

//========================================================================
// VALIDATION FUNCTIONS
//========================================================================
//------------------------------------------------------------------------
//  NAME:
//      ValidateConstantSegment
//  
//  DESCRIPTION:
//      Validates a constant semgnet by checking whether it is indeed
//      constant
//  INPUT:
//      amplitude_expected  - expected amplitude of the segment
//      size_expectedi      - expected length of the segment
//      segment             - the segment to check
//  OUTPUT:
//      None
//------------------------------------------------------------------------
static void ValidateConstantSegment(
        float amplitude_expected, 
        size_t size_expected,
        Segment &segment)
{
        EXPECT_EQ(segment.Length(), size_expected);
        EXPECT_EQ(segment[0], amplitude_expected);
        EXPECT_EQ(segment[size_expected-1], amplitude_expected);
        EXPECT_EQ(segment[(size_expected-1)/2], amplitude_expected);
}

//------------------------------------------------------------------------
//  NAME:
//      ValidateLinerSegment
//  
//  DESCRIPTION:
//      Validates a liner semgnet. Verifies values at the beginning,
//      end, and in the middle of the segment.
//  INPUT:
//      amplitude_start_expected - expected amplitude at the start of the segment
//      amplitude_end_expected   - expected amplitude at the end of the segment
//      size_expectedi           - expected length of the segment
//      segment                  - the segment to check
//  OUTPUT:
//      None
//------------------------------------------------------------------------
static void ValidateLinearSegment(
        float amplitude_start_expected, 
        float amplitude_end_expected, 
        size_t size_expected,
        Segment &segment)
{

        float middle_amplitude_expected = (amplitude_end_expected + amplitude_start_expected)/2;

        EXPECT_EQ(segment.Length(), size_expected);
        EXPECT_EQ(segment[size_expected-1], amplitude_end_expected);
        EXPECT_EQ(segment[0], amplitude_start_expected);
        if ((size_expected % 2))
        {
            EXPECT_LE(fabs(segment[(size_expected-1)/2]- middle_amplitude_expected), kEps);
        } else
        {
            double temp = (segment[(size_expected-1)/2] + segment[(size_expected+1)/2])/2;
            EXPECT_LE(fabs(temp- middle_amplitude_expected), kEps);
        }
}

//------------------------------------------------------------------------
//  NAME:
//      ValidateExponentialSegment
//  
//  DESCRIPTION:
//      Validates an exponential semgnet. Verifies values at the beginning
//      and end of the segment.
//  INPUT:
//      amplitude_start_expected - expected amplitude at the start of the segment
//      amplitude_end_expected   - expected amplitude at the end of the segment
//      size_expectedi           - expected length of the segment
//      segment                  - the segment to check
//  OUTPUT:
//      None
//------------------------------------------------------------------------
static void ValidateSegmentExponential(
        float amplitude_start_expected, 
        float amplitude_end_expected, 
        size_t size_expected,
        Segment &segment)
{
        EXPECT_EQ(segment.Length(), size_expected);
        EXPECT_EQ(segment[0], amplitude_start_expected);
        EXPECT_EQ(segment[size_expected-1], amplitude_end_expected);
}

//========================================================================
// TESTS
//========================================================================
//------------------------------------------------------------------------
// All types of segments 
//------------------------------------------------------------------------
TEST(AllSegmentTypesTest, HandleEmptySegment)
{
    size_t number_of_steps = 0;
    float peak_amplitude   = 1 << 15;
    float amplitude_start  = 1 << 15;
    float amplitude_end    = 1;
    float exponent         = 100;
    
    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    // Constant segment
    ConstantSegment segment_c(peak_amplitude, number_of_steps); 
    EXPECT_EQ(segment_c.IsEmpty(), true);

    // Linear segment
    LinearSegment segment_l(peak_amplitude, number_of_steps, SegmentGradient::kIncline); 
    EXPECT_EQ(segment_l.IsEmpty(), true);

    // Exponential segment
    ExponentialSegment segment_e(amplitude_start, amplitude_end, exponent, number_of_steps); 
    EXPECT_EQ(segment_e.IsEmpty(), true);
}

//------------------------------------------------------------------------
// ConstantSegment 
//------------------------------------------------------------------------
TEST(ConsantSegmentTest, HandleDifferentLengths)
{
    vector<size_t> number_of_steps = {4, 41, 101, 1001, 2000};
    float amplitude                = 1 << 15;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = number_of_steps.begin(); it != number_of_steps.end(); it++) 
    {
        ConstantSegment segment(amplitude, *it); 
        ValidateConstantSegment(amplitude, *it, segment);
    }
}

TEST(ConstantSegmentTest, HandleDifferentVolumes)
{
    size_t number_of_steps  = 101;
    vector<float> amplitude = {0, 1, 1000, 1 << 15};

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = amplitude.begin(); it != amplitude.end(); it++) 
    {
        ConstantSegment segment(*it, number_of_steps); 
        ValidateConstantSegment(*it, number_of_steps, segment);

    }
}

//------------------------------------------------------------------------
// LinearSegment 
//------------------------------------------------------------------------
TEST(LinearSegmentTest, HandleDifferentLengthsIncline)
{
    vector<size_t> number_of_steps = {4, 41, 101, 1001, 2000};
    float peak_amplitude           = 1 << 15;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = number_of_steps.begin(); it != number_of_steps.end(); it++) 
    {
        LinearSegment segment(peak_amplitude, *it, SegmentGradient::kIncline); 
        ValidateLinearSegment(0.0f, peak_amplitude, *it, segment);
    }
}

TEST(LinearSegmentTest, HandleDifferentVolumesIncline)
{
    size_t number_of_steps       = 101;
    vector<float> peak_amplitude = {0, 1, 1000, 1 << 15};

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = peak_amplitude.begin(); it != peak_amplitude.end(); it++) 
    {
        LinearSegment segment(*it, number_of_steps, SegmentGradient::kIncline); 
        ValidateLinearSegment(0.0f, *it, number_of_steps, segment);

    }
}

TEST(LinearSegmentTest, HandleDifferentLengthsDecline)
{
    vector<size_t> number_of_steps = {2, 41, 101, 1001, 2000};
    float peak_amplitude           = 1 << 15;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = number_of_steps.begin(); it != number_of_steps.end(); it++) 
    {
        LinearSegment segment(peak_amplitude, *it, SegmentGradient::kDecline); 
        ValidateLinearSegment(peak_amplitude, 0.0f, *it, segment);
    }
}

TEST(LinearSegmentTest, HandleDifferentVolumesDecline)
{
    size_t number_of_steps       = 101;
    vector<float> peak_amplitude = {0, 1, 1000, 1 << 15};

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = peak_amplitude.begin(); it != peak_amplitude.end(); it++) 
    {
        LinearSegment segment(*it, number_of_steps, SegmentGradient::kDecline); 
        ValidateLinearSegment(*it, 0.0f, number_of_steps, segment);
    }
}

//------------------------------------------------------------------------
// ExponentialSegment 
//------------------------------------------------------------------------
TEST(ExponentialSegmentTest, HandleDifferentVolumesStart)
{
    size_t number_of_steps        = 101;
    vector<float> amplitude_start = {0, 1, 1000, 1 << 15};
    float amplitude_end           = 1;
    float exponent                = 2;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = amplitude_start.begin(); it != amplitude_start.end(); it++) 
    {
        ExponentialSegment segment(*it, amplitude_end, exponent, number_of_steps); 
        ValidateSegmentExponential(*it, amplitude_end, number_of_steps, segment);
    }
}

TEST(ExponentialSegmentTest, HandleDifferentVolumesEnd)
{
    size_t number_of_steps      = 101;
    vector<float> amplitude_end = {0, 1, 1000, 1 << 15};
    float amplitude_start       = 1;
    float exponent              = 2;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = amplitude_end.begin(); it != amplitude_end.end(); it++) 
    {
        ExponentialSegment segment(amplitude_start, *it, exponent, number_of_steps); 
        ValidateSegmentExponential(amplitude_start, *it, number_of_steps, segment);
    }
}

TEST(ExponentialSegmentTest, HandleDifferentLengths)
{
    vector<size_t> number_of_steps = {2, 41, 101, 1001, 2000};
    float amplitude_start          = 13;
    float amplitude_end            = 1313;
    float exponent                 = 2;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = number_of_steps.begin(); it != number_of_steps.end(); it++) 
    {
        ExponentialSegment segment(amplitude_start, amplitude_end, exponent, *it); 
        ValidateSegmentExponential(amplitude_start, amplitude_end, *it, segment);
    }
}

TEST(ExponentialSegmentTest, HandleDifferentExponents)
{
    size_t number_of_steps = 101;
    float amplitude_start  = 13;
    float amplitude_end    = 1313;
    vector<float> exponent = {0.0001f, 0.001f, 0.01f, 0.1f, 1.0f, 10.0f, 100.0f, 1000.0f, 10000.0f};

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = exponent.begin(); it != exponent.end(); it++) 
    {
        ExponentialSegment segment(amplitude_start, amplitude_end, *it, number_of_steps); 
        ValidateSegmentExponential(amplitude_start, amplitude_end, number_of_steps, segment);
    }
}

TEST(ExponentialSegmentTest, ExponentEqualZero)
{
    size_t number_of_steps      = 101;
    float amplitude_start       = 13;
    float exponent              = 0;
    vector<float> amplitude_end = {
        -(1 << 15), 
        -1313.0f, 
        -13.25f, 
        -1.0f/2048.0f, 
        1.0f/2048.0f, 
        13.25f, 
        1313.0f, 
        1 >> 15};

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it : amplitude_end)
    {
        ExponentialSegment segment(amplitude_start, it, exponent, number_of_steps); 

        // Exponent is 0, so expect this segment to be constant
        ValidateConstantSegment(it, number_of_steps, segment);
    }
}

TEST(ExponentialSegmentTest, ExponentEqualOneDifferentStepsIncline)
{
    vector<size_t> number_of_steps = {2, 41, 101, 1001, 2000};
    float amplitude_start  = 0;
    float amplitude_end    = 1;
    float exponent         = 1;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it : number_of_steps)
    {
        ExponentialSegment segment(amplitude_start, amplitude_end, exponent, it); 

        // Exponent is 1, so expect this segment to be linear
        ValidateLinearSegment(amplitude_start, amplitude_end,  it, segment);
    }
}

TEST(ExponentialSegmentTest, ExponentEqualOneDifferentStepsDecline)
{
    vector<size_t> number_of_steps = {2, 41, 101, 1001, 2000};
    float amplitude_start  = 1;
    float amplitude_end    = 0;
    float exponent         = 1;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it : number_of_steps)
    {
        ExponentialSegment segment(amplitude_start, amplitude_end, exponent, it); 

        // Exponent is 1, so expect this segment to be linear
        ValidateLinearSegment(amplitude_start, amplitude_end, it, segment);
    }
}

TEST(ExponentialSegmentTest, ExponentEqualOneDifferentAmplitudeStart)
{
    size_t number_of_steps = 101;
    vector<float> amplitude_start = {
        -(1 << 15), 
        -1313.0f, 
        -13.25f, 
        -1.0f/2048.0f, 
        1.0f/2048.0f, 
        13.25f, 
        1313.0f, 
        1 >> 15};
    float amplitude_end    = -1;
    float exponent         = 1;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it : amplitude_start)
    {
        ExponentialSegment segment(it, amplitude_end, exponent, number_of_steps); 

        // Exponent is 1, so expect this segment to be linear
        ValidateLinearSegment(it, amplitude_end, number_of_steps, segment);
    }
}

TEST(ExponentialSegmentTest, ExponentEqualOneDifferentAmplitudeEnd)
{
    size_t number_of_steps = 101;
    vector<float> amplitude_end = {
        -(1 << 15), 
        -1313.0f, 
        -13.25f, 
        -1.0f/2048.0f, 
        1.0f/2048.0f, 
        13.25f, 
        1313.0f, 
        1 >> 15};
    float amplitude_start  = -1;
    float exponent         = 1;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it : amplitude_end)
    {
        ExponentialSegment segment(amplitude_start,it, exponent, number_of_steps); 

        // Exponent is 1, so expect this segment to be linear
        ValidateLinearSegment(amplitude_start, it, number_of_steps, segment);
    }
}
//========================================================================
// End of file
//========================================================================
