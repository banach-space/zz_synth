//=============================================================
// FILE:
//   /src/zz_WaveFileOut.cc
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//   The implementation of the WaveFileOut class. 
//
// License: GNU GPL v2.0 
//=============================================================

#include "common/wave_file.h"

//=============================================================
// Public methods
//=============================================================
//-------------------------------------------------------------
// Class: WaveFile
//-------------------------------------------------------------
// 1. Constructors + destructors
WaveFile::WaveFile()
{
    // 1. Member variables that can be initialised independently
    chunk_id_       = kRiffChunkId;
    format_         = kRiffFormat;
    subchunk_1_id_  = kFmtSubchunkId;
    subchunk_1_size_= kPcmSubchunk1Size;
    audio_format_   = kPcmAudioFormat;
    num_channels_   = kNumberOfChannelsMono;
    sample_rate_    = kCdSampleRate;
    bits_per_sample_= kNumberOfBitsPerSample;
    subchunk_2_id_  = kDataSubchunkId;

    // 2. Member variables that dependend on previously defined variables
    // subchunk_2_size is 0 at this stage, as there are no data samples
    subchunk_2_size_ = 0; 
    chunk_size_ = kWaveFileHeaderSize + subchunk_2_size_;
    byte_rate_  = sample_rate_ * num_channels_ * bits_per_sample_
        / kNumberOfBitsPerByte;
    block_align_= num_channels_ * bits_per_sample_ / kNumberOfBitsPerByte;
}

// 3. Accessors
int32_t WaveFile::chunk_id() {return chunk_id_;}
int32_t WaveFile::chunk_size() {return chunk_size_;}
int32_t WaveFile::format()    {return format_;}
int32_t WaveFile::subchunk_1_id() {return subchunk_1_id_;}
int32_t WaveFile::subchunk_1_size() {return subchunk_1_size_;}
int16_t WaveFile::audio_format() {return audio_format_;}
int16_t WaveFile::num_channels() {return num_channels_;}
int32_t WaveFile::sample_rate() {return sample_rate_;}
int32_t WaveFile::byte_rate() {return byte_rate_;}
int16_t WaveFile::block_align() {return block_align_;}
int16_t WaveFile::bits_per_sample() {return bits_per_sample_;}
int32_t WaveFile::subchunk_2_id() {return subchunk_2_id_;}
int32_t WaveFile::subchunk_2_size() {return subchunk_2_size_;}

// 4. Mutators
void WaveFile::set_chunk_id(int32_t value) {chunk_id_ = value;}
void WaveFile::set_chunk_size(int32_t value) {chunk_size_ = value;}
void WaveFile::set_format(int32_t value) {format_ = value;}
void WaveFile::set_subchunk_1_id(int32_t value) {subchunk_1_id_ = value;}
void WaveFile::set_subchunk_1_size(int32_t value) {subchunk_1_size_ = value;}
void WaveFile::set_audio_format(int16_t value) {audio_format_ = value;}
void WaveFile::set_num_channels(int16_t value) {num_channels_ = value;}
void WaveFile::set_sample_rate(int32_t value) {sample_rate_ = value;}
void WaveFile::set_byte_rate(int32_t value) {byte_rate_ = value;}
void WaveFile::set_block_align(int16_t value) {block_align_ = value;}
void WaveFile::set_bits_per_sample(int16_t value) {bits_per_sample_ = value;}
void WaveFile::set_subchunk_2_id(int32_t value) {subchunk_2_id_ = value;}
void WaveFile::set_subchunk_2_size(int32_t value) {subchunk_2_size_ = value;}

//-------------------------------------------------------------
// Class: WaveFileOut
//-------------------------------------------------------------
WaveFileOut::WaveFileOut(std::size_t number_of_seconds)
{
    std::size_t temp_size;

    temp_size = WaveFile::sample_rate() * WaveFile::num_channels()
              * WaveFile::bits_per_sample() / kNumberOfBitsPerByte;

    WaveFile::set_subchunk_2_size(temp_size * number_of_seconds);
}

