#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

// 迷路のサイズ
#define MAZE_WIDTH (8)
#define MAZE_HEIGHT (8)

// 方位の種類
enum
{
    DIRECTION_NORTH,
    DIRECTION_WEST,
    DIRECTION_SOUTH,
    DIRECTION_EAST,
    DIRECTION_MAX
};

// 迷路のマス
typedef struct
{
    bool walls[DIRECTION_MAX];
} TILE;

TILE maze[MAZE_HEIGHT][MAZE_WIDTH];

// 迷路の座標
typedef struct
{
    int x, y;
} VEC2;

bool IsInsideMaze(VEC2 _position)
{
    return (_position.x >= 0) && (_position.x < MAZE_WIDTH) && (_position.y >= 0) && (_position.y < MAZE_HEIGHT);
}

// 各方位のベクトルを宣言
VEC2 directions[] = {
    {0, -1}, // 北
    {-1, 0}, // 西
    {0, 1},  // 南
    {1, 0}   // 東
};

// ベクトルを加算する関数
VEC2 VecAdd(VEC2 _v0, VEC2 _v1)
{
    return {
        _v0.x + _v1.x,
        _v0.y + _v1.y};
}

// 迷路の壁を掘る
void DigWall(VEC2 _position, int _direction)
{
    if (!IsInsideMaze(_position))
    {
        return;
    }

    // 対象の壁を掘る
    maze[_position.y][_position.x].walls[_direction] = false;

    // 隣のマスの座標
    VEC2 nextPosition = VecAdd(_position, directions[_direction]);

    // 隣のマスが迷路の範囲内かどうか判定
    if (IsInsideMaze(nextPosition))
    {
    }
}

void DrawMap()
{
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {

        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            printf("＋%s＋", maze[y][x].walls[DIRECTION_NORTH] ? "-" : "　");
        }
        printf("\n");

        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // 床のアスキーアート
            char floorAA[] = " ";
            printf(
                "%s%s%s", maze[y][x].walls[DIRECTION_WEST] ? "｜" : "　",
                floorAA,
                maze[y][x].walls[DIRECTION_EAST] ? "｜" : "　");
        }
        printf("\n");

        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            printf("＋%s＋", maze[y][x].walls[DIRECTION_SOUTH] ? "-" : "　");
        }
        printf("\n");
    }
}

void GenerateMap()
{
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            for (int i = 0; i < DIRECTION_MAX; i++)
            {
                // 対象の方位を壁にする
                maze[y][x].walls[i] = true;
            }
        }
    }
}

// ゲームの初期化
void Init()
{
    GenerateMap();
}

int main()
{
    Init();

    while (1)
    {
        system("clear");

        DrawMap();

        // initscr();
        switch (getchar())
        {
        }
        // endwin();
    }
}