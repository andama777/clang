// コンソールに文字列を表示するレイヤーを定義する

# include "Layer.h"

Layer create_layer(
    int start_x,
    int start_y,
    int width,
    int height,
    int priority
    ) {
    Layer layer;
    layer.start_x = start_x;
    layer.start_y = start_y;
    layer.width = width;
    layer.height = height;
    layer.priority = priority;

    return layer;
}

// void print_string(Layer *layer, int x, int y, char *s) {
//     memcpy(&layer->screen[y * WIDTH + x], s, strlen(s));
// }

