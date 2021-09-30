#include "CharacterBase.h"
#include "HudLayer.h"
#include "Core/Provider.hpp"
#include "GameMode/GameModeImpl.h"
#include "MyUtils/CCShake.h"

CharacterBase::CharacterBase()
{
	_actionState = State::WALK;

	_idleAction = nullptr;
	_nattackAction = nullptr;
	_walkAction = nullptr;
	_hurtAction = nullptr;
	_airHurtAction = nullptr;
	_knockDownAction = nullptr;
	_floatAction = nullptr;
	_deadAction = nullptr;
	_skill1Action = nullptr;
	_skill2Action = nullptr;
	_skill3Action = nullptr;
	_skill4Action = nullptr;
	_skill5Action = nullptr;

	gearCKRValue = 0;
	gearRecoverValue = 0;
	isAttackGainCKR = false;
	isGearCD = false;
	hasArmorBroken = false;
	hasArmor = false;
	battleCondiction = 0;
	hearts = 0;
	isHurtingTower = false;
	damageEffectCount = 0;

	_isSuicide = false;

	_charNO = 0;
	_backY = 0;
	_diretionY = 0;

	_isAllAttackLocked = false;
	_isOnlySkillLocked = false;
	_sattack1isDouble = false;
	_sattack2isDouble = false;
	_sattack3isDouble = false;
	_sattack4isDouble = false;

	_moveAction = nullptr;
	_jumpUPAction = nullptr;
	_floatUPAction = nullptr;

	_hurtFromLeft = false;
	_hurtFromRight = false;
	_isFlipped = false;
	_isHitOne = false;
	_isCatchOne = false;
	_isHealling = false;
	_isVisable = true;
	_isSticking = false;
	_isControlled = false;

	_isCanSkill1 = true;
	_isCanSkill2 = true;
	_isCanSkill3 = true;
	_isCanItem1 = true;
	_isCanOugis1 = false;
	_isCanOugis2 = false;

	_isCanGear00 = false;
	_isCanGear03 = false;
	_isCanGear06 = false;

	enemyCombatPoint = 0;
	//totalCombatPoint=0;
	friendCombatPoint = 0;

	isBaseDanger = false;

	_sattackCombatPoint1 = 0;
	_sattackCombatPoint2 = 0;
	_sattackCombatPoint3 = 0;
	_sattackCombatPoint4 = 0;
	_sattackCombatPoint5 = 0;

	_role = nullptr;
	_group = nullptr;
	_character = nullptr;
	_killNum = nullptr;
	_coin = nullptr;

	_master = nullptr;
	_controller = nullptr;
	_secmaster = nullptr;
	_slayer = nullptr;
	_sticker = nullptr;

	_mainTarget = nullptr;

	_deadNum = 0;
	_flogNum = 0;

	_knockLength = 0;
	_knockDirection = false;

	_effectType = nullptr;

	_damageArray = nullptr;
	_monsterArray = nullptr;

	_originY = 0;

	_nattackValue = nullptr;
	_sattackValue1 = nullptr;
	_sattackValue2 = nullptr;
	_sattackValue3 = nullptr;
	_sattackValue4 = nullptr;
	_sattackValue5 = nullptr;
	_spcattackValue1 = nullptr;
	_spcattackValue2 = nullptr;
	_spcattackValue3 = nullptr;
	_tempAttackValue1 = nullptr;

	_healBuffEffect = nullptr;
	_powerBuffEffect = nullptr;
	_skillBuffEffect = nullptr;
	_healItemEffect = nullptr;
	_speedItemEffect = nullptr;
	_dehealBuffEffect = nullptr;

	_buffStartTime = 0;
	_debuffStartTime = 0;
	_heartEffect = nullptr;

	_shadow = nullptr;

	_healBuffValue = 0;
	_skillUPBuffValue = 0;
	_skillChangeBuffValue = 0;
	_dehealBuffValue = 0;
	_powerUPBuffValue = 0;
	_hpBar = nullptr;
	_maxHP = nullptr;
	_hp = nullptr;
	_ckr = nullptr;
	_ckr2 = nullptr;

	_gardValue = 0;
	_exp = 0;
	_level = 1;

	_isInvincible = false;
	_isTaunt = false;
	_isArmored = false;

	_rebornTime = 5;

	_markPoint = ccp(0, 0);
	_startPoint = ccp(0, 0);

	rebornLabelTime = 0;

	_isAI = false;

	cpLabel = nullptr;

	_gearArray = nullptr;

	_affectedByTower = false;
}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::setID(CCString *character, CCString *role, CCString *group)
{
}

void CharacterBase::setHPbar()
{
}

void CharacterBase::setShadows()
{
}

void CharacterBase::changeHPbar()
{
}

void CharacterBase::updateDataByLVOnly()
{
	uint32_t tempMaxHP = getMaxHPValue();
	int attackValue = getNAttackValue();
	if (_level >= 2)
	{
		_isCanOugis1 = true;
		if (isPlayer())
		{
			getDelegate()->setCKRLose(false);
			getDelegate()->removeOugisMark(1);
		}
		tempMaxHP += 500;
		attackValue += 9;
		_rebornTime += 1;
	}
	if (_level >= 3)
	{
		tempMaxHP += 1000;
		attackValue += 18;
		_rebornTime += 2;
	}
	if (_level >= 4)
	{
		_isCanOugis2 = true;
		if (isPlayer())
		{
			getDelegate()->setCKRLose(true);
			getDelegate()->removeOugisMark(2);
		}
		tempMaxHP += 2000;
		attackValue += 27;
		_rebornTime += 3;
	}
	if (_level >= 5)
	{
		tempMaxHP += 2500;
		attackValue += 36;
		_rebornTime += 4;
	}
	if (_level >= 6)
	{
		tempMaxHP += 3000;
		attackValue += 45;
		_rebornTime += 5;
	}
	setMaxHP(to_ccstring(tempMaxHP));
	setnAttackValue(to_ccstring(attackValue));
}

void CharacterBase::readData(CCArray *tmpData, CCString *&attackType, CCString *&attackValue, int &attackRangeX, int &attackRangeY, uint32_t &coldDown, int &combatPoint)
{
	CCDictionary *tmpDict;

	for (uint32_t i = 0; i < tmpData->count(); ++i)
	{
		tmpDict = (CCDictionary *)(tmpData->objectAtIndex(i));
		switch (i)
		{
		case 0:
			attackType = CCString::create(tmpDict->valueForKey("attackType")->getCString());
			break;
		case 1:
			attackValue = CCString::create(tmpDict->valueForKey("attackValue")->getCString());
			break;
		case 2:
			attackRangeX = tmpDict->valueForKey("attackRangeX")->intValue();
			break;
		case 3:
			attackRangeY = tmpDict->valueForKey("attackRangeY")->intValue();
			break;
		case 4:
			coldDown = tmpDict->valueForKey("coldDown")->uintValue();
		case 5:
			combatPoint = tmpDict->valueForKey("combatPoint")->intValue();
		}
	}
}

void CharacterBase::onEnter()
{
	CCSprite::onEnter();
}

void CharacterBase::onExit()
{
	CCSprite::onExit();
}

void CharacterBase::update(float dt)
{
	if (_healBuffEffect)
	{
		_healBuffEffect->setPositionX(getContentSize().width / 2 + (_isFlipped ? 2 : -2));
	}
	if (_powerBuffEffect)
	{
		_powerBuffEffect->setPositionX(getContentSize().width / 2 + (_isFlipped ? 2 : -2));
	}
	if (_skillBuffEffect)
	{
		_skillBuffEffect->setPositionX(getContentSize().width / 2);
	}

	if (_heartEffect)
	{
		_heartEffect->setPositionX(getContentSize().width / 2 + (_isFlipped ? 22 : -22));
	}

	if (_healItemEffect)
	{
		_healItemEffect->setPosition(ccp(_isFlipped ? getContentSize().width / 2 + 16 : getContentSize().width / 2 - 16,
										 _height));
	}

	if (_speedItemEffect)
	{
		_speedItemEffect->setPosition(ccp(_isFlipped ? getContentSize().width / 2 + 16 : getContentSize().width / 2 - 16,
										  _height));
	}

	/*if(_kaguraEffect){
		_kaguraEffect->setPosition(ccp(getPositionX(),getPositionY()+getContentSize().height/2));
	}*/

	if (_dehealBuffEffect)
	{
		_dehealBuffEffect->setPositionX(getContentSize().width / 2);
	}

	if (_shadow)
	{
		_shadow->setPosition(ccp(getPositionX(), _originY ? _originY : getPositionY()));
	}

	if (!_isControlled && _actionState != State::DEAD)
	{
		if (isPlayer() || isCom())
		{
			if (isNotGuardian())
			{
				if (isKonohaGroup() && getPositionX() <= 11 * 32)
				{
					_isHealling = true;
					if (getHpPercent() < 1.0f)
					{
						scheduleOnce(schedule_selector(CharacterBase::setRestore), 1.0f);
					}
				}
				else if (isAkatsukiGroup() && getPositionX() >= 85 * 32)
				{
					_isHealling = true;
					if (getHpPercent() < 1.0f)
					{
						scheduleOnce(schedule_selector(CharacterBase::setRestore), 1.0f);
					}
				}
				else
				{
					_isHealling = false;
				}
			}
		}
	}

	if (_actionState == State::WALK)
	{
		_desiredPosition = ccpAdd(getPosition(), ccpMult(_velocity, dt));

		if (isPlayer() && !_isAI && !_isInvincible && !_isArmored)
		{
			//save the stop Area
			CCObject *pObject;
			CCARRAY_FOREACH(_delegate->_TowerArray, pObject)
			{
				Tower *tower = (Tower *)pObject;
				if (tower)
				{
					int metaWidth = 96;
					int metaHeight = 128;
					int metaX = tower->getPositionX() - metaWidth / 2;
					int metaY = tower->getPositionY() - metaHeight / 2;
					CCRect rect = CCRectMake(metaX, metaY + 32, metaWidth, metaHeight - 64);

					if (rect.containsPoint(_desiredPosition))
					{
						_affectedByTower = true;

						float anchorYpoint = metaY + metaHeight / 2;
						if (getPositionY() > anchorYpoint)
						{
							_velocity = ccp(0, 1 * _walkSpeed * winSize.width / 1280);
						}
						else
						{
							_velocity = ccp(0, -1 * _walkSpeed * winSize.width / 1280);
						}
						_desiredPosition = ccpAdd(getPosition(), ccpMult(_velocity, dt));
					}
				}
			}

			if (_affectedByTower && checkHasMovement())
			{
				_affectedByTower = false;
			}
		}

		float posX = MIN(_delegate->currentMap->getMapSize().width * _delegate->currentMap->getTileSize().width,
						 MAX(0, _desiredPosition.x));

		// map height		: 10
		// backgroud height	: 4.5
		// floor height		: 5.5
		float poxY = MIN(_delegate->currentMap->getTileSize().height * 5.5, MAX(0, _desiredPosition.y));

		setPosition(ccp(posX, poxY));
		_delegate->reorderChild(this, -getPositionY());
		if (isPlayer() || isCom())
		{
			CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", this);
		}
	}

	if (_hpBar)
	{
		_hpBar->setPositionX(getContentSize().width / 2 - _hpBar->getHPBottom()->getContentSize().width / 2);
	}
}

void CharacterBase::updateHpBarPosition(float dt)
{
	if (_hpBar)
	{
		_hpBar->setPositionX(getContentSize().width / 2 - _hpBar->getHPBottom()->getContentSize().width / 2);
		_hpBar->setPositionY(getHeight());
	}
}

