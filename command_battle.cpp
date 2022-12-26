#include <curses.h>
#include <stdio.h>

// キャラクターの構造体
typedef struct
{
    int hp;
    int maxHp;
    int mp;
    int maxMp;
    char name[16];
    char aa[256];
} CHARACTER;

enum
{
    MONSTER_PLAYER,
    MONSTER_SLIME,
    MONSTER_MAX
};

CHARACTER monsters[MONSTER_MAX] = {
    {
        15,         // 現在のHP
        15,         // 最大HP
        15,         // 現在のMP
        15,         // 最大MP
        "ゆうしゃ", // 名前
    },

    {3,          // 現在のHP
     3,          // 最大MP
     0,          // Mp
     0,          // 最大MP
     "スライム", // 名前
     "／・Д・＼\n"
     "〜〜〜〜〜"},
};

enum
{
    CHARACTER_PLAYER,
    CHARACTER_MONSTER,
    CHARACTER_MAX
};

CHARACTER characters[CHARACTER_MAX];

// 戦闘シーンの画面を描画
void DrawBattleScreen()
{
    // プレイヤー情報の表示
    printf("%s\n", characters[CHARACTER_PLAYER].name);
    printf("HP: %d/%d MP:%d/%d\n",
           characters[CHARACTER_PLAYER].hp,
           characters[CHARACTER_PLAYER].maxHp,
           characters[CHARACTER_PLAYER].mp,
           characters[CHARACTER_PLAYER].maxMp);
    printf("\n");

    // モンスターのアスキーアートを表示
    printf("%s", characters[CHARACTER_MONSTER].aa);
}

void Battle(int _monster)
{
    characters[CHARACTER_MONSTER] = monsters[_monster];

    DrawBattleScreen();

    getchar();
}

void Init()
{
    characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

int main()
{
    Init();
    Battle(MONSTER_SLIME);
}