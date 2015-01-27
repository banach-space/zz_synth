//=============================================================
// FILE:
//   /include/zz_SynthConfig.h
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//   The definition of the SynthConfig class - configuration
//   class for the zz_synth library.
//
// License: GNU GPL v2.0 
//=============================================================

#ifndef _SYNTH_CONFIG_H_
#define _SYNTH_CONFIG_H_

#include "zz_global_include.h"
#include "zz_global.h"
#include <cmath>
#include <vector>

using namespace std;

class SynthConfig
{
public:
    //--------------------------------------------------------------
    // Constructors/Destructors/Assignment Operators
    //--------------------------------------------------------------
    // This class is implemented as Singleton, so block default constructors
    // and assignment operators. Use default destructor - it's sufficient.
    SynthConfig(SynthConfig const& copy) = delete;
    SynthConfig(SynthConfig&& copy) = delete;
    SynthConfig& operator=(SynthConfig const& copy) = delete;
    SynthConfig& operator=(SynthConfig&&) = delete;
    ~SynthConfig() = default;

    //-------------------------------------------------------------
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
    //--------------------------------------------------------------
    static SynthConfig& getInstance();

    //-------------------------------------------------------------
    //  NAME:
    //      Init()  
    //
    //  DESCRIPTION:
    //      Initialises the synthesiser using the parameters
    //      specified. This operation can only be performed once for
    //      every instance of the synthesiser. This function should
    //      be called after calling getInstance(), but before any
    //      subsequent uses of the synthesiser.
    //  INPUT:
    //      sampling_rate - the sampling rate to be used
    //  OUTPUT:
    //      none
    // 
    //--------------------------------------------------------------
    void Init(const int32_t sampling_rate = 44100);

    //--------------------------------------------------------------
    // Accessors
    //--------------------------------------------------------------
    double frequency_table(const int pitch) const;
    int32_t sampling_rate() const;
    double phase_increment_per_sample() const;

private:
    // The default constructor used implicitely in getInstance(). Not to
    // be called by users.
    SynthConfig() : frequency_table_(kNumberOfFrequencies) {};

    // The frequencie table based on equal-tempered scale with
    // middle C at index 48 (i.e. frequencies[48]). 
    vector<double> frequency_table_;
    int32_t sampling_rate_;
    // Maximum representable frequency according to Nyquist
    float nyquist_limit_;
    // Phase increment per sample for signals at 1 Hz. Mathematically this
    // is simply 2*Pi / sample_rate_.
    double phase_increment_per_sample_;
    // Pre-calculated multipler for frequency to table index
    // (tableLength/sampleRate)
    double frqTI;
    // Pre-calculated multipler for radians to table index
    // (tableLength/twoPI)
    double radTI;
    // Maximum phase increment for wavetables (ftableLength/2)
    double maxIncrWT;
    // Wave table length
    double ftableLength;
    // Wave table length as integer
    int32_t itableLength;

};

#endif /* _SYNTH_CONFIG_H_ */
