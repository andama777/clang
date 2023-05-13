#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char magic[3];
    int width, height, max, **image;
} frame;

frame init_frame(char magic[3], int width, int height, int max);
frame process_contrast(frame f);
frame moving_average(frame f);
frame median_filter(frame f, int bsize);
