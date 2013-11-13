#ifndef __CTESS_TYPES_H
#define __CTESS_TYPES_H

typedef struct
{
    void *opaque;
} tess_api_t;

typedef enum { 
    PSM_OSD_ONLY, 
    PSM_AUTO_OSD, 
    PSM_AUTO_ONLY, 
    PSM_AUTO, 
    PSM_SINGLE_COLUMN, 
    PSM_SINGLE_BLOCK_VERT_TEXT, 
    PSM_SINGLE_BLOCK, 
    PSM_SINGLE_LINE, 
    PSM_SINGLE_WORD, 
    PSM_CIRCLE_WORD, 
    PSM_SINGLE_CHAR, 
    PSM_SPARSE_TEXT,
    PSM_SPARSE_TEXT_OSD, 
    PSM_COUNT 
} tess_page_seg_mode_e;

typedef enum {
  RIL_BLOCK,     // Block of text/image/separator line.
  RIL_PARA,      // Paragraph within a block.
  RIL_TEXTLINE,  // Line within a paragraph.
  RIL_WORD,      // Word within a textline.
  RIL_SYMBOL     // Symbol/character within a word.
} tess_page_iterator_level_e;

#endif

