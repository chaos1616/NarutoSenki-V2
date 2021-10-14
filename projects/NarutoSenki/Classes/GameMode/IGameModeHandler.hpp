#pragma once
#include "Core/Hero.hpp"
#include "GameLayer.h"
#include "LoadLayer.h"
#include "SelectLayer.h"

class IGameModeHandler;

enum GameMode
{
	// 1 VS 1 // TODO: As a test mode
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
	Deathmatch, // TODO
	// 3 VS 3
	RandomDeathmatch,

	_Internal_Max_Length
}; // namespace GameMode

struct GameModeData
{
public:
	string title;
	string description;

	bool isLocked;
	bool useMask2;

	bool hasSelected;
	// IGameModeHandler *handler;

	// static const GameModeData &from(const char *path);
};

struct GameData
{
	bool enableGear = true;
	bool isHardCore = true;
	bool isRandomChar = false;

	string playerGroup;
};

class IGameModeHandler
{
	friend class GameLayer;
	friend class GameModeLayer;
	friend class SelectLayer;

private:
	vector<HeroData> heroDataVector;
	// map
	int mapId = 0;
	// tower
	bool enableKonohaTowers = true;
	bool enableAkatsukiTowers = true;
	// flog
	bool skipInitFlogs = false;
	bool enableKonohaFlogs = false;
	bool enableAkatsukiFlogs = false;
	float flogSpawnDuration = 15.0f;
	bool isLimitFlog = false;
	int maxFlogWaves;
	// hero
	bool enableHeroReborn = true;

	void Internal_GameOver()
	{
		onGameOver();

		clearHeroArray();
	}

protected:
	SelectLayer *selectLayer = nullptr;
	// game
	GameData gd;
	int oldCheats;
	vector<string> heroVector;
	// player
	const char *playerGroup = nullptr;

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

	inline const GameData &getGameData() { return gd; }
	inline int getOldCheats() { return oldCheats; }
	inline int resetCheats() { return Cheats = oldCheats; }
	inline const vector<HeroData> &getHerosArray() { return heroDataVector; }

protected:
	IGameModeHandler()
	{
		oldCheats = Cheats;
	}

	void clearHeroArray()
	{
		heroDataVector.clear();
		heroVector.clear();
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
		this->flogSpawnDuration = (duration < 5 || duration > 60) ? 15.0f : duration;
		this->isLimitFlog = maxWaves >= 0;
		this->maxFlogWaves = maxWaves;
	}

	void setHero(bool enableReborn)
	{
		this->enableHeroReborn = enableReborn;
	}

	// init hero
	inline void addHero(const char *name, const char *role, const char *group, uint32_t lv = 1)
	{
		heroDataVector.push_back({name, role, group});
		heroVector.push_back(name);
	}

	inline void addHeros(int count, const char *name, const char *role, const char *group, uint32_t lv = 1)
	{
		for (int i = 0; i < count; i++)
			addHero(name, role, group, lv);
	}

	inline void addKonohaHero(const vector<string> &heros, const char *name, const char *role, uint32_t lv = 1)
	{
		addHero(name, role, Konoha, lv);
	}

	inline void addAkatsukiHero(const vector<string> &heros, const char *name, const char *role, uint32_t lv = 1)
	{
		addHero(name, role, Akatsuki, lv);
	}

	inline void initHeros(uint32_t playerCount, uint32_t enemyCount)
	{
		initHeros(playerCount, enemyCount, nullptr, nullptr);
	}

