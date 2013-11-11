#include "ctess_string.h"

const char *tess_get_string_get_char_array(tess_string_t *text)
{
    return text->tess_string.string();
}