void CharacterBase::acceptAttack(CCObject *object)
{
	auto attacker = (CharacterBase *)object;
	bool isCannotMiss = false;

	if (isCharacter("Tobi"))
	{
		if (_skillChangeBuffValue && (getActionState() == State::IDLE ||
									  getActionState() == State::WALK ||
									  getActionState() == State::NATTACK))
		{
			if (getOpacity() == 255)
			{
				scheduleOnce(schedule_selector(CharacterBase::disableBuff), 0.2f);
			}
			setOpacity(150);
			return;
		}
	}

	if (attacker->isCharacter("Hiruzen") && attacker->getActionState() == State::O2ATTACK)
	{
		isCannotMiss = true;
	}

	if (strcmp(_group->getCString(), attacker->_group->getCString()) != 0 && _isVisable && (!_isInvincible || isCannotMiss) && getActionState() != State::DEAD)
	{
		// Tower
		if (isTower())
		{
			bool isHit = false;
			if (is_same(attacker->_attackType->getCString(), "nAttack") &&
				!is_same(attacker->_effectType, "f_hit") &&
				!is_same(attacker->_effectType, "c_hit") &&
				!is_same(attacker->_effectType, "o_hit") &&
				!is_same(attacker->_effectType, "b_hit") &&
				!is_same(attacker->_effectType, "bc_hit"))
			{
				if (setHitBox().intersectsRect(attacker->setHalfBox()))
				{
					isHit = true;
				}
			}
			else if (is_same(attacker->_effectType, "n_hit"))
			{
				bool isHitX = false;
				float distanceX = ccpSub(attacker->getPosition(), getPosition()).x;

				float tempRange1 = attacker->_attackRangeX + attacker->getContentSize().width / 2 + getContentSize().width / 2;

				if (!attacker->_isFlipped && distanceX < 0 && -distanceX < tempRange1)
				{
					_hurtFromLeft = true;
					isHitX = true;
				}
				else if (attacker->_isFlipped && distanceX > 0 && distanceX < tempRange1)
				{
					_hurtFromRight = true;
					isHitX = true;
				}

				if (isHitX)
				{
					if (abs(getPositionY() - attacker->getPositionY()) <= attacker->_attackRangeY)
					{
						isHit = true;
					}
				}
			}

			if (isHit)
			{
				_slayer = attacker;
				setDamage(attacker->_effectType, attacker->_attackValue, attacker->_isFlipped);
				if (_hpBar)
				{
					_hpBar->loseHP(getHpPercent());
				}

				if (!_isHitOne)
				{
					_isHitOne = true;
					auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::disableShack));
					auto delay = CCDelayTime::create(0.5f);
					auto list = CCArray::create();
					list->addObject(CCShake::createWithStrength(0.1f, 2, 0));
					list->addObject(delay);
					list->addObject(call);
					runAction(CCSequence::create(list));
				}
			}

			return;
		}
		// Bullet
		else if (attacker->isBullet())
		{
			if (setHitBox().intersectsRect(attacker->setHitBox()))
			{
				if (isCharacter("Hidan") && _skillChangeBuffValue)
				{
					bool _isCounter = false;
					if (hasMonsterArrayAny())
					{
						CCObject *pObject;
						CCARRAY_FOREACH(_monsterArray, pObject)
						{
							auto tempMonster = (CharacterBase *)pObject;
							float distanceX = ccpSub(tempMonster->getPosition(), getPosition()).x;
							float distanceY = ccpSub(tempMonster->getPosition(), getPosition()).y;
							if (abs(distanceX) < 40 && abs(distanceY) < 15)
							{
								_isCounter = true;
							}
						}
					}

					if (_isCounter)
					{
						if (attacker->_master && attacker->_master->_actionState != State::DEAD)
						{
							attacker->_master->_slayer = this;

							attacker->_master->setDamage(attacker->_effectType, attacker->_attackValue, attacker->_isFlipped);
							if (attacker->_master->_hpBar)
							{
								attacker->_master->_hpBar->loseHP(attacker->_master->getHpPercent());
							}
						}

						CCObject *pObject;
						CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
						{
							auto tempHero = (Hero *)pObject;
							if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0 && (tempHero->isPlayer() || tempHero->isCom()) && tempHero->_actionState != State::DEAD)
							{
								tempHero->_slayer = this;
								tempHero->setDamage(attacker->_effectType, attacker->_attackValue / 2, attacker->_isFlipped);
								if (tempHero->_hpBar)
								{
									tempHero->_hpBar->loseHP(tempHero->getHpPercent());
								}
							}
						}

						return;
					}
				}

				_slayer = attacker;
				setDamage(attacker->_effectType, attacker->_attackValue, attacker->_isFlipped);
				if (_hpBar)
				{
					_hpBar->loseHP(getHpPercent());
				}
				if (attacker->isCharacter("HiraishinKunai") ||
					attacker->isCharacter("Shintenshin"))
				{
					if (isPlayerOrCom() && isNotGuardian() && _actionState != State::DEAD)
					{
						attacker->stopAllActions();
						attacker->dealloc();

						if (attacker->isCharacter("Shintenshin") && !attacker->_isCatchOne)
						{
							attacker->_isCatchOne = true;
							if (attacker->_master)
							{
								_isControlled = true;
								_controller = attacker->_master;

								if (attacker->_master->getActionState() == State::O2ATTACK)
								{
									attacker->_master->stopAllActions();
									attacker->_master->runAction(createAnimation(attacker->_master->skillSPC1Array, 10.0f, false, false));
									attacker->_master->scheduleOnce(schedule_selector(CharacterBase::resumeAction), 15);
									attacker->_master->_isArmored = true;
									attacker->_master->_isInvincible = false;
								}

								if (_controller->isPlayer())
								{
									unschedule(schedule_selector(CharacterBase::setAI));
									_isAI = false;
									// Set controlled character to player
									_delegate->currentPlayer = this;
									_delegate->getHudLayer()->updateSkillButtons();
									idle();

									_delegate->controlChar = this;
								}

								if (isPlayer())
								{
									doAI();
									_delegate->getHudLayer()->_isAllButtonLocked = true;
								}
								changeGroup();
							}
						}
					}
				}
			}

			return;
		}
		else
		{
			bool isHitX = false;

			float distanceX = ccpSub(attacker->getPosition(), getPosition()).x;

			float tempRange1 = attacker->_attackRangeX + attacker->getContentSize().width / 2 + getContentSize().width / 2;

			if (is_same(attacker->_attackType->getCString(), "aAttack"))
			{
				if (abs(distanceX) <= tempRange1)
				{
					isHitX = true;
				}
			}
			else
			{
				if (!attacker->_isFlipped && distanceX < 0 && -distanceX < tempRange1)
				{
					_hurtFromLeft = true;
					isHitX = true;
				}
				else if (attacker->_isFlipped && distanceX > 0 && distanceX < tempRange1)
				{
					_hurtFromRight = true;
					isHitX = true;
				}
			}

			if (isHitX)
			{
				float attackerPosY;
				float currentPosY;
				if (attacker->_actionState == State::JUMP)
					attackerPosY = attacker->_originY;
				else
					attackerPosY = attacker->getPositionY();

				if (_actionState == State::FLOAT || _actionState == State::JUMP || _actionState == State::AIRHURT)
					currentPosY = _originY;
				else
					currentPosY = getPositionY();

				if (abs(currentPosY - attackerPosY) <= attacker->_attackRangeY)
				{
					const char *hitType = attacker->_effectType;

					//hit or not !
					attacker->_isHitOne = true;

					//record the slayer
					_slayer = attacker;

					//flog hurt
					if (isFlog())
					{
						if (is_same(hitType, "o_hit"))
						{
							setKnockLength(48);
							setKnockDirection(attacker->_isFlipped);
							hurt();
						}
						else if (is_same(hitType, "ac_hit"))
						{
							airHurt();
						}
						else if (is_same(hitType, "f_hit") || is_same(hitType, "bf_hit"))
						{
							autoFlip(attacker);
							floatUP(64, true);
						}
						else if (is_same(hitType, "f2_hit"))
						{
							autoFlip(attacker);
							floatUP(128, true);
						}
						else if (is_same(hitType, "b_hit"))
						{
							autoFlip(attacker);
							floatUP(16, false);
						}
						else if (is_same(hitType, "ab_hit"))
						{
							absorb(attacker->getPosition(), true);
						}
						else if (is_same(hitType, "s_hit"))
						{
							absorb(attacker->getPosition(), false);
						}
					}
					// hero hurt
					else if (isPlayer() || isCom() || isClone())
					{
						if (is_same(hitType, "l_hit"))
						{
							if (!_isArmored)
							{
								setKnockLength(32);
							}
							hurt();
						}
						else if (is_same(hitType, "c_hit") ||
								 is_same(hitType, "bc_hit"))
						{
							if (!_isArmored)
							{
								setKnockLength(1);
							}

							if (attacker->isCharacter("Kakuzu") && _sticker)
							{
								CharacterBase *stHero = _sticker;
								if (stHero->isCharacter("Kakuzu") && stHero->hearts <= 4)
								{
									attacker->hearts += 1;

									if (attacker->_heartEffect)
									{
										auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Heart_Effect_%02d.png", attacker->hearts)->getCString());
										attacker->_heartEffect->setDisplayFrame(frame);
									}
								}

								if (attacker->isPlayer() && attacker->hearts > 0)
								{
									CCObject *pObject;
									int countMON = 0;
									CCARRAY_FOREACH(attacker->getMonsterArray(), pObject)
									{
										auto mo = (Monster *)pObject;
										if (mo->isNotCharacter("Traps"))
										{
											countMON++;
										}
									}
									if (countMON < 3 && attacker->getLV() >= 2)
									{
										_delegate->getHudLayer()->skill4Button->unLock();
									}
								}
							}
							hurt();
						}
						else if (is_same(hitType, "ts_hit"))
						{
							if (!_isArmored)
							{
								setKnockLength(1);
							}
							if (hurt() &&
								(!attacker->_isCatchOne || attacker->isCharacter("FakeMinato")))
							{
								attacker->_isCatchOne = true;
								if (attacker->getMaster())
								{
									if (attacker->isCharacter("FakeMinato"))
									{
										setPosition(ccp(attacker->getMaster()->_isFlipped ? attacker->getMaster()->getPositionX() - 64 : attacker->getMaster()->getPositionX() + 64,
														attacker->getMaster()->getPositionY() + 2));
									}
									else
									{
										setPosition(ccp(attacker->getMaster()->_isFlipped ? attacker->getMaster()->getPositionX() - 48 : attacker->getMaster()->getPositionX() + 48,
														attacker->getMaster()->getPositionY()));
									}

									CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", this);
									_delegate->reorderChild(this, -getPositionY());
								}
							}
						}
						else if (is_same(hitType, "sl_hit"))
						{
							if (!_isArmored)
							{
								setKnockLength(1);
							}
							hurt();
							if (getWalkSpeed() == 224)
							{
								setWalkSpeed(112);
								schedule(schedule_selector(CharacterBase::disableDebuff), 3);
							}
						}
						else if (is_same(hitType, "ac_hit"))
						{
							if (_actionState == State::FLOAT || _actionState == State::AIRHURT)
							{
								airHurt();
							}
							else
							{
								if (!_isArmored)
								{
									setKnockLength(1);
								}
								hurt();
							}
						}
						else if (is_same(hitType, "o_hit"))
						{
							if (_actionState != State::OATTACK ||
								(_actionState == State::OATTACK &&
								 (attacker->_actionState == State::O2ATTACK ||
								  attacker->_actionState == State::OATTACK)))
							{
								if (!_isArmored)
								{
									setKnockLength(48);
								}
								setKnockDirection(attacker->_isFlipped);
								hardHurt(500, true, false, false, false);
							}
						}
						else if (is_same(hitType, "o2_hit"))
						{
							if (!_isArmored)
							{
								setKnockLength(1);
							}
							setKnockDirection(attacker->_isFlipped);
							hardHurt(1000, true, false, false, true);
						}
						else if (is_same(hitType, "ob_hit"))
						{
							if (!_isArmored)
							{
								setKnockLength(1);
							}
							setKnockDirection(attacker->_isFlipped);
							hardHurt(2000, true, false, false, true);

							if (_dehealBuffEffect)
							{
								_dehealBuffValue += 1000;
							}
							else
							{
								_dehealBuffValue = 1000;
								setBuffEffect("dhBuff");
								schedule(schedule_selector(CharacterBase::dehealBuff), 1);
							}
							scheduleOnce(schedule_selector(CharacterBase::disableBuff), 5);
						}
						else if (is_same(hitType, "ct_hit"))
						{
							if (_actionState != State::OATTACK ||
								(_actionState == State::OATTACK &&
								 (attacker->_actionState == State::O2ATTACK ||
								  attacker->_actionState == State::OATTACK)))
							{
								if (attacker->_isCatchOne == false ||
									attacker->isCharacter("Shenwei"))
								{
									if (attacker->getMaster())
									{
										if (attacker->isCharacter("Kuroari") ||
											attacker->isCharacter("Shenwei") ||
											attacker->isCharacter("Sabaku") ||
											attacker->isCharacter("Shenwei2"))
										{
											if (hardHurt(3000, false, true, false, false))
											{
												attacker->_isCatchOne = true;
												scheduleOnce(schedule_selector(CharacterBase::reCatched), 2.9f);
											}
										}
										else if (attacker->isCharacter("SandBall"))
										{
											if (hardHurt(1000, false, true, false, false))
											{
												attacker->_isCatchOne = true;
												scheduleOnce(schedule_selector(CharacterBase::reCatched), 0.9f);
											}
										}
										else if (attacker->getMaster()->isCharacter("Shikamaru"))
										{
											bool pianyi = false;
											if (attacker->isCharacter("KageHand"))
											{
												pianyi = hardHurt(6000, false, false, true, false);
												if (pianyi)
												{
													attacker->stopAllActions();
													attacker->schedule(schedule_selector(CharacterBase::getSticker), 0.1f);
													schedule(schedule_selector(CharacterBase::lostBlood), 1.0f);
													lostBloodValue = 400;
													scheduleOnce(schedule_selector(CharacterBase::removeLostBlood), 6.0f);
												}
											}
											else if (attacker->isCharacter("QuanRen") ||
													 attacker->isCharacter("KageBom"))
											{
												pianyi = hardHurt(3000, false, false, true, false);
											}

											if (pianyi)
											{
												attacker->_isCatchOne = true;
												setPosition(CCPointMake(attacker->getPositionX(), attacker->getPositionY() + 1));
												_delegate->reorderChild(this, -getPositionY());
											}
										}
										else if (attacker->getMaster()->isCharacter("Itachi") ||
												 attacker->getMaster()->isCharacter("Chiyo"))
										{
											bool pianyi = false;

											if (attacker->getMaster()->isCharacter("Chiyo"))
											{
												pianyi = hardHurt(2000, false, false, true, false);
											}
											else
											{
												pianyi = hardHurt(3000, false, false, true, false);
											}
											if (pianyi)
											{
												attacker->_isCatchOne = true;
												setPosition(CCPointMake(attacker->getPositionX() + 2, attacker->getPositionY() - 2));
												_delegate->reorderChild(this, -getPositionY());
											}
										}
									}
									else
									{
										if (attacker->isCharacter("Lee") ||
											attacker->isCharacter("RockLee"))
										{
											if (hardHurt(1000, false, true, false, false))
											{
												attacker->_isCatchOne = true;
												scheduleOnce(schedule_selector(CharacterBase::reCatched), 1.1f);
											}
										}
										else if (attacker->isCharacter("Kakuzu"))
										{
											bool pianyi = false;

											if (!_isArmored)
											{
												setKnockLength(1);
											}
											pianyi = hardHurt(1500, false, false, true, true);

											if (pianyi)
											{
												attacker->_isCatchOne = true;
												setPosition(CCPointMake(attacker->getPositionX() + (attacker->_isFlipped ? -28 : 28), attacker->getPositionY() - 1));
												setFlipX(attacker->_isFlipped ? false : true);
												_delegate->reorderChild(this, -getPositionY());
											}
										}
										else if (attacker->isCharacter("Tobi"))
										{
											if (!_isArmored)
											{
												setKnockLength(1);
											}
											hardHurt(1000, true, false, false, false);
										}
									}
								}
							}
						}
						else if (is_same(hitType, "f_hit") || is_same(hitType, "bf_hit"))
						{
							autoFlip(attacker);
							if (_actionState != State::OATTACK ||
								(_actionState == State::OATTACK &&
								 (attacker->_actionState == State::O2ATTACK ||
								  attacker->_actionState == State::OATTACK)))
							{
								floatUP(64, true);
							}
						}
						else if (is_same(hitType, "f2_hit"))
						{
							autoFlip(attacker);
							if (_actionState != State::OATTACK ||
								(_actionState == State::OATTACK &&
								 (attacker->_actionState == State::O2ATTACK ||
								  attacker->_actionState == State::OATTACK)))
							{
								floatUP(128, true);
							}
						}
						else if (is_same(hitType, "b_hit"))
						{
							autoFlip(attacker);

							if (_actionState != State::OATTACK ||
								(_actionState == State::OATTACK &&
								 (attacker->_actionState == State::O2ATTACK ||
								  attacker->_actionState == State::OATTACK)))
							{
								floatUP(16, false);
							}
						}
						else if (is_same(hitType, "ab_hit"))
						{
							absorb(attacker->getPosition(), true);
						}
						else if (is_same(hitType, "s_hit"))
						{
							absorb(attacker->getPosition(), false);
						}
					}

					if (isCharacter("Hidan") && _skillChangeBuffValue)
					{
						bool _isCounter = false;
						if (hasMonsterArrayAny())
						{
							CCObject *pObject;
							CCARRAY_FOREACH(_monsterArray, pObject)
							{
								auto tempMonster = (CharacterBase *)pObject;
								float distanceX = ccpSub(tempMonster->getPosition(), getPosition()).x;
								float distanceY = ccpSub(tempMonster->getPosition(), getPosition()).y;
								if (abs(distanceX) < 40 && abs(distanceY) < 15)
								{
									_isCounter = true;
								}
							}
						}

						if (_isCounter && attacker->isNotGuardian())
						{
							if (attacker->_master && attacker->_master->_actionState != State::DEAD)
							{
								attacker->_master->_slayer = this;

								attacker->_master->setDamage(attacker->_effectType, attacker->_attackValue, attacker->_isFlipped);
								if (attacker->_master->_hpBar)
								{
									attacker->_master->_hpBar->loseHP(attacker->_master->getHpPercent());
								}
							}
							else if (!attacker->_master)
							{
								if (attacker->_actionState != State::DEAD)
								{
									attacker->_slayer = this;

									attacker->setDamage(attacker->_effectType, attacker->_attackValue, attacker->_isFlipped);
									if (attacker->_hpBar)
									{
										attacker->_hpBar->loseHP(attacker->getHpPercent());
									}
								}
							}

							CCObject *pObject;
							CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
							{
								auto tempHero = (Hero *)pObject;
								if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0 && (tempHero->isPlayer() || tempHero->isCom()) && tempHero->_actionState != State::DEAD)
								{
									tempHero->_slayer = this;
									tempHero->setDamage(attacker->_effectType, attacker->_attackValue / 2, attacker->_isFlipped);
									if (tempHero->_hpBar)
									{
										tempHero->_hpBar->loseHP(tempHero->getHpPercent());
									}
								}
							}

							return;
						}
					}
					else if (isCharacter("Kakuzu") && _skillChangeBuffValue)
					{
						if (!attacker->_master)
						{
							if (attacker->_actionState != State::DEAD)
							{
								attacker->_slayer = this;

								attacker->setDamage(attacker->_effectType, attacker->_attackValue / 2, attacker->_isFlipped);
								if (attacker->_hpBar)
								{
									attacker->_hpBar->loseHP(attacker->getHpPercent());
								}
							}
						}
					}

					setDamage(attacker->_effectType, attacker->_attackValue, attacker->_isFlipped);
					//lose the hp
					if (_hpBar)
					{
						_hpBar->loseHP(getHpPercent());
					}
				}
			}
		}
	}
}

CCAction *CharacterBase::createAnimation(CCArray *ationArray, float fps, bool isRepeat, bool isReturn)
{
	CCObject *tObject;
	CCArray *animeFrames = CCArray::create();
	auto seqArray = CCArray::create();
	CCAnimation *tempAnimation;
	CCAction *tempAction;
	CCAction *seq;

	CCARRAY_FOREACH(ationArray, tObject)
	{
		auto dic = (CCDictionary *)tObject;
		CCDictElement *ele = nullptr;

		CCDICT_FOREACH(dic, ele)
		{
			const char *key = CCString::create(ele->getStrKey())->getCString();
			const char *keyValue = dic->valueForKey(key)->getCString();
			if (is_same(key, "frameName"))
			{
				auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(keyValue);
				animeFrames->addObject(frame);
			}
			else
			{
				tempAnimation = CCAnimation::createWithSpriteFrames(animeFrames, float(1.0 / fps));
				tempAction = CCAnimate::create(tempAnimation);

				seqArray->addObject(tempAction);
				if (is_same(key, "setAttackBox"))
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setAttackBox), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setSound"))
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setSound), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setDSound"))
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setDSound), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setDelay"))
				{
					float delayTime = dic->valueForKey(key)->intValue();
					auto delay = CCDelayTime::create(delayTime / 100);
					seqArray->addObject(delay);
				}
				else if (is_same(key, "setMove"))
				{
					int moveLength = dic->valueForKey(key)->intValue();
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setMove), (void *)moveLength);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setSkillEffect"))
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setSkillEffect), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setJump"))
				{
					bool jumpDirection = dic->valueForKey(key)->boolValue();
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setJump), (void *)jumpDirection);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setCharge"))
				{
					auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::getCollider));
					seqArray->addObject(call);
					int moveLength = dic->valueForKey(key)->intValue();
					call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setCharge), (void *)moveLength);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setChargeB"))
				{
					int moveLength = dic->valueForKey(key)->intValue();
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setChargeB), (void *)moveLength);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setClone"))
				{
					int cloneTime = dic->valueForKey(key)->intValue();
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setClone), (void *)cloneTime);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setMon"))
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setMon), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setFont"))
				{
					callValue = CCDictionary::create();
					callValue->retain();
					const char *split = ",";
					char *p;
					char *str = new char[20];
					strcpy(str, keyValue);
					p = strtok(str, split);
					int i = 1;
					while (p != nullptr)
					{
						callValue->setObject(CCString::create(p), i);
						i++;
						p = strtok(nullptr, split);
					}

					//auto call = CCCallFuncND::create(this,callfuncND_selector(CharacterBase::setFontEffect),(void*)callValue);
					//seqArray->addObject(call);
				}
				else if (is_same(key, "setBuff"))
				{
					int buffValue = dic->valueForKey(key)->intValue();
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setBuff), (void *)buffValue);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setCommand"))
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setCommand), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setDetonation"))
				{
					auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::dealloc));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setBullet"))
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setBullet), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setMonAttack"))
				{
					int skillNum = dic->valueForKey(key)->intValue();
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setMonAttack), (void *)skillNum);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setTrap"))
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setTrap), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setActionResume"))
				{
					auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::setActionResume));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setActionResume2"))
				{
					auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::setActionResume2));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setShadow"))
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(animeFrames->objectAtIndex(int(animeFrames->count() - 1)), 1);
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setShadow), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setTransform"))
				{
					auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::setTransform));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setOugis"))
				{
					auto call = CCCallFuncN::create(this, callfuncN_selector(CharacterBase::setOugis));
					seqArray->addObject(call);
				}
				else if (is_same(key, "stopJump"))
				{
					int stopTime = dic->valueForKey(key)->intValue();
					auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::stopJump), (void *)stopTime);
					seqArray->addObject(call);
				}
				else if (is_same(key, "setFlipped"))
				{
					auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::setCharFlip));
					seqArray->addObject(call);
				}

				animeFrames->removeAllObjects();
			}
		}
	}
	if (animeFrames->count() > 0)
	{
		tempAnimation = CCAnimation::createWithSpriteFrames(animeFrames, float(1.0 / fps));
		tempAction = CCAnimate::create(tempAnimation);
		seqArray->addObject(tempAction);
	}

	if (isRepeat)
	{
		seq = CCRepeatForever::create(CCSequence::create(seqArray));
	}
	else
	{
		if (isReturn)
		{
			auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::idle));
			seqArray->addObject(call);
		}

		seq = CCSequence::create(seqArray);
	}

	return seq;
}

void CharacterBase::setCharFlip()
{
	if (_isFlipped)
	{
		setFlipX(false);
		_isFlipped = false;
	}
	else
	{
		setFlipX(true);
		_isFlipped = true;
	}
}

void CharacterBase::setShadow(CCNode *sender, void *data)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	auto file = (CCDictionary *)data;
	auto frame = (CCSpriteFrame *)(file->objectForKey(1));
	CCSprite *charN = CCSprite::createWithSpriteFrame(frame);
	charN->setVisible(false);
	if (isKonohaGroup())
	{
		charN->setColor(ccGREEN);
	}
	else
	{
		charN->setColor(ccRED);
	}

	charN->setOpacity(180);
	charN->setAnchorPoint(ccp(0.5, 0));
	charN->setFlipX(_isFlipped);
	charN->setPosition(getPosition());
	auto delay = CCDelayTime::create(0.1f);
	auto call = CCCallFuncN::create(charN, callfuncN_selector(CharacterBase::enableShadow));
	charN->runAction(CCSequence::createWithTwoActions(delay, call));
	_delegate->addChild(charN, -getPositionY() - 1);
}

void CharacterBase::enableShadow(CCNode *sender)
{
	CCSprite *charN = (CCSprite *)sender;
	charN->setVisible(true);
	auto delay = CCDelayTime::create(0.1f);
	auto call = CCCallFuncN::create(charN, callfuncN_selector(CharacterBase::disableShadow));
	charN->runAction(CCSequence::createWithTwoActions(delay, call));
}

void CharacterBase::disableShadow(CCNode *sender)
{
	CCSprite *charN = (CCSprite *)sender;
	charN->stopAllActions();
	charN->removeFromParentAndCleanup(true);
}

void CharacterBase::setOugis(CCNode *sender)
{
	_delegate->setOugis(this);
}

CCRect CharacterBase::setHalfBox()
{
	CCRect halfbox = CCRectMake(_isFlipped ? getPositionX() - getContentSize().width / 2 : getPositionX(),
								getPositionY() + getContentSize().height / 2,
								getContentSize().width / 2,
								getContentSize().height / 2);
	return halfbox;
}

CCRect CharacterBase::setHitBox()
{
	CCRect hitbox = boundingBox();
	return hitbox;
}

void CharacterBase::disableHpBar(float dt)
{
	if (_hpBar)
		_hpBar->setVisible(false);
}

