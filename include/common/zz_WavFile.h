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

#include "zz_global_include.h"
//=============================================================
//  Private constants
//=============================================================
// None

//=============================================================
//Public defines 
//=============================================================
// None

//=============================================================
//Private data structures
//=============================================================
// None

/*=============================================================
  Public data structures
  =============================================================*/
class WavFile
{
    public:
        explicit WavFile();
        ~WavFile();

        void AllocateBuffer(int8_t numberOfSeconds);
        void SaveBufferToFile(std::string fileName);
    private:
        explicit const WavFile(const WavFile &rhs);
        WavFile& operator=(const WavFile&rhs);
        
        int16_t *sample_Buffer_;
        int8_t signal_length_in_seconds;

        // The chunk ID is "RIFF" (big-endian form)
        static const int32_t  kCchunkId = 0x52494646;
        // Chunk size is equal to: (file_size - 8) (saved in little-endian byte order)
        int32_t chunk_size_;
        // RIFF type is "WAVE" (big-endian form)
        static const int32_t  kRiffType = 0x57415645;
        // The subchunk ID is "fmt" in big-endian form
        static const int32_t  kSubChunk1Id = 0x666d7420;
        // Subchunk size is (16 + format bytes) for PCM. Not using
        // extra format bytes so setting to 16.
        int32_t sub_chunk_1_size_ = 16;
        // Format code 1 = PCM, 3 = IEEE float
        static const int16_t kAudioFormat = 1;
        // Number of channles, 1 = mono, 2 = stereo
        static const int16_t kNumChannels = 1;
        // Sample rate (44100Hz)
        static const int32_t kSampleRate = 44100;
        // Bytes per second (sampleRate * numChannels * bytesPerSample_)
        int32_t byte_rate_ = 44100 * 1 * 2;
        // Sample alignment (channels*bits)/8
        int16_t block_align_ = num_channels_ * bits_per_sample / 8;
        // Bits per sample
        int16_t bits_per_sample_ = 16;
        // The subchunk id is "data" in big-endia form
        static const int32_t kSubChunk2Id = 0x64617461;
        // Subchunk size is (16 + format bytes) for PCM. Not using
        // extra format bytes so setting to 16.
        int32_t sub_chunk_2_size_ = number_of_samples * num_channels_ * bits_per_sample_ / 8;
};

#endif /* #define _WAVFILE_H_ */
