//========================================================================
// FILE:
//   src/global/global_variables.cc
//
// AUTHOR:
//   zimzum@github
//
// DESCRIPTION:
//   Implementation of the global variables used in the synthesiser.
//   All submodules are free to use this file.
//
//  TODO: Turn this into a namespace!
//
// License: GNU GPL v2.0
//========================================================================

#include "global/global_variables.h"

using namespace std;

//========================================================================
// Floating poing globals
//========================================================================
const double kTwelthRootOfTwo = 1.0594630943593;

// Pi and 2*Pi
const double kPi = 3.14159265358979;
const double kTwoPi = 6.28318530717958;

// Epsilon for floating point comparisons. Very carefull here: is this value
// accurate enough for you!?
extern const double kEps = 1e-14;

// Notes: C0
const double kNoteC0 = 16.35;

//========================================================================
// Fixed point globals
//========================================================================
//------------------------------------------------------------------------
// Wave File Related
//------------------------------------------------------------------------
const uint16_t kNumberOfBitsPerByte = 8;
const uint8_t kNumberOfBitsPerSample = 16;

// The size of the header in the Canonical Wave File format. See
// WaveFile.h for description of this format. This is basically
// the size of the whole file minus:
//      - 8 bytes not included in this count (ChunkId and ChunkSize)
//      - size of data (sound samples) in bytes.
const uint8_t kWaveFileHeaderSize = 36;

// Contains the letters "RIFF" in ASCII in little-endian form,
// so that on little-endia machine (i.e. x86) it will be saved in
// big-endian form, as per the format
const uint32_t kRiffChunkId = 0x46464952;

// Contains the letters "WAVE" in ASCII in little-endian form,
// so that on little-endia machine (i.e. x86) it will be saved in
// big-endian form, as per the format
const uint32_t kRiffFormat = 0x45564157;

// Contains the letters "fmt " in ASCII in little-endian form,
// so that on little-endia machine (i.e. x86) it will be saved in
// big-endian form, as per the format
const uint32_t kFmtSubchunkId = 0x20746d66;

// Contains the letters "data" in ASCII in little-endian form,
// so that on little-endia machine (i.e. x86) it will be saved in
// big-endian form, as per the format
const uint32_t kDataSubchunkId = 0x61746164;

// 16 for PCM
const uint32_t kPcmSubchunk1Size = 16;

// 1 for pcm
const uint16_t kPcmAudioFormat = 1;

const uint16_t kNumberOfChannelsMono = 1;
const uint16_t kNumberOfChannelsStereo = 2;

//------------------------------------------------------------------------
// SynthConfig
//------------------------------------------------------------------------
// SynthConfig contains pre-calculated frequencies for various notes.
// This number specifies how many of those it contains.
const size_t kNumberOfFrequencies = 128;

//------------------------------------------------------------------------
// General
//------------------------------------------------------------------------
const uint32_t kCdSampleRate = 44100;

extern const uint8_t kSizeTwoBytes = 2;
extern const uint8_t kSizeFourBytes = 4;
