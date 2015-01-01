//=============================================================
//  FILE:
//    include/zz_WavFile.h
//
//  AUTHOR:
//    zimzum@github 
//
//  DESCRIPTION:
//    The definition of the zz_WavFile class.
//
//  License: GNU GPL v2.0 
//=============================================================

#ifndef _WAVFILE_H_
#define _WAVFILE_H_

//=============================================================
//  Private constants
//=============================================================
// Lenght of Chunk ID in bytes
const int8_t kChunkIDlength = 4;

//=============================================================
//Public defines 
//=============================================================
/* None */

//=============================================================
//Private data structures
//=============================================================
// A header of a chunk in a RIFF file.
class RiffChunkHDR
{
    private:
        // The chunk ID
        int8_t  chunkId[kChunkIDlength];
        // The chunk size (little-endian byte order)
        int32_t chunkSize;
};

// Format chunk.
class FmtDataHDR
{
    private:
        // Format code 1 = PCM, 3 = IEEE float
        int16_t fmtCode;
        // Number of channles, 1 = mono, 2 = stereo
        int16_t channels;
        // Sample rate (44100Hz)
        int32_t sampleRate;
        // Bytes per second (samplerate * align)
        int32_t avgbps;
        // Sample alignment (channels*bits)/8
        int16_t align;
        // Bits per sample
        int16_t bits;
};

// Simplified WAVE file header. The chunks and format are combined
// into a single structure.
class WavHDR
{
    private:
        // 'RIFF' chunk
        RiffChunkHDR riff;
        // 'WAVE' type of file
        int8_t  waveType[4];
        // 'fmt ' chunk
        RiffChunkHDR fmt;           
        FmtDataHDR fmtdata;
        // 'data' chunk
        RiffChunkHDR data;      
};

/*=============================================================
  Public data structures
  =============================================================*/
class WavFile
{

};

#endif /* #define _WAVFILE_H_ */
