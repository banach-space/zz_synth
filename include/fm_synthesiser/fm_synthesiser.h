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
//  License: GNU GPL v2.0 
//========================================================================

#ifndef _FMSYNTHESIS_H_
#define _FMSYNTHESIS_H_

#include <global/global_include.h>
#include <common/synth_config.h>

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
            double frequency_deviation);
    virtual ~FmSynthesiser() = default;
    explicit FmSynthesiser(const FmSynthesiser& rhs) = delete;
    explicit FmSynthesiser(FmSynthesiser&& rhs) = delete;
    FmSynthesiser& operator=(const FmSynthesiser &rhs) = delete;
    FmSynthesiser& operator=(FmSynthesiser&& rhs) = delete;

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      operator()
    //  
    //  DESCRIPTION:
    //      Oscillators by oscillating generate waveforms. This operator
    //      will generate one for you.
    //  INPUT:
    //      number_of_seconds - the length (in seconds) of the desired
    //                          waveform (TODO!!! Limit?!)
    //  RETURN:
    //      Vector of samples for the requested waveform
    //--------------------------------------------------------------------
	std::vector<int16_t> operator()(uint32_t number_of_seconds);

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
    // 3. INTERFACE DEFINITION 
    //--------------------------------------------------------------------
    virtual std::vector<int16_t> GenWaveform(
            size_t number_of_samples,
            int16_t peak_amplitude,
            double initial_phase,
            double frequency_carrier,
            double frequency_modulator
            ) const;

    //--------------------------------------------------------------------
    // 5. DATA MEMMBERS 
    //--------------------------------------------------------------------
    int16_t peak_amplitude_;
    double frequency_carrier_;
    double frequency_modulator_;
    double initial_phase_;
    uint32_t sampling_rate_;
    
};

#endif /* #define _FMSYNTHESIS_H_ */
