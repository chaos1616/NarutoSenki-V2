#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeRandomDeathmatch : public IGameModeHandler
{
public:
	const uint8_t kRebornCount = 40;

private:
	uint8_t konohaRebornCount;
	uint8_t akatsukiRebornCount;
	uint8_t konohaLiveCount;
	uint8_t akatsukiLiveCount;

public:
	ModeRandomDeathmatch()
	{
		konohaRebornCount = kRebornCount;
		akatsukiRebornCount = kRebornCount;

		konohaLiveCount = 3;
		akatsukiLiveCount = 3;
	}

	void init()
	{
		konohaRebornCount = 30;
		akatsukiRebornCount = 30;
	}

	void onInitHeros()
	{
		initHeros(3, 3);
	}

	void onGameStart()
	{
	}

	void onGameOver()
	{
	}

	void onCharacterInit(CharacterBase *c)
	{
		// NOTE: Not implement
		// CCLOG("[Character Init] %s, %s, %s", c->getCharacter(), c->getRole(), c->getGroup());
	}

	void onCharacterDead(CharacterBase *c)
	{
		CCLOG("[Character Dead] Name: %s, Role: %s, Group: %s", c->getCharacter()->getCString(), c->getRole()->getCString(), c->getGroup()->getCString());

		if (c->isPlayerOrCom())
		{
			uint8_t &count = c->isKonohaGroup() ? konohaRebornCount : akatsukiRebornCount;
			uint8_t &liveCount = c->isKonohaGroup() ? konohaLiveCount : akatsukiLiveCount;
			if (count == 0)
			{
				c->enableReborn = false;
				if (liveCount == 0)
					_gLayer->onGameOver(!c->isGroup(playerGroup));
			}
			else
			{
				count--;
				liveCount--;
				setRandomHero(c);
			}
		}
	}

	void onCharacterReborn(CharacterBase *c)
	{
		CCLOG("[Character Reborn] Name: %s, Role: %s, Group: %s", c->getCharacter()->getCString(), c->getRole()->getCString(), c->getGroup()->getCString());

		if (c->isPlayerOrCom())
		{
			uint8_t liveCount = c->isKonohaGroup() ? konohaLiveCount++ : akatsukiLiveCount++;
		}
	}

private:
	void setRandomHero(CharacterBase *c)
	{
		auto index = getIndexByHero(c);
		if (index == -1)
		{
			CCLOGERROR("Not found hero %s from heros vector", c->getCharacter()->getCString());
			return;
		}

		auto newChar = getRandomHeroExceptAll(herosVector);
		herosVector[index] = newChar;
		c->setID(CCString::create(newChar), c->getRole(), c->getGroup());
	}

	int getIndexByHero(CharacterBase *c)
	{
		for (size_t i = 0; i < herosVector.size(); i++)
		{
			if (c->isCharacter(herosVector[i]))
				return i;
		}
		return -1;
	}
};
