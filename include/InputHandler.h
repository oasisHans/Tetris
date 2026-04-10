#pragma once
#include "Common.h"
#include <easyx.h>

class InputHandler
{
public:
    Command getCommand()
    {
        ExMessage msg;
        if (peekmessage(&msg, EX_KEY))
        {
            if (msg.message == WM_KEYDOWN)
            {
                switch (msg.vkcode)
                {
                case VK_LEFT:
                    return Command::LEFT;
                case VK_RIGHT:
                    return Command::RIGHT;
                case VK_UP:
                    return Command::ROTATE;
                case VK_DOWN:
                    return Command::DOWN;
                case VK_SPACE:
                    return Command::DROP;
                case VK_RETURN:
                    return Command::ENTER;
                case VK_ESCAPE:
                    return Command::EXIT;
                }
            }
        }
        return Command::NONE;
    }
};
