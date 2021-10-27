#pragma once
#include "Core/Hero.hpp"
#include "Enums/Enums.hpp"

#include <unordered_map>

namespace Command
{
	mk_const(addHP);
	mk_const(setInvincible);
	mk_const(setGainCKR);
	mk_const(reInvincible);
	mk_const(setInvisible);
	mk_const(reInvisible);
	mk_const(setTransport2);
	mk_const(setTransport);
	mk_const(reTransport);
	mk_const(setDead);
	mk_const(findTarget);
	mk_const(setRevive);
	mk_const(setTrade);
	mk_const(addExtern);
	mk_const(pauseJump);
	mk_const(setCounter);
} // namespace Command

using CommandHandler = std::function<void(CharacterBase *)>;

class CommandSystem
{
private:
	static inline std::unordered_map<string, CommandHandler> cmdMap;

public:
	static inline void on(const string &cmd, CommandHandler handler)
	{
		cmdMap.insert(std::make_pair(cmd, handler));
	}

	static inline void invoke(const string &cmd, CharacterBase *thiz)
	{
		auto it_find = cmdMap.find(cmd);
		if (it_find != cmdMap.end())
		{
			auto handler = it_find->second;
			handler(thiz);
		}
		else
		{
			CCLOGERROR("Not found command handler `%s`", cmd.c_str());
		}
	}

	static inline void remove(const string &cmd)
	{
		cmdMap.erase(cmd);
	}

	static inline void replaceOrInsert(const string &cmd, CommandHandler handler)
	{
		cmdMap[cmd] = handler;
	}

