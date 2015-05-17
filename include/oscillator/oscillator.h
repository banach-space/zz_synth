//========================================================================
//  FILE:
//      include/oscillator/oscillator.h 
//
//  AUTHOR:
//      zimzum@github 
//
//  DESCRIPTION:
//      Defines all classes used for generating basic waveforms:
//		 a) Oscillator - pure abstract base class
//       b) SineWaveform - plain sine wave 
//       c) SawtoohWaveform - saw tooth
//       d) SquareWaveform - square wave
//       e) TriangleWaveform - triangle wave
//
//  License: GNU GPL v2.0 
//========================================================================

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <global/global_include.h>
#include <common/synth_config.h>

//========================================================================
// CLASS: Oscillator
//
// DESCRIPTION:
//      Base class for other waveforms - defines the interface.
//      Implemented as a pure abstract class. 
//========================================================================
class Oscillator 
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      Oscillator()
    //  
    //  DESCRIPTION:
    //      Constructor
    //  INPUT:
    //      synthesiser     - currently used synthesiser
    //      peak_amplitude  - peak amplitude of the waveform 
    //                        (range: [0, 2^15-1]). 
    //      initial_phase   - initial phase of the waveform 
    //                        (range: [0, kTwoPi))
    //      pitch_id        - index into the frequency table (range: 
    //                        [0, kNumberOfFrequencies) (see the 
    //                        definition of SynthConfig)
    //--------------------------------------------------------------------
    explicit Oscillator(
            const SynthConfig& synthesiser,
            int16_t peak_amplitude, 
            double initial_phase ,
            std::size_t pitch_id);
    //--------------------------------------------------------------------
    //  NAME:
    //      Oscillator()
    //  
    //  DESCRIPTION:
    //      Constructor
    //  INPUT:
    //      synthesiser     - currently used synthesiser
    //      peak_amplitude  - peak amplitude of the waveform 
    //                        (range: [0, 2^15-1]). 
    //      initial_phase   - initial phase of the waveform 
    //                        (range: [0, kTwoPi))
    //      frequency       - the frequency (range: according to Nyquist)
    //--------------------------------------------------------------------
    explicit Oscillator(
            const SynthConfig& synthesiser,
            int16_t peak_amplitude, 
            double initial_phase ,
            double frequency);
    virtual ~Oscillator();
    explicit Oscillator(const Oscillator& rhs)   = delete;
    explicit Oscillator(Oscillator&& rhs)        = delete;
    Oscillator& operator=(const Oscillator &rhs) = delete;
    Oscillator& operator=(Oscillator&& rhs)      = delete;

    //--------------------------------------------------------------------
    // 2. GENERAL USER INTERFACE 
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      operator()
    //  
    //  DESCRIPTION:
    //      Oscillators by oscillating generate waveforms. This operator
    //      will generate one for you.
    //  INPUT:
    //      number_of_seconds - the length (in seconds) of the desired
    //                          waveform (TODO!!! Limit?!)
    //  RETURN:
    //      Vector of samples for the requested waveform
    //--------------------------------------------------------------------
	std::vector<int16_t> operator()(uint32_t number_of_seconds);

private:
    //--------------------------------------------------------------------
    // 3. INTERFACE DEFINITION 
    //--------------------------------------------------------------------
    virtual std::vector<int16_t> GenWaveform(
            size_t number_of_samples,
            int16_t peak_amplitude,
            double initial_phase,
            double phase_increment
            ) const = 0;

    //--------------------------------------------------------------------
    // 4. DATA MEMMBERS 
    //--------------------------------------------------------------------
    int16_t peak_amplitude_;
    double frequency_;
    double initial_phase_;
    uint32_t sampling_rate_;
    double phase_increment_;
    
};

