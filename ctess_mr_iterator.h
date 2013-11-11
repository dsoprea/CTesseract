#ifndef __CTESS_MR_ITERATOR_H
#define __CTESS_MR_ITERATOR_H

#include <tesseract/baseapi.h>
#include <tesseract/resultiterator.h>

#include "ctess_types.h"

typedef union {
    tesseract::ResultIterator *tess_result;
//    tesseract::MutableIterator *tess_mutable;
} tess_mr_it_u;

typedef enum
{ 
    TESS_MR_IT_TYPE_RESULT, 
//    TESS_MR_IT_TYPE_MUTABLE 
} tess_mr_it_type_e;
    
typedef struct {
    tess_mr_it_u iterator;
    tess_mr_it_type_e type;
} tess_mr_iterator_t;

int tess_mr_init_for_result_it(tess_mr_iterator_t *it, 
                               tesseract::ResultIterator *tess_result);

//int tess_mr_init_for_mutable_it(tess_mr_iterator_t *it, 
//                                tesseract::MutableIterator *tess_mutable);

int tess_mr_it_next(tess_mr_iterator_t *it, 
                    tess_page_iterator_level_e level);

char *tess_mr_it_get_utf8_text(tess_mr_iterator_t *it, 
                               tess_page_iterator_level_e level);

int tess_mr_it_delete(tess_mr_iterator_t *it);

int tess_mr_it_empty(tess_mr_iterator_t *it, tess_page_iterator_level_e level);

#endif

