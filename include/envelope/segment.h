//========================================================================
//  FILE:
//      include/common/segment.h
//
//  AUTHOR:
//      zimzum@github
//
//  DESCRIPTION:
//      Classes representing enevelop segments.
//
//  License: GNU GPL v2.0
//========================================================================

#ifndef SEGMENT_H
#define SEGMENT_H

#include <global/global_include.h>

//========================================================================
// FORWARD DECLARATIONS
//========================================================================
class ArEnvelope;
class AdsrEnvelope;

//========================================================================
// PRIVATE DATA TYPES
//========================================================================
//------------------------------------------------------------------------
//  NAME:
//      SegmentGradient
//
//  DESCRIPTION:
//      Enum used for differentiating between two types of linear
//      segments:
//          - kIncline represents attack (positive gradient, i.e. 'a')
//          - kDecline represents decay (negative gradient, i.e. 'a')
//------------------------------------------------------------------------
enum class SegmentGradient { kDecline, kIncline };

//========================================================================
// CLASS: Segment
//
// DESCRIPTION:
//      A segment in an envelope - the most  basic building block. Abstract
//      base class tha defines the basic interface.
//========================================================================
class Segment {
 public:
  //--------------------------------------------------------------------
  // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
  //--------------------------------------------------------------------
  explicit Segment(size_t number_of_samples_arg = 0);
  virtual ~Segment();
  explicit Segment(const Segment& rhs) = delete;
  explicit Segment(Segment&& rhs) = delete;
  Segment& operator=(const Segment& rhs) = delete;
  Segment& operator=(Segment&& rhs) = delete;

  //--------------------------------------------------------------------
  // 2. GENERAL USER INTERFACE
  //--------------------------------------------------------------------
  //--------------------------------------------------------------------
  //  NAME:
  //      GetSamples()
  //
  //  DESCRIPTION:
  //      Returns a copy of the segment in form of vector of float.
  //      Note that derived classes are not forced to internally store
  //      their segments as vectors of floats and that this function
  //      only returns a copy.
  //  INPUT:
  //      None
  //  OUTPUT:
  //      The segment
  //--------------------------------------------------------------------
  virtual std::vector<float> GetSamples() {
    if (!generated_) GenerateSamples();

    return samples_;
  }

  //--------------------------------------------------------------------
  //  NAME:
  //      GenerateSamples()
  //
  //  DESCRIPTION:
  //      Generates the samples for this segment. Note that every time the
  //      parameters of a segment are changed, this method needs to be called
  //      to regrenerate the samples.
  //  INPUT:
  //      None
  //  OUTPUT:
  //      None
  //--------------------------------------------------------------------
  virtual void GenerateSamples() = 0;

  //--------------------------------------------------------------------
  //  NAME:
  //      operator[]
  //
  //  DESCRIPTION:
  //      Return the n-th element in the segment.
  //  INPUT:
  //      Index of the segment element to be returned.
  //  OUTPUT:
  //      The value of the segment at the specified position
  //--------------------------------------------------------------------
  virtual const float& operator[](const std::size_t position) const;
  virtual float& operator[](const std::size_t position);

  //--------------------------------------------------------------------
  //  NAME:
  //      IsEmpty()
  //
  //  DESCRIPTION:
  //      Check whether the segment is empty
  //  INPUT:
  //      None
  //  OUTPUT:
  //      True if the segment is empty, false otherwise.
  //--------------------------------------------------------------------
  virtual bool IsEmpty() const = 0;

  bool IsGenerated() { return generated_; }

  //--------------------------------------------------------------------
  //  NAME:
  //      GetLength()
  //
  //  DESCRIPTION:
  //      Returns the length of this Segment expressed in samples.
  //  INPUT:
  //      None
  //  OUTPUT:
  //      The length of this Segment expressed in samples.
  //--------------------------------------------------------------------
  virtual std::size_t GetLength() const = 0;

  //--------------------------------------------------------------------
  // 3. ACCESSORS
  //--------------------------------------------------------------------
  // None

 protected:
  std::vector<float> samples_;
  bool generated_;
  std::size_t number_of_samples_;

 private:
  //--------------------------------------------------------------------
  // 4. PRIVATE METHODS
  //--------------------------------------------------------------------
  // None

  //--------------------------------------------------------------------
  // 5. DATA MEMMBERS
  //--------------------------------------------------------------------
  // None
};

//========================================================================
// CLASS: ConstantSegment
//
// DESCRIPTION:
//      A constant segment in an envelope. Mathematically it is defined
//      by: y = a, where 'a' is the amplitude_. Due to its simplicity,
//      there's no need to pre-calculate and store the values of
//      this segment. This will improve memory footprint.
//========================================================================
class ConstantSegment : public Segment {
 public:
  //--------------------------------------------------------------------
  // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
  //--------------------------------------------------------------------
  //--------------------------------------------------------------------
  //  NAME:
  //      ConstantSegment()
  //
  //  DESCRIPTION:
  //      Constructor
  //  INPUT:
  //      amplitude_arg       - the value of the segment
  //      number_of_samples_arg - the total number of steps/samples in this
  //                            segment
  //--------------------------------------------------------------------
  explicit ConstantSegment(float amplitude_arg = 0.0,
                           size_t number_of_samples_arg = 0);
  ~ConstantSegment();

  //--------------------------------------------------------------------
  // 2. GENERAL USER INTERFACE
  //--------------------------------------------------------------------
  void SetAmplitude(float amp) {
    amplitude_ = amp;
    generated_ = false;
  }

  void SetNumberOfSamples(size_t n) {
    number_of_samples_ = n;
    generated_ = false;
  }

