#include "Render.h"
#include <stdio.h>
#include <string>

Render::Render()
{
}

void Render::drawScene(GameState state, const MapManager &map, const Block *cur, const Block *next, int score, const std::vector<int> &records)
{
    setbkcolor(WHITE);
    cleardevice();

    switch (state)
    {
    case GameState::START:
        drawStartUI();
        break;
    case GameState::HISTORY:
        drawHistoryUI(records);
        break;
    case GameState::PLAYING:
        drawBoard(map, cur);
        drawSidebar(next, score);
        break;
    case GameState::GAMEOVER:
        drawGameOverUI(score);
        break;
    }
}

void Render::drawBoard(const MapManager &map, const Block *cur)
{
    // 绘制游戏主界面框
    setlinecolor(RGB(200, 200, 200));
    setlinestyle(PS_SOLID, 2);
    rectangle(boardX - 1, boardY - 1, boardX + BOARD_WIDTH, boardY + BOARD_HEIGHT);
    setlinestyle(PS_SOLID, 1);

    // 绘制底部方块
    for (int y = 0; y < ROW; y++)
    {
        for (int x = 0; x < COL; x++)
        {

            BlockType type = map.getType({x, y});
            drawCell(x, y, type, boardX, boardY, CELL_SIZE);
        }
    }

    // 绘制curBlock
    if (cur)
    {

        std::vector<Point> pts = cur->getAbsPoints();
        for (auto p : pts)
        {
            drawCell(p.x, p.y, cur->type, boardX, boardY, CELL_SIZE);
        }
    }
}

void Render::drawSidebar(const Block *next, int score)
{
    settextcolor(BLACK);
    settextstyle(25, 0, "Arial Bold");
    outtextxy(sidebarX, boardY, "NEXT");

    setlinecolor(RGB(230, 230, 230));
    rectangle(sidebarX, boardY + 40, sidebarX + 4 * 25, boardY + 40 + 4 * 25);

    if (next)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (next->matrix[i][j])
                {
                    drawCell(j, i, next->type, sidebarX, boardY + 40, 25);
                }
            }
        }
    }

    settextcolor(RGB(60, 60, 60));
    settextstyle(25, 0, "Arial Bold");
    outtextxy(sidebarX, boardY + 200, "SCORE");

    settextcolor(BLACK);
    settextstyle(35, 0, "Consolas");
    char scoreStr[20];
    sprintf_s(scoreStr, "%06d", score);
    outtextxy(sidebarX, boardY + 240, scoreStr);
}

void Render::drawCell(int x, int y, BlockType type, int startX, int startY, int size)
{
    if (type == EMPTY)
        return;
    int left = startX + x * size;
    int top = startY + y * size;

    setfillcolor(getColor(type));

    setlinecolor(WHITE);
    fillrectangle(left, top, left + size, top + size);
}

void Render::drawStartUI()
{
    // 1. 背景：填充整个窗口大小 (wndWIDTH x wndHEIGHT)
    setfillcolor(WHITE); // 设置为纯白
    solidrectangle(0, 0, wndWIDTH, wndHEIGHT);

    // 2. 顶部彩色装饰条：横跨整个窗口宽度
    COLORREF colors[] = {
        RGB(255, 50, 50), RGB(255, 140, 0), RGB(255, 200, 0),
        RGB(50, 210, 50), RGB(0, 200, 255), RGB(0, 80, 255), RGB(160, 50, 240)};
    int decorationHeight = 20;       // 稍微加厚一点更有质感
    int segmentWidth = wndWIDTH / 7; // 按照窗口总宽平分
    for (int i = 0; i < 7; i++)
    {
        setfillcolor(colors[i]);
        setlinecolor(colors[i]);
        solidrectangle(i * segmentWidth, 0, (i + 1) * segmentWidth, decorationHeight);
    }

    // 3. 字体设置：确保透明背景，无白框
    setbkmode(TRANSPARENT);

    // --- TETRIS 大标题 ---
    settextcolor(BLACK);
    settextstyle(100, 0, "Impact"); // 既然全屏了，字号可以加大到 100
    int titleW = textwidth("TETRIS");
    int titleX = (wndWIDTH - titleW) / 2; // 全窗口居中
    outtextxy(titleX, 150, "TETRIS");

    // --- 装饰线 ---
    setlinecolor(RGB(230, 230, 230));
    line(100, 280, wndWIDTH - 100, 280);

    // --- 开始提示 ---
    settextstyle(30, 0, "Consolas");
    settextcolor(RGB(50, 50, 50));
    const char *hint1 = "PRESS ENTER";
    outtextxy((wndWIDTH - textwidth(hint1)) / 2, 400, hint1);

    settextstyle(20, 0, "Consolas");
    settextcolor(RGB(150, 150, 150));
    const char *hint2 = "TO START GAME";
    outtextxy((wndWIDTH - textwidth(hint2)) / 2, 440, hint2);

    // --- 底部操作说明 (CONTROLS) ---
    // 移到窗口靠下的中央位置
    settextstyle(20, 0, "Arial Bold");
    settextcolor(BLACK);
    int controlBaseX = (wndWIDTH - 250) / 2; // 大概居中
    int controlBaseY = 580;
    outtextxy(controlBaseX, controlBaseY, "CONTROLS:");

    settextstyle(18, 0, "Arial");
    settextcolor(RGB(120, 120, 120));
    outtextxy(controlBaseX, controlBaseY + 30, "Arrows : Move & Rotate");
    outtextxy(controlBaseX, controlBaseY + 60, "Down   : Soft Drop");
    outtextxy(controlBaseX, controlBaseY + 90, "Space  : Hard Drop");
}

