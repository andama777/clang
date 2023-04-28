#include "Window.h"

Window create_window() {
    Window window;
    window.width = WIDTH;
    window.height = HEIGHT;
    window.screen = (char **)malloc(sizeof(char *) * HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
        window.screen[i] = (char *)malloc(sizeof(char) * WIDTH);
    }
    window.layers = malloc(sizeof(Layer) * 10);
    set_layer(&window);
    return window;
}


void set_layer(Window *window){
    window->layers[0] = create_layer(1, 1, 18, 18, 0, window->width, window->height);
}

void clear_screen(Window *window) {
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            window->screen[i][j] = ' ';
        }
    }
}

void show_screen(Window *window){
    printf("\x1b[H");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++){
            if(i == 0 || i == HEIGHT - 1){
                printf("=");
            } else if (j == 0 || j == WIDTH - 1){
                printf("|");
            } else {
                printf("%c", window->screen[i][j]);
            }
        }
        printf("\n");
    }
}

void set_screen(Window *window, char *s) {
    // screnn[] というバッファに文字列をセットする
    Layer l = window->layers[0];
    int x = l.start_x;
    int y = l.start_y;
    int width = l.width;
    int height = l.height;


    for (int j = 0; j < l.width; j++) {
        window->screen[l.start_y][l.start_x + j] = s[j];
    }
}


