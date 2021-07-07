#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeRegular : public IGameModeHandler
{
private:
    uint8_t heroNum;

public:
    const uint8_t kMaxHeroNum = 4;
    const uint8_t kDefaultHeroNum = 3;

    ModeRegular(uint8_t heroNum)
    {
        if (heroNum > 0 && heroNum <= kMaxHeroNum)
            this->heroNum = heroNum;
        else
            this->heroNum = kDefaultHeroNum;
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
