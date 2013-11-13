#ifndef __CTESS_STRING_H
#define __CTESS_STRING_H

typedef struct
{
    void *opaque;
} tess_string_t;

const char *tess_string_get_char_array(tess_string_t *text);
void tess_string_free(tess_string_t *text);

#endif

