## 「小一時間でゲームを作る」　の写経

### コンパイル

```C++
g++ -o out 3d_dungion.cpp -std=c++11
```

-> program というコンパイルされたファイルが出来上がる

### 実行

```C++
./out
```

### プレイ動画

https://user-images.githubusercontent.com/45703844/209433262-b2b7373f-8376-46c0-9844-19c8ad4dd258.mov


### 補足

#include <conio.h> は Mac だと使えない。
#include <curses.h> に置き換える

下記を実行して ncurses をインストールする必要あり

```sh
brew install ncurses
```

https://formulae.brew.sh/formula/ncurses

### 書籍

- [小一時間でゲームを作る](https://www.amazon.co.jp/dp/4297127458)
- [サンプルコード](https://gihyo.jp/book/2022/978-4-297-12745-9/support)
