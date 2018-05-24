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
        EXPECT_EQ(true, segment.IsGenerated());
        EXPECT_EQ(segment.GetLength(), size_expected);
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

        EXPECT_EQ(true, segment.IsGenerated());
        EXPECT_EQ(segment.GetLength(), size_expected);
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
        EXPECT_EQ(true, segment.IsGenerated());
        EXPECT_EQ(segment.GetLength(), size_expected);
        EXPECT_EQ(segment[0], amplitude_start_expected);
        EXPECT_EQ(segment[size_expected-1], amplitude_end_expected);
}

//========================================================================
// TEST FIXTURES
//========================================================================
// The structure to hold some default set up for the segment
typedef struct SegConf {
  const float amplitude;
  const float amplitude_start;
  const float amplitude_end;
  const size_t number_of_samples;
  const SegmentGradient grad;
  const float exponent;
  SegConf()
      : amplitude(1 << 15),
        amplitude_start(0),
        amplitude_end(1),
        number_of_samples(101),
        grad(SegmentGradient::kIncline),
        exponent(2) {}
} SegConf;

class ConstSegmentTestFixture : public ::testing::Test {
    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
protected:
    // Init the segment
    ConstantSegment segment;

    static const SegConf default_conf;

    virtual void SetUp() {
      synthesiser.Init();
      segment.SetAmplitude(default_conf.amplitude);
      segment.SetNumberOfSamples(default_conf.number_of_samples);
    }
};

SegConf const ConstSegmentTestFixture::default_conf;

class LinearSegmentTestFixture : public ::testing::Test {
    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
protected:
    // Init the segment
    LinearSegment segment;

    static const SegConf default_conf;

    virtual void SetUp() {
      synthesiser.Init();
      segment.SetPeakAmplitude(default_conf.amplitude);
      segment.SetNumberOfSamples(default_conf.number_of_samples);
      segment.SetGradient(default_conf.grad);
    }
};

SegConf const LinearSegmentTestFixture::default_conf;

class ExponentialSegmentTestFixture : public ::testing::Test {
    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
protected:
    // Init the segment
    ExponentialSegment segment;

    static const SegConf default_conf;

    virtual void SetUp() {
      synthesiser.Init();
      segment.SetStartAmplitude(default_conf.amplitude_start);
      segment.SetEndAmplitude(default_conf.amplitude_end);
      segment.SetNumberOfSamples(default_conf.number_of_samples);
      segment.SetExponent(default_conf.exponent);
    }
};

SegConf const ExponentialSegmentTestFixture::default_conf;

//========================================================================
// TESTS
//========================================================================
//------------------------------------------------------------------------
// All types of segments
//------------------------------------------------------------------------
TEST(AllSegmentTypesTest, HandleEmptySegment)
{
    size_t number_of_samples = 0;
    float peak_amplitude   = 1 << 15;
    float amplitude_start  = 1 << 15;
    float amplitude_end    = 1;
    float exponent         = 100;

    // Initialise the synthesiser
    SynthConfig &synthesiser  = SynthConfig::getInstance();
    synthesiser.Init();

    // Constant segment
    ConstantSegment segment_c(peak_amplitude, number_of_samples);
    EXPECT_EQ(segment_c.IsEmpty(), true);

    // Linear segment
    LinearSegment segment_l(peak_amplitude, number_of_samples, SegmentGradient::kIncline);
    EXPECT_EQ(segment_l.IsEmpty(), true);

    // Exponential segment
    ExponentialSegment segment_e(amplitude_start, amplitude_end, exponent, number_of_samples);
    EXPECT_EQ(segment_e.IsEmpty(), true);
}

//------------------------------------------------------------------------
// ConstantSegment
//------------------------------------------------------------------------
TEST_F(ConstSegmentTestFixture, HandleDifferentLengths)
{
    vector<size_t> number_of_samples = {4, 41, 101, 1001, 2000};

    for (auto it = number_of_samples.begin(); it != number_of_samples.end(); it++)
    {
        segment.SetNumberOfSamples(*it);
        segment.GenerateSamples();
        ValidateConstantSegment(default_conf.amplitude, *it, segment);
    }
}

