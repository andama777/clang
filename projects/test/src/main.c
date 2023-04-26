// libフォルダのconsole.hを使う

#include "../lib/console.h"

void main()
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

}