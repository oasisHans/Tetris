#pragma once
#include "Common.h"
#include <vector>

class Block
{
public:
    int matrix[4][4];
    Point pos; // 矩阵左上角坐标
    BlockType type;

public:
    Block(BlockType t);

    void move(Point offset);

    void rotate();
    void rotateBack();

    std::vector<Point> getAbsPoints() const;
};
