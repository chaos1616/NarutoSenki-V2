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
	static inline std::unordered_map<std::string, CommandHandler> cmdMap;

public:
	static inline void on(const char *cmd, CommandHandler handler)
	{
		cmdMap.insert(std::make_pair(cmd, handler));
	}

	static inline void invoke(const char *cmd, CharacterBase *c)
	{
		auto it_find = cmdMap.find(cmd);
		if (it_find != cmdMap.end())
		{
			auto handler = it_find->second;
			handler(c);
		}
		else
		{
			CCLOGERROR("Not found command handler `%s`", cmd);
		}
	}

	static inline void remove(const char *cmd)
	{
		cmdMap.erase(cmd);
	}

	static inline void replaceOrInsert(const char *cmd, CommandHandler handler)
	{
		cmdMap[cmd] = handler;
	}

	static inline void reset()
	{
		cmdMap.clear();
		init();

		if (cmdMap.size() > 0)
			CCLOG("Command System ] [ Count: %u", cmdMap.size());
		else
			CCLOG("Command System ] [ Initial error, not found any command");
	}

private:
	static void init()
	{
		on(Command::addExtern, [](CharacterBase *c)
		   {
			   auto tempArray = CCArray::create();

			   int i = 1;
			   if (c->isCharacter("Tenten"))
			   {
				   while (i < 11)
				   {
					   auto path = CCString::createWithFormat("Tenten_Extern_0%d.png", i);
					   auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path->getCString());
					   tempArray->addObject(frame);
					   i += 1;
				   }
			   }

			   auto tempAnimation = CCAnimation::createWithSpriteFrames(tempArray, 0.1f);
			   auto call = CCCallFuncN::create(c, callfuncN_selector(CharacterBase::disableShadow));
			   auto tempAction = CCAnimate::create(tempAnimation);
			   auto list = CCArray::create();
			   list->addObject(tempAction);
			   list->addObject(call);
			   auto seq = CCSequence::create(list);

			   CCSprite *tempChar = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s_Extern_01.png", c->getCharacter()->getCString())->getCString());

			   tempChar->setAnchorPoint(ccp(0.5f, 0));
			   tempChar->setPosition(c->getPosition());
			   c->_delegate->addChild(tempChar, -c->_originY);

			   tempChar->runAction(seq);
		   });
		on(Command::addHP, [](CharacterBase *c)
		   {
			   if (c->_hpBar)
			   {
				   c->setHPValue(c->getMaxHPValue());
				   c->_hpBar->setPositionY(c->getHeight());
			   }
		   });
		on(Command::findTarget, [](CharacterBase *c)
		   {
			   if (c->notFindHero(0))
			   {
				   if (c->notFindFlog(0) ||
					   c->isCharacter("RikudoNaruto", "SageNaruto"))
					   c->_mainTarget = nullptr;
			   }

			   if (c->_mainTarget)
			   {
				   if (c->isCharacter("Dogs",
									  "Yominuma",
									  "SandBall",
									  "Sabaku",
									  "Yataikuzu",
									  "Lee",
									  "RockLee"))
				   {
					   c->_markPoint = ccp(c->_mainTarget->getPositionX(), c->_mainTarget->_originY ? c->_mainTarget->_originY : c->_mainTarget->getPositionY());
				   }
				   else if (c->isCharacter("Tsukuyomi"))
				   {
					   c->_markPoint = ccp(c->_mainTarget->getPositionX(), c->_mainTarget->_originY ? c->_mainTarget->_originY : c->_mainTarget->getPositionY() + 2);
				   }
				   else if (c->isCharacter("KageFeng"))
				   {
					   c->_markPoint = ccp(c->_mainTarget->getPositionX(), c->_mainTarget->_originY ? c->_mainTarget->_originY - 6 : c->_mainTarget->getPositionY() - 6);
				   }
				   else
				   {
					   c->_markPoint = ccp(c->_mainTarget->_isFlipped ? c->_mainTarget->getPositionX() + 32 : c->_mainTarget->getPositionX() - 32,
										   c->_mainTarget->_originY ? c->_mainTarget->_originY : c->_mainTarget->getPositionY());
				   }
			   }
		   });
		on(Command::pauseJump, [](CharacterBase *c)
		   {
			   // pause jump
			   c->getActionManager()->addAction(c->_jumpUPAction, c, false);
		   });
		on(Command::setDead, [](CharacterBase *c)
		   {
			   c->_isSuicide = true;
			   c->dead();
		   });
		on(Command::setGainCKR, [](CharacterBase *c)
		   {
			   uint32_t boundValue = 1500;
			   c->increaseAllCkrs(boundValue, true, !c->_isControlled);
		   });
		on(Command::setInvincible, [](CharacterBase *c)
		   {
			   // set character invincible
			   c->_isInvincible = true;
		   });
		on(Command::reInvincible, [](CharacterBase *c)
		   {
			   // unset character invincible
			   c->_isInvincible = false;
		   });
		on(Command::setInvisible, [](CharacterBase *c)
		   {
			   c->setVisible(false);
			   c->_isVisable = false;
		   });
		on(Command::reInvisible, [](CharacterBase *c)
		   {
			   c->setVisible(true);
			   c->_isVisable = true;
		   });
		on(Command::setTransport, [](CharacterBase *c)
		   {
			   int tsPosX = c->getPositionX();
			   int tsPosY = c->getPositionY();

			   if (c->_mainTarget)
			   {
				   if (c->_mainTarget->_isFlipped)
				   {
					   c->setFlipX(true);
					   c->_isFlipped = true;
				   }
				   else
				   {
					   c->setFlipX(false);
					   c->_isFlipped = false;
				   }
			   }

			   if (c->isCharacter("Sakura"))
			   {
				   float posY = c->getPositionY();
				   if (!c->_originY)
				   {
					   if (posY == 0)
						   posY = 0.1f;
					   c->_originY = posY;
				   }
				   c->setPosition(ccp(c->getPositionX(), c->getPositionY() + 64));
				   return;
			   }
			   else
			   {
				   if (c->_markPoint.x != 0)
				   {
					   c->_startPoint = ccp(tsPosX, tsPosY);
					   tsPosX = c->_markPoint.x;
					   tsPosY = c->_markPoint.y;
					   c->_markPoint = ccp(0, 0);
				   }
				   else if (c->_startPoint.x != 0)
				   {
					   tsPosX = c->_startPoint.x;
					   tsPosY = c->_startPoint.y;
					   c->_startPoint = ccp(0, 0);
				   }
			   }

			   c->setPosition(ccp(tsPosX, tsPosY));
			   CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", c);

			   if (c->isNotCharacter("Yominuma"))
			   {
				   c->_delegate->reorderChild(c, -tsPosY);
			   }
		   });
		on(Command::reTransport, [](CharacterBase *c)
		   {
			   c->setPosition(ccp(c->getPositionX(), c->_originY));
			   c->_originY = 0;
		   });
		// For special characters
		on(Command::setCounter, [](CharacterBase *c)
		   {
			   bool _isCounter = false;
			   if (c->hasMonsterArrayAny())
			   {
				   CCObject *pObject;
				   CCARRAY_FOREACH(c->getMonsterArray(), pObject)
				   {
					   auto tempMonster = (CharacterBase *)pObject;
					   float distanceX = ccpSub(tempMonster->getPosition(), c->getPosition()).x;
					   float distanceY = ccpSub(tempMonster->getPosition(), c->getPosition()).y;
					   if (abs(distanceX) < 40 && abs(distanceY) < 15)
					   {
						   _isCounter = true;
					   }
				   }
			   }

			   if (_isCounter)
			   {
				   CCObject *pObject;
				   CCARRAY_FOREACH(c->_delegate->_CharacterArray, pObject)
				   {
					   auto tempHero = (Hero *)pObject;
					   if (c->isNotSameGroupAs(tempHero) &&
						   tempHero->isPlayerOrCom() &&
						   tempHero->_actionState != State::DEAD)
					   {
						   if (tempHero->_hpBar)
						   {
							   if (tempHero->getHPValue() <= 2000)
							   {
								   tempHero->setDamage(c, "c_hit", tempHero->getHPValue(), false);
							   }
							   else
							   {
								   tempHero->setDamage(c, "c_hit", 2000, false);
							   }

							   if (tempHero->isPlayer())
							   {
								   c->_delegate->setHPLose(tempHero->getHpPercent());
							   }
						   }
					   }
				   }
			   }
			   else
			   {
				   if (c->_hpBar)
				   {
					   if (c->getHPValue() <= 2000)
					   {
						   c->setDamage(c, "c_hit", c->getHPValue(), false);
					   }
					   else
					   {
						   c->setDamage(c, "c_hit", 2000, false);
					   }

					   if (c->isPlayer())
					   {
						   c->_delegate->setHPLose(c->getHpPercent());
					   }
				   }
			   }

			   c->setActionResume();
		   });
		on(Command::setRevive, [](CharacterBase *c)
		   {
			   CCObject *pObject;
			   CCARRAY_FOREACH(c->_delegate->_CharacterArray, pObject)
			   {
				   auto tempHero = (Hero *)pObject;
				   if (c->isSameGroupAs(tempHero) &&
					   tempHero->isPlayerOrCom() &&
					   tempHero->_actionState == State::DEAD &&
					   tempHero->rebornSprite)
				   {
					   tempHero->unschedule(schedule_selector(Hero::reborn));
					   tempHero->reborn(0.1f);
				   }
			   }
		   });
		on(Command::setTrade, [](CharacterBase *c)
		   {
			   CCObject *pObject;
			   CCARRAY_FOREACH(c->_delegate->_CharacterArray, pObject)
			   {
				   auto tempHero = (Hero *)pObject;
				   if (tempHero->hearts > 0 &&
					   tempHero->_actionState == State::DEAD &&
					   tempHero->rebornSprite &&
					   tempHero->isPlayerOrCom() &&
					   tempHero->isNotCharacter("Kakuzu"))
				   {
					   CCPoint sp = ccpSub(tempHero->getPosition(), c->getPosition());
					   if (abs(sp.x) <= 48 && abs(sp.y) <= 48)
					   {
						   tempHero->hearts -= 1;
						   if (c->isNotSameGroupAs(tempHero))
						   {
							   uint32_t tempMaxHP = c->getMaxHPValue();
							   tempMaxHP += 100;
							   c->setnAttackValue(to_ccstring(c->getNAttackValue() + 5));
							   c->setMaxHPValue(tempMaxHP);
						   }

						   if (c->isPlayer())
						   {
							   if (c->_delegate->_isHardCoreGame)
							   {
								   c->_delegate->setCoin(to_cstr(50 + (tempHero->getLV() - 1) * 10));
								   c->setCoinDisplay(50 + (tempHero->getLV() - 1) * 10);
								   c->addCoin(50 + (tempHero->getLV() - 1) * 10);
							   }
							   else
							   {
								   c->_delegate->setCoin("50");
								   c->setCoinDisplay(50);
								   c->addCoin(50);
							   }
						   }
					   }
				   }
			   }
		   });
		on(Command::setTransport2, [](CharacterBase *c)
		   {
			   CCObject *pObject;
			   int tsPosX = c->getPositionX();
			   int tsPosY = c->getPositionY();

			   if (c->_actionState != State::NATTACK && c->hasMonsterArrayAny())
			   {
				   CCARRAY_FOREACH(c->getMonsterArray(), pObject)
				   {
					   auto mo = (Monster *)pObject;
					   if (mo->isCharacter("HiraishinMark"))
					   {
						   tsPosX = mo->getPositionX();
						   tsPosY = mo->getPositionY();
						   mo->attack(NAttack);
					   }
				   }
			   }

			   c->setPosition(ccp(tsPosX, tsPosY));
			   CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", c);

			   c->_delegate->reorderChild(c, -tsPosY);
		   });
	}
};
