//========================================================================
//  FILE:
//      include/fm_synthesiser/fm_synthesiser.h 
//
//  AUTHOR:
//      zimzum@github 
//
//  DESCRIPTION:
//      Classes for generating audio spectra using frequency modulation.
//
//  DEPENDENCIES:
//      lib/liboscillator.a
//
//  License: GNU GPL v2.0 
//========================================================================

#ifndef _FMSYNTHESIS_H_
#define _FMSYNTHESIS_H_

#include <global/global_include.h>
#include <common/synth_config.h>
#include <oscillator/oscillator.h>

//========================================================================
// CLASS: FmSynthesiser
//
// DESCRIPTION:
//      TODO!!!
//========================================================================
class FmSynthesiser 
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    explicit FmSynthesiser(
            const SynthConfig& synthesiser,
            int16_t peak_amplitude, 
            double initial_phase ,
            std::size_t pitch_id_carrier,
            std::size_t pitch_id_modulator,
            double index_of_modulation);
    ~FmSynthesiser() = default;
    explicit FmSynthesiser(const FmSynthesiser& rhs) = delete;
    explicit FmSynthesiser(FmSynthesiser&& rhs) = delete;
    FmSynthesiser& operator=(const FmSynthesiser &rhs) = delete;
    FmSynthesiser& operator=(FmSynthesiser&& rhs) = delete;

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  TODO!!! 
    //--------------------------------------------------------------------
	std::vector<int16_t> operator()(uint32_t number_of_seconds) const;

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    // None

protected:
    //--------------------------------------------------------------------
    // 4. MUTATORS
    //--------------------------------------------------------------------
    // None

private:
    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
    const SynthConfig& synthesiser_;
    int16_t peak_amplitude_;
    double initial_phase_;
    double frequency_carrier_;
    double frequency_modulator_;
    double index_of_modulation_;
    
};

#endif /* #define _FMSYNTHESIS_H_ */
