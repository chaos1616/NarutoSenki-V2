#pragma once
#include "GameMode/IGameModeHandler.hpp"

class Mode4v4 : public IGameModeHandler
{
public:
    void init()
    {
        CCLOG("Enter 4 VS 4 mode.");
    }

    CCArray *onInitHeros()
    {
        return initHeros(4, 4);
    }

    void onGameStart()
    {
    }

    void onGameOver()
    {
    }

    void onCharacterInit(CharacterBase *c)
    {
    }

    void onCharacterDead(CharacterBase *c)
    {
    }

    void onCharacterReborn(CharacterBase *c)
    {
    }
};
