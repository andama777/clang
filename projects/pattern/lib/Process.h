#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Interface.h"

#define func_count 8
typedef struct {
    char magic[3];
    int width, height, max;
    int **image;
    int* args;
} frame;

frame init_frame(char magic[3], int width, int height, int max);
frame process(frame f, void* args);
frame discriminant_analysis(frame f);
frame binarization(frame f, int threshold);
frame rotate(frame f, int axis_x, int axis_y, int rad);
frame contrast(frame f);
frame moving_average(frame f);
frame median_filter(frame f, int bsize);
frame scale(frame f, float width_scale, float height_scale);
frame affine(frame f, double a, double b, double c, double d, double e, double f2);

typedef struct {
    char name[20];
    int args_num;
} function_info;

