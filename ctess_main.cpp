#include <ctesseract/ctess_main.h>

extern "C" {
int tess_create(const char *data_path, const char *language, tess_api_t *api)
{
    assert(language != NULL);

    api->tess_api = new tesseract::TessBaseAPI();

    // Initialize tesseract-ocr with English, without specifying tessdata path.
    if(api->tess_api->Init(data_path, language) != 0) 
    {
        api->tess_api->End();

        return -1;
    }

    return 0;
}

int tess_destroy(tess_api_t *api)
{
    api->tess_api->End();
    delete api->tess_api;
    
    return 0;
}

const char *tess_version()
{
    return tesseract::TessBaseAPI::Version();
}

const char *tess_get_init_languages_as_string(tess_api_t *api)
{
    return api->tess_api->GetInitLanguagesAsString();
}

int tess_init_lang_mod(tess_api_t *api, 
                       const char* datapath, 
                       const char* language)
{
    return api->tess_api->InitLangMod(datapath, language);
}

//  void GetLoadedLanguagesAsVector(GenericVector<STRING>* langs) const;
//  void GetAvailableLanguagesAsVector(GenericVector<STRING>* langs) const;
//  void InitForAnalysePage();
//  void ReadConfigFile(const char* filename);

int tess_set_page_seg_mode(tess_api_t *api, tess_page_seg_mode_e mode)
{
    api->tess_api->SetPageSegMode((tesseract::PageSegMode)mode);
    
    return 0;
}

tess_page_seg_mode_e tess_get_page_seg_mode(tess_api_t *api)
{
    return (tess_page_seg_mode_e)api->tess_api->GetPageSegMode();
}

char *tess_tesseract_rect(tess_api_t *api, 
                          const unsigned char* imagedata,
                          int bytes_per_pixel, 
                          int bytes_per_line, 
                          int left, 
                          int top, 
                          int width, 
                          int height)
{
    return api->tess_api->TesseractRect(imagedata, bytes_per_pixel, 
                                        bytes_per_line, left, top, width, 
                                        height);
}

int tess_clear_adaptive_classifier(tess_api_t *api)
{
    api->tess_api->ClearAdaptiveClassifier();

    return 0;
}

int tess_set_image_details(tess_api_t *api, 
                           const unsigned char *imagedata, 
                           int width, 
                           int height, 
                           int bytes_per_pixel, 
                           int bytes_per_line)
{
    api->tess_api->SetImage(imagedata, 
                            width, 
                            height, 
                            bytes_per_pixel, 
                            bytes_per_line);

    return 0;
}

int tess_set_image_pix(tess_api_t *api, const PIX *pix)
{
    api->tess_api->SetImage(pix);

    return 0;
}

int tess_set_source_resolution(tess_api_t *api, int ppi)
{
    api->tess_api->SetSourceResolution(ppi);

    return 0;
}

int tess_set_rectangle(tess_api_t *api, int left, int top, int width, 
                       int height)
{
    api->tess_api->SetRectangle(left, top, width, height);

    return 0;
}
/*
// TODO: We need to encapsulte the ImageThresholder type.
int tess_set_thresholder(tess_api_t *api, 
                         tesseract::ImageThresholder *thresholder)
{
    api->tess_api->SetThresholder(thresholder);

    return 0;
}
*/

PIX *tess_get_thresholded_image(tess_api_t *api)
{
    return api->tess_api->GetThresholdedImage();
}

BOXA *tess_get_regions(tess_api_t *api, 
                       PIXA **pixa)
{
    return api->tess_api->GetRegions(pixa);
}

BOXA *tess_get_text_lines(tess_api_t *api, PIXA **pixa, int **blockids)
{
    return api->tess_api->GetTextlines(pixa, blockids);
}

BOXA *tess_get_strips(tess_api_t *api, PIXA **pixa, int **blockids)
{
    return api->tess_api->GetStrips(pixa, blockids);
}

BOXA *tess_get_words(tess_api_t *api, PIXA **pixa)
{
    return api->tess_api->GetWords(pixa);
}

BOXA *tess_get_connected_components(tess_api_t *api, PIXA **cc)
{
    return api->tess_api->GetConnectedComponents(cc);
}

BOXA *tess_get_component_images(tess_api_t *api, 
                                const tess_page_iterator_level_e level,
                                const int text_only, 
                                PIXA **pixa, 
                                int **blockids)
{
    return api->tess_api->GetComponentImages(
            (tesseract::PageIteratorLevel)level, 
            (text_only == 1), 
            pixa, 
            blockids);
}

int tess_get_thresholded_image_scale_factor(tess_api_t *api)
{
    return api->tess_api->GetThresholdedImageScaleFactor();
}

int tess_dump_pgm(tess_api_t *api, const char* filename)
{
    api->tess_api->DumpPGM(filename);
    
    return 0;
}

int tess_analyse_layout(tess_api_t *api, tess_page_iterator_t *result)
{
    tesseract::PageIterator *tess_it = api->tess_api->AnalyseLayout();
    if(tess_it == NULL)
        return -1;

    result->tess_page_iterator = tess_it;
    return 0;
}

// TODO: Encapsulate ETEXT_DESC *, and allow it as a parameter (like with the 
//       original library).
int tess_recognize(tess_api_t *api)
{
    return api->tess_api->Recognize(NULL);
}

int tess_process_pages_string(tess_api_t *api, const char *filename, 
                              const char *retry_config, int timeout_millisec,
                              tess_string_t *text_out)
{
    // This has to be destroyed with c=tess_string_free().
    text_out->tess_string = new STRING();

    if(api->tess_api->ProcessPages(filename, 
                                   retry_config, 
                                   timeout_millisec,
                                   text_out->tess_string) == false)
        return -1;

    return 0;
}

// TODO: Encapsulate TessResultRenderer
/*
int tess_process_pages_renderer(tess_api_t *api, const char* filename,
                                const char* retry_config, int timeout_millisec,
                                TessResultRenderer* renderer)
{
    if(api->tess_api->ProcessPages(filename, retry_config, timeout_millisec,
                                   renderer) == false)
        return -1;

    return 0;
}
*/

int tess_process_page_string(tess_api_t *api, PIX *pix, int page_index, 
                             const char* filename, const char* retry_config, 
                             int timeout_millisec, tess_string_t *text_out)
{
    // This has to be destroyed with c=tess_string_free().
    text_out->tess_string = new STRING();

    if(api->tess_api->ProcessPage(pix, 
                                  page_index, 
                                  filename, 
                                  retry_config, 
                                  timeout_millisec, 
                                  text_out->tess_string) == false)
        return -1;
    
    return 0;
}

// TODO: Encapsulate TessResultRenderer
/*
int tess_process_page_renderer(tess_api_t *api, PIX *pix, int page_index, 
                               const char* filename, const char* retry_config, 
                               int timeout_millisec, 
                               TessResultRenderer* renderer)
{
    if(api->tess_api->ProcessPage(pix, page_index, filename, retry_config, 
                                  timeout_millisec, renderer) == false)
        return -1;
    
    return 0;
}
*/

int tess_get_iterator(tess_api_t *api, tess_mr_iterator_t *result)
{
    tesseract::ResultIterator *tess_result = api->tess_api->GetIterator();
    if(tess_result == NULL)
        return -1;

    tess_mr_init_for_result_it(result, tess_result);

    return 0;
}

/*
int tess_get_mutable_iterator(tess_api_t *api, tess_mr_iterator_t *result)
{
    tesseract::MutableIterator *it = api->tess_api->GetMutableIterator();
    if(it == NULL)
        return -1;

    tess_mr_init_for_mutable_it(result, it);

    return 0;
}
*/

char *tess_get_utf8_text(tess_api_t *api)
{
    return api->tess_api->GetUTF8Text();
}

char *tess_get_hocr_text(tess_api_t *api, int page_number)
{
    return api->tess_api->GetHOCRText(page_number);
}

char *tess_get_box_text(tess_api_t *api, int page_number)
{
    return api->tess_api->GetBoxText(page_number);
}

char *tess_get_unlv_text(tess_api_t *api)
{
    return api->tess_api->GetUNLVText();
}

int tess_mean_text_conf(tess_api_t *api)
{
    return api->tess_api->MeanTextConf();
}

int *tess_all_word_confidences(tess_api_t *api)
{
    return api->tess_api->AllWordConfidences();
}

int tess_adapt_to_word_str(tess_api_t *api, tess_page_seg_mode_e mode, 
                            const char* wordstr)
{
    if(api->tess_api->AdaptToWordStr((tesseract::PageSegMode)mode, 
                                     wordstr) == false)
        return -1;
    
    return 0;
}

int tess_clear(tess_api_t *api)
{
    api->tess_api->Clear();
    
    return 0;
}

int tess_is_valid_word(tess_api_t *api, const char *word)
{
    return api->tess_api->IsValidWord(word);
}

int tess_get_text_direction(tess_api_t *api, int* out_offset, float* out_slope)
{
    if(api->tess_api->GetTextDirection(out_offset, out_slope) == true)
        return 1;
    else
        return 0;
}

//void SetDictFunc(DictFunc f);
//  void SetProbabilityInContextFunc(ProbabilityInContextFunc f);
//  void SetParamsModelClassifyFunc(ParamsModelClassifyFunc f);
//  void SetFillLatticeFunc(FillLatticeFunc f);
/*
// TODO: Encapsulate OSResults *.
int tess_detect_os(tess_api_t *api, OSResults *os_results)
{
    if(api->tess_api->DetectOS(os_results) == false)
        return -1;
    
    return 0;
}
*/

// TODO: Write functions to access tess_features_t.

int tess_get_features_for_blob(tess_api_t *api, 
                               tess_blob_t *blob, 
                               const DENORM &denorm,
                               tess_features_t *int_features,
                               int *num_features, 
                               int *feature_outline_index)
{
    api->tess_api->GetFeaturesForBlob(blob->tess_blob, 
                                      denorm,
                                      int_features->tess_features, 
                                      num_features, 
                                      feature_outline_index);

    return 0;
}

int tess_find_row_for_box(tess_api_t *api, 
                           tess_blocklist_t *blocks, 
                           int left, 
                           int top,
                           int right, 
                           int bottom,
                           tess_row_t *result)
{
    ROW *row = api->tess_api->FindRowForBox(blocks->tess_blocks, 
                                            left, 
                                            top,
                                            right, 
                                            bottom);

    if(row == NULL)
        return -1;

    result->tess_row = row;
    return 0;
}

int tess_run_adaptive_classifier(tess_api_t *api, 
                                 tess_blob_t *blob,
                                 const DENORM &denorm,
                                 int num_max_matches, 
                                 int *unichar_ids,
                                 float *ratings, 
                                 int *num_matches_returned)
{
    api->tess_api->RunAdaptiveClassifier(blob->tess_blob, 
                                         denorm,
                                         num_max_matches, 
                                         unichar_ids,
                                         ratings, 
                                         num_matches_returned);

    return 0;
}

const char *tess_get_unichar(tess_api_t *api, int unichar_id)
{
    return api->tess_api->GetUnichar(unichar_id);
}

// const Dawg *GetDawg(int i) const;
// int NumDawgs() const;

int tess_make_tess_ocr_row(float baseline, 
                           float xheight,
                           float descender, 
                           float ascender,
                           tess_row_t *result)
{
    ROW *row = tesseract::TessBaseAPI::MakeTessOCRRow(baseline, 
                                                      xheight, 
                                                      descender,
                                                      ascender);
    
    if(row == NULL)
        return -1;

    result->tess_row = row;
    return 0;
}

int tess_make_tblob(PIX *pix, tess_blob_t *result)
{
    TBLOB *blob = tesseract::TessBaseAPI::MakeTBLOB(pix);
    if(blob == NULL)
        return -1;
    
    result->tess_blob = blob;
    return 0;
}

int tess_normalize_tblob(tess_blob_t *tblob, 
                         tess_row_t *row, 
                         bool numeric_mode, 
                         DENORM *denorm)
{
    tesseract::TessBaseAPI::NormalizeTBLOB(tblob->tess_blob, 
                                           row->tess_row, 
                                           numeric_mode,
                                           denorm);

    return 0;
}

//  Tesseract* const tesseract() const {
//  OcrEngineMode const oem() const {
//  void InitTruthCallback(TruthCallback *cb) { truth_cb_ = cb; }
//  CubeRecoContext *GetCubeRecoContext() const;

int tess_set_min_orientation_margin(tess_api_t *api, double margin)
{
    api->tess_api->set_min_orientation_margin(margin);
    
    return 0;
}

int tess_get_block_text_orientations(tess_api_t *api, 
                                     int **block_orientation,
                                     void **vertical_writing,
                                     int *vw_size)
{
    if(vw_size != NULL)
        *vw_size = sizeof(bool);
    
    api->tess_api->GetBlockTextOrientations(block_orientation,
                                            (bool **)vertical_writing);

    return 0;
}

int tess_find_lines_create_block_list(tess_api_t *api, 
                                      tess_blocklist_t *result)
{
    BLOCK_LIST *blocks = api->tess_api->FindLinesCreateBlockList();
    if(blocks == NULL)
        return -1;
    
    result->tess_blocks = blocks;
    return 0;
}

int tess_delete_block_list(tess_blocklist_t *blocks)
{
    tesseract::TessBaseAPI::DeleteBlockList(blocks->tess_blocks);
    
    return 0;
}

int tess_delete_string(char *text)
{
    delete[] text;

    return 0;
}
}