void WaveFileOut::SaveBufferToFile(
    const std::string &file_name, 
    std::vector<int16_t> &samples)
{
    int32_t temp32;
    int16_t temp16;

    std::ofstream output_file;
    output_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // The size of the 2nd chunk is the number of bytes for all samples
    WaveFile::set_subchunk_2_size(samples.size() * sizeof(int16_t));

    try
    {
        // Open the file
        output_file.open(file_name, std::ifstream::binary);

        // Write in binary format to the file so that correct Wave file is
        // constructed
        temp32 = WaveFile::chunk_id();
        output_file.write(
                reinterpret_cast<const char*>(&temp32),
                kSizeFourBytes);

        temp32 = WaveFile::chunk_size();
        output_file.write(
                reinterpret_cast<const char*>(&temp32),
                kSizeFourBytes);

        temp32 = WaveFile::format();
        output_file.write(
                reinterpret_cast<const char*>(&temp32), 
                kSizeFourBytes);

        temp32 = WaveFile::subchunk_1_id();
        output_file.write(
                reinterpret_cast<const char*>(&temp32), 
                kSizeFourBytes);

        temp32 = WaveFile::subchunk_1_size();
        output_file.write(
                reinterpret_cast<const char*>(&temp32), 
                kSizeFourBytes);

        temp16 = WaveFile::audio_format();
        output_file.write(
                reinterpret_cast<const char*>(&temp16), 
                kSizeTwoBytes);

        temp16 = WaveFile::num_channels();
        output_file.write(
                reinterpret_cast<const char*>(&temp16), 
                kSizeTwoBytes);

        temp32 = WaveFile::sample_rate();
        output_file.write(
                reinterpret_cast<const char*>(&temp32), 
                kSizeFourBytes);

        temp32 = WaveFile::byte_rate();
        output_file.write(
                reinterpret_cast<const char*>(&temp32), 
                kSizeFourBytes);

        temp16 = WaveFile::block_align();
        output_file.write(
                reinterpret_cast<const char*>(&temp16), 
                kSizeTwoBytes);

        temp16 = WaveFile::bits_per_sample();
        output_file.write(
                reinterpret_cast<const char*>(&temp16), 
                kSizeTwoBytes);

        temp32 = WaveFile::subchunk_2_id();
        output_file.write(
                reinterpret_cast<const char*>(&temp32), 
                kSizeFourBytes);

        temp32 = WaveFile::subchunk_2_size();
        output_file.write(
                reinterpret_cast<const char*>(&temp32), 
                kSizeFourBytes);

        output_file.write(
                reinterpret_cast<const char*>(&samples[0]),  
                temp32 );

        output_file.close();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "Exception opening/reading/closing file\n";
    }
}

//-------------------------------------------------------------
// Class: WaveFileOut
//-------------------------------------------------------------
std::vector<int16_t>& 
WaveFileIn::ReadBufferFromFile(const std::string& file_name)
{
    int32_t temp32;
    int16_t temp16;
    std::size_t number_of_samples;

    std::ifstream input_file;
    input_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // Open the file
        input_file.open(file_name, std::ifstream::binary);

        // Read from the binary file assume it's in the cannoncial Wave
        // format
        input_file.read(
                reinterpret_cast<char*>(&temp32), 
                kSizeFourBytes);
        WaveFile::set_chunk_id(temp32);

        input_file.read(
                reinterpret_cast<char*>(&temp32), 
                kSizeFourBytes);
        WaveFile::set_chunk_size(temp32);

        input_file.read(
                reinterpret_cast<char*>(&temp32), 
                kSizeFourBytes);
        WaveFile::set_format(temp32);

        input_file.read(
                reinterpret_cast<char*>(&temp32), 
                kSizeFourBytes);
        WaveFile::set_subchunk_1_id(temp32);

        input_file.read(
                reinterpret_cast<char*>(&temp32), 
                kSizeFourBytes);
        WaveFile::set_subchunk_1_size(temp32);

        input_file.read(
                reinterpret_cast<char*>(&temp16), 
                kSizeTwoBytes);
        WaveFile::set_audio_format(temp16);

        input_file.read(
                reinterpret_cast<char*>(&temp16), 
                kSizeTwoBytes);
        WaveFile::set_num_channels(temp16);

        input_file.read(
                reinterpret_cast<char*>(&temp32), 
                kSizeFourBytes);
        WaveFile::set_sample_rate(temp32);

        input_file.read(
                reinterpret_cast<char*>(&temp32), 
                kSizeFourBytes);
        WaveFile::set_byte_rate(temp32);

        input_file.read(
                reinterpret_cast<char*>(&temp16), 
                kSizeTwoBytes);
        WaveFile::set_block_align(temp16);

        input_file.read(
                reinterpret_cast<char*>(&temp16), 
                kSizeTwoBytes);
        WaveFile::set_bits_per_sample(temp16);

        input_file.read(
                reinterpret_cast<char*>(&temp32), 
                kSizeFourBytes);
        WaveFile::set_subchunk_2_id(temp32);

        input_file.read(
                reinterpret_cast<char*>(&temp32), 
                kSizeFourBytes);
        WaveFile::set_subchunk_2_size(temp32);

        // There's now enough data to calculate the number of data samples
        number_of_samples = WaveFile::subchunk_2_size() 
            / WaveFile::num_channels() / WaveFile::bits_per_sample() 
            * kNumberOfBitsPerByte;
        std::cout << number_of_samples << std::endl;
        std::vector<int16_t> samples(number_of_samples);

        input_file.read(
                reinterpret_cast<char*>(&samples[0]),  
                number_of_samples);
        input_file.close();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "Exception opening/reading/closing file\n";
    }

}

//=============================================================
// Protected methods
//=============================================================
// None

//=============================================================
// Private methods
//=============================================================
// None
