#include "CharacterBase.h"
#include "Core/Provider.hpp"
#include "HudLayer.h"
#include "GameLayer.h"
#include "GameMode/GameModeImpl.h"
#include "MyUtils/CCShake.h"
#include "Systems/CommandSystem.hpp"

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
	_isHealing = false;
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
	// totalCombatPoint=0;
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
			getGameLayer()->setCKRLose(false);
			getGameLayer()->removeOugisMark(1);
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
			getGameLayer()->setCKRLose(true);
			getGameLayer()->removeOugisMark(2);
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
	setMaxHPValue(tempMaxHP, false);
	setnAttackValue(to_ccstring(attackValue));
}

// TODO: Move to setData(HeroMetadata data)
void CharacterBase::readData(CCArray *tmpData, CCString *&attackType, CCString *&attackValue, int &attackRangeX, int &attackRangeY, uint32_t &cooldown, int &combatPoint)
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
			cooldown = tmpDict->valueForKey("cd")->uintValue();
		case 5:
			combatPoint = tmpDict->valueForKey("combatPoint")->intValue();
		}
	}
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
		if (isPlayerOrCom())
		{
			if (isNotGuardian())
			{
				if (isKonohaGroup() && getPositionX() <= 11 * 32)
				{
					_isHealing = true;
					if (getHpPercent() < 1.0f)
					{
						scheduleOnce(schedule_selector(CharacterBase::setRestore), 1.0f);
					}
				}
				else if (isAkatsukiGroup() && getPositionX() >= 85 * 32)
				{
					_isHealing = true;
					if (getHpPercent() < 1.0f)
					{
						scheduleOnce(schedule_selector(CharacterBase::setRestore), 1.0f);
					}
				}
				else
				{
					_isHealing = false;
				}
			}
		}
	}

	if (_actionState == State::WALK)
	{
		_desiredPosition = ccpAdd(getPosition(), ccpMult(_velocity, dt));

		if (isPlayer() && !_isAI && !_isInvincible && !_isArmored)
		{
			// save the stop Area
			for (auto tower : getGameLayer()->_TowerArray)
			{
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
							_velocity = ccp(0, 1 * _walkSpeed * kSpeedBase);
						}
						else
						{
							_velocity = ccp(0, -1 * _walkSpeed * kSpeedBase);
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

		float posX = MIN(getGameLayer()->currentMap->getMapSize().width * getGameLayer()->currentMap->getTileSize().width,
						 MAX(0, _desiredPosition.x));

		// map height		: 10
		// backgroud height	: 4.5
		// floor height		: 5.5
		float poxY = MIN(getGameLayer()->currentMap->getTileSize().height * 5.5, MAX(0, _desiredPosition.y));

		setPosition(ccp(posX, poxY));
		getGameLayer()->reorderChild(this, -getPositionY());
		if (isPlayerOrCom())
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

	if (!onAcceptAttack(attacker))
		return;

	if (attacker->isCharacter("Hiruzen") && attacker->_actionState == State::O2ATTACK)
	{
		isCannotMiss = true; // TODO: Add this as a parameter of CharacterBase::acceptAttack
	}

	if (isNotSameGroupAs(attacker) &&
		_isVisable &&
		(!_isInvincible || isCannotMiss) &&
		_actionState != State::DEAD)
	{
		// Tower
		if (isTower())
		{
			bool isHit = false;
			if (attacker->_attackType == "nAttack" &&
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

				float atkRangeX = attacker->_attackRangeX + attacker->getContentSize().width / 2 + getContentSize().width / 2;

				if (!attacker->_isFlipped && distanceX < 0 && -distanceX < atkRangeX)
				{
					_hurtFromLeft = true;
					isHitX = true;
				}
				else if (attacker->_isFlipped && distanceX > 0 && distanceX < atkRangeX)
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
				setDamage(attacker);

				if (!_isHitOne)
				{
					_isHitOne = true;
					auto call = CallFunc::create(std::bind(&CharacterBase::disableShack, this));
					auto delay = CCDelayTime::create(0.5f);
					auto seq = newSequence(CCShake::createWithStrength(0.1f, 2, 0), delay, call);
					runAction(seq);
				}
			}

			return;
		}
		// Bullet
		else if (attacker->isBullet())
		{
			if (setHitBox().intersectsRect(attacker->setHitBox()))
			{
				if (!onBulletHit(attacker))
					return;
				setDamage(attacker);

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

								if (attacker->_master->_actionState == State::O2ATTACK)
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
									getGameLayer()->controlChar = this;
									getGameLayer()->currentPlayer = this;
									getGameLayer()->getHudLayer()->updateSkillButtons();
									idle();
								}

								if (isPlayer())
								{
									doAI();
									getGameLayer()->getHudLayer()->_isAllButtonLocked = true;
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

			float atkRangeX = attacker->_attackRangeX + attacker->getContentSize().width / 2 + getContentSize().width / 2;

			if (attacker->_attackType == "aAttack")
			{
				if (abs(distanceX) <= atkRangeX)
				{
					isHitX = true;
				}
			}
			else
			{
				if (!attacker->_isFlipped && distanceX < 0 && -distanceX < atkRangeX)
				{
					_hurtFromLeft = true;
					isHitX = true;
				}
				else if (attacker->_isFlipped && distanceX > 0 && distanceX < atkRangeX)
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

					// hit or not !
					attacker->_isHitOne = true;

					// record the slayer
					_slayer = attacker;

					// flog hurt
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
					else if (isPlayerOrCom() || isClone())
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
										auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Heart_Effect_%02d", attacker->hearts)->getCString());
										attacker->_heartEffect->setDisplayFrame(frame);
									}
								}

								if (attacker->isPlayer() && attacker->hearts > 0)
								{
									int countMON = 0;
									for (auto mo : attacker->getMonsterArray())
									{
										if (mo->isNotCharacter("Traps"))
										{
											countMON++;
										}
									}

									if (countMON < 3 && attacker->getLV() >= 2)
									{
										getGameLayer()->getHudLayer()->skill4Button->unLock();
									}
								}
							}
							else if (attacker->isCharacter("Nagato") && _sticker)
							{
								CharacterBase *stHero = _sticker;
								if (stHero->isCharacter("Nagato") && stHero->hearts <= 2)
									attacker->hearts += 1;
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
								if (attacker->_master)
								{
									if (attacker->isCharacter("FakeMinato"))
									{
										setPosition(ccp(attacker->_master->_isFlipped ? attacker->_master->getPositionX() - 64 : attacker->_master->getPositionX() + 64,
														attacker->_master->getPositionY() + 2));
									}
									else
									{
										setPosition(ccp(attacker->_master->_isFlipped ? attacker->_master->getPositionX() - 48 : attacker->_master->getPositionX() + 48,
														attacker->_master->getPositionY()));
									}

									CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", this);
									getGameLayer()->reorderChild(this, -getPositionY());
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
									if (attacker->_master)
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
										else if (attacker->_master->isCharacter("Shikamaru"))
										{
											bool underAttack = false;
											if (attacker->isCharacter("KageHand"))
											{
												underAttack = hardHurt(6000, false, false, true, false);
												if (underAttack)
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
												underAttack = hardHurt(3000, false, false, true, false);
											}

											if (underAttack)
											{
												attacker->_isCatchOne = true;
												setPosition(ccp(attacker->getPositionX(), attacker->getPositionY() + 1));
												getGameLayer()->reorderChild(this, -getPositionY());
											}
										}
										else if (attacker->_master->isCharacter("Itachi") ||
												 attacker->_master->isCharacter("Chiyo"))
										{
											bool underAttack = false;

											if (attacker->_master->isCharacter("Chiyo"))
											{
												underAttack = hardHurt(2000, false, false, true, false);
											}
											else
											{
												underAttack = hardHurt(3000, false, false, true, false);
											}
											if (underAttack)
											{
												attacker->_isCatchOne = true;
												setPosition(ccp(attacker->getPositionX() + 2, attacker->getPositionY() - 2));
												getGameLayer()->reorderChild(this, -getPositionY());
											}
										}
										else if (attacker->_master->isCharacter("Nagato"))
										{
											bool underAttack = false;

											if (attacker->isCharacter("NarakaPath"))
												underAttack = hardHurt(2000, false, false, true, false);

											if (underAttack)
											{
												attacker->_isCatchOne = true;
												setPosition(ccp(getPositionX() + (_isFlipped ? -30 : 30), getPositionY() - 10));
												getGameLayer()->reorderChild(this, -getPositionY());
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
											bool underAttack = false;

											if (!_isArmored)
											{
												setKnockLength(1);
											}
											underAttack = hardHurt(1500, false, false, true, true);

											if (underAttack)
											{
												attacker->_isCatchOne = true;
												setPosition(ccp(attacker->getPositionX() + (attacker->_isFlipped ? -28 : 28), attacker->getPositionY() - 1));
												setFlipX(attacker->_isFlipped ? false : true);
												getGameLayer()->reorderChild(this, -getPositionY());
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

					if (onHit(attacker))
						setDamage(attacker);
				}
			}
		}
	}
}

CCFiniteTimeAction *CharacterBase::createAnimation(CCArray *ationArray, float fps, bool isRepeat, bool isReturn)
{
	CCObject *tObject;
	CCArray *animeFrames = CCArray::create();
	auto seqArray = CCArray::create();
	CCAnimation *tempAnimation;
	CCAction *tempAction;
	CCFiniteTimeAction *seq;

	CCARRAY_FOREACH(ationArray, tObject)
	{
		auto dic = (CCDictionary *)tObject;
		CCDictElement *ele = nullptr;

		CCDICT_FOREACH(dic, ele)
		{
			auto key = CCString::create(ele->getStrKey())->getCString();
			auto keyValue = dic->valueForKey(key)->getCString();
			if (is_same(key, "f"))
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
					auto call = CallFunc::create(std::bind(&CharacterBase::setAttackBox, this, string(keyValue)));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setSound"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::setSound, this, string(keyValue)));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setDSound"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::setDSound, this, string(keyValue)));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setDelay"))
				{
					float delayTime = dic->valueForKey(key)->intValue();
					auto delay = CCDelayTime::create(delayTime / 100.0f);
					seqArray->addObject(delay);
				}
				else if (is_same(key, "setMove"))
				{
					int moveLength = dic->valueForKey(key)->intValue();
					auto call = CallFunc::create(std::bind(&CharacterBase::setMove, this, moveLength));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setSkillEffect"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::setSkillEffect, this, string(keyValue)));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setJump"))
				{
					bool jumpDirection = dic->valueForKey(key)->boolValue();
					auto call = CallFunc::create(std::bind(&CharacterBase::setJump, this, jumpDirection));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setCharge"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::getCollider, this));
					seqArray->addObject(call);
					int moveLength = dic->valueForKey(key)->intValue();
					call = CallFunc::create(std::bind(&CharacterBase::setCharge, this, moveLength));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setChargeB"))
				{
					int moveLength = dic->valueForKey(key)->intValue();
					auto call = CallFunc::create(std::bind(&CharacterBase::setChargeB, this, moveLength));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setClone"))
				{
					int cloneTime = dic->valueForKey(key)->intValue();
					auto call = CallFunc::create(std::bind(&CharacterBase::setClone, this, cloneTime));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setMon"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::setMon, this, string(keyValue)));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setFont"))
				{
					// const char *split = ",";
					// char *p;
					// char str[] = char[strlen(keyValue)];
					// strcpy(str, keyValue);
					// p = strtok(str, split);
					// vector<string> valueVector;
					// while (p != nullptr)
					// {
					// 	valueVector.push_back(p);
					// 	p = strtok(nullptr, split);
					// }

					// auto call = CallFunc::create(std::bind(&CharacterBase::setFontEffect, this, valueVector));
					// seqArray->addObject(call);
				}
				else if (is_same(key, "setBuff"))
				{
					int buffValue = dic->valueForKey(key)->intValue();
					auto call = CallFunc::create(std::bind(&CharacterBase::setBuff, this, buffValue));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setCommand"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::setCommand, this, string(keyValue)));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setDetonation"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::dealloc, this));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setBullet"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::setBullet, this, string(keyValue)));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setMonAttack"))
				{
					int skillNum = dic->valueForKey(key)->intValue();
					auto call = CallFunc::create(std::bind(&CharacterBase::setMonAttack, this, skillNum));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setTrap"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::setTrap, this, string(keyValue)));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setActionResume"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::setActionResume, this));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setActionResume2"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::setActionResume2, this));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setShadow"))
				{
					auto frame = (CCSpriteFrame *)(animeFrames->objectAtIndex(animeFrames->count() - 1));
					auto call = CallFunc::create(std::bind(&CharacterBase::setShadow, this, frame));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setTransform"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::setTransform, this));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setOugis"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::setOugis, this));
					seqArray->addObject(call);
				}
				else if (is_same(key, "stopJump"))
				{
					int stopTime = dic->valueForKey(key)->intValue();
					auto call = CallFunc::create(std::bind(&CharacterBase::stopJump, this, stopTime));
					seqArray->addObject(call);
				}
				else if (is_same(key, "setFlipped"))
				{
					auto call = CallFunc::create(std::bind(&CharacterBase::setCharFlip, this));
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
			auto call = CallFunc::create(std::bind(&CharacterBase::idle, this));
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
		_isFlipped = false; // TODO: Upgrade to V4 then use CCSprite::_isFlippedX instead
	}
	else
	{
		setFlipX(true);
		_isFlipped = true;
	}
}

