#pragma once
#include "GameMode/IGameModeHandler.hpp"

class Mode1v1 : public IGameModeHandler
{
public:
    void init()
    {
        CCLOG("Enter 1 VS 1 mode.");
    }

    CCArray *onInitHeros()
    {
        return initHeros(1, 1);
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
