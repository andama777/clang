#include "Interface.h"

function_info func_list[func_count] = {
{"contrast", 0},
{"moving_average", 0},
{"median_filter", 1},
{"scale", 2},
{"rotate", 3},
{"affine", 6},
{"binarization", 1},
{"discriminant_analysis", 0}
};

// console関数を回すことで、画像に対してどの操作を適用するか選択させる
void* console(){
    // 関数を選択
    int func_id = function_select();
    void* args = malloc(sizeof(int) * (func_list[func_id].args_num + 2));
    ((int *)args)[FUNC_ID] = func_id;
    ((int *)args)[ARGS_NUM] = func_list[func_id].args_num;

    char affine_args[6]= {'a', 'b', 'c', 'd', 'e', 'f'};
    char *func_name = func_list[func_id].name;
    printf("func_name = %s\n", func_list[func_id].name);

    // 引数を入力させる
    if (strcmp(func_name, "constrast") == 0){
        return args;
    } else if(strcmp(func_name, "moving_average") == 0){
        return args;
    } else if(strcmp(func_name, "median_filter") == 0){
        printf("フィルタのサイズを入力してください\n");
        scanf("%d", &((int *)args)[2]);
        printf("filter_size = %d\n", ((int *)args)[2]);
    } else if(strcmp(func_name, "scale") == 0){
        printf("x方向の倍率を入力してください (float) \n");
        scanf("%f", &((float *)args)[2]);
        printf("y方向の倍率を入力してください (float) \n");
        scanf("%f", &((float *)args)[3]);
        printf("x_mult = %f, y_mult = %f)\n", ((float *)args)[2], ((float *)args)[3]);
    } else if(strcmp(func_name, "rotate") == 0){
        printf("回転軸のx座標を入力してください\n");
        scanf("%d", &((int *)args)[2]);
        printf("回転軸のy座標を入力してください\n");
        scanf("%d", &((int *)args)[3]);
        printf("回転角を入力してください\n");
        scanf("%d", &((int *)args)[4]);
        printf("axis = (%d, %d), angle = %d\n", ((int *)args)[2], ((int *)args)[3], ((int *)args)[4]);
    } else if(strcmp(func_name, "binarization") == 0){
        printf("閾値を入力してください\n");
        scanf("%d", &((int *)args)[2]);
        printf("threshold = %d\n", ((int *)args)[2]);
    } else if(strcmp(func_name, "discriminant_analysis") == 0){
        return args;
    } else if(strcmp(func_name, "affine") == 0){
        for (int i = 0; i < 6; i++){
            printf("%cを入力してください\n", affine_args[i]);
            scanf("%d", &((int *)args)[i + 2]);
        }
        int a = ((int *)args)[2];
        int b = ((int *)args)[3];
        int c = ((int *)args)[4];
        int d = ((int *)args)[5];
        int e = ((int *)args)[6];
        int f = ((int *)args)[7];

        if (b == 0 && c == 0 && d == 0 && f == 0) {
            printf("(0, 0) 中心の拡大縮小\n");
        } else if (a == e) {
            if (b == -d && a * a + b * b == 1 && c == f && c == 0) {
                printf("回転\n");
            } else if (a == 1) {
                if (b == d && b == 0) {
                    printf("平行移動");
                } else if (b != 0 || d != 1) {
                    printf("(0, 0)中心のせん断");
                }
            }
        }
    }

    return args;
}

/// @brief 
/// @return select: 選択した関数のid
int function_select(){
    // 選択肢を表示
    int select;
    bool isValid = false;
    while(!isValid){
        // 選択肢を表示
        printf("どの処理を行うか選んでください\n");
        for (int i = 1; i < func_count + 1; i++){
            printf("%d: %s\n", i, func_list[i - 1].name);
        }

        // 選択させる
        
        scanf("%d", &select);

        if(select > func_count || select < 1){ // 選択肢にない数字が入力されたら
            printf("1~%dの数字を入力してください\n", func_count);
            isValid = false;
        } else {
            isValid = true;
        }
    }

    select -= 1;

    return select;
}