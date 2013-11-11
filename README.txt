This library provides a C adapter for the Tesseract C++ library.

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

I still need to add a makefile, and finish the README.

