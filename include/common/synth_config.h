//========================================================================
// FILE:
//   /include/SynthConfig.h
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//  The definition of the SynthConfig class - configuration
//  class for the zz_synth library. In order to use the
//  synthesiser call SynthConfig::getInstance(), which will return a
//  reference to the only possible instance of the synthesiser (it's
//  implemented as singleton) and the call SynthConfig::Init() to make sure 
//  that it's in a good state.
//
// License: GNU GPL v2.0 
//========================================================================

#ifndef SYNTH_CONFIG_H
#define SYNTH_CONFIG_H

#include <global/global_include.h>
#include <global/global_variables.h>
#include <cmath>
#include <vector>

//========================================================================
// CLASS: SynthConfig
//========================================================================
class SynthConfig
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    // This class is implemented as Singleton, so block default constructors
    // and assignment operators. Use default destructor - it's sufficient.
    SynthConfig(SynthConfig const& copy) = delete;
    SynthConfig(SynthConfig&& copy) = delete;
    SynthConfig& operator=(SynthConfig const& copy) = delete;
    SynthConfig& operator=(SynthConfig&&) = delete;
    ~SynthConfig();

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      getInstance()  
    //
    //  DESCRIPTION:
    //      Returns a reference to the only instance of this class.
    //      This function can be called multiple times, but it always
    //      returns a reference to the same instance of the synthesiser.
    //  INPUT:
    //      none
    //  OUTPUT:
    //      Reference to the only instance of this class per execution.
    // 
    //--------------------------------------------------------------------
    static SynthConfig& getInstance();

    //--------------------------------------------------------------------
    //  NAME:
    //      Init()  
    //
    //  DESCRIPTION:
    //      Initialises the only available instance of the synthesiser.
    //      Should only be called after getInstance(), as otherwise
    //      there won't be any synthesiser to initialise.
    //      This initialisation is performed only once per every instance
    //      of the synthesiser. Make sure that you call this function
    //      before using the synthesiser.
    //  INPUT:
    //      sampling_rate_arg - the sampling rate to be used
    //  OUTPUT:
    //      none
    // 
    //--------------------------------------------------------------------
    void Init(uint32_t sampling_rate_arg = 44100);

    //--------------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------------
    double frequency_table(std::vector<double>::size_type pitch) const;
    uint32_t sampling_rate() const;
    double phase_increment_per_sample() const;

private:
    // The default constructor used implicitly in getInstance(). Not to
    // be called by external users.
    SynthConfig() : frequency_table_(kNumberOfFrequencies) {}

    // The frequency table based on equal-tempered scale with
    // middle C at index 48 (i.e. frequency_table_[48]). 
	std::vector<double> frequency_table_;
    uint32_t sampling_rate_;
    // Maximum representable frequency according to Nyquist
    float nyquist_limit_;
    // Phase increment per sample for signals at 1 Hz. Mathematically this
    // is simply 2*Pi / sample_rate_.
    double phase_increment_per_sample_;
    // Pre-calculated multiplier for frequency to table index
    // (tableLength/sampleRate)
    /*double frqTI_;*/
    // Pre-calculated multiplier for radians to table index
    // (tableLength/twoPI)
    /*double radTI_;*/
    // Maximum phase increment for wavetables (ftableLength/2)
    /*double maxIncrWT_;*/
    // Wave table length
    /*double ftableLength_;*/
    // Wave table length as integer
    /*int32_t itableLength_;*/

};

#endif /* SYNTH_CONFIG_H */
