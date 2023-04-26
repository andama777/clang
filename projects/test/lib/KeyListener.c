// use sleep(1)
#include "KeyListener.h"

bool key_search(KeyList *keyList, char c){
    for(int i = 0; i < KEYNUM; i++){
        if(keyList->key[i].key == c){
            return true;
        }
    }
    return false;
}

// キー入力を取得する
char listen_key(KeyList *keyList)
{
    struct termios oldt, newt;
    //標準入力の設定を保存する
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;

    // カノニカルモード(Enterキーを待つモード)を無効にする
    newt.c_lflag &= ~(ICANON | ECHO);

    // 設定を反映する
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    char c;
    if (read(STDIN_FILENO, &c, 1) > 0){
        if(key_search(keyList, c)){
            printf("key : %c\n", c);
            return c;
        } else {
            printf("key not found\n");
            return ' ';
        }
    }   
}

void main(){

    KeyList keyList = {
        'w', 'a', 's', 'd', 'e'
    };

    char temp;
    while(1){
        temp = listen_key(&keyList);
        sleep(0.5);
    }
}
