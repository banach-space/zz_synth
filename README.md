zz_synth
========

A software synthesiser implemented in C++11. 

Status
--------
I am currently re-visiting this after a very long break and intend to spend
some time refactoring the code and then adding new features. Consider this as
very **WORK-IN-PROGRESS**.

Technicalities
--------------
Developed and tested under Linux (3.16.0-4-amd64) with GCC (4.9.1) and Clang
(3.4). No support for other platforms at this point.

The unit testing is implemented with the aid of Google's mocking and
unit-testing frameworks, gmock and gtest respectively. Otherwise, no external
libraries are used.

Build instructions
----------------------------
At this point **zz_synth** requires **Google Test** in order to build
succesfuly. There shouldn't be such dependency here and I intend to remove it
shortly. For the time being, following the following steps.

### Building Google Test
Assuming that you checked out this repo in `zz_synth`, follow these steps to
build **Google Test**:
```
$ ~/zz_synth > cd unit_tests
$ ~/zz_synth/unit_tests > git clone https://github.com/google/googletest.git
$ ~/zz_synth/unit_tests > cd googletest/googletest/make
$ ~/zz_synth/unit_tests/git clone https://github.com/google/googletest.git > make gtest.a
```

### Building zz_synth
Create the **bin** and **lib** directories, and then call make:
```
$ ~/zz_synth > mkdir bin; mkdir lib
$ ~/zz_synth > make ZZDIR=<root_dir>/zz_synth all_recursive
```

The provided build system is recursive and every build command should be
invoked from the top directory. For example, in order to build the
**read_write_wav** testbench, type the following:
```
$: make unit_tests/read_write_wav TARGET=new
```
The **TARGET** variable is defined so that the requested target type is passed
to makefiles in sub-directories. The following, fairly standard approach, is
insufficient:
```
$: make unit_tests/read_write_wav new
```

Making some noise
----------------------------
Clearly the main goal of creating an audio synthesiser is to generate some
noise! The easiest way to achieve that is to play with example code in the
**examples/** sub-directory. For instance, type  
```
$: make examples/ar_envelope_note TARGET=all
```
and then type:
```
$: bin/ar_envelope_note.out
```
Finally! You'll find some noise in the **examples/ar_envelope_note/sounds**
sub-directory.

The purpose of this project
----------------------------
Audio synthesis/DSP and C++ are my hobbies and this is my toy-project to try
out various things, learn new stuff and be creative! My goal is to write
efficient, high-standard, maintainable C++ library following best coding
standards. If on top of that somebody finds this code useful/helpful, then I'll
be extremely happy!

Requirements
-------------
The unit testing is performed with the aid of Google Unit Testing and Google
Mocking Frameworks. These are assumed to be available in the system on which
the synthesiser is run.

Message for you
----------------
Comments, feedback and suggestions are more than welcome!
