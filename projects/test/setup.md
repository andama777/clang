# vscodeにおけるc言語開発環境のsetup

vscodeで開発環境いくつか試してみる
make, gdbのclasicなやつ
cmake, cpputestのモダンなやつ
まずはモダンで動かしてみましょう

## 1. C/C++拡張機能のインストール

- [C/C++ for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

- [C/C++ Runner](https://marketplace.visualstudio.com/items?itemName=formulahendry.c-cpp-runner)

```
sudo apt update
sudo apt install build-essential gdb -y
sudo apt install g++ build-essential git cmake
gcc --version
```
## 実行してみる

```
gcc main.c -o main
```
## Cmakeの導入

## cpputestの導入

[参考](https://qiita.com/sarakane/items/6e3a775577e8a134bb51)
```
git clone https://github.com/cpputest/cpputest.git
cd cpputest/build
cmake ..
make
sudo make install
export CPPUTEST_HOME=/usr/local
source ~/.bashrc
```

```