void CharacterBase::setShadow(CCSpriteFrame *frame)
{
	auto charN = CCSprite::createWithSpriteFrame(frame);
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
	auto call = CallFunc::create(std::bind(&CharacterBase::enableShadow, this, charN));
	auto seq = newSequence(delay, call);
	charN->runAction(seq);
	getGameLayer()->addChild(charN, -getPositionY() - 1);
}

void CharacterBase::enableShadow(CCSprite *charN)
{
	charN->setVisible(true);
	auto delay = CCDelayTime::create(0.1f);
	auto call = CallFunc::create(std::bind(&CharacterBase::disableShadow, this, charN));
	auto seq = newSequence(delay, call);
	charN->runAction(seq);
}

void CharacterBase::disableShadow(CCSprite *charN)
{
	charN->stopAllActions();
	charN->removeFromParent();
}

void CharacterBase::setOugis()
{
	getGameLayer()->setOugis(this);
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

void CharacterBase::setDamage(CharacterBase *attacker)
{
	setDamage(attacker, attacker->_effectType, attacker->_attackValue, _isFlipped);
}

void CharacterBase::setDamage(CharacterBase *attacker, const char *effectType, int attackValue, bool isFlipped)
{
	if (isTower())
	{
		if (_hpBar)
			_hpBar->setVisible(true);

		unschedule(schedule_selector(CharacterBase::disableHpBar));
		scheduleOnce(schedule_selector(CharacterBase::disableHpBar), 2.0f);
	}

	int criticalValue;
	uint32_t realValue;

	_slayer = attacker;
	CharacterBase *currentAttacker;
	if (attacker->_master)
		currentAttacker = attacker->_master;
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
		if (attacker->isCharacter("Hiruzen") && attacker->_actionState == State::O2ATTACK)
		{
			isCannotMiss = true;
		}

		if (isCannotMiss)
		{
			realValue = attackValue + criticalValue;
		}
		else if ((attacker->_master ||
				  attacker->_actionState == State::NATTACK) &&
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
					for (auto mo : _monsterArray)
					{
						if (mo->isCharacter("Parents") && !mo->_skillChangeBuffValue && mo->_actionState != State::SATTACK)
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

	setHPValue(getHPValue() < realValue ? 0 : getHPValue() - realValue);

	if (isClone() && _master && !_master->_isControlled)
	{
		uint32_t boundValue = 0;
		if (isCharacter("Naruto"))
			boundValue = realValue * 15 / 100;
		else if (isCharacter("SageNaruto"))
			boundValue = realValue * 25 / 100;
		else if (isCharacter("RikudoNaruto"))
			boundValue = realValue * 35 / 100;

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

		_master->increaseAllCkrs(boundValue);
	}
	else if (!_isControlled)
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

		if (isGainable)
			increaseAllCkrs(boundValue);
	}

	if (isPlayerOrCom() && !currentAttacker->_isControlled)
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
			currentAttacker->increaseAllCkrs(gainValue);
	}

	if (isPlayer() || (isNotTower() &&
					   abs(ccpSub(getPosition(), getGameLayer()->currentPlayer->getPosition()).x) < kAttackRange))
	{
		// create damage value display
		bool _isDisplay = false;

		if (attacker->isPlayer() || isPlayer())
		{
			_isDisplay = true;
		}
		if (attacker->_master)
		{
			if (attacker->_master->isPlayer())
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

		// create damage effect
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

void CharacterBase::setCoinDisplay(int num)
{
	CCSprite *coinDisplay = CCSprite::create();

	CCSprite *coinSprite = CCSprite::createWithSpriteFrameName("coin");
	coinSprite->setPosition(ccp(14, 0));
	coinDisplay->addChild(coinSprite);

	CCString *label = CCString::createWithFormat("+%d", num);
	auto rewardLabel = CCLabelBMFont::create(label->getCString(), "Fonts/yellow.fnt");
	rewardLabel->setPosition(ccp(0, 0));
	rewardLabel->setScale(0.3f);
	coinDisplay->addChild(rewardLabel);

	coinDisplay->setPosition(ccp(getPositionX(), getPositionY() + getContentSize().height / 2));
	getGameLayer()->addChild(coinDisplay, 5000);

	auto mv = CCMoveBy::create(0.5f, ccp(0, 12));
	auto fadeOut = CCFadeOut::create(0.8f);
	auto call = CallFunc::create(std::bind(&CharacterBase::removeCoinDisplay, this, coinDisplay));
	auto sp = CCSpawn::create(fadeOut, mv, nullptr);
	auto seq = newSequence(sp, call);
	coinDisplay->runAction(seq);
}

void CharacterBase::removeCoinDisplay(CCSprite *coinDisplay)
{
	coinDisplay->removeFromParent();
}

void CharacterBase::setDamgeDisplay(int value, const char *type)
{
	if (_damageArray.size() < 6)
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

		getGameLayer()->addChild(damageFont, currentNumberTag);
		_damageArray.push_back(damageFont);

		auto sd = CCScaleBy::create(0.2f, 0.5f);
		auto call = CallFunc::create(std::bind(&CharacterBase::removeDamageDisplay, this));
		auto mv = CCMoveBy::create(0.4f, ccp(0, 12));
		auto fadeOut = CCFadeOut::create(0.4f);
		auto sp = CCSpawn::create(fadeOut, mv, nullptr);
		auto seq = newSequence(sd, sp, call);
		damageFont->runAction(seq);
	}
}

void CharacterBase::removeDamageDisplay()
{
	if (_damageArray.size() > 0)
	{
		auto damageFont = _damageArray.at(0);
		damageFont->removeFromParent();
		_damageArray.erase(_damageArray.begin());
	}
}

void CharacterBase::setDamgeEffect(const char *type)
{
	if (isPlayer() || abs(ccpSub(getPosition(), getGameLayer()->currentPlayer->getPosition()).x) < kAttackRange)
	{
		if (damageEffectCount < 2)
		{
			if (isNotFlog())
			{
				Effect *ef = Effect::create(type, this);
				getGameLayer()->damageEffectBatch->addChild(ef, 5000);
			}
			else
			{
				Effect *ef = Effect::create(type, this);
				getGameLayer()->damageEffectBatch->addChild(ef);
			}

			damageEffectCount++;
		}
	}
}

void CharacterBase::setSkillEffect(const string &type)
{
	if (isPlayer() ||
		abs(ccpSub(getPosition(), getGameLayer()->currentPlayer->getPosition()).x) < kAttackRange)
	{
		Effect *ef = Effect::create(type.c_str(), this);
		if (type == "Bagua" ||
			type == "Kujiyose")
		{
			getGameLayer()->addChild(ef, -500);
		}
		else if (type == "DarkFlame")
		{
			getGameLayer()->addChild(ef, -ef->getPositionY());
		}
		else
		{
			getGameLayer()->skillEffectBatch->addChild(ef);
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
		for (auto mo : _monsterArray)
		{
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
			getGameLayer()->getHudLayer()->offCoin(to_cstr(50));
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
		increaseHpAndUpdateUI(hpRestore);

		if (!_isHealing && !_healItemEffect)
		{
			_healItemEffect = Effect::create("hp_restore", this);
			_healItemEffect->setPosition(ccp(_isFlipped ? getContentSize().width / 2 + 16 : getContentSize().width / 2 - 16,
											 _height));
			addChild(_healItemEffect);
			//_isHealing=true;
		}
	}
}

bool CharacterBase::setGear(gearType type)
{
	uint32_t gearCost = 0;
	// The cost of [ 00 03 06 ] is 500
	if (type % 3 == 0)
		gearCost = 500;
	else
		gearCost = 1000;

	if (getGearArray().size() <= 2 && getCoin() >= gearCost)
	{
		getGearArray().push_back(type);

		if (isPlayer())
			getGameLayer()->getHudLayer()->offCoin(to_cstr(gearCost));
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
			if (hasTempAttackValue1())
			{
				settempAttackValue1(to_ccstring(getTempAttackValue1() + 160));
			}
			setnAttackValue(to_ccstring(getNAttackValue() + 160));
			hasArmorBroken = true;
			break;
		case gear05:
			isGearCD = true;
			_sattackcooldown1 -= 5;
			_sattackcooldown2 -= 5;
			_sattackcooldown3 -= 5;

			if (isPlayer())
			{
				getGameLayer()->getHudLayer()->skill1Button->setCD(to_ccstring(_sattackcooldown1 * 1000));
				getGameLayer()->getHudLayer()->skill2Button->setCD(to_ccstring(_sattackcooldown2 * 1000));
				getGameLayer()->getHudLayer()->skill3Button->setCD(to_ccstring(_sattackcooldown3 * 1000));

				getGameLayer()->getHudLayer()->skill1Button->_isColdChanged = true;
				getGameLayer()->getHudLayer()->skill2Button->_isColdChanged = true;
				getGameLayer()->getHudLayer()->skill3Button->_isColdChanged = true;
			}
			break;
		case gear06:
			_isCanGear06 = true;
			break;
		case gear07:
			gearRecoverValue = 3000;
			getGameLayer()->getHudLayer()->item1Button->setCD(to_ccstring(3000));
			getGameLayer()->getHudLayer()->item1Button->_isColdChanged = true;
			break;
		case gear08:
			uint32_t tempMaxHP = getMaxHPValue();
			tempMaxHP += 6000;
			setMaxHPValue(tempMaxHP);
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
		if (_actionState == State::NATTACK ||
			_actionState == State::WALK ||
			_actionState == State::IDLE)
		{
			if (getWalkSpeed() == 224)
			{
				setWalkSpeed(320);

				_isCanGear00 = false;

				_speedItemEffect = Effect::create("speedUp", this);
				addChild(_speedItemEffect);

				scheduleOnce(schedule_selector(CharacterBase::enableGear00), 15.0f);
				if (isPlayer() || is_same(getGroup()->getCString(), getGameLayer()->currentPlayer->getGroup()->getCString()))
					setOpacity(150);
				else
					setVisible(false);

				if (_hpBar)
					_hpBar->setVisible(false);
				if (_shadow)
					_shadow->setVisible(false);

				_isVisable = false;

				setSound("Audio/Effect/suzou_effect.ogg");
				schedule(schedule_selector(CharacterBase::disableGear1), 3.0f);
			}
		}
	}
	else if (type == gear03)
	{
		_isCanGear03 = false;
		setMon("Traps");
		scheduleOnce(schedule_selector(CharacterBase::enableGear03), 15.0f);
	}
	else if (type == gear06)
	{
		_isCanGear06 = false;
		scheduleOnce(schedule_selector(CharacterBase::enableGear06), 15.0f);

		if (!_isInvincible && !_isArmored)
		{
			if (_actionState == State::IDLE ||
				_actionState == State::WALK ||
				_actionState == State::FLOAT ||
				_actionState == State::AIRHURT ||
				_actionState == State::HURT ||
				_actionState == State::KNOCKDOWN)
			{
				if (_isSticking)
				{
					_isSticking = false;
				}
				if (_actionState == State::FLOAT ||
					_actionState == State::AIRHURT)
				{
					setPositionY(_originY);
					_originY = 0;
					getGameLayer()->reorderChild(this, -getPositionY());
				}

				idle();

				setSkillEffect("tishen");
				scheduleOnce(schedule_selector(CharacterBase::disableGear2), 1.0f);
				setSound("Audio/Effect/poof2.ogg");

				if (isPlayer() || is_same(getGroup()->getCString(), getGameLayer()->currentPlayer->getGroup()->getCString()))
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

void CharacterBase::addCoin(uint32_t num)
{
	setCoin(getCoin() + num);
}

void CharacterBase::minusCoin(uint32_t num)
{
	if (getCoin() > num)
		setCoin(getCoin() - num);
	else
		setCoin(0);
}

void CharacterBase::setRestore(float dt)
{
	if (_hpBar)
	{
		increaseHpAndUpdateUI(800);

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
		if (isAkatsukiGroup() && getPositionX() <= getGameLayer()->currentMap->getTileSize().width * 2)
			isZone = true;
		else if (isKonohaGroup() && getPositionX() >= (getGameLayer()->currentMap->getMapSize().width - 2) * getGameLayer()->currentMap->getTileSize().width)
			isZone = true;

		if (isZone)
			setHPValue(getHPValue() > 1000 ? getHPValue() - 1000 : 100);

		if (_actionState == State::IDLE && getHpPercent() < 1)
		{
			increaseHpAndUpdateUI(300);
		}
	}
}

void CharacterBase::disableEffect()
{
	if (_healItemEffect)
	{
		_healItemEffect->removeFromParent();
		_healItemEffect = nullptr;
	}

	if (_speedItemEffect)
	{
		_speedItemEffect->removeFromParent();
		_speedItemEffect = nullptr;
	}
}

void CharacterBase::setSound(const string &file)
{
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isVoice"))
	{
		bool _isPlayable = false;
		if (isPlayer() ||
			abs(ccpSub(getPosition(), getGameLayer()->currentPlayer->getPosition()).x) < kAttackRange)
		{
			_isPlayable = true;
		}
		if (getGameLayer()->controlChar)
		{
			if (abs(ccpSub(getPosition(), getGameLayer()->controlChar->getPosition()).x) < kAttackRange)
			{
				_isPlayable = true;
			}
		}

		if (_isPlayable)
		{
			SimpleAudioEngine::sharedEngine()->preloadEffect(file.c_str());
			SimpleAudioEngine::sharedEngine()->playEffect(file.c_str());
		}
	}
}

void CharacterBase::setDSound(const string &file)
{
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isVoice"))
	{
		bool _isPlayable = false;
		if (isPlayer() ||
			abs(ccpSub(getPosition(), getGameLayer()->currentPlayer->getPosition()).x) < kAttackRange)
		{
			_isPlayable = true;
		}
		if (getGameLayer()->controlChar)
		{
			if (abs(ccpSub(getPosition(), getGameLayer()->controlChar->getPosition()).x) < kAttackRange)
			{
				_isPlayable = true;
			}
		}

		if (_isPlayable && _isHitOne)
		{
			SimpleAudioEngine::sharedEngine()->preloadEffect(file.c_str());
			SimpleAudioEngine::sharedEngine()->playEffect(file.c_str());
		}
	}
}

void CharacterBase::setAttackBox(const string &effectType)
{
	_effectType = effectType.c_str();

	if (_actionState == State::HURT)
	{
		if (isCharacter("Sasuke",
						"ImmortalSasuke",
						"NarakaPath"))
		{
			increaseHpAndUpdateUI(260);

			if (isPlayer())
			{
				getGameLayer()->setHPLose(getHpPercent());
			}

			_attackType = _spcattackType1;
			_attackValue = getSpcAttackValue1();
			_attackRangeX = _spcattackRangeX1;
			_attackRangeY = _spcattackRangeY1;
		}
		// else if (isCharacter("Nagato"))
		// {
		// 	uint realValue;

		// 	CharacterBase *attacker = _slayer;
		// 	CharacterBase *currentAttacker = attacker->_master ? attacker->_master : attacker;
		// 	float gainValue = 0;

		// 	if (attacker->isCharacter("Nagato"))
		// 	{
		// 		if (currentAttacker->isAttackGainCKR)
		// 			gainValue = realValue * 80 / 100;
		// 		else
		// 			gainValue = realValue * 65 / 100;
		// 	}
		// 	else if (currentAttacker->isAttackGainCKR)
		// 	{
		// 		gainValue = realValue * 15 / 100;
		// 	}
		// }
	}

	CCNotificationCenter::sharedNotificationCenter()->postNotification("acceptAttack", this);

	if (isPlayer())
	{
		if ((_actionState == State::OATTACK || _actionState == State::O2ATTACK) && _isHitOne == true && !getGameLayer()->_isShacking)
		{
			getGameLayer()->_isShacking = true;
			CCScene *f = CCDirector::sharedDirector()->getRunningScene();
			auto call = CallFunc::create(std::bind(&CharacterBase::disableShack, this));
			f->runAction(newSequence(CCShake::create(0.05f, 12), call));
		}
		if (getGameLayer()->_isAttackButtonRelease && _actionState == State::NATTACK && !_isOnlySkillLocked && !_isAI)
		{
			idle();
			return;
		}
	}
}

void CharacterBase::getSticker(float dt)
{
	for (auto hero : getGameLayer()->_CharacterArray)
	{
		CharacterBase *tempSticker = nullptr;
		if (hero->_sticker)
		{
			tempSticker = (CharacterBase *)hero->_sticker;
		}
		if (tempSticker && is_same(tempSticker->getCharacter()->getCString(), getCharacter()->getCString()) && hero->_isSticking)
		{
			return;
		}
	}

	unschedule(schedule_selector(CharacterBase::getSticker));
	dealloc();
}

void CharacterBase::disableShack()
{
	getGameLayer()->_isShacking = false;
	if (isTower())
	{
		_isHitOne = false;
	}
}

void CharacterBase::setMove(int moveLength)
{
	if (getKnockLength())
	{
		if (getKnockLength() == 1)
			return;

		moveLength = getKnockLength();
	}

	if (getPositionX() > getGameLayer()->currentMap->getTileSize().width &&
		getPositionX() < (getGameLayer()->currentMap->getMapSize().width - 1) * getGameLayer()->currentMap->getTileSize().width)
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

void CharacterBase::setJump(bool jumpDirection)
{
	if (_actionState != State::FLOAT &&
		_actionState != State::AIRHURT &&
		_actionState != State::HURT &&
		_actionState != State::DEAD)
	{
		_actionState = State::JUMP;

		float posX = getPositionX();
		float posY = getPositionY();
		_originY = posY;

		if (jumpDirection) // Jump forward
		{
			_jumpUPAction = CCJumpTo::create(0.8f, ccp(posX + (_isFlipped ? -64 : 64), posY), 64, 1);
		}
		else // Jump back
		{
			_jumpUPAction = CCJumpTo::create(0.8f, ccp(posX + (_isFlipped ? 64 : -64), posY), 64, 1);
		}

		runAction(_jumpUPAction);
	}
}

void CharacterBase::setCharge(int moveLength)
{
	if ((getPositionX() < getGameLayer()->currentMap->getTileSize().width && _isFlipped) ||
		(getPositionX() > (getGameLayer()->currentMap->getMapSize().width - 1) * getGameLayer()->currentMap->getTileSize().width && !_isFlipped))
	{
		return;
	}
	else
	{
		_moveAction = CCMoveBy::create(0.1f, ccp(_isFlipped ? -moveLength * kSpeedBase : moveLength * kSpeedBase, 0));
		runAction(_moveAction);
	}
}

// without getCollider
void CharacterBase::setChargeB(int moveLength)
{
	if ((getPositionX() < getGameLayer()->currentMap->getTileSize().width && _isFlipped) ||
		(getPositionX() > (getGameLayer()->currentMap->getMapSize().width - 1) * getGameLayer()->currentMap->getTileSize().width && !_isFlipped))
	{
		return;
	}
	else
	{
		float delay = (_actionState == State::OATTACK || _actionState == State::O2ATTACK)
						  ? 0.4f
						  : 0.1f;
		_moveAction = CCMoveBy::create(delay, ccp(_isFlipped ? -moveLength * kSpeedBase : moveLength * kSpeedBase, 0));
		runAction(_moveAction);
	}
}

void CharacterBase::setCommand(const string &cmd)
{
	CommandSystem::invoke(cmd, this);
}

void CharacterBase::setBuff(int buffValue)
{
	float buffStayTime = _attackRangeY;

	if (_attackType == "hBuff")
	{
		_healBuffValue = buffValue;
		schedule(schedule_selector(CharacterBase::healBuff), 1);
		setBuffEffect("hBuff");
	}
	else if (_attackType == "sBuff" ||
			 _attackType == "rsBuff" ||
			 _attackType == "hsBuff" ||
			 _attackType == "dcBuff")
	{
		_skillUPBuffValue = buffValue;
		scheduleOnce(schedule_selector(CharacterBase::disableBuff), buffStayTime);
		setBuffEffect(_attackType.c_str());

		setsAttackValue1(to_ccstring(getSAttackValue1() + _skillUPBuffValue));
		setsAttackValue2(to_ccstring(getSAttackValue2() + _skillUPBuffValue));
		setsAttackValue3(to_ccstring(getSAttackValue3() + _skillUPBuffValue));

		if (_attackType == "hsBuff")
		{
			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (isNotSameGroupAs(hero) && hero->isPlayerOrCom() && hero->_actionState != State::HURT && hero->_actionState != State::DEAD)
				{
					float distanceX = ccpSub(hero->getPosition(), getPosition()).x;
					if (distanceX < kAttackRange)
					{
						if (!hero->_isVisable)
						{
							if (hero->isCharacter("Konan") ||
								hero->isCharacter("Deidara"))
							{
								hero->unschedule(schedule_selector(CharacterBase::disableBuff));
							}

							hero->setOpacity(255);
							hero->setVisible(true);
							hero->_isVisable = true;

							if (hero->_hpBar)
								hero->_hpBar->setVisible(true);
							if (hero->_shadow)
								hero->_shadow->setVisible(true);
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
	else if (_attackType == "cBuff")
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
				isNotCharacter("Kankuro") &&
				isNotCharacter("Chiyo") &&
				isNotCharacter("Hiruzen") &&
				isNotCharacter("Suigetsu") &&
				isNotCharacter("Jugo") &&
				isNotCharacter("Kisame") &&
				isNotCharacter("Parents") &&
				isNotCharacter("Lee") &&
				isNotCharacter("RockLee") &&
				isNotCharacter("Nagato"))
			{
				scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
			}
		}

		changeAction();
	}
	else if (_attackType == "tBuff")
	{
		_skillChangeBuffValue = buffValue;
		scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
		scheduleOnce(schedule_selector(CharacterBase::disableBuff), buffStayTime);
		setBuffEffect(_attackType.c_str());

		changeAction();
	}
	else if (_attackType == "gBuff")
	{
		_skillChangeBuffValue = buffValue;
		if (isCharacter("Nagato"))
		{
			if (_skillChangeBuffValue == 18 && hearts == 1)
			{
				scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
			}
		}
		changeAction2();
	}
	else if (_attackType == "stBuff")
	{
		if (isPlayer() || is_same(getGroup()->getCString(), getGameLayer()->currentPlayer->getGroup()->getCString()))
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
	else if (_attackType == "GroupHeal" ||
			 _attackType == "GroupBuff")
	{
		if (_healBuffValue)
			_healBuffValue += buffValue;
		else
			_healBuffValue = buffValue;

		schedule(schedule_selector(CharacterBase::healBuff), 1);
	}

	if (isPlayer())
		getGameLayer()->getHudLayer()->setBuffDisplay(_attackType.c_str(), buffStayTime);
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
		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (isSameGroupAs(hero) && hero->isPlayerOrCom() && hero->_actionState != State::DEAD)
			{
				float distanceX = ccpSub(hero->getPosition(), getPosition()).x;
				float atkRangeX = 128 + getContentSize().width / 2;
				if (abs(distanceX) <= atkRangeX &&
					abs(hero->getPositionY() - getPositionY()) <= 128)
				{
					hero->increaseHpAndUpdateUI(_healBuffValue);

					if (hero->isPlayer())
						getGameLayer()->setHPLose(hero->getHpPercent());

					if (hero->_isVisable)
					{
						Effect *tmpEffect = Effect::create("Kagura", hero);
						if (hero->isPlayer())
						{
							tmpEffect->setOpacity(150);
						}
						tmpEffect->setPosition(ccp(hero->getContentSize().width / 2, hero->getContentSize().height / 2));
						hero->addChild(tmpEffect);
					}
				}
			}
		}
	}
	else if (isCharacter("Chiyo"))
	{
		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (isSameGroupAs(hero) &&
				hero->isPlayerOrCom() &&
				hero->isNotCharacter("Chiyo"))
			{
				CCPoint sp = ccpSub(hero->getPosition(), getPosition());
				if (abs(sp.x) <= kAttackRange)
				{
					hero->increaseAllCkrs(_healBuffValue);

					if (hero->_isVisable)
					{
						Effect *tmpEffect = Effect::create("Hupo", hero);
						if (hero->isPlayer())
						{
							tmpEffect->setOpacity(150);
						}
						tmpEffect->setPosition(ccp(hero->getContentSize().width / 2, hero->getContentSize().height / 2 + 6));
						hero->addChild(tmpEffect);
					}
				}
			}
		}
	}
	else if (isCharacter("Slug"))
	{
		auto list = isAkatsukiGroup()
						? getGameLayer()->_AkatsukiFlogArray
						: getGameLayer()->_KonohaFlogArray;
		for (auto flog : list)
		{
			if (isSameGroupAs(flog) && flog->_actionState != State::DEAD)
			{
				float distanceX = ccpSub(flog->getPosition(), getPosition()).x;
				float atkRangeX = 128 + getContentSize().width / 2;
				if (abs(distanceX) <= atkRangeX &&
					abs(flog->getPositionY() - getPositionY()) <= 128)
				{
					flog->increaseHpAndUpdateUI(_healBuffValue);
				}
			}
		}
	}
	else if (isCharacter("Sakura", "Tsunade"))
	{
		increaseHpAndUpdateUI(_healBuffValue);
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

	for (auto hero : getGameLayer()->_CharacterArray)
	{
		if (hero->isCharacter("Asuma"))
			_slayer = hero;
	}

	if (getHPValue() <= _dehealBuffValue)
		setDamage(_slayer, "c_hit", _dehealBuffValue, false);
	else
		setDamage(_slayer, "c_hit", _dehealBuffValue, false);

	if (isPlayer())
		getGameLayer()->setHPLose(getHpPercent());
}

// NOTE: Only for Shikamaru's KageHand
void CharacterBase::lostBlood(float dt)
{
	for (auto hero : getGameLayer()->_CharacterArray)
	{
		if (hero->isCharacter("Shikamaru"))
			_slayer = hero;
	}

	// if (getHPValue() <= lostBloodValue)
	setDamage(_slayer, "c_hit", lostBloodValue, false);

	if (isPlayer())
		getGameLayer()->setHPLose(getHpPercent());
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
		setAttackType(getSpcAttack2Type());
		_attackRangeX = _spcattackRangeX2;
		_attackRangeY = _spcattackRangeY2;

		setSkill2Action(createAnimation(skillSPC2Array, 10.0f, false, true));
	}
	else if (isCharacter("Nagato"))
	{
		if (_skillChangeBuffValue == 18)
		{
			setHurtAction(createAnimation(skillSPC4Array, 10.0f, false, true));
		}
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
	else if (isCharacter("Nagato"))
	{
		if (_skillChangeBuffValue == 18)
		{
			hearts -= 1;
			setHurtAction(createAnimation(hurtArray, 10.0f, false, true));
		}
		_skillChangeBuffValue = 0;
	}
}

void CharacterBase::getCollider()
{
	schedule(schedule_selector(CharacterBase::stopMove), 0.0f);
}

void CharacterBase::stopMove(float dt)
{
	if (getPositionX() <= getGameLayer()->currentMap->getTileSize().width ||
		getPositionX() >= (getGameLayer()->currentMap->getMapSize().width - 1) * getGameLayer()->currentMap->getTileSize().width)
	{
		unschedule(schedule_selector(CharacterBase::stopMove));
		getActionManager()->removeAction(_moveAction);
		return;
	}

	for (auto hero : getGameLayer()->_CharacterArray)
	{
		if (isNotSameGroupAs(hero) && hero->_isVisable && hero->_actionState != State::DEAD && hero->_actionState != State::JUMP && !hero->_isInvincible)
		{
			float distanceX = ccpSub(hero->getPosition(), getPosition()).x;
			float atkRangeX = _attackRangeX + getContentSize().width / 2;
			if (abs(distanceX) <= atkRangeX &&
				abs(hero->getPositionY() - getPositionY()) <= _attackRangeY)
			{
				unschedule(schedule_selector(CharacterBase::stopMove));
				getActionManager()->removeAction(_moveAction);
				return;
			}
		}
	}
}

void CharacterBase::stopJump(int stopTime)
{
	if (_actionState == State::JUMP)
	{
		getActionManager()->pauseTarget(this);
		scheduleOnce(schedule_selector(CharacterBase::resumePauseStuff), stopTime / 100.0f);
	}
}

void CharacterBase::setBullet(const string &bulletName)
{
	Bullet *bullet = Bullet::create();
	bullet->setID(CCString::create(bulletName), CCString::create("Bullet"), _group);
	bullet->idle();
	bullet->_master = _master ? _master : this;

	if (_isFlipped)
	{
		bullet->setFlipX(true);
		bullet->_isFlipped = true;
	}

	getGameLayer()->addChild(bullet, -getPositionY());

	if (bulletName == "PaperSrk")
	{
		bullet->setScale(0.8f);
		bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32),
								getPositionY() + 52));
		bullet->attack(NAttack);
		bullet->setMove(192, 2.0f, false);
	}
	else if (bulletName == "PaperSpear")
	{
		bullet->setScale(0.8f);
		bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -68 : 68),
								getPositionY() + 42));
		bullet->attack(NAttack);
		bullet->setMove(192, 2.0f, false);
	}
	else if (bulletName == "HugeSRK")
	{
		bullet->setScale(0.8f);
		bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -76 : 76),
								getPositionY() + getHeight() / 2));
		if (_skillUPBuffValue)
			bullet->setnAttackValue(to_ccstring(bullet->getNAttackValue() + _skillUPBuffValue));

		bullet->scheduleOnce(schedule_selector(Bullet::setAttack), 0.5f);
		scheduleOnce(schedule_selector(CharacterBase::setBulletGroup), 0.2f);
		bullet->setEaseIn(224, 5.0f);
	}
	else if (bulletName == "FlyKnife" ||
			 bulletName == "TentenSRK")
	{
		bullet->setScale(0.8f);
		bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32),
								getPositionY() + getHeight() / 2));

		bullet->setEaseIn(224, 2.0f);
		bullet->attack(NAttack);
	}
	else if (bulletName == "HiraishinKunai" ||
			 bulletName == "Shintenshin")
	{
		if (bulletName == "HiraishinKunai")
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
		_monsterArray.push_back(bullet);
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
		getGameLayer()->addChild(bullet, currentSkillTag);
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

void CharacterBase::setClone(int cloneTime)
{
	Hero *clone = createClone(cloneTime);
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

	clone->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32), getPositionY() - 1));

	if (isCharacter("SageNaruto", "Naruto") ||
		(isCharacter("RikudoNaruto") && cloneTime == 10))
	{
		clone->setHPValue(getHPValue(), false);
	}
	else
	{
		clone->setHPValue(getMaxHPValue(), false);
	}

	clone->setMaxHPValue(getMaxHPValue(), false);
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
	clone->setSkillEffect("smk");
	clone->idle();
	getGameLayer()->_CharacterArray.push_back(clone);
	getGameLayer()->addChild(clone, -clone->getPositionY());
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

