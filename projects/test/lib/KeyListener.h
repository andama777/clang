// キーボード入力を受け付けるクラス

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <termios.h>

#define KEYNUM 5


typedef struct{
    char key;
} Key;

typedef struct{
    Key key[KEYNUM];
} KeyList;

typedef struct {
    bool allowed;
    bool isPressed;
    KeyList keyList;
    int state;
} Keyboard;


bool key_search(KeyList *keyList, char c);
char listen_key(Keyboard *keyboard);



