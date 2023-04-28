#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "../lib/Clock.h"
#include "../lib/Window.h"

void main()
{
    bool is_running = true;

    Clock clock = create_clock();
    Window window = create_window();

    while(is_running){
        clear_screen(&window);

        char str[1000];
        sprintf(str, "GameTime : %f", get_game_time(&clock));

        set_screen(&window, str);

        show_screen(&window);

        usleep(10 * 1000);
    }
}