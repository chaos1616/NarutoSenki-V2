#include "UI/GameModeLayer.h"

GameModeLayer::GameModeLayer()
{
}

GameModeLayer::~GameModeLayer()
{
}

bool GameModeLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());

        bRet = true;

    } while (0);

    return bRet;
}
