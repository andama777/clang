#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25
#define SIZE (WIDTH * HEIGHT)
char screen[SIZE];

typedef struct {
    char screen[SIZE];
} console;

void clear_screen(console *con);

void show_screen(console *con);

void put_string(console *con, int x, int y, char *s);

void put_char(console *con, int x, int y, char c);