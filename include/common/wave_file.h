//=============================================================
//  FILE:
//    include/zz_WavFile.h
//
//  AUTHOR:
//    zimzum@github 
//
//  DESCRIPTION:
//      The definition of the WaveFile, WaveFileIn and WaveFileOut classes.
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
//
// DESCRIPTION:
//  Represents a general WAVE file. Contains a canonical WAVE file
//  header. It's a pure virtual class.
//=============================================================
class WaveFile
{
public:
    //--------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
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
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------
    // None

    //--------------------------------------------------------------
    // 3. ACCESSORS
    //--------------------------------------------------------------
    uint32_t chunk_id();
    uint32_t chunk_size();
    uint32_t format();
    uint32_t subchunk_1_id();
    uint32_t subchunk_1_size();
    uint16_t audio_format();
    uint16_t num_channels();
    uint32_t sample_rate();
    uint32_t byte_rate();
    uint16_t block_align();
    uint16_t bits_per_sample();
    uint32_t subchunk_2_id();
    uint32_t subchunk_2_size();

protected:
    //--------------------------------------------------------------
    // 4. MUTATORS
    //--------------------------------------------------------------
    void set_chunk_id(uint32_t value);
    void set_chunk_size(uint32_t value);
    void set_format(uint32_t value);
    void set_subchunk_1_id(uint32_t value);
    void set_subchunk_1_size(uint32_t value);
    void set_audio_format(uint16_t value);
    void set_num_channels(uint16_t value);
    void set_sample_rate(uint32_t value);
    void set_byte_rate(uint32_t value);
    void set_block_align(uint16_t value);
    void set_bits_per_sample(uint16_t value);
    void set_subchunk_2_id(uint32_t value);
    void set_subchunk_2_size(uint32_t value);

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

    uint32_t chunk_id_;
    // The size of the rest of the chunk following this number. This is
    // the size of the entire WAVE file in bytes minus 8 bytes for the
    // two fields not included in this count: chunk_id_ and chunk_size_.
    uint32_t chunk_size_;
    uint32_t format_;
    uint32_t subchunk_1_id_;
    uint32_t subchunk_1_size_;
    uint16_t audio_format_;
    uint16_t num_channels_;
    uint32_t sample_rate_;
    uint32_t byte_rate_;
    // The number of bytes for one sample including all channels.
    uint16_t block_align_;
    uint16_t bits_per_sample_;
    uint32_t subchunk_2_id_;
    uint32_t subchunk_2_size_;
    
};

//=============================================================
// CLASS: WaveFileOut 
//
// DESCRIPTION:
//  Represents an output WAVE file. Implemented for writing WAVE
//  files to disk. Does not hold output samples. These are always
//  passed in an input vector. 
//=============================================================
class WaveFileOut: public WaveFile
{
public:
    //--------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------
    explicit WaveFileOut(size_t number_of_seconds);
    ~WaveFileOut() = default;

    //--------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
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
    void SaveBufferToFile(const string& file_name, vector<int16_t> &samples);

};

//=============================================================
//  CLASS: WaveFileIn 
//
//
// DESCRIPTION:
//  Represents an input WAVE file. Implemented for reading WAVE
//  files from disk. Does not hold the input samples. Instead it reads
//  them and returns to the user when requested.
//=============================================================
class WaveFileIn: public WaveFile
{
public:
    //--------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------
    explicit WaveFileIn() {};
    ~WaveFileIn() = default;

    //--------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
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
//
// DESCRIPTION:
//  Exception class. Thrown when the number of samples passed is
//  smaller than expected.
//=============================================================
class BufferToSmallException : public exception
{
    virtual const char* what() const throw();
};
#endif /* #define _WAVEFILE_H_ */
