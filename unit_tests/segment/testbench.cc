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

//========================================================================
// UTILITIES 
//========================================================================

//========================================================================
// TESTS
//========================================================================
TEST(EnvelopeSegmentTest, LinearSegment)
{
    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();	

}

//========================================================================
// MAIN 
//========================================================================
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
