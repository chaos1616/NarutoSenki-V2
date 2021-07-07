#pragma once
#include "cocos2d.h"
#include "CharacterBase.h"
#include "GameLayer.h"
#include "LoadLayer.h"

using namespace cocos2d;

class IGameModeHandler;

enum GameMode
{
    // 1 VS 1
    OneVsOne,
    // 3 VS 3
    Classic,
    // 4 VS 4
    FourVsFour,
    // 4 VS 4 (Disabled gears)
    HardCore_4Vs4,
    // 3 VS 1
    Boss,
    // 3 VS 3
    Clone,
    // 3 VS 3
    Deathmatch,
    // 3 VS 3
    RandomDeathmatch,

    _Internal_Max_Length
}; // namespace GameMode

struct GameModeData
{
public:
    const char *title;
    const char *description;

    bool hasSelected;
    IGameModeHandler *handler;

    // static const GameModeData &from(const char *path);
};

class IGameModeHandler
{
    friend class GameLayer;
    friend class LoadLayer;
    friend class GameModeLayer;

private:
    static IGameModeHandler *instance;

    LoadLayer *_loadLayer;
    // player
    const char *playerGroup;
    // map
    int mapId;
    // tower
    bool enableKonohaTowers;
    bool enableAkatsukiTowers;
    // flog
    bool skipInitFlogs;
    bool enableKonohaFlogs;
    bool enableAkatsukiFlogs;
    float flogDuration;
    bool isLimitFlog;
    int maxFlogWaves;
    // hero
    bool enableHeroReborn;

public:
    const int kDefaultMap = 1;

    virtual void init() = 0;
    virtual void loadGame() {}

    virtual void onGameStart() = 0;
    virtual void onGameOver() = 0;

    // callbacks
    virtual void onCharacterInit(CharacterBase *c) = 0;
    virtual void onCharacterDead(CharacterBase *c) = 0;
    virtual void onCharacterReborn(CharacterBase *c) = 0;

protected:
    // Warpper of game layer
    void setMap(int id)
    {
        this->mapId = id;
    }

    void setTower(bool enableKonohaTowers, bool enableAkatsukiTowers)
    {
        this->enableKonohaTowers = enableKonohaTowers;
        this->enableAkatsukiTowers = enableAkatsukiTowers;
    }

    void setFlog(bool enableKonohaFlogs, bool enableAkatsukiFlogs, float duration = 15.0f, int maxWaves = -1)
    {
        this->enableKonohaFlogs = enableKonohaFlogs;
        this->enableAkatsukiFlogs = enableAkatsukiFlogs;
        this->flogDuration = (duration < 5 || duration > 60) ? 15.0f : duration;
        this->isLimitFlog = maxWaves >= 0;
        this->maxFlogWaves = maxWaves;
    }

    void setHero(bool enableReborn)
    {
        this->enableHeroReborn = enableReborn;
    }

    void setPlayerGroup(const char *group = nullptr)
    {
        if (strcmp(group, Konoha) == 0)
            this->playerGroup = Konoha;
        else if (strcmp(group, Akatsuki) == 0)
            this->playerGroup = Akatsuki;
        else
            this->playerGroup = random(100) > 50 ? Akatsuki : Konoha;
    }

    // init hero
    void generateKonohaHero(const char *name, const char *roleKind, unsigned int lv = 1)
    {
        if (!_loadLayer)
            return;

        // _loadLayer->addHero(name, role, Konoha, lv);
    }

    void generateAkatsukiHero(const char *name, const char *roleKind, unsigned int lv = 1)
    {
        if (!_loadLayer)
            return;

        // _loadLayer->addHero(name, role, Akatsuki, lv);
    }
};
