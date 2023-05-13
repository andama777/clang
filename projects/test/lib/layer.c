// コンソールに文字列を表示するレイヤーを定義する

# include "Layer.h"

Layer create_layer(
    int start_x,
    int start_y,
    int width,
    int height,
    int priority,
    int windowWidth,
    int windowHeight,
    bool is_framed
    ) {
    Layer layer;

    // レイヤーのサイズチェック
    if (start_x < 0 || windowWidth - 1 < start_x
        || start_y < 0 || windowHeight - 1 < start_y) {
        printf("error: invalid layer size\n");
        exit(1);
    }
    layer.start_x = start_x;
    layer.start_y = start_y;

    // printf("width: %d, height: %d\n", width, height);
    // printf("windowWidth: %d, windowHeight: %d\n", windowWidth, windowHeight);
    if (width < 0 || windowWidth  < start_x + width
        || height < 0 || windowHeight < start_y + height) {
        printf("error: invalid layer size\n");
        exit(1);
    }
    layer.width = width;
    layer.height = height;

    layer.priority = priority;

    return layer;
}

// void print_string(Layer *layer, int x, int y, char *s) {
//     memcpy(&layer->screen[y * WIDTH + x], s, strlen(s));
// }

