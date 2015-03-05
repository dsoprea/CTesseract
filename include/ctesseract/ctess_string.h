#ifndef __CTESS_STRING_H
#define __CTESS_STRING_H

#include <tesseract/baseapi.h>
#include <tesseract/strngs.h>

typedef struct {
    STRING *tess_string;
} tess_string_t;

extern "C"
{
    const char *tess_string_get_char_array(tess_string_t *text);
    void tess_string_free(tess_string_t *text);
}

#endif