void CharacterBase::setDamage(const char *effectType, int attackValue, bool isFlipped)
{
	if (isTower())
	{
		if (_hpBar)
			_hpBar->setVisible(true);

		unschedule(schedule_selector(CharacterBase::disableHpBar));
		scheduleOnce(schedule_selector(CharacterBase::disableHpBar), 2.0f);
	}

	int criticalValue;
	int realValue;

	auto attacker = _slayer;
	CharacterBase *currentAttacker;
	if (attacker->getMaster())
		currentAttacker = attacker->getMaster();
	else
		currentAttacker = attacker;

	if (attacker->isGearCD || (attacker->_master && attacker->_master->isGearCD))
		criticalValue = rand() % 60 + 10;
	else
		criticalValue = rand() % 50;

	if (attacker->isCharacter("Hidan") && attacker->_skillChangeBuffValue)
	{
		realValue = attackValue + criticalValue;
	}
	else
	{
		bool isCannotMiss = false; // is this attack has 100 percent accuracy
		if (attacker->isCharacter("Hiruzen") && attacker->getActionState() == State::O2ATTACK)
		{
			isCannotMiss = true;
		}

		if (isCannotMiss)
		{
			realValue = attackValue + criticalValue;
		}
		else if ((attacker->getMaster() ||
				  attacker->getActionState() == State::NATTACK) &&
				 attacker->hasArmorBroken)
		{
			realValue = attackValue + criticalValue;
		}
		else
		{
			if (attackValue - _gardValue <= 0)
			{
				realValue = criticalValue;
			}
			else
			{
				realValue = attackValue - _gardValue + criticalValue;
				float decreaseRating = 0;
				if (hasArmor)
					decreaseRating += 0.25;

				if (isCharacter("Kakuzu") && _skillChangeBuffValue)
					decreaseRating += 0.25;

				if (isCharacter("Chiyo"))
				{
					CCObject *pObject;
					CCARRAY_FOREACH(getMonsterArray(), pObject)
					{
						auto mo = (Monster *)pObject;
						if (mo->isCharacter("Parents") && !mo->_skillChangeBuffValue && mo->getActionState() != State::SATTACK)
						{
							CCPoint sp = ccpSub(mo->getPosition(), getPosition());
							if (sp.x <= 48)
								decreaseRating += 0.25;
						}
					}
				}

				if (realValue - realValue * decreaseRating < 0)
					realValue = 0;
				else
					realValue -= realValue * decreaseRating;
			}
		}
	}

	if (getHPValue() - realValue < 0)
		setHP(to_ccstring(0));
	else
		setHP(to_ccstring(getHPValue() - realValue));

	if (isClone())
	{
		uint32_t boundValue = 0;
		if (isCharacter("Naruto"))
			boundValue = realValue * 15 / 100;
		else if (isCharacter("SageNaruto"))
			boundValue = realValue * 25 / 100;
		else if (isCharacter("RikudoNaruto"))
		{
			boundValue = realValue * 35 / 100;

			//4v4
			if (Cheats >= MaxCheats)
				boundValue = boundValue / 2;

			if (currentAttacker->isAttackGainCKR)
			{
				if (boundValue - boundValue * 25 / 100 > 0)
					boundValue = boundValue - boundValue * 25 / 100;
				else
					boundValue = 0;
			}

			if (_master)
			{
				if (_master->getLV() >= 2 && !_master->_isControlled)
				{
					if (45000 - _master->getCkrValue() >= boundValue)
					{
						uint32_t newValue = _master->getCkrValue() + boundValue;
						_master->setCKR(to_ccstring(newValue));
					}
					else
					{
						_master->setCKR(CCString::create("45000"));
					}

					if (_master->getCkrValue() >= 15000)
						_master->_isCanOugis1 = true;

					if (_master->isPlayer())
						_delegate->setCKRLose(false);
				}

				if (_master->getLV() >= 4 && !_master->_isControlled)
				{
					if (50000 - _master->getCkr2Value() >= boundValue)
					{
						uint32_t newValue = _master->getCkr2Value() + boundValue;
						_master->setCKR2(to_ccstring(newValue));
					}
					else
					{
						_master->setCKR2(CCString::create("50000"));
					}

					if (_master->getCkr2Value() >= 25000)
						_master->_isCanOugis2 = true;

					if (_master->isPlayer())
						_delegate->setCKRLose(true);
				}
			}
		}
		else
		{
			uint32_t boundValue;

			if (_level == 5)
				boundValue = realValue + realValue * 5 / 100;
			else if (_level == 6)
				boundValue = realValue + realValue * 10 / 100;
			else
				boundValue = realValue;

			boundValue += realValue * gearCKRValue / 100;

			// 4v4
			if (Cheats >= MaxCheats)
				boundValue = boundValue / 2;

			if (currentAttacker->isAttackGainCKR)
			{
				if (boundValue - boundValue * 25 / 100 > 0)
					boundValue = boundValue - boundValue * 25 / 100;
				else
					boundValue = 0;
			}

			bool isGainable = true;
			if (isCharacter("Tsunade") && _skillChangeBuffValue)
				isGainable = false;
			if (attacker->isCharacter("Hinata") && attacker->_skillUPBuffValue)
				isGainable = false;

			if (_level >= 2 && !_isControlled && isGainable)
			{
				if (45000 - getCkrValue() >= boundValue)
				{
					uint32_t newValue = getCkrValue() + boundValue;
					setCKR(to_ccstring(newValue));
				}
				else
				{
					setCKR(CCString::create("45000"));
				}

				if (getCkrValue() >= 15000)
					_isCanOugis1 = true;

				if (isPlayer())
					_delegate->setCKRLose(false);
			}

			if (_level >= 4 && !_isControlled && isGainable)
			{
				if (50000 - getCkr2Value() >= boundValue)
				{
					uint32_t newValue = getCkr2Value() + boundValue;
					setCKR2(to_ccstring(newValue));
				}
				else
				{
					setCKR2(CCString::create("50000"));
				}

				if (getCkr2Value() >= 25000)
					_isCanOugis2 = true;

				if (isPlayer())
					_delegate->setCKRLose(true);
			}
		}

		if (isPlayer() || isCom())
		{
			uint32_t gainValue = 0;

			if (attacker->isCharacter("Kisame") && attacker->_skillChangeBuffValue)
			{
				if (currentAttacker->isAttackGainCKR)
					gainValue = realValue * 80 / 100;
				else
					gainValue = realValue * 65 / 100;
			}
			else if (currentAttacker->isAttackGainCKR)
			{
				gainValue = realValue * 15 / 100;
			}

			if (gainValue != 0)
			{
				if (currentAttacker->_level >= 2 && !currentAttacker->_isControlled)
				{
					if (45000 - currentAttacker->getCkrValue() >= gainValue)
					{
						uint32_t newValue = currentAttacker->getCkrValue() + gainValue;
						currentAttacker->setCKR(to_ccstring(newValue));
					}
					else
					{
						currentAttacker->setCKR(CCString::create("45000"));
					}

					if (currentAttacker->getCkrValue() >= 15000)
						currentAttacker->_isCanOugis1 = true;

					if (currentAttacker->isPlayer())
						_delegate->setCKRLose(false);
				}

				if (currentAttacker->_level >= 4 && !currentAttacker->_isControlled)
				{
					if (50000 - currentAttacker->getCkr2Value() >= gainValue)
					{
						uint32_t newValue = currentAttacker->getCkr2Value() + gainValue;
						currentAttacker->setCKR2(to_ccstring(newValue));
					}
					else
					{
						currentAttacker->setCKR2(CCString::create("50000"));
					}

					if (currentAttacker->getCkr2Value() >= 25000)
						currentAttacker->_isCanOugis2 = true;

					if (currentAttacker->isPlayer())
						_delegate->setCKRLose(true);
				}
			}
		}

		if (isPlayer() || (isNotTower() &&
						   abs(ccpSub(getPosition(), _delegate->currentPlayer->getPosition()).x) < winSize.width / 2))
		{
			//create damage value display
			bool _isDisplay = false;

			if (attacker->isPlayer() || isPlayer())
			{
				_isDisplay = true;
			}
			if (attacker->getMaster())
			{
				if (attacker->getMaster()->isPlayer())
					_isDisplay = true;
			}

			if (_isDisplay)
			{
				if (criticalValue <= 20)
					setDamgeDisplay(realValue, "white");
				else if (criticalValue <= 40)
					setDamgeDisplay(realValue, "yellow");
				else
					setDamgeDisplay(realValue, "red");
			}

			//create damage effect
			if (isFlog() && attacker->isNotFlog())
			{
				if (is_same(effectType, "a_hit"))
				{
					setDamgeEffect("a_hit");
				}
			}
			else if (attacker->isNotFlog())
			{
				setDamgeEffect(effectType);
			}
		}
	}
}

void CharacterBase::setCoinDisplay(int num)
{
	CCSprite *coinDisplay = CCSprite::create();

	CCSprite *coinSprite = CCSprite::createWithSpriteFrameName("coin.png");
	coinSprite->setPosition(ccp(14, 0));
	coinDisplay->addChild(coinSprite);

	CCString *label = CCString::createWithFormat("+%d", num);
	auto rewardLabel = CCLabelBMFont::create(label->getCString(), "Fonts/yellow.fnt");
	rewardLabel->setPosition(ccp(0, 0));
	rewardLabel->setScale(0.3f);
	coinDisplay->addChild(rewardLabel);

	coinDisplay->setPosition(ccp(getPositionX(), getPositionY() + getContentSize().height / 2));
	_delegate->addChild(coinDisplay, 5000);

	auto mv = CCMoveBy::create(0.5f, ccp(0, 12));
	auto fadeOut = CCFadeOut::create(0.8f);
	auto call = CCCallFuncND::create(coinDisplay, callfuncND_selector(CharacterBase::removeCoinDisplay), nullptr);
	auto sp = CCSpawn::create(fadeOut, mv, nullptr);
	auto seqArray = CCArray::create();
	seqArray->addObject(sp);
	seqArray->addObject(call);
	auto seq = CCSequence::create(seqArray);
	coinDisplay->runAction(seq);
}

void CharacterBase::removeCoinDisplay(CCNode *sender, void *data)
{
	sender->removeFromParent();
	sender = nullptr;
}

void CharacterBase::setDamgeDisplay(int value, const char *type)
{
	if (_damageArray->count() < 6)
	{
		auto damageFont = CCLabelBMFont::create(to_cstr(value), CCString::createWithFormat("Fonts/%s.fnt", type)->getCString());
		damageFont->setAnchorPoint(ccp(0.5, 0.5));

		if (isFlog())
		{
			damageFont->setScale(0.6f);
			damageFont->setPosition(ccp(getPositionX() + rand() % 16, getPositionY() + getHeight() + rand() % 4));
		}
		else
		{
			damageFont->setScale(0.8f);
			damageFont->setPosition(ccp(getPositionX() + rand() % 16, getPositionY() + getHeight() + rand() % 16));
		}

		_delegate->addChild(damageFont, currentNumberTag);
		_damageArray->addObject(damageFont);

		auto sd = CCScaleBy::create(0.2f, 0.5f);
		auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::removeDamageDisplay));

		auto mv = CCMoveBy::create(0.4f, ccp(0, 12));
		auto fadeOut = CCFadeOut::create(0.4f);
		auto sp = CCSpawn::create(fadeOut, mv, nullptr);

		auto seqArray = CCArray::create();
		seqArray->addObject(sd);
		seqArray->addObject(sp);
		seqArray->addObject(call);

		auto seq = CCSequence::create(seqArray);

		damageFont->runAction(seq);
	}
}

void CharacterBase::removeDamageDisplay()
{
	if (_damageArray && _damageArray->count() > 0)
	{
		CCObject *pObject = _damageArray->objectAtIndex(0);
		auto damageFont = (CCLabelBMFont *)pObject;
		damageFont->removeFromParent();
		_damageArray->removeObjectAtIndex(0);
		damageFont = nullptr;
	}
}

void CharacterBase::setDamgeEffect(const char *type)
{
	if (isPlayer() || abs(ccpSub(getPosition(), _delegate->currentPlayer->getPosition()).x) < winSize.width / 2)
	{
		if (damageEffectCount < 2)
		{
			if (isNotFlog())
			{
				Effect *ef = Effect::create(type, this);
				_delegate->damageEffectBatch->addChild(ef, 5000);
			}
			else
			{
				Effect *ef = Effect::create(type, this);
				_delegate->damageEffectBatch->addChild(ef);
			}

			damageEffectCount++;
		}
	}
}

void CharacterBase::setSkillEffect(CCNode *sender, void *data)
{
	auto file = (CCDictionary *)data;
	auto type = ((CCString *)(file->objectForKey(1)))->getCString();

	if (isPlayer() ||
		abs(ccpSub(getPosition(), _delegate->currentPlayer->getPosition()).x) < winSize.width / 2)
	{
		Effect *ef = Effect::create(type, this);
		if (is_same(type, "Bagua") ||
			is_same(type, "Kujiyose"))
		{
			_delegate->addChild(ef, -500);
		}
		else if (is_same(type, "DarkFlame"))
		{
			_delegate->addChild(ef, -ef->getPositionY());
		}
		else
		{
			_delegate->skillEffectBatch->addChild(ef);
		}
	}
}

void CharacterBase::setItem(abType type)
{
	if (_isControlled)
		return;

	if (isCharacter("Kankuro",
					"Chiyo",
					"Kiba",
					"Kakuzu") &&
		hasMonsterArrayAny())
	{
		CCObject *pObject;
		CCARRAY_FOREACH(getMonsterArray(), pObject)
		{
			auto mo = (Monster *)pObject;
			if (mo->isNotCharacter("Traps"))
			{
				mo->setItem(Item1);
			}
		}
	}
	_isCanItem1 = false;
	if (isPlayer())
	{
		if (_isAI)
		{
			_delegate->getHudLayer()->offCoin(to_cstr(50));
		}
	}
	else
	{
		minusCoin(50);
	}
	scheduleOnce(schedule_selector(Hero::enableItem1), 5.0f);

	if (_hpBar)
	{
		uint32_t hpRestore = 3000 + gearRecoverValue;
		if (getMaxHPValue() - getHPValue() <= hpRestore)
		{
			setHP(CCString::create(getMaxHP()->getCString()));
			if (_hpBar)
			{
				_hpBar->loseHP(getHpPercent());
			}
		}
		else
		{
			setHP(to_ccstring(getHPValue() + hpRestore));
			if (_hpBar)
			{
				_hpBar->loseHP(getHpPercent());
			}
		}

		if (!_isHealling && !_healItemEffect)
		{
			_healItemEffect = Effect::create("hp_restore", this);
			_healItemEffect->setPosition(ccp(_isFlipped ? getContentSize().width / 2 + 16 : getContentSize().width / 2 - 16,
											 _height));
			addChild(_healItemEffect);
			//_isHealling=true;
		}
	}
}

bool CharacterBase::setGear(gearType type)
{
	int gearCost = 0;
	// The cost of [ 00 03 06 ] is 500
	if (type % 3 == 0)
		gearCost = 500;
	else
		gearCost = 1000;

	if (getGearArray()->count() <= 2 && getCoinValue() >= gearCost)
	{
		CCString *gearItem = to_ccstring(gearType(type));
		getGearArray()->addObject(gearItem);

		if (isPlayer())
			_delegate->getHudLayer()->offCoin(to_cstr(gearCost));
		else
			minusCoin(gearCost);

		switch (type)
		{
		case gear00:
			_isCanGear00 = true;
			break;
		case gear01:
			gearCKRValue = 25;
			break;
		case gear02:
			isAttackGainCKR = true;
			break;
		case gear03:
			_isCanGear03 = true;
			break;
		case gear04:
			if (getTempAttackValue1())
			{
				settempAttackValue1(to_ccstring(getTempAttackValue1() + 160));
			}
			setnAttackValue(to_ccstring(getNAttackValue() + 160));
			hasArmorBroken = true;
			break;
		case gear05:
			isGearCD = true;
			_sattackcoldDown1 -= 5;
			_sattackcoldDown2 -= 5;
			_sattackcoldDown3 -= 5;

			if (isPlayer())
			{
				_delegate->getHudLayer()->skill1Button->setCD(to_ccstring(_sattackcoldDown1 * 1000));
				_delegate->getHudLayer()->skill2Button->setCD(to_ccstring(_sattackcoldDown2 * 1000));
				_delegate->getHudLayer()->skill3Button->setCD(to_ccstring(_sattackcoldDown3 * 1000));

				_delegate->getHudLayer()->skill1Button->_isColdChanged = true;
				_delegate->getHudLayer()->skill2Button->_isColdChanged = true;
				_delegate->getHudLayer()->skill3Button->_isColdChanged = true;
			}
			break;
		case gear06:
			_isCanGear06 = true;
			break;
		case gear07:
			gearRecoverValue = 3000;
			_delegate->getHudLayer()->item1Button->setCD(to_ccstring(3000));
			_delegate->getHudLayer()->item1Button->_isColdChanged = true;
			break;
		case gear08:
			uint32_t tempMaxHP = getMaxHPValue();
			tempMaxHP += 6000;
			setMaxHP(to_ccstring(tempMaxHP));
			if (_hpBar)
			{
				_hpBar->loseHP(getHpPercent());
			}
			hasArmor = true;
			break;
		}

		return true;
	}
	else
	{
		return false;
	}
}

void CharacterBase::useGear(gearType type)
{
	if (_isControlled)
		return;

	if (type == gear00)
	{
		if (getActionState() == State::NATTACK ||
			getActionState() == State::WALK ||
			getActionState() == State::IDLE)
		{
			if (getWalkSpeed() == 224)
			{
				setWalkSpeed(320);

				_isCanGear00 = false;

				_speedItemEffect = Effect::create("speedUp", this);
				addChild(_speedItemEffect);

				scheduleOnce(schedule_selector(CharacterBase::enableGear00), 15.0f);
				if (isPlayer() || is_same(getGroup()->getCString(), _delegate->currentPlayer->getGroup()->getCString()))
					setOpacity(150);
				else
					setVisible(false);

				if (_hpBar)
					_hpBar->setVisible(false);
				if (_shadow)
					_shadow->setVisible(false);

				_isVisable = false;

				auto callValue2 = CCDictionary::create();
				callValue2->setObject(CCString::create("Audio/Effect/suzou_effect.ogg"), 1);
				setSound(this, callValue2);

				schedule(schedule_selector(CharacterBase::disableGear1), 3.0f);
			}
		}
	}
	else if (type == gear03)
	{
		_isCanGear03 = false;

		auto tmpValue = CCDictionary::create();
		tmpValue->setObject(CCString::create("Traps"), 1);
		setMon(this, (void *)tmpValue);

		scheduleOnce(schedule_selector(CharacterBase::enableGear03), 15.0f);
	}
	else if (type == gear06)
	{
		_isCanGear06 = false;
		scheduleOnce(schedule_selector(CharacterBase::enableGear06), 15.0f);

		if (!_isInvincible && !_isArmored)
		{
			if (getActionState() == State::IDLE ||
				getActionState() == State::WALK ||
				getActionState() == State::FLOAT ||
				getActionState() == State::AIRHURT ||
				getActionState() == State::HURT ||
				getActionState() == State::KNOCKDOWN)
			{
				if (_isSticking)
				{
					_isSticking = false;
				}
				if (getActionState() == State::FLOAT ||
					getActionState() == State::AIRHURT)
				{
					setPositionY(_originY);
					_originY = 0;
					_delegate->reorderChild(this, -getPositionY());
				}

				idle();

				auto callValue = CCDictionary::create();
				callValue->setObject(CCString::create("tishen"), 1);
				setSkillEffect(this, callValue);
				scheduleOnce(schedule_selector(CharacterBase::disableGear2), 1.0f);

				auto callValue2 = CCDictionary::create();
				callValue2->setObject(CCString::create("Audio/Effect/poof2.ogg"), 1);
				setSound(this, callValue2);

				if (isPlayer() || is_same(getGroup()->getCString(), _delegate->currentPlayer->getGroup()->getCString()))
					setOpacity(150);
				else
					setVisible(false);

				if (_hpBar)
					_hpBar->setVisible(false);
				if (_shadow)
					_shadow->setVisible(false);

				_isVisable = false;
			}
		}
	}
}

void CharacterBase::disableGear1(float dt)
{
	if (!_isVisable && _actionState != State::HURT)
	{
		setOpacity(255);
		setVisible(true);
		_isVisable = true;

		if (_hpBar)
			_hpBar->setVisible(true);
		if (_shadow)
			_shadow->setVisible(true);
	}
	else
	{
		unschedule(schedule_selector(CharacterBase::disableGear1));
		if (getWalkSpeed() == 320)
		{
			setWalkSpeed(224);
		}
	}
}

void CharacterBase::disableGear2(float dt)
{
	setOpacity(255);
	setVisible(true);
	_isVisable = true;

	if (_hpBar)
		_hpBar->setVisible(true);
	if (_shadow)
		_shadow->setVisible(true);
}

void CharacterBase::disableGear3(float dt)
{
}

void CharacterBase::enableGear00(float dt)
{
	_isCanGear00 = true;
}

void CharacterBase::enableGear03(float dt)
{
	_isCanGear03 = true;
}

void CharacterBase::enableGear06(float dt)
{
	_isCanGear06 = true;
}

void CharacterBase::addCoin(int num)
{
	setCoin(to_ccstring(getCoinValue() + num));
}

void CharacterBase::minusCoin(int num)
{
	if (getCoinValue() > num)
		setCoin(to_ccstring(getCoinValue() - num));
	else
		setCoin(to_ccstring(0));
}

void CharacterBase::setRestore(float dt)
{
	if (_hpBar)
	{
		if (getMaxHPValue() - getHPValue() <= 800)
		{
			setHP(CCString::create(getMaxHP()->getCString()));
			_hpBar->loseHP(getHpPercent());
		}
		else
		{
			setHP(to_ccstring(getHPValue() + 800));
			_hpBar->loseHP(getHpPercent());
		}

		_healItemEffect = Effect::create("hp_restore", this);
		_healItemEffect->setPosition(ccp(_isFlipped ? getContentSize().width / 2 + 16 : getContentSize().width / 2 - 16,
										 _height));
		addChild(_healItemEffect);
	}
}

void CharacterBase::setRestore2(float dt)
{
	if (_hpBar)
	{
		bool isZone = false;
		if (isAkatsukiGroup() && getPositionX() <= _delegate->currentMap->getTileSize().width * 2)
		{
			isZone = true;
		}
		else if (isKonohaGroup() && getPositionX() >= (_delegate->currentMap->getMapSize().width - 2) * _delegate->currentMap->getTileSize().width)
		{
			isZone = true;
		}
		if (isZone)
		{
			if (getHPValue() - 1000 > 0)
			{
				setHP(to_ccstring(getHPValue() - 1000));
				_hpBar->loseHP(getHpPercent());
			}
			else
			{
				setHP(to_ccstring(100));
				_hpBar->loseHP(getHpPercent());
			}
		}

		if (getActionState() == State::IDLE && getHpPercent() < 1)
		{
			if (getMaxHPValue() - getHPValue() <= 300)
			{
				setHP(CCString::create(getMaxHP()->getCString()));
				_hpBar->loseHP(getHpPercent());
			}
			else
			{
				setHP(to_ccstring(getHPValue() + 300));
				_hpBar->loseHP(getHpPercent());
			}
		}
	}
}

void CharacterBase::disableEffect()
{
	if (_healItemEffect)
	{
		_healItemEffect->removeFromParentAndCleanup(true);
		_healItemEffect = nullptr;
	}

	if (_speedItemEffect)
	{
		_speedItemEffect->removeFromParentAndCleanup(true);
		_speedItemEffect = nullptr;
	}
}

