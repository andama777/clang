// #define WIDTH 80
// #define HEIGHT 25
// #define SIZE (WIDTH * HEIGHT)
// char screen[SIZE];

// typedef struct {
//     char screen[SIZE];
// } console;

#include "console.h"

// 画面のバッファをクリアする
void clear_screen(console *con)
{
    memset(con->screen, ' ', SIZE);
}

// 画面のバッファを表示する
void show_screen(console *con)
{
    printf("\x1b[H");
    for (int i = 0; i < SIZE; i++) {
        putchar(con->screen[i]);
        if ((i + 1) % WIDTH == 0) {
            putchar('\n');
        }
    }
}

// 画面のバッファに文字列を配置する
void put_string(console *con, int x, int y, char *s)
{
    memcpy(&con->screen[y * WIDTH + x], s, strlen(s));
}

// 画面のバッファに文字を配置する
void put_char(console *con, int x, int y, char c)
{
    con->screen[y * WIDTH + x] = c;
}

int main()
{
    int i = 0;
    console con;

    while(1){

        clear_screen(&con);
        put_string(&con, 0, 0, "Hello, world!");
        put_string(&con, 0, 1, "こんにちは世界！");
        put_string(&con, 0, 2, "你好，世界！");

        // i = i+1して表示
        char str[10];
        sprintf(str, "%d", i++);
        put_string(&con, 0, 3, str);

        show_screen(&con);
        usleep(1 * 1000 * 1000);
    }

    return 0;
}













// // 画面のバッファをクリアする
// void clear_screen()
// {
//     memset(screen, ' ', SIZE);
// }

// // 画面のバッファを表示する
// void show_screen()
// {
//     printf("\x1b[H");
//     for (int i = 0; i < SIZE; i++) {
//         putchar(screen[i]);
//         if ((i + 1) % WIDTH == 0) {
//             putchar('\n');
//         }
//     }
// }

// // 画面のバッファに文字列を配置する
// void put_string(int x, int y, char *s)
// {
//     memcpy(&screen[y * WIDTH + x], s, strlen(s));
// }

// // 画面のバッファに文字を配置する
// void put_char(int x, int y, char c)
// {
//     screen[y * WIDTH + x] = c;
// }

// void main()
// {
//     int i = 0;

//     while(1){

//         clear_screen();
//         put_string(0, 0, "Hello, world!");
//         put_string(0, 1, "こんにちは世界！");
//         put_string(0, 2, "你好，世界！");

//         // i = i+1して表示
//         char str[10];
//         sprintf(str, "%d", i++);
//         put_string(0, 3, str);
//         show_screen();
//         usleep(1 * 1000 * 1000);
//     }
// }