//========================================================================
// CLASS: SineWaveform
//
// DESCRIPTION:
//      Basic sinewave: y[n] = A*sin(kTwoPi*f*n + phi), in which A is the
//      peak amplitude, f is the frequency (determined by pitch_id), and
//      phi is the initial phase. This sine wave is implemented with aid
//      of the sin() function from <cmath>.
//========================================================================
class SineWaveform : public Oscillator
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      SineWaveform()
    //  
    //  DESCRIPTION:
    //      Constructor.
    //  INPUT:
    //      synthesiser     - currently used synthesiser
    //      peak_amplitude  - peak amplitude of the waveform 
    //                        (range: [0, 2^15-1]). 
    //      initial_phase   - initial phase of the waveform 
    //                        (range: [0, kTwoPi))
    //      pitch_id        - index into the frequency table (range: 
    //                        [0, kNumberOfFrequencies) (see the 
    //                        definition of SynthConfig)
    //--------------------------------------------------------------------
    explicit SineWaveform(
            const SynthConfig& synthesiser,
            int16_t peak_amplitude, 
            double initial_phase ,
            std::size_t pitch_id);
    //--------------------------------------------------------------------
    //  NAME:
    //      SineWaveform()
    //  
    //  DESCRIPTION:
    //      Constructor.
    //  INPUT:
    //      synthesiser     - currently used synthesiser
    //      peak_amplitude  - peak amplitude of the waveform 
    //                        (range: [0, 2^15-1]). 
    //      initial_phase   - initial phase of the waveform 
    //                        (range: [0, kTwoPi))
    //      frequency       - frequency (range: according to Nyquist)
    //--------------------------------------------------------------------
    explicit SineWaveform(
            const SynthConfig& synthesiser,
            int16_t peak_amplitude, 
            double initial_phase ,
            double frequency);
    ~SineWaveform() = default;

private:
    //--------------------------------------------------------------------
    // 2. INTERFACE DEFINITION 
    //--------------------------------------------------------------------
    std::vector<int16_t> GenWaveform(
            size_t number_of_samples,
            int16_t peak_amplitude,
            double initial_phase,
            double phase_increment
            ) const final;
};

//========================================================================
// CLASS: SawtoothWaveform
//
// DESCRIPTION:
//     The sawtooth waveform defined by: 
//                 \phi_n
//          y[n] = ------ - 1
//                   Pi
//
//      TODO!!! Implement this using BLEP 
//========================================================================
class SawtoothWaveform : public Oscillator
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      SawtoothWaveform()
    //  
    //  DESCRIPTION:
    //      Constructor.
    //  INPUT:
    //      synthesiser     - currently used synthesiser
    //      peak_amplitude  - peak amplitude of the waveform 
    //                        (range: [0, 2^15-1]). 
    //      initial_phase   - initial phase of the waveform 
    //                        (range: [0, kTwoPi))
    //      pitch_id        - index into the frequency table (range: 
    //                        [0, kNumberOfFrequencies) (see the 
    //                        definition of SynthConfig)
    //--------------------------------------------------------------------
    explicit SawtoothWaveform(
            const SynthConfig& synthesiser,
            int16_t peak_amplitude, 
            double initial_phase ,
            std::size_t pitch_id);
    //--------------------------------------------------------------------
    //  NAME:
    //      SawtoothWaveform()
    //  
    //  DESCRIPTION:
    //      Constructor.
    //  INPUT:
    //      synthesiser     - currently used synthesiser
    //      peak_amplitude  - peak amplitude of the waveform 
    //                        (range: [0, 2^15-1]). 
    //      initial_phase   - initial phase of the waveform 
    //                        (range: [0, kTwoPi))
    //      frequency       - frequency (range: according to Nyquist)
    //--------------------------------------------------------------------
    explicit SawtoothWaveform(
            const SynthConfig& synthesiser,
            int16_t peak_amplitude, 
            double initial_phase ,
            double frequency);
    ~SawtoothWaveform() = default;

private:
    //--------------------------------------------------------------------
    // 2. INTERFACE DEFINITION 
    //--------------------------------------------------------------------
    std::vector<int16_t> GenWaveform(
            size_t number_of_samples,
            int16_t peak_amplitude,
            double initial_phase,
            double phase_increment
            ) const final;
};