void CharacterBase::setSound(CCNode *sender, void *data)
{
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isVoice"))
	{
		bool _isPlayable = false;
		if (isPlayer() ||
			abs(ccpSub(getPosition(), _delegate->currentPlayer->getPosition()).x) < winSize.width / 2)
		{
			_isPlayable = true;
		}
		if (_delegate->controlChar)
		{
			if (abs(ccpSub(getPosition(), _delegate->controlChar->getPosition()).x) < winSize.width / 2)
			{
				_isPlayable = true;
			}
		}

		if (_isPlayable)
		{
			auto file = (CCDictionary *)data;
			CCString *str = (CCString *)(file->objectForKey(1));
			SimpleAudioEngine::sharedEngine()->preloadEffect(str->getCString());
			SimpleAudioEngine::sharedEngine()->playEffect(str->getCString());
		}
	}
}

void CharacterBase::setDSound(CCNode *sender, void *data)
{
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isVoice"))
	{
		bool _isPlayable = false;
		if (isPlayer() ||
			abs(ccpSub(getPosition(), _delegate->currentPlayer->getPosition()).x) < winSize.width / 2)
		{
			_isPlayable = true;
		}
		if (_delegate->controlChar)
		{
			if (abs(ccpSub(getPosition(), _delegate->controlChar->getPosition()).x) < winSize.width / 2)
			{
				_isPlayable = true;
			}
		}

		if (_isPlayable && _isHitOne)
		{
			auto file = (CCDictionary *)data;
			CCString *str = (CCString *)(file->objectForKey(1));
			SimpleAudioEngine::sharedEngine()->preloadEffect(str->getCString());
			SimpleAudioEngine::sharedEngine()->playEffect(str->getCString());
		}
	}
}

void CharacterBase::setAttackBox(CCNode *sender, void *data)
{
	auto file = (CCDictionary *)data;
	CCString *str = (CCString *)(file->objectForKey(1));

	_effectType = str->getCString();

	if (_actionState == State::HURT)
	{
		if (isCharacter("Sasuke",
						"ImmortalSasuke",
						"DevaPath"))
		{
			if (getMaxHPValue() - getHPValue() <= 260)
			{
				setHP(CCString::create(getMaxHP()->getCString()));
				_hpBar->loseHP(getHpPercent());
			}
			else
			{
				setHP(to_ccstring(getHPValue() + 260));
				_hpBar->loseHP(getHpPercent());
			}

			if (_role && isPlayer())
			{
				_delegate->setHPLose(getHpPercent());
			}

			_attackType = _spcattackType1;
			_attackValue = getSpcAttackValue1();
			_attackRangeX = _spcattackRangeX1;
			_attackRangeY = _spcattackRangeY1;
		}
	}

	CCNotificationCenter::sharedNotificationCenter()->postNotification("acceptAttack", this);

	if (isPlayer())
	{
		if ((_actionState == State::OATTACK || _actionState == State::O2ATTACK) && _isHitOne == true && !_delegate->_isShacking)
		{
			_delegate->_isShacking = true;
			CCScene *f = CCDirector::sharedDirector()->getRunningScene();
			auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::disableShack));
			f->runAction(CCSequence::createWithTwoActions(CCShake::create(0.05f, 12), call));
		}
		if (_delegate->_isAttackButtonRelease && _actionState == State::NATTACK && !_isOnlySkillLocked && !_isAI)
		{
			idle();
			return;
		}
	}
}

void CharacterBase::getSticker(float dt)
{
	CCObject *pObject;
	CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
	{
		auto tempHero = (Hero *)pObject;
		CharacterBase *tempSticker = nullptr;
		if (tempHero->_sticker)
		{
			tempSticker = (CharacterBase *)tempHero->_sticker;
		}
		if (tempSticker && is_same(tempSticker->getCharacter()->getCString(), getCharacter()->getCString()) && tempHero->_isSticking)
		{
			return;
		}
	}

	unschedule(schedule_selector(CharacterBase::getSticker));
	dealloc();
}

void CharacterBase::disableShack()
{
	_delegate->_isShacking = false;
	if (isTower())
	{
		_isHitOne = false;
	}
}

void CharacterBase::setMove(CCNode *sender, void *data)
{
	int moveLength = 0;

	if (getKnockLength())
	{
		if (getKnockLength() == 1)
			return;

		moveLength = getKnockLength();
	}
	else
	{
		moveLength = *((int *)&data);
	}

	if (getPositionX() > _delegate->currentMap->getTileSize().width &&
		getPositionX() < (_delegate->currentMap->getMapSize().width - 1) * _delegate->currentMap->getTileSize().width)
	{
		CCActionInterval *mv;
		if (_actionState == State::HURT)
		{
			if (!_knockDirection)
				mv = CCMoveBy::create(0.1f, ccp(_hurtFromRight ? -moveLength : moveLength, 0));
			else
				mv = CCMoveBy::create(0.1f, ccp(_knockDirection ? -moveLength : moveLength, 0));
			runAction(mv);
		}
		else
		{
			mv = CCMoveBy::create(0.1f, ccp(_isFlipped ? -moveLength : moveLength, 0));
			runAction(mv);
		}
	}
}

void CharacterBase::setJump(CCNode *sender, void *data)
{
	if (_actionState != State::FLOAT &&
		_actionState != State::AIRHURT &&
		_actionState != State::HURT &&
		_actionState != State::DEAD)
	{
		_actionState = State::JUMP;

		bool jumpDirection = (bool)data;
		float posX = getPositionX();
		float posY = getPositionY();
		_originY = posY;

		if (jumpDirection) // Jump Forward
		{
			_jumpUPAction = CCJumpTo::create(0.8f, ccp(posX + (_isFlipped ? -64 : 64), posY), 64, 1);
		}
		else // Jump Back
		{
			_jumpUPAction = CCJumpTo::create(0.8f, ccp(posX + (_isFlipped ? 64 : -64), posY), 64, 1);
		}

		runAction(_jumpUPAction);
	}
}

void CharacterBase::setCharge(CCNode *sender, void *data)
{
	int moveLength = *((int *)&data);
	if ((getPositionX() < _delegate->currentMap->getTileSize().width && _isFlipped) ||
		(getPositionX() > (_delegate->currentMap->getMapSize().width - 1) * _delegate->currentMap->getTileSize().width && !_isFlipped))
	{
		return;
	}
	else
	{
		_moveAction = CCMoveBy::create(0.1f, ccp(_isFlipped ? -moveLength * winSize.width / 1280 : moveLength * winSize.width / 1280, 0));
		runAction(_moveAction);
	}
}

// without getCollider
void CharacterBase::setChargeB(CCNode *sender, void *data)
{
	int moveLength = *((int *)&data);
	float delay;

	if (_actionState == State::OATTACK || _actionState == State::O2ATTACK)
		delay = 0.4f;
	else
		delay = 0.1f;

	if ((getPositionX() < _delegate->currentMap->getTileSize().width && _isFlipped) ||
		(getPositionX() > (_delegate->currentMap->getMapSize().width - 1) * _delegate->currentMap->getTileSize().width && !_isFlipped))
	{
		return;
	}
	else
	{
		_moveAction = CCMoveBy::create(delay, ccp(_isFlipped ? -moveLength * winSize.width / 1280 : moveLength * winSize.width / 1280, 0));
		runAction(_moveAction);
	}
}

void CharacterBase::setCommand(CCNode *sender, void *data)
{
	auto file = (CCDictionary *)data;
	CCString *commandType = (CCString *)(file->objectForKey(1));

	if (is_same(commandType->getCString(), "addHP"))
	{
		if (_hpBar)
		{
			setHP(CCString::create(getMaxHP()->getCString()));
			_hpBar->loseHP(getHpPercent());
			_hpBar->setPositionY(getHeight());
		}
	}
	else if (is_same(commandType->getCString(), "setInvincible"))
	{
		_isInvincible = true;
	}
	else if (is_same(commandType->getCString(), "setGainCKR"))
	{
		uint32_t boundValue = 1500;
		if (_level >= 2)
		{
			if (45000 - getCkrValue() >= boundValue)
			{
				uint32_t newValue = getCkrValue() + boundValue;
				setCKR(to_ccstring(newValue));
			}
			else
			{
				setCKR(CCString::create("45000"));
			}

			if (getCkrValue() >= 15000)
				_isCanOugis1 = true;

			if (isPlayer())
				_delegate->setCKRLose(false);
		}

		if (_level >= 4 && !_isControlled)
		{
			if (50000 - getCkr2Value() >= boundValue)
			{
				uint32_t newValue = getCkr2Value() + boundValue;
				setCKR2(to_ccstring(newValue));
			}
			else
			{
				setCKR2(CCString::create("50000"));
			}

			if (getCkr2Value() >= 25000)
				_isCanOugis2 = true;

			if (isPlayer())
				_delegate->setCKRLose(true);
		}
	}
	else if (is_same(commandType->getCString(), "reInvincible"))
	{
		_isInvincible = false;
	}
	else if (is_same(commandType->getCString(), "setInvisible"))
	{
		setVisible(false);
		_isVisable = false;
	}
	else if (is_same(commandType->getCString(), "reInvisible"))
	{
		setVisible(true);
		_isVisable = true;
	}
	else if (is_same(commandType->getCString(), "setTransport2"))
	{
		CCObject *pObject;
		int tsPosX = getPositionX();
		int tsPosY = getPositionY();

		if (getMonsterArray() && _actionState != State::NATTACK)
		{
			CCARRAY_FOREACH(getMonsterArray(), pObject)
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

		setPosition(ccp(tsPosX, tsPosY));
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", this);

		_delegate->reorderChild(this, -tsPosY);
	}
	else if (is_same(commandType->getCString(), "setTransport"))
	{
		int tsPosX = getPositionX();
		int tsPosY = getPositionY();

		if (_mainTarget)
		{
			if (_mainTarget->_isFlipped)
			{
				setFlipX(true);
				_isFlipped = true;
			}
			else
			{
				setFlipX(false);
				_isFlipped = false;
			}
		}

		if (isCharacter("Sakura"))
		{
			float posY = getPositionY();
			if (!_originY)
			{
				if (posY == 0)
					posY = 0.1f;
				_originY = posY;
			}
			setPosition(ccp(getPositionX(), getPositionY() + 64));
			return;
		}
		else
		{
			if (_markPoint.x != 0)
			{
				_startPoint = ccp(tsPosX, tsPosY);
				tsPosX = _markPoint.x;
				tsPosY = _markPoint.y;
				_markPoint = ccp(0, 0);
			}
			else if (_startPoint.x != 0)
			{
				tsPosX = _startPoint.x;
				tsPosY = _startPoint.y;
				_startPoint = ccp(0, 0);
			}
		}

		setPosition(ccp(tsPosX, tsPosY));
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", this);

		if (isNotCharacter("Yominuma"))
		{
			_delegate->reorderChild(this, -tsPosY);
		}
	}
	else if (is_same(commandType->getCString(), "reTransport"))
	{
		setPosition(ccp(getPositionX(), _originY));
		_originY = 0;
	}
	else if (is_same(commandType->getCString(), "setDead"))
	{
		_isSuicide = true;
		dead();
	}
	else if (is_same(commandType->getCString(), "findTarget"))
	{
		if (notFindHero(0))
		{
			if (notFindFlog(0) ||
				isCharacter("RikudoNaruto", "SageNaruto"))
				_mainTarget = nullptr;
		}

		if (_mainTarget)
		{
			if (isCharacter("Dogs",
							"Yominuma",
							"SandBall",
							"Sabaku",
							"Yataikuzu",
							"Lee",
							"RockLee"))
			{
				_markPoint = ccp(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY());
			}
			else if (isCharacter("Tsukuyomi"))
			{
				_markPoint = ccp(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY() + 2);
			}
			else if (isCharacter("KageFeng"))
			{
				_markPoint = ccp(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY - 6 : _mainTarget->getPositionY() - 6);
			}
			else
			{
				_markPoint = ccp(_mainTarget->_isFlipped ? _mainTarget->getPositionX() + 32 : _mainTarget->getPositionX() - 32,
								 _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY());
			}
		}
	}
	else if (is_same(commandType->getCString(), "setRevive"))
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			auto tempHero = (Hero *)pObject;
			if (is_same(_group->getCString(), tempHero->_group->getCString()) && (tempHero->isPlayer() || tempHero->isCom()) && tempHero->_actionState == State::DEAD && tempHero->rebornSprite)
			{
				tempHero->unschedule(schedule_selector(Hero::reborn));
				tempHero->reborn(0.1f);
			}
		}
	}
	else if (is_same(commandType->getCString(), "setTrade"))
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			auto tempHero = (Hero *)pObject;
			if (tempHero->isPlayerOrCom() &&
				tempHero->_actionState == State::DEAD &&
				tempHero->rebornSprite &&
				tempHero->hearts > 0 &&
				tempHero->isNotCharacter("Kakuzu"))
			{
				CCPoint sp = ccpSub(tempHero->getPosition(), getPosition());
				if (abs(sp.x) <= 48 && abs(sp.y) <= 48)
				{
					tempHero->hearts -= 1;
					if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0)
					{
						uint32_t tempMaxHP = getMaxHPValue();
						tempMaxHP += 100;
						setnAttackValue(to_ccstring(getNAttackValue() + 5));
						setMaxHP(to_ccstring(tempMaxHP));

						if (_hpBar)
						{
							_hpBar->loseHP(getHpPercent());
						}
					}

					if (isPlayer())
					{
						if (_delegate->_isHardCoreGame)
						{
							getDelegate()->setCoin(to_cstr(50 + (tempHero->getLV() - 1) * 10));
							setCoinDisplay(50 + (tempHero->getLV() - 1) * 10);
							addCoin(50 + (tempHero->getLV() - 1) * 10);
						}
						else
						{
							getDelegate()->setCoin("50");
							setCoinDisplay(50);
							addCoin(50);
						}
					}
				}
			}
		}
	}
	else if (is_same(commandType->getCString(), "addExtern"))
	{
		auto tempArray = CCArray::create();

		int i = 1;
		if (isCharacter("Tenten"))
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
		auto call = CCCallFuncN::create(this, callfuncN_selector(CharacterBase::disableShadow));
		auto tempAction = CCAnimate::create(tempAnimation);
		auto list = CCArray::create();
		list->addObject(tempAction);
		list->addObject(call);
		auto seq = CCSequence::create(list);

		CCSprite *tempChar = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s_Extern_01.png", getCharacter()->getCString())->getCString());

		tempChar->setAnchorPoint(ccp(0.5f, 0));
		tempChar->setPosition(getPosition());
		_delegate->addChild(tempChar, -_originY);

		tempChar->runAction(seq);
	}
	else if (is_same(commandType->getCString(), "pauseJump"))
	{
		getActionManager()->addAction(_jumpUPAction, this, false);
	}
	else if (is_same(commandType->getCString(), "setCounter"))
	{
		bool _isCounter = false;
		if (hasMonsterArrayAny())
		{
			CCObject *pObject;
			CCARRAY_FOREACH(_monsterArray, pObject)
			{
				auto tempMonster = (CharacterBase *)pObject;
				float distanceX = ccpSub(tempMonster->getPosition(), getPosition()).x;
				float distanceY = ccpSub(tempMonster->getPosition(), getPosition()).y;
				if (abs(distanceX) < 40 && abs(distanceY) < 15)
				{
					_isCounter = true;
				}
			}
		}

		if (_isCounter)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
			{
				auto tempHero = (Hero *)pObject;
				if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0 && (tempHero->isPlayer() || tempHero->isCom()) && tempHero->_actionState != State::DEAD)
				{
					if (tempHero->_hpBar)
					{
						tempHero->_slayer = this;
						if (tempHero->getHPValue() <= 2000)
						{
							tempHero->setDamage("c_hit", tempHero->getHPValue(), false);
						}
						else
						{
							tempHero->setDamage("c_hit", 2000, false);
						}

						tempHero->_hpBar->loseHP(tempHero->getHpPercent());

						if (tempHero->isPlayer())
						{
							_delegate->setHPLose(tempHero->getHpPercent());
						}
					}
				}
			}
		}
		else
		{
			if (_hpBar)
			{
				_slayer = this;
				if (getHPValue() <= 2000)
				{
					setDamage("c_hit", getHPValue(), false);
				}
				else
				{
					setDamage("c_hit", 2000, false);
				}
				_hpBar->loseHP(getHpPercent());

				if (isPlayer())
				{
					_delegate->setHPLose(getHpPercent());
				}
			}
		}

		setActionResume();
	}
}

void CharacterBase::setBuff(CCNode *sender, void *data)
{
	int buffValue = *((int *)&data);
	float buffStayTime = _attackRangeY;

	if (is_same(_attackType->getCString(), "hBuff"))
	{
		_healBuffValue = buffValue;
		schedule(schedule_selector(CharacterBase::healBuff), 1);
		setBuffEffect("hBuff");
	}
	else if (is_same(_attackType->getCString(), "sBuff") ||
			 is_same(_attackType->getCString(), "rsBuff") ||
			 is_same(_attackType->getCString(), "hsBuff") ||
			 is_same(_attackType->getCString(), "dcBuff"))
	{
		_skillUPBuffValue = buffValue;
		scheduleOnce(schedule_selector(CharacterBase::disableBuff), buffStayTime);
		setBuffEffect(_attackType->getCString());

		setsAttackValue1(to_ccstring(getSAttackValue1() + _skillUPBuffValue));
		setsAttackValue2(to_ccstring(getSAttackValue2() + _skillUPBuffValue));
		setsAttackValue3(to_ccstring(getSAttackValue3() + _skillUPBuffValue));

		if (is_same(_attackType->getCString(), "hsBuff"))
		{
			CCObject *pObject;
			CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
			{
				auto tempHero = (CharacterBase *)pObject;
				if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0 && (tempHero->isPlayer() || tempHero->isCom()) && tempHero->_actionState != State::HURT && tempHero->_actionState != State::DEAD)
				{
					float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
					if (distanceX < winSize.width / 2)
					{
						if (!tempHero->_isVisable)
						{
							if (tempHero->isCharacter("Konan") ||
								tempHero->isCharacter("Deidara"))
							{
								tempHero->unschedule(schedule_selector(CharacterBase::disableBuff));
							}

							tempHero->setOpacity(255);
							tempHero->setVisible(true);
							tempHero->_isVisable = true;

							if (tempHero->_hpBar)
								tempHero->_hpBar->setVisible(true);
							if (tempHero->_shadow)
								tempHero->_shadow->setVisible(true);
						}
					}
				}
			}
			if (isCharacter("Neji"))
			{
				_isArmored = true;
			}
		}
	}
	else if (is_same(_attackType->getCString(), "cBuff"))
	{
		_skillChangeBuffValue = buffValue;

		if (isCharacter("Shino",
						"Sai",
						"Deidara"))
		{
			if (_skillChangeBuffValue == 17)
			{
				scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
			}
			else if (_skillChangeBuffValue == 18)
			{
				unschedule(schedule_selector(CharacterBase::resumeAction));
				setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
				scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
			}
		}
		else if (isCharacter("Kiba"))
		{
			if (_skillChangeBuffValue == 18)
			{
				scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
			}
		}
		else if ((isCharacter("ImmortalSasuke") ||
				  isCharacter("Sasuke")) &&
				 _skillChangeBuffValue == 18)
		{
			unschedule(schedule_selector(CharacterBase::resumeAction));
			unschedule(schedule_selector(CharacterBase::disableBuff));

			_isTaunt = false;
			setHurtAction(createAnimation(hurtArray, 10.0f, false, true));
			disableBuff(0);

			scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
		}
		else if (isCharacter("Minato"))
		{
			if (_skillChangeBuffValue == 18)
			{
				scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
			}
		}
		else
		{
			if (isNotGuardian() &&
				isNotCharacter("Kankuro",
							   "Chiyo",
							   "Hiruzen",
							   "Suigetsu,"
							   "Jugo",
							   "Kisame",
							   "Parents",
							   "Lee",
							   "RockLee"))
			{
				scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
			}
		}

		changeAction();
	}
	else if (is_same(_attackType->getCString(), "tBuff"))
	{
		_skillChangeBuffValue = buffValue;
		scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
		scheduleOnce(schedule_selector(CharacterBase::disableBuff), buffStayTime);
		setBuffEffect(_attackType->getCString());

		changeAction();
	}
	else if (is_same(_attackType->getCString(), "stBuff"))
	{
		if (isPlayer() || is_same(getGroup()->getCString(), _delegate->currentPlayer->getGroup()->getCString()))
			setOpacity(150);
		else
			setVisible(false);

		if (_hpBar)
			_hpBar->setVisible(false);

		if (_shadow)
			_shadow->setVisible(false);

		_isVisable = false;
		scheduleOnce(schedule_selector(CharacterBase::disableBuff), buffStayTime);
	}
	else if (is_same(_attackType->getCString(), "GroupHeal") ||
			 is_same(_attackType->getCString(), "GroupBuff"))
	{
		if (_healBuffValue)
			_healBuffValue += buffValue;
		else
			_healBuffValue = buffValue;

		schedule(schedule_selector(CharacterBase::healBuff), 1);
	}

	if (isPlayer())
		_delegate->getHudLayer()->setBuffDisplay(_attackType->getCString(), buffStayTime);
}

