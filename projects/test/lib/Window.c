#include "Window.h"

Window create_window() {
    Window window;
    window.width = WIDTH;
    window.height = HEIGHT;
    window.screen = malloc(SIZE);
    window.layers = malloc(sizeof(Layer) * 10);
    set_layer(&window);
    return window;
}

void set_layer(Window *window){
    window->layers[0] = create_layer(0, 0, 20, 20, 0);
}

void clear_screen(Window *window) {
    memset(window->screen, ' ', SIZE);
}

void show_screen(Window *window) {
    printf("\x1b[H");
    for (int i = 0; i < SIZE; i++) {
        putchar(window->screen[i]);
        if ((i + 1) % WIDTH == 0) {
            putchar('\n');
        }
    }
}

void print_string(Window *window, char *s) {
    Layer l = window->layers[0];
    int x = l.start_x;
    int y = l.start_y;
    int width = l.width;
    int height = l.height;
    memcpy(&window->screen[y * width + x], s, strlen(s));
}


