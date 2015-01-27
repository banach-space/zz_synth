//=============================================================
//  FILE:
//    include/zz_WavFile.h
//
//  AUTHOR:
//    zimzum@github 
//
//  DESCRIPTION:
//    The definition of the WaveFileOut class.
//
//  License: GNU GPL v2.0 
//=============================================================

#ifndef _WAVEFILE_H_
#define _WAVEFILE_H_

#include "zz_global_include.h" 
#include <vector>
#include <exception>

//=============================================================
// CLASS: WaveFile
//=============================================================
class WaveFile
{
public:
    //--------------------------------------------------------------
    //  -= CONSTRUCTORS/DESTRUCTORS/ASSIGNMENT OPERATORS =-
    //--------------------------------------------------------------
    // Make this class pure abstract and block copy constructor, assignment
    // operator and the corresponding move operators.
    explicit WaveFile();
    virtual ~WaveFile() = 0;
    explicit WaveFile(const WaveFile& rhs) = delete;
    explicit WaveFile(WaveFile&& rhs) = delete;
    WaveFile& operator=(const WaveFile &rhs) = delete;
    WaveFile& operator=(WaveFile&& rhs) = delete;

    //--------------------------------------------------------------
    // -= ACCESSORS =-
    //--------------------------------------------------------------
    int32_t chunk_id();
    int32_t chunk_size();
    int32_t format();
    int32_t subchunk_1_id();
    int32_t subchunk_1_size();
    int16_t audio_format();
    int16_t num_channels();
    int32_t sample_rate();
    int32_t byte_rate();
    int16_t block_align();
    int16_t bits_per_sample();
    int32_t subchunk_2_id();
    int32_t subchunk_2_size();

protected:
    //--------------------------------------------------------------
    //  -= MUTATORS =-
    //--------------------------------------------------------------
    void set_chunk_id(int32_t value);
    void set_chunk_size(int32_t value);
    void set_format(int32_t value);
    void set_subchunk_1_id(int32_t value);
    void set_subchunk_1_size(int32_t value);
    void set_audio_format(int16_t value);
    void set_num_channels(int16_t value);
    void set_sample_rate(int32_t value);
    void set_byte_rate(int32_t value);
    void set_block_align(int16_t value);
    void set_bits_per_sample(int16_t value);
    void set_subchunk_2_id(int32_t value);
    void set_subchunk_2_size(int32_t value);

private:
    //---------------------------------------------------------
    // The following canonical WAVE file format is implemented :
    // (see http://soundfile.sapp.org/doc/WaveFormat/ )
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
    int32_t subchunk_1_id_;
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

//=============================================================
//  CLASS: WaveFileOut 
//=============================================================
class WaveFileOut: public WaveFile
{
public:
    //--------------------------------------------------------------
    //  -= CONSTRUCTORS/DESTRUCTORS/ASSIGNMENT OPERATORS =-
    //--------------------------------------------------------------
    explicit WaveFileOut(size_t number_of_seconds);
    ~WaveFileOut() = default;

    //--------------------------------------------------------------
    //  -= INTERFACE =-
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    //  NAME:
    //      SaveBufferToFile()  
    //
    //  DESCRIPTION:
    //      Saves the content of this file to the specified physical file.
    //      The data samples are passed as argument.
    //  INPUT:
    //      The name of the file to write to and the data samples.
    //  OUTPUT:
    //      Vector containing read samples.
    // 
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    void SaveBufferToFile(const string& file_name, vector<int16_t> &samples);

};

//=============================================================
//  CLASS: WaveFileIn 
//=============================================================
class WaveFileIn: public WaveFile
{
public:
    //--------------------------------------------------------------
    //  -= CONSTRUCTORS/DESTRUCTORS/ASSIGNMENT OPERATORS =-
    //--------------------------------------------------------------
    explicit WaveFileIn() {};
    ~WaveFileIn() = default;

    //--------------------------------------------------------------
    //  -= INTERFACE =-
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    //  NAME:
    //      ReadBufferFromFile()  
    //
    //  DESCRIPTION:
    //      Reads a WaveFile. The WAVE header is saved in the appropriate
    //      variables in the base clase. The audio samples are read into
    //      a vector and returned. The Wave file is expected to be in the
    //      canonical WAVE format as described above (see also:
    //      http://soundfile.sapp.org/doc/WaveFormat/).
    //  INPUT:
    //      The name of the file to read.
    //  OUTPUT:
    //      Vector containing read samples.
    //  EXCEPTIONS:
    //      BufferToSmallException, std::ofstream::failure
    // 
    //--------------------------------------------------------------
    std::vector<int16_t> ReadBufferFromFile(const string& file_name);
};

//=============================================================
//  CLASS: BufferToSmallException 
//=============================================================
class BufferToSmallException : public exception
{
    virtual const char* what() const throw();
};
#endif /* #define _WAVEFILE_H_ */