void CharacterBase::setBuffEffect(const char *type)
{
	if (_skillBuffEffect)
	{
		_skillBuffEffect->removeFromParent();
		_skillBuffEffect = nullptr;
	}

	if (_healBuffEffect)
	{
		_healBuffEffect->removeFromParent();
		_healBuffEffect = nullptr;
	}

	if (is_same(type, "hBuff"))
	{
		_healBuffEffect = Effect::create(type, this);
		addChild(_healBuffEffect);
	}
	else if (is_same(type, "hsBuff"))
	{
		_skillBuffEffect = Effect::create(type, this);
		_skillBuffEffect->setPositionY(14);
		addChild(_skillBuffEffect);
	}
	else if (is_same(type, "tBuff") ||
			 is_same(type, "dcBuff") ||
			 is_same(type, "jdBuff") ||
			 is_same(type, "bmBuff"))
	{
		_skillBuffEffect = Effect::create(type, this);
		addChild(_skillBuffEffect);
	}
	else if (is_same(type, "dhBuff"))
	{
		_dehealBuffEffect = Effect::create(type, this);
		addChild(_dehealBuffEffect);
	}
	else if (is_same(type, "sBuff"))
	{
		_skillBuffEffect = Effect::create(type, this);
		addChild(_skillBuffEffect);
	}
}

void CharacterBase::removeBuffEffect(const char *type)
{
	if (is_same(type, "hBuff") && _healBuffEffect)
	{
		_healBuffEffect->removeFromParent();
		_healBuffEffect = nullptr;
	}
	else if (is_same(type, "sBuff") && _skillBuffEffect)
	{
		_skillBuffEffect->removeFromParent();
		_skillBuffEffect = nullptr;
	}
	else if (is_same(type, "dhBuff") && _dehealBuffEffect)
	{
		_dehealBuffEffect->removeFromParent();
		_dehealBuffEffect = nullptr;
	}

	else if (is_same(type, "all"))
	{
		if (_healBuffEffect)
		{
			_healBuffEffect->removeFromParent();
			_healBuffEffect = nullptr;
			_healBuffValue = 0;
			_buffStartTime = 0;
		}
		if (_powerBuffEffect)
		{
			_powerBuffEffect->removeFromParent();
			_powerBuffEffect = nullptr;
		}
		if (_skillBuffEffect)
		{
			_skillBuffEffect->removeFromParent();
			_skillBuffEffect = nullptr;
		}
		if (_dehealBuffEffect)
		{
			_dehealBuffEffect->removeFromParent();
			_dehealBuffValue = 0;
			_dehealBuffEffect = nullptr;
			_debuffStartTime = 0;
		}
	}
}

void CharacterBase::disableBuff(float dt)
{
	if (_skillUPBuffValue)
	{
		setsAttackValue1(to_ccstring(getSAttackValue1() - _skillUPBuffValue));
		setsAttackValue2(to_ccstring(getSAttackValue2() - _skillUPBuffValue));
		setsAttackValue3(to_ccstring(getSAttackValue3() - _skillUPBuffValue));
		_skillUPBuffValue = 0;

		if (isCharacter("Neji"))
		{
			_isArmored = false;
		}
		removeBuffEffect("sBuff");
	}
	else if (_skillBuffEffect)
	{
		removeBuffEffect("sBuff");
	}
	else if (!_isVisable && _actionState != State::HURT)
	{
		setOpacity(255);
		setVisible(true);
		_isVisable = true;

		if (_hpBar)
			_hpBar->setVisible(true);
		if (_shadow)
			_shadow->setVisible(true);
	}
	else if (_skillChangeBuffValue && isCharacter("Tobi"))
	{
		setOpacity(255);
	}
}

void CharacterBase::disableDebuff(float dt)
{
	if (isCharacter("ImmortalSasuke", "Itachi") &&
		_isArmored)
	{
		return;
	}

	if (getWalkSpeed() == 112)
		setWalkSpeed(224);
}

void CharacterBase::healBuff(float dt)
{
	cc_timeval timeVal;
	CCTime::gettimeofdayCocos2d(&timeVal, 0);
	float curTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;

	if (!_buffStartTime)
	{
		_buffStartTime = curTime;
	}
	int limitTime = 10000;
	if (isCharacter("Tsunade"))
	{
		limitTime = 15000;
	}

	if (_buffStartTime && curTime - _buffStartTime >= limitTime)
	{
		unschedule(schedule_selector(CharacterBase::healBuff));
		removeBuffEffect("hBuff");
		_healBuffValue = 0;
		_buffStartTime = 0;
		return;
	}
	if (isCharacter("Karin"))
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			auto tempHero = (Hero *)pObject;
			if (is_same(_group->getCString(), tempHero->_group->getCString()) && (tempHero->isPlayer() || tempHero->isCom()) && tempHero->_actionState != State::DEAD)
			{
				float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
				float tempRange1 = 128 + getContentSize().width / 2;
				if (abs(distanceX) <= tempRange1 &&
					abs(tempHero->getPositionY() - getPositionY()) <= 128)
				{
					if (tempHero->getMaxHPValue() - tempHero->getHPValue() <= _healBuffValue)
					{
						tempHero->setHP(CCString::create(tempHero->getMaxHP()->getCString()));
						if (tempHero->_hpBar)
							tempHero->_hpBar->loseHP(tempHero->getHpPercent());
					}
					else
					{
						tempHero->setHP(to_ccstring(tempHero->getHPValue() + _healBuffValue));
						if (tempHero->_hpBar)
							tempHero->_hpBar->loseHP(tempHero->getHpPercent());
					}

					if (tempHero->isPlayer())
						_delegate->setHPLose(tempHero->getHpPercent());

					if (tempHero->_isVisable)
					{
						Effect *tmpEffect = Effect::create("Kagura", tempHero);
						if (tempHero->isPlayer())
						{
							tmpEffect->setOpacity(150);
						}
						tmpEffect->setPosition(ccp(tempHero->getContentSize().width / 2, tempHero->getContentSize().height / 2));
						tempHero->addChild(tmpEffect);
					}
				}
			}
		}
	}
	else if (isCharacter("Chiyo"))
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			auto tempHero = (Hero *)pObject;
			if (is_same(_group->getCString(), tempHero->_group->getCString()) &&
				tempHero->isPlayerOrCom() &&
				tempHero->isNotCharacter("Chiyo"))
			{
				CCPoint sp = ccpSub(tempHero->getPosition(), getPosition());
				if (abs(sp.x) <= winSize.width / 2)
				{
					if (tempHero->_level >= 2)
					{
						if (45000 - tempHero->getCkrValue() >= _healBuffValue)
						{
							float newValue = tempHero->getCkrValue() + _healBuffValue;
							tempHero->setCKR(to_ccstring(newValue));
						}
						else
						{
							tempHero->setCKR(CCString::create("45000"));
						}

						if (tempHero->getCkrValue() >= 15000)
							tempHero->_isCanOugis1 = true;

						if (tempHero->isPlayer())
							_delegate->setCKRLose(false);
					}

					if (tempHero->_level >= 4)
					{
						if (50000 - tempHero->getCkr2Value() >= _healBuffValue)
						{
							float newValue = tempHero->getCkr2Value() + _healBuffValue;
							tempHero->setCKR2(to_ccstring(newValue));
						}
						else
						{
							tempHero->setCKR2(CCString::create("50000"));
						}

						if (tempHero->getCkr2Value() >= 25000)
							tempHero->_isCanOugis2 = true;

						if (tempHero->isPlayer())
							tempHero->_delegate->setCKRLose(true);
					}

					if (tempHero->_isVisable)
					{
						Effect *tmpEffect = Effect::create("Hupo", tempHero);
						if (tempHero->isPlayer())
						{
							tmpEffect->setOpacity(150);
						}
						tmpEffect->setPosition(ccp(tempHero->getContentSize().width / 2, tempHero->getContentSize().height / 2 + 6));
						tempHero->addChild(tmpEffect);
					}
				}
			}
		}
	}
	else if (isCharacter("Slug"))
	{
		CCObject *pObject;
		CCArray *list;

		if (isAkatsukiGroup())
			list = _delegate->_AkatsukiFlogArray;
		else
			list = _delegate->_KonohaFlogArray;

		CCARRAY_FOREACH(list, pObject)
		{
			auto tempHero = (CharacterBase *)pObject;
			if (is_same(_group->getCString(), tempHero->_group->getCString()) && tempHero->_actionState != State::DEAD)
			{
				float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
				float tempRange1 = 128 + getContentSize().width / 2;
				if (abs(distanceX) <= tempRange1 &&
					abs(tempHero->getPositionY() - getPositionY()) <= 128)
				{
					if (tempHero->getMaxHPValue() - tempHero->getHPValue() <= _healBuffValue)
					{
						tempHero->setHP(CCString::create(tempHero->getMaxHP()->getCString()));
						if (tempHero->_hpBar)
							tempHero->_hpBar->loseHP(tempHero->getHpPercent());
					}
					else
					{
						tempHero->setHP(to_ccstring(tempHero->getHPValue() + int(_healBuffValue)));
						if (tempHero->_hpBar)
							tempHero->_hpBar->loseHP(tempHero->getHpPercent());
					}
				}
			}
		}
	}
	else if (isCharacter("Sakura", "Tsunade"))
	{
		if (getMaxHPValue() - getHPValue() <= _healBuffValue)
		{
			setHP(CCString::create(_maxHP->getCString()));
			if (_hpBar)
				_hpBar->loseHP(getHpPercent());
		}
		else
		{
			setHP(to_ccstring(getHPValue() + _healBuffValue));
			if (_hpBar)
				_hpBar->loseHP(getHpPercent());
		}
		if (_role && isPlayer())
		{
			_delegate->setHPLose(getHpPercent());
		}
	}
}

void CharacterBase::dehealBuff(float dt)
{
	cc_timeval timeVal;
	CCTime::gettimeofdayCocos2d(&timeVal, 0);
	float curTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;

	if (!_debuffStartTime)
		_debuffStartTime = curTime;

	if (_debuffStartTime && abs(_debuffStartTime - curTime) > 10000)
	{
		unschedule(schedule_selector(CharacterBase::dehealBuff));
		setWalkSpeed(_originSpeed);
		removeBuffEffect("dhBuff");
		_dehealBuffValue = 0;
		_debuffStartTime = 0;
		return;
	}

	CCObject *pObject;
	CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
	{
		auto tempHero = (Hero *)pObject;
		if (tempHero->isCharacter("Asuma"))
			_slayer = tempHero;
	}

	if (getHPValue() <= _dehealBuffValue)
		setDamage("c_hit", _dehealBuffValue, false);
	else
		setDamage("c_hit", _dehealBuffValue, false);

	if (_hpBar)
		_hpBar->loseHP(getHpPercent());

	if (isPlayer())
		_delegate->setHPLose(getHpPercent());
}

// NOTE: Only for Shikamaru's KageHand
void CharacterBase::lostBlood(float dt)
{
	CCObject *pObject;
	CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
	{
		auto tempHero = (Hero *)pObject;
		if (tempHero->isCharacter("Shikamaru"))
			_slayer = tempHero;
	}

	if (getHPValue() <= lostBloodValue)
		setDamage("c_hit", lostBloodValue, false);
	else
		setDamage("c_hit", lostBloodValue, false);

	if (_hpBar)
		_hpBar->loseHP(getHpPercent());

	if (isPlayer())
		_delegate->setHPLose(getHpPercent());
}

void CharacterBase::removeLostBlood(float dt)
{
	lostBloodValue = 0;
	unschedule(schedule_selector(CharacterBase::lostBlood));
}

void CharacterBase::changeAction()
{
}

void CharacterBase::changeAction2()
{
	if (isCharacter("Minato"))
	{
		_attackValue = getSpcAttackValue2();
		setAttackType(getspcAttack2Type());
		_attackRangeX = _spcattackRangeX2;
		_attackRangeY = _spcattackRangeY2;

		setSkill2Action(createAnimation(skillSPC2Array, 10.0f, false, true));
	}
}

// Release catched characters
void CharacterBase::reCatched(float dt)
{
	setVisible(true);
	_isVisable = true;

	if (_shadow)
		_shadow->setVisible(true);
}

void CharacterBase::resumeAction(float dt)
{
	_skillChangeBuffValue = 0;
}

void CharacterBase::setActionResume()
{
}

void CharacterBase::setActionResume2()
{
	if (isCharacter("Minato"))
	{
		setSkill2Action(createAnimation(skill2Array, 10.0f, false, true));
	}
}

void CharacterBase::getCollider()
{
	schedule(schedule_selector(CharacterBase::stopMove), 0.0f);
}

void CharacterBase::stopMove(float dt)
{
	if (getPositionX() <= _delegate->currentMap->getTileSize().width ||
		getPositionX() >= (_delegate->currentMap->getMapSize().width - 1) * _delegate->currentMap->getTileSize().width)
	{
		unschedule(schedule_selector(CharacterBase::stopMove));
		getActionManager()->removeAction(_moveAction);
		return;
	}

	CCObject *pObject;
	CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
	{
		auto tempHero = (Hero *)pObject;
		if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0 && tempHero->_isVisable && tempHero->_actionState != State::DEAD && tempHero->_actionState != State::JUMP && !tempHero->_isInvincible)
		{
			float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
			float tempRange1 = _attackRangeX + getContentSize().width / 2;
			if (abs(distanceX) <= tempRange1 &&
				abs(tempHero->getPositionY() - getPositionY()) <= _attackRangeY)
			{
				unschedule(schedule_selector(CharacterBase::stopMove));
				getActionManager()->removeAction(_moveAction);
				return;
			}
		}
	}
}

void CharacterBase::stopJump(CCNode *sender, void *data)
{
	int stopTime = *((int *)&data);

	if (_actionState == State::JUMP)
	{
		getActionManager()->pauseTarget(this);
		scheduleOnce(schedule_selector(CharacterBase::resumePauseStuff), float(stopTime) / 100);
	}
}

void CharacterBase::setBullet(CCNode *sender, void *data)
{
	auto file = (CCDictionary *)data;
	CCString *str = (CCString *)(file->objectForKey(1));
	CCString *bulletType = str;

	Bullet *bullet = Bullet::create();
	bullet->setDelegate(_delegate);
	bullet->setID(bulletType, CCString::create("Bullet"), _group);
	bullet->idle();
	if (_master)
	{
		bullet->_master = _master;
	}
	else
	{
		bullet->_master = this;
	}

	if (_isFlipped)
	{
		bullet->setFlipX(true);
		bullet->_isFlipped = true;
	}

	_delegate->addChild(bullet, -getPositionY());

	if (is_same(bulletType->getCString(), "PaperSrk"))
	{
		bullet->setScale(0.8f);
		bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32),
								getPositionY() + 52));
		bullet->attack(NAttack);
		bullet->setMove(192, 2.0f, false);
	}
	else if (is_same(bulletType->getCString(), "PaperSpear"))
	{
		bullet->setScale(0.8f);
		bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -68 : 68),
								getPositionY() + 42));
		bullet->attack(NAttack);
		bullet->setMove(192, 2.0f, false);
	}
	else if (is_same(bulletType->getCString(), "HugeSRK"))
	{
		float rangeX = 76;

		bullet->setScale(0.8f);
		bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -rangeX : rangeX),
								getPositionY() + getHeight() / 2));
		if (_skillUPBuffValue)
		{
			bullet->setnAttackValue(to_ccstring(bullet->getNAttackValue() + _skillUPBuffValue));
		}

		bullet->scheduleOnce(schedule_selector(Bullet::setAttack), 0.5f);
		scheduleOnce(schedule_selector(CharacterBase::setBulletGroup), 0.2f);
		bullet->setEaseIn(224, 5.0f);
	}
	else if (is_same(bulletType->getCString(), "FlyKnife") ||
			 is_same(bulletType->getCString(), "TentenSRK"))
	{
		bullet->setScale(0.8f);
		bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32),
								getPositionY() + getHeight() / 2));

		bullet->setEaseIn(224, 2.0f);
		bullet->attack(NAttack);
	}
	else if (is_same(bulletType->getCString(), "HiraishinKunai") ||
			 is_same(bulletType->getCString(), "Shintenshin"))
	{
		if (!_monsterArray)
		{
			_monsterArray = CCArray::create();
			_monsterArray->retain();
		}
		if (is_same(bulletType->getCString(), "HiraishinKunai"))
		{
			bullet->setScale(0.8f);
			bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -42 : 42),
									getPositionY() + getHeight() / 2));
		}
		else
		{
			bullet->setAnchorPoint(ccp(0.5f, 0));
			bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -42 : 42),
									getPositionY()));
		}

		bullet->_originY = getPositionY();
		bullet->setEaseIn(196, 2.0f);
		bullet->attack(NAttack);
		_monsterArray->addObject(bullet);
	}
	else
	{
		bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32),
								getPositionY() + getContentSize().height / 2));

		bullet->attack(NAttack);
		bullet->setMove(192, 2.0f, false);
	}
}

void CharacterBase::setBulletGroup(float dt)
{
	for (int i = 0; i < 2; i++)
	{
		Bullet *bullet = Bullet::create();
		bullet->setDelegate(_delegate);
		float rangeX = 0;

		bullet->setID(CCString::create("HugeSRK"), CCString::create("Bullet"), _group);
		rangeX = 76;

		bullet->_master = this;
		bullet->setScale(0.8f);

		if (_isFlipped)
		{
			bullet->setFlipX(true);
			bullet->_isFlipped = true;
		}
		if (i == 0)
		{
			CCPoint location = ccp(getPositionX() + (_isFlipped ? -rangeX : rangeX), getPositionY() + (getHeight() / 2 + 23));
			bullet->setPosition(location);
		}
		else
		{
			CCPoint location = ccp(getPositionX() + (_isFlipped ? -rangeX : rangeX), getPositionY() + (getHeight() / 2 - 23));
			bullet->setPosition(location);
		}
		_delegate->addChild(bullet, currentSkillTag);
		bullet->idle();
		if (_skillUPBuffValue)
		{
			bullet->setnAttackValue(to_ccstring(bullet->getNAttackValue() + _skillUPBuffValue));
		}

		bullet->scheduleOnce(schedule_selector(Bullet::setAttack), 0.5f);
		bullet->setEaseIn(352, 5.0f);
	}
}

Hero *CharacterBase::createClone(int cloneTime)
{
	return nullptr;
}

void CharacterBase::setClone(CCNode *sender, void *data)
{
	int cloneTime = *((int *)&data);
	auto clone = createClone(cloneTime);
	if (!clone)
	{
		CCLOG("Current character %s can not create clone", _character->getCString());
		return;
	}

	if (_master)
	{
		clone->setMaster(this);
		clone->setSecMaster(_master);
	}
	else
	{
		clone->setMaster(this);
	}

	clone->setDelegate(_delegate);
	clone->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32), getPositionY() - 1));

	if (isCharacter("SageNaruto", "Naruto") ||
		(isCharacter("RikudoNaruto") && cloneTime == 10))
	{
		clone->setHP(CCString::create(getHP()->getCString()));
	}
	else
	{
		clone->setHP(CCString::create(getMaxHP()->getCString()));
	}

	clone->setMaxHP(CCString::create(getMaxHP()->getCString()));
	clone->_exp = _exp;
	clone->setnAttackValue(to_ccstring(getNAttackValue()));
	clone->_gardValue = _gardValue;
	clone->_level = _level;
	clone->setHPbar();
	clone->_hpBar->getHPBAR()->setScaleX(clone->getHpPercent());

	if (isCharacter("RikudoNaruto") && cloneTime == 9)
	{
		if (clone->_hpBar)
		{
			clone->_hpBar->setPositionY(120);
		}
		clone->setnAttackValue(CCString::createWithFormat("1060"));
	}
	else if (isCharacter("Kakashi"))
	{
		clone->setnAttackValue(CCString::createWithFormat("1060"));
	}

	if (hasArmorBroken)
	{
		clone->hasArmorBroken = true;
	}

	if (hasArmor)
	{
		clone->hasArmor = true;
	}

	clone->setFlipX(_isFlipped);
	clone->_isFlipped = _isFlipped;
	auto callValue = CCDictionary::create();
	callValue->setObject(CCString::create("smk"), 1);
	clone->setSkillEffect(clone, callValue);
	clone->idle();
	_delegate->_CharacterArray->addObject(clone);
	_delegate->addChild(clone, -clone->getPositionY());
	clone->doAI();

	if (cloneTime > 0)
	{
		clone->scheduleOnce(schedule_selector(Hero::removeClone), float(cloneTime));
	}
}

