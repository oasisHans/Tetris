#include <iostream>
#include "Common.h"
#include "MapManager.h"
#include "GameManager.h"

extern "C"
{
    void *__imp___iob_func = nullptr;
}

int main()
{
    GameManager game;
    game.run();

    return 0;
}