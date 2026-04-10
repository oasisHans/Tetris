#include "Common.h"
#include "MapManager.h"

MapManager::MapManager()
{
    clearAll();
}

void MapManager::clearAll()
{
    for (int y = 0; y < ROW; ++y)
    {
        for (int x = 0; x < COL; ++x)
        {
            Map[y][x] = EMPTY;
        }
    }
}

bool MapManager::isPosAvailable(Point p) const
{
    if (p.x < 0 || p.x >= COL || p.y < 0 || p.y >= ROW)
    {
        return false;
    }
    return (Map[p.y][p.x] == EMPTY);
}

// 设置已经落地的方块
void MapManager::setMapData(Point p, BlockType type)
{
    if (p.x < 0 || p.x >= COL || p.y < 0 || p.y >= ROW)
        return;
    Map[p.y][p.x] = type;
}

int MapManager::clearFullLines()
{
    int lines = 0;
    for (int y = ROW - 1; y >= 0; y--)
    {
        if (isLineFull(y))
        {
            deleteLine(y);
            y++;
            lines++;
        }
    }
    return lines;
}

bool MapManager::isLineFull(int row) const
{
    for (int x = 0; x < COL; ++x)
    {
        if (Map[row][x] == EMPTY)
        {
            return false;
        }
    }
    return true;
}

void MapManager::deleteLine(int row)
{
    for (int y = row; y > 0; y--)
    {
        for (int x = 0; x < COL; x++)
        {
            Map[y][x] = Map[y - 1][x];
        }
    }

    for (int x = 0; x < COL; x++)
        Map[0][x] = EMPTY;
}