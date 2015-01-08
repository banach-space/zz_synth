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

#include "common/zz_SynthConfig.h"
#include "common/zz_global_include.h"

#include "common/zz_global_include.h"

void zz_SynthConfig::Init(int32_t sr, int32_t tl)
{
    sampleRate = (float) sr;
    nyquist = sampleRate * 0.5;
    isampleRate = sr;
    itableLength = tl;
    ftableLength = (double) tl;
    maxIncrWT = ftableLength * 0.5;
    //frqRad = twoPI / (double) sampleRate;
    frqTI = ftableLength / (double) sampleRate;
    //radTI = ftableLength / twoPI;
}