//========================================================================
// CLASS: SquareWaveform
//
// DESCRIPTION:
//     The square waveform defined by: 
//                  _
//                 |  1 when n before the midpoint of the period
//          y[n] = { 
//                 |_-1 otherwise
//
//========================================================================
class SquareWaveform : public Oscillator
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      SawtoothWaveform()
    //  
    //  DESCRIPTION:
    //      Constructor.
    //  INPUT:
    //      synthesiser     - currently used synthesiser
    //      peak_amplitude  - peak amplitude of the waveform 
    //                        (range: [0, 2^15-1]). 
    //      initial_phase   - initial phase of the waveform 
    //                        (range: [0, kTwoPi))
    //      pitch_id        - index into the frequency table (range: 
    //                        [0, kNumberOfFrequencies) (see the 
    //                        definition of SynthConfig)
    //--------------------------------------------------------------------
    explicit SquareWaveform(
            const SynthConfig& synthesiser,
            int16_t peak_amplitude, 
            double initial_phase ,
            std::size_t pitch_id);
    //--------------------------------------------------------------------
    //  NAME:
    //      SquareWaveform()
    //  
    //  DESCRIPTION:
    //      Constructor.
    //  INPUT:
    //      synthesiser     - currently used synthesiser
    //      peak_amplitude  - peak amplitude of the waveform 
    //                        (range: [0, 2^15-1]). 
    //      initial_phase   - initial phase of the waveform 
    //                        (range: [0, kTwoPi))
    //      frequency       - frequency (range: according to Nyquist)
    //--------------------------------------------------------------------
    explicit SquareWaveform(
            const SynthConfig& synthesiser,
            int16_t peak_amplitude, 
            double initial_phase ,
            double frequency);
    ~SquareWaveform() = default;

private:
    //--------------------------------------------------------------------
    // 2. INTERFACE DEFINITION 
    //--------------------------------------------------------------------
    std::vector<int16_t> GenWaveform(
            size_t number_of_samples,
            int16_t peak_amplitude,
            double initial_phase,
            double phase_increment
            ) const final;
};

//========================================================================
// CLASS: TriangleWaveform
//
// DESCRIPTION:
//     The triangle waveform defined by:
//                     2 |\phi_n - Pi|
//          y[n] = 1 - ---------------
//                          Pi
//========================================================================
class TriangleWaveform : public Oscillator
{
public:
    //--------------------------------------------------------------------
    // 1. CONSTRUCTORS/DESTRUCTOR/ASSIGNMENT OPERATORS
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    //  NAME:
    //      TriangleWaveform()
    //  
    //  DESCRIPTION:
    //      Constructor.
    //  INPUT:
    //      synthesiser     - currently used synthesiser
    //      peak_amplitude  - peak amplitude of the waveform 
    //                        (range: [0, 2^15-1]). 
    //      initial_phase   - initial phase of the waveform 
    //                        (range: [0, kTwoPi))
    //      pitch_id        - index into the frequency table (range: 
    //                        [0, kNumberOfFrequencies) (see the 
    //                        definition of SynthConfig)
    //--------------------------------------------------------------------
    explicit TriangleWaveform(
            const SynthConfig& synthesiser,
            int16_t peak_amplitude, 
            double initial_phase ,
            std::size_t pitch_id);
    //--------------------------------------------------------------------
    //  NAME:
    //      TriangleWaveform()
    //  
    //  DESCRIPTION:
    //      Constructor.
    //  INPUT:
    //      synthesiser     - currently used synthesiser
    //      peak_amplitude  - peak amplitude of the waveform 
    //                        (range: [0, 2^15-1]). 
    //      initial_phase   - initial phase of the waveform 
    //                        (range: [0, kTwoPi))
    //      frequency       - frequency (range: according to Nyquist)
    //--------------------------------------------------------------------
    explicit TriangleWaveform(
            const SynthConfig& synthesiser,
            int16_t peak_amplitude, 
            double initial_phase ,
            double frequency);
    ~TriangleWaveform() = default;

private:
    //--------------------------------------------------------------------
    // 2. INTERFACE DEFINITION 
    //--------------------------------------------------------------------
    std::vector<int16_t> GenWaveform(
            size_t number_of_samples,
            int16_t peak_amplitude,
            double initial_phase,
            double phase_increment
            ) const final;
};

#endif /* #define OSCILLATOR_H */
