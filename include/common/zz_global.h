//=============================================================
// FILE:
//   include/zz_global.h
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//   Global variables - declarations. For definitions go to
//   src/common/zz_global.cc
//
// License: GNU GPL v2.0 
//=============================================================

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <cstdint>

//=============================================================
// Floating point globals
//=============================================================
extern const double kTwelthRootOfTwo;

// Pi and 2*Pi
extern const double kPi;
extern const double kTwoPi;

// Notes
extern const double kNoteC0;

//=============================================================
// Fixed point globals 
//=============================================================
extern const int kNumberOfBitsPerByte;
extern const int8_t kNumberOfBitsPerSample;

// Contains the letters "RIFF" in ASCII big-endian form
extern const int32_t kRiffChunkId;


// Contains the letters "WAVE" in ASCII big-endian form
extern const int32_t  kRiffFormat;

// Contains the letters "fmt" in ASCII big-endian form
extern const int32_t kFmtSubchunkId;

// Contains the letters "data" in ASCII big-endian form
extern const int32_t kDataSubchunkId;

// 16 for PCM
extern const int32_t kPcmSubchunk1Size;

// 1 for pcm
extern const int16_t kPcmAudioFormat;

extern const int16_t kNumberOfChannelsMono;
extern const int16_t kNumberOfChannelsStereo;

extern const int32_t kCdSampleRate;

extern const int8_t kSizeTwoBytes;
extern const int8_t kSizeFourBytes;

#endif /* _GLOBAL_H_ */