TEST_F(ConstSegmentTestFixture, HandleDifferentVolumes)
{
    vector<float> amplitude = {0, 1, 1000, 1 << 15};

    for (auto it = amplitude.begin(); it != amplitude.end(); it++)
    {
        segment.SetAmplitude(*it);
        segment.GenerateSamples();
        ValidateConstantSegment(*it, default_conf.number_of_samples, segment);
    }
}

//------------------------------------------------------------------------
// LinearSegment
//------------------------------------------------------------------------
TEST_F(LinearSegmentTestFixture, HandleDifferentLengthsIncline)
{
    vector<size_t> number_of_samples = {4, 41, 101, 1001, 2000};

    for (auto it = number_of_samples.begin(); it != number_of_samples.end(); it++)
    {
        segment.SetNumberOfSamples(*it);
        segment.GenerateSamples();
        ValidateLinearSegment(0.0f, default_conf.amplitude, *it, segment);
    }
}

TEST_F(LinearSegmentTestFixture, HandleDifferentVolumesIncline)
{
    vector<float> peak_amplitude = {0, 1, 1000, 1 << 15};

    for (auto it = peak_amplitude.begin(); it != peak_amplitude.end(); it++)
    {
        segment.SetPeakAmplitude(*it);
        segment.GenerateSamples();
        ValidateLinearSegment(0.0f, *it, default_conf.number_of_samples, segment);
    }
}

TEST_F(LinearSegmentTestFixture, HandleDifferentLengthsDecline)
{
    vector<size_t> number_of_samples = {2, 41, 101, 1001, 2000};

    segment.SetGradient(SegmentGradient::kDecline);

    for (auto it = number_of_samples.begin(); it != number_of_samples.end(); it++)
    {
        segment.SetNumberOfSamples(*it);
        segment.GenerateSamples();
        ValidateLinearSegment(default_conf.amplitude, 0.0f, *it, segment);
    }
}

TEST_F(LinearSegmentTestFixture, HandleDifferentVolumesDecline)
{
    vector<float> peak_amplitude = {0, 1, 1000, 1 << 15};

    segment.SetGradient(SegmentGradient::kDecline);

    for (auto it = peak_amplitude.begin(); it != peak_amplitude.end(); it++)
    {
        segment.SetPeakAmplitude(*it);
        segment.GenerateSamples();
        ValidateLinearSegment(*it, 0.0f, default_conf.number_of_samples, segment);
    }
}

//------------------------------------------------------------------------
// ExponentialSegment
//------------------------------------------------------------------------
TEST_F(ExponentialSegmentTestFixture, HandleDifferentVolumesStart) {
  vector<float> amplitude_start = {0, 1, 1000, 1 << 15};

  for (auto it = amplitude_start.begin(); it != amplitude_start.end(); it++) {
    segment.SetStartAmplitude(*it);
    segment.GenerateSamples();
    ValidateSegmentExponential(*it, default_conf.amplitude_end,
                               default_conf.number_of_samples, segment);
  }
}

TEST_F(ExponentialSegmentTestFixture, HandleDifferentVolumesEnd) {
  vector<float> amplitude_end = {0, 1, 1000, 1 << 15};

  for (auto it = amplitude_end.begin(); it != amplitude_end.end(); it++) {
    segment.SetEndAmplitude(*it);
    segment.GenerateSamples();
    ValidateSegmentExponential(default_conf.amplitude_start, *it,
                               default_conf.number_of_samples, segment);
  }
}

TEST_F(ExponentialSegmentTestFixture, HandleDifferentLengths) {
  vector<size_t> number_of_samples = {2, 41, 101, 1001, 2000};

  for (auto it = number_of_samples.begin(); it != number_of_samples.end();
       it++) {
    segment.SetNumberOfSamples(*it);
    segment.GenerateSamples();
    ValidateSegmentExponential(default_conf.amplitude_start,
                               default_conf.amplitude_end, *it, segment);
  }
}

TEST_F(ExponentialSegmentTestFixture, HandleDifferentExponents) {
  vector<float> exponent = {0.0001f, 0.001f, 0.01f,   0.1f,    1.0f,
                            10.0f,   100.0f, 1000.0f, 10000.0f};

  for (auto it = exponent.begin(); it != exponent.end(); it++) {
    segment.SetExponent(*it);
    segment.GenerateSamples();
    ValidateSegmentExponential(default_conf.amplitude_start,
                               default_conf.amplitude_end,
                               default_conf.number_of_samples, segment);
  }
}