  //--------------------------------------------------------------------
  // Virtual functions/operators
  //--------------------------------------------------------------------
  virtual void GenerateSamples() override;
  bool IsEmpty() const override;
  std::size_t GetLength() const override;

 private:
  //--------------------------------------------------------------------
  // 4. PRIVATE METHODS
  //--------------------------------------------------------------------
  // None

  //--------------------------------------------------------------------
  // 5. DATA MEMMBERS
  //--------------------------------------------------------------------
  float amplitude_;
  friend AdsrEnvelope;
  friend ArEnvelope;
};

//========================================================================
// CLASS: LinearSegment
//
// DESCRIPTION:
//      A linear segment in an envelope. Mathematically it is defined
//      by: y = a*x. The segment is guaranteed to be 0 at one end and
//      the specified peak amplitude at the other. In particular,
//      this class is not suitable for segments described by: y = a*x +b.
//========================================================================
class LinearSegment : public Segment {
 public:
  //--------------------------------------------------------------------
  // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
  //--------------------------------------------------------------------
  //--------------------------------------------------------------------
  //  NAME:
  //      LinearSegment()
  //
  //  DESCRIPTION:
  //      Constructor
  //  INPUT:
  //      peak_amplitude_arg  - the peak amplitude value (guaranteed to be
  //                            reached) which is either the first value
  //                            (kDecline) or the last value (kIncline)
  //      number_of_samples_arg - the total number of steps/samples in this
  //                            segment (including the peak value and 0)
  //      seg_gradient_arg        - either kDecline or kIncline
  //--------------------------------------------------------------------
  explicit LinearSegment(
      float peak_amplitude_arg = 0.0, size_t number_of_samples_arg = 0,
      SegmentGradient seg_gradient_arg = SegmentGradient::kDecline);
  ~LinearSegment();

  //--------------------------------------------------------------------
  // 2. GENERAL USER INTERFACE
  //--------------------------------------------------------------------
  void SetPeakAmplitude(float amp) {
    peak_amplitude_ = amp;
    generated_ = false;
  }

  void SetNumberOfSamples(size_t n) {
    number_of_samples_ = n;
    generated_ = false;
  }

  void SetGradient(SegmentGradient grad) {
    seg_gradient_ = grad;
    generated_ = false;
  }

  //--------------------------------------------------------------------
  // Virtual functions/operators
  //--------------------------------------------------------------------
  virtual void GenerateSamples() override;
  bool IsEmpty() const override;
  std::size_t GetLength() const override;

 private:
  //--------------------------------------------------------------------
  // 4. PRIVATE METHODS
  //--------------------------------------------------------------------
  // None

  //--------------------------------------------------------------------
  // 5. DATA MEMMBERS
  //--------------------------------------------------------------------
  float peak_amplitude_;
  SegmentGradient seg_gradient_;
  friend ArEnvelope;
};

//========================================================================
// CLASS: ExponentialSegment
//
// DESCRIPTION:
//      An exponential segment in an envelope. Mathematically it is defined
//      by: y = a*x^b + c. The segment is guaranteed to be 0 at one end and
//      the specified peak amplitude at the other.
//========================================================================
class ExponentialSegment : public Segment {
 public:
  //--------------------------------------------------------------------
  // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
  //--------------------------------------------------------------------
  //--------------------------------------------------------------------
  //  NAME:
  //      ExponentialSegment()
  //
  //  DESCRIPTION:
  //      Constructor
  //  INPUT:
  //      amplitude_start_arg - amplitude at the start of the segment
  //      amplitude_end_arg   - amplitude at the end of the segment
  //      number_of_samples_arg - the total number of steps/samples in this
  //                            segment
  //--------------------------------------------------------------------
  explicit ExponentialSegment(float amplitude_start_arg = 0.0,
                              float amplitude_end_arg = 0.0,
                              float exponent_arg = 0.0,
                              size_t number_of_samples_arg = 0);
  ~ExponentialSegment();

  //--------------------------------------------------------------------
  // 2. GENERAL USER INTERFACE
  //--------------------------------------------------------------------
  void SetStartAmplitude(float amp) {
    amplitude_start_ = amp;
    generated_ = false;
  }

  void SetEndAmplitude(float amp) {
    amplitude_end_ = amp;
    generated_ = false;
  }

  void SetExponent(float exp) {
    exponent_ = exp;
    generated_ = false;
  }

  void SetNumberOfSamples(size_t n) {
    number_of_samples_ = n;
    generated_ = false;
  }

  //--------------------------------------------------------------------
  // Virtual functions/operators
  //--------------------------------------------------------------------
  virtual void GenerateSamples() override;
  bool IsEmpty() const override;
  std::size_t GetLength() const override;

  //--------------------------------------------------------------------
  // 3. ACCESSORS
  //--------------------------------------------------------------------
  float GetEndAmplitude() { return amplitude_end_; }

  float GetStartAmplitude() { return amplitude_start_; }

 private:
  //--------------------------------------------------------------------
  // 4. PRIVATE METHODS
  //--------------------------------------------------------------------
  // None

  //--------------------------------------------------------------------
  // 5. DATA MEMMBERS
  //--------------------------------------------------------------------
  float amplitude_start_;
  float amplitude_end_;
  float exponent_;
  friend AdsrEnvelope;
};

//========================================================================
//  CLASS: SegmentInitialisationException
//
// DESCRIPTION:
//  Exception thrown when the corresponding segment is not initialised
//  correctly. This can be detected by checking init_ agains the 'emptiness'
//  of the segment.
//========================================================================
class SegmentInitialisationException : public std::exception {
  virtual const char* what() const noexcept;
};

#endif /* #define _SEGMENT_H_ */
