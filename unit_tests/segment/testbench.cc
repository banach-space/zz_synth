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
#include <gmock/gmock.h>

#include <envelope/segment.h>
#include <common/zz_global.h>

using namespace std;

//========================================================================
// UTILITIES 
//========================================================================
void ValidateSegmentIncline(
        float peak_amplitude_expected, 
        size_t size_expected,
        LinearSegment &segment);
void ValidateSegmentDecline(
        float peak_amplitude_expected, 
        size_t size_expected,
        LinearSegment &segment);

void ValidateSegmentIncline(
        float peak_amplitude_expected, 
        size_t size_expected,
        LinearSegment &segment)
{
        EXPECT_EQ(segment.number_of_steps(), size_expected);
        EXPECT_EQ(segment[0], 0);
        EXPECT_EQ(segment[size_expected-1], peak_amplitude_expected);
        if ((size_expected % 2))
        {
            EXPECT_LE(fabs(segment[(size_expected-1)/2]- peak_amplitude_expected/2), kEps);
        } else
        {
            double temp = (segment[(size_expected-1)/2] + segment[(size_expected+1)/2])/2;
            EXPECT_LE(fabs(temp- peak_amplitude_expected/2), kEps);
        }
}

void ValidateSegmentDecline(
        float peak_amplitude_expected, 
        size_t size_expected,
        LinearSegment &segment)
{
        EXPECT_EQ(segment.number_of_steps(), size_expected);
        EXPECT_EQ(segment[size_expected-1], 0);
        EXPECT_EQ(segment[0], peak_amplitude_expected);
        if ((size_expected % 2))
        {
            EXPECT_LE(fabs(segment[(size_expected-1)/2]- peak_amplitude_expected/2), kEps);
        } else
        {
            double temp = (segment[(size_expected-1)/2] + segment[(size_expected+1)/2])/2;
            EXPECT_LE(fabs(temp- peak_amplitude_expected/2), kEps);
        }
}
//========================================================================
// TESTS
//========================================================================
TEST(LinearSegmentTest, HandleEmptySegment)
{
    size_t number_of_steps = 0;
    float peak_amplitude = 1 << 15;
    
    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    LinearSegment segment(peak_amplitude, number_of_steps, SegmentGradient::kIncline); 

    EXPECT_EQ(segment.IsEmpty(), true);
}

TEST(LinearSegmentTest, HandleDifferentLengthsIncline)
{
    vector<size_t> number_of_steps = {4, 41, 101, 1001, 2000};
    float peak_amplitude = 1 << 15;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = number_of_steps.begin(); it != number_of_steps.end(); it++) 
    {
        LinearSegment segment(peak_amplitude, *it, SegmentGradient::kIncline); 
        ValidateSegmentIncline(peak_amplitude, *it, segment);
    }
}

TEST(LinearSegmentTest, HandleDifferentVolumesIncline)
{
    size_t number_of_steps = 101;
    vector<float> peak_amplitude = {0, 1, 1000, 1 << 15};

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = peak_amplitude.begin(); it != peak_amplitude.end(); it++) 
    {
        LinearSegment segment(*it, number_of_steps, SegmentGradient::kIncline); 
        ValidateSegmentIncline(*it, number_of_steps, segment);

    }
}

TEST(LinearSegmentTest, HandleDifferentLengthsDecline)
{
    vector<size_t> number_of_steps = {2, 41, 101, 1001, 2000};
    float peak_amplitude = 1 << 15;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = number_of_steps.begin(); it != number_of_steps.end(); it++) 
    {
        LinearSegment segment(peak_amplitude, *it, SegmentGradient::kDecline); 
        ValidateSegmentDecline(peak_amplitude, *it, segment);
    }
}

TEST(LinearSegmentTest, HandleDifferentVolumesDecline)
{
    size_t number_of_steps = 101;
    vector<float> peak_amplitude = {0, 1, 1000, 1 << 15};

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (auto it = peak_amplitude.begin(); it != peak_amplitude.end(); it++) 
    {
        LinearSegment segment(*it, number_of_steps, SegmentGradient::kDecline); 
        ValidateSegmentDecline(*it, number_of_steps, segment);
    }
}

//========================================================================
// MAIN 
//========================================================================
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
