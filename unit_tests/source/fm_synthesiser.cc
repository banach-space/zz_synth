//========================================================================
// FILE:
//		unit_tests/fm_synthesiser/testbench.cc
//
// AUTHOR:
//		zimzum@github
//
// DESCRIPTION:
//      Testbench for FM synthesiser
//
// License: GNU GPL v2.0
//========================================================================

#include <gtest/gtest.h>

#include <common/synth_config.h>
#include <fm_synthesiser/fm_synthesiser.h>
#include <global/global_variables.h>

using namespace std;

//========================================================================
// UTILITIES
//========================================================================
void TestFmSynthesiser() {
  size_t pitch_carrier = 64;
  vector<size_t> pitch_modulator = {10, 20, 30, 40,  50,  60,
                                    70, 80, 90, 100, 110, 120};
  vector<double> index_of_modulation = {1 << 3, 1 << 5, 1 << 8};
  int16_t volume = 1 << 14;
  double initial_phase = 0;
  size_t pitch = kNumberOfFrequencies / size_t(2);
  uint32_t duration = 1;

  // Initialise the synthesiser
  SynthConfig &synthesiser = SynthConfig::getInstance();
  synthesiser.Init();

  // The following lambda is used to check whether the input sample
  // is within the volume bounds, i.e. sample \in (-volume, volume).
  // volume_current is defined for passing the current volume.
  int16_t volume_current = volume;
  auto outside_bounds = [volume_current](int16_t sample) {
    return (sample > volume_current) && (sample < -volume_current);
  };

  for (auto it : pitch_modulator) {
    for (auto it2 : index_of_modulation) {
      FmSynthesiser fm_synthesiser(synthesiser, volume, initial_phase,
                                   pitch_carrier, it, it2);
      vector<int16_t> samples = fm_synthesiser(duration);

      EXPECT_EQ(samples.size(), duration * synthesiser.sampling_rate());
      auto n_outside_bounds =
          count_if(samples.begin(), samples.end(), outside_bounds);

      EXPECT_EQ(n_outside_bounds, 0);
    }
  }
}

//========================================================================
// TESTS
//========================================================================
TEST(YourTestNameTest, SubtestName) { TestFmSynthesiser(); }

//========================================================================
// End of file
//========================================================================
