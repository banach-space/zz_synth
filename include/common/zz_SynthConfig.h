//=============================================================
// FILE:
//   /include/zz_SynthConfig.h
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//   The definition of the zz_SynthConfig class - configuration
//   class for the zz_synth library.
//
// License: GNU GPL v2.0 
//=============================================================

#ifndef _SYNTH_CONFIG_H_
#define _SYNTH_CONFIG_H_

#include "zz_global_include.h"
#include<cmath>

class zz_SynthConfig
{
public:
    // Sampling rate
    float sampleRate;
    // Maximum frequency (Nyquist limit)
    float nyquist;
    // Sample rate as integer
    int32_t isampleRate;
    // Pre-calculated multipler for frequency to radians
    // (twoPI/sampleRate)
    double frqRad;
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

    //-------------------------------------------------------------
    //  NAME:
    //      getInstance()  
    //
    //  DESCRIPTION:
    //      Returns a reference to the only instance of this class.
    //      Performs basic intialisation of the member variables.
    //  INPUT:
    //      none
    //  OUTPUT:
    //      Reference to the only possible instance of this class
    //      initialised as required.
    // 
    //--------------------------------------------------------------
    static zz_SynthConfig& getInstance();

    void Init(int32_t sr = 44100, int32_t tl = 16384);

    //-------------------------------------------------------------
    //  NAME:
    //      frequency_table()  
    //
    //  DESCRIPTION:
    //      Converts pitch index to frequency. The frequency table is 
    //      built in the constructor based on an equal-tempered scale with
    //      middle C at index 48. Negative pitch values are allowed
    //      but are calculated directly using the equation for
    //      equal-tempered  tuning:
    //          f_n = (f0 * 2^n/12)
    //      where f_n is the desired frequencie (determined by index n)
    //      and f0 is the initial freq. set here to C0.
    //
    //      This method is an extended accesor.
    //  INPUT:
    //      pitch - pitch index 
    //  OUTPUT:
    //      frequency that corresponds to the passed pitch index
    // 
    //--------------------------------------------------------------
    double frequency_table(int pitch);

private:
    // Block direct access to constructors - this class is a singleton
    zz_SynthConfig() {};
    zz_SynthConfig(zz_SynthConfig const& copy);
    zz_SynthConfig& operator=(zz_SynthConfig const& copy);

    // The frequencie table based on equal-tempered scale with
    // middle C at index 48 (i.e. frequencies[48]). 
    double frequency_table_[128];

};

#endif /* _SYNTH_CONFIG_H_ */
