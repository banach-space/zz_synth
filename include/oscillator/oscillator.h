//========================================================================
//  FILE:
//      include/oscillator/oscillator.h 
//
//  AUTHOR:
//      zimzum@github 
//
//  DESCRIPTION:
//      Defines all classes used for generating basic waveforms:
//		 a) Oscillator - plain sine wave
//
//  License: GNU GPL v2.0 
//========================================================================

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <global/global_include.h>
#include <common/synth_config.h>

//========================================================================
// CLASS: Oscillator
//
// DESCRIPTION:
//      TODO
//========================================================================
class Oscillator 
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    // Make this class pure abstract and block copy constructor, assignment
    // operator and the corresponding move operators.
    explicit Oscillator(
            const SynthConfig& synthesiser,
            int16_t peak_amplitude, 
            double initial_phase ,
            std::size_t pitch_id);
    virtual ~Oscillator();
    explicit Oscillator(const Oscillator& rhs) = delete;
    explicit Oscillator(Oscillator&& rhs) = delete;
    Oscillator& operator=(const Oscillator &rhs) = delete;
    Oscillator& operator=(Oscillator&& rhs) = delete;

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
	std::vector<int16_t> operator()(uint32_t number_of_seconds);

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    // None

private:
    //--------------------------------------------------------------------
    // 4. DATA MEMMBERS 
    //--------------------------------------------------------------------
    int16_t peak_amplitude_;
    double frequency_;
    double initial_phase_;
    uint32_t sampling_rate_;
    double phase_increment_;
    
};

#endif /* #define OSCILLATOR_H */