void CharacterBase::setMon(const string &monName)
{
	float monsterStayTime = _attackRangeY;

	auto monster = Monster::create();
	monster->setID(CCString::create(monName), CCString::create(kRoleMon), _group);

	if (_master)
	{
		if (getSecMaster())
		{
			monster->setMaster(this);
			monster->setSecMaster(getSecMaster());
		}
		else
		{
			monster->setMaster(_master);
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

	if (monName == "FakeDeidara" ||
		monName == "FakeKisame" ||
		monName == "DeidaraBom" ||
		monName == "ChuiDi" ||
		monName == "SakuraBom" ||
		monName == "Shoryu" ||
		monName == "Stream" ||
		monName == "FakeMinato")
	{
		monster->setPosition(ccp(getPositionX(), _originY ? _originY : getPositionY()));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "LeeBom")
	{
		// monster->setAnchorPoint(ccp(0.5,0.5f));
		monster->setPosition(ccp(getPositionX(), getPositionY()));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "FakeItachi")
	{
		monster->setPosition(ccp(getPositionX(), _originY ? _originY : getPositionY() - 4));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "Tenmu")
	{
		monster->setPosition(ccp(getPositionX(), _originY));
		monster->setAnchorPoint(ccp(0.5, -0.1f));
		monster->attack(NAttack);
	}
	else if (monName == "Kaiten")
	{
		monster->setPosition(ccp(getPositionX(), getPositionY()));
		monster->setAnchorPoint(ccp(0.5, 0.25f));
		monster->attack(NAttack);
	}
	else if (monName == "Crash" ||
			 monName == "Crash2")
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32), _originY ? _originY : getPositionY()));
		monster->setAnchorPoint(ccp(0.5, 0.25f));
		monster->attack(NAttack);
	}
	else if (monName == "SansyoRed")
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 240 : getPositionX() + 240, getPositionY() - 32));
		monster->attack(NAttack);
	}
	else if (monName == "SansyoGreen")
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 144 : getPositionX() + 144, getPositionY() - 32 + 1));
		monster->attack(NAttack);
	}
	else if (monName == "SansyoBlue")
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 48 : getPositionX() + 48, getPositionY() - 32 + 2));
		monster->attack(NAttack);
	}
	else if (monName == "SmallSlug")
	{
		if (_monsterArray.size() < 3)
		{
			monster->setSkillEffect("smk");
			_monsterArray.push_back(monster);
			monster->doAI();
		}
		else
		{
			monster = nullptr;
			return;
		}
	}
	else if (monName == "Kuroari")
	{
		monster->setSkillEffect("smk");
		_monsterArray.push_back(monster);
		monster->doAI();
	}
	else if (monName == "PaperRain" ||
			 monName == "Steam")
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 16 : getPositionX() + 16, _originY));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "FireRain")
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 75 : getPositionX() + 75, _originY - 1));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "Tuji" ||
			 monName == "Tuji2" ||
			 monName == "Suiji")
	{
		monster->setPositionY(getPositionY() - 24);
		monster->setPositionX(getPositionX() + (_isFlipped ? -64 : 64));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "ThunderWave")
	{
		monster->setPosition(ccp(getPositionX(), getPositionY() - 1));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "Jibaku" ||
			 monName == "JibakuEX" ||
			 monName == "Shenwei")
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -96 : 96), getPositionY()));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "Bikyu")
	{
		monster->setFlipX(_isFlipped);
		monster->hasArmorBroken = true;
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -(16 + getContentSize().width) : (16 + getContentSize().width)), getPositionY() - 32));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "Qilin")
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -4 : 4), getPositionY() - 6));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "Laser")
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -100 : 100), getPositionY()));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "MagicDragon")
	{
		monster->hasArmorBroken = true;
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
		monster->setDirectMove(156, 2.0f, false);
	}
	else if (monName == "Chameleon" ||
			 monName == "Naraka" ||
			 monName == "Roar" ||
			 monName == "Smoke" ||
			 monName == "BannShou" ||
			 monName == "Bull" ||
			 monName == "Raintiger")
	{
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "SuiRyuDan" ||
			 monName == "DotonPillar" ||
			 monName == "Yataikuzu" ||
			 monName == "Yominuma" ||
			 monName == "Dogs" ||
			 monName == "SandHand" ||
			 monName == "KageFeng" ||
			 monName == "Sanbao" ||
			 monName == "SandBall" ||
			 monName == "Sabaku" ||
			 monName == "SandWave" ||
			 monName == "Tsukuyomi" ||
			 monName == "Shark")
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped == true ? -48 : 48), getPositionY() - 4));
		monster->attack(NAttack);
	}
	else if (monName == "Suijin" ||
			 monName == "BugPillar")
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped == true ? -64 : 64), getPositionY() + 1));
		monster->attack(NAttack);
	}
	else if (monName == "Mine")
	{
		monster->setSkillEffect("smk");
		_monsterArray.push_back(monster);
		monster->doAI();
		if (strcmp(getGroup()->getCString(), getGameLayer()->currentPlayer->getGroup()->getCString()) != 0)
		{
			monster->setVisible(false);
		}
	}
	else if (monName == "Kage")
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
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
		monster->doAI();
	}
	else if (monName == "KageHand")
	{
		CCPoint dir = ccp(_isFlipped ? getPositionX() - getContentSize().width : getPositionX() + getContentSize().width, getPositionY());
		monster->setPosition(dir);
		stopAllActions();

		if (_master)
			_master->_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "KageHands")
	{
		if (_master)
			_master->_monsterArray.push_back(monster);
		monster->setPosition(ccp(getPositionX(), getPositionY()));
		monster->setAnchorPoint(ccp(0.5f, 0.15f));
		monster->attack(NAttack);
	}
	else if (monName == "QuanRen")
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 64 : getPositionX() + 64, _originY));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "ItachiSusano" ||
			 monName == "SasukeSusano")
	{
		_monsterArray.push_back(monster);
	}
	else if (monName == "HiraishinMark")
	{
		_monsterArray.push_back(monster);
		_isCanSkill1 = true;
	}
	else if (monName == "CircleMark")
	{
		monster->setPosition(ccp(getPositionX(), getPositionY()));
		monster->setAnchorPoint(ccp(0.5f, 0.5f));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);

		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill1Button->setLock();
		}
	}
	else if (monName == "InkDragon")
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 128 : getPositionX() + 128, getPositionY()));
		monster->attack(NAttack);
		monster->setDirectMove(156, 2.0f, false);
	}
	else if (monName == "BugTomado")
	{
		monster->attack(NAttack);
		monster->setDirectMove(128, 2.0f, false);
	}
	else if (monName == "FutonSRK2" ||
			 monName == "FutonSRK")
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
	else if (monName == "Kubi")
	{
		monster->attack(NAttack);
		monster->setDirectMove(128, 0.8f, true);
	}
	else if (monName == "Shark2")
	{
		monster->attack(NAttack);
		monster->setEaseIn(224, 3.0f);
	}
	else if (monName == "WaterBullet" ||
			 monName == "BoneBullet" ||
			 monName == "WaterBom")
	{
		monster->attack(NAttack);
		monster->setEaseIn(224, 1.0f);
	}
	else if (monName == "Hasan")
	{
		monster->attack(NAttack);
		monster->setAnchorPoint(ccp(0.5f, 0.28f));
		monster->setPosition(ccp(getPositionX() + (_isFlipped == true ? -24 : 24), getPositionY()));
		monster->setEaseIn(224, 1.0f);
	}
	else if (monName == "Wave")
	{
		monster->attack(NAttack);
		monster->setAnchorPoint(ccp(0.5f, 0.1f));
		monster->setPosition(ccp(getPositionX() + (_isFlipped == true ? -24 : 24), getPositionY()));
		monster->setEaseIn(224, 1.0f);
	}
	else if (monName == "InkBird" ||
			 monName == "FakeTobirama" ||
			 monName == "TamaBomb" ||
			 monName == "Shenwei2")
	{
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else
	{
		_monsterArray.push_back(monster);
		monster->doAI();
	}

	if (monName == "ItachiSusano")
	{
		monster->setFlipX(_isFlipped);
		monster->setAnchorPoint(ccp(0.5f, 0));
		monster->setPosition(ccp(146 / 2 - 10, -40));
		addChild(monster, -1000);
	}
	else if (monName == "SasukeSusano")
	{
		monster->setFlipX(_isFlipped);
		monster->setAnchorPoint(ccp(0.5f, 0));
		monster->setPosition(ccp(141 / 2, -6));
		addChild(monster, -1000);
	}
	else if (monName == "CircleMark" ||
			 monName == "Yominuma")
	{
		getGameLayer()->addChild(monster, -5000);
	}
	else
	{
		getGameLayer()->addChild(monster, -monster->getPositionY());
	}
}

