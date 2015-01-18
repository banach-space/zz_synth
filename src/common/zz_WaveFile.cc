//=============================================================
// FILE:
//   /src/zz_WaveFile.cc
//
// AUTHOR:
//   zimzum@github 
//
// DESCRIPTION:
//   The implementation of the WaveFile class. 
//
// License: GNU GPL v2.0 
//=============================================================

#include "common/zz_WaveFile.h"

//=============================================================
// Public methods
//=============================================================
void WaveFile::SaveBufferToFile(const std::string &file_name)
{
    std::ofstream output_file;
    output_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        output_file.open(file_name);
        output_file.write(
                reinterpret_cast<const char*>(&chunk_id_),
                kSizeFourBytes);
        output_file.write(
                reinterpret_cast<const char*>(&chunk_size_),
                kSizeFourBytes);
        output_file.write(
                reinterpret_cast<const char*>(&format_),
                kSizeFourBytes);
        output_file.write(
                reinterpret_cast<const char*>(&subchunk_1_id_),
                kSizeFourBytes);
        output_file.write(
                reinterpret_cast<const char*>(&subchunk_1_size_),
                kSizeFourBytes);
        output_file.write(
                reinterpret_cast<const char*>(&audio_format_),
                kSizeTwoBytes);
        output_file.write(
                reinterpret_cast<const char*>(&num_channels_),
                kSizeTwoBytes);
        output_file.write(
                reinterpret_cast<const char*>(&sample_rate_),
                kSizeFourBytes);
        output_file.write(
                reinterpret_cast<const char*>(&byte_rate_),
                kSizeFourBytes);
        output_file.write(
                reinterpret_cast<const char*>(&block_align_),
                kSizeTwoBytes);
        output_file.write(
                reinterpret_cast<const char*>(&bits_per_sample_),
                kSizeTwoBytes);
        output_file.write(
                reinterpret_cast<const char*>(&subchunk_2_id_),
                kSizeFourBytes);
        output_file.write(
                reinterpret_cast<const char*>(&subchunk_2_size_),
                kSizeFourBytes);
        output_file.write(
            reinterpret_cast<const char*>(sample_buffer_.get()), 
            subchunk_2_size_ );
        output_file.close();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "Exception opening/reading/closing file\n";
    }
}

WaveFile::WaveFile(int8_t number_of_seconds)
{
    int32_t internal_buffer_size;

    // Member variables that can be initialised independently
    chunk_id_       = kRiffChunkId;
    format_         = kRiffFormat;
    subchunk_1_id_  = kFmtSubchunkId;
    subchunk_1_size_= kPcmSubchunk1Size;
    audio_format_   = kPcmAudioFormat;
    num_channels_   = kNumberOfChannelsMono;
    sample_rate_    = kCdSampleRate;
    bits_per_sample_= kNumberOfBitsPerSample;
    subchunk_2_id_  = kDataSubchunkId;

    // Member variables that dependend on previously defined variables
    internal_buffer_size = number_of_seconds * sample_rate_;
    subchunk_2_size_ = internal_buffer_size * num_channels_ 
        * bits_per_sample_ / kNumberOfBitsPerByte;
    std::cout << subchunk_2_size_ << std::endl;
    chunk_size_ = 36 + subchunk_2_size_;
    byte_rate_  = sample_rate_ * num_channels_ * bits_per_sample_
        / kNumberOfBitsPerByte;
    block_align_= num_channels_ * bits_per_sample_ / kNumberOfBitsPerByte;

    sample_buffer_ = std::unique_ptr<int16_t[]>(new int16_t[internal_buffer_size]);
}
//=============================================================
// Protected methods
//=============================================================
// None

//=============================================================
// Private methods
//=============================================================
// None
