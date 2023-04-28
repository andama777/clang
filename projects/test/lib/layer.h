
typedef struct {
    int start_x;
    int start_y;
    int width;
    int height;
    int priority;
} Layer;

Layer create_layer(
    int start_x,
    int start_y,
    int width,
    int height,
    int priority
);

// void print_string(Layer *layer, int x, int y, char *s);