void CharacterBase::setMonPer(float dt)
{
	auto monster = Monster::create();

	if (isCharacter("Deidara"))
	{
		monster->setID(CCString::create("Spider"), CCString::create(kRoleMon), _group);
	}
	else if (isCharacter("Sai"))
	{
		monster->setID(CCString::create("Mouse"), CCString::create(kRoleMon), _group);
		setSound("Audio/Sai/ink_mouse.ogg");
	}

	monster->setMaster(this);

	monster->idle();
	monster->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32), _originY ? _originY : getPositionY()));
	monster->setFlipX(_isFlipped);
	monster->_isFlipped = _isFlipped;

	_monsterArray.push_back(monster);
	monster->doAI();

	getGameLayer()->addChild(monster, -monster->getPositionY());
}

void CharacterBase::setTrap(const string &trapName)
{
	if (trapName == "Amaterasu")
	{
		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (isNotSameGroupAs(hero) && hero->isPlayerOrCom() && hero->_actionState != State::HURT && hero->_actionState != State::DEAD)
			{
				float distanceX = ccpSub(hero->getPosition(), getPosition()).x;
				if (distanceX < kAttackRange)
				{
					if (!hero->_isVisable)
					{
						if (hero->isCharacter("Konan") ||
							hero->isCharacter("Deidara"))
						{
							hero->unschedule(schedule_selector(CharacterBase::disableBuff));
						}

						hero->setOpacity(255);
						hero->setVisible(true);
						hero->_isVisable = true;

						if (hero->_hpBar)
							hero->_hpBar->setVisible(true);
						if (hero->_shadow)
							hero->_shadow->setVisible(true);
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
					trap->_master = this;
					trap->setID(CCString::create(trapName), CCString::create(kRoleMon), _group);
					trap->setAnchorPoint(ccp(0.5, 0));
					trap->setPosition(ccp(targetPoint.x, targetPoint.y + 32));
					trap->idle();
					trap->attack(NAttack);
					trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 4.0f);
					getGameLayer()->addChild(trap, -trap->getPositionY());
				}
				else if (z == 1)
				{
					for (int i = 0; i < 3; i++)
					{
						Bullet *trap = Bullet::create();
						trap->_master = this;
						trap->setID(CCString::create(trapName), CCString::create(kRoleMon), _group);
						trap->setAnchorPoint(ccp(0.5, 0));
						trap->setPosition(ccp(targetPoint.x + (i - 1) * 60, targetPoint.y));
						trap->idle();
						trap->attack(NAttack);
						trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 4.0f);
						getGameLayer()->addChild(trap, -trap->getPositionY());
					}
				}
				else if (z == 2)
				{
					Bullet *trap = Bullet::create();
					trap->_master = this;
					trap->setID(CCString::create(trapName), CCString::create(kRoleMon), _group);
					trap->setAnchorPoint(ccp(0.5, 0));
					trap->setPosition(ccp(targetPoint.x, targetPoint.y - 32));
					trap->idle();
					trap->attack(NAttack);
					trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 4.0f);
					getGameLayer()->addChild(trap, -trap->getPositionY());
				}
			}
		}
		else
		{
			for (int z = 0; z < 3; z++)
			{
				if (z == 0)
				{
					for (int i = 0; i < 3; i++)
					{
						Bullet *trap = Bullet::create();
						trap->_master = this;
						trap->setID(CCString::create(trapName), CCString::create(kRoleMon), _group);

						trap->setPosition(ccp(getPositionX() + (_isFlipped ? -112 : 112), getPositionY() + (48 - i * 24)));
						trap->idle();
						trap->attack(NAttack);
						trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 2.5f);
						getGameLayer()->addChild(trap, -trap->getPositionY());
					}
				}
				else if (z == 1)
				{
					for (int i = 0; i < 2; i++)
					{
						Bullet *trap = Bullet::create();
						trap->_master = this;
						trap->setID(CCString::create(trapName), CCString::create(kRoleMon), _group);
						trap->setPosition(ccp(getPositionX() + (_isFlipped ? -80 : 80), getPositionY() + (32 - i * 24)));
						trap->idle();
						trap->attack(NAttack);
						trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 2.5f);
						getGameLayer()->addChild(trap, -trap->getPositionY());
					}
				}
				else
				{
					Bullet *trap = Bullet::create();
					trap->_master = this;
					trap->setID(CCString::create(trapName), CCString::create(kRoleMon), _group);
					trap->setPosition(ccp(getPositionX() + (_isFlipped ? -48 : 48), getPositionY() + 22));
					trap->idle();
					trap->attack(NAttack);
					trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 2.5f);
					getGameLayer()->addChild(trap, -trap->getPositionY());
				}
			}
		}
	}
	else
	{
		onSetTrap(trapName);
	}
}

