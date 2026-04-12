#pragma once
#include "Common.h"
#include "GameManager.h"
#include "MapManager.h"
#include "Block.h"

class Render
{
private:
    const int boardX = MARGIN;
    const int boardY = MARGIN;
    const int sidebarX = boardX + BOARD_WIDTH + MARGIN;

public:
    Render();
    void drawScene(GameState state, const MapManager &map, const Block *cur, const Block *next, int score, const std::vector<int> &records);

private:
    void drawBoard(const MapManager &map, const Block *cur);
    void drawSidebar(const Block *next, int score);
    void drawCell(int x, int y, BlockType type, int startX, int startY, int size);

    void drawStartUI();
    void drawGameOverUI(int score);

    void drawHistoryUI(const std::vector<int> &records);

    // 获取方块颜色
    COLORREF getColor(BlockType type);
};