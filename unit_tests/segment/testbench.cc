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

//========================================================================
// UTILITIES 
//========================================================================

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

    LinearSegment segment(peak_amplitude, number_of_steps); 

    shared_ptr< const vector<float> > segment_data = segment.GetSegment();

    EXPECT_EQ(segment_data->empty(), true);
}

TEST(LinearSegmentTest, HandleDifferentLengths)
{
    size_t number_of_steps[] = {2, 40, 100, 1000};
    float peak_amplitude = 1 << 15;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (size_t idx = 0; idx < 4; idx++) 
    {
        LinearSegment segment(peak_amplitude, number_of_steps[idx]); 

        shared_ptr< const vector<float> > segment_data = segment.GetSegment();

        EXPECT_EQ((*segment_data)[0], 0);
        EXPECT_EQ((*segment_data)[number_of_steps[idx]], peak_amplitude);
        // Carefull here: comapring to kEps which is not that small!
        EXPECT_LE(fabs((*segment_data)[number_of_steps[idx]/2]- peak_amplitude/2), kEps);
    }
}

TEST(LinearSegmentTest, HandleDifferentVolumes)
{
    size_t number_of_steps = 100;
    float peak_amplitude[] = {0, 1, 1000, 1 << 15};

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

    for (size_t idx = 0; idx < 4; idx++) 
    {
        LinearSegment segment(peak_amplitude[idx], number_of_steps); 

        shared_ptr< const vector<float> > segment_data = segment.GetSegment();

        EXPECT_EQ((*segment_data)[0], 0);
        EXPECT_EQ((*segment_data)[number_of_steps], peak_amplitude[idx]);
        // Carefull here: comapring to kEps which is not that small!
        EXPECT_LE(fabs((*segment_data)[number_of_steps/2]- peak_amplitude[idx]/2), kEps);
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
