//=============================================================
// FILE:
//   /src/zz_SynthConfig.cc
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//   The implementation of the SynthConfig class.
//
// License: GNU GPL v2.0 
//=============================================================

#include "common/synth_config.h"
#include "common/zz_global_include.h"

using namespace std;

//=============================================================
// Class: SynthConfig
//=============================================================
//--------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//--------------------------------------------------------------
// None

//--------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//--------------------------------------------------------------
SynthConfig& SynthConfig::getInstance()
{   
    // The only instance of the SynthConfig class. Guaranteed to be
    // lazy initialised and destroyed correctly.
    static SynthConfig instance;

    return instance;
}

void SynthConfig::Init(uint32_t sampling_rate_arg)
{
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

    sampling_rate_  = sampling_rate_arg;
    nyquist_limit_  = sampling_rate_ >> 1;
    phase_increment_per_sample_ = kTwoPi / sampling_rate_;
}


//--------------------------------------------------------------
// 3. ACCESSORS
//--------------------------------------------------------------
double SynthConfig::frequency_table(vector<double>::size_type  pitch) const
{
    return frequency_table_[pitch];
}

uint32_t SynthConfig::sampling_rate() const 
{
    return sampling_rate_;
}

double SynthConfig::phase_increment_per_sample() const
{
    return phase_increment_per_sample_;
}