void CharacterBase::removeSelf(float dt)
{
	dealloc();
}

void CharacterBase::setMonAttack(int skillNum)
{
	for (auto mo : _monsterArray)
	{
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
						// mo->attack(SKILL1);
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

void CharacterBase::setTransform()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "acceptAttack");
	unschedule(schedule_selector(CharacterBase::dehealBuff));

	if (isCharacter("Lee", "RockLee"))
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

	auto tempAttackValue = getNAttackValueStr();
	setnAttackValue(tempAttackValue);

	setMaxHPValue(getMaxHPValue(), false);
	setHPValue(getHPValue());

	if (_hpBar)
	{
		_hpBar->setPositionY(getHeight());
	}

	if (isGearCD)
	{
		_sattackcooldown1 -= 5;
		_sattackcooldown2 -= 5;
		_sattackcooldown3 -= 5;
	}

	if (isPlayer())
		getGameLayer()->setHPLose(getHpPercent());

	// NOTE: Update HudLayer logic was moved to Hero::setID
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
		if (!getGameLayer()->getSkillFinish() && !_isOnlySkillLocked)
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
				getGameLayer()->getHudLayer()->skill1Button->click();
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
				getGameLayer()->getHudLayer()->skill2Button->click();
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
				getGameLayer()->getHudLayer()->skill3Button->click();
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
			uint32_t ckr = getCkrValue();
			if (ckr >= 15000)
			{
				ckr -= 15000;
				setCkrValue(ckr);
			}
			else
			{
				setCkrValue(0);
			}
			if (ckr < 15000)
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
			uint32_t ckr2 = getCkr2Value();
			if (ckr2 >= 25000)
			{
				ckr2 -= 25000;
				setCkr2Value(ckr2);
			}
			else
			{
				setCkr2Value(0);
			}
			if (ckr2 < 25000)
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
				getGameLayer()->setSkillFinish(false);
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
					getGameLayer()->setSkillFinish(false);
				}
				runAction(_skill1Action);
			}
			_isCanSkill1 = false;

			scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sattackcooldown1);
			break;
		case SKILL2:
			if (_isCanSkill2)
			{
				_actionState = State::SATTACK;
				if (isPlayer())
				{
					getGameLayer()->setSkillFinish(false);
				}
				runAction(_skill2Action);
			}

			_isCanSkill2 = false;

			scheduleOnce(schedule_selector(CharacterBase::enableSkill2), _sattackcooldown2);

			break;
		case SKILL3:
			if (_isCanSkill3)
			{
				_actionState = State::SATTACK;
				if (isPlayer())
				{
					getGameLayer()->setSkillFinish(false);
				}
				runAction(_skill3Action);
			}
			_isCanSkill3 = false;

			scheduleOnce(schedule_selector(CharacterBase::enableSkill3), _sattackcooldown3);
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
			getGameLayer()->setSkillFinish(false);
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
	return getGameLayer()->checkHasAnyMovement();
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
				getGameLayer()->setSkillFinish(true);
			}
		}

		if (!getGameLayer()->_isAttackButtonRelease &&
			_isPlayer &&
			!_attackType.empty() &&
			!_isAllAttackLocked)
		{
			getGameLayer()->setSkillFinish(true);
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
				for (auto mo : _monsterArray)
				{
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

		_velocity = ccp(direction.x * _walkSpeed * kSpeedBase, direction.y * _walkSpeed * kSpeedBase);
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
		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (isSameGroupAs(hero) &&
				hero->isCharacter("Chiyo") &&
				hero->_actionState != State::DEAD &&
				hero->_buffStartTime)
			{
				CCPoint sp = ccpSub(hero->getPosition(), getPosition());
				if (abs(sp.x) <= kAttackRange)
				{
					return false;
				}
			}
		}
		if (isCharacter("Chiyo"))
		{
			for (auto mo : _monsterArray)
			{
				if (mo->isCharacter("Parents") && !mo->_skillChangeBuffValue && mo->_actionState != State::SATTACK && mo->_actionState != State::DEAD)
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
			getGameLayer()->setSkillFinish(false);
		}

		_actionState = State::HURT;
		stopAllActions();
		if (_hurtAction)
		{
			auto call = CallFunc::create(std::bind(&CharacterBase::idle, this));
			auto seq = newSequence(_hurtAction, call);
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
			getGameLayer()->reorderChild(this, -getPositionY());
		}

		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (isSameGroupAs(hero) &&
				hero->isCharacter("Chiyo") &&
				hero->_actionState != State::DEAD &&
				hero->_buffStartTime)
			{
				CCPoint sp = ccpSub(hero->getPosition(), getPosition());
				if (abs(sp.x) <= kAttackRange)
				{
					return false;
				}
			}
		}

		if (isCharacter("Chiyo"))
		{
			for (auto mo : _monsterArray)
			{
				if (mo->isCharacter("Parents") && !mo->_skillChangeBuffValue && mo->_actionState != State::SATTACK && mo->_actionState != State::DEAD)
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
			getGameLayer()->setSkillFinish(false);
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
			string path = getCharacter()->getCString();
			if (attacker->isCharacter("Kakuzu"))
				path += "_AirHurt_02";
			else
				path += "_Hurt_02";

			auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path.c_str());
			if (frame == nullptr)
			{ // Try use xxx_AirHurt_01 instead of xxx_AirHurt_02
				path = getCharacter()->getCString();
				path += "_AirHurt_01";
				frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path.c_str());

				if (frame == nullptr)
					CCMessageBox(path.c_str(), "Not found hard hurt frame");
			}

			auto tempArray = CCArray::create();
			tempArray->addObject(frame);
			auto tempAnimation = CCAnimation::createWithSpriteFrames(tempArray, 0.1f);
			auto tempAction = CCAnimate::create(tempAnimation);
			list->addObject(tempAction);
		}

		if (isStun)
		{
			auto call = CallFunc::create(std::bind(&CharacterBase::setSkillEffect, this, "stun"));
			list->addObject(call);
		}

		auto delay = CCDelayTime::create(delayTime / 1000.0f);
		list->addObject(delay);

		auto call = CallFunc::create(std::bind(&CharacterBase::idle, this));
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
			getGameLayer()->setSkillFinish(false);
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
			getGameLayer()->setSkillFinish(false);
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

		auto call = CallFunc::create(std::bind(&CharacterBase::idle, this));
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
		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (isSameGroupAs(hero) &&
				hero->isCharacter("Chiyo") &&
				hero->_actionState != State::DEAD &&
				hero->_buffStartTime)
			{
				CCPoint sp = ccpSub(hero->getPosition(), getPosition());
				if (abs(sp.x) <= kAttackRange)
				{
					return;
				}
			}
		}

		if (isCharacter("Chiyo"))
		{
			for (auto mo : _monsterArray)
			{
				if (mo->isCharacter("Parents") && !mo->_skillChangeBuffValue && mo->_actionState != State::SATTACK && mo->_actionState != State::DEAD)
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
			getGameLayer()->setSkillFinish(false);
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

		auto call = CallFunc::create(std::bind(&CharacterBase::knockDown, this));
		_floatUPAction = newSequence(_floatAwayAction, call);

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

				getGameLayer()->currentPlayer = _controller;
				getGameLayer()->getHudLayer()->updateSkillButtons();
			}

			getGameLayer()->controlChar = nullptr;
		}

		changeGroup();

		if (isPlayer())
		{
			_isAI = false;
			getGameLayer()->getHudLayer()->_isAllButtonLocked = false;
		}

		if (_controller->_actionState != State::DEAD)
		{
			_controller->unschedule(schedule_selector(CharacterBase::resumeAction));
			_controller->idle();
			_controller->_isArmored = false;
		}

		_controller = nullptr;
	}

	if (isCharacter("Minato", "Nagato"))
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
		getGameLayer()->setSkillFinish(false);
		getGameLayer()->getHudLayer()->hpLabel->setString("0");
		getGameLayer()->getHudLayer()->status_hpbar->setOpacity(0);
	}

	// kill all buffEffect
	if (isPlayerOrCom())
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
				auto deadStr = getGameLayer()->getHudLayer()->deadLabel->getString();
				int deads = to_int(deadStr) + 1;
				getGameLayer()->getHudLayer()->deadLabel->setString(to_cstr(deads));
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
		getGameLayer()->reorderChild(this, -getPositionY());
	}

	stopAllActions();
	_actionState = State::DEAD;

	if (isPlayerOrCom())
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", this);
	}

	if (isNotClone() && isNotSummon())
	{
		auto fadeOut = CCFadeOut::create(0.5);
		auto call = CallFunc::create(std::bind(&CharacterBase::dealloc, this));
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
		setSkillEffect("smk");
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
		auto call = CallFunc::create(std::bind(&CharacterBase::dealloc, this));
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
	if (is_same(kRoleHero, type))
	{
		return findEnemyBy(getGameLayer()->_CharacterArray, searchRange, masterRange);
	}
	else if (is_same(kRoleFlog, type))
	{
		if (isAkatsukiGroup())
			return findEnemyBy(getGameLayer()->_KonohaFlogArray, searchRange, masterRange);
		else
			return findEnemyBy(getGameLayer()->_AkatsukiFlogArray, searchRange, masterRange);
	}
	else if (is_same(kRoleTower, type))
	{
		return findEnemyBy(getGameLayer()->_TowerArray, searchRange, masterRange);
	}

	return false;
}

