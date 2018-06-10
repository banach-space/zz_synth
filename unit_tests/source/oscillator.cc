//========================================================================
// FILE:
//		unit_tests/oscillator/testbench.cc
//
// AUTHOR:
//		zimzum@github
//
// DESCRIPTION:
//      Testbench for the Oscillator class.
//
// License: GNU GPL v2.0
//========================================================================

#include <algorithm>

#include <gtest/gtest.h>

#include <common/synth_config.h>
#include <oscillator/oscillator.h>

using namespace std;

//========================================================================
// UTILITIES
//========================================================================
template <typename T>
void TestOscillator() {
  size_t pitch = kNumberOfFrequencies / size_t(2);
  vector<int16_t> volume = {0, 1 << 7, 1 << 14};
  uint32_t duration = 1;
  double initial_phase = 0;

  // Initialise the synthesiser
  SynthConfig &synthesiser = SynthConfig::getInstance();
  synthesiser.Init();

  // The following lambda is used to check whether the input sample
  // is within the volume bounds, i.e. sample \in (-volume, volume).
  // volume_current is defined for passing the current volume.
  int16_t volume_current = 0;
  auto outside_bounds = [volume_current](int16_t sample) {
    return (sample > volume_current) && (sample < -volume_current);
  };

  for (auto it = volume.begin(); it != volume.end(); it++) {
    // 1. Generate the oscillator and the sound-wave
    T osc(synthesiser, *it, initial_phase, pitch);
    vector<int16_t> samples = osc(duration);

    // 2. Define volume_current for outside_bounds and check that the
    // generated wave is within the volume bounds.
    volume_current = *it;

    EXPECT_EQ(samples.size(), duration * synthesiser.sampling_rate());
    auto n_outside_bounds =
        count_if(samples.begin(), samples.end(), outside_bounds);

    EXPECT_EQ(n_outside_bounds, 0);
  }
}

//========================================================================
// TESTS
//========================================================================
TEST(AllOscillators, BasicTest) {
  TestOscillator<SineWaveform>();
  TestOscillator<SawtoothWaveform>();
  TestOscillator<SquareWaveform>();
  TestOscillator<TriangleWaveform>();
}
//========================================================================
// End of file
//========================================================================
