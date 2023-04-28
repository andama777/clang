#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "../lib/Window.h"

void main()
{
    long i = 0;
    bool is_running = true;
    float game_time = 0;

    Window window;
    window = create_window();

while(is_running){
        game_time += 0.01;

        clear_screen(&window);

        char str[10];
        sprintf(str, "GameTime : %f", game_time);
        print_string(&window, str);

        show_screen(&window);

        usleep(10 * 1000);
    }
}