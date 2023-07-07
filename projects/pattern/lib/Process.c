#include "Process.h"

label_info max_label_info;

label_info* info;

int label;

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

frame process(frame f, void* args){
    int func_id = ((int *)args)[0];
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
        case 6:
            return binarization(f, ((int *)args)[2]);
        case 7:
            return discriminant_analysis(f);
        default:
            printf("Error: func_id is invalid.\n");
            exit(1);
    }
}

void labeling(int i, int j, int label, frame f){
    if (i < 0 || i >= f.height || j < 0 || j >= f.width) return;
    if (f.image[i][j] != f.max) return;
    f.image[i][j] = label;
    if (f.image[i+1][j] == f.max) labeling(i+1, j, label, f);
    if (f.image[i-1][j] == f.max) labeling(i-1, j, label, f);
    if (f.image[i][j+1] == f.max) labeling(i, j+1, label, f);
    if (f.image[i][j-1] == f.max) labeling(i, j-1, label, f);
}

frame labeling_frame(frame f){
    // 領域にラベルをつける
    label = 1;
    for (int i = 0; i < f.height; i++){
        for (int j = 0; j < f.width; j++){
            if (f.image[i][j] == f.max){
                labeling(i, j, label, f);
                label++;
            }
        }
    }

    // ラベリングした領域の情報を格納する
    info = calloc(label, sizeof(label_info));
    for (int i = 0; i < f.height; i++){
        for (int j = 0; j < f.width; j++){
            if (f.image[i][j] != 0){
                info[f.image[i][j]].label_number = f.image[i][j];
                info[f.image[i][j]].area++;
                info[f.image[i][j]].xwt += j;
                info[f.image[i][j]].ywt += i;
            }
        }
    }

    // ラベリングした領域の情報を出力 また、一番大きい領域のラベルを返す
    printf("label number area xwt ywt\n");
    int max_label = 0;
    for (int i = 0; i < label; i++){
        if (info[i].area == 0) continue;
        info[i].xwt /= info[i].area;
        info[i].ywt /= info[i].area;
        printf("%d %d %d %d\n", info[i].label_number, info[i].area, info[i].xwt, info[i].ywt);
        if (info[i].area > info[max_label].area) max_label = i;
    }

    // 一番大きい領域のラベル情報
    max_label_info = info[max_label];

    //一番大きい領域のラベルを表示
    printf("max label: %d\n", max_label);

    return f;
}

void print_area_info(frame f){
    frame labeled_frame = labeling_frame(f);
}

// 画像を綺麗に二値化するような閾値を求める
frame discriminant_analysis(frame f){
    int k = 0; // 濃度
    int pix_num = f.width * f.height; // 総画素数
    int threshold = 0; // 閾値
    int*n = calloc(f.max, sizeof(int) * f.max); // 濃度がiの画素数
    float*p = calloc(f.max, sizeof(float) * f.max); // 濃度が0~kの生起確率
    float*m = calloc(f.max, sizeof(float) * f.max); // 0~kまでの平均濃度

    // 濃度ごとの画素数を求める
    for (int i = 0; i < f.height; i++){ 
        for (int j = 0; j < f.width; j++){
            n[f.image[i][j]]++;
        }
    }

    // 濃度0~kまでの生起確率と、濃度0~kまでの平均濃度を求める
    m[0] = 0; // 濃度0の平均濃度は0
    p[0] = (float)n[0] / pix_num; // 濃度0の生起確率
    for (k = 1; k <= f.max; k++){
        p[k] = p[k-1] + (float)n[k] / pix_num; // 濃度0~kまでの生起確率を求める
        m[k] = m[k-1] + (float)k * n[k] / pix_num; // 濃度0~kまでの平均濃度を求める
        // printf("k = %d, m = %f\n", k, m[k]);
    }

    // 閾値kの時のクラス間分散を求め、最大の閾値を求める
    float tmp_var=0, var=0;
    for (k = 0; k <= f.max; k++){
        var = pow(m[f.max] * p[k] - m[k], 2) / (p[k] * (1 - p[k])); // クラス間分散を求める
        if (var > tmp_var){
            tmp_var = var;
            threshold = k;
        }
    }

    printf("閾値: %d\n", threshold);

    free(n); free(p); free(m); // メモリ解放

    return binarization(f, threshold);
}

