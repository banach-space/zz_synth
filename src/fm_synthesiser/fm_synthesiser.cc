//========================================================================
// FILE:
//      src/fm_synthesiser/fm_synthesiser.cc
//
// AUTHOR:
//      zimzum@github
//
// DESCRIPTION:
//		Implements classes for generating frequency modulated waveforms.
//
//  License: GNU GPL v2.0
//========================================================================

#include <common/synth_config.h>
#include <fm_synthesiser/fm_synthesiser.h>
#include <oscillator/oscillator.h>

using namespace std;

//========================================================================
// CLASS: FmSynthesiser
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
FmSynthesiser::FmSynthesiser(const SynthConfig& synthesiser,
                             int16_t peak_amplitude_arg,
                             double initial_phase_arg,
                             std::size_t pitch_id_carrier_arg,
                             std::size_t pitch_id_modulator_arg,
                             double index_of_modulation_arg)
    : synthesiser_(synthesiser),
      peak_amplitude_(peak_amplitude_arg),
      frequency_carrier_(synthesiser.frequency_table(pitch_id_carrier_arg)),
      frequency_modulator_(synthesiser.frequency_table(pitch_id_modulator_arg)),
      initial_phase_(initial_phase_arg),
      index_of_modulation_(index_of_modulation_arg) {
  assert((pitch_id_carrier_arg >= 0) &&
         (pitch_id_carrier_arg <= kNumberOfFrequencies));
  assert((pitch_id_modulator_arg >= 0) &&
         (pitch_id_modulator_arg <= kNumberOfFrequencies));
}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE
//------------------------------------------------------------------------
vector<int16_t> FmSynthesiser::operator()(uint32_t number_of_seconds) const {
  size_t number_of_samples = (synthesiser_.sampling_rate() * number_of_seconds);
  double phase_modulator = 0.0;
  double modulator_current_value = 0.0;
  double current_phase_at_sampling_rate = 0.0;
  double temp = 0.0;
  vector<int16_t> samples_output(number_of_samples);
  vector<int16_t> samples_modulator(number_of_samples);

  // Use Oscillator to get the modulating signal
  SynthConfig& synthesiser = SynthConfig::getInstance();
  SineWaveform osc(synthesiser, index_of_modulation_, initial_phase_,
                   frequency_modulator_);
  samples_modulator = osc(number_of_seconds);

  // Modulate
  for (auto it = samples_output.begin(), it2 = samples_modulator.begin();
       it != samples_output.end(); it++, it2++) {
    temp = (peak_amplitude_ *
            sin((frequency_carrier_ + *it2) * current_phase_at_sampling_rate));
    *it = static_cast<int16_t>(temp);
    current_phase_at_sampling_rate += synthesiser_.phase_increment_per_sample();
  }

  return samples_output;
}

//------------------------------------------------------------------------
// 3. ACCESSORS
//------------------------------------------------------------------------
// None

//------------------------------------------------------------------------
// 4. MUTATORS
//------------------------------------------------------------------------
// None