void CharacterBase::removeClone(float dt)
{
	dead();
}

void CharacterBase::setMon(CCNode *sender, void *data)
{
	auto file = (CCDictionary *)data;
	CCString *monsterType = (CCString *)(file->objectForKey(1));
	const char *monsterName = monsterType->getCString();
	float monsterStayTime = _attackRangeY;

	if (!_monsterArray)
	{
		_monsterArray = CCArray::create();
		_monsterArray->retain();
	}

	auto monster = Monster::create();
	monster->setDelegate(_delegate);

	monster->setID(monsterType, CCString::create(kRoleMon), _group);

	if (getMaster())
	{
		if (getSecMaster())
		{
			monster->setMaster(this);
			monster->setSecMaster(getSecMaster());
		}
		else
		{
			monster->setMaster(getMaster());
			monster->setSecMaster(this);
		}
	}
	else
	{
		monster->setMaster(this);
	}

	monster->idle();
	monster->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32), _originY ? _originY : getPositionY()));
	monster->setFlipX(_isFlipped);
	monster->_isFlipped = _isFlipped;

	if (is_same(monsterName, "FakeDeidara") ||
		is_same(monsterName, "FakeKisame") ||
		is_same(monsterName, "DeidaraBom") ||
		is_same(monsterName, "ChuiDi") ||
		is_same(monsterName, "SakuraBom") ||
		is_same(monsterName, "Shoryu") ||
		is_same(monsterName, "Stream") ||
		is_same(monsterName, "FakeMinato"))
	{
		monster->setPosition(ccp(getPositionX(), _originY ? _originY : getPositionY()));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "LeeBom"))
	{
		//monster->setAnchorPoint(ccp(0.5,0.5f));
		monster->setPosition(ccp(getPositionX(), getPositionY()));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "FakeItachi"))
	{
		monster->setPosition(ccp(getPositionX(), _originY ? _originY : getPositionY() - 4));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "Tenmu"))
	{
		monster->setPosition(ccp(getPositionX(), _originY));
		monster->setAnchorPoint(ccp(0.5, -0.1f));
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "Kaiten"))
	{
		monster->setPosition(ccp(getPositionX(), getPositionY()));
		monster->setAnchorPoint(ccp(0.5, 0.25f));
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "Crash") ||
			 is_same(monsterName, "Crash2"))
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32), _originY ? _originY : getPositionY()));
		monster->setAnchorPoint(ccp(0.5, 0.25f));
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "SansyoRed"))
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 240 : getPositionX() + 240, getPositionY() - 32));
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "SansyoGreen"))
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 144 : getPositionX() + 144, getPositionY() - 32 + 1));
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "SansyoBlue"))
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 48 : getPositionX() + 48, getPositionY() - 32 + 2));
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "SmallSlug"))
	{
		if (_monsterArray && _monsterArray->count() < 3)
		{
			auto callValue = CCDictionary::create();
			callValue->setObject(CCString::create("smk"), 1);
			monster->setSkillEffect(monster, callValue);
			_monsterArray->addObject(monster);
			monster->doAI();
		}
		else
		{
			monster = nullptr;
			return;
		}
	}
	else if (is_same(monsterName, "Kuroari"))
	{
		auto callValue = CCDictionary::create();
		callValue->setObject(CCString::create("smk"), 1);
		monster->setSkillEffect(monster, callValue);
		_monsterArray->addObject(monster);
		monster->doAI();
	}
	else if (is_same(monsterName, "PaperRain") ||
			 is_same(monsterName, "Steam"))
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 16 : getPositionX() + 16, _originY));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "FireRain"))
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 75 : getPositionX() + 75, _originY - 1));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "Tuji") ||
			 is_same(monsterName, "Tuji2") ||
			 is_same(monsterName, "Suiji"))
	{
		monster->setPositionY(getPositionY() - 24);
		monster->setPositionX(getPositionX() + (_isFlipped ? -64 : 64));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "ThunderWave"))
	{
		monster->setPosition(ccp(getPositionX(), getPositionY() - 1));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "Jibaku") ||
			 is_same(monsterName, "JibakuEX") ||
			 is_same(monsterName, "Shenwei"))
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -96 : 96), getPositionY()));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "Bikyu"))
	{
		monster->setFlipX(_isFlipped);
		monster->hasArmorBroken = true;
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -(16 + getContentSize().width) : (16 + getContentSize().width)), getPositionY() - 32));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "Qilin"))
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -4 : 4), getPositionY() - 6));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "SuiRyuDan") ||
			 is_same(monsterName, "TodonPillar") ||
			 is_same(monsterName, "Yataikuzu") ||
			 is_same(monsterName, "Yominuma") ||
			 is_same(monsterName, "Dogs") ||
			 is_same(monsterName, "SandHand") ||
			 is_same(monsterName, "KageFeng") ||
			 is_same(monsterName, "Sanbao") ||
			 is_same(monsterName, "SandBall") ||
			 is_same(monsterName, "Sabaku") ||
			 is_same(monsterName, "SandWave") ||
			 is_same(monsterName, "Tsukuyomi") ||
			 is_same(monsterName, "Shark"))
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped == true ? -48 : 48), getPositionY() - 4));
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "Suijin") ||
			 is_same(monsterName, "BugPillar"))
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped == true ? -64 : 64), getPositionY() + 1));
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "Mine"))
	{
		auto callValue = CCDictionary::create();
		callValue->setObject(CCString::create("smk"), 1);
		monster->setSkillEffect(monster, callValue);
		_monsterArray->addObject(monster);
		monster->doAI();
		if (strcmp(getGroup()->getCString(), _delegate->currentPlayer->getGroup()->getCString()) != 0)
		{
			monster->setVisible(false);
		}
	}
	else if (is_same(monsterName, "Kage"))
	{
		_isCatchOne = true;
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -getContentSize().width / 2 + 4 : getContentSize().width / 2 - 4), getPositionY()));
		if (_isFlipped)
		{
			monster->setAnchorPoint(ccp(1, 0));
		}
		else
		{
			monster->setAnchorPoint(ccp(0, 0));
		}

		stopAllActions();
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
		monster->doAI();
	}
	else if (is_same(monsterName, "KageHand"))
	{
		CCPoint dir = CCPointMake(_isFlipped ? getPositionX() - getContentSize().width : getPositionX() + getContentSize().width, getPositionY());
		monster->setPosition(dir);
		stopAllActions();

		if (getMaster())
		{
			_master->_monsterArray->addObject(monster);
		}
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "KageHands"))
	{
		if (getMaster())
		{
			_master->_monsterArray->addObject(monster);
		}

		monster->setPosition(ccp(getPositionX(), getPositionY()));
		monster->setAnchorPoint(ccp(0.5f, 0.15f));
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "QuanRen"))
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 64 : getPositionX() + 64, _originY));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (is_same(monsterName, "ItachiSusano") ||
			 is_same(monsterName, "SasukeSusano"))
	{
		_monsterArray->addObject(monster);
	}
	else if (is_same(monsterName, "HiraishinMark"))
	{
		_monsterArray->addObject(monster);
		_isCanSkill1 = true;
	}
	else if (is_same(monsterName, "CircleMark"))
	{
		monster->setPosition(ccp(getPositionX(), getPositionY()));
		monster->setAnchorPoint(ccp(0.5f, 0.5f));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);

		if (isPlayer())
		{
			_delegate->getHudLayer()->skill1Button->setLock();
		}
	}
	else if (is_same(monsterName, "InkDragon"))
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 128 : getPositionX() + 128, getPositionY()));
		monster->attack(NAttack);
		monster->setDirectMove(156, 2.0f, false);
	}
	else if (is_same(monsterName, "BugTomado"))
	{
		monster->attack(NAttack);
		monster->setDirectMove(128, 2.0f, false);
	}
	else if (is_same(monsterName, "FudonSRK2") ||
			 is_same(monsterName, "FudonSRK"))
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped == true ? -48 : 48), getPositionY()));

		monster->attack(NAttack);
		bool isFollow = false;
		CCPoint moveDirection;
		if (_mainTarget)
		{
			if (_mainTarget->getPositionX() > getPositionX() && !_isFlipped)
			{
				isFollow = true;
			}
			else if (_mainTarget->getPositionX() <= getPositionX() && _isFlipped)
			{
				isFollow = true;
			}
		}

		if (isFollow)
		{
			monster->_mainTarget = _mainTarget;
			monster->doAI();
		}
		else
		{
			if (_isFlipped)
			{
				moveDirection = ccpNormalize(ccp(-1, 0));
			}
			else
			{
				moveDirection = ccpNormalize(ccp(1, 0));
			}
			monster->setActionState(State::WALK);
			monster->walk(moveDirection);
		}
	}
	else if (is_same(monsterName, "Kubi"))
	{
		monster->attack(NAttack);
		monster->setDirectMove(128, 0.8f, true);
	}
	else if (is_same(monsterName, "Shark2"))
	{
		monster->attack(NAttack);
		monster->setEaseIn(224, 3.0f);
	}
	else if (is_same(monsterName, "WaterBullet") ||
			 is_same(monsterName, "BoneBullet") ||
			 is_same(monsterName, "WaterBom"))
	{
		monster->attack(NAttack);
		monster->setEaseIn(224, 1.0f);
	}
	else if (is_same(monsterName, "Hasan"))
	{
		monster->attack(NAttack);
		monster->setAnchorPoint(ccp(0.5f, 0.28f));
		monster->setPosition(ccp(getPositionX() + (_isFlipped == true ? -24 : 24), getPositionY()));
		monster->setEaseIn(224, 1.0f);
	}
	else if (is_same(monsterName, "Wave"))
	{
		monster->attack(NAttack);
		monster->setAnchorPoint(ccp(0.5f, 0.1f));
		monster->setPosition(ccp(getPositionX() + (_isFlipped == true ? -24 : 24), getPositionY()));
		monster->setEaseIn(224, 1.0f);
	}
	else if (is_same(monsterName, "InkBird") ||
			 is_same(monsterName, "FakeTobirama") ||
			 is_same(monsterName, "TamaBomb") ||
			 is_same(monsterName, "Shenwei2"))
	{
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else
	{
		_monsterArray->addObject(monster);
		monster->doAI();
	}

	if (is_same(monsterName, "ItachiSusano"))
	{
		monster->setFlipX(_isFlipped);
		monster->setAnchorPoint(ccp(0.5f, 0));
		monster->setPosition(ccp(146 / 2 - 10, -40));
		addChild(monster, -1000);
	}
	else if (is_same(monsterName, "SasukeSusano"))
	{
		monster->setFlipX(_isFlipped);
		monster->setAnchorPoint(ccp(0.5f, 0));
		monster->setPosition(ccp(141 / 2, -6));
		addChild(monster, -1000);
	}
	else if (is_same(monsterName, "CircleMark") ||
			 is_same(monsterName, "Yominuma"))
	{
		_delegate->addChild(monster, -5000);
	}
	else
	{
		_delegate->addChild(monster, -monster->getPositionY());
	}
}

void CharacterBase::setMonPer(float dt)
{
	if (!_monsterArray)
	{
		_monsterArray = CCArray::create();
		_monsterArray->retain();
	}

	auto monster = Monster::create();
	monster->setDelegate(_delegate);

	if (isCharacter("Deidara"))
	{
		monster->setID(CCString::create("Spider"), CCString::create(kRoleMon), _group);
	}
	else if (isCharacter("Sai"))
	{
		monster->setID(CCString::create("Mouse"), CCString::create(kRoleMon), _group);
		auto callValue2 = CCDictionary::create();
		callValue2->setObject(CCString::create("Audio/Sai/ink_mouse.ogg"), 1);
		setSound(this, callValue2);
	}

	monster->setMaster(this);

	monster->idle();
	monster->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32), _originY ? _originY : getPositionY()));
	monster->setFlipX(_isFlipped);
	monster->_isFlipped = _isFlipped;

	_monsterArray->addObject(monster);
	monster->doAI();

	_delegate->addChild(monster, -monster->getPositionY());
}

void CharacterBase::setTrap(CCNode *sender, void *data)
{
	auto file = (CCDictionary *)data;
	CCString *trapType = (CCString *)(file->objectForKey(1));

	if (is_same(trapType->getCString(), "Amaterasu"))
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			auto tempHero = (CharacterBase *)pObject;
			if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0 && (tempHero->isPlayer() || tempHero->isCom()) && tempHero->_actionState != State::HURT && tempHero->_actionState != State::DEAD)
			{
				float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
				if (distanceX < winSize.width / 2)
				{
					if (!tempHero->_isVisable)
					{
						if (tempHero->isCharacter("Konan") ||
							tempHero->isCharacter("Deidara"))
						{
							tempHero->unschedule(schedule_selector(CharacterBase::disableBuff));
						}

						tempHero->setOpacity(255);
						tempHero->setVisible(true);
						tempHero->_isVisable = true;

						if (tempHero->_hpBar)
							tempHero->_hpBar->setVisible(true);
						if (tempHero->_shadow)
							tempHero->_shadow->setVisible(true);
					}
				}
			}
		}

		if (isCharacter("ImmortalSasuke"))
		{
			CCPoint targetPoint = _mainTarget ? _mainTarget->getPosition() : getPosition();

			for (int z = 0; z < 3; z++)
			{
				if (z == 0)
				{
					Bullet *trap = Bullet::create();
					trap->setDelegate(_delegate);
					trap->_master = this;
					trap->setID(trapType, CCString::create(kRoleMon), _group);
					trap->setAnchorPoint(ccp(0.5, 0));
					trap->setPosition(ccp(targetPoint.x, targetPoint.y + 32));
					trap->idle();
					trap->attack(NAttack);
					trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 4.0f);
					_delegate->addChild(trap, -trap->getPositionY());
				}
				else if (z == 1)
				{
					for (int i = 0; i < 3; i++)
					{
						Bullet *trap = Bullet::create();
						trap->setDelegate(_delegate);
						trap->_master = this;
						trap->setID(trapType, CCString::create(kRoleMon), _group);
						trap->setAnchorPoint(ccp(0.5, 0));
						trap->setPosition(ccp(targetPoint.x + (i - 1) * 60, targetPoint.y));
						trap->idle();
						trap->attack(NAttack);
						trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 4.0f);
						_delegate->addChild(trap, -trap->getPositionY());
					}
				}
				else if (z == 2)
				{
					Bullet *trap = Bullet::create();
					trap->setDelegate(_delegate);
					trap->_master = this;
					trap->setID(trapType, CCString::create(kRoleMon), _group);
					trap->setAnchorPoint(ccp(0.5, 0));
					trap->setPosition(ccp(targetPoint.x, targetPoint.y - 32));
					trap->idle();
					trap->attack(NAttack);
					trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 4.0f);
					_delegate->addChild(trap, -trap->getPositionY());
				}
			}
			return;
		}

		for (int z = 0; z < 3; z++)
		{
			if (z == 0)
			{
				for (int i = 0; i < 3; i++)
				{
					Bullet *trap = Bullet::create();
					trap->setDelegate(_delegate);
					trap->_master = this;
					trap->setID(trapType, CCString::create(kRoleMon), _group);

					trap->setPosition(ccp(getPositionX() + (_isFlipped ? -112 : 112), getPositionY() + (48 - i * 24)));
					trap->idle();
					trap->attack(NAttack);
					trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 2.5f);
					_delegate->addChild(trap, -trap->getPositionY());
				}
			}
			else if (z == 1)
			{
				for (int i = 0; i < 2; i++)
				{
					Bullet *trap = Bullet::create();
					trap->setDelegate(_delegate);
					trap->_master = this;
					trap->setID(trapType, CCString::create(kRoleMon), _group);
					trap->setPosition(ccp(getPositionX() + (_isFlipped ? -80 : 80), getPositionY() + (32 - i * 24)));
					trap->idle();
					trap->attack(NAttack);
					trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 2.5f);
					_delegate->addChild(trap, -trap->getPositionY());
				}
			}
			else
			{
				Bullet *trap = Bullet::create();
				trap->setDelegate(_delegate);
				trap->_master = this;
				trap->setID(trapType, CCString::create(kRoleMon), _group);
				trap->setPosition(ccp(getPositionX() + (_isFlipped ? -48 : 48), getPositionY() + 22));
				trap->idle();
				trap->attack(NAttack);
				trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 2.5f);
				_delegate->addChild(trap, -trap->getPositionY());
			}
		}
	}
	else if (is_same(trapType->getCString(), "Kusuri"))
	{
		for (int i = 0; i < 3; i++)
		{
			Bullet *trap = Bullet::create();
			trap->setDelegate(_delegate);
			trap->setAnchorPoint(ccp(0.5f, 0));
			trap->_master = this;
			trap->setID(trapType, CCString::create(kRoleMon), _group);

			if (i == 0)
				trap->setPosition(ccp(getPositionX() + (_isFlipped ? -24 : 24), getPositionY() - 24));
			else if (i == 1)
				trap->setPosition(ccp(getPositionX() + (_isFlipped ? 24 : -24), getPositionY() - 24));
			else if (i == 2)
				trap->setPosition(ccp(getPositionX(), getPositionY() + 24));

			trap->attack(NAttack);
			_delegate->addChild(trap, -trap->getPositionY());
		}
	}
	else if (is_same(trapType->getCString(), "KageBom"))
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			auto tempHero = (Hero *)pObject;
			if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0 && (tempHero->isPlayer() || tempHero->isCom()) && tempHero->_actionState != State::DEAD && tempHero->_isVisable && !tempHero->_isSticking)
			{
				float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
				float tempRange1 = winSize.width / 2;
				if (abs(distanceX) <= tempRange1)
				{
					Monster *trap = Monster::create();
					trap->setDelegate(_delegate);
					trap->_master = this;
					trap->setID(trapType, CCString::create(kRoleMon), _group);
					trap->setPosition(ccp(tempHero->getPositionX(), tempHero->getPositionY()));
					trap->idle();
					trap->attack(NAttack);
					_delegate->addChild(trap, -trap->getPositionY());
				}
			}
		}
	}
}

void CharacterBase::removeSelf(float dt)
{
	dealloc();
}

void CharacterBase::setMonAttack(CCNode *sender, void *data)
{
	int skillNum = *((int *)&data);
	if (getMonsterArray())
	{
		CCObject *pObject;
		CCARRAY_FOREACH(getMonsterArray(), pObject)
		{
			auto mo = (Monster *)pObject;
			if (mo->isNotCharacter("Traps"))
			{
				if (isCharacter("Kiba"))
				{
					mo->attack(SKILL1);
				}
				else if (isCharacter("Kankuro"))
				{
					if (mo->isCharacter("Karasu"))
					{
						if (skillNum == 1)
						{
							//mo->attack(SKILL1);
						}
						else if (skillNum == 2)
						{
							mo->attack(SKILL2);
						}
					}
				}
				else if (isCharacter("Chiyo"))
				{
					if (mo->isCharacter("Parents"))
					{
						if (skillNum == 1 && !mo->_skillChangeBuffValue)
						{
							mo->attack(SKILL1);
						}
						else if (skillNum == 2)
						{
							mo->attack(SKILL2);
						}
					}
				}
				else if (isCharacter("Itachi", "ImmortalSasuke"))
				{
					if (_actionState == State::NATTACK)
					{
						mo->attack(NAttack);
					}
				}
			}
		}
	}
	else
	{
		return;
	}
}

