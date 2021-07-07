#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeClone : public IGameModeHandler
{
private:
    bool isOneForAllGroups;

public:
    ModeClone(bool isOneForAllGroups)
    {
        this->isOneForAllGroups = isOneForAllGroups;
    }

    void init()
    {
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
