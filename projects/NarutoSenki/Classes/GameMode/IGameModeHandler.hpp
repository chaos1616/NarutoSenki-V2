#pragma once
#include "cocos2d.h"
#include "CharacterBase.h"
#include "GameLayer.h"
#include "LoadLayer.h"

using namespace cocos2d;

class IGameModeHandler;
class SelectLayer;

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

static GameMode s_GameMode = GameMode::Classic;
static IGameModeHandler *s_IGameModeHandler = nullptr;

class IGameModeHandler
{
    friend class GameLayer;
    friend class GameModeLayer;

private:
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

    virtual CCArray *onInitHeros(SelectLayer *selectLayer) = 0;
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
    // void addHero(const char *name, const char *role, const char *group)
    // {
    // }

    void generateKonohaHero(const char *name, const char *roleKind, unsigned int lv = 1)
    {
        // addHero(name, role, Konoha, lv);
    }

    void generateAkatsukiHero(const char *name, const char *roleKind, unsigned int lv = 1)
    {
        // addHero(name, role, Akatsuki, lv);
    }

    CCArray *initHeros(SelectLayer *selectLayer)
    {
        CCDictionary *dic = CCDictionary::create();

        CCString *tmpChar;

        if (selectLayer->_playerSelect)
        {
            tmpChar = CCString::create(selectLayer->_playerSelect);
        }
        else
        {
            int num2 = selectLayer->_selectList->count();
            int index = random(num2);
            tmpChar = (CCString *)selectLayer->_selectList->objectAtIndex(index);
            do
            {
                int num = selectLayer->_selectList->count();
                int index = random(num);
                tmpChar = (CCString *)selectLayer->_selectList->objectAtIndex(index);
            } while (strcmp(tmpChar->getCString(), "None") == 0);

            selectLayer->_playerSelect = tmpChar->getCString();
            selectLayer->setIsRandomChar(true);
        }

        int team = random(2);
        const char *groupName = team > 0 ? Konoha : Akatsuki;

        CCString *tmpRole = CCString::create("Player");
        CCString *tmpGroup = CCString::create(groupName);

        dic->setObject(tmpChar, "character");
        dic->setObject(tmpRole, "role");
        dic->setObject(tmpGroup, "group");

        CCArray *tempHeros = CCArray::createWithObject(dic);
        CCArray *realHero = CCArray::create();

        for (int i = 0; i < kHeroNum; i++)
        {
            if (strcmp(selectLayer->_playerSelect, kHeroList[i]) == 0)
                continue;

            if (selectLayer->_com1Select)
            {
                if (strcmp(selectLayer->_com1Select, kHeroList[i]) == 0)
                    continue;
            }
            if (selectLayer->_com2Select)
            {
                if (strcmp(selectLayer->_com2Select, kHeroList[i]) == 0)
                    continue;
            }

            CCString *hero = CCString::create(kHeroList[i]);
            realHero->addObject(hero);
        }

        for (int i = 0; i < ComCount; i++)
        {
            CCString *hero;
            if (i < KonohaCount)
            {

                if (i == 0 && selectLayer->_com1Select)
                {
                    hero = CCString::create(selectLayer->_com1Select);
                }
                else if (i == 1 && selectLayer->_com2Select)
                {
                    hero = CCString::create(selectLayer->_com2Select);
                }
                else
                {
                    int length = realHero->count();
                    int index = random(length);
                    if (index == (int)realHero->count())
                    {
                        index = realHero->count() - 1;
                    }

                    CCObject *tempObject = realHero->objectAtIndex(index);
                    hero = (CCString *)tempObject;
                    realHero->removeObjectAtIndex(index);
                }

                dic = CCDictionary::create();
                tmpChar = CCString::create(hero->getCString());
                tmpRole = CCString::create("Com");
                tmpGroup = CCString::create(team > 0 ? Konoha : Akatsuki);
                dic->setObject(tmpChar, "character");
                dic->setObject(tmpRole, "role");
                dic->setObject(tmpGroup, "group");

                tempHeros->addObject(dic);
            }
            else
            {
                int length = realHero->count();
                int index = random(length);
                if (index == (int)realHero->count())
                {
                    index = realHero->count() - 1;
                }

                CCObject *tempObject = realHero->objectAtIndex(index);
                CCString *hero = (CCString *)tempObject;

                dic = CCDictionary::create();
                tmpChar = CCString::create(hero->getCString());
                tmpRole = CCString::create("Com");
                tmpGroup = CCString::create(team > 0 ? Akatsuki : Konoha);
                dic->setObject(tmpChar, "character");
                dic->setObject(tmpRole, "role");
                dic->setObject(tmpGroup, "group");

                tempHeros->addObject(dic);
                realHero->removeObjectAtIndex(index);
            }
        }

        return tempHeros;
    }
};