void CharacterBase::setTransform()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "acceptAttack");
	unschedule(schedule_selector(CharacterBase::dehealBuff));

	if (isCharacter("Lee",
					"RockLee"))
	{
		removeBuffEffect("dhBuff");
	}
	else
	{
		if (_skillUPBuffValue)
		{
			unschedule(schedule_selector(CharacterBase::disableBuff));
			disableBuff(0.1f);
		}

		removeBuffEffect("all");
	}

	CCString *tempAttackValue = CCString::createWithFormat("%s", getNAttackValueStr()->getCString());
	if (isCharacter("Naruto"))
		setID(CCString::create("SageNaruto"), _role, _group);
	else if (isCharacter("SageNaruto"))
		setID(CCString::create("RikudoNaruto"), _role, _group);
	else if (isCharacter("Jiraiya"))
		setID(CCString::create("SageJiraiya"), _role, _group);
	else if (isCharacter("Sasuke"))
		setID(CCString::create("ImmortalSasuke"), _role, _group);
	else if (isCharacter("Lee"))
		setID(CCString::create("RockLee"), _role, _group);
	else if (isCharacter("RockLee"))
		setID(CCString::create("Lee"), _role, _group);
	else if (isCharacter("Pain"))
		setID(CCString::create("Nagato"), _role, _group);

	setMaxHP(to_ccstring(getMaxHPValue()));
	setHP(to_ccstring(getHPValue()));

	if (_hpBar)
	{
		_hpBar->setPositionY(getHeight());
		_hpBar->loseHP(getHpPercent());
	}

	if (isGearCD)
	{
		_sattackcoldDown1 -= 5;
		_sattackcoldDown2 -= 5;
		_sattackcoldDown3 -= 5;
	}

	if (_role && isPlayer())
		_delegate->setHPLose(getHpPercent());

	setnAttackValue(tempAttackValue);

	if (isCharacter("RockLee"))
		return;

	// Update HudLayer
	if (isPlayer())
	{
		auto charName = _character->getCString();

		_delegate->getHudLayer()->skill1Button->setCD(to_ccstring(_sattackcoldDown1 * 1000));
		_delegate->getHudLayer()->skill2Button->setCD(to_ccstring(_sattackcoldDown2 * 1000));
		_delegate->getHudLayer()->skill3Button->setCD(to_ccstring(_sattackcoldDown3 * 1000));

		_delegate->getHudLayer()->skill1Button->_isColdChanged = true;
		_delegate->getHudLayer()->skill2Button->_isColdChanged = true;
		_delegate->getHudLayer()->skill3Button->_isColdChanged = true;

		auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s_skill1.png", charName)->getCString());
		if (frame)
			_delegate->getHudLayer()->skill1Button->setDisplayFrame(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s_skill2.png", charName)->getCString());
		if (frame)
			_delegate->getHudLayer()->skill2Button->setDisplayFrame(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s_skill3.png", charName)->getCString());
		if (frame)
			_delegate->getHudLayer()->skill3Button->setDisplayFrame(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s_skill4.png", charName)->getCString());
		if (frame && _delegate->getHudLayer()->skill4Button)
			_delegate->getHudLayer()->skill4Button->setDisplayFrame(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s_skill5.png", charName)->getCString());
		if (frame && _delegate->getHudLayer()->skill5Button)
			_delegate->getHudLayer()->skill5Button->setDisplayFrame(frame);

		_delegate->getHudLayer()->initGearButton(charName);
	}
}

float CharacterBase::getHpPercent()
{
	float p = _hp->floatValue() / _maxHP->floatValue();
	return p;
}

void CharacterBase::attack(abType type)
{
	if (isPlayer() && type == NAttack)
	{
		if (!_delegate->getSkillFinish() && !_isOnlySkillLocked)
			return;
	}

	switch (type)
	{
	case NAttack:
		_attackValue = getNAttackValue();
		_attackType = _nattackType;
		_attackRangeX = _nattackRangeX;
		_attackRangeY = _nattackRangeY;
		nAttack();
		break;
	case SKILL1:
		if (isPlayer())
		{
			if (_isControlled)
				_delegate->getHudLayer()->skill1Button->click();
		}

		_attackValue = getSAttackValue1();
		_attackType = _sattackType1;
		_attackRangeX = _sattackRangeX1;
		_attackRangeY = _sattackRangeY1;
		sAttack(SKILL1);
		break;
	case SKILL2:
		if (isPlayer())
		{
			if (_isControlled)
				_delegate->getHudLayer()->skill2Button->click();
		}

		_attackValue = getSAttackValue2();
		_attackType = _sattackType2;
		_attackRangeX = _sattackRangeX2;
		_attackRangeY = _sattackRangeY2;
		sAttack(SKILL2);
		break;
	case SKILL3:
		if (isPlayer())
		{
			if (_isControlled)
				_delegate->getHudLayer()->skill3Button->click();
		}

		_attackValue = getSAttackValue3();
		_attackType = _sattackType3;
		_attackRangeX = _sattackRangeX3;
		_attackRangeY = _sattackRangeY3;
		sAttack(SKILL3);
		break;
	case OUGIS1:
		if (isNotPlayer() || _isAI)
		{
			uint32_t newValue = getCkrValue() - 15000;
			setCKR(to_ccstring(newValue));
			if (getCkrValue() < 15000)
			{
				_isCanOugis1 = false;
			}
		}

		_attackValue = getSAttackValue4();
		_attackType = _sattackType4;
		_attackRangeX = _sattackRangeX4;
		_attackRangeY = _sattackRangeY4;
		oAttack(OUGIS1);
		break;
	case OUGIS2:
		if (isNotPlayer() || _isAI)
		{
			uint32_t newValue = getCkr2Value() - 25000;
			setCKR2(to_ccstring(newValue));
			if (getCkr2Value() < 25000)
			{
				_isCanOugis2 = false;
			}
		}

		_attackValue = getSAttackValue5();
		_attackType = _sattackType5;
		_attackRangeX = _sattackRangeX5;
		_attackRangeY = _sattackRangeY5;
		oAttack(OUGIS2);
		break;
	default:
		return;
	}
}

void CharacterBase::nAttack()
{
	if (_actionState == State::IDLE || _actionState == State::WALK)
	{
		if (!_isAllAttackLocked || _isOnlySkillLocked)
		{
			if (isPlayer())
			{
				_delegate->setSkillFinish(false);
			}
			if (isNotBullet())
			{
				stopAllActions();
			}
			_actionState = State::NATTACK;
			runAction(_nattackAction);
		}
	}
}

void CharacterBase::sAttack(abType type)
{
	if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
	{
		if (!_isVisable)
		{
			if (isCharacter("Konan",
							"Deidara"))
			{
				unschedule(schedule_selector(CharacterBase::disableBuff));
			}

			setOpacity(255);
			setVisible(true);
			_isVisable = true;

			if (_hpBar)
				_hpBar->setVisible(true);
			if (_shadow)
				_shadow->setVisible(true);
		}

		stopAllActions();

		switch (type)
		{
		case SKILL1:
			if (_isCanSkill1)
			{
				_actionState = State::SATTACK;
				if (isPlayer())
				{
					_delegate->setSkillFinish(false);
				}
				runAction(_skill1Action);
			}
			_isCanSkill1 = false;

			scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sattackcoldDown1);
			break;
		case SKILL2:
			if (_isCanSkill2)
			{
				_actionState = State::SATTACK;
				if (isPlayer())
				{
					_delegate->setSkillFinish(false);
				}
				runAction(_skill2Action);
			}

			_isCanSkill2 = false;

			scheduleOnce(schedule_selector(CharacterBase::enableSkill2), _sattackcoldDown2);

			break;
		case SKILL3:
			if (_isCanSkill3)
			{
				_actionState = State::SATTACK;
				if (isPlayer())
				{
					_delegate->setSkillFinish(false);
				}
				runAction(_skill3Action);
			}
			_isCanSkill3 = false;

			scheduleOnce(schedule_selector(CharacterBase::enableSkill3), _sattackcoldDown3);
			break;
		default:
			break;
		}
	}
}

void CharacterBase::oAttack(abType type)
{
	if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
	{
		if (isPlayer())
		{
			_delegate->setSkillFinish(false);
		}
		if (!_isVisable)
		{
			if (isCharacter("Konan",
							"Deidara"))
			{
				unschedule(schedule_selector(CharacterBase::disableBuff));
			}

			setOpacity(255);
			setVisible(true);
			_isVisable = true;

			if (_hpBar)
				_hpBar->setVisible(true);
			if (_shadow)
				_shadow->setVisible(true);
		}

		stopAllActions();
		switch (type)
		{
		case OUGIS1:
			_actionState = State::OATTACK;
			runAction(_skill4Action);
			break;
		case OUGIS2:
			_actionState = State::O2ATTACK;
			runAction(_skill5Action);
			break;
		default:
			break;
		}
	}
}

bool CharacterBase::checkHasMovement()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	// DRIVEND BY JOYSTICK
	return false;
#else
	return _delegate->checkHasAnyMovement();
#endif
}

void CharacterBase::idle()
{
	if (_actionState != State::IDLE && _actionState != State::DEAD)
	{
		_actionState = State::IDLE;
		stopAllActions();
		_backY = 0;
		_hurtFromLeft = false;
		_hurtFromRight = false;
		_isHitOne = false;
		_isCatchOne = false;
		_isSticking = false;
		_knockLength = 0;
		_originY = 0;
		_sticker = nullptr;
		_knockDirection = false;

		unschedule(schedule_selector(CharacterBase::stopMove));

		bool _isPlayer = isPlayer();

		if (_isPlayer)
		{
			if (!_isAllAttackLocked && !_isOnlySkillLocked)
			{
				_delegate->setSkillFinish(true);
			}
		}

		if (!_delegate->_isAttackButtonRelease &&
			_isPlayer &&
			_attackType && !_isAllAttackLocked)
		{
			_delegate->setSkillFinish(true);
			attack(NAttack);
		}
		else
		{
			if (_isPlayer && checkHasMovement())
				return;

			runAction(_idleAction);
		}
	}
}

void CharacterBase::walk(CCPoint direction)
{
	if (_actionState == State::IDLE || _actionState == State::WALK || (_actionState == State::NATTACK && isNotPlayer()))
	{
		isHurtingTower = false;

		if (_actionState == State::NATTACK &&
			isCharacter("Suigetsu",
						"Jugo",
						"Hiruzen",
						"Kisame") &&
			_isOnlySkillLocked)
		{
			if (isNotPlayer())
			{
				return;
			}
		}
		else if (_actionState == State::IDLE || _actionState == State::NATTACK)
		{
			stopAllActions();
			runAction(_walkAction);
		}

		_actionState = State::WALK;

		// NOTE: FIXED when direction.x is zero but still set to flipped
		if (direction.x != 0)
		{
			_isFlipped = direction.x > 0 ? false : true;
			setFlipX(_isFlipped);
			if (_healBuffEffect)
			{
				_healBuffEffect->setFlipX(_isFlipped);
			}
		}

		if (isCharacter("Itachi",
						"ImmortalSasuke",
						"Chiyo"))
		{
			if (hasMonsterArrayAny())
			{
				CCObject *pObject;
				CCARRAY_FOREACH(getMonsterArray(), pObject)
				{
					auto mo = (Monster *)pObject;
					if (mo->isCharacter("ItachiSusano") ||
						mo->isCharacter("SasukeSusano"))
					{
						mo->setFlipX(_isFlipped);
					}
					else if (mo->isCharacter("Parents"))
					{
						if (mo->_actionState == State::IDLE)
						{
							mo->setFlipX(_isFlipped);
							mo->_isFlipped = _isFlipped;
						}
					}
				}
			}
		}

		_velocity = ccp(direction.x * _walkSpeed * winSize.width / 1280, direction.y * _walkSpeed * winSize.width / 1280);
	}
}

bool CharacterBase::hurt()
{
	if (_actionState != State::SATTACK &&
		_actionState != State::JUMP &&
		_actionState != State::OATTACK &&
		_actionState != State::O2ATTACK &&
		_actionState != State::FLOAT &&
		_actionState != State::DEAD &&
		_actionState != State::KNOCKDOWN &&
		_actionState != State::AIRHURT &&
		!_isSticking &&
		!_isCatchOne &&
		!_isArmored)
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			auto tempHero = (Hero *)pObject;
			if (is_same(_group->getCString(), tempHero->_group->getCString()) &&
				tempHero->isCharacter("Chiyo") &&
				tempHero->_actionState != State::DEAD &&
				tempHero->_buffStartTime)
			{
				CCPoint sp = ccpSub(tempHero->getPosition(), getPosition());
				if (abs(sp.x) <= winSize.width / 2)
				{
					return false;
				}
			}
		}
		if (isCharacter("Chiyo"))
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				auto mo = (Monster *)pObject;
				if (mo->isCharacter("Parents") && !mo->_skillChangeBuffValue && mo->getActionState() != State::SATTACK && mo->getActionState() != State::DEAD)
				{
					CCPoint sp = ccpSub(mo->getPosition(), getPosition());
					if (sp.x <= 48)
					{
						return false;
					}
				}
			}
		}

		if (isPlayer())
		{
			_delegate->setSkillFinish(false);
		}

		_actionState = State::HURT;
		stopAllActions();
		if (_hurtAction)
		{
			auto list = CCArray::create();
			list->addObject(_hurtAction);
			auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::idle));
			list->addObject(call);
			auto seq = CCSequence::create(list);
			runAction(seq);
		}
		return true;
	}
	return false;
}

bool CharacterBase::hardHurt(int delayTime, bool isHurtAction, bool isCatch, bool isStick, bool isStun)
{
	if ((_actionState != State::JUMP || isStick) &&
		_actionState != State::O2ATTACK &&
		(_actionState != State::FLOAT || isStick) &&
		_actionState != State::DEAD &&
		(_actionState != State::KNOCKDOWN || isStick) &&
		_actionState != State::AIRHURT &&
		!_isSticking &&
		!_isCatchOne &&
		!_isArmored)
	{
		if (_actionState == State::FLOAT ||
			_actionState == State::AIRHURT ||
			_actionState == State::JUMP)
		{
			setPositionY(_originY);
			_originY = 0;
			_delegate->reorderChild(this, -getPositionY());
		}
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			auto tempHero = (Hero *)pObject;
			if (is_same(_group->getCString(), tempHero->_group->getCString()) &&
				tempHero->isCharacter("Chiyo") &&
				tempHero->_actionState != State::DEAD &&
				tempHero->_buffStartTime)
			{
				CCPoint sp = ccpSub(tempHero->getPosition(), getPosition());
				if (abs(sp.x) <= winSize.width / 2)
				{
					return false;
				}
			}
		}

		if (isCharacter("Chiyo"))
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				auto mo = (Monster *)pObject;
				if (mo->isCharacter("Parents") && !mo->_skillChangeBuffValue && mo->getActionState() != State::SATTACK && mo->getActionState() != State::DEAD)
				{
					CCPoint sp = ccpSub(mo->getPosition(), getPosition());
					if (sp.x <= 48)
					{
						if (mo->_isCanSkill3)
						{
							mo->attack(SKILL3);
						}
						return false;
					}
				}
			}
		}

		if (isPlayer())
		{
			_delegate->setSkillFinish(false);
		}
		if (isStick)
		{
			_sticker = _slayer;
		}

		if (isCatch)
		{
			setVisible(false);
			_isVisable = false;

			if (_shadow)
			{
				_shadow->setVisible(false);
			}
		}

		_actionState = State::HURT;
		stopAllActions();
		auto list = CCArray::create();

		if (isHurtAction)
		{
			list->addObject(_hurtAction);
		}
		else
		{
			_isSticking = true;
			auto attacker = _slayer;
			CCString *path;
			if (attacker->isCharacter("Kakuzu"))
			{
				path = CCString::createWithFormat("%s_AirHurt_02.png", getCharacter()->getCString());
			}
			else
			{
				path = CCString::createWithFormat("%s_Hurt_02.png", getCharacter()->getCString());
			}

			auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path->getCString());
			auto tempArray = CCArray::create();
			tempArray->addObject(frame);
			auto tempAnimation = CCAnimation::createWithSpriteFrames(tempArray, 0.1f);
			auto tempAction = CCAnimate::create(tempAnimation);
			list->addObject(tempAction);
		}

		if (isStun)
		{
			auto callValue = CCDictionary::create();
			callValue->setObject(CCString::create("stun"), 1);
			callValue->retain();
			auto call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setSkillEffect), (void *)callValue);
			list->addObject(call);
		}

		auto delay = CCDelayTime::create(delayTime / 1000);
		list->addObject(delay);

		auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::idle));
		list->addObject(call);

		auto seq = CCSequence::create(list);
		runAction(seq);

		return true;
	}

	return false;
}

void CharacterBase::airHurt()
{
	if (_actionState == State::FLOAT || _actionState == State::AIRHURT)
	{
		if (isPlayer())
		{
			_delegate->setSkillFinish(false);
		}

		if (_actionState == State::AIRHURT)
		{
			getActionManager()->removeAction(_airHurtAction);
			unschedule(schedule_selector(CharacterBase::resumePauseStuff));
		}
		_actionState = State::AIRHURT;
		runAction(_airHurtAction);
		getActionManager()->pauseTarget(this);
		scheduleOnce(schedule_selector(CharacterBase::resumePauseStuff), 0.2f);
	}
}

void CharacterBase::resumePauseStuff(float dt)
{
	getActionManager()->resumeTarget(this);
}

void CharacterBase::absorb(CCPoint position, bool isImmediate)
{
	if (_actionState == State::IDLE ||
		_actionState == State::WALK ||
		_actionState == State::NATTACK)
	{
		if (_isArmored || _isSticking)
			return;

		if (isPlayer())
		{
			_delegate->setSkillFinish(false);
		}
		_actionState = State::HURT;

		auto list = CCArray::create();
		if (isImmediate)
		{
			stopAllActions();
			auto mv = CCMoveTo::create(0.2f, position);
			list->addObject(_hurtAction);
			runAction(mv);
		}
		else
		{
			CCPoint direction = ccpSub(getPosition(), position);
			position.x = direction.x > 0 ? getPositionX() - 16 : getPositionX() + 16;
			position.y = direction.y > 0 ? getPositionY() - 8 : getPositionY() + 8;
			auto mv = CCMoveTo::create(0.2f, position);
			list->addObject(mv);
		}

		auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::idle));
		list->addObject(call);
		auto seq = CCSequence::create(list);
		runAction(seq);
	}
}

void CharacterBase::floatUP(float floatHeight, bool isCancelSkill)
{
	if (_actionState == State::SATTACK && !isCancelSkill)
	{
		return;
	}

	if (_actionState != State::JUMP &&
		_actionState != State::FLOAT &&
		_actionState != State::O2ATTACK &&
		_actionState != State::OATTACK &&
		_actionState != State::AIRHURT &&
		_actionState != State::DEAD &&
		!_isSticking &&
		!_isCatchOne &&
		!_isArmored)
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			auto tempHero = (Hero *)pObject;
			if (is_same(_group->getCString(), tempHero->_group->getCString()) &&
				tempHero->isCharacter("Chiyo") &&
				tempHero->_actionState != State::DEAD &&
				tempHero->_buffStartTime)
			{
				CCPoint sp = ccpSub(tempHero->getPosition(), getPosition());
				if (abs(sp.x) <= winSize.width / 2)
				{
					return;
				}
			}
		}

		if (isCharacter("Chiyo"))
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				auto mo = (Monster *)pObject;
				if (mo->isCharacter("Parents") && !mo->_skillChangeBuffValue && mo->getActionState() != State::SATTACK && mo->getActionState() != State::DEAD)
				{
					CCPoint sp = ccpSub(mo->getPosition(), getPosition());
					if (sp.x <= 48)
					{
						if (mo->_isCanSkill3)
						{
							mo->attack(SKILL3);
						}
						return;
					}
				}
			}
		}

		if (isPlayer())
		{
			_delegate->setSkillFinish(false);
		}
		_actionState = State::FLOAT;
		stopAllActions();

		float posX = getPositionX();
		float posY = getPositionY();
		_originY = posY;
		CCActionInterval *_floatAwayAction;

		if (floatHeight == 64)
			_floatAwayAction = CCJumpTo::create(0.8f, ccp(posX + (_isFlipped ? 64 : -64), posY), 64, 1);
		else if (floatHeight == 128)
			_floatAwayAction = CCJumpTo::create(1.0f, ccp(posX + (_isFlipped ? 128 : -128), posY), 64, 1);
		else
			_floatAwayAction = CCJumpTo::create(0.3f, ccp(posX + (_isFlipped ? 8 : -8), posY), 16, 1);

		auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::knockDown));
		_floatUPAction = CCSequence::create(_floatAwayAction, call, nullptr);

		runAction(_floatUPAction);
		runAction(_floatAction);
	}
}

void CharacterBase::knockDown()
{
	if (_actionState != State::KNOCKDOWN && _actionState != State::DEAD)
	{
		_actionState = State::KNOCKDOWN;
		stopAllActions();

		runAction(_knockDownAction);
	}
}

