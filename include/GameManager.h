#pragma once
#include "Common.h"
#include "Block.h"
#include "MapManager.h"
#include "InputHandler.h"
#include <chrono>

class Render;

class GameManager
{
private:
    GameState state;
    MapManager mapMgr;
    InputHandler input;
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
    void handleStart();
    void handlePlaying();
    void handleGameOver();

    void spawnNextBlock();
    bool checkCollision();
    void processCommand(Command cmd);
    void updateautoFall();
    void resetGame();
};