frame binarization(frame f, int threshold){
    int max = 255;
    for (int y = 0; y < f.height; y++){
        for (int x = 0; x < f.width; x++){
            if (f.image[y][x] > threshold){
                f.image[y][x] = max;
            } else {
                f.image[y][x] = 0;
            }
        }
    }

    return f;
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

frame face_area_extract(frame f){
    // deep copy
    frame bin = init_frame(f.magic, f.width, f.height, f.max);
    for (int i = 0; i < f.height; i++){
        for (int j = 0; j < f.width; j++){
            bin.image[i][j] = f.image[i][j];
        }
    }
    bin = discriminant_analysis(bin); // 画像を二値化
    
    frame labeled = labeling_frame(bin); // ラベリング
    label_info max_label = max_label_info; // 一番大きい領域のラベル情報

    // 一番大きい領域のみを抽出 マスクを作成
    for (int i = 0; i < labeled.height; i++){
        for (int j = 0; j < labeled.width; j++){
            if (labeled.image[i][j] != max_label.label_number){
                labeled.image[i][j] = 0;
            } else {
                labeled.image[i][j] = 1;
            }
        }
    }

    frame result = init_frame(f.magic, f.width, f.height, f.max);
    // オリジナルの画像にマスクをかける
    for (int i = 0; i < f.height; i++){
        for (int j = 0; j < f.width; j++){
            result.image[i][j] = f.image[i][j] * labeled.image[i][j];
        }
    }

    return result;
}

//2枚の画像を読み込み、距離を用いてテンプレートマッチングを行なう。
// 出力は、マッチング位置を表示した画像ファイルと、距離の最大値とすること
frame template_matching_distance(frame t, frame f){
    int minD = INT_MAX;
    int rx, ry; // 最適座標 result_x result_y

    for (int y = 0; y <= f.height - t.height; y++){
        for (int x = 0; x <= f.width - t.width; x++){

            int D = 0;
            for (int i = 0; i < t.height; i++){ // テンプレートとの距離を計算する
                for (int j = 0; j < t.width; j++){
                    D += abs(f.image[y+i][x+j] - t.image[i][j]);
                    if (D > minD) break; // 最小値を超えたら計算を打ち切る
                }
            }

            if (D < minD){ // 最小値と最適座標を更新する
                minD = D;
                rx = x;
                ry = y;
            }
        }
    }

    // テンプレートとの距離が最小となる座標を表示する
    printf("x: %d, y: %d\n", rx, ry);
    printf("minD: %d\n", minD);

    // マッチング位置をオリジナルの画像に白枠で表示する
    for (int i = rx; i < rx + t.width; i++){
        f.image[ry][i] = f.image[ry + t.height][i] = f.max;
    }
    for (int i = ry; i < ry + t.height; i++){
        f.image[i][rx] = f.image[i][rx + t.width] = f.max;
    }

    return f;

}

//2枚の画像を読み込み、類似度を用いてテンプレートマッチングを行なう。
// 出力は、マッチング位置を表示した画像ファイルと、類似度の最大値とすること
frame template_matching_similarity(frame t, frame f){
    double maxS = INT_MIN;
    int rx, ry; // 最適座標 result_x result_y

    for (int y = 0; y <= f.height - t.height; y++){ // テンプレートとの類似度を計算する
        for (int x = 0; x <= f.width - t.width; x++){

            double IT = 0, II = 0, TT = 0;
            for (int i = 0; i < t.height; i++){
                for (int j = 0; j < t.width; j++){
                    int yplusi = y + i;
                    int xplusj = x + j;
                    IT += f.image[yplusi][xplusj] * t.image[i][j];
                    II += f.image[yplusi][xplusj] * f.image[yplusi][xplusj];
                    TT += t.image[i][j] * t.image[i][j];
                }
            }

            double S = IT / (sqrt(II) * sqrt(TT));

            if (S > maxS){ // 最大値と最適座標を更新する
                maxS = S;
                rx = x;
                ry = y;
            }
        }
    }

    // テンプレートとの類似度が最大となる座標を表示する
    printf("x: %d, y: %d\n", rx, ry);
    printf("maxS: %f\n", maxS);

    // マッチング位置をオリジナルの画像に白枠で表示する
    for (int i = rx; i < rx + t.width; i++){
        f.image[ry][i] = f.image[ry + t.height][i] = f.max;
    }
    for (int i = ry; i < ry + t.height; i++){
        f.image[i][rx] = f.image[i][rx + t.width] = f.max;
    }

    return f;

}

frame invert_frame(frame f){
    for (int i = 0; i < f.height; i++){
        for (int j = 0; j < f.width; j++){
            f.image[i][j] = f.max - f.image[i][j];
        }
    }
    return f;
}

void k_means_classify(frame f, int k){
    frame neg = invert_frame(f);
    frame bin = discriminant_analysis(neg);
    frame labeled = labeling_frame(bin);

    // ラベル情報 グローバル変数渡し
    label_info* patterns = info;

    // ラベル数 グローバル変数渡し
    label -= 1; // 調整
    int pattern = label;
    printf("pattern number : %d\n", pattern);

    // クラスタ情報の宣言
    claster_info* clasters = (claster_info*)malloc(sizeof(claster_info) * k);

    for (int i = 0; i < k; i++){ // クラスタごとに処理を行う
        clasters[i].center = patterns[i].area;
        clasters[i].claster_num = i;
    }

    int center_error = 0;
    do {
        center_error = 0;
        for(int c = 0; c < k; c++){ // クラスタの初期化
            clasters[c].claster_num = 0;
            clasters[c].area_sum = 0;
        }

        for (int p = 0; p < pattern; p++){ // 各パターンに対して処理を行う
            int minD = INT_MAX;
            for (int c = 0; c < k; c++){ // 各クラスタについて
                int D = 0;
                for (int j = 0; j < patterns[p].area; j++){ // クラスタの中心と、各パターンの差を足しあげる
                    D += abs(clasters[c].center - patterns[p].area);
                }
                if (D < minD){ // 最も近いクラスタを探す
                    minD = D;
                    patterns[p].label_number = c; // 最も近いクラスタのラベル番号を設定する
                }
            }
            clasters[patterns[p].label_number].claster_num++; // クラスタのパターン数を1増やす
            clasters[patterns[p].label_number].area_sum += patterns[p].area; //クラスタの面積合計を更新
        }

        for (int i = 0; i < k; i++){ // クラスタの中心を更新する
            clasters[i].old_center = clasters[i].center;
            clasters[i].center = clasters[i].area_sum / clasters[i].claster_num;
            center_error += abs(clasters[i].center - clasters[i].old_center);
        }
    } while (center_error > 0); // クラスタの中心が変化しなくなるまで繰り返す

    // 結果の確認
    for (int i = 0; i < k; i++){
        printf("クラスタ%dの中心 : %d\n", i, clasters[i].center);
        printf("クラスタ%dの合計面積 : %d\n", i, clasters[i].area_sum);
        printf("クラスタ%dの数 : %d\n", i, clasters[i].claster_num);
    }
}