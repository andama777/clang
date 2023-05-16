#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT_PATH "../../data/pics"
#define OUTPUT_PATH "../../output/pics"

typedef struct {
    char magic[3];
    int width, height, max, **image;
} frame;

frame init_frame(char magic[3], int width, int height, int max){
    frame f;
    strcpy(f.magic, magic);
    f.width = width;
    f.height = height;
    f.max = max;
    f.image = (int **)malloc(sizeof(int *) * f.height);
    for (int i = 0; i < f.height; i++) f.image[i] = (int *)malloc(sizeof(int) * f.width);
    return f;
}

FILE* init_FILE(char *path, char *mode){
    FILE *fp = fopen(path, mode);
    if (fp == NULL) printf("Error opening file %s\n", path);
    return fp;
}

char** get_file_list(char* path){
    char* command = (char *)malloc(sizeof(char) * 100);
    sprintf(command, "ls %s > tmp.txt", path);
    system(command); // ls ../../data/pics > tmp.txt を実行

    FILE *fp = init_FILE("tmp.txt", "r");
    // 1つのファイル名(image1.pgm)の長さは100とする
    char line[100];
    int item_num = 0;
    while (fgets(line, 100, fp) != NULL) item_num++; // ファイルの行数を数える
    rewind(fp); // ファイルポインタを先頭に戻す

    // アイテムの数を使ってfile_listを初期化&ファイル名を代入
    char** file_list = (char **)malloc(sizeof(char *) * item_num);
    for (int j = 0; j < item_num; j++){
        file_list[j] = (char *)malloc(sizeof(char) * 100);
        fgets(line, sizeof(line), fp); // 1行読み込む(改行コードも含まれる
        line[strlen(line) - 1] = '\0'; // 改行コードを削除
        strcpy(file_list[j], line);
    }
    fclose(fp);
    return file_list;
}

void output_frame(char* path, frame f){
    FILE *outfp = init_FILE(path, "w");
    fprintf(outfp, "%s\n%d %d\n%d\n", f.magic, f.width, f.height, f.max);
    for (int i = 0; i < f.height; i++){
        int* row = f.image[i];
        for (int j = 0; j < f.width; j++){
            fprintf(outfp, "%d ", row[j]);
        }
        fprintf(outfp, "\n");
    }
    fclose(outfp);
}

void main(){
    char** file_list = get_file_list(INPUT_PATH);
    int frame_count = 0;
    while(file_list[frame_count]) frame_count++;

    frame *frames = (frame *)malloc(sizeof(frame) * frame_count);
    FILE *tmp;
    char magic[3];
    int width, height, max;
    for (int i = 0; i < frame_count; i++){
        char* file_path = (char *)malloc(strlen(INPUT_PATH) + strlen(file_list[i]) + 2);
        sprintf(file_path, "%s/%s", INPUT_PATH, file_list[i]);

        tmp = init_FILE(file_path, "r");
        fscanf(tmp, "%s%d%d%d", magic, &width, &height, &max);
        frames[i] = init_frame(magic, width, height, max);

        for (int j = 0; j < frames[i].height; j++){
            for (int k = 0; k < frames[i].width; k++) fscanf(tmp, "%d", &frames[i].image[j][k]);
        }

        char* output_path = (char *)malloc(strlen(OUTPUT_PATH) + strlen(file_list[i]) + 2);
        sprintf(output_path, "%s/%s", OUTPUT_PATH, file_list[i]);
        output_frame(output_path, frames[i]);
    }
    return;
}