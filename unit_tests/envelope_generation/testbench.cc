//========================================================================
// FILE:
//		unit_tests/envelope_generation/testbench.cc
//
// AUTHOR:
//		zimzum@github 
//
// DESCRIPTION:
//		Template testbench file.	
//
// License: GNU GPL v2.0 
//========================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <common/envelope.h>

//========================================================================
// UTILITIES 
//========================================================================

//========================================================================
// TESTS
//========================================================================
TEST(EnvelopeGenerationTest, LinearEnvelope)
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
