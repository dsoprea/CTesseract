#ifndef __CTESS_PAGE_ITERATOR_H
#define __CTESS_PAGE_ITERATOR_H

#include <ctess_api/ctess_types.h>

typedef struct
{
    void *opaque;
} tess_page_iterator_t;

int tess_page_it_next(tess_page_iterator_t *it, 
                      tess_page_iterator_level_e level);

int tess_page_it_empty(tess_page_iterator_t *it, 
                       tess_page_iterator_level_e level);

#endif

