/mnt/c/Users/kanda.mao.18/Documents/GitHub/clang/projects/test/src/main.c: In function ‘main’:
/mnt/c/Users/kanda.mao.18/Documents/GitHub/clang/projects/test/src/main.c:28:44: error: invalid type argument of ‘->’ (have 
‘Clock’)
   28 |         sprintf(str, "GameTime : %f", clock->get_game_time(&clock));
      |                                            ^~
/mnt/c/Users/kanda.mao.18/Documents/GitHub/clang/projects/test/src/main.c:30:9: warning: implicit declaration of function ‘set_screen’; did you mean ‘show_screen’? [-Wimplicit-function-declaration]
   30 |         set_screen(&window, str);
      |         ^~~~~~~~~~
      |         show_screen
make[2]: *** [CMakeFiles/game.dir/build.make:76: CMakeFiles/game.dir/src/main.c.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:169: CMakeFiles/game.dir/all] Error 2
make: *** [Makefile:91: all] Error 2