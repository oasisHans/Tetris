#include "Block.h"

const int SHAPE_DATA[8][4][4] = {
    {{0, 0, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // EMPTY

    {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0}}, // I

    {{1, 1, 1, 0},
     {0, 0, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // J

    {{1, 1, 1, 0},
     {1, 0, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // L

    {{0, 1, 1, 0},
     {0, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // O

    {{0, 1, 1, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // S

    {{1, 1, 1, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // T

    {{1, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}} // Z
};

Block::Block(BlockType t)
{
    this->type = t;
    this->pos = {3, 0}; // 初始出生在顶部中央

    // 先清零
    memset(this->matrix, 0, sizeof(this->matrix));
    // 再从形状数据表拷贝
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            this->matrix[i][j] = SHAPE_DATA[t][i][j];
}

// 移动算法
void Block::move(Point offset)
{
    this->pos.x += offset.x;
    this->pos.y += offset.y;
}

void Block::rotate()
{
    int temp[4][4] = {0};
    // 矩阵顺时针旋转 90 度算法
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            temp[j][3 - i] = this->matrix[i][j];
        }
    }
    // 拷贝回原矩阵
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->matrix[i][j] = temp[i][j];
        }
    }
}

void Block::rotateBack()
{
    // 逆时针转 90 度等于顺时针转 270 度
    rotate();
    rotate();
    rotate();
}

std::vector<Point> Block::getAbsPoints() const
{
    std::vector<Point> pts;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (matrix[i][j] != 0)
            {
                pts.push_back({pos.x + j, pos.y + i});
            }
        }
    }
    return pts;
}