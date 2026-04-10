#pragma once
#include "Common.h"

class MapManager
{
private:
    BlockType Map[ROW][COL];

public:
    MapManager();

    bool isPosAvailable(Point p) const;

    void setMapData(Point p, BlockType type);

    int clearFullLines();

    void clearAll();

    BlockType getType(Point p) const { return Map[p.y][p.x]; }

    bool isLineFull(int row) const;
    void deleteLine(int row);
};