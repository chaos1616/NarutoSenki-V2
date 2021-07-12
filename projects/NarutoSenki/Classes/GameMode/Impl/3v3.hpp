#pragma once
#include "GameMode/IGameModeHandler.hpp"

class Mode3v3 : public IGameModeHandler
{
public:
    void init()
    {
        CCLOG("Enter 3 VS 3 mode.");
    }

    CCArray *onInitHeros()
    {
        return initHeros(3, 3);
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
