#pragma once
#include "Core/Provider.hpp"
#include "GameMode/IGameModeHandler.hpp"

class ModeRandomDeathmatch : public IGameModeHandler
{
public:
	const uint8_t kRebornCount = 40;
	const uint8_t kHeroAmount = 3;

private:
	uint8_t konohaRebornCount;
	uint8_t akatsukiRebornCount;
	uint8_t konohaLiveCount;
	uint8_t akatsukiLiveCount;

public:
	void init()
	{
		CCLOG("Enter Random Deathmatch mode.");

		konohaRebornCount = kRebornCount;
		akatsukiRebornCount = kRebornCount;

		konohaLiveCount = kHeroAmount;
		akatsukiLiveCount = kHeroAmount;

		gd.isHardCore = true;
	}

	void onInitHeros()
	{
		initHeros(kHeroAmount, kHeroAmount);
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

		if (c->changeCharId > -1)
		{
			// TODO: initial a new random character
			auto newCharName = CCString::create(heroVector[c->changeCharId]);
			CharacterBase *newChar = Provider::create(newCharName, c->getRole(), c->getGroup());
			if (c->isPlayer())
			{
				c->getDelegate()->currentPlayer = newChar;
			}
			c->getDelegate()->_CharacterArray->replaceObjectAtIndex(c->getCharNO() - 1, newChar);
			CCLOG("[Change Character] From %s to %s", c->getCharacter()->getCString(), newCharName->getCString());

			c->dealloc();
			// unload old char assets
			LoadLayer::unloadCharIMG(c); // Unload dead hero's assets
		}
	}

private:
	void setRandomHero(CharacterBase *c)
	{
		auto index = getIndexByHero(c);
		if (index == -1)
		{
			CCLOGERROR("Not found hero %s from hero vector", c->getCharacter()->getCString());
			return;
		}
		c->changeCharId = index;

		auto newChar = getRandomHeroExceptAll(heroVector);
		heroVector[index] = newChar;
		// load new char assets
		LoadLayer::perloadCharIMG(newChar);
	}

	int getIndexByHero(CharacterBase *c)
	{
		const char *realName = nullptr;
		if (c->isCharacter("SageNaruto"))
			realName = "Naruto";
		else if (c->isCharacter("RikudoNaruto"))
			realName = "Naruto";
		else if (c->isCharacter("SageJiraiya"))
			realName = "Jiraiya";
		else if (c->isCharacter("ImmortalSasuke"))
			realName = "Sasuke";
		else if (c->isCharacter("RockLee"))
			realName = "Lee";
		realName = realName ? realName : c->getCharacter()->getCString();

		for (size_t i = 0; i < heroVector.size(); i++)
		{
			if (strcmp(heroVector[i], realName) == 0)
				return i;
		}
		return -1;
	}
};
