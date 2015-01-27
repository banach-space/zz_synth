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
// Class: SynthConfig
//=============================================================
//--------------------------------------------------------------
// Constructors/Destructors/Assignment Operators
//--------------------------------------------------------------
// None

//--------------------------------------------------------------
// User interface 
//--------------------------------------------------------------
SynthConfig& SynthConfig::getInstance()
{   
    // The only instance of the SynthConfig class. Guaranteed to be
    // lazy initialised and destroyed correctly.
    static SynthConfig instance;

    return instance;
}

void SynthConfig::Init(const int32_t sampling_rate)
{
    // Initialise frequency_table_.
    double frequency = kNoteC0;

    for (
            vector<double>::iterator it = frequency_table_.begin();
            it != frequency_table_.end();
            ++it
            )
    {
        *it = frequency;
        frequency *= kTwelthRootOfTwo;
    }

    sampling_rate_  = sampling_rate;
    nyquist_limit_  = sampling_rate_ >> 1;
    phase_increment_per_sample_ = kTwoPi / sampling_rate_;
}


//--------------------------------------------------------------
// Accessors
//--------------------------------------------------------------
double SynthConfig::frequency_table(const int pitch) const
{
    return frequency_table_[pitch];
}
int32_t SynthConfig::sampling_rate() const 
{
    return sampling_rate_;
}

double SynthConfig::phase_increment_per_sample() const
{
    return phase_increment_per_sample_;
}
