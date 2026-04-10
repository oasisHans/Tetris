#include "GameManager.h"
#include "Render.h"
#include <easyx.h>
#include <ctime>

GameManager::GameManager() : state(GameState::START), curBlock(nullptr), nextBlock(nullptr)
{
    render = new Render();
    state = GameState::START;
    curBlock = nullptr;
    nextBlock = nullptr;
    resetGame();
}

GameManager::~GameManager()
{
    if (render)
        delete render;
    if (curBlock)
        delete curBlock;
    if (nextBlock)
        delete nextBlock;
}

void GameManager::resetGame()
{
    mapMgr.clearAll();
    score = 0;

    // 设置下落速度
    fallInterval = FALLTIME;

    // 清空方块指针
    if (curBlock)
    {
        delete curBlock;
        curBlock = nullptr;
    }
    if (nextBlock)
    {
        delete nextBlock;
        nextBlock = nullptr;
    }
}

void GameManager::spawnNextBlock()
{
    auto getRandomType = [&]()
    {
        return static_cast<BlockType>(rgn.generate(1, 7));
    };

    if (nextBlock == nullptr)
    {
        curBlock = new Block(getRandomType());
        nextBlock = new Block(getRandomType());
    }
    else
    {
        curBlock = nextBlock;
        nextBlock = new Block(getRandomType());
    }

    if (checkCollision())
    {
        state = GameState::GAMEOVER;
    }
}

bool GameManager::checkCollision()
{
    if (!curBlock)
        return false;
    for (auto p : curBlock->getAbsPoints())
    {
        if (!mapMgr.isPosAvailable(p))
            return true;
    }
    return false;
}

void GameManager::run()
{
    initgraph(wndWIDTH, wndHEIGHT);
    BeginBatchDraw();

    while (true)
    {
        Command cmd = input.getCommand();
        if (cmd == Command::EXIT)
            break;

        switch (state)
        {
        case GameState::START:
            handleStart();
            break;
        case GameState::PLAYING:
            handlePlaying();
            break;
        case GameState::GAMEOVER:
            handleGameOver();
            break;
        }

        processCommand(cmd);
        render->drawScene(state, mapMgr, curBlock, nextBlock, score);

        FlushBatchDraw();
        Sleep(10);
    }
    EndBatchDraw();
    closegraph();
}

void GameManager::processCommand(Command cmd)
{
    if (cmd == Command::NONE)
        return;

    if (cmd == Command::ENTER)
    {
        if (state == GameState::START)
        {
            resetGame();
            spawnNextBlock();
            state = GameState::PLAYING;
            lastFallTime = std::chrono::steady_clock::now();
        }
        else if (state == GameState::GAMEOVER)
        {
            state = GameState::START;
        }
        return;
    }

    if (state == GameState::PLAYING && curBlock)
    {
        switch (cmd)
        {
        case Command::LEFT:
            curBlock->move({-1, 0});
            if (checkCollision())
                curBlock->move({1, 0});
            break;
        case Command::RIGHT:
            curBlock->move({1, 0});
            if (checkCollision())
                curBlock->move({-1, 0});
            break;
        case Command::ROTATE:
            curBlock->rotate();
            if (checkCollision())
                curBlock->rotateBack();
            break;
        case Command::DOWN:
            curBlock->move({0, 1});
            if (checkCollision())
                curBlock->move({0, -1});
            break;
        case Command::DROP:
            while (!checkCollision())
            {
                curBlock->move({0, 1});
            }
            curBlock->move({0, -1});
            lastFallTime = std::chrono::steady_clock::now() - std::chrono::milliseconds(fallInterval + 1);
            break;
        }
    }
}

void GameManager::updateautoFall()
{
    if (state != GameState::PLAYING || !curBlock)
        return;
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFallTime).count() > fallInterval)
    {
        curBlock->move({0, 1});
        if (checkCollision())
        {
            curBlock->move({0, -1});
            for (auto p : curBlock->getAbsPoints())
                mapMgr.setMapData(p, curBlock->type);
            score += mapMgr.clearFullLines() * 10;
            spawnNextBlock();
        }
        lastFallTime = now;
    }
}

void GameManager::handleStart() {}
void GameManager::handlePlaying() { updateautoFall(); }
void GameManager::handleGameOver() {}