	static inline void reset()
	{
		cmdMap.clear();
		init();

		if (cmdMap.size() > 0)
			CCLOG("[ Command System ] Count: %lu ", cmdMap.size());
		else
			CCLOG("[ Command System ] Initial error, not found any command");
	}

private:
	static void init()
	{
		on(Command::addExtern, [](CharacterBase *thiz)
		   {
			   auto tempArray = CCArray::create();

			   int i = 1;
			   if (thiz->isCharacter("Tenten"))
			   {
				   while (i < 11)
				   {
					   auto frame = getSpriteFrame("Tenten_Extern_0{}", i);
					   tempArray->addObject(frame);
					   i += 1;
				   }
			   }

			   auto tempAnimation = CCAnimation::createWithSpriteFrames(tempArray, 0.1f);
			   auto tempAction = CCAnimate::create(tempAnimation);
			   auto call = CallFunc::create(std::bind(&CharacterBase::disableShadow, thiz, thiz));
			   auto seq = newSequence(tempAction, call);

			   auto tempChar = CCSprite::createWithSpriteFrameName(format("{}_Extern_01", thiz->getCharacter()->getCString()).c_str());
			   tempChar->setAnchorPoint(ccp(0.5f, 0));
			   tempChar->setPosition(thiz->getPosition());
			   getGameLayer()->addChild(tempChar, -thiz->_originY);

			   tempChar->runAction(seq);
		   });
		on(Command::addHP, [](CharacterBase *thiz)
		   {
			   if (thiz->_hpBar)
			   {
				   thiz->setHPValue(thiz->getMaxHPValue());
				   thiz->_hpBar->setPositionY(thiz->getHeight());
			   }
		   });
		on(Command::findTarget, [](CharacterBase *thiz)
		   {
			   if (thiz->notFindHero(0))
			   {
				   if (thiz->notFindFlog(0) ||
					   thiz->isCharacter("RikudoNaruto", "SageNaruto"))
					   thiz->_mainTarget = nullptr;
			   }

			   if (thiz->_mainTarget)
			   {
				   if (thiz->isCharacter("Dogs") ||
					   thiz->isCharacter("Yominuma") ||
					   thiz->isCharacter("SandBall") ||
					   thiz->isCharacter("Sabaku") ||
					   thiz->isCharacter("Yataikuzu") ||
					   thiz->isCharacter("Lee") ||
					   thiz->isCharacter("RockLee"))
				   {
					   thiz->_markPoint = ccp(thiz->_mainTarget->getPositionX(), thiz->_mainTarget->_originY ? thiz->_mainTarget->_originY : thiz->_mainTarget->getPositionY());
				   }
				   else if (thiz->isCharacter("Tsukuyomi"))
				   {
					   thiz->_markPoint = ccp(thiz->_mainTarget->getPositionX(), thiz->_mainTarget->_originY ? thiz->_mainTarget->_originY : thiz->_mainTarget->getPositionY() + 2);
				   }
				   else if (thiz->isCharacter("KageFeng"))
				   {
					   thiz->_markPoint = ccp(thiz->_mainTarget->getPositionX(), thiz->_mainTarget->_originY ? thiz->_mainTarget->_originY - 6 : thiz->_mainTarget->getPositionY() - 6);
				   }
				   else
				   {
					   thiz->_markPoint = ccp(thiz->_mainTarget->_isFlipped ? thiz->_mainTarget->getPositionX() + 32 : thiz->_mainTarget->getPositionX() - 32,
											  thiz->_mainTarget->_originY ? thiz->_mainTarget->_originY : thiz->_mainTarget->getPositionY());
				   }
			   }
		   });
		on(Command::pauseJump, [](CharacterBase *thiz)
		   {
			   // pause jump
			   thiz->getActionManager()->addAction(thiz->_jumpUPAction, thiz, false);
		   });
		on(Command::setDead, [](CharacterBase *thiz)
		   {
			   thiz->_isSuicide = true;
			   thiz->dead();
		   });
		on(Command::setGainCKR, [](CharacterBase *thiz)
		   {
			   uint32_t boundValue = 1500;
			   thiz->increaseAllCkrs(boundValue, true, !thiz->_isControlled);
		   });
		on(Command::setInvincible, [](CharacterBase *thiz)
		   {
			   // set character invincible
			   thiz->_isInvincible = true;
		   });
		on(Command::reInvincible, [](CharacterBase *thiz)
		   {
			   // unset character invincible
			   thiz->_isInvincible = false;
		   });
		on(Command::setInvisible, [](CharacterBase *thiz)
		   {
			   thiz->setVisible(false);
			   thiz->_isVisable = false;
		   });
		on(Command::reInvisible, [](CharacterBase *thiz)
		   {
			   thiz->setVisible(true);
			   thiz->_isVisable = true;
		   });
		on(Command::setTransport, [](CharacterBase *thiz)
		   {
			   int tsPosX = thiz->getPositionX();
			   int tsPosY = thiz->getPositionY();

			   if (thiz->_mainTarget)
			   {
				   if (thiz->_mainTarget->_isFlipped)
				   {
					   thiz->setFlipX(true);
					   thiz->_isFlipped = true;
				   }
				   else
				   {
					   thiz->setFlipX(false);
					   thiz->_isFlipped = false;
				   }
			   }

			   if (thiz->isCharacter("Sakura"))
			   {
				   float posY = thiz->getPositionY();
				   if (!thiz->_originY)
				   {
					   if (posY == 0)
						   posY = 0.1f;
					   thiz->_originY = posY;
				   }
				   thiz->setPosition(ccp(thiz->getPositionX(), thiz->getPositionY() + 64));
				   return;
			   }
			   else
			   {
				   if (thiz->_markPoint.x != 0)
				   {
					   thiz->_startPoint = ccp(tsPosX, tsPosY);
					   tsPosX = thiz->_markPoint.x;
					   tsPosY = thiz->_markPoint.y;
					   thiz->_markPoint = ccp(0, 0);
				   }
				   else if (thiz->_startPoint.x != 0)
				   {
					   tsPosX = thiz->_startPoint.x;
					   tsPosY = thiz->_startPoint.y;
					   thiz->_startPoint = ccp(0, 0);
				   }
			   }

			   thiz->setPosition(ccp(tsPosX, tsPosY));
			   CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", thiz);

			   if (thiz->isNotCharacter("Yominuma"))
			   {
				   getGameLayer()->reorderChild(thiz, -tsPosY);
			   }
		   });
		on(Command::reTransport, [](CharacterBase *thiz)
		   {
			   thiz->setPosition(ccp(thiz->getPositionX(), thiz->_originY));
			   thiz->_originY = 0;
		   });
		// For special characters
		on(Command::setCounter, [](CharacterBase *thiz)
		   {
			   bool _isCounter = false;
			   if (thiz->hasMonsterArrayAny())
			   {
				   for (auto mo : thiz->getMonsterArray())
				   {
					   float distanceX = ccpSub(mo->getPosition(), thiz->getPosition()).x;
					   float distanceY = ccpSub(mo->getPosition(), thiz->getPosition()).y;
					   if (abs(distanceX) < 40 && abs(distanceY) < 15)
					   {
						   _isCounter = true;
					   }
				   }
			   }

			   if (_isCounter)
			   {
				   for (auto hero : getGameLayer()->_CharacterArray)
				   {
					   if (thiz->isNotSameGroupAs(hero) &&
						   hero->isPlayerOrCom() &&
						   hero->_actionState != State::DEAD)
					   {
						   if (hero->_hpBar)
						   {
							   if (hero->getHPValue() <= 2000)
								   hero->setDamage(thiz, "c_hit", hero->getHPValue(), false);
							   else
								   hero->setDamage(thiz, "c_hit", 2000, false);

							   if (hero->isPlayer())
								   getGameLayer()->setHPLose(hero->getHpPercent());
						   }
					   }
				   }
			   }
			   else
			   {
				   if (thiz->_hpBar)
				   {
					   if (thiz->getHPValue() <= 2000)
						   thiz->setDamage(thiz, "c_hit", thiz->getHPValue(), false);
					   else
						   thiz->setDamage(thiz, "c_hit", 2000, false);

					   if (thiz->isPlayer())
						   getGameLayer()->setHPLose(thiz->getHpPercent());
				   }
			   }

			   thiz->setActionResume();
		   });
		on(Command::setRevive, [](CharacterBase *thiz)
		   {
			   for (auto hero : getGameLayer()->_CharacterArray)
			   {
				   if (thiz->isSameGroupAs(hero) &&
					   hero->isPlayerOrCom() &&
					   hero->_actionState == State::DEAD &&
					   hero->rebornSprite)
				   {
					   hero->unschedule(schedule_selector(Hero::reborn));
					   hero->reborn(0.1f);
				   }
			   }
		   });
		on(Command::setTrade, [](CharacterBase *thiz)
		   {
			   for (auto hero : getGameLayer()->_CharacterArray)
			   {
				   if (hero->hearts > 0 &&
					   hero->_actionState == State::DEAD &&
					   hero->rebornSprite &&
					   hero->isPlayerOrCom() &&
					   hero->isNotCharacter("Kakuzu"))
				   {
					   CCPoint sp = ccpSub(hero->getPosition(), thiz->getPosition());
					   if (abs(sp.x) <= 48 && abs(sp.y) <= 48)
					   {
						   hero->hearts -= 1;
						   if (thiz->isNotSameGroupAs(hero))
						   {
							   uint32_t tempMaxHP = thiz->getMaxHPValue();
							   tempMaxHP += 100;
							   thiz->setnAttackValue(to_ccstring(thiz->getNAttackValue() + 5));
							   thiz->setMaxHPValue(tempMaxHP);
						   }

						   if (thiz->isPlayer())
						   {
							   if (getGameLayer()->_isHardCoreGame)
							   {
								   getGameLayer()->setCoin(to_cstr(50 + (hero->getLV() - 1) * 10));
								   thiz->setCoinDisplay(50 + (hero->getLV() - 1) * 10);
								   thiz->addCoin(50 + (hero->getLV() - 1) * 10);
							   }
							   else
							   {
								   getGameLayer()->setCoin("50");
								   thiz->setCoinDisplay(50);
								   thiz->addCoin(50);
							   }
						   }
					   }
				   }
			   }
		   });
		on(Command::setTransport2, [](CharacterBase *thiz)
		   {
			   int tsPosX = thiz->getPositionX();
			   int tsPosY = thiz->getPositionY();

			   if (thiz->_actionState != State::NATTACK && thiz->hasMonsterArrayAny())
			   {
				   for (auto mo : thiz->getMonsterArray())
				   {
					   if (mo->isCharacter("HiraishinMark"))
					   {
						   tsPosX = mo->getPositionX();
						   tsPosY = mo->getPositionY();
						   mo->attack(NAttack);
					   }
				   }
			   }

			   thiz->setPosition(ccp(tsPosX, tsPosY));
			   CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", thiz);

			   getGameLayer()->reorderChild(thiz, -tsPosY);
		   });
	}
};
