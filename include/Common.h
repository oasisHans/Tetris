#pragma once
#include <iostream>
#include <easyx.h>
#include <random>

// 游戏状态枚举
enum class GameState
{
    START,
    HISTORY,
    PLAYING,
    GAMEOVER
};

// 逻辑常量
constexpr int ROW = 20; // 纵向20行（高）
constexpr int COL = 10; // 横向10列（宽）

// 视觉常量
constexpr int CELL_SIZE = 35;
constexpr int BOARD_WIDTH = COL * CELL_SIZE;  // 350px
constexpr int BOARD_HEIGHT = ROW * CELL_SIZE; // 700px

constexpr int SIDEBAR_WIDTH = 200; // 侧边栏宽度
constexpr int MARGIN = 30;         // 边距

// 窗口总大小
constexpr int wndWIDTH = BOARD_WIDTH + SIDEBAR_WIDTH + MARGIN * 3;
constexpr int wndHEIGHT = BOARD_HEIGHT + MARGIN * 2;

// 定义坐标类型
struct Point
{
    int x;
    int y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}

    // 重载"=="判断坐标是否重合
    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }

    // 重载"+"方便矩阵运算
    Point operator+(const Point &other) const
    {
        return {x + other.x, y + other.y};
    }
};

constexpr int FALLTIME = 250;

// 方块类型枚举
enum BlockType
{
    EMPTY = 0,
    SHAPE_I,
    SHAPE_J,
    SHAPE_L,
    SHAPE_O,
    SHAPE_S,
    SHAPE_T,
    SHAPE_Z
};

// 输入指令枚举
enum class Command
{
    NONE,
    LEFT,
    RIGHT,
    DOWN,
    ROTATE,
    DROP,
    ENTER,
    HISTORY,
    EXIT
};

// 随机数工具
class RandomGenerator
{
private:
    std::mt19937 gen;

public:
    RandomGenerator() : gen(std::random_device{}()) {}
    // 随机数生成
    int generate(int min, int max)
    {
        std::uniform_int_distribution<> distrib(min, max);
        return distrib(gen);
    }

    bool chance(int odds)
    {
        int num = generate(0, 99);
        if (num < odds)
        {
            return true;
        }
        return false;
    }
};