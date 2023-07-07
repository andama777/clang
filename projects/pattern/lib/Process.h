#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "Interface.h"

#define func_count 8
typedef struct {
    char magic[3];
    int width, height, max;
    int **image;
    int* args;
} frame;

typedef struct {
    int label_number;
    int area;
    int xwt, ywt; // 重心
}label_info;

typedef struct {
    int center;
    int old_center;
    int claster_num; // クラスタ番号
    int area_sum; // 面積の合計
}claster_info;

frame init_frame(char magic[3], int width, int height, int max);
frame process(frame f, void* args);
void print_area_info(frame f);
void labeling(int i, int j, int label, frame f);
frame labeling_frame(frame f);
frame discriminant_analysis(frame f);
frame binarization(frame f, int threshold);
frame rotate(frame f, int axis_x, int axis_y, int rad);
frame contrast(frame f);
frame moving_average(frame f);
frame median_filter(frame f, int bsize);
frame scale(frame f, float width_scale, float height_scale);
frame affine(frame f, double a, double b, double c, double d, double e, double f2);
frame face_area_extract(frame f);
frame template_matching_distance(frame t, frame f);
frame template_matching_similarity(frame t, frame f);
frame invert_frame(frame f);
void k_means_classify(frame f, int k);

typedef struct {
    char name[30];
    int args_num;
} function_info;