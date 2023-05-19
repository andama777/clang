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

frame scale(frame f, float width_scale, float height_scale){
    frame imageout = init_frame(f.magic, (int)(f.width * width_scale), (int)(f.height * height_scale), f.max);
    float x0, y0, a, b;
    int u, v;
    for (int y = 0; y < imageout.height; y++){
        for (int x = 0; x < imageout.width; x++){
            x0 = (float)x / width_scale;
            y0 = (float)y / height_scale;
            if(0 <= x0 && x0 < f.width - 1 && 0 <= y0 && y0 < f.height - 1){
                u = (int)x0;
                v = (int)y0;
                a = 1 / (x0 - u);
                b = 1 / (y0 - v);
                imageout.image[y][x] = (int)(
                    (1 - a) * (1 - b) * f.image[v][u] +
                    a * (1 - b) * f.image[v][u+1] +
                    (1 - a) * b * f.image[v+1][u] +
                    a * b * f.image[v+1][u+1]
                );
            }
        }
    }

    return imageout;
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

frame moving_average(frame f){
    frame imageout = f;

    for (int i = 0; i < f.height; i++){
        for (int j = 0; j < f.width; j++){
            if(i == 0 || i == f.height - 1
            || j == 0 || j == f.width - 1 ){
                imageout.image[i][j] = f.image[i][j];
            } else {
                imageout.image[i][j] = (
                    f.image[i-1][j-1] + f.image[i-1][j] + f.image[i-1][j+1] +
                    f.image[i][j-1]   + f.image[i][j]   + f.image[i][j+1]   +
                    f.image[i+1][j-1] + f.image[i+1][j] + f.image[i+1][j+1]
                ) / 9;
            }
        }
    }

    return imageout;
}

frame median_filter(frame f, int bsize){

    int mid;

    for(int i = 0; i <= f.height - bsize; i += bsize){
        for(int j = 0; j <= f.width - bsize; j += bsize){

            //ブロック内のピクセルの平均値を求める
            for (int k = i; k < i + bsize; k++){
                for (int l = j; l < j + bsize; l++){
                    mid += f.image[k][l];
                }
            }
            mid = mid / (bsize * bsize);
            // ブロック内のピクセルに代入する

            for (int k = i; k < i + bsize; k++){
                for (int l = j; l < j + bsize; l++){
                    f.image[k][l] = mid;
                }
            }
            
        }
    }

    return f;
}


