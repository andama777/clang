// libフォルダのconsole.hを使う

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
#include <stdbool.h>

#include "../lib/console.h"

void main()
{
    long i = 0;
    bool is_running = true;
    float game_time = 0;

    console con;

    while(is_running){
        game_time += 0.001;

        clear_screen(&con);

        char str[10];
        sprintf(str, "GameTime : %f", game_time);
        put_string(&con, 0, 0, str);
        //put_string(&con, 0, 0, "Hello, world!");

        show_screen(&con);
        usleep(1 * 1000);
    }

    // while(1){

    //     clear_screen(&con);

    //     put_string(&con, 0, 0, "Hello, world!");
    //     put_string(&con, 0, 1, "こんにちは世界！");
    //     put_string(&con, 0, 2, "你好，世界！");

    //     // i = i+1して表示
    //     char str[10];
    //     sprintf(str, "%d", i++);
    //     put_string(&con, 0, 3, str);
    //     show_screen(&con);

    //     usleep(1 * 1000 * 1000);
    // }

}