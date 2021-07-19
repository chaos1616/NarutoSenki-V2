#pragma once
#include "CharacterBase.h"
#include "GameLayer.h"
#include "LoadLayer.h"
#include "SelectLayer.h"

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
	friend class GameModeLayer;
	friend class SelectLayer;

private:
	CCArray *_herosArr = nullptr;
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

	void Internal_Init()
	{
		init();
	}

	void Internal_GameOver()
	{
		CC_SAFE_RELEASE_NULL(_herosArr);

		onGameOver();
	}

protected:
	SelectLayer *selectLayer;
	// game
	bool isHardCoreGame;

public:
	const uint8_t kMaxCharCount = 4;
	const int kDefaultMap = 1;
	const char *kDefaultGroup = Konoha;

	virtual void init() = 0;

	virtual void onInitHeros() = 0;
	virtual void onGameStart() = 0;
	virtual void onGameOver() = 0;

	// callbacks
	virtual void onCharacterInit(CharacterBase *c) = 0;
	virtual void onCharacterDead(CharacterBase *c) = 0;
	virtual void onCharacterReborn(CharacterBase *c) = 0;

protected:
	CCArray *getHerosArray()
	{
		return _herosArr;
	}

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

	// init hero
	void addHero(const char *name, const char *role, const char *group, uint32_t lv = 1)
	{
		auto dic = CCDictionary::create();
		dic->setObject(CCString::create(name), "character");
		dic->setObject(CCString::create(role), "role");
		dic->setObject(CCString::create(group), "group");
		if (!_herosArr)
			_herosArr = CCArray::create();
		_herosArr->addObject(dic);
	}

	void addHeros(int count, const char *name, const char *role, const char *group, uint32_t lv = 1)
	{
		for (int i = 0; i < count; i++)
			addHero(name, role, group, lv);
	}

	void addKonohaHero(CCArray *heros, const char *name, const char *role, uint32_t lv = 1)
	{
		addHero(name, role, Konoha, lv);
	}

	void addAkatsukiHero(CCArray *heros, const char *name, const char *role, uint32_t lv = 1)
	{
		addHero(name, role, Akatsuki, lv);
	}

	CCArray *initHeros(uint32_t konohaCount, uint32_t akatsukiCount)
	{
		return initHeros(konohaCount, akatsukiCount, nullptr, nullptr);
	}

	CCArray *initHeros(uint8_t konohaCount, uint8_t akatsukiCount,
					   const char *playerSelect, const char *playerGroup,
					   const char *com1Select = nullptr, const char *com2Select = nullptr, const char *com3Select = nullptr)
	{
		konohaCount = konohaCount > kMaxCharCount ? kMaxCharCount : konohaCount;
		akatsukiCount = akatsukiCount > kMaxCharCount ? kMaxCharCount : akatsukiCount;
		setRand();
		int team = random(2);
		uint8_t comCount = konohaCount + akatsukiCount - 1;
		uint8_t comOfPlayerGroupCount = (team == 0 ? konohaCount : akatsukiCount) - 1;

		if (playerSelect)
			selectLayer->_playerSelect = playerSelect;
		if (com1Select)
			selectLayer->_com1Select = com1Select;
		if (com2Select)
			selectLayer->_com2Select = com2Select;
		if (com3Select)
			selectLayer->_com3Select = com3Select;

		// init player hero
		CCString *tmpChar;
		if (selectLayer->_playerSelect)
		{
			tmpChar = CCString::create(selectLayer->_playerSelect);
		}
		else
		{
			int num2 = selectLayer->_selectList->count();
			setRand();
			int index = random(num2);
			tmpChar = (CCString *)selectLayer->_selectList->objectAtIndex(index);
			do
			{
				int num = selectLayer->_selectList->count();
				setRand();
				int index = random(num);
				tmpChar = (CCString *)selectLayer->_selectList->objectAtIndex(index);
			} while (strcmp(tmpChar->getCString(), "None") == 0);

			selectLayer->_playerSelect = tmpChar->getCString();
			selectLayer->setIsRandomChar(true);
		}

		CCString *tmpRole = CCString::create("Player");
		CCString *tmpGroup = CCString::create(team > 0 ? Konoha : Akatsuki);

		CCDictionary *dic = CCDictionary::create();
		dic->setObject(tmpChar, "character");
		dic->setObject(tmpRole, "role");
		dic->setObject(tmpGroup, "group");

		CCArray *herosArr = CCArray::createWithObject(dic);
		CCArray *realHero = CCArray::create();

		// init com heros
		for (int i = 0; i < kHeroNum; i++)
		{
			if (strcmp(selectLayer->_playerSelect, kHeroList[i]) == 0)
				continue;
			if (selectLayer->_com1Select && strcmp(selectLayer->_com1Select, kHeroList[i]) == 0)
				continue;
			if (selectLayer->_com2Select && strcmp(selectLayer->_com2Select, kHeroList[i]) == 0)
				continue;
			if (selectLayer->_com3Select && strcmp(selectLayer->_com3Select, kHeroList[i]) == 0)
				continue;

			CCString *hero = CCString::create(kHeroList[i]);
			realHero->addObject(hero);
		}

		for (int i = 0; i < comCount; i++)
		{
			CCString *hero;
			if (i < comOfPlayerGroupCount)
			{
				if (i == 0 && selectLayer->_com1Select)
				{
					hero = CCString::create(selectLayer->_com1Select);
				}
				else if (i == 1 && selectLayer->_com2Select)
				{
					hero = CCString::create(selectLayer->_com2Select);
				}
				else if (i == 2 && selectLayer->_com3Select)
				{
					hero = CCString::create(selectLayer->_com3Select);
				}
				else
				{
					int length = realHero->count();
					setRand();
					int index = random(length);
					if (index == length)
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

				herosArr->addObject(dic);
			}
			else
			{
				int length = realHero->count();
				setRand();
				int index = random(length);
				if (index == length)
					index = realHero->count() - 1;

				CCObject *tempObject = realHero->objectAtIndex(index);
				CCString *hero = (CCString *)tempObject;

				dic = CCDictionary::create();
				tmpChar = CCString::create(hero->getCString());
				tmpRole = CCString::create("Com");
				tmpGroup = CCString::create(team > 0 ? Akatsuki : Konoha);
				dic->setObject(tmpChar, "character");
				dic->setObject(tmpRole, "role");
				dic->setObject(tmpGroup, "group");

				herosArr->addObject(dic);
				realHero->removeObjectAtIndex(index);
			}
		}

		return _herosArr = herosArr;
	}

	/**
	 * Static Utils
	 */

	static inline const char *getRandomHero()
	{
		return kHeroList[random(kHeroNum)];
	}

	static inline const char *getRandomHeroExcept(const char *except)
	{
		setRand();
		if (except)
		{
			int i = random(kHeroNum);
			while (strcmp(kHeroList[i], except) == 0)
				i = random(kHeroNum);
			return kHeroList[i];
		}
		else
		{
			return kHeroList[random(kHeroNum)];
		}
	}

	static inline const char *getRandomGroup()
	{
		setRand();
		return random(2) == 0 ? Konoha : Akatsuki;
	}

	static inline void getRandomGroups(const char *&groupA, const char *&groupB)
	{
		setRand();
		int team = random(2) == 0;
		groupA = team == 0 ? Konoha : Akatsuki;
		groupB = team == 0 ? Akatsuki : Konoha;
	}
};