template <typename T>
typename std::enable_if<std::is_base_of<CharacterBase, T>::value, bool>::type
// template find ememy
CharacterBase::findEnemyBy(const vector<T *> &list, int searchRange, bool masterRange)
{
	float distance;
	float curDistance = 0;
	CCPoint sp;
	bool findSome = false;

	for (auto target : list)
	{
		if (target->_actionState == State::DEAD ||
			target->_isVisable == false ||
			target->_isInvincible ||
			target->isKugutsu())
		{
			continue;
		}

		if ((_actionState == State::OATTACK || _actionState == State::O2ATTACK) ||
			(_master && (_master->_actionState == State::OATTACK || _actionState == State::O2ATTACK)))
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
			if (masterRange && _master)
			{
				distance = ccpDistance(target->getPosition(), _master->getPosition());
				sp = ccpSub(target->getPosition(), _master->getPosition());
			}
			else
			{
				distance = ccpDistance(target->getPosition(), getPosition());
				sp = ccpSub(target->getPosition(), getPosition());
			}

			if (abs(sp.x) < (searchRange ? searchRange : kAttackRange))
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
	if (is_same(kRoleHero, type))
	{
		return findEnemy2By(getGameLayer()->_CharacterArray);
	}
	else if (is_same(kRoleFlog, type))
	{
		if (isAkatsukiGroup())
			return findEnemy2By(getGameLayer()->_KonohaFlogArray);
		else
			return findEnemy2By(getGameLayer()->_AkatsukiFlogArray);
	}
	else if (is_same(kRoleTower, type))
	{
		return findEnemy2By(getGameLayer()->_TowerArray);
	}

	return false;
}

template <typename T>
typename std::enable_if<std::is_base_of<CharacterBase, T>::value, bool>::type
// template find ememy 2
CharacterBase::findEnemy2By(const vector<T *> &list)
{
	float distance;
	float curDistance = 0;
	CCPoint sp;
	bool findSome = false;

	enemyCombatPoint = 0;
	friendCombatPoint = 0;

	for (auto target : list)
	{
		if (target->_actionState == State::DEAD ||
			target->_isVisable == false ||
			target->isKugutsu())
		{
			continue;
		}

		distance = ccpDistance(target->getPosition(), getPosition());
		sp = ccpSub(target->getPosition(), getPosition());
		if (abs(sp.x) < kAttackRange)
		{
			if (target->isNotClone() && target->isNotSummon())
			{
				int baseSkillCombatPoint = 0;

				if (target->_isCanSkill1)
					baseSkillCombatPoint += _sattackCombatPoint1;
				if (target->_isCanSkill2)
					baseSkillCombatPoint += _sattackCombatPoint2;
				if (target->_isCanSkill2)
					baseSkillCombatPoint += _sattackCombatPoint3;

				if (is_same(_group->getCString(), target->_group->getCString()))
				{
					if (abs(sp.x) < getGameLayer()->currentMap->getTileSize().width * 3)
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

					if (!target->_isInvincible && (target->getPositionX() >= getGameLayer()->currentMap->getTileSize().width * 3 && target->getPositionX() <= (getGameLayer()->currentMap->getMapSize().width - 3) * getGameLayer()->currentMap->getTileSize().width))
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

bool CharacterBase::findTargetEnemy(const char *type, bool isTowerDected)
{
	if (is_same(kRoleHero, type))
	{
		return findTargetEnemyBy(getGameLayer()->_CharacterArray, isTowerDected);
	}
	else if (is_same(kRoleFlog, type))
	{
		if (isAkatsukiGroup())
			return findTargetEnemyBy(getGameLayer()->_KonohaFlogArray, isTowerDected);
		else
			return findTargetEnemyBy(getGameLayer()->_AkatsukiFlogArray, isTowerDected);
	}

	return false;
}

template <typename T>
typename std::enable_if<std::is_base_of<CharacterBase, T>::value, bool>::type
CharacterBase::findTargetEnemyBy(const vector<T *> &list, bool isTowerDected)
{
	float curDistance = 0;
	CCPoint sp;
	bool findSome = false;

	for (auto target : list)
	{
		if (isNotSameGroupAs(target) &&
			target->isNotKugutsu() &&
			target->_actionState != State::DEAD &&
			target->_isVisable && !target->_isInvincible)
		{
			// float gardZone
			findSome = getGameLayer()->playerGroup == Konoha
						   ? target->getPositionX() <= 14 * 32
						   : target->getPositionX() >= 81 * 32;

			if (findSome)
			{
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

	if (!isTowerDected)
		return findSome;
	else
		return false;
}

bool CharacterBase::checkBase()
{
	for (auto target : getGameLayer()->_CharacterArray)
	{
		if (target->_actionState == State::DEAD)
			continue;

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

	auto &flogArray = isAkatsukiGroup()
						  ? getGameLayer()->_KonohaFlogArray
						  : getGameLayer()->_AkatsukiFlogArray;

	for (auto target : flogArray)
	{
		if (target->_actionState == State::DEAD)
			continue;

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

	if (getPositionX() >= getGameLayer()->currentMap->getTileSize().width * 2 &&
		getPositionX() <= (getGameLayer()->currentMap->getMapSize().width - 2) * getGameLayer()->currentMap->getTileSize().width)
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
			if (getPositionY() + 96 < getGameLayer()->currentMap->getTileSize().height * 5.5)
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
			if (_diretionY == 1 && (getPositionY() >= _backY || getPositionY() > getGameLayer()->currentMap->getTileSize().height * 5))
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
			if (_diretionY == 1 && getPositionY() <= getGameLayer()->currentMap->getTileSize().height * 5)
			{
				_diretionY = 1;
				_backY = getGameLayer()->currentMap->getTileSize().height * 5;
			}
			else if (getPositionY() > 16)
			{
				_diretionY = -1;
				_backY = 16;
			}
		}
	}

	if (isKonohaGroup() && getPositionX() >= getGameLayer()->currentMap->getTileSize().width * 2)
	{
		moveDirection = ccp(-1, _diretionY);
		walk(moveDirection);
		return true;
	}
	else if (isAkatsukiGroup() && getPositionX() <= (getGameLayer()->currentMap->getMapSize().width - 2) * getGameLayer()->currentMap->getTileSize().width)
	{
		moveDirection = ccp(1, _diretionY);
		walk(moveDirection);
		return true;
	}
	else
	{
		return false;
	}
}

// [For AI] 检查角色是否需要使用【拉面】回血，若血量低于界限，则返回true
bool CharacterBase::checkRetri()
{
	if (_isCanItem1 && getCoin() >= 50)
	{
		if (getGameLayer()->_isHardCoreGame)
		{
			if (battleCondiction >= 0)
			{
				if (!_isHealing)
				{
					if (getMaxHPValue() - getHPValue() >= 3000 + gearRecoverValue && getGearArray().size() > 1)
						setItem(Item1);
					else if (getHPValue() < 5000 && getGearArray().size() > 0)
						setItem(Item1);
					else if (getHPValue() < 1500)
						setItem(Item1);
				}
			}
			else
			{
				if (getMaxHPValue() - getHPValue() >= 3000 + gearRecoverValue && !_isHealing && getGearArray().size() > 0)
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
			if (getPositionX() >= getGameLayer()->currentMap->getTileSize().width * 60)
				return false;
		}
		else
		{
			if (getPositionX() <= getGameLayer()->currentMap->getTileSize().width * 36)
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
			for (auto mo : _monsterArray)
			{
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
		if (strcmp(getGroup()->getCString(), getGameLayer()->currentPlayer->getGroup()->getCString()) != 0)
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
		changeGroupBy(getGameLayer()->_CharacterArray);
		changeGroupBy(getGameLayer()->_TowerArray);
		changeGroupBy(getGameLayer()->_AkatsukiFlogArray);
		changeGroupBy(getGameLayer()->_KonohaFlogArray);
	}
}

template <typename T>
typename std::enable_if<std::is_base_of<CharacterBase, T>::value, void>::type
CharacterBase::changeGroupBy(const vector<T *> &list)
{
	for (auto target : list)
	{
		if (target->_hpBar == nullptr)
			continue;
		if (strcmp(_group->getCString(), target->_group->getCString()) != 0)
		{
			if (target->isFlog())
				target->_hpBar->changeBar("flog_bar_r.png");
			else
				target->_hpBar->changeBar("hp_bar_r.png");
		}
		else
		{
			if (target->isFlog())
				target->_hpBar->changeBar("flog_bar.png");
			else if (target->isTower())
				target->_hpBar->changeBar("hp_bar.png");
			else if (target->isNotPlayer())
				target->_hpBar->changeBar("hp_bar_b.png");
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

/**
 * Utilities
 */

void CharacterBase::increaseAllCkrs(uint32_t value, bool enableLv2, bool enableLv4)
{
	if (_level >= 2 && enableLv2)
	{
		uint32_t ckr = MIN(getCkrValue() + value, 45000);
		setCkrValue(ckr);

		if (ckr >= 15000)
			_isCanOugis1 = true;

		if (isPlayer())
			getGameLayer()->setCKRLose(false);
	}

	if (_level >= 4 && enableLv4)
	{
		uint32_t ckr2 = MIN(getCkr2Value() + value, 50000);
		setCkr2Value(ckr2);

		if (ckr2 >= 25000)
			_isCanOugis2 = true;

		if (isPlayer())
			getGameLayer()->setCKRLose(true);
	}
}

void CharacterBase::increaseHpAndUpdateUI(uint32_t value)
{
	setHPValue(MIN(getHPValue() + value, getMaxHPValue()));
}

void CharacterBase::updateHpBar()
{
	if (_hpBar)
		_hpBar->loseHP(getHpPercent());
}
