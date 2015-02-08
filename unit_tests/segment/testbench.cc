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

#include <common/segment.h>
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
        EXPECT_EQ(segment[size_expected], peak_amplitude_expected);
        EXPECT_LE(fabs(segment[size_expected/2]- peak_amplitude_expected/2), kEps);
}

void ValidateSegmentDecline(
        float peak_amplitude_expected, 
        size_t size_expected,
        LinearSegment &segment)
{
        EXPECT_EQ(segment.number_of_steps(), size_expected);
        EXPECT_EQ(segment[size_expected], 0);
        EXPECT_EQ(segment[0], peak_amplitude_expected);
        EXPECT_LE(fabs(segment[size_expected/2]- peak_amplitude_expected/2), kEps);
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

    LinearSegment segment(peak_amplitude, number_of_steps, kIncline); 

    EXPECT_EQ(segment.IsEmpty(), true);
}

TEST(LinearSegmentTest, HandleDifferentLengthsIncline)
{
    size_t number_of_steps[] = {2, 40, 100, 1000};
    float peak_amplitude = 1 << 15;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (size_t idx = 0; idx < 4; idx++) 
    {
        LinearSegment segment(peak_amplitude, number_of_steps[idx], kIncline); 
        ValidateSegmentIncline(peak_amplitude, number_of_steps[idx], segment);
    }
}

TEST(LinearSegmentTest, HandleDifferentVolumesIncline)
{
    size_t number_of_steps = 100;
    float peak_amplitude[] = {0, 1, 1000, 1 << 15};

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (size_t idx = 0; idx < 4; idx++) 
    {
        LinearSegment segment(peak_amplitude[idx], number_of_steps, kIncline); 
        ValidateSegmentIncline(peak_amplitude[idx], number_of_steps, segment);

    }
}

TEST(LinearSegmentTest, HandleDifferentLengthsDecline)
{
    size_t number_of_steps[] = {2, 40, 100, 1000};
    float peak_amplitude = 1 << 15;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (size_t idx = 3; idx < 4; idx++) 
    {
        LinearSegment segment(peak_amplitude, number_of_steps[idx], kDecline); 
        ValidateSegmentDecline(peak_amplitude, number_of_steps[idx], segment);
    }
}

TEST(LinearSegmentTest, HandleDifferentVolumesDecline)
{
    size_t number_of_steps = 100;
    float peak_amplitude[] = {0, 1, 1000, 1 << 15};

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (size_t idx = 0; idx < 4; idx++) 
    {
        LinearSegment segment(peak_amplitude[idx], number_of_steps, kDecline); 
        ValidateSegmentDecline(peak_amplitude[idx], number_of_steps, segment);
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
