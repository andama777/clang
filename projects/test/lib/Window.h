// Window -> layer -> console
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "Layer.h"

#define WIDTH 80
#define HEIGHT 20
#define SIZE (WIDTH * HEIGHT)

// #define LAYER_NUM 10

typedef struct {
    Layer* layers;
    int layer_num;
    int width;
    int height;
    char** screen;
} Window;

Window create_window();

void set_screen(Window *window, char *s);

void clear_screen(Window *window);

void show_screen(Window *window);

void print_string(Window *window, char *s);

//// void print_char(Window *window, int x, int y, char c);