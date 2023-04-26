// フィボナッチ数列の計算

#include "stdio.h"

int fib(int n)
{
    if (n == 0 || n == 1) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}

int main()
{
    // 手入力で数字を受け付ける
    int n;
    printf("n = ");
    scanf("%d", &n);
    printf("fib(%d) = %d\n", n, fib(n));
}