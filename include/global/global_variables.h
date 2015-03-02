//=============================================================
// FILE:
//   global/global_variables.h
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//   Global variables - declarations. For definitions and 
//   thorough descriptions go to src/global/global_variables.cc
//
// License: GNU GPL v2.0 
//=============================================================

#ifndef GLOBAL_H
#define GLOBAL_H

#include <cstdint>

//=============================================================
// Floating point globals
//=============================================================
extern const double kTwelthRootOfTwo;

extern const double kPi;
extern const double kTwoPi;

extern const double kNoteC0;

extern const double kEps;

//=============================================================
// Fixed point globals 
//=============================================================
//-------------------------------------------------------------
// Wave File Related
//-------------------------------------------------------------
extern const uint16_t kNumberOfBitsPerByte;
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
extern const std::size_t kNumberOfFrequencies;

//-------------------------------------------------------------
// General 
//-------------------------------------------------------------
extern const uint32_t kCdSampleRate;

extern const uint8_t kSizeTwoBytes;
extern const uint8_t kSizeFourBytes;

#endif /* _GLOBAL_H_ */
