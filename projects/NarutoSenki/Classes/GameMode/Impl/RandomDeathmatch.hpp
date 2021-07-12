#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeRandomDeathmatch : public IGameModeHandler
{
public:
    void init()
    {
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
