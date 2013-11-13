#include <stdio.h>

#include <leptonica/allheaders.h>

#include <ctess_api/ctess_types.h>
#include <ctess_api/ctess_main.h>

// Process individual blocks of the document. Allows you to identify visual 
// separate parts of the document.
int recognize_iterate(tess_api_t *api)
{
    if(tess_recognize(api) != 0)
        return -1;

    int confidence = tess_mean_text_conf(api);
    printf("Confidence: %d\n", confidence);
    if(confidence < 80)
        printf("Confidence is low!\n");

    tess_mr_iterator_t it;
    tess_get_iterator(api, &it);

    do 
    {
        printf("=================\n");
        if(tess_mr_it_empty(&it, RIL_PARA) == 1)
            continue;

        char *para_text = tess_mr_it_get_utf8_text(&it, RIL_PARA);
        printf("%s", para_text);
        tess_delete_string(para_text);
    } while (tess_mr_it_next(&it, RIL_PARA) == 1);

    tess_mr_it_delete(&it);
    return 0;
}

// Process the document and return the complete thing as a single string.
int recognize_complete(tess_api_t *api)
{
    if(tess_recognize(api) != 0)
        return -1;

    int confidence = tess_mean_text_conf(api);
    printf("Confidence: %d\n", confidence);
    if(confidence < 80)
        printf("Confidence is low!\n");

    char *para_text = tess_get_utf8_text(api);
    printf("%s", para_text);
    tess_delete_string(para_text);

    return 0;
}

int main()
{
    tess_api_t api;

    if(tess_create(NULL, "eng", &api) != 0)
        return 1;

    // Open input image with leptonica library
    PIX *image;
    if((image = pixRead("../receipt4.png")) == NULL)
    {
        pixDestroy(&image);
        tess_destroy(&api);
        return 2;
    }
 
    if(tess_set_image_pix(&api, image) != 0)
    {
        pixDestroy(&image);
        tess_destroy(&api);
        return 3;
    }

    if(recognize_iterate(&api) != 0)
    {
        pixDestroy(&image);
        tess_destroy(&api);
        return 4;
    }

    pixDestroy(&image);
    tess_destroy(&api);

    return 0;
}

