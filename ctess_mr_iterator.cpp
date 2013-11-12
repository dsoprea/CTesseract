#include <ctesseract/ctess_mr_iterator.h>

// We married the mutable iterator and result iterator (the former inheriting
// from the latter). Hence, we refer to this as "MR".

// TODO: We also need to implement the functionality inherited from
//       LTRResultIterator AND from page-iterator. Check if page-iterator needs 
//       this, too. We don't have to implement everything, at this time.

int tess_mr_init_for_result_it(tess_mr_iterator_t *it, 
                               tesseract::ResultIterator *tess_result)
{
    it->type = TESS_MR_IT_TYPE_RESULT;
    it->iterator.tess_result = tess_result;
    
    return 0;
}
/*
int tess_mr_init_for_mutable_it(tess_mr_iterator_t *it, 
                                tesseract::MutableIterator *tess_mutable)
{
    it->type = TESS_MR_IT_TYPE_MUTABLE;
    it->iterator.tess_mutable = tess_mutable;
    
    return 0;
}
*/
/*
virtual void Begin();
*/

int tess_mr_it_next(tess_mr_iterator_t *it, 
                    tess_page_iterator_level_e level)
{
    switch(it->type)
    {
        case TESS_MR_IT_TYPE_RESULT:
            if(it->iterator.tess_result->Next(
                    (tesseract::PageIteratorLevel)level) == true)
                return 1;

            return 0;
/*
        case TESS_MR_IT_TYPE_MUTABLE:
            if(it->iterator.tess_mutable->Next(
                    (tesseract::PageIteratorLevel)level) == true)
                return 1;

            return 0;
*/
        default:
            return -1;
    }
}

/*
virtual bool IsAtBeginningOf(PageIteratorLevel level) const;
virtual bool IsAtFinalElement(PageIteratorLevel level,
                            PageIteratorLevel element) const;
*/

char *tess_mr_it_get_utf8_text(tess_mr_iterator_t *it, 
                                   tess_page_iterator_level_e level)
{
    switch(it->type)
    {
        case TESS_MR_IT_TYPE_RESULT:
            return it->iterator.tess_result->GetUTF8Text(
                    (tesseract::PageIteratorLevel)level);
/*
        case TESS_MR_IT_TYPE_MUTABLE:
            return it->iterator.tess_mutable->GetUTF8Text(
                    (tesseract::PageIteratorLevel)level);
*/
        default:
            return NULL;
    }
}

/*
bool ParagraphIsLtr() const;
static void CalculateTextlineOrder(
    bool paragraph_is_ltr,
    const GenericVector<StrongScriptDirection> &word_dirs,
    GenericVectorEqEq<int> *reading_order);

static const int kMinorRunStart;
static const int kMinorRunEnd;
static const int kComplexWord;
*/

int tess_mr_it_delete(tess_mr_iterator_t *it)
{
    switch(it->type)
    {
        case TESS_MR_IT_TYPE_RESULT:
            delete it->iterator.tess_result;
            return 0;

//        case TESS_MR_IT_TYPE_MUTABLE:
//            delete it->iterator.tess_mutable;
//            return 0;

        default:
            return -1;
    }    
}

int tess_mr_it_empty(tess_mr_iterator_t *it, tess_page_iterator_level_e level)
{
    switch(it->type)
    {
        case TESS_MR_IT_TYPE_RESULT:
            if(it->iterator.tess_result->Empty(
                    (tesseract::PageIteratorLevel)level) == true)
                return 1;
            else
                return 0;
/*
        case TESS_MR_IT_TYPE_MUTABLE:
            if(it->iterator.tess_mutable->Empty(
                    (tesseract::PageIteratorLevel)level) == true)
                return 1;
            else
                return 0;
*/
        default:
            return -1;
    }
}