void Render::drawGameOverUI(int score)
{
    // 1. 背景：填充整个窗口，遮盖之前的游戏画面
    setfillcolor(WHITE);
    solidrectangle(0, 0, wndWIDTH, wndHEIGHT);

    // 2. 顶部彩色装饰条 (保持与 Start 界面一致)
    COLORREF colors[] = {
        RGB(255, 50, 50), RGB(255, 140, 0), RGB(255, 200, 0),
        RGB(50, 210, 50), RGB(0, 200, 255), RGB(0, 80, 255), RGB(160, 50, 240)};
    int decorationHeight = 20;
    int segmentWidth = wndWIDTH / 7;
    for (int i = 0; i < 7; i++)
    {
        setfillcolor(colors[i]);
        setlinecolor(colors[i]);
        solidrectangle(i * segmentWidth, 0, (i + 1) * segmentWidth, decorationHeight);
    }

    // 3. 字体设置
    setbkmode(TRANSPARENT);

    // --- GAME OVER 大标题 ---
    settextcolor(RED); // 游戏结束使用红色
    settextstyle(100, 0, "Impact");
    int goW = textwidth("GAME OVER");
    outtextxy((wndWIDTH - goW) / 2, 150, "GAME OVER");

    // --- 装饰线 ---
    setlinecolor(RGB(230, 230, 230));
    line(150, 280, wndWIDTH - 150, 280);

    // --- 分数展示区域 ---
    settextcolor(RGB(100, 100, 100));
    settextstyle(30, 0, "Arial Bold");
    const char *scoreLabel = "FINAL SCORE";
    outtextxy((wndWIDTH - textwidth(scoreLabel)) / 2, 350, scoreLabel);

    // 绘制具体分数数字 (加大字号)
    settextcolor(BLACK);
    settextstyle(70, 0, "Consolas");
    char scoreStr[20];
    sprintf_s(scoreStr, "%06d", score);
    int scW = textwidth(scoreStr);
    outtextxy((wndWIDTH - scW) / 2, 400, scoreStr);

    // --- 操作提示 ---
    setlinecolor(RGB(230, 230, 230));
    line(200, 520, wndWIDTH - 200, 520);

    settextcolor(RGB(50, 50, 50));
    settextstyle(25, 0, "Consolas");
    const char *restart1 = "PRESS ENTER";
    outtextxy((wndWIDTH - textwidth(restart1)) / 2, 560, restart1);

    settextstyle(20, 0, "Consolas");
    settextcolor(RGB(150, 150, 150));
    const char *restart2 = "TO RESTART";
    outtextxy((wndWIDTH - textwidth(restart2)) / 2, 600, restart2);
}

void Render::drawHistoryUI(const std::vector<int> &records)
{
    // 1. 装饰背景
    setfillcolor(WHITE);
    solidrectangle(0, 0, wndWIDTH, wndHEIGHT);

    // 顶部彩色条
    COLORREF colors[] = {RGB(255, 50, 50), RGB(255, 140, 0), RGB(255, 200, 0), RGB(50, 210, 50), RGB(0, 200, 255), RGB(0, 80, 255), RGB(160, 50, 240)};
    int segmentWidth = wndWIDTH / 7;
    for (int i = 0; i < 7; i++)
    {
        setfillcolor(colors[i]);
        solidrectangle(i * segmentWidth, 0, (i + 1) * segmentWidth, 20);
    }

    setbkmode(TRANSPARENT);

    // 2. 标题
    settextcolor(BLACK);
    settextstyle(60, 0, "Impact");
    outtextxy((wndWIDTH - textwidth("TOP RECORDS")) / 2, 80, "TOP RECORDS");

    // 3. 绘制前 10 名分数
    settextstyle(25, 0, "Consolas");
    settextcolor(RGB(50, 50, 50));

    int startY = 180;
    int limit = records.size() > 10 ? 10 : records.size();

    if (limit == 0)
    {
        outtextxy((wndWIDTH - textwidth("NO RECORDS YET")) / 2, 300, "NO RECORDS YET");
    }
    else
    {
        for (int i = 0; i < limit; i++)
        {
            char buf[50];
            sprintf_s(buf, "RANK %02d ...... %06d", i + 1, records[i]);
            outtextxy((wndWIDTH - textwidth(buf)) / 2, startY + i * 40, buf);
        }
    }

    // 4. 底部操作提示
    setlinecolor(RGB(230, 230, 230));
    line(100, 620, wndWIDTH - 100, 620);

    settextstyle(20, 0, "Consolas");
    settextcolor(RGB(150, 150, 150));

    const char *hint1 = "[SPACE] BACK TO MENU";
    const char *hint2 = "[ENTER] START GAME";
    outtextxy((wndWIDTH - textwidth(hint1)) / 2, 640, hint1);
    outtextxy((wndWIDTH - textwidth(hint2)) / 2, 675, hint2);
}

COLORREF Render::getColor(BlockType type)
{
    switch (type)
    {
    case SHAPE_I:
        return RGB(0, 200, 255);
    case SHAPE_J:
        return RGB(0, 80, 255);
    case SHAPE_L:
        return RGB(255, 140, 0);
    case SHAPE_O:
        return RGB(255, 200, 0);
    case SHAPE_S:
        return RGB(50, 210, 50);
    case SHAPE_T:
        return RGB(160, 50, 240);
    case SHAPE_Z:
        return RGB(255, 50, 50);
    default:
        return RGB(220, 220, 220);
    }
}