学籍番号 : 70810025

名前 : 神田毬央

課題番号 : 課題3

前回の課題2で実装したコードを拡張する形で課題3を実装しました。

コードは後述のmain.cのみです。

frame構造体を定義し、frameのインスタンスを初期化する関数init_frameと、

入力ファイルのデータが格納されたframeに対してコントラスト処理を行い、

frameを返す関数process_contrastを実装しました。

実装は以下のようになっています。

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPATH "../../data/pics/image3.pgm"
#define OUTPATH "../../output/pics/image3.pgm"

typedef struct {
    char magic[3];
    int width, height, max, **image;
} frame;

frame init_frame(char magic[3], int width, int height, int max){
    frame f;
    strcpy(f.magic, magic);
    f.width = width;
    f.height = height;
    f.max = max;
    f.image = (int **)malloc(sizeof(int *) * f.height);
    for (int i = 0; i < f.height; i++){
        f.image[i] = (int *)malloc(sizeof(int) * f.width);
    }
    return f;
}

frame process_contrast(frame f){
    // 最小値と最大値を求める
    int min = 255, max = 0;
    for (int i = 0; i < f.height; i++){
        for (int j = 0; j < f.width; j++){
            if ( f.image[i][j] < min ){ min = f.image[i][j]; }
            if ( f.image[i][j] > max ){ max = f.image[i][j]; }
        }
    }
    // コントラスト処理
    for (int i = 0; i < f.height; i++){
        for (int j = 0; j < f.width; j++){
            f.image[i][j] = (f.image[i][j] - min) * (f.max / (max - min));
        }
    }

    return f;
} 

void main(){
    char infile[100], outfile[100], magic[3];
    int width, height, max;
    FILE *infp, *outfp;

    infp = fopen(INPATH, "r");
    if (infp == NULL) printf("Error opening file %s\n", INPATH);

    fscanf(infp, "%s%d%d%d", magic, &width, &height, &max);

    frame f = init_frame(magic, width, height, max);

    for (int i = 0; i < f.height; i++){
        for (int j = 0; j < f.width; j++){
            fscanf(infp, "%d", &f.image[i][j]);
        }
    }

    fclose(infp);

    f = process_contrast(f); // コントラスト処理

    outfp = fopen(OUTPATH, "w");
    if (outfp == NULL) printf("Error opening file %s\n", outfile); 

    fprintf(outfp, "%s\n%d %d\n%d\n", f.magic, f.width, f.height, f.max);

    for (int i = 0; i < f.height; i++){
        for (int j = 0; j < f.width; j++){
            fprintf(outfp, "%d ", f.image[i][j]);
        }
        fprintf(outfp, "\n");
    }

    fclose(outfp);
}
```