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
extern const uint32_t kNumberOfBitsPerByte;
extern const uint8_t kNumberOfBitsPerSample;

extern const uint8_t kWaveFileHeaderSize;

extern const uint32_t kRiffChunkId;

extern const uint32_t  kRiffFormat;

extern const uint32_t kFmtSubchunkId;

extern const uint32_t kDataSubchunkId;

extern const uint32_t kPcmSubchunk1Size;

extern const uint16_t kPcmAudioFormat;

extern const uint16_t kNumberOfChannelsMono;
extern const uint16_t kNumberOfChannelsStereo;

//-------------------------------------------------------------
// SynthConfig 
//-------------------------------------------------------------
extern const size_t kNumberOfFrequencies;

//-------------------------------------------------------------
// General 
//-------------------------------------------------------------
extern const uint32_t kCdSampleRate;

extern const uint8_t kSizeTwoBytes;
extern const uint8_t kSizeFourBytes;

#endif /* _GLOBAL_H_ */
