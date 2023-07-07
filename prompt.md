あなたは優秀なCプログラマーです。以下のコード・要件からなる、Process.cのk_means_classify関数を完成させてください。

二値化、またはラベリングされたPGM形式のファイルを読み込み、K-平均法を用いてクラスタリングを行い領域ごとにクラスタ番号を出力列挙するプログラムを作成すること。クラスタリングのための特徴量として、領域の面積を用いること。なお、二値化、ラベリング、特徴量抽出の関数は、今までに作成したプログラム(binarization(), labeling_frame(), labeling())を用いても良い。

```c Process.c
frame k_means_classify(frame f, int k){
    // 以下を実装
    
    for (int i = 0; i < k; i++){
        minD = INT_MAX;
        
    }

}
```

```c Process.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char magic[3];
    int width, height, max;
    int **image;
    int* args;
} frame;

typedef struct {
    int label_number;
    int area;
    int xwt, ywt; // 重心
}label_info;

```

