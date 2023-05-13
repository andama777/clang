#include <errno.h>
#include <stdbool.h>

typedef struct {
    int start_x;
    int start_y;
    int width;
    int height;
    int priority;
    bool is_framed;
} Layer;

Layer create_layer(
    int start_x,
    int start_y,
    int width,
    int height,
    int priority,
    int windowWidth,
    int windowHeight,
    bool is_framed
);

// void print_string(Layer *layer, int x, int y, char *s);



