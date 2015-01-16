//=============================================================
//  FILE:
//    include/zz_WavFile.h
//
//  AUTHOR:
//    zimzum@github 
//
//  DESCRIPTION:
//    The definition of the WaveFile class.
//
//  License: GNU GPL v2.0 
//=============================================================

#ifndef _WAVEFILE_H_
#define _WAVEFILE_H_

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
class WaveFile
{
public:
    explicit WaveFile(int8_t number_of_seconds);
    ~WaveFile();

    void SaveBufferToFile(const std::string& file_name);
private:
    explicit WaveFile(const WaveFile& rhs);
    WaveFile& operator=(const WaveFile &rhs);
    
    int16_t *p_sample_buffer_;
    int8_t signal_length_in_seconds;

    //---------------------------------------------------------
    // The following canonical WAVE file format is implemented :
    // (c.f. https://ccrma.stanford.edu/courses/422/projects/WaveFormat/)
    //
    //  Field Size       Field name
    //  (bytes)
    //              +-------------------+    ---
    //     4        | ChunkId           |       |
    //              |-------------------|       |
    //     4        | ChunkSize         |       |---> The "RIFF" chunk
    //              |-------------------|       |     descriptor
    //     4        | Format            |       |
    //              +-------------------+    ---
    //     4        | Subchunk1Id       |       | 
    //              |-------------------|       |
    //     4        | Subchunk1Size     |       |
    //              |-------------------|       |
    //     2        | AudioFormat       |       |
    //              |-------------------|       |
    //     2        | NumChannels       |       | 
    //              |-------------------|       | ---> The "fmt" sub-chunk
    //     4        | SampleRate        |       |
    //              |-------------------|       |
    //     4        | ByteRate          |       |
    //              |-------------------|       |
    //     2        | BlockAlign        |       |
    //              |-------------------|       |
    //     2        | BitsPerSample     |       |
    //              +-------------------+   ---
    //     4        | Subchunk2Id       |       |
    //              |-------------------|       |
    //     4        | Subchunk2Size     |       | ---> The "data" sub-chuk
    //              |-------------------|       |
    //    (.)       | data              |       |
    //              +-------------------+   ---
    //
    //---------------------------------------------------------
    int32_t chunk_id_;
    // The size of the rest of the chunk following this number. This is
    // the size of the entire WAVE file in bytes minus 8 bytes for the
    // two fields not included in this count: chunk_id_ and chunk_size_.
    int32_t chunk_size_;
    int32_t format_;
    int32_t subchunk_1_id;
    int32_t subchunk_1_size_;
    int16_t audio_format_;
    int16_t num_channels_;
    int32_t sample_rate_;
    int32_t byte_rate_;
    // The number of bytes for one sample including all channels.
    int16_t block_align_;
    int16_t bits_per_sample_;
    int32_t subchunk_2_id_;
    int32_t subchunk_2_size_;
};

#endif /* #define _WAVEFILE_H_ */
