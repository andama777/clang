#include "Process.h"

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