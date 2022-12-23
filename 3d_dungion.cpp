#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <vector>
#include <time.h>

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
        // 隣の部屋の掘る壁の方位を宣言
        int nextDirection = (_direction + 2) % DIRECTION_MAX;
        // 隣の部屋の壁を掘る
        maze[nextPosition.y][nextPosition.x].walls[nextDirection] = false;
    }
}

void DrawMap()
{
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {

        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            printf("＋%s＋", maze[y][x].walls[DIRECTION_NORTH] ? "-" : " ");
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
            printf("＋%s＋", maze[y][x].walls[DIRECTION_SOUTH] ? "-" : " ");
        }
        printf("\n");
    }
}

bool CanDigWall(VEC2 _position, int _direction)
{
    // 隣の座標を宣言する
    VEC2 nextPosition = VecAdd(_position, directions[_direction]);

    // 隣の座標が迷路の範囲内でないかどうかを判定
    if (!IsInsideMaze(nextPosition))
    {
        return false;
    }

    for (int i = 0; i < DIRECTION_MAX; i++)
    {
        if (!maze[nextPosition.y][nextPosition.x].walls[i])
        {
            return false;
        }
    }

    return true;
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

    // 現在の座標を宣言
    VEC2 currentPostion = {0, 0};

    // 壁を掘るべきマスのリスト
    std::vector<VEC2> toDigWallPositions;

    // 壁がなくなるまで掘る
    while (1)
    {
        // 掘れる壁の方位のリスト
        std::vector<int> canDigDirections;

        for (int i = 0; i < DIRECTION_MAX; i++)
        {
            if (CanDigWall(currentPostion, i))
            {
                canDigDirections.push_back(i);
            }
        }
        // 掘れる壁があるかどうかを判定する
        if (canDigDirections.size() > 0)
        {
            int digDirection = canDigDirections[rand() % canDigDirections.size()];

            // 対象の壁を掘る
            DigWall(currentPostion, digDirection);

            // 堀田壁の向こう側に移動する
            currentPostion = VecAdd(currentPostion, directions[digDirection]);

            // 壁を掘るべきますの座標リストに現在の座標を加える
            toDigWallPositions.push_back(currentPostion);
        }
        else
        {
            // 壁を掘るべきますのリストから現在のマスを削除
            toDigWallPositions.erase(toDigWallPositions.begin());

            // 壁を掘るべきますのリストが空かどうか判定する
            if (toDigWallPositions.size() <= 0)
            {
                break;
            }

            // 壁を掘るべきマスのリストから、先頭のマスを取得し移動する
            currentPostion = toDigWallPositions.front();
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
    // 乱数をシャッフルする
    // srand((unsigned int)time(NULL));

    Init();

    while (1)
    {
        system("clear");

        DrawMap();

        switch (getchar())
        {
        }
    }
}