#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeRegular : public IGameModeHandler
{
private:
    uint8_t konohaHeroNum;
    uint8_t akatsukiHeroNum;

public:
    const uint8_t kMaxHeroNum = 4;
    const uint8_t kDefaultHeroNum = 3;

    ModeRegular(uint8_t konohaHeroNum, uint8_t akatsukiHeroNum)
    {
        this->konohaHeroNum = konohaHeroNum <= kMaxHeroNum ? konohaHeroNum : kMaxHeroNum;
        this->akatsukiHeroNum = akatsukiHeroNum <= kMaxHeroNum ? akatsukiHeroNum : kMaxHeroNum;
    }

    void init()
    {
    }

    CCArray *onInitHeros(SelectLayer *selectLayer)
    {
        return initHeros(selectLayer);
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
