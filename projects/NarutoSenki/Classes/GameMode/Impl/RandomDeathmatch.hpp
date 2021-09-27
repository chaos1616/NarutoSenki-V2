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
			auto gameLayer = c->getDelegate();
			// initial a new random character
			auto newCharName = CCString::create(heroVector[c->changeCharId]);
			auto newChar = gameLayer->addHero(newCharName, c->getRole(), c->getGroup(), c->getSpawnPoint(), c->getCharNO());
			newChar->setCoin(c->getCoin());
			newChar->setCKR(c->getCKR());
			newChar->setCKR2(c->getCKR2());
			newChar->setEXP(c->getEXP());
			newChar->setLV(c->getLV());
			newChar->setKillNum(c->getKillNum());
			newChar->setWalkSpeed(224);
			newChar->setGearArray(c->getGearArray());
			CCObject *pObject = nullptr;
			CCARRAY_FOREACH(c->getGearArray(), pObject)
			{
				auto gear = (gearType)(((CCString *)pObject)->intValue());
				if (gear == gear00)
					newChar->_isCanGear00 = true;
				if (gear == gear03)
					newChar->_isCanGear03 = true;
				if (gear == gear06)
					newChar->_isCanGear06 = true;
			}
			newChar->_deadNum = c->_deadNum;
			newChar->_flogNum = c->_flogNum;
			newChar->isBaseDanger = c->isBaseDanger;
			newChar->hasArmor = c->hasArmor;
			newChar->isGearCD = c->isGearCD;
			newChar->changeHPbar();
			if (newChar->isCom())
			{
				newChar->doAI();
			}
			else if (newChar->isPlayer())
			{
				auto hudLayer = gameLayer->getHudLayer();
				gameLayer->currentPlayer = newChar;
				// reset hud layer
				hudLayer->updateSkillButtons();
				hudLayer->resetSkillButtons();

				hudLayer->status_hpbar->setOpacity(255);
				hudLayer->status_expbar->setOpacity(255);
				hudLayer->setHPLose(newChar->getHpPercent());
			}
			gameLayer->_CharacterArray->replaceObjectAtIndex(c->getCharNO() - 1, newChar);
			CCLOG("[Change Character] From %s to %s", c->getCharacter()->getCString(), newCharName->getCString());

			// unload old character assets
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
