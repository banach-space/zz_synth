//=============================================================
// FILE:
//   /src/zz_SynthConfig.cc
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//   The implementation of the SynthConfig class - configuration
//   class for the zz_synth library.
//
// License: GNU GPL v2.0 
//=============================================================

#include "common/synth_config.h"
#include "common/zz_global_include.h"

//=============================================================
// Public methods
//=============================================================
void zz_SynthConfig::Init(int32_t sampling_rate)
{
    // !!! TODO Commenting!!!
    sampling_rate_  = sampling_rate;
    nyquist_limit_  = sampling_rate_ >> 1;
    phase_increment_per_sample_ = kTwoPi / sampling_rate_;
    //frqRad = twoPI / (double) sampleRate;
    //frqTI = ftableLength / (double) sampleRate;
    //radTI = ftableLength / twoPI;
}

zz_SynthConfig& zz_SynthConfig::getInstance()
{   
    // The only instance of the SynthConfig class. Guaranteed to be
    // lazy initialised and destroyed correctly.
    static zz_SynthConfig instance;

    // Initialise frequency_table_.
    double frequency = kNoteC0;

    for (std::size_t i = 0; i < 128; i++)
    {
        instance.frequency_table_[i] = frequency;
        frequency *= kTwelthRootOfTwo;
    }

    return instance;
}

double zz_SynthConfig::frequency_table(int pitch)
{
    if (pitch < 0 || pitch > 127)
    {
        return frequency_table_[0] * pow(kTwelthRootOfTwo, pitch);
    }

    return frequency_table_[pitch];
}

//=============================================================
// Protected methods
//=============================================================

//=============================================================
// Private methods
//=============================================================
