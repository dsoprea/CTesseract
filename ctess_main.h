#ifndef __CTESS_MAIN_H
#define __CTESS_MAIN_H

#include <assert.h>

#include <tesseract/baseapi.h>
#include <tesseract/resultiterator.h>
#include <leptonica/allheaders.h>

#include "ctess_types.h"
#include "ctess_page_iterator.h"
#include "ctess_mr_iterator.h"
#include "ctess_string.h"

typedef struct {
    TBLOB *tess_blob;
} tess_blob_t;

typedef struct {
    INT_FEATURE_STRUCT *tess_features;
} tess_features_t;

typedef struct {
    BLOCK_LIST *tess_blocks;
} tess_blocklist_t;

typedef struct {
    ROW *tess_row;
} tess_row_t;

extern "C" {
int tess_create(const char *data_path, const char *language, tess_api_t *api);
int tess_destroy(tess_api_t *api);
const char *tess_version();
const char *tess_get_init_languages_as_string(tess_api_t *api);
int tess_init_lang_mod(tess_api_t *api, 
                       const char* datapath, 
                       const char* language);

//  void GetLoadedLanguagesAsVector(GenericVector<STRING>* langs) const;
//  void GetAvailableLanguagesAsVector(GenericVector<STRING>* langs) const;
//  void InitForAnalysePage();
//  void ReadConfigFile(const char* filename);

int tess_set_page_seg_mode(tess_api_t *api, tess_page_seg_mode_e mode);
tess_page_seg_mode_e tess_get_page_seg_mode(tess_api_t *api);
char *tess_tesseract_rect(tess_api_t *api, 
                          const unsigned char* imagedata,
                          int bytes_per_pixel, 
                          int bytes_per_line, 
                          int left, 
                          int top, 
                          int width, 
                          int height);

int tess_clear_adaptive_classifier(tess_api_t *api);
int tess_set_image_details(tess_api_t *api, 
                           const unsigned char *imagedata, 
                           int width, 
                           int height, 
                           int bytes_per_pixel, 
                           int bytes_per_line);

int tess_set_image_pix(tess_api_t *api, const Pix* pix);
int tess_set_source_resolution(tess_api_t *api, int ppi);
int tess_set_rectangle(tess_api_t *api, int left, int top, int width, 
                       int height);

/*
// TODO: We need to encapsulte the ImageThresholder type.
int tess_set_thresholder(tess_api_t *api, 
                         tesseract::ImageThresholder *thresholder)
*/

Pix *tess_get_thresholded_image(tess_api_t *api);
Boxa *tess_get_regions(tess_api_t *api, Pixa **pixa);
Boxa *tess_get_text_lines(tess_api_t *api, Pixa **pixa, int **blockids);
Boxa *tess_get_strips(tess_api_t *api, Pixa **pixa, int **blockids);
Boxa *tess_get_words(tess_api_t *api, Pixa **pixa);
Boxa *tess_get_connected_components(tess_api_t *api, Pixa **cc);
Boxa *tess_get_component_images(tess_api_t *api, 
                                const tess_page_iterator_level_e level,
                                const bool text_only, 
                                Pixa **pixa, 
                                int **blockids);

int tess_get_thresholded_image_scale_factor(tess_api_t *api);
int tess_dump_pgm(tess_api_t *api, const char* filename);
int tess_analyse_layout(tess_api_t *api, tess_page_iterator_t *result);

int tess_recognize(tess_api_t *api);

int tess_process_pages_string(tess_api_t *api, const char *filename, 
                              const char *retry_config, int timeout_millisec,
                              tess_string_t *text_out);

// TODO: Encapsulate TessResultRenderer
/*
int tess_process_pages_renderer(tess_api_t *api, const char* filename,
                                const char* retry_config, int timeout_millisec,
                                TessResultRenderer* renderer)
*/

int tess_process_page_string(tess_api_t *api, Pix* pix, int page_index, 
                             const char* filename, const char* retry_config, 
                             int timeout_millisec, tess_string_t *text_out);

// TODO: Encapsulate TessResultRenderer
/*
int tess_process_page_renderer(tess_api_t *api, Pix* pix, int page_index, 
                               const char* filename, const char* retry_config, 
                               int timeout_millisec, 
                               TessResultRenderer* renderer);
*/

int tess_get_iterator(tess_api_t *api, tess_mr_iterator_t *result);
int tess_get_mutable_iterator(tess_api_t *api, tess_mr_iterator_t *result);
char *tess_get_utf8_text(tess_api_t *api);
char *tess_get_hocr_text(tess_api_t *api, int page_number);
char *tess_get_box_text(tess_api_t *api, int page_number);
char *tess_get_unlv_text(tess_api_t *api);
int tess_mean_text_conf(tess_api_t *api);
int *tess_all_word_confidences(tess_api_t *api);
int tess_adapt_to_word_str(tess_api_t *api, tess_page_seg_mode_e mode, 
                            const char* wordstr);
int tess_clear(tess_api_t *api);
int tess_is_valid_word(tess_api_t *api, const char *word);
int tess_get_text_direction(tess_api_t *api, int* out_offset, float* out_slope);

/*
//void SetDictFunc(DictFunc f);
//  void SetProbabilityInContextFunc(ProbabilityInContextFunc f);
//  void SetParamsModelClassifyFunc(ParamsModelClassifyFunc f);
//  void SetFillLatticeFunc(FillLatticeFunc f);
/*
// TODO: Encapsulate OSResults *.
int tess_detect_os(tess_api_t *api, OSResults *os_results)
*/

// TODO: Write functions to access tess_features_t.

int tess_get_features_for_blob(tess_api_t *api, 
                               tess_blob_t *blob, 
                               const DENORM &denorm,
                               tess_features_t *int_features,
                               int *num_features, 
                               int *feature_outline_index);

int tess_find_row_for_box(tess_api_t *api, 
                           tess_blocklist_t *blocks, 
                           int left, 
                           int top,
                           int right, 
                           int bottom,
                           tess_row_t *result);

int tess_run_adaptive_classifier(tess_api_t *api, 
                                 tess_blob_t *blob,
                                 const DENORM &denorm,
                                 int num_max_matches, 
                                 int *unichar_ids,
                                 float *ratings, 
                                 int *num_matches_returned);

const char *tess_get_unichar(tess_api_t *api, int unichar_id);

// const Dawg *GetDawg(int i) const;
// int NumDawgs() const;

int tess_make_tess_ocr_row(float baseline, 
                           float xheight,
                           float descender, 
                           float ascender,
                           tess_row_t *result);

int tess_make_tblob(Pix *pix, tess_blob_t *result);
int tess_normalize_tblob(tess_blob_t *tblob, 
                         tess_row_t *row, 
                         bool numeric_mode, 
                         DENORM *denorm);

//  Tesseract* const tesseract() const {
//  OcrEngineMode const oem() const {
//  void InitTruthCallback(TruthCallback *cb) { truth_cb_ = cb; }
//  CubeRecoContext *GetCubeRecoContext() const;

int tess_set_min_orientation_margin(tess_api_t *api, double margin);
int tess_get_block_text_orientations(tess_api_t *api, 
                                     int** block_orientation,
                                     bool** vertical_writing);

int tess_find_lines_create_block_list(tess_api_t *api, 
                                      tess_blocklist_t *result);

int tess_delete_block_list(tess_blocklist_t *blocks);

int tess_delete_string(char *text);
}

#endif

