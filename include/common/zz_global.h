//=============================================================
// FILE:
//   include/zz_global.h
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//   Global variables - declarations. For definitions and 
//   description go to src/common/zz_global.cc
//
// License: GNU GPL v2.0 
//=============================================================

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <cstdint>

using namespace std;

//=============================================================
// Floating point globals
//=============================================================
extern const double kTwelthRootOfTwo;

extern const double kPi;
extern const double kTwoPi;

extern const double kNoteC0;

//=============================================================
// Fixed point globals 
//=============================================================
//-------------------------------------------------------------
// Wave File Related
//-------------------------------------------------------------
extern const int kNumberOfBitsPerByte;
extern const int8_t kNumberOfBitsPerSample;

extern const int8_t kWaveFileHeaderSize;

extern const int32_t kRiffChunkId;

extern const int32_t  kRiffFormat;

extern const int32_t kFmtSubchunkId;

extern const int32_t kDataSubchunkId;

extern const int32_t kPcmSubchunk1Size;

extern const int16_t kPcmAudioFormat;

extern const int16_t kNumberOfChannelsMono;
extern const int16_t kNumberOfChannelsStereo;

//-------------------------------------------------------------
// SynthConfig 
//-------------------------------------------------------------
extern const size_t kNumberOfFrequencies;

//-------------------------------------------------------------
// General 
//-------------------------------------------------------------
extern const int32_t kCdSampleRate;

extern const int8_t kSizeTwoBytes;
extern const int8_t kSizeFourBytes;

#endif /* _GLOBAL_H_ */