void CharacterBase::dead()
{
	getGameModeHandler()->onCharacterDead(this);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "acceptAttack");

	_isHitOne = false;
	_isCatchOne = false;
	_isSticking = false;
	_isInvincible = false;
	_startPoint = ccp(0, 0);
	_markPoint = ccp(0, 0);

	_sticker = nullptr;

	setWalkSpeed(224);
	_originSpeed = 224;

	unscheduleUpdate();

	if (_isControlled)
	{
		_isControlled = false;
		if (_controller->isPlayer())
		{
			if (_controller->isCharacter("Ino"))
			{
				_isAI = true;
				_isControlled = false;
				doAI();

				_delegate->currentPlayer = _controller;
				_delegate->getHudLayer()->updateSkillButtons();
			}

			_delegate->controlChar = nullptr;
		}

		changeGroup();

		if (isPlayer())
		{
			_isAI = false;
			_delegate->getHudLayer()->_isAllButtonLocked = false;
		}

		if (_controller->getActionState() != State::DEAD)
		{
			_controller->unschedule(schedule_selector(CharacterBase::resumeAction));
			_controller->idle();
			_controller->_isArmored = false;
		}

		_controller = nullptr;
	}

	if (isCharacter("Minato"))
	{
		setActionResume2();
	}
	else
	{
		setActionResume();
	}

	removeLostBlood(0.1f);
	unschedule(schedule_selector(CharacterBase::stopMove));
	unschedule(schedule_selector(CharacterBase::setAI));
	unschedule(schedule_selector(CharacterBase::disableHpBar));

	if (isPlayer())
	{
		_delegate->setSkillFinish(false);
		_delegate->getHudLayer()->hpLabel->setString("0");
		_delegate->getHudLayer()->status_hpbar->setOpacity(0);
	}

	//kill all buffEffect
	if (isPlayer() || isCom())
	{
		unschedule(schedule_selector(CharacterBase::healBuff));
		_buffStartTime = 0;
		unschedule(schedule_selector(CharacterBase::dehealBuff));
		if (isNotCharacter("RockLee",
						   "Lee"))
		{
			removeBuffEffect("all");
		}
		else
		{
			removeBuffEffect("dhBuff");
		}

		if (_isSuicide)
		{
			_isSuicide = false;
			rebornLabelTime = 3;
		}
		else
		{
			rebornLabelTime = 0;
			_deadNum++;

			if (isPlayer())
			{
				auto deadStr = _delegate->getHudLayer()->deadLabel->getString();
				int deads = to_int(deadStr) + 1;
				_delegate->getHudLayer()->deadLabel->setString(to_cstr(deads));
			}
		}

		if (!_isVisable)
		{
			setOpacity(255);
			setVisible(true);
			_isVisable = true;

			if (_hpBar)
				_hpBar->setVisible(true);
			if (_shadow)
				_shadow->setVisible(true);
		}
	}

	if (_hpBar)
	{
		_hpBar->removeFromParent();
		_hpBar = nullptr;
	}

	if (hearts < 1)
	{
		hearts += 1;
	}

	if (_actionState == State::FLOAT || _actionState == State::AIRHURT)
	{
		_actionState = State::DEAD;
		unschedule(schedule_selector(CharacterBase::removeClone));
		schedule(schedule_selector(CharacterBase::checkActionFinish), 0.0f);
		return;
	}
	else if (_actionState == State::JUMP)
	{
		setPositionY(_originY);
		_originY = 0;
		_delegate->reorderChild(this, -getPositionY());
	}

	stopAllActions();
	_actionState = State::DEAD;

	if (isPlayer() || isCom())
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", this);
	}

	if (isNotClone() && isNotSummon())
	{
		auto fadeOut = CCFadeOut::create(0.5);
		auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::dealloc));
		auto seqArray = CCArray::create();
		seqArray->addObject(_deadAction);

		if (isFlog())
		{
			seqArray->addObject(fadeOut);
		}
		seqArray->addObject(call);
		auto seq = CCSequence::create(seqArray);
		runAction(seq);
	}
	else
	{
		unschedule(schedule_selector(CharacterBase::removeClone));
		auto callValue = CCDictionary::create();
		callValue->setObject(CCString::create("smk"), 1);
		setSkillEffect(this, callValue);
		dealloc();
	}
}

void CharacterBase::checkActionFinish(float dt)
{
	if (getActionManager()->numberOfRunningActionsInTarget(this) == 0)
	{
		unschedule(schedule_selector(CharacterBase::checkActionFinish));
		stopAllActions();
		auto fadeOut = CCFadeOut::create(0.5);
		auto call = CCCallFunc::create(this, callfunc_selector(CharacterBase::dealloc));
		auto seqArray = CCArray::create();
		if (_deadAction)
		{
			seqArray->addObject(_deadAction);
		}
		if (isFlog())
		{
			seqArray->addObject(fadeOut);
		}
		seqArray->addObject(call);
		auto seq = CCSequence::create(seqArray);
		runAction(seq);
	}
}

void CharacterBase::dealloc()
{
}

void CharacterBase::reborn(float dt)
{
	getGameModeHandler()->onCharacterReborn(this);
}

void CharacterBase::setAI(float dt)
{
}

void CharacterBase::doAI()
{
	_isAI = true;
	schedule(schedule_selector(CharacterBase::setAI), 0.1f);
}

bool CharacterBase::findEnemy(const char *type, int searchRange, bool masterRange)
{
	CCArray *list;
	if (is_same(kRoleHero, type))
	{
		list = _delegate->_CharacterArray;
	}
	else if (is_same(kRoleFlog, type))
	{
		if (isAkatsukiGroup())
		{
			list = _delegate->_KonohaFlogArray;
		}
		else
		{
			list = _delegate->_AkatsukiFlogArray;
		}
	}
	else if (is_same(kRoleTower, type))
	{
		list = _delegate->_TowerArray;
	}

	CCObject *pObject;
	float distance;
	float curDistance = 0;
	CCPoint sp;
	bool findSome = false;
	CCARRAY_FOREACH(list, pObject)
	{
		auto target = (CharacterBase *)pObject;

		if (target->_actionState == State::DEAD ||
			target->_isVisable == false ||
			target->_isInvincible ||
			target->isKugutsu())
		{
			continue;
		}
		if ((getActionState() == State::OATTACK ||
			 getActionState() == State::O2ATTACK) ||
			(getMaster() && (getMaster()->getActionState() == State::OATTACK ||
							 getActionState() == State::O2ATTACK)))
		{
			if (target->isClone() ||
				target->isSummon() ||
				target->isMon())
			{
				continue;
			}
		}

		if (strcmp(_group->getCString(), target->_group->getCString()) != 0)
		{
			if (masterRange && getMaster())
			{
				distance = ccpDistance(target->getPosition(), getMaster()->getPosition());
				sp = ccpSub(target->getPosition(), getMaster()->getPosition());
			}
			else
			{
				distance = ccpDistance(target->getPosition(), getPosition());
				sp = ccpSub(target->getPosition(), getPosition());
			}

			if (abs(sp.x) < (searchRange ? searchRange : winSize.width / 2))
			{
				if (target->_isTaunt)
				{
					_mainTarget = target;
					return true;
				}
				if (curDistance && abs(curDistance) > abs(distance))
				{
					_mainTarget = target;
					curDistance = distance;
				}
				else if (!curDistance)
				{
					findSome = true;
					curDistance = distance;
					_mainTarget = target;
				}
			}
		}
	}
	return findSome;
}

// NOTE: Use half the window width as the search range
bool CharacterBase::findEnemy2(const char *type)
{
	CCArray *list;
	if (is_same(kRoleHero, type))
	{
		list = _delegate->_CharacterArray;
	}
	else if (is_same(kRoleFlog, type))
	{
		if (isAkatsukiGroup())
		{
			list = _delegate->_KonohaFlogArray;
		}
		else
		{
			list = _delegate->_AkatsukiFlogArray;
		}
	}
	else if (is_same(kRoleTower, type))
	{
		list = _delegate->_TowerArray;
	}

	CCObject *pObject;
	float distance;
	float curDistance = 0;
	CCPoint sp;
	bool findSome = false;

	enemyCombatPoint = 0;
	friendCombatPoint = 0;

	CCARRAY_FOREACH(list, pObject)
	{
		auto target = (CharacterBase *)pObject;

		if (target->_actionState == State::DEAD ||
			target->_isVisable == false ||
			target->isKugutsu())
		{
			continue;
		}

		distance = ccpDistance(target->getPosition(), getPosition());
		sp = ccpSub(target->getPosition(), getPosition());
		if (abs(sp.x) < winSize.width / 2)
		{
			if (target->isNotClone() && target->isNotSummon())
			{
				int baseSkillCombatPoint = 0;

				if (target->_isCanSkill1)
				{
					baseSkillCombatPoint += _sattackCombatPoint1;
				}
				if (target->_isCanSkill2)
				{
					baseSkillCombatPoint += _sattackCombatPoint2;
				}
				if (target->_isCanSkill2)
				{
					baseSkillCombatPoint += _sattackCombatPoint3;
				}

				if (is_same(_group->getCString(), target->_group->getCString()))
				{
					if (abs(sp.x) < _delegate->currentMap->getTileSize().width * 3)
					{
						if (target->isNotGuardian())
						{
							friendCombatPoint += baseSkillCombatPoint + target->getHPValue() +
												 (target->getCkrValue() / 15000) * target->_sattackCombatPoint4 +
												 (target->getCkr2Value() / 25000) * target->_sattackCombatPoint5;
						}
					}
				}
				else
				{
					if (target->isNotGuardian())
					{
						enemyCombatPoint += baseSkillCombatPoint + target->getHPValue() +
											(target->getCkrValue() / 15000) * target->_sattackCombatPoint4 +
											(target->getCkr2Value() / 25000) * target->_sattackCombatPoint5;
					}

					if (!target->_isInvincible && (target->getPositionX() >= _delegate->currentMap->getTileSize().width * 3 && target->getPositionX() <= (_delegate->currentMap->getMapSize().width - 3) * _delegate->currentMap->getTileSize().width))
					{
						if (curDistance && curDistance > distance)
						{
							_mainTarget = target;
							curDistance = distance;
						}
						else if (!curDistance)
						{
							findSome = true;
							curDistance = distance;
							_mainTarget = target;
						}
					}
				}
			}
		}
	}

	return findSome;
}

bool CharacterBase::checkBase()
{
	auto list = _delegate->_CharacterArray;
	CCObject *pObject;

	CCARRAY_FOREACH(list, pObject)
	{
		auto target = (CharacterBase *)pObject;
		if (target->_actionState == State::DEAD)
		{
			continue;
		}
		if (strcmp(_group->getCString(), target->_group->getCString()) != 0)
		{
			if (isKonohaGroup())
			{
				if (target->getPositionX() <= 11 * 32)
				{
					_mainTarget = target;
					return true;
				}
			}
			else
			{
				if (target->getPositionX() >= 85 * 32)
				{
					_mainTarget = target;
					return true;
				}
			}
		}
	}

	if (isAkatsukiGroup())
	{
		list = _delegate->_KonohaFlogArray;
	}
	else
	{
		list = _delegate->_AkatsukiFlogArray;
	}

	CCARRAY_FOREACH(list, pObject)
	{
		auto target = (CharacterBase *)pObject;
		if (target->_actionState == State::DEAD)
		{
			continue;
		}
		if (strcmp(_group->getCString(), target->_group->getCString()) != 0)
		{
			if (isKonohaGroup())
			{
				if (target->getPositionX() <= 11 * 32)
				{
					_mainTarget = target;
					return true;
				}
			}
			else
			{
				if (target->getPositionX() >= 85 * 32)
				{
					_mainTarget = target;
					return true;
				}
			}
		}
	}

	return false;
}

bool CharacterBase::findTargetEnemy(const char *type, bool isTowerDected)
{
	CCArray *list;
	if (is_same(kRoleHero, type))
	{
		list = _delegate->_CharacterArray;
	}
	else if (is_same(kRoleFlog, type))
	{
		if (isAkatsukiGroup())
		{
			list = _delegate->_KonohaFlogArray;
		}
		else
		{
			list = _delegate->_AkatsukiFlogArray;
		}
	}

	CCObject *pObject;

	float curDistance = 0;
	CCPoint sp;
	bool findSome = false;

	CCARRAY_FOREACH(list, pObject)
	{
		auto target = (CharacterBase *)pObject;

		if (strcmp(_group->getCString(), target->_group->getCString()) != 0 &&
			target->isNotKugutsu() &&
			target->_actionState != State::DEAD &&
			target->_isVisable && !target->_isInvincible)
		{
			// float gardZone;
			if (getDelegate()->team > 0)
			{
				if (target->getPositionX() >= 81 * 32)
				{
					findSome = true;

					if (target->isHurtingTower)
					{
						if (target->isCharacter("Choji") ||
							target->isCharacter("Sakura"))
						{
							_mainTarget = target;
							return true;
						}
						_mainTarget = target;
					}

					if (!isTowerDected)
					{
						_mainTarget = target;
					}
				}
			}
			else
			{
				if (target->getPositionX() <= 14 * 32)
				{
					findSome = true;

					if (target->isHurtingTower)
					{
						if (target->isCharacter("Choji") ||
							target->isCharacter("Sakura"))
						{
							_mainTarget = target;
							return true;
						}
						_mainTarget = target;
					}

					if (!isTowerDected)
					{
						_mainTarget = target;
					}
				}
			}
		}
	}
	if (!isTowerDected)
	{
		return findSome;
	}
	else
	{
		return false;
	}
}

// [For AI] 血量充足后，使AI前进
void CharacterBase::stepOn()
{
	CCPoint moveDirection;

	if (isKonohaGroup())
		moveDirection = ccpNormalize(ccp(1, 0));
	else
		moveDirection = ccpNormalize(ccp(-1, 0));

	walk(moveDirection);
}

// [For AI] 使AI撤退，只有横向移动方向
bool CharacterBase::stepBack()
{
	if (_isControlled)
		return false;
	CCPoint moveDirection;

	if (isKonohaGroup())
		moveDirection = ccpNormalize(ccp(-1, 0));
	else
		moveDirection = ccpNormalize(ccp(1, 0));

	if (getPositionX() >= _delegate->currentMap->getTileSize().width * 2 &&
		getPositionX() <= (_delegate->currentMap->getMapSize().width - 2) * _delegate->currentMap->getTileSize().width)
	{
		walk(moveDirection);
		return true;
	}
	else
	{
		return false;
	}
}

// [For AI] 使AI撤退
bool CharacterBase::stepBack2()
{
	if (_isControlled)
		return false;
	CCPoint moveDirection;

	setRand();
	int randomDirection = random(10);

	if (!_backY)
	{
		if (randomDirection > 5)
		{
			if (getPositionY() + 96 < _delegate->currentMap->getTileSize().height * 5.5)
			{
				_diretionY = 1;
				_backY = getPositionY() + 96;
			}
			else
			{
				_diretionY = -1;
				_backY = getPositionY() - 96;
			}
		}
		else
		{
			if (getPositionY() - 96 > 16)
			{
				_diretionY = -1;
				_backY = getPositionY() - 96;
			}
			else
			{
				_diretionY = 1;
				_backY = getPositionY() + 96;
			}
		}
	}
	else
	{
		if (randomDirection > 5)
		{
			if (_diretionY == 1 && (getPositionY() >= _backY || getPositionY() > _delegate->currentMap->getTileSize().height * 5))
			{
				_diretionY = -1;
				_backY = getPositionY() - 96;
			}
			else if (_diretionY == -1 && (getPositionY() <= _backY || getPositionY() < 16))
			{
				_diretionY = 1;
				_backY = getPositionY() + 96;
			}
		}
		else
		{
			if (_diretionY == 1 && getPositionY() <= _delegate->currentMap->getTileSize().height * 5)
			{
				_diretionY = 1;
				_backY = _delegate->currentMap->getTileSize().height * 5;
			}
			else if (getPositionY() > 16)
			{
				_diretionY = -1;
				_backY = 16;
			}
		}
	}

	if (isKonohaGroup() && getPositionX() >= _delegate->currentMap->getTileSize().width * 2)
	{
		moveDirection = CCPoint(ccp(-1, _diretionY));
		walk(moveDirection);
		return true;
	}
	else if (isAkatsukiGroup() && getPositionX() <= (_delegate->currentMap->getMapSize().width - 2) * _delegate->currentMap->getTileSize().width)
	{
		moveDirection = CCPoint(ccp(1, _diretionY));
		walk(moveDirection);
		return true;
	}
	else
	{
		return false;
	}
}

// [For AI] 检查角色是否需要使用【拉面】回血，血量低于界限，则返回true
bool CharacterBase::checkRetri()
{
	if (_isCanItem1 && getCoinValue() >= 50)
	{
		if (_delegate->_isHardCoreGame)
		{
			if (battleCondiction >= 0)
			{
				if (!_isHealling)
				{
					if (getMaxHPValue() - getHPValue() >= 3000 + gearRecoverValue && getGearArray()->count() > 1)
						setItem(Item1);
					else if (getHPValue() < 5000 && getGearArray()->count() > 0)
						setItem(Item1);
					else if (getHPValue() < 1500)
						setItem(Item1);
				}
			}
			else
			{
				if (getMaxHPValue() - getHPValue() >= 3000 + gearRecoverValue && !_isHealling && getGearArray()->count() > 0)
					setItem(Item1);
				else if (getHPValue() < 3000)
					setItem(Item1);
			}
		}
		else
		{
			if (getHPValue() < 1500 && isKonohaGroup())
				setItem(Item1);
			if (getHPValue() < 500 && isAkatsukiGroup())
				setItem(Item1);
		}
	}

	if (battleCondiction >= 0)
	{
		if (isKonohaGroup())
		{
			if (getPositionX() >= _delegate->currentMap->getTileSize().width * 60)
				return false;
		}
		else
		{
			if (getPositionX() <= _delegate->currentMap->getTileSize().width * 36)
				return false;
		}
	}

	if (getHPValue() < 1500 && !_isControlled)
		return true;
	return false;
}

void CharacterBase::changeSide(CCPoint sp)
{
	if (sp.x > 0)
	{
		setFlipX(false);
		_isFlipped = false;
	}
	else
	{
		setFlipX(true);
		_isFlipped = true;
	}

	if (isCharacter("Itachi", "ImmortalSasuke"))
	{
		if (hasMonsterArrayAny())
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				auto mo = (Monster *)pObject;
				if (mo->isCharacter("ItachiSusano", "SasukeSusano"))
					mo->_isFlipped = _isFlipped;
				mo->setFlipX(_isFlipped);
			}
		}
	}
}

void CharacterBase::changeGroup()
{
	if (isKonohaGroup())
		setGroup(CCString::create(Akatsuki));
	else
		setGroup(CCString::create(Konoha));

	if (_hpBar && isNotPlayer())
	{
		if (strcmp(getGroup()->getCString(), _delegate->currentPlayer->getGroup()->getCString()) != 0)
		{
			_hpBar->changeBar("hp_bar_r.png");
		}
		else if (isCom())
		{
			_hpBar->changeBar("hp_bar_b.png");
		}
	}

	if (isPlayer())
	{
		for (int i = 0; i < 4; i++)
		{
			CCArray *list;

			if (i == 0)
				list = _delegate->_CharacterArray;
			else if (i == 1)
				list = _delegate->_TowerArray;
			else if (i == 2)
				list = _delegate->_AkatsukiFlogArray;
			else if (i == 3)
				list = _delegate->_KonohaFlogArray;

			CCObject *pObject;
			CCARRAY_FOREACH(list, pObject)
			{
				auto target = (CharacterBase *)pObject;
				if (target->_hpBar)
				{
					if (strcmp(_group->getCString(), target->_group->getCString()) != 0)
					{
						if (target->isFlog())
						{
							target->_hpBar->changeBar("flog_bar_r.png");
						}
						else
						{
							target->_hpBar->changeBar("hp_bar_r.png");
						}
					}
					else
					{
						if (target->isFlog())
						{
							target->_hpBar->changeBar("flog_bar.png");
						}
						else if (target->isTower())
						{
							target->_hpBar->changeBar("hp_bar.png");
						}
						else
						{
							if (target->isNotPlayer())
							{
								target->_hpBar->changeBar("hp_bar_b.png");
							}
						}
					}
				}
			}
		}
	}
}

void CharacterBase::autoFlip(CharacterBase *attacker)
{
	if (_isFlipped == attacker->_isFlipped)
	{
		if (_isFlipped)
		{
			setFlipX(false);
			_isFlipped = false;
		}
		else
		{
			setFlipX(true);
			_isFlipped = true;
		}
	}
}

void CharacterBase::enableItem1(float dt)
{
	_isCanItem1 = true;
}

void CharacterBase::enableSkill1(float dt)
{
	_isCanSkill1 = true;
}

void CharacterBase::enableSkill2(float dt)
{
	_isCanSkill2 = true;
}

void CharacterBase::enableSkill3(float dt)
{
	_isCanSkill3 = true;
}
