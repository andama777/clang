#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Interface.h"
#include "Process.h"

// #define INPUT_PATH "../../data/pics"
#define INPUT_PATH "../../data/pics_face"
#define OUTPUT_PATH "../../output/pics"

frame set_frame(char* path);
FILE* init_FILE(char *path, char *mode);
char** get_file_list(char* path);
void output_frame(char* path, frame f);


int main(void){
    char** file_list = get_file_list(INPUT_PATH);
    int frame_count = 0; // 画像の数
    while(file_list[frame_count]) frame_count++; // 画像の数を数える

    // void* args = console(); // 適用する処理を選択

    // 各画像を処理
    for (int i = 0; i < frame_count; i++){ // frame_count

        frame f = set_frame(file_list[i]);
        printf("--------------------------\n");
        printf("%s\n", file_list[i]);

        // int a,b,c,d,e,f2;
        // int affine_testdata[6] = {1.0, 0.0, 100.0, 0.0, 1.0, 100.0}; // 拡大縮小１

        // a = affine_testdata[0];
        // b = affine_testdata[1];
        // c = affine_testdata[2];
        // d = affine_testdata[3];
        // e = affine_testdata[4];
        // f2 = affine_testdata[5];

        // f = affine(f, a, b, c, d, e, f2); // アフィン変換 a,b,c,d,e,f


        //f = process(f, args);
        //f = labeling_frame(f);
        // f = discriminant_analysis(f);
        f = face_area_extract(f);

        output_frame(file_list[i], f);
    }

    return 0;
};

void output_frame(char* file, frame f){
    char outfile[100];
    sprintf(outfile, "%s/%s", OUTPUT_PATH, file);
    FILE *outfp = init_FILE(outfile, "w");
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

FILE* init_FILE(char *path, char *mode){
    FILE *fp;
    fp = fopen(path, mode);
    if (fp == NULL) printf("Error opening file %s\n", path);
    return fp;
}

frame set_frame(char* path){
    char infile[100];
    sprintf(infile, "%s/%s", INPUT_PATH, path);
    FILE *infp = init_FILE(infile, "r");
    char magic[3];
    int width, height, max;
    fscanf(infp, "%s%d%d%d", magic, &width, &height, &max);

    frame f = init_frame(magic, width, height, max);
    for (int i = 0; i < f.height; i++){
        for (int j = 0; j < f.width; j++){
            fscanf(infp, "%d", &f.image[i][j]);
        }
    }
    fclose(infp);

    return f;
}