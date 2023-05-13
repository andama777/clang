#include "Window.h"

Window create_window() {
    Window window;
    window.width = WIDTH;
    window.height = HEIGHT;
    window.screen = (char **)malloc(sizeof(char *) * HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
        window.screen[i] = (char *)malloc(sizeof(char) * WIDTH);
    }
    window.layer_num = 0;;
    set_layer(&window);
    return window;
}


void set_layer(Window *window){
    window->layers[0] = create_layer(0, 0, 80, 5, 0, window->width, window->height, true);
    window->layers[1] = create_layer(0, 15, 80, 5, 1, window->width, window->height, true);
    window->layer_num = 2;
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
            if(i == 0){
                if(j == 0){
                    printf("┏");
                } else if (j == WIDTH - 1){
                    printf("┓");
                } else {
                    printf("━");
                }
            } else if (i == HEIGHT - 1){
                if(j == 0){
                    printf("┗");
                } else if (j == WIDTH - 1){
                    printf("┛");
                } else {
                    printf("━");
                }
            } else if (j == 0 || j == WIDTH - 1){
                printf("┃");
            } else {
                printf("%c", window->screen[i][j]);
            }
        }
        printf("\n");
    }
}

void set_screen(Window *window, char *s) {
    // screnn[] というバッファに文字列をセットする
    Layer l;
    for (int i = window->layer_num - 1; i > -1; i--) {
        l = window->layers[i];
        printf("layer: %d\n", i);
        // printf("str %s\n", s);

        char wall;
        for (int i = 0; i < l.height; i++){
            for (int j = 0; j < l.width; j++){
                bool is_lr_edge = (j == 0 && j == l.width);
                bool is_ud_edge = (i == 0 && i == l.height);
                
                if (!l.is_framed) {
                    wall = ' ';
                } else if (is_lr_edge && is_ud_edge) {
                    wall = '╋';
                } else if (is_lr_edge) {
                    wall = '┃';
                } else {
                    wall = '━';
                }

                if (is_lr_edge || is_ud_edge) {
                    // if (i != 0) {
                    //     window->screen[l.start_y][l.start_x + j] = wall;
                    // } else {
                    //     window->screen[l.start_y][l.start_x + j] = wall;
                    // }
                    window->screen[l.start_y][l.start_x + j] = wall;
                } else if (i == 1 && j < strlen(s)) {
                    window->screen[l.start_y + i][l.start_x + j + 1] = s[j];
                }
            }
        }
    }
}


