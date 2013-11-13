#include <ctesseract/ctess_string.h>

extern "C" {

const char *tess_string_get_char_array(tess_string_t *text)
{
    return text->tess_string->string();
}

void tess_string_free(tess_string_t *text)
{
    delete text->tess_string;
}

}
