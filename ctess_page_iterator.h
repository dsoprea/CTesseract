#ifndef __CTESS_PAGE_ITERATOR_H
#define __CTESS_PAGE_ITERATOR_H

#include <tesseract/baseapi.h>
#include <tesseract/pageiterator.h>

#include "ctess_types.h"

typedef struct {
    tesseract::PageIterator *tess_page_iterator;
} tess_page_iterator_t;

int tess_page_it_next(tess_page_iterator_t *it, 
                      tess_page_iterator_level_e level);

int tess_page_it_empty(tess_page_iterator_t *it, 
                       tess_page_iterator_level_e level);

#endif

