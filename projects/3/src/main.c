#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/Process.h"

#define INPATH "../../data/pics/image3.pgm"
#define OUTPATH "../../output/pics/image3.pgm"

FILE* init_FILE(char *path, char *mode){
    FILE *fp;
    fp = fopen(path, mode);
    if (fp == NULL) printf("Error opening file %s\n", path);
    return fp;
}

void main(){
    char infile[100], outfile[100], magic[3];
    int width, height, max;

    FILE *infp = init_FILE(INPATH, "r");

    fscanf(infp, "%s%d%d%d", magic, &width, &height, &max);

    frame f = init_frame(magic, width, height, max);

    for (int i = 0; i < f.height; i++){
        for (int j = 0; j < f.width; j++){
            fscanf(infp, "%d", &f.image[i][j]);
        }
    }

    fclose(infp);

    f = process_contrast(f); // コントラスト処理

    FILE *outfp = init_FILE(OUTPATH, "w");

    fprintf(outfp, "%s\n%d %d\n%d\n", f.magic, f.width, f.height, f.max);

    for (int i = 0; i < f.height; i++){
        for (int j = 0; j < f.width; j++){
            fprintf(outfp, "%d ", f.image[i][j]);
        }
        fprintf(outfp, "\n");
    }

    fclose(outfp);
}