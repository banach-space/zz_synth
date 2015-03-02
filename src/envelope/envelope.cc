//========================================================================
// FILE:
//      src/common/envelope.cc
//
// AUTHOR:
//      zimzum@github 
//
// DESCRIPTION:
//      Classes for envelope generation
//
//  License: GNU GPL v2.0 
//========================================================================

#include <envelope/envelope.h>

using namespace std;

//========================================================================
// CLASS: Envelope
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
Envelope::Envelope()
{
}

Envelope::~Envelope() {}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// 3. ACCESSORS
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// 4. MUTATORS
//------------------------------------------------------------------------
// None

//========================================================================
// CLASS: ArEnvelope
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
ArEnvelope::ArEnvelope(
        SynthConfig& synthesiser,
        float peak_amplitude_arg,
        double attack_duration_arg,
        double decay_duration_arg
        ) :
    Envelope(),
    attack_number_of_samples_(
            static_cast<size_t>(synthesiser.sampling_rate() * attack_duration_arg)),
    decay_number_of_samples_(
            static_cast<size_t>(synthesiser.sampling_rate() * decay_duration_arg)),
    decay_segment_(
            peak_amplitude_arg, 
            decay_number_of_samples_,
            SegmentGradient::kDecline),
    attack_segment_(
            peak_amplitude_arg, 
            attack_number_of_samples_,
            SegmentGradient::kIncline)
{
    assert(attack_duration_arg >= 0);
    assert(decay_duration_arg >= 0);
}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
void ArEnvelope::ApplyEnvelope(std::vector<int16_t> &samples) const
{
    assert(samples.size() >= (attack_number_of_samples_ + decay_number_of_samples_));
    assert(!samples.empty());

    // 1. Apply attack
    vector<float>::const_iterator it_seg = attack_segment_.segment_.begin();
    vector<float>::const_iterator it_seg_end = attack_segment_.segment_.end();
    vector<int16_t>::iterator it_data = samples.begin();
    vector<int16_t>::const_iterator it_data_end = samples.begin() 
        + static_cast<vector<int16_t>::difference_type>(attack_number_of_samples_);

    for ( ; it_seg != it_seg_end && it_data != it_data_end; it_seg++, it_data++)
    {

       *it_data = static_cast<int16_t>(*it_seg * static_cast<float>(*it_data)); 
    }

    // 2. Apply decay
    it_seg = decay_segment_.segment_.begin();
    it_seg_end = decay_segment_.segment_.end();
    it_data = samples.end()
        - static_cast<vector<int16_t>::difference_type>(decay_number_of_samples_);
    it_data_end = samples.end();


    for ( ; it_seg != it_seg_end && it_data != it_data_end; it_seg++, it_data++)
    {
       *it_data = static_cast<int16_t>(*it_seg * static_cast<float>(*it_data)); 
    }
}

//------------------------------------------------------------------------
// 3. ACCESSORS
//------------------------------------------------------------------------
// None

//------------------------------------------------------------------------
// 4. MUTATORS
//------------------------------------------------------------------------
// None

//========================================================================
// CLASS: AdsrEnvelope
//========================================================================
//------------------------------------------------------------------------
// 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
//------------------------------------------------------------------------
AdsrEnvelope::AdsrEnvelope(
        std::unique_ptr<Segment> &attack_segment_arg,
        std::unique_ptr<Segment> &decay_segment_arg,
        std::unique_ptr<Segment> &sustain_segment_arg,
        std::unique_ptr<Segment> &release_segment_arg
        ) :
    Envelope(),
    attack_segment_(std::move(attack_segment_arg)),
    decay_segment_(std::move(decay_segment_arg)),
    sustain_segment_(std::move(sustain_segment_arg)),
    release_segment_(std::move(release_segment_arg)),
    length_(attack_segment_->Length() + decay_segment_->Length() + sustain_segment_->Length() + release_segment_->Length())
{
}

//------------------------------------------------------------------------
// 2. GENERAL USER INTERFACE 
//------------------------------------------------------------------------
void AdsrEnvelope::ApplyEnvelope(std::vector<int16_t> &samples) const
{
    // TODO: This is a rather slow and inefficient implementation and I'm unhappy
    //       about it. Come back here and improve.
    assert(samples.size() == length_);
    assert(!samples.empty());

    // 1. Apply attack
    vector<float> attack_segment = attack_segment_->GetSegment();

    vector<float>::const_iterator it_seg     = attack_segment.begin();
    vector<float>::const_iterator it_seg_end = attack_segment.end();
    vector<int16_t>::iterator it_data        = samples.begin();
    vector<int16_t>::iterator it_data_end    = samples.begin()
        + static_cast<vector<int16_t>::difference_type>(attack_segment_->Length());

    for ( ; it_seg != it_seg_end && it_data != it_data_end; it_seg++, it_data++)
    {
        *it_data = static_cast<int16_t>(*it_seg * static_cast<float>(*it_data)); 
    }

    // 2. Apply decay
    vector<float> decay_segment = decay_segment_->GetSegment();

    it_data     = it_data_end;
    it_data_end = it_data
        + static_cast<vector<int16_t>::difference_type>(decay_segment_->Length());
    it_seg     = decay_segment.begin();
    it_seg_end = decay_segment.end();

    for ( ; it_seg != it_seg_end && it_data != it_data_end; it_seg++, it_data++)
    {
        *it_data = static_cast<int16_t>(*it_seg * static_cast<float>(*it_data)); 
    }

    // 3. Apply sustain
    vector<float> sustain_segment = sustain_segment_->GetSegment();

    it_data     = it_data_end;
    it_data_end = it_data
        + static_cast<vector<int16_t>::difference_type>(sustain_segment_->Length());
    it_seg     = sustain_segment.begin();
    it_seg_end = sustain_segment.end();

    for ( ; it_seg != it_seg_end && it_data != it_data_end; it_seg++, it_data++)
    {
        *it_data = static_cast<int16_t>(*it_seg * static_cast<float>(*it_data)); 
    }

    // 4. Apply release
    vector<float> release_segment = release_segment_->GetSegment();

    it_data     = it_data_end;
    it_data_end = it_data
        + static_cast<vector<int16_t>::difference_type>(release_segment_->Length());
    it_seg     = release_segment.begin();
    it_seg_end = release_segment.end();

    for ( ; it_seg != it_seg_end && it_data != it_data_end; it_seg++, it_data++)
    {
        *it_data = static_cast<int16_t>(*it_seg * static_cast<float>(*it_data)); 
    }
}

//------------------------------------------------------------------------
// 3. ACCESSORS
//------------------------------------------------------------------------
// None

//------------------------------------------------------------------------
// 4. MUTATORS
//------------------------------------------------------------------------
// None
