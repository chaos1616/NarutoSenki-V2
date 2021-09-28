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
				c->unschedule(schedule_selector(CharacterBase::resumeAction));
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
			auto newCharName = heroVector[c->changeCharId];
			CCLOG("[Change Character] From %s to %s", c->getCharacter()->getCString(), newCharName);

			if (c->isCharacter(newCharName))
			{
				c->changeCharId = -1;
				return;
			}
			else
			{
				// If the character has changed, then cleanup
				CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(c);
				if (c->_shadow)
					c->_shadow->removeFromParentAndCleanup(true);
				c->stopAllActions();
				c->unscheduleAllSelectors();
				c->removeFromParentAndCleanup(true);
				if (c->getMonsterArray() && c->getMonsterArray()->count() > 0)
				{
					CCObject *pObject;
					CCARRAY_FOREACH(c->getMonsterArray(), pObject)
					{
						auto mo = (Monster *)pObject;
						CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(mo);
						if (mo->_shadow)
							mo->_shadow->removeFromParentAndCleanup(true);
						mo->stopAllActions();
						mo->unscheduleAllSelectors();
						mo->removeFromParentAndCleanup(true);
					}
				}
				// Unload old character assets
				// If the new character has a sprite with the same name as the old character,
				// it may cause some null sprite errors
				LoadLayer::unloadCharIMG(c);
				// load new char assets
				LoadLayer::perloadCharIMG(newCharName);
			}
			auto hudLayer = gameLayer->getHudLayer();
			auto newChar = gameLayer->addHero(CCString::create(newCharName), c->getRole(), c->getGroup(), c->getSpawnPoint(), c->getCharNO());
			bool isPlayer = newChar->isPlayer();
			newChar->setCoin(c->getCoin());
			newChar->setCKR(c->getCKR());
			newChar->setCKR2(c->getCKR2());
			newChar->setEXP(c->getEXP());
			newChar->setLV(c->getLV());
			newChar->setKillNum(c->getKillNum());
			newChar->setWalkSpeed(224);
			newChar->setGearArray(c->getGearArray());
			newChar->changeHPbar();
			newChar->updateDataByLVOnly();
			CCObject *pObject = nullptr;
			CCARRAY_FOREACH(c->getGearArray(), pObject)
			{
				auto gear = (gearType)(((CCString *)pObject)->intValue());
				if (gear == gear00)
				{
					newChar->_isCanGear00 = true;
				}
				else if (gear == gear01)
				{
					newChar->gearCKRValue = 25;
				}
				else if (gear == gear02)
				{
					newChar->isAttackGainCKR = true;
				}
				else if (gear == gear03)
				{
					newChar->_isCanGear03 = true;
				}
				else if (gear == gear04)
				{
					if (newChar->gettempAttackValue1())
						newChar->settempAttackValue1(CCString::createWithFormat("%d", to_int(newChar->gettempAttackValue1()->getCString()) + 160));
					newChar->setnAttackValue(CCString::createWithFormat("%d", to_int(newChar->getnAttackValue()->getCString()) + 160));
					newChar->hasArmorBroken = true;
				}
				else if (gear == gear05)
				{
					newChar->isGearCD = true;
					newChar->_sattackcoldDown1 -= 5;
					newChar->_sattackcoldDown2 -= 5;
					newChar->_sattackcoldDown3 -= 5;
				}
				else if (gear == gear06)
				{
					newChar->_isCanGear06 = true;
				}
				else if (gear == gear07)
				{
					newChar->gearRecoverValue = 3000;
					if (isPlayer)
					{
						hudLayer->item1Button->setCD(CCString::createWithFormat("%d", 3000));
						hudLayer->item1Button->_isColdChanged = true;
					}
				}
				else if (gear == gear08)
				{
					uint32_t tempMaxHP = to_uint(newChar->getMaxHP()->getCString());
					tempMaxHP += 6000;
					newChar->setMaxHP(CCString::createWithFormat("%d", tempMaxHP));
					if (newChar->_hpBar)
					{
						newChar->_hpBar->loseHP(newChar->getHpPercent());
					}
					newChar->hasArmor = true;
				}
			}
			newChar->_deadNum = c->_deadNum;
			newChar->_flogNum = c->_flogNum;
			newChar->isBaseDanger = c->isBaseDanger;

			if (isPlayer)
			{
				gameLayer->currentPlayer = newChar;
				// reset hud layer
				hudLayer->updateSkillButtons();
				hudLayer->resetSkillButtons();

				hudLayer->status_hpbar->setOpacity(255);
				hudLayer->status_expbar->setOpacity(255);
				hudLayer->setHPLose(newChar->getHpPercent());
			}
			else if (newChar->isCom())
			{
				newChar->doAI();
			}
			gameLayer->_CharacterArray->replaceObjectAtIndex(c->getCharNO() - 1, newChar);
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
