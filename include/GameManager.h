#pragma once
#include "Common.h"
#include "Block.h"
#include "MapManager.h"
#include "InputHandler.h"
#include "RecordManager.h"
#include <chrono>

class Render;

class GameManager
{
private:
    GameState state;
    MapManager mapMgr;
    InputHandler input;
    RecordManager record;
    Render *render;
    RandomGenerator rgn;

    Block *curBlock;
    Block *nextBlock;

    int score;

    std::chrono::steady_clock::time_point lastFallTime;
    int fallInterval;

public:
    GameManager();
    ~GameManager();

    void run();

private:
    void handleStart(Command &cmd);
    void handleHistory(Command &cmd);
    void handlePlaying(Command &cmd);
    void handleGameOver(Command &cmd);

    void spawnNextBlock();
    bool checkCollision();
    void updateautoFall();
    void resetGame();
};