TEST_F(ExponentialSegmentTestFixture, ExponentEqualZero) {
  float exponent = 0;
  vector<float> amplitude_end = {-(1 << 15),      -1313.0f,       -13.25f,
                                 -1.0f / 2048.0f, 1.0f / 2048.0f, 13.25f,
                                 1313.0f,         1 >> 15};

  segment.SetExponent(exponent);

  for (auto it : amplitude_end) {
    segment.SetEndAmplitude(it);
    segment.GenerateSamples();

    // Exponent is 0, so expect this segment to be constant
    ValidateConstantSegment(it, default_conf.number_of_samples, segment);
  }
}

TEST_F(ExponentialSegmentTestFixture, ExponentEqualOneDifferentStepsIncline) {
  vector<size_t> number_of_samples = {2, 41, 101, 1001, 2000};

  // This test is specifically about kIncline segments. Make sure that the
  // necessary conditions are met.
  EXPECT_TRUE(segment.GetStartAmplitude() < segment.GetEndAmplitude())
      << "This test relies on the amplitudes being suitable for kIncline";

  // Setting the exponent to 1 makes this segment a linear segment.
  segment.SetExponent(1.0f);

  for (auto it : number_of_samples) {
    segment.SetNumberOfSamples(it);
    segment.GenerateSamples();

    // Exponent is 1, so expect this segment to be linear
    ValidateLinearSegment(default_conf.amplitude_start,
                          default_conf.amplitude_end, it, segment);
  }
}

TEST_F(ExponentialSegmentTestFixture, ExponentEqualOneDifferentStepsDecline) {
  vector<size_t> number_of_samples = {2, 41, 101, 1001, 2000};
  float amplitude_start = 1;
  float amplitude_end = 0;

  // Setting the exponent to 1 makes this segment a linear segment.
  segment.SetExponent(1.0f);

  // Make this a kDecline segment and make sure that the necessary conditions
  // are met.
  segment.SetStartAmplitude(amplitude_start);
  segment.SetEndAmplitude(amplitude_end);
  EXPECT_TRUE(segment.GetStartAmplitude() > segment.GetEndAmplitude())
      << "This test relies on the amplitudes being suitable for kDecline";

  for (auto it : number_of_samples) {
    segment.SetNumberOfSamples(it);
    segment.GenerateSamples();

    // Exponent is 1, so expect this segment to be linear
    ValidateLinearSegment(amplitude_start, amplitude_end, it, segment);
  }
}

TEST_F(ExponentialSegmentTestFixture, ExponentEqualOneDifferentAmplitudeStart) {
  vector<float> amplitude_start = {-(1 << 15),      -1313.0f,       -13.25f,
                                   -1.0f / 2048.0f, 1.0f / 2048.0f, 13.25f,
                                   1313.0f,         1 >> 15};
  float amplitude_end = -1;

  segment.SetEndAmplitude(amplitude_end);

  // Setting the exponent to 1 makes this segment a linear segment.
  segment.SetExponent(1.0f);

  for (auto it : amplitude_start) {
    segment.SetStartAmplitude(it);
    segment.GenerateSamples();

    // Exponent is 1, so expect this segment to be linear
    ValidateLinearSegment(it, amplitude_end, default_conf.number_of_samples,
                          segment);
  }
}

TEST_F(ExponentialSegmentTestFixture, ExponentEqualOneDifferentAmplitudeEnd) {
  vector<float> amplitude_end = {-(1 << 15),      -1313.0f,       -13.25f,
                                 -1.0f / 2048.0f, 1.0f / 2048.0f, 13.25f,
                                 1313.0f,         1 >> 15};
  float amplitude_start = -1;

  segment.SetStartAmplitude(amplitude_start);
  // Setting the exponent to 1 makes this segment a linear segment.
  segment.SetExponent(1.0f);

  for (auto it : amplitude_end) {
    segment.SetEndAmplitude(it);
    segment.GenerateSamples();

    // Exponent is 1, so expect this segment to be linear
    ValidateLinearSegment(amplitude_start, it, default_conf.number_of_samples,
                          segment);
  }
}
//========================================================================
// End of file
//========================================================================