	void initHeros(uint8_t playerCount, uint8_t enemyCount,
				   const char *playerSelect, const char *playerGroup,
				   const char *com1Select = nullptr, const char *com2Select = nullptr, const char *com3Select = nullptr)
	{
		clearHeroArray();

		playerCount = playerCount > kMaxCharCount ? kMaxCharCount : playerCount;
		enemyCount = enemyCount > kMaxCharCount ? kMaxCharCount : enemyCount;
		setRand();
		int team = random(2);
		// TODO: Support custom player group
		// playerGroup = playerGroup == nullptr ? (team > 0 ? Konoha : Akatsuki) : playerGroup;
		playerGroup = team > 0 ? Akatsuki : Konoha;
		this->gd.playerGroup = playerGroup;
		this->playerGroup = playerGroup;
		uint8_t totalCount = playerCount + enemyCount;
		uint8_t comCount = totalCount > 0 ? totalCount - 1 : 0;
		uint8_t comOfPlayerGroupCount = playerCount > 0 ? playerCount - 1 : 0;

		if (playerSelect)
			selectLayer->_playerSelect = playerSelect;
		if (com1Select)
			selectLayer->_com1Select = com1Select;
		if (com2Select)
			selectLayer->_com2Select = com2Select;
		if (com3Select)
			selectLayer->_com3Select = com3Select;

		// init player hero
		string tmpChar;
		if (selectLayer->_playerSelect)
		{
			tmpChar = selectLayer->_playerSelect;
		}
		else
		{
			auto selcetList = selectLayer->_selectList;
			int count = selcetList->count();
			setRand();
			int index = random(count);
			tmpChar = ((CCString *)selcetList->objectAtIndex(index))->m_sString;
			do
			{
				setRand();
				index = random(count);
				tmpChar = ((CCString *)selcetList->objectAtIndex(index))->m_sString;
			} while (tmpChar == "None");

			selectLayer->_playerSelect = tmpChar.c_str();
			gd.isRandomChar = true;
		}

		// push player
		heroDataVector.push_back({tmpChar, kRolePlayer, playerGroup});
		heroVector.push_back(tmpChar);

		// init com heros
		vector<string> realHeroVector;
		for (int i = 0; i < kHeroNum; i++)
		{
			if (is_same(selectLayer->_playerSelect, kHeroList[i]))
				continue;
			if (selectLayer->_com1Select && is_same(selectLayer->_com1Select, kHeroList[i]))
				continue;
			if (selectLayer->_com2Select && is_same(selectLayer->_com2Select, kHeroList[i]))
				continue;
			if (selectLayer->_com3Select && is_same(selectLayer->_com3Select, kHeroList[i]))
				continue;

			realHeroVector.push_back(kHeroList[i]);
		}

		string hero;
		for (int i = 0; i < comCount; i++)
		{
			if (i < comOfPlayerGroupCount)
			{
				if (i == 0 && selectLayer->_com1Select)
				{
					hero = selectLayer->_com1Select;
				}
				else if (i == 1 && selectLayer->_com2Select)
				{
					hero = selectLayer->_com2Select;
				}
				else if (i == 2 && selectLayer->_com3Select)
				{
					hero = selectLayer->_com3Select;
				}
				else
				{
					int count = realHeroVector.size();
					setRand();
					int index = random(count);
					if (index == count)
						index = realHeroVector.size() - 1;

					hero = realHeroVector.at(index);
					realHeroVector.erase(std::find(realHeroVector.begin(), realHeroVector.end(), hero));
				}

				heroDataVector.push_back({hero, kRoleCom, team > 0 ? Akatsuki : Konoha});
				heroVector.push_back(hero);
			}
			else
			{
				int count = realHeroVector.size();
				setRand();
				int index = random(count);
				if (index == count)
					index = realHeroVector.size() - 1;

				hero = realHeroVector.at(index);
				heroDataVector.push_back({hero, kRoleCom, team > 0 ? Konoha : Akatsuki});
				heroVector.push_back(hero);
				realHeroVector.erase(std::find(realHeroVector.begin(), realHeroVector.end(), hero));
			}
		}
	}

	inline void setPlayerTeamByGroup(const char *group)
	{
		gd.playerGroup = group;
	}

	/**
	 * Static Utils
	 */

	static inline const char *getRandomHero()
	{
		setRand();
		return kHeroList[random(kHeroNum)];
	}

	static inline const char *getRandomHeroExcept(const char *except)
	{
		if (except)
		{
			setRand();
			int i = random(kHeroNum);
			while (is_same(kHeroList[i], except))
				i = random(kHeroNum);
			return kHeroList[i];
		}
		else
		{
			return kHeroList[random(kHeroNum)];
		}
	}

	static inline const char *getRandomHeroExceptAll(const vector<string> &excepts, const char *defaultChar = "Naruto")
	{
		bool ret = true;
		int i;
		while (ret)
		{
			setRand();
			i = random(kHeroNum);
			for (size_t j = 0; j < excepts.size(); j++)
			{
				if (excepts[j] == kHeroList[i])
				{
					ret = true;
					continue;
				}
				ret &= false;
			}
		}
		return !ret ? kHeroList[i] : defaultChar;
	}

	inline const char *getSelectedOrRandomHero()
	{
		return selectLayer->_playerSelect ? selectLayer->_playerSelect : getRandomHero();
	}

	inline const char *getSelectOrRandomHeroExcept(const char *except)
	{
		return selectLayer->_playerSelect ? selectLayer->_playerSelect : getRandomHeroExcept(except);
	}

	inline const char *getSelectOrRandomHeroExceptAll(const vector<string> &excepts, const char *defaultChar = "Naruto")
	{
		return selectLayer->_playerSelect ? selectLayer->_playerSelect : getRandomHeroExceptAll(excepts, defaultChar);
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
