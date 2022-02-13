#include <chromaprint.h>

void fnc(){
    ChromaprintContext *ctx;
    char *fp;

    const int sample_rate = 44100;
    const int num_channels = 2;

    ctx = chromaprint_new(CHROMAPRINT_ALGORITHM_DEFAULT);

    chromaprint_start(ctx, sample_rate, num_channels);
    while (has_more_data) {
        chromaprint_feed(ctx, data, size);
    }
    chromaprint_finish(ctx);

    chromaprint_get_fingerprint(ctx, &fp);
    printf("%s\n", fp);
    chromaprint_dealloc(fp);

    chromaprint_free(ctx);
}

int main(){
    fnc();
    return 0;
}

