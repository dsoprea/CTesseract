#include <ctesseract/ctess_page_iterator.h>

extern "C" {
// TODO: Finish implementing these methods (we only needed Next() and Empty(), 
//       initially).

/*
bool PositionedAtSameWord(const PAGE_RES_IT* other) const;
virtual void Begin();
virtual void RestartParagraph();
bool IsWithinFirstTextlineOfParagraph() const;
virtual void RestartRow();
*/

int tess_page_it_next(tess_page_iterator_t *it, 
                      tess_page_iterator_level_e level)
{
    if(it->tess_page_iterator->Next((tesseract::PageIteratorLevel)level) == true)
        return 1;
    else
        return 0;
}

/*
virtual bool IsAtBeginningOf(PageIteratorLevel level) const;
virtual bool IsAtFinalElement(PageIteratorLevel level,
                              PageIteratorLevel element) const;
int Cmp(const PageIterator &other) const;
bool BoundingBox(PageIteratorLevel level,
                 int* left, int* top, int* right, int* bottom) const;
bool BoundingBoxInternal(PageIteratorLevel level,
                         int* left, int* top, int* right, int* bottom) const;
*/

int tess_page_it_empty(tess_page_iterator_t *it, 
                       tess_page_iterator_level_e level)
{
    if(it->tess_page_iterator->Empty(
            (tesseract::PageIteratorLevel)level) == true)
        return 1;
    else
        return 0;
}

/*
PolyBlockType BlockType() const;
Pix* GetBinaryImage(PageIteratorLevel level) const;
Pix* GetImage(PageIteratorLevel level, int padding,
              int* left, int* top) const;
bool Baseline(PageIteratorLevel level,
              int* x1, int* y1, int* x2, int* y2) const;
void Orientation(tesseract::Orientation *orientation,
                 tesseract::WritingDirection *writing_direction,
                 tesseract::TextlineOrder *textline_order,
                 float *deskew_angle) const;
void ParagraphInfo(tesseract::ParagraphJustification *justification,
                   bool *is_list_item,
                   bool *is_crown,
                   int *first_line_indent) const;
*/
}

