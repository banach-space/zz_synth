zz_synth
========

A software synthesiser implemented in C++11. 

Status
--------
This is work in progress and will remain so for a while. I try to add new features as often as possible, but with other commitments this proves very challenging. 

Technicalities
--------------
Developed and tested under Linux (3.16.0-4-amd64) with GCC (4.9.1) and Clang (3.4). No support for other platforms at this point.

The unit testing is implemented with the aid of Google's mocking and unit-testing frameworks, gmock and gtest respectively. Otherwise, no external libraries are used.

The attached build system is recursive and every build command should be invoked from the top directory. For example, in order to build the **read_write_wav** testbench, type the following:
```
make unit_tests/read_write_wav TARGET=new
```
The **TARGET** variable is defined so that the requested target type is passed to makefiles in sub-directories. The following, fairly standard
approach, is insufficient:
```
make unit_tests/read_write_wav new
```

The purpose of this project
----------------------------
I'm fascinated with both audio synthesis/DSP and C++ and this is my toy-project to try out various things, learn new stuff and be creative! My goal is to write efficient, high-standard, maintainable C++ library following best coding standards. If on top of that somebody finds this code useful/helpful, then I'll be extremely happy!

Requirements:
-------------
The unit testing is performed with the aid of Google Unit Testing and Google Mocking Frameworks. These are assumed to be available in the system on which the synthesiser is run.

Message for you
----------------
Comments, feedback and suggestions are more than welcome!
