#include "Core/Hero.hpp"
#include "HudLayer.h"

HPBar::HPBar()
{
	hpBar = nullptr;
	hpBottom = nullptr;
}

HPBar::~HPBar()
{
}

bool HPBar::init(const char *szImage)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCSprite::init());

		char fileName[3] = "xx";
		strncpy(fileName, szImage, 2);

		hpBar = CCSprite::createWithSpriteFrameName(szImage);
		hpBar->setAnchorPoint(ccp(0, 0));
		addChild(hpBar, 1);

		if (is_same(fileName, "hp"))
		{
			hpBottom = CCSprite::createWithSpriteFrameName("hp_bottom.png");
			hpBar->setPosition(ccp(15, 1));
		}
		else
		{
			hpBottom = CCSprite::createWithSpriteFrameName("flog_bar_buttom.png");
			hpBar->setPosition(ccp(1, 1));
		}
		hpBottom->setAnchorPoint(ccp(0, 0));
		addChild(hpBottom, -1);

		bRet = true;

	} while (0);

	return bRet;
}

void HPBar::changeBar(const char *szImage)
{
	auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szImage);
	hpBar->setDisplayFrame(frame);
}

void HPBar::loseHP(float percent)
{
	if (_delegate->getDelegate()->_isHardCoreGame)
	{
		const char *gardTower;
		if (_delegate->getDelegate()->team > 0)
		{
			gardTower = "AkatsukiCenter";
		}
		else
		{
			gardTower = "KonohaCenter";
		}

		if (is_same(_delegate->getCharacter()->getCString(), gardTower))
		{
			if (!_delegate->getDelegate()->_isGuardian && percent <= 0.8)
			{
				_delegate->getDelegate()->initGard();
			}
		}

		if (_delegate->getDelegate()->_isGuardian)
		{
			auto _slayer = (CharacterBase *)_delegate->_slayer;
			if (_slayer)
			{
				if (is_same(_delegate->getCharacter()->getCString(), gardTower))
				{
					_slayer->isHurtingTower = true;
				}
				else
				{
					_slayer->isHurtingTower = false;
				}
			}
		}
	}

	if (percent <= 0)
	{
		CharacterBase *_slayer = _delegate->_slayer;
		CharacterBase *currentSlayer;

		if (_delegate->isFlog())
		{
			if (_slayer->getSecMaster() &&
				_slayer->isNotCharacter("KageHand") &&
				_slayer->isNotCharacter("KageHands"))
			{
				if (_slayer->getSecMaster()->getController())
				{
					currentSlayer = _slayer->getSecMaster()->getController();
				}
				else
				{
					currentSlayer = _slayer->getSecMaster();
				}
			}
			else if (_slayer->getMaster())
			{
				if (_slayer->getMaster()->getController())
				{
					currentSlayer = _slayer->getMaster()->getController();
				}
				else
				{
					currentSlayer = _slayer->getMaster();
				}
			}
			else
			{
				if (_slayer->getController())
				{
					currentSlayer = _slayer->getController();
				}
				else
				{
					currentSlayer = _slayer;
				}
			}

			if (currentSlayer->getLV() != 6)
			{
				if (currentSlayer->isCharacter("Naruto") ||
					currentSlayer->isCharacter("SageNaruto"))
				{
					currentSlayer->setEXP(currentSlayer->getEXP() + 12);
					currentSlayer->changeHPbar();
				}
				else
				{
					currentSlayer->setEXP(currentSlayer->getEXP() + 10);
					currentSlayer->changeHPbar();
				}
			}

			if (currentSlayer->isPlayer())
			{
				if (_delegate->getMaxHPValue() == 10000)
				{
					_delegate->setCoinDisplay(30);
					_delegate->getDelegate()->setCoin("30");
					_delegate->getDelegate()->getHudLayer()->setEXPLose(0);
				}
				else if (_delegate->getMaxHPValue() == 5000)
				{
					_delegate->setCoinDisplay(20);
					_delegate->getDelegate()->setCoin("20");
					_delegate->getDelegate()->getHudLayer()->setEXPLose(0);
				}
				else
				{
					_delegate->setCoinDisplay(10);
					_delegate->getDelegate()->setCoin("10");
					_delegate->getDelegate()->getHudLayer()->setEXPLose(0);
				}
			}

			currentSlayer->_flogNum += 1;
			if (_delegate->getMaxHPValue() == 10000)
			{
				currentSlayer->addCoin(30);
			}
			else if (_delegate->getMaxHPValue() == 5000)
			{
				currentSlayer->addCoin(20);
			}
			else
			{
				currentSlayer->addCoin(10);
			}
		}
		else if (_delegate->isTower())
		{
			if (_slayer->getSecMaster() &&
				_slayer->isNotCharacter("KageHand",
										"KageHands",
										"SmallSlug"))
			{
				if (_slayer->getSecMaster()->getController())
				{
					currentSlayer = _slayer->getSecMaster()->getController();
				}
				else
				{
					currentSlayer = _slayer->getSecMaster();
				}
			}
			else if (_slayer->getMaster())
			{
				if (_slayer->getMaster()->getController())
				{
					currentSlayer = _slayer->getMaster()->getController();
				}
				else
				{
					currentSlayer = _slayer->getMaster();
				}
			}
			else
			{
				if (_slayer->getController())
				{
					currentSlayer = _slayer->getController();
				}
				else
				{
					currentSlayer = _slayer;
				}
			}

			if ((currentSlayer->isNotFlog()))
			{
				_delegate->getDelegate()->setReport(currentSlayer->getCharacter()->getCString(), kRoleTower, currentSlayer->getKillNum());

				if (currentSlayer->getLV() != 6)
				{
					if (currentSlayer->isCharacter("Naruto") ||
						currentSlayer->isCharacter("SageNaruto"))
					{
						currentSlayer->setEXP(currentSlayer->getEXP() + 625);
						currentSlayer->changeHPbar();
					}
					else
					{
						currentSlayer->setEXP(currentSlayer->getEXP() + 500);
						currentSlayer->changeHPbar();
					}
				}

				if (currentSlayer->isPlayer())
				{
					if (_delegate->getDelegate()->_isHardCoreGame)
					{
						if (_delegate->getMaxHPValue() > 40000)
						{
							_delegate->getDelegate()->setCoin("1000");
							_delegate->setCoinDisplay(1000);
						}
						else
						{
							_delegate->getDelegate()->setCoin("500");
							_delegate->setCoinDisplay(500);
						}
					}
					else
					{
						_delegate->getDelegate()->setCoin("300");
						_delegate->setCoinDisplay(300);
					}

					_delegate->getDelegate()->getHudLayer()->setEXPLose(0);
				}

				if (_delegate->getDelegate()->_isHardCoreGame)
				{
					if (_delegate->getMaxHPValue() > 40000)
					{
						currentSlayer->addCoin(1000);
					}
					else
					{
						currentSlayer->addCoin(500);
					}
				}
				else
				{
					currentSlayer->addCoin(300);
				}
			}

			CCObject *pObject;
			CCARRAY_FOREACH(_delegate->getDelegate()->_CharacterArray, pObject)
			{
				auto otherSlayer = (Hero *)pObject;
				if (is_same(currentSlayer->getGroup()->getCString(), otherSlayer->getGroup()->getCString()) &&
					strcmp(currentSlayer->getCharacter()->getCString(), otherSlayer->getCharacter()->getCString()) != 0)
				{
					if (otherSlayer->getLV() != 6)
					{
						otherSlayer->setEXP(otherSlayer->getEXP() + 250);
						otherSlayer->changeHPbar();
					}

					if (otherSlayer->isPlayer())
					{
						if (_delegate->getDelegate()->_isHardCoreGame)
						{
							if (_delegate->getMaxHPValue() > 40000)
							{
								_delegate->getDelegate()->setCoin("850");
								_delegate->setCoinDisplay(850);
							}
							else
							{
								_delegate->getDelegate()->setCoin("350");
								_delegate->setCoinDisplay(350);
							}
						}
						else
						{
							_delegate->getDelegate()->setCoin("150");
							_delegate->setCoinDisplay(150);
						}

						_delegate->getDelegate()->getHudLayer()->setEXPLose(0);
					}

					if (_delegate->getDelegate()->_isHardCoreGame)
					{
						if (_delegate->getMaxHPValue() > 40000)
						{
							otherSlayer->addCoin(850);
						}
						else
						{
							otherSlayer->addCoin(350);
						}
					}
					else
					{
						otherSlayer->addCoin(150);
					}
				}
			}
		}
		else if (_delegate->isPlayerOrCom())
		{
			if (_delegate->isCharacter("Kakuzu") && _delegate->getDelegate()->_isOugis2Game)
			{
				bool reieveAble = false;
				if (_delegate->getCkr2Value() >= 25000 && _delegate->hearts > 0)
				{
					if (_delegate->isPlayer())
					{
						reieveAble = true;
					}
					else if (_delegate->isCom())
					{
						reieveAble = true;
					}
				}

				if (reieveAble && _delegate->getActionState() != State::O2ATTACK && !_delegate->_isInvincible && _delegate->getActionState() != State::DEAD)
				{
					if (_delegate->_isSticking)
					{
						_delegate->_isSticking = false;
					}
					if (_delegate->getActionState() == State::FLOAT ||
						_delegate->getActionState() == State::AIRHURT)
					{
						setPositionY(_delegate->_originY);
						_delegate->_originY = 0;
						_delegate->getDelegate()->reorderChild(_delegate, -_delegate->getPositionY());
					}

					if (_delegate->isPlayer())
					{
						_delegate->getDelegate()->getHudLayer()->skill5Button->unLock();
						_delegate->setActionState(State::IDLE);
						_delegate->getDelegate()->setSkillFinish(true);
						_delegate->getDelegate()->getHudLayer()->skill5Button->click();
						_delegate->getDelegate()->getHudLayer()->skill5Button->setLock();
					}
					else
					{
						if (_delegate->_isCanOugis2)
						{
							_delegate->setActionState(State::IDLE);
							_delegate->attack(OUGIS2);
						}
					}
					_delegate->hearts -= 1;

					if (_delegate->_heartEffect)
					{
						auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Heart_Effect_%02d.png", _delegate->hearts)->getCString());
						_delegate->_heartEffect->setDisplayFrame(frame);
					}

					if (_delegate->hearts < 1)
					{
						if (_delegate->isPlayer())
						{
							_delegate->getDelegate()->getHudLayer()->skill4Button->setLock();
						}
					}

					return;
				}

				if (_delegate->getActionState() == State::O2ATTACK)
				{
					return;
				}
			}

			if (_delegate->_isControlled)
			{
				_delegate->_isSuicide = true;
				currentSlayer = _delegate->getController();
			}
			else if (_slayer->getSecMaster() &&
					 _slayer->isNotCharacter("KageHand",
											 "KageHands",
											 "SmallSlug",
											 "FakeItachi"))
			{
				if (_slayer->getSecMaster()->getController())
				{
					currentSlayer = _slayer->getSecMaster()->getController();
				}
				else
				{
					currentSlayer = _slayer->getSecMaster();
				}
			}
			else if (_slayer->getMaster())
			{
				if (_slayer->getMaster()->getController())
				{
					currentSlayer = _slayer->getMaster()->getController();
				}
				else
				{
					currentSlayer = _slayer->getMaster();
				}
			}
			else
			{
				if (_slayer->getController())
				{
					currentSlayer = _slayer->getController();
				}
				else
				{
					currentSlayer = _slayer;
				}
			}

			if (currentSlayer->isCharacter("Kakuzu"))
			{
				if (currentSlayer->hearts <= 4)
				{
					currentSlayer->hearts += 1;

					if (currentSlayer->_heartEffect)
					{
						auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Heart_Effect_%02d.png", currentSlayer->hearts)->getCString());
						currentSlayer->_heartEffect->setDisplayFrame(frame);
					}

					if (currentSlayer->isPlayer())
					{
						if (currentSlayer->getMonsterArray() && currentSlayer->getMonsterArray()->count() < 3 && currentSlayer->getLV() >= 2)
						{
							_delegate->getDelegate()->getHudLayer()->skill4Button->unLock();
						}
					}
				}
			}

			if (currentSlayer->isNotFlog())
			{
				int realKillNum = to_int(currentSlayer->getKillNum()->getCString()) + 1;
				currentSlayer->setKillNum(to_ccstring(realKillNum));
				_delegate->getDelegate()->setReport(currentSlayer->getCharacter()->getCString(), _delegate->getCharacter()->getCString(), currentSlayer->getKillNum());

				const char *currentTeam;
				if (_delegate->getDelegate()->team > 0)
				{
					currentTeam = Konoha;
				}
				else
				{
					currentTeam = Akatsuki;
				}

				if (is_same(currentSlayer->getGroup()->getCString(), currentTeam))
				{
					int teamKills = to_int(_delegate->getDelegate()->getHudLayer()->KonoLabel->getString()) + 1;
					_delegate->getDelegate()->getHudLayer()->KonoLabel->setString(to_cstr(teamKills));
				}
				else
				{
					int teamKills = to_int(_delegate->getDelegate()->getHudLayer()->AkaLabel->getString()) + 1;
					_delegate->getDelegate()->getHudLayer()->AkaLabel->setString(to_cstr(teamKills));
				}
				if (currentSlayer->isNotGuardian())
				{
					int newValue = to_int(_delegate->getDelegate()->getTotalKills()->getCString()) + 1;
					_delegate->getDelegate()->setTotalKills(to_ccstring(newValue));
				}

				if (currentSlayer->getLV() != 6)
				{
					if (currentSlayer->isCharacter("Naruto") ||
						currentSlayer->isCharacter("SageNaruto"))
					{
						currentSlayer->setEXP(currentSlayer->getEXP() + 125);
						currentSlayer->changeHPbar();
					}
					else
					{
						currentSlayer->setEXP(currentSlayer->getEXP() + 100);
						currentSlayer->changeHPbar();
					}
				}

				if (currentSlayer->isPlayer())
				{
					if (_delegate->isGuardian())
					{
						_delegate->getDelegate()->setCoin("1000");
						_delegate->setCoinDisplay(1000);
					}
					else
					{
						if (_delegate->getDelegate()->_isHardCoreGame)
						{
							_delegate->getDelegate()->setCoin(to_cstr(50 + (_delegate->getLV() - 1) * 10));
							_delegate->setCoinDisplay(50 + (_delegate->getLV() - 1) * 10);
						}
						else
						{
							_delegate->getDelegate()->setCoin(to_cstr(50));
							_delegate->setCoinDisplay(50);
						}
					}

					_delegate->getDelegate()->getHudLayer()->setEXPLose(0);
					const char *kl = _delegate->getDelegate()->getHudLayer()->killLabel->getString();
					int kills = to_int(kl) + 1;
					_delegate->getDelegate()->getHudLayer()->killLabel->setString(to_cstr(kills));
				}

				if (_delegate->isGuardian())
				{
					currentSlayer->addCoin(1000);
				}
				else
				{
					if (_delegate->getDelegate()->_isHardCoreGame)
					{
						currentSlayer->addCoin(50 + (_delegate->getLV() - 1) * 10);
					}
					else
					{
						currentSlayer->addCoin(50);
					}
				}
			}

			CCObject *pObject;
			CCARRAY_FOREACH(_delegate->getDelegate()->_CharacterArray, pObject)
			{
				auto otherSlayer = (Hero *)pObject;
				if (is_same(currentSlayer->getGroup()->getCString(), otherSlayer->getGroup()->getCString()) &&
					strcmp(currentSlayer->getCharacter()->getCString(), otherSlayer->getCharacter()->getCString()) != 0)
				{
					if (otherSlayer->getLV() != 6)
					{
						otherSlayer->setEXP(otherSlayer->getEXP() + 25);
						otherSlayer->changeHPbar();
					}

					if (otherSlayer->isPlayer())
					{
						if (_delegate->getDelegate()->_isHardCoreGame)
						{
							if (_delegate->isGuardian())
							{
								_delegate->getDelegate()->setCoin(to_cstr(850));
								_delegate->setCoinDisplay(850);
							}
							else
							{
								_delegate->getDelegate()->setCoin(to_cstr(25 + (_delegate->getLV() - 1) * 10));
								_delegate->setCoinDisplay(25 + (_delegate->getLV() - 1) * 10);
							}
						}
						else
						{
							_delegate->getDelegate()->setCoin(to_cstr(25));
							_delegate->setCoinDisplay(25);
						}
						_delegate->getDelegate()->getHudLayer()->setEXPLose(0);
					}
					if (_delegate->getDelegate()->_isHardCoreGame)
					{
						if (_delegate->isGuardian())
						{
							otherSlayer->addCoin(850);
						}
						else
						{
							otherSlayer->addCoin(25 + (_delegate->getLV() - 1) * 10);
						}
					}
					else
					{
						otherSlayer->addCoin(25);
					}
				}
			}
		}

		_delegate->dead();
	}
	else
	{
		auto s = CCScaleTo::create(0.2f, percent, 1);
		hpBar->runAction(s);
		if (_delegate->isPlayer())
		{
			_delegate->getDelegate()->setHPLose(percent);
		}
	}
}

HPBar *HPBar::create(const char *szImage)
{
	HPBar *hb = new HPBar();
	if (hb && hb->init(szImage))
	{
		hb->autorelease();
		return hb;
	}
	else
	{
		delete hb;
		return nullptr;
	}
}
