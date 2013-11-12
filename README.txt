Summary
-------

This library provides a C adapter for the Tesseract C++ library.


Description
-----------

This project was created as a transitional library on which to build a tighter 
Python module.


Dependencies
------------

Tesseract:
    Library: libtesseract.so
    Includes: /usr/include/tesseract

    * For Ubuntu, install the "libtesseract-dev" package.


Build
-----

To build ctesseract shared library:

    $ mkdir build && build
    $ cmake ..
    $ make
    $ sudo make install

To build test program ("test" subdirectory):

    $ mkdir build && build
    $ cmake ..
    $ make

    To run the test program, run "./ctesseract_test". The OCR'd text from the 
    test image will be dumped.


Details
-------

Most of the functionality in baseapi.h (the primary API interface) is provided.
The exceptions are:

> debug-related calls
> calls requiring callbacks
> calls requiring types that aren't fully implemented in the API 
  (MutableIterator and OSResults, specifically)
> calls that have little chance of being tested properly due to a lack of clear 
  usage. 

This should be a complete list of such unimplemented calls:

    SetThresholder
    ProcessPagesRenderer
    ProcessPageRenderer
    SetDictFunc
    SetProbabilityInContextFunc
    SetParamsModelClassifyFunc
    SetFillLatticeFunc
    DetectOS
    GetDawg
    NumDawgs
    oem
    InitTruthCallback
    GetCubeRecoContext

