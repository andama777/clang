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

frame process(frame f){
    // コンソールから操作を選択
    void* args = console();
    // printf("args = %p\n", args);
    // printf("args[0] = %d\n", ((int *)args)[0]);
    int func_id = ((int *)args)[0];
    printf("func_id = %d\n", func_id);
    switch (func_id){
        case 0:
            return contrast(f);
        case 1:
            return moving_average(f);
        case 2:
            return median_filter(f, ((int *)args)[2]);
        case 3:
            return scale(f, ((float *)args)[2], ((float *)args)[3]);
        case 4:
            return rotate(f, ((int *)args)[2], ((int *)args)[3], ((int *)args)[4]);
        case 5:
            return affine(f, ((int *)args)[2], ((int *)args)[3], ((int *)args)[4], ((int *)args)[5], ((int *)args)[6], ((int *)args)[7]);
        default:
            printf("Error: func_id is invalid.\n");
            exit(1);
    }

}

frame affine(frame f, double a, double b, double c, double d, double e, double f2){
    frame imageout = init_frame(f.magic, f.width, f.height, f.max);
    float x0, y0, alpha, beta, t;
    int u,v;

    for (int y = 0; y < f.height; y++){
        for (int x = 0; x < f.width; x++){
            if ((a * e - b * d) == 0) continue; // 逆行列が存在しない場合(行列式が0の場合
            t = 1 / (a * e - b * d); // temp
            x0 = t * (e * x - b * y + b * f2 - c * e);
            y0 = t * (-d * x + a * y - a * f2 + c * d);

            if(0 <= x0 && x0 < f.width - 1 && 0 <= y0 && y0 < f.height - 1){ 
                u = (int)x0;
                v = (int)y0;
                alpha = x0 - u;
                beta = y0 - v;
                imageout.image[y][x] = (int)( 
                    (1 - alpha) * (1 - beta) * f.image[v][u] +
                    alpha * (1 - beta) * f.image[v][u + 1] +
                    (1 - alpha) * beta * f.image[v + 1][u] +
                    alpha * beta * f.image[v + 1][u + 1]
                );
            }
        }
    }

    return imageout;
}

frame rotate(frame f, int axis_x, int axis_y, int angle){
    frame imageout = init_frame(f.magic, f.width, f.height, f.max);
    float x0, y0, a, b; // 回転前の座標
    int u,v;
    float radian = angle * (M_PI / 180);
    double r_sin = sin(radian);
    double r_cos = cos(radian);

    for (int y = 0; y < f.height; y++){
        for (int x = 0; x < f.width; x++){
            x0 = (x - axis_x) * r_cos + (y - axis_y) * r_sin + axis_x;
            y0 = (y - axis_y) * r_cos - (x - axis_x) * r_sin + axis_y;
            
            if(0 <= x0 && x0 < f.width - 1 && 0 <= y0 && y0 < f.height - 1){ 
                u = (int)x0;
                v = (int)y0;
                a = x0 - u;
                b = y0 - v;
                imageout.image[y][x] = (int)(
                    (1 - a) * (1 - b) * f.image[v][u] + a * (1 - b) * f.image[v][u+1] +
                    (1 - a) * b * f.image[v+1][u] + a * b * f.image[v+1][u+1]
                );
            }
        }
    }

    return imageout;
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
                a = x0 - u;
                b = y0 - v;
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

frame contrast(frame f){
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