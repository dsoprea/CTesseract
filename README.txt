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
    Also needs language data.

    * For Ubuntu, install the "libtesseract-dev" and "libtesseract3", packages.
    * As an example of installing English language data under Ubuntu, you'll
      require the "tesseract-ocr-eng" packages.

Leptonica:
    * For Ubuntu, install the "libleptonica-dev" package.


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


Usage Notes
-----------

Aside from a handful of new functions required for the C implementation
(creating and destroying the API context, deleting an allocated string, and
several functions related to iterators) and new C types to wrap the C++
originals, the C functions are named by a very predictable convention. This
specifically applies to the API methods (this will probably be 95% of your
usage). 

For example, "api->GetUTF8Text()" translates to "tess_get_utf8_text(&api)"
(assuming the API context is an auto-allocated variable named "api"). When 
multiple overloads of the same C++ method are concerned, a type or some other 
type of discriminator will be suffixed to the end of the corresponding C call. 
For example, "api->SetImage(image)" translates to 
"tess_set_image_pix(&api, image)".

For a complete comparison:

    In Tesseract:
        
        tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
        api->Init(NULL, "eng")

        Pix *image;
        image = pixRead("receipt4.png");

        api->SetImage(image);
        api->Recognize(NULL);

        char *text = api->GetUTF8Text();
        std::cout << text << std::endl;
        delete[] text;

        api->End();
        delete api;
        
    In CTesseract:

        tess_api_t api;
        tess_create(NULL, "eng", &api)

        PIX *image;
        image = pixRead("../receipt4.png");

        tess_set_image_pix(&api, image);
        tess_recognize(&api);

        char *para_text = tess_get_utf8_text(&api);
        printf("%s", para_text);
        tess_delete_string(para_text);

        pixDestroy(&image);
        tess_destroy(&api)


Full Example
------------

The following is an example implementation. Aside from the symbol changes, this 
code has the same flow-of-logic:

    #include <stdio.h>

    #include <leptonica/allheaders.h>

    #include <ctess_api/ctess_types.h>
    #include <ctess_api/ctess_main.h>

    // Process individual blocks of the document. Allows you to identify visual 
    // separate parts of the document.
    int recognize_iterate(tess_api_t *api)
    {
        if(tess_recognize(api) != 0)
            return -1;

        int confidence = tess_mean_text_conf(api);
        printf("Confidence: %d\n", confidence);
        if(confidence < 80)
            printf("Confidence is low!\n");

        tess_mr_iterator_t it;
        tess_get_iterator(api, &it);

        do 
        {
            printf("=================\n");
            if(tess_mr_it_empty(&it, RIL_PARA) == 1)
                continue;

            char *para_text = tess_mr_it_get_utf8_text(&it, RIL_PARA);
            printf("%s", para_text);
            tess_delete_string(para_text);
        } while (tess_mr_it_next(&it, RIL_PARA) == 1);

        tess_mr_it_delete(&it);
        return 0;
    }

    // Process the document and return the complete thing as a single string.
    int recognize_complete(tess_api_t *api)
    {
        if(tess_recognize(api) != 0)
            return -1;

        int confidence = tess_mean_text_conf(api);
        printf("Confidence: %d\n", confidence);
        if(confidence < 80)
            printf("Confidence is low!\n");

        char *para_text = tess_get_utf8_text(api);
        printf("%s", para_text);
        tess_delete_string(para_text);

        return 0;
    }

    int main()
    {
        tess_api_t api;

        if(tess_create(NULL, "eng", &api) != 0)
            return 1;

        // Open input image with leptonica library
        PIX *image;
        if((image = pixRead("../receipt4.png")) == NULL)
        {
            pixDestroy(&image);
            tess_destroy(&api);
            return 2;
        }
     
        if(tess_set_image_pix(&api, image) != 0)
        {
            pixDestroy(&image);
            tess_destroy(&api);
            return 3;
        }

        if(recognize_iterate(&api) != 0)
        {
            pixDestroy(&image);
            tess_destroy(&api);
            return 4;
        }

        pixDestroy(&image);
        tess_destroy(&api);

        return 0;
    }


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
    GetFeaturesForBlob
    RunAdaptiveClassifier
    NormalizeTBLOB

