#include "Defines.h"
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
	uint32_t tempMaxHP = to_uint(getMaxHP()->getCString());
	int attackValue = to_int(getnAttackValue()->getCString());
	if (_level >= 2)
	{
		_isCanOugis1 = true;
		if (strcmp(getRole()->getCString(), "Player") == 0)
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
		if (strcmp(getRole()->getCString(), "Player") == 0)
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
	setMaxHP(CCString::createWithFormat("%d", tempMaxHP));
	setnAttackValue(CCString::createWithFormat("%d", attackValue));
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
		if (strcmp(_role->getCString(), "Player") == 0 || strcmp(_role->getCString(), "Com") == 0)
		{
			if (strcmp(_character->getCString(), Guardian_Roshi) != 0 &&
				strcmp(_character->getCString(), Guardian_Han) != 0)
			{
				if (strcmp(_group->getCString(), Konoha) == 0 && getPositionX() <= 11 * 32)
				{
					_isHealling = true;
					if (getHpPercent() < 1.0f)
					{
						scheduleOnce(schedule_selector(CharacterBase::setRestore), 1.0f);
					}
				}
				else if (strcmp(_group->getCString(), Akatsuki) == 0 && getPositionX() >= 85 * 32)
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

		if (strcmp(_role->getCString(), "Player") == 0 && !_isAI && !_isInvincible && !_isArmored)
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
		if (strcmp(getRole()->getCString(), "Player") == 0 || strcmp(getRole()->getCString(), "Com") == 0)
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
	CharacterBase *attacker = (CharacterBase *)object;
	bool isCannotMiss = false;

	if (strcmp(getCharacter()->getCString(), "Tobi") == 0)
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

	if (strcmp(attacker->getCharacter()->getCString(), "Hiruzen") == 0 && attacker->getActionState() == State::O2ATTACK)
	{
		isCannotMiss = true;
	}

	if (strcmp(_group->getCString(), attacker->_group->getCString()) != 0 && _isVisable && (!_isInvincible || isCannotMiss) && getActionState() != State::DEAD)
	{
		// Tower
		if (strcmp(_role->getCString(), "Tower") == 0)
		{
			bool isHit = false;
			if (strcmp(attacker->_attackType->getCString(), "nAttack") == 0 &&
				strcmp(attacker->_effectType->getCString(), "f_hit") != 0 &&
				strcmp(attacker->_effectType->getCString(), "c_hit") != 0 &&
				strcmp(attacker->_effectType->getCString(), "o_hit") != 0 &&
				strcmp(attacker->_effectType->getCString(), "b_hit") != 0 &&
				strcmp(attacker->_effectType->getCString(), "bc_hit") != 0)
			{
				if (setHitBox().intersectsRect(attacker->setHalfBox()))
				{
					isHit = true;
				}
			}
			else if (strcmp(attacker->_effectType->getCString(), "n_hit") == 0)
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
					CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::disableShack));
					CCDelayTime *delay = CCDelayTime::create(0.5f);
					CCArray *list = CCArray::create();
					list->addObject(CCShake::createWithStrength(0.1f, 2, 0));
					list->addObject(delay);
					list->addObject(call);
					runAction(CCSequence::create(list));
				}
			}

			return;
		}
		// Bullet
		else if (strcmp(attacker->_role->getCString(), "Bullet") == 0)
		{
			if (setHitBox().intersectsRect(attacker->setHitBox()))
			{
				if (strcmp(getCharacter()->getCString(), "Hidan") == 0 && _skillChangeBuffValue)
				{
					bool _isCounter = false;
					if (_monsterArray && _monsterArray->count() > 0)
					{
						CCObject *pObject;
						CCARRAY_FOREACH(_monsterArray, pObject)
						{
							CharacterBase *tempMonster = (CharacterBase *)pObject;
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
							Hero *tempHero = (Hero *)pObject;
							if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0 && (strcmp(tempHero->_role->getCString(), "Player") == 0 || strcmp(tempHero->_role->getCString(), "Com") == 0) && tempHero->_actionState != State::DEAD)
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
				if (strcmp(attacker->_character->getCString(), "HiraishinKunai") == 0 ||
					strcmp(attacker->_character->getCString(), "Shintenshin") == 0)
				{
					if ((strcmp(_role->getCString(), "Player") == 0 || strcmp(_role->getCString(), "Com") == 0) && strcmp(_character->getCString(), Guardian_Roshi) != 0 && strcmp(_character->getCString(), Guardian_Han) != 0 && _actionState != State::DEAD)
					{
						attacker->stopAllActions();
						attacker->dealloc();

						if (strcmp(attacker->_character->getCString(), "Shintenshin") == 0 && !attacker->_isCatchOne)
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

								if (strcmp(_controller->getRole()->getCString(), "Player") == 0)
								{
									unschedule(schedule_selector(CharacterBase::setAI));
									_isAI = false;
									// Set controlled character to player
									_delegate->currentPlayer = this;
									_delegate->getHudLayer()->updateSkillButtons();
									idle();

									_delegate->controlChar = this;
								}

								if (strcmp(getRole()->getCString(), "Player") == 0)
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

			if (strcmp(attacker->_attackType->getCString(), "aAttack") == 0)
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
					const char *hitType = attacker->_effectType->getCString();

					//hit or not !
					attacker->_isHitOne = true;

					//record the slayer
					_slayer = attacker;

					//flog hurt
					if (strcmp(_role->getCString(), ROLE_FLOG) == 0)
					{
						if (strcmp(hitType, "o_hit") == 0)
						{
							setKnockLength(48);
							setKnockDirection(attacker->_isFlipped);
							hurt();
						}
						else if (strcmp(hitType, "ac_hit") == 0)
						{
							airHurt();
						}
						else if (strcmp(hitType, "f_hit") == 0 || strcmp(hitType, "bf_hit") == 0)
						{
							autoFlip(attacker);
							floatUP(64, true);
						}
						else if (strcmp(hitType, "f2_hit") == 0)
						{
							autoFlip(attacker);
							floatUP(128, true);
						}
						else if (strcmp(hitType, "b_hit") == 0)
						{
							autoFlip(attacker);
							floatUP(16, false);
						}
						else if (strcmp(hitType, "ab_hit") == 0)
						{
							absorb(attacker->getPosition(), true);
						}
						else if (strcmp(hitType, "s_hit") == 0)
						{
							absorb(attacker->getPosition(), false);
						}
					}
					// hero hurt
					else if (strcmp(_role->getCString(), "Player") == 0 || strcmp(_role->getCString(), "Com") == 0 || strcmp(_role->getCString(), ROLE_CLONE) == 0)
					{
						if (strcmp(hitType, "l_hit") == 0)
						{
							if (!_isArmored)
							{
								setKnockLength(32);
							}
							hurt();
						}
						else if (strcmp(hitType, "c_hit") == 0 ||
								 strcmp(hitType, "bc_hit") == 0)
						{
							if (!_isArmored)
							{
								setKnockLength(1);
							}

							if (strcmp(attacker->getCharacter()->getCString(), "Kakuzu") == 0 && _sticker)
							{
								CharacterBase *stHero = _sticker;
								if (strcmp(stHero->getCharacter()->getCString(), "Kakuzu") == 0 && stHero->hearts <= 4)
								{
									attacker->hearts += 1;

									if (attacker->_heartEffect)
									{
										CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Heart_Effect_%02d.png", attacker->hearts)->getCString());
										attacker->_heartEffect->setDisplayFrame(frame);
									}
								}

								if (strcmp(attacker->getRole()->getCString(), "Player") == 0 && attacker->hearts > 0)
								{
									CCObject *pObject;
									int countMON = 0;
									CCARRAY_FOREACH(attacker->getMonsterArray(), pObject)
									{
										Monster *mo = (Monster *)pObject;
										if (strcmp(mo->getCharacter()->getCString(), "Traps") != 0)
										{
											countMON++;
										}
									}
									if (countMON < 3 && attacker->getLV() >= 2)
									{
										if (_delegate->getHudLayer()->skill4Button)
										{
											_delegate->getHudLayer()->skill4Button->unLock();
										}
									}
								}
							}
							hurt();
						}
						else if (strcmp(hitType, "ts_hit") == 0)
						{
							if (!_isArmored)
							{
								setKnockLength(1);
							}
							if (hurt() &&
								(!attacker->_isCatchOne || strcmp(attacker->getCharacter()->getCString(), "FakeMinato") == 0))
							{
								attacker->_isCatchOne = true;
								if (attacker->getMaster())
								{
									if (strcmp(attacker->getCharacter()->getCString(), "FakeMinato") == 0)
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
						else if (strcmp(hitType, "sl_hit") == 0)
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
						else if (strcmp(hitType, "ac_hit") == 0)
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
						else if (strcmp(hitType, "o_hit") == 0)
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
						else if (strcmp(hitType, "o2_hit") == 0)
						{
							if (!_isArmored)
							{
								setKnockLength(1);
							}
							setKnockDirection(attacker->_isFlipped);
							hardHurt(1000, true, false, false, true);
						}
						else if (strcmp(hitType, "ob_hit") == 0)
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
						else if (strcmp(hitType, "ct_hit") == 0)
						{
							if (_actionState != State::OATTACK ||
								(_actionState == State::OATTACK &&
								 (attacker->_actionState == State::O2ATTACK ||
								  attacker->_actionState == State::OATTACK)))
							{
								if (attacker->_isCatchOne == false ||
									strcmp(attacker->getCharacter()->getCString(), "Shenwei") == 0)
								{
									if (attacker->getMaster())
									{
										if (strcmp(attacker->getCharacter()->getCString(), "Kuroari") == 0 ||
											strcmp(attacker->getCharacter()->getCString(), "Shenwei") == 0 ||
											strcmp(attacker->getCharacter()->getCString(), "Sabaku") == 0 ||
											strcmp(attacker->getCharacter()->getCString(), "Shenwei2") == 0)
										{
											if (hardHurt(3000, false, true, false, false))
											{
												attacker->_isCatchOne = true;
												scheduleOnce(schedule_selector(CharacterBase::reCatched), 2.9f);
											}
										}
										else if (strcmp(attacker->getCharacter()->getCString(), "SandBall") == 0)
										{
											if (hardHurt(1000, false, true, false, false))
											{
												attacker->_isCatchOne = true;
												scheduleOnce(schedule_selector(CharacterBase::reCatched), 0.9f);
											}
										}
										else if (strcmp(attacker->getMaster()->getCharacter()->getCString(), "Shikamaru") == 0)
										{
											bool pianyi = false;
											if (strcmp(attacker->getCharacter()->getCString(), "KageHand") == 0)
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
											else if (strcmp(attacker->getCharacter()->getCString(), "QuanRen") == 0 ||
													 strcmp(attacker->getCharacter()->getCString(), "KageBom") == 0)
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
										else if (strcmp(attacker->getMaster()->getCharacter()->getCString(), "Itachi") == 0 ||
												 strcmp(attacker->getMaster()->getCharacter()->getCString(), "Chiyo") == 0)
										{
											bool pianyi = false;

											if (strcmp(attacker->getMaster()->getCharacter()->getCString(), "Chiyo") == 0)
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
										if (strcmp(attacker->getCharacter()->getCString(), "Lee") == 0 ||
											strcmp(attacker->getCharacter()->getCString(), "RockLee") == 0)
										{
											if (hardHurt(1000, false, true, false, false))
											{
												attacker->_isCatchOne = true;
												scheduleOnce(schedule_selector(CharacterBase::reCatched), 1.1f);
											}
										}
										else if (strcmp(attacker->getCharacter()->getCString(), "Kakuzu") == 0)
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
										else if (strcmp(attacker->getCharacter()->getCString(), "Tobi") == 0)
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
						else if (strcmp(hitType, "f_hit") == 0 || strcmp(hitType, "bf_hit") == 0)
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
						else if (strcmp(hitType, "f2_hit") == 0)
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
						else if (strcmp(hitType, "b_hit") == 0)
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
						else if (strcmp(hitType, "ab_hit") == 0)
						{
							absorb(attacker->getPosition(), true);
						}
						else if (strcmp(hitType, "s_hit") == 0)
						{
							absorb(attacker->getPosition(), false);
						}
					}

					if (strcmp(getCharacter()->getCString(), "Hidan") == 0 && _skillChangeBuffValue)
					{
						bool _isCounter = false;
						if (_monsterArray && _monsterArray->count() > 0)
						{
							CCObject *pObject;
							CCARRAY_FOREACH(_monsterArray, pObject)
							{
								CharacterBase *tempMonster = (CharacterBase *)pObject;
								float distanceX = ccpSub(tempMonster->getPosition(), getPosition()).x;
								float distanceY = ccpSub(tempMonster->getPosition(), getPosition()).y;
								if (abs(distanceX) < 40 && abs(distanceY) < 15)
								{
									_isCounter = true;
								}
							}
						}

						if (_isCounter &&
							strcmp(attacker->_character->getCString(), Guardian_Roshi) != 0 &&
							strcmp(attacker->_character->getCString(), Guardian_Han) != 0)
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
								Hero *tempHero = (Hero *)pObject;
								if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0 && (strcmp(tempHero->_role->getCString(), "Player") == 0 || strcmp(tempHero->_role->getCString(), "Com") == 0) && tempHero->_actionState != State::DEAD)
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

					if (strcmp(getCharacter()->getCString(), "Kakuzu") == 0 && _skillChangeBuffValue)
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
	CCArray *seqArray = CCArray::create();
	CCAnimation *tempAnimation;
	CCAction *tempAction;
	CCAction *seq;

	CCARRAY_FOREACH(ationArray, tObject)
	{
		CCDictionary *dic = (CCDictionary *)tObject;
		CCDictElement *ele = nullptr;

		CCDICT_FOREACH(dic, ele)
		{
			const char *key = CCString::create(ele->getStrKey())->getCString();
			const char *keyValue = dic->valueForKey(key)->getCString();
			if (strcmp(key, "frameName") == 0)
			{
				CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(keyValue);
				animeFrames->addObject(frame);
			}
			else
			{
				tempAnimation = CCAnimation::createWithSpriteFrames(animeFrames, float(1.0 / fps));
				tempAction = CCAnimate::create(tempAnimation);

				seqArray->addObject(tempAction);
				if (strcmp(key, "setAttackBox") == 0)
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setAttackBox), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setSound") == 0)
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setSound), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setDSound") == 0)
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setDSound), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setDelay") == 0)
				{
					float delayTime = dic->valueForKey(key)->intValue();
					CCAction *delay = CCDelayTime::create(delayTime / 100);
					seqArray->addObject(delay);
				}
				else if (strcmp(key, "setMove") == 0)
				{
					int moveLength = dic->valueForKey(key)->intValue();
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setMove), (void *)moveLength);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setSkillEffect") == 0)
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setSkillEffect), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setJump") == 0)
				{
					bool jumpDirection = dic->valueForKey(key)->boolValue();
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setJump), (void *)jumpDirection);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setCharge") == 0)
				{
					CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::getCollider));
					seqArray->addObject(call);
					int moveLength = dic->valueForKey(key)->intValue();
					call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setCharge), (void *)moveLength);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setChargeB") == 0)
				{
					int moveLength = dic->valueForKey(key)->intValue();
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setChargeB), (void *)moveLength);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setClone") == 0)
				{
					int cloneTime = dic->valueForKey(key)->intValue();
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setClone), (void *)cloneTime);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setMon") == 0)
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setMon), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setFont") == 0)
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

					//CCFiniteTimeAction *call = CCCallFuncND::create(this,callfuncND_selector(CharacterBase::setFontEffect),(void*)callValue);
					//seqArray->addObject(call);
				}
				else if (strcmp(key, "setBuff") == 0)
				{
					int buffValue = dic->valueForKey(key)->intValue();
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setBuff), (void *)buffValue);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setCommand") == 0)
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setCommand), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setDetonation") == 0)
				{
					CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::dealloc));
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setBullet") == 0)
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setBullet), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setMonAttack") == 0)
				{
					int skillNum = dic->valueForKey(key)->intValue();
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setMonAttack), (void *)skillNum);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setTrap") == 0)
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(CCString::create(keyValue), 1);
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setTrap), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setActionResume") == 0)
				{
					CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::setActionResume));
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setActionResume2") == 0)
				{
					CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::setActionResume2));
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setShadow") == 0)
				{
					callValue = CCDictionary::create();
					callValue->retain();
					callValue->setObject(animeFrames->objectAtIndex(int(animeFrames->count() - 1)), 1);
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setShadow), (void *)callValue);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setTransform") == 0)
				{
					CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::setTransform));
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setOugis") == 0)
				{
					CCFiniteTimeAction *call = CCCallFuncN::create(this, callfuncN_selector(CharacterBase::setOugis));
					seqArray->addObject(call);
				}
				else if (strcmp(key, "stopJump") == 0)
				{
					int stopTime = dic->valueForKey(key)->intValue();
					CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::stopJump), (void *)stopTime);
					seqArray->addObject(call);
				}
				else if (strcmp(key, "setFlipped") == 0)
				{
					CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::setCharFlip));
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
			CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::idle));
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
	CCDictionary *file = (CCDictionary *)data;
	CCSpriteFrame *frame = (CCSpriteFrame *)(file->objectForKey(1));
	CCSprite *charN = CCSprite::createWithSpriteFrame(frame);
	charN->setVisible(false);
	if (strcmp(_group->getCString(), Konoha) == 0)
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
	CCDelayTime *delay = CCDelayTime::create(0.1f);
	CCFiniteTimeAction *call = CCCallFuncN::create(charN, callfuncN_selector(CharacterBase::enableShadow));
	charN->runAction(CCSequence::createWithTwoActions(delay, call));
	_delegate->addChild(charN, -getPositionY() - 1);
}

void CharacterBase::enableShadow(CCNode *sender)
{
	CCSprite *charN = (CCSprite *)sender;
	charN->setVisible(true);
	CCDelayTime *delay = CCDelayTime::create(0.1f);
	CCFiniteTimeAction *call = CCCallFuncN::create(charN, callfuncN_selector(CharacterBase::disableShadow));
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

void CharacterBase::setDamage(CCString *effectType, int attackValue, bool isFlipped)
{
	if (strcmp(_role->getCString(), "Tower") == 0)
	{
		if (_hpBar)
			_hpBar->setVisible(true);

		unschedule(schedule_selector(CharacterBase::disableHpBar));
		scheduleOnce(schedule_selector(CharacterBase::disableHpBar), 2.0f);
	}

	int criticalValue;
	int realValue;

	CharacterBase *attacker = _slayer;
	CharacterBase *currentAttacker;
	if (attacker->getMaster())
		currentAttacker = attacker->getMaster();
	else
		currentAttacker = attacker;

	if (attacker->isGearCD || (attacker->_master && attacker->_master->isGearCD))
		criticalValue = rand() % 60 + 10;
	else
		criticalValue = rand() % 50;

	if (strcmp(attacker->getCharacter()->getCString(), "Hidan") == 0 && attacker->_skillChangeBuffValue)
	{
		realValue = attackValue + criticalValue;
	}
	else
	{
		bool isCannotMiss = false; // is this attack has 100 percent accuracy
		if (strcmp(attacker->getCharacter()->getCString(), "Hiruzen") == 0 && attacker->getActionState() == State::O2ATTACK)
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

				if (strcmp(getCharacter()->getCString(), "Kakuzu") == 0 && _skillChangeBuffValue)
					decreaseRating += 0.25;

				if (strcmp(_character->getCString(), "Chiyo") == 0)
				{
					CCObject *pObject;
					CCARRAY_FOREACH(getMonsterArray(), pObject)
					{
						Monster *mo = (Monster *)pObject;
						if (strcmp(mo->getCharacter()->getCString(), "Parents") == 0 && !mo->_skillChangeBuffValue && mo->getActionState() != State::SATTACK)
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

	if (to_uint(_hp->getCString()) - realValue < 0)
		setHP(CCString::createWithFormat("%d", 0));
	else
		setHP(CCString::createWithFormat("%ld", to_uint(getHP()->getCString()) - realValue));

	if (strcmp(getRole()->getCString(), ROLE_CLONE) == 0)
	{
		int boundValue = 0;
		if (strcmp(getCharacter()->getCString(), "Naruto") == 0)
			boundValue = realValue * 15 / 100;
		else if (strcmp(getCharacter()->getCString(), "SageNaruto") == 0)
			boundValue = realValue * 25 / 100;
		else if (strcmp(getCharacter()->getCString(), "RikudoNaruto") == 0)
		{
			boundValue = realValue * 35 / 100;

			//4v4
			if (Cheats > 6)
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
					if (45000 - atof(_master->getCKR()->getCString()) >= boundValue)
					{
						float newValue = atof(_master->getCKR()->getCString()) + boundValue;
						_master->setCKR(CCString::createWithFormat("%f", newValue));
					}
					else
					{
						_master->setCKR(CCString::create("45000"));
					}

					if (atof(_master->getCKR()->getCString()) >= 15000)
						_master->_isCanOugis1 = true;

					if (strcmp(_master->getRole()->getCString(), "Player") == 0)
						_delegate->setCKRLose(false);
				}

				if (_master->getLV() >= 4 && !_master->_isControlled)
				{
					if (50000 - atof(_master->getCKR2()->getCString()) >= boundValue)
					{
						float newValue = atof(_master->getCKR2()->getCString()) + boundValue;
						_master->setCKR2(CCString::createWithFormat("%f", newValue));
					}
					else
					{
						_master->setCKR2(CCString::create("50000"));
					}

					if (atof(_master->getCKR2()->getCString()) >= 25000)
						_master->_isCanOugis2 = true;

					if (strcmp(_master->getRole()->getCString(), "Player") == 0)
						_delegate->setCKRLose(true);
				}
			}
		}
		else
		{
			int boundValue;

			if (_level == 5)
				boundValue = realValue + realValue * 5 / 100;
			else if (_level == 6)
				boundValue = realValue + realValue * 10 / 100;
			else
				boundValue = realValue;

			boundValue += realValue * gearCKRValue / 100;

			// 4v4
			if (Cheats > 6)
				boundValue = boundValue / 2;

			if (currentAttacker->isAttackGainCKR)
			{
				if (boundValue - boundValue * 25 / 100 > 0)
					boundValue = boundValue - boundValue * 25 / 100;
				else
					boundValue = 0;
			}

			bool isGainable = true;
			if (strcmp(getCharacter()->getCString(), "Tsunade") == 0 && _skillChangeBuffValue)
				isGainable = false;
			if (strcmp(attacker->getCharacter()->getCString(), "Hinata") == 0 && attacker->_skillUPBuffValue)
				isGainable = false;

			if (_level >= 2 && !_isControlled && isGainable)
			{
				if (45000 - atof(getCKR()->getCString()) >= boundValue)
				{
					float newValue = atof(getCKR()->getCString()) + boundValue;
					setCKR(CCString::createWithFormat("%f", newValue));
				}
				else
				{
					setCKR(CCString::create("45000"));
				}

				if (atof(getCKR()->getCString()) >= 15000)
					_isCanOugis1 = true;

				if (strcmp(_role->getCString(), "Player") == 0)
					_delegate->setCKRLose(false);
			}

			if (_level >= 4 && !_isControlled && isGainable)
			{
				if (50000 - atof(getCKR2()->getCString()) >= boundValue)
				{
					float newValue = atof(getCKR2()->getCString()) + boundValue;
					setCKR2(CCString::createWithFormat("%f", newValue));
				}
				else
				{
					setCKR2(CCString::create("50000"));
				}

				if (atof(getCKR2()->getCString()) >= 25000)
					_isCanOugis2 = true;

				if (strcmp(_role->getCString(), "Player") == 0)
					_delegate->setCKRLose(true);
			}
		}

		if (strcmp(_role->getCString(), "Player") == 0 || strcmp(_role->getCString(), "Com") == 0)
		{
			float gainValue = 0;

			if (strcmp(attacker->getCharacter()->getCString(), "Kisame") == 0 && attacker->_skillChangeBuffValue)
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
					if (45000 - atof(currentAttacker->getCKR()->getCString()) >= gainValue)
					{
						float newValue = atof(currentAttacker->getCKR()->getCString()) + gainValue;
						currentAttacker->setCKR(CCString::createWithFormat("%f", newValue));
					}
					else
					{
						currentAttacker->setCKR(CCString::create("45000"));
					}

					if (atof(currentAttacker->getCKR()->getCString()) >= 15000)
						currentAttacker->_isCanOugis1 = true;

					if (strcmp(currentAttacker->getRole()->getCString(), "Player") == 0)
						_delegate->setCKRLose(false);
				}

				if (currentAttacker->_level >= 4 && !currentAttacker->_isControlled)
				{
					if (50000 - atof(currentAttacker->getCKR2()->getCString()) >= gainValue)
					{
						float newValue = atof(currentAttacker->getCKR2()->getCString()) + gainValue;
						currentAttacker->setCKR2(CCString::createWithFormat("%f", newValue));
					}
					else
					{
						currentAttacker->setCKR2(CCString::create("50000"));
					}

					if (atof(currentAttacker->getCKR2()->getCString()) >= 25000)
						currentAttacker->_isCanOugis2 = true;

					if (strcmp(currentAttacker->getRole()->getCString(), "Player") == 0)
						_delegate->setCKRLose(true);
				}
			}
		}

		if (strcmp(_role->getCString(), "Player") == 0 || (strcmp(_role->getCString(), "Tower") != 0 &&
														   abs(ccpSub(getPosition(), _delegate->currentPlayer->getPosition()).x) < winSize.width / 2))
		{
			//create damage value display
			bool _isDisplay = false;

			if (strcmp(attacker->_role->getCString(), "Player") == 0 || strcmp(_role->getCString(), "Player") == 0)
			{
				_isDisplay = true;
			}
			if (attacker->getMaster())
			{
				if (strcmp(attacker->getMaster()->_role->getCString(), "Player") == 0)
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
			if (strcmp(_role->getCString(), ROLE_FLOG) == 0 && strcmp(attacker->_role->getCString(), ROLE_FLOG) != 0)
			{
				if (strcmp(effectType->getCString(), "a_hit") == 0)
				{
					setDamgeEffect(CCString::create("a_hit"));
				}
			}
			else if (strcmp(attacker->_role->getCString(), ROLE_FLOG) != 0)
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
	CCLabelBMFont *rewardLabel = CCLabelBMFont::create(label->getCString(), "Fonts/yellow.fnt");
	rewardLabel->setPosition(ccp(0, 0));
	rewardLabel->setScale(0.3f);
	coinDisplay->addChild(rewardLabel);

	coinDisplay->setPosition(ccp(getPositionX(), getPositionY() + getContentSize().height / 2));
	_delegate->addChild(coinDisplay, 5000);

	CCActionInterval *mv = CCMoveBy::create(0.5f, ccp(0, 12));
	CCActionInterval *fadeOut = CCFadeOut::create(0.8f);
	CCFiniteTimeAction *call = CCCallFuncND::create(coinDisplay, callfuncND_selector(CharacterBase::removeCoinDisplay), nullptr);
	CCActionInterval *sp = CCSpawn::create(fadeOut, mv, nullptr);
	CCArray *seqArray = CCArray::create();
	seqArray->addObject(sp);
	seqArray->addObject(call);
	CCAction *seq = CCSequence::create(seqArray);
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
		CCLabelBMFont *damageFont = CCLabelBMFont::create(CCString::createWithFormat("%d", value)->getCString(),
														  CCString::createWithFormat("Fonts/%s.fnt", type)->getCString());
		damageFont->setAnchorPoint(ccp(0.5, 0.5));

		if (strcmp(_role->getCString(), ROLE_FLOG) == 0)
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

		CCActionInterval *sd = CCScaleBy::create(0.2f, 0.5f);
		CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::removeDamageDisplay));

		CCActionInterval *mv = CCMoveBy::create(0.4f, ccp(0, 12));
		CCActionInterval *fadeOut = CCFadeOut::create(0.4f);
		CCActionInterval *sp = CCSpawn::create(fadeOut, mv, nullptr);

		CCArray *seqArray = CCArray::create();
		seqArray->addObject(sd);
		seqArray->addObject(sp);
		seqArray->addObject(call);

		CCAction *seq = CCSequence::create(seqArray);

		damageFont->runAction(seq);
	}
}

void CharacterBase::removeDamageDisplay()
{
	if (_damageArray && _damageArray->count() > 0)
	{
		CCObject *pObject = _damageArray->objectAtIndex(0);
		CCLabelBMFont *damageFont = (CCLabelBMFont *)pObject;
		damageFont->removeFromParent();
		_damageArray->removeObjectAtIndex(0);
		damageFont = nullptr;
	}
}

void CharacterBase::setDamgeEffect(CCString *type)
{
	CCString *str = type;
	if (strcmp(_role->getCString(), "Player") == 0 || abs(ccpSub(getPosition(), _delegate->currentPlayer->getPosition()).x) < winSize.width / 2)
	{
		if (damageEffectCount < 2)
		{
			if (strcmp(_role->getCString(), ROLE_FLOG) != 0)
			{
				Effect *ef = Effect::create(str->getCString(), this);
				_delegate->damageEffectBatch->addChild(ef, 5000);
			}
			else
			{
				Effect *ef = Effect::create(str->getCString(), this);
				_delegate->damageEffectBatch->addChild(ef);
			}

			damageEffectCount++;
		}
	}
}

void CharacterBase::setSkillEffect(CCNode *sender, void *data)
{
	CCDictionary *file = (CCDictionary *)data;
	CCString *str = (CCString *)(file->objectForKey(1));

	if (strcmp(_role->getCString(), "Player") == 0 ||
		abs(ccpSub(getPosition(), _delegate->currentPlayer->getPosition()).x) < winSize.width / 2)
	{
		Effect *ef = Effect::create(str->getCString(), this);
		if (strcmp(str->getCString(), "Bagua") == 0 ||
			strcmp(str->getCString(), "Kujiyose") == 0)
		{
			_delegate->addChild(ef, -500);
		}
		else if (strcmp(str->getCString(), "DarkFlame") == 0)
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

	if ((strcmp(getCharacter()->getCString(), "Kankuro") == 0 ||
		 strcmp(getCharacter()->getCString(), "Chiyo") == 0 ||
		 strcmp(getCharacter()->getCString(), "Kiba") == 0 ||
		 strcmp(getCharacter()->getCString(), "Kakuzu") == 0) &&
		getMonsterArray() && getMonsterArray()->count() > 0)
	{
		CCObject *pObject;
		CCARRAY_FOREACH(getMonsterArray(), pObject)
		{
			Monster *mo = (Monster *)pObject;
			if (strcmp(mo->getCharacter()->getCString(), "Traps") != 0)
			{
				mo->setItem(Item1);
			}
		}
	}
	_isCanItem1 = false;
	if (strcmp(getRole()->getCString(), "Player") == 0)
	{
		if (_isAI)
		{
			_delegate->getHudLayer()->offCoin(CCString::createWithFormat("%d", 50)->getCString());
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
		if (to_uint(_maxHP->getCString()) - to_uint(_hp->getCString()) <= hpRestore)
		{
			setHP(CCString::create(getMaxHP()->getCString()));
			if (_hpBar)
			{
				_hpBar->loseHP(getHpPercent());
			}
		}
		else
		{
			setHP(CCString::createWithFormat("%ld", to_uint(_hp->getCString()) + hpRestore));
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

	if (getGearArray()->count() <= 2 && to_int(getCoin()->getCString()) >= gearCost)
	{
		CCString *gearItem = CCString::createWithFormat("%d", gearType(type));
		getGearArray()->addObject(gearItem);

		if (strcmp(getRole()->getCString(), "Player") == 0)
			_delegate->getHudLayer()->offCoin(CCString::createWithFormat("%d", gearCost)->getCString());
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
			if (gettempAttackValue1())
			{
				settempAttackValue1(CCString::createWithFormat("%d", to_int(gettempAttackValue1()->getCString()) + 160));
			}
			setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) + 160));
			hasArmorBroken = true;
			break;
		case gear05:
			isGearCD = true;
			_sattackcoldDown1 -= 5;
			_sattackcoldDown2 -= 5;
			_sattackcoldDown3 -= 5;

			if (strcmp(getRole()->getCString(), "Player") == 0)
			{
				_delegate->getHudLayer()->skill1Button->setCD(CCString::createWithFormat("%d", _sattackcoldDown1 * 1000));
				_delegate->getHudLayer()->skill2Button->setCD(CCString::createWithFormat("%d", _sattackcoldDown2 * 1000));
				_delegate->getHudLayer()->skill3Button->setCD(CCString::createWithFormat("%d", _sattackcoldDown3 * 1000));

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
			_delegate->getHudLayer()->item1Button->setCD(CCString::createWithFormat("%d", 3000));
			_delegate->getHudLayer()->item1Button->_isColdChanged = true;
			break;
		case gear08:
			uint32_t tempMaxHP = to_uint(getMaxHP()->getCString());
			tempMaxHP += 6000;
			setMaxHP(CCString::createWithFormat("%d", tempMaxHP));
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
				if (strcmp(_role->getCString(), "Player") == 0 || strcmp(getGroup()->getCString(), _delegate->currentPlayer->getGroup()->getCString()) == 0)
					setOpacity(150);
				else
					setVisible(false);

				if (_hpBar)
					_hpBar->setVisible(false);

				if (_shadow)
					_shadow->setVisible(false);

				_isVisable = false;

				CCDictionary *callValue2 = CCDictionary::create();
				callValue2->setObject(CCString::create("Audio/Effect/suzou_effect.ogg"), 1);
				setSound(this, callValue2);

				schedule(schedule_selector(CharacterBase::disableGear1), 3.0f);
			}
		}
	}
	else if (type == gear03)
	{
		_isCanGear03 = false;

		CCDictionary *tmpValue = CCDictionary::create();
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

				CCDictionary *callValue = CCDictionary::create();
				callValue->setObject(CCString::create("tishen"), 1);
				setSkillEffect(this, callValue);
				scheduleOnce(schedule_selector(CharacterBase::disableGear2), 1.0f);

				CCDictionary *callValue2 = CCDictionary::create();
				callValue2->setObject(CCString::create("Audio/Effect/poof2.ogg"), 1);
				setSound(this, callValue2);

				if (strcmp(_role->getCString(), "Player") == 0 || strcmp(getGroup()->getCString(), _delegate->currentPlayer->getGroup()->getCString()) == 0)
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

		if (_hpBar)
			_hpBar->setVisible(true);

		if (_shadow)
			_shadow->setVisible(true);

		_isVisable = true;
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

	if (_hpBar)
		_hpBar->setVisible(true);

	if (_shadow)
		_shadow->setVisible(true);

	_isVisable = true;
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
	setCoin(CCString::createWithFormat("%d", to_int(getCoin()->getCString()) + num));
}

void CharacterBase::minusCoin(int num)
{
	if (to_int(getCoin()->getCString()) > num)
		setCoin(CCString::createWithFormat("%d", to_int(getCoin()->getCString()) - num));
	else
		setCoin(CCString::createWithFormat("%d", 0));
}

void CharacterBase::setRestore(float dt)
{
	if (_hpBar)
	{
		if (to_uint(_maxHP->getCString()) - to_uint(_hp->getCString()) <= 800)
		{
			setHP(CCString::create(getMaxHP()->getCString()));
			_hpBar->loseHP(getHpPercent());
		}
		else
		{
			setHP(CCString::createWithFormat("%ld", to_uint(_hp->getCString()) + 800));
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
		if (strcmp(Akatsuki, _group->getCString()) == 0 && getPositionX() <= _delegate->currentMap->getTileSize().width * 2)
		{
			isZone = true;
		}
		else if (strcmp(Konoha, _group->getCString()) == 0 && getPositionX() >= (_delegate->currentMap->getMapSize().width - 2) * _delegate->currentMap->getTileSize().width)
		{
			isZone = true;
		}
		if (isZone)
		{
			if (to_uint(_hp->getCString()) - 1000 > 0)
			{
				setHP(CCString::createWithFormat("%ld", to_uint(_hp->getCString()) - 1000));
				_hpBar->loseHP(getHpPercent());
			}
			else
			{
				setHP(CCString::createWithFormat("%d", 100));
				_hpBar->loseHP(getHpPercent());
			}
		}

		if (getActionState() == State::IDLE && getHpPercent() < 1)
		{
			if (to_uint(_maxHP->getCString()) - to_uint(_hp->getCString()) <= 300)
			{
				setHP(CCString::create(getMaxHP()->getCString()));
				_hpBar->loseHP(getHpPercent());
			}
			else
			{
				setHP(CCString::createWithFormat("%ld", to_uint(_hp->getCString()) + 300));
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
		if (strcmp(_role->getCString(), "Player") == 0 ||
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
			CCDictionary *file = (CCDictionary *)data;
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
		if (strcmp(_role->getCString(), "Player") == 0 ||
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
			CCDictionary *file = (CCDictionary *)data;
			CCString *str = (CCString *)(file->objectForKey(1));
			SimpleAudioEngine::sharedEngine()->preloadEffect(str->getCString());
			SimpleAudioEngine::sharedEngine()->playEffect(str->getCString());
		}
	}
}

void CharacterBase::setAttackBox(CCNode *sender, void *data)
{
	CCDictionary *file = (CCDictionary *)data;
	CCString *str = (CCString *)(file->objectForKey(1));

	_effectType = str;

	if (_actionState == State::HURT)
	{
		if (strcmp(getCharacter()->getCString(), "Sasuke") == 0 ||
			strcmp(getCharacter()->getCString(), "ImmortalSasuke") == 0 ||
			strcmp(getCharacter()->getCString(), "DevaPath") == 0)
		{
			if (to_uint(_maxHP->getCString()) - to_uint(_hp->getCString()) <= 260)
			{
				setHP(CCString::create(getMaxHP()->getCString()));
				_hpBar->loseHP(getHpPercent());
			}
			else
			{
				setHP(CCString::createWithFormat("%ld", to_uint(_hp->getCString()) + 260));
				_hpBar->loseHP(getHpPercent());
			}

			if (_role && strcmp(_role->getCString(), "Player") == 0)
			{
				_delegate->setHPLose(getHpPercent());
			}

			_attackType = _spcattackType1;
			_attackValue = to_int(_spcattackValue1->getCString());
			_attackRangeX = _spcattackRangeX1;
			_attackRangeY = _spcattackRangeY1;
		}
	}

	CCNotificationCenter::sharedNotificationCenter()->postNotification("acceptAttack", this);

	if (strcmp(_role->getCString(), "Player") == 0)
	{
		if ((_actionState == State::OATTACK || _actionState == State::O2ATTACK) && _isHitOne == true && !_delegate->_isShacking)
		{
			_delegate->_isShacking = true;
			CCScene *f = CCDirector::sharedDirector()->getRunningScene();
			CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::disableShack));
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
		Hero *tempHero = (Hero *)pObject;
		CharacterBase *tempSticker = nullptr;
		if (tempHero->_sticker)
		{
			tempSticker = (CharacterBase *)tempHero->_sticker;
		}
		if (tempSticker && strcmp(tempSticker->getCharacter()->getCString(), getCharacter()->getCString()) == 0 && tempHero->_isSticking)
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
	if (strcmp(getRole()->getCString(), "Tower") == 0)
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
	CCDictionary *file = (CCDictionary *)data;
	CCString *commandType = (CCString *)(file->objectForKey(1));

	if (strcmp(commandType->getCString(), "addHP") == 0)
	{
		if (_hpBar)
		{
			setHP(CCString::create(getMaxHP()->getCString()));
			_hpBar->loseHP(getHpPercent());
			_hpBar->setPositionY(getHeight());
		}
	}
	else if (strcmp(commandType->getCString(), "setInvincible") == 0)
	{
		_isInvincible = true;
	}
	else if (strcmp(commandType->getCString(), "setGainCKR") == 0)
	{
		int boundValue = 1500;
		if (_level >= 2)
		{
			if (45000 - atof(getCKR()->getCString()) >= boundValue)
			{
				float newValue = atof(getCKR()->getCString()) + boundValue;
				setCKR(CCString::createWithFormat("%f", newValue));
			}
			else
			{
				setCKR(CCString::create("45000"));
			}

			if (atof(getCKR()->getCString()) >= 15000)
				_isCanOugis1 = true;

			if (strcmp(_role->getCString(), "Player") == 0)
				_delegate->setCKRLose(false);
		}

		if (_level >= 4 && !_isControlled)
		{
			if (50000 - atof(getCKR2()->getCString()) >= boundValue)
			{
				float newValue = atof(getCKR2()->getCString()) + boundValue;
				setCKR2(CCString::createWithFormat("%f", newValue));
			}
			else
			{
				setCKR2(CCString::create("50000"));
			}

			if (atof(getCKR2()->getCString()) >= 25000)
				_isCanOugis2 = true;

			if (strcmp(_role->getCString(), "Player") == 0)
				_delegate->setCKRLose(true);
		}
	}
	else if (strcmp(commandType->getCString(), "reInvincible") == 0)
	{
		_isInvincible = false;
	}
	else if (strcmp(commandType->getCString(), "setInvisible") == 0)
	{
		setVisible(false);
		_isVisable = false;
	}
	else if (strcmp(commandType->getCString(), "reInvisible") == 0)
	{
		setVisible(true);
		_isVisable = true;
	}
	else if (strcmp(commandType->getCString(), "setTransport2") == 0)
	{
		CCObject *pObject;
		int tsPosX = getPositionX();
		int tsPosY = getPositionY();

		if (getMonsterArray() && _actionState != State::NATTACK)
		{
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				Monster *mo = (Monster *)pObject;
				if (strcmp(mo->getCharacter()->getCString(), "HiraishinMark") == 0)
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
	else if (strcmp(commandType->getCString(), "setTransport") == 0)
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

		if (strcmp(getCharacter()->getCString(), "Sakura") == 0)
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

		if (strcmp(getCharacter()->getCString(), "Yominuma") != 0)
		{
			_delegate->reorderChild(this, -tsPosY);
		}
	}
	else if (strcmp(commandType->getCString(), "reTransport") == 0)
	{
		setPosition(ccp(getPositionX(), _originY));
		_originY = 0;
	}
	else if (strcmp(commandType->getCString(), "setDead") == 0)
	{
		_isSuicide = true;
		dead();
	}
	else if (strcmp(commandType->getCString(), "findTarget") == 0)
	{
		if (!findEnemy("Hero", 0))
		{
			if (!findEnemy(ROLE_FLOG, 0) || strcmp(getCharacter()->getCString(), "RikudoNaruto") == 0 ||
				strcmp(getCharacter()->getCString(), "SageNaruto") == 0)
			{
				_mainTarget = nullptr;
			}
		}

		if (_mainTarget)
		{
			if (strcmp(getCharacter()->getCString(), "Dogs") == 0 ||
				strcmp(getCharacter()->getCString(), "Yominuma") == 0 ||
				strcmp(getCharacter()->getCString(), "SandBall") == 0 ||
				strcmp(getCharacter()->getCString(), "Sabaku") == 0 ||
				strcmp(getCharacter()->getCString(), "Yataikuzu") == 0 ||
				strcmp(getCharacter()->getCString(), "Lee") == 0 ||
				strcmp(getCharacter()->getCString(), "RockLee") == 0)
			{
				_markPoint = ccp(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY());
			}
			else if (strcmp(getCharacter()->getCString(), "Tsukuyomi") == 0)
			{
				_markPoint = ccp(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY() + 2);
			}
			else if (strcmp(getCharacter()->getCString(), "KageFeng") == 0)
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
	else if (strcmp(commandType->getCString(), "setRevive") == 0)
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			Hero *tempHero = (Hero *)pObject;
			if (strcmp(_group->getCString(), tempHero->_group->getCString()) == 0 && (strcmp(tempHero->_role->getCString(), "Player") == 0 || strcmp(tempHero->_role->getCString(), "Com") == 0) && tempHero->_actionState == State::DEAD && tempHero->rebornSprite)
			{
				tempHero->unschedule(schedule_selector(Hero::reborn));
				tempHero->reborn(0.1f);
			}
		}
	}
	else if (strcmp(commandType->getCString(), "setTrade") == 0)
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			Hero *tempHero = (Hero *)pObject;
			if ((strcmp(tempHero->_role->getCString(), "Player") == 0 ||
				 strcmp(tempHero->_role->getCString(), "Com") == 0) &&
				tempHero->_actionState == State::DEAD && tempHero->rebornSprite && tempHero->hearts > 0 && strcmp(tempHero->_character->getCString(), "Kakuzu") != 0)
			{
				CCPoint sp = ccpSub(tempHero->getPosition(), getPosition());
				if (abs(sp.x) <= 48 && abs(sp.y) <= 48)
				{
					tempHero->hearts -= 1;
					if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0)
					{
						uint32_t tempMaxHP = to_uint(getMaxHP()->getCString());
						tempMaxHP += 100;
						setnAttackValue(CCString::createWithFormat("%d", to_int(_nattackValue->getCString()) + 5));
						setMaxHP(CCString::createWithFormat("%d", tempMaxHP));

						if (_hpBar)
						{
							_hpBar->loseHP(getHpPercent());
						}
					}

					if (strcmp(getRole()->getCString(), "Player") == 0)
					{
						if (_delegate->_isHardCoreGame)
						{
							getDelegate()->setCoin(CCString::createWithFormat("%d", 50 + (tempHero->getLV() - 1) * 10)->getCString());
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
	else if (strcmp(commandType->getCString(), "addExtern") == 0)
	{
		CCArray *tempArray = CCArray::create();

		int i = 1;
		if (strcmp(getCharacter()->getCString(), "Tenten") == 0)
		{
			while (i < 11)
			{
				CCString *path = CCString::createWithFormat("Tenten_Extern_0%d.png", i);
				CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path->getCString());
				tempArray->addObject(frame);
				i += 1;
			}
		}

		CCAnimation *tempAnimation = CCAnimation::createWithSpriteFrames(tempArray, 0.1f);
		CCFiniteTimeAction *call = CCCallFuncN::create(this, callfuncN_selector(CharacterBase::disableShadow));
		CCAction *tempAction = CCAnimate::create(tempAnimation);
		CCArray *list = CCArray::create();
		list->addObject(tempAction);
		list->addObject(call);
		CCAction *seq = CCSequence::create(list);

		CCSprite *tempChar = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s_Extern_01.png", getCharacter()->getCString())->getCString());

		tempChar->setAnchorPoint(ccp(0.5f, 0));
		tempChar->setPosition(getPosition());
		_delegate->addChild(tempChar, -_originY);

		tempChar->runAction(seq);
	}
	else if (strcmp(commandType->getCString(), "pauseJump") == 0)
	{
		getActionManager()->addAction(_jumpUPAction, this, false);
	}
	else if (strcmp(commandType->getCString(), "setCounter") == 0)
	{
		bool _isCounter = false;
		if (_monsterArray && _monsterArray->count() > 0)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(_monsterArray, pObject)
			{
				CharacterBase *tempMonster = (CharacterBase *)pObject;
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
				Hero *tempHero = (Hero *)pObject;
				if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0 && (strcmp(tempHero->_role->getCString(), "Player") == 0 || strcmp(tempHero->_role->getCString(), "Com") == 0) && tempHero->_actionState != State::DEAD)
				{
					if (tempHero->_hpBar)
					{
						tempHero->_slayer = this;
						if (to_int(tempHero->_hp->getCString()) <= 2000)
						{
							tempHero->setDamage(CCString::create("c_hit"), to_int(tempHero->_hp->getCString()), false);
						}
						else
						{
							tempHero->setDamage(CCString::create("c_hit"), 2000, false);
						}

						tempHero->_hpBar->loseHP(tempHero->getHpPercent());

						if (strcmp(tempHero->_role->getCString(), "Player") == 0)
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
				if (to_uint(_hp->getCString()) <= 2000)
				{
					setDamage(CCString::create("c_hit"), to_uint(_hp->getCString()), false);
				}
				else
				{
					setDamage(CCString::create("c_hit"), 2000, false);
				}
				_hpBar->loseHP(getHpPercent());

				if (strcmp(_role->getCString(), "Player") == 0)
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

	if (strcmp(_attackType->getCString(), "hBuff") == 0)
	{
		_healBuffValue = buffValue;
		schedule(schedule_selector(CharacterBase::healBuff), 1);
		setBuffEffect("hBuff");
	}
	else if (strcmp(_attackType->getCString(), "sBuff") == 0 ||
			 strcmp(_attackType->getCString(), "rsBuff") == 0 ||
			 strcmp(_attackType->getCString(), "hsBuff") == 0 ||
			 strcmp(_attackType->getCString(), "dcBuff") == 0)
	{
		_skillUPBuffValue = buffValue;
		scheduleOnce(schedule_selector(CharacterBase::disableBuff), buffStayTime);
		setBuffEffect(_attackType->getCString());

		setsAttackValue1(CCString::createWithFormat("%d", to_int(_sattackValue1->getCString()) + _skillUPBuffValue));
		setsAttackValue2(CCString::createWithFormat("%d", to_int(_sattackValue2->getCString()) + _skillUPBuffValue));
		setsAttackValue3(CCString::createWithFormat("%d", to_int(_sattackValue3->getCString()) + _skillUPBuffValue));

		if (strcmp(_attackType->getCString(), "hsBuff") == 0)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
			{
				CharacterBase *tempHero = (CharacterBase *)pObject;
				if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0 && (strcmp(tempHero->_role->getCString(), "Player") == 0 || strcmp(tempHero->_role->getCString(), "Com") == 0) && tempHero->_actionState != State::HURT && tempHero->_actionState != State::DEAD)
				{
					float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
					if (distanceX < winSize.width / 2)
					{
						if (!tempHero->_isVisable)
						{
							if (strcmp(tempHero->getCharacter()->getCString(), "Konan") == 0 ||
								strcmp(tempHero->getCharacter()->getCString(), "Deidara") == 0)
							{
								tempHero->unschedule(schedule_selector(CharacterBase::disableBuff));
							}

							tempHero->setOpacity(255);
							tempHero->setVisible(true);

							if (tempHero->_hpBar)
							{
								tempHero->_hpBar->setVisible(true);
							}
							if (tempHero->_shadow)
							{
								tempHero->_shadow->setVisible(true);
							}

							tempHero->_isVisable = true;
						}
					}
				}
			}
			if (strcmp(getCharacter()->getCString(), "Neji") == 0)
			{
				_isArmored = true;
			}
		}
	}
	else if (strcmp(_attackType->getCString(), "cBuff") == 0)
	{
		_skillChangeBuffValue = buffValue;

		if (strcmp(_character->getCString(), "Shino") == 0 ||
			strcmp(_character->getCString(), "Sai") == 0 ||
			strcmp(_character->getCString(), "Deidara") == 0)
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
		else if (strcmp(_character->getCString(), "Kiba") == 0)
		{
			if (_skillChangeBuffValue == 18)
			{
				scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
			}
		}
		else if ((strcmp(_character->getCString(), "ImmortalSasuke") == 0 ||
				  strcmp(_character->getCString(), "Sasuke") == 0) &&
				 _skillChangeBuffValue == 18)
		{
			unschedule(schedule_selector(CharacterBase::resumeAction));
			unschedule(schedule_selector(CharacterBase::disableBuff));

			_isTaunt = false;
			setHurtAction(createAnimation(hurtArray, 10.0f, false, true));
			disableBuff(0);

			scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
		}
		else if (strcmp(_character->getCString(), "Minato") == 0)
		{
			if (_skillChangeBuffValue == 18)
			{
				scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
			}
		}
		else
		{
			if (strcmp(_character->getCString(), "Kankuro") != 0 &&
				strcmp(_character->getCString(), "Chiyo") != 0 &&
				strcmp(_character->getCString(), Guardian_Roshi) != 0 &&
				strcmp(_character->getCString(), Guardian_Han) != 0 &&
				strcmp(_character->getCString(), "Hiruzen") != 0 &&
				strcmp(_character->getCString(), "Suigetsu") != 0 &&
				strcmp(_character->getCString(), "Jugo") != 0 &&
				strcmp(_character->getCString(), "Kisame") != 0 &&
				strcmp(_character->getCString(), "Parents") != 0 &&
				strcmp(_character->getCString(), "Lee") != 0 &&
				strcmp(_character->getCString(), "RockLee") != 0)
			{
				scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
			}
		}

		changeAction();
	}
	else if (strcmp(_attackType->getCString(), "tBuff") == 0)
	{
		_skillChangeBuffValue = buffValue;
		scheduleOnce(schedule_selector(CharacterBase::resumeAction), buffStayTime);
		scheduleOnce(schedule_selector(CharacterBase::disableBuff), buffStayTime);
		setBuffEffect(_attackType->getCString());

		changeAction();
	}
	else if (strcmp(_attackType->getCString(), "stBuff") == 0)
	{
		if (strcmp(_role->getCString(), "Player") == 0 || strcmp(getGroup()->getCString(), _delegate->currentPlayer->getGroup()->getCString()) == 0)
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
	else if (strcmp(_attackType->getCString(), "GroupHeal") == 0 ||
			 strcmp(_attackType->getCString(), "GroupBuff") == 0)
	{
		if (_healBuffValue)
			_healBuffValue += buffValue;
		else
			_healBuffValue = buffValue;

		schedule(schedule_selector(CharacterBase::healBuff), 1);
	}

	if (strcmp(getRole()->getCString(), "Player") == 0)
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

	if (strcmp(type, "hBuff") == 0)
	{
		_healBuffEffect = Effect::create(type, this);
		addChild(_healBuffEffect);
	}
	else if (strcmp(type, "hsBuff") == 0)
	{
		_skillBuffEffect = Effect::create(type, this);
		_skillBuffEffect->setPositionY(14);
		addChild(_skillBuffEffect);
	}
	else if (strcmp(type, "tBuff") == 0 ||
			 strcmp(type, "dcBuff") == 0 ||
			 strcmp(type, "jdBuff") == 0 ||
			 strcmp(type, "bmBuff") == 0)
	{
		_skillBuffEffect = Effect::create(type, this);
		addChild(_skillBuffEffect);
	}
	else if (strcmp(type, "dhBuff") == 0)
	{
		_dehealBuffEffect = Effect::create(type, this);
		addChild(_dehealBuffEffect);
	}
	else if (strcmp(type, "sBuff") == 0)
	{
		_skillBuffEffect = Effect::create(type, this);
		addChild(_skillBuffEffect);
	}
}

void CharacterBase::removeBuffEffect(const char *type)
{
	if (strcmp(type, "hBuff") == 0 && _healBuffEffect)
	{
		_healBuffEffect->removeFromParent();
		_healBuffEffect = nullptr;
	}
	else if (strcmp(type, "sBuff") == 0 && _skillBuffEffect)
	{
		_skillBuffEffect->removeFromParent();
		_skillBuffEffect = nullptr;
	}
	else if (strcmp(type, "dhBuff") == 0 && _dehealBuffEffect)
	{
		_dehealBuffEffect->removeFromParent();
		_dehealBuffEffect = nullptr;
	}

	else if (strcmp(type, "all") == 0)
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
		setsAttackValue1(CCString::createWithFormat("%d", to_int(_sattackValue1->getCString()) - _skillUPBuffValue));
		setsAttackValue2(CCString::createWithFormat("%d", to_int(_sattackValue2->getCString()) - _skillUPBuffValue));
		setsAttackValue3(CCString::createWithFormat("%d", to_int(_sattackValue3->getCString()) - _skillUPBuffValue));
		_skillUPBuffValue = 0;

		if (strcmp(getCharacter()->getCString(), "Neji") == 0)
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

		if (_hpBar)
			_hpBar->setVisible(true);

		if (_shadow)
			_shadow->setVisible(true);

		_isVisable = true;
	}
	else if (_skillChangeBuffValue && strcmp(getCharacter()->getCString(), "Tobi") == 0)
	{
		setOpacity(255);
	}
}

void CharacterBase::disableDebuff(float dt)
{
	if ((strcmp(getCharacter()->getCString(), "ImmortalSasuke") == 0 ||
		 strcmp(getCharacter()->getCString(), "Itachi") == 0) &&
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
	if (strcmp(_character->getCString(), "Tsunade") == 0)
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
	if (strcmp(_character->getCString(), "Karin") == 0)
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			Hero *tempHero = (Hero *)pObject;
			if (strcmp(_group->getCString(), tempHero->_group->getCString()) == 0 && (strcmp(tempHero->_role->getCString(), "Player") == 0 || strcmp(tempHero->_role->getCString(), "Com") == 0) && tempHero->_actionState != State::DEAD)
			{
				float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
				float tempRange1 = 128 + getContentSize().width / 2;
				if (abs(distanceX) <= tempRange1 &&
					abs(tempHero->getPositionY() - getPositionY()) <= 128)
				{
					if (to_uint(tempHero->getMaxHP()->getCString()) - to_uint(tempHero->getHP()->getCString()) <= _healBuffValue)
					{
						tempHero->setHP(CCString::create(tempHero->getMaxHP()->getCString()));
						if (tempHero->_hpBar)
							tempHero->_hpBar->loseHP(tempHero->getHpPercent());
					}
					else
					{
						tempHero->setHP(CCString::createWithFormat("%ld", to_uint(tempHero->getHP()->getCString()) + int(_healBuffValue)));
						if (tempHero->_hpBar)
							tempHero->_hpBar->loseHP(tempHero->getHpPercent());
					}

					if (strcmp(tempHero->getRole()->getCString(), "Player") == 0)
						_delegate->setHPLose(tempHero->getHpPercent());

					if (tempHero->_isVisable)
					{
						Effect *tmpEffect = Effect::create("Kagura", tempHero);
						if (strcmp(tempHero->getRole()->getCString(), "Player") == 0)
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
	else if (strcmp(_character->getCString(), "Chiyo") == 0)
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			Hero *tempHero = (Hero *)pObject;
			if (strcmp(_group->getCString(), tempHero->_group->getCString()) == 0 && (strcmp(tempHero->_role->getCString(), "Player") == 0 || strcmp(tempHero->_role->getCString(), "Com") == 0) && strcmp(tempHero->_character->getCString(), "Chiyo") != 0)
			{
				CCPoint sp = ccpSub(tempHero->getPosition(), getPosition());
				if (abs(sp.x) <= winSize.width / 2)
				{
					if (tempHero->_level >= 2)
					{
						if (45000 - atof(tempHero->getCKR()->getCString()) >= _healBuffValue)
						{
							float newValue = atof(tempHero->getCKR()->getCString()) + _healBuffValue;
							tempHero->setCKR(CCString::createWithFormat("%f", newValue));
						}
						else
						{
							tempHero->setCKR(CCString::create("45000"));
						}

						if (atof(tempHero->getCKR()->getCString()) >= 15000)
							tempHero->_isCanOugis1 = true;

						if (strcmp(tempHero->_role->getCString(), "Player") == 0)
							_delegate->setCKRLose(false);
					}

					if (tempHero->_level >= 4)
					{
						if (50000 - atof(tempHero->getCKR2()->getCString()) >= _healBuffValue)
						{
							float newValue = atof(tempHero->getCKR2()->getCString()) + _healBuffValue;
							tempHero->setCKR2(CCString::createWithFormat("%f", newValue));
						}
						else
						{
							tempHero->setCKR2(CCString::create("50000"));
						}

						if (atof(tempHero->getCKR2()->getCString()) >= 25000)
							tempHero->_isCanOugis2 = true;

						if (strcmp(tempHero->_role->getCString(), "Player") == 0)
							tempHero->_delegate->setCKRLose(true);
					}

					if (tempHero->_isVisable)
					{
						Effect *tmpEffect = Effect::create("Hupo", tempHero);
						if (strcmp(tempHero->getRole()->getCString(), "Player") == 0)
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
	else if (strcmp(_character->getCString(), "Slug") == 0)
	{
		CCObject *pObject;
		CCArray *list;

		if (strcmp(Akatsuki, _group->getCString()) == 0)
			list = _delegate->_AkatsukiFlogArray;
		else
			list = _delegate->_KonohaFlogArray;

		CCARRAY_FOREACH(list, pObject)
		{
			CharacterBase *tempHero = (CharacterBase *)pObject;
			if (strcmp(_group->getCString(), tempHero->_group->getCString()) == 0 && tempHero->_actionState != State::DEAD)
			{
				float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
				float tempRange1 = 128 + getContentSize().width / 2;
				if (abs(distanceX) <= tempRange1 &&
					abs(tempHero->getPositionY() - getPositionY()) <= 128)
				{
					if (to_uint(tempHero->getMaxHP()->getCString()) - to_uint(tempHero->getHP()->getCString()) <= _healBuffValue)
					{
						tempHero->setHP(CCString::create(tempHero->getMaxHP()->getCString()));
						if (tempHero->_hpBar)
							tempHero->_hpBar->loseHP(tempHero->getHpPercent());
					}
					else
					{
						tempHero->setHP(CCString::createWithFormat("%ld", to_uint(tempHero->getHP()->getCString()) + int(_healBuffValue)));
						if (tempHero->_hpBar)
							tempHero->_hpBar->loseHP(tempHero->getHpPercent());
					}
				}
			}
		}
	}
	else if (strcmp(_character->getCString(), "Sakura") == 0 ||
			 strcmp(_character->getCString(), "Tsunade") == 0)
	{
		if (to_uint(_maxHP->getCString()) - to_uint(_hp->getCString()) <= _healBuffValue)
		{
			setHP(CCString::create(_maxHP->getCString()));
			if (_hpBar)
				_hpBar->loseHP(getHpPercent());
		}
		else
		{
			setHP(CCString::createWithFormat("%ld", to_uint(_hp->getCString()) + int(_healBuffValue)));
			if (_hpBar)
				_hpBar->loseHP(getHpPercent());
		}
		if (_role && strcmp(_role->getCString(), "Player") == 0)
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
		Hero *tempHero = (Hero *)pObject;
		if (strcmp(tempHero->getCharacter()->getCString(), "Asuma") == 0)
			_slayer = tempHero;
	}

	if (to_uint(_hp->getCString()) <= _dehealBuffValue)
		setDamage(CCString::create("c_hit"), _dehealBuffValue, false);
	else
		setDamage(CCString::create("c_hit"), _dehealBuffValue, false);

	if (_hpBar)
		_hpBar->loseHP(getHpPercent());

	if (strcmp(_role->getCString(), "Player") == 0)
		_delegate->setHPLose(getHpPercent());
}

// NOTE: Only for Shikamaru's KageHand
void CharacterBase::lostBlood(float dt)
{
	CCObject *pObject;
	CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
	{
		Hero *tempHero = (Hero *)pObject;
		if (strcmp(tempHero->getCharacter()->getCString(), "Shikamaru") == 0)
			_slayer = tempHero;
	}

	if (to_uint(_hp->getCString()) <= lostBloodValue)
		setDamage(CCString::create("c_hit"), lostBloodValue, false);
	else
		setDamage(CCString::create("c_hit"), lostBloodValue, false);

	if (_hpBar)
		_hpBar->loseHP(getHpPercent());

	if (strcmp(_role->getCString(), "Player") == 0)
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
	if (strcmp(_character->getCString(), "Minato") == 0)
	{
		_attackValue = to_int(_spcattackValue2->getCString());
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
	if (strcmp(_character->getCString(), "Minato") == 0)
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
		Hero *tempHero = (Hero *)pObject;
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
	CCDictionary *file = (CCDictionary *)data;
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

	if (strcmp(bulletType->getCString(), "PaperSrk") == 0)
	{
		bullet->setScale(0.8f);
		bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32),
								getPositionY() + 52));
		bullet->attack(NAttack);
		bullet->setMove(192, 2.0f, false);
	}
	else if (strcmp(bulletType->getCString(), "PaperSpear") == 0)
	{
		bullet->setScale(0.8f);
		bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -68 : 68),
								getPositionY() + 42));
		bullet->attack(NAttack);
		bullet->setMove(192, 2.0f, false);
	}
	else if (strcmp(bulletType->getCString(), "HugeSRK") == 0)
	{
		float rangeX = 76;

		bullet->setScale(0.8f);
		bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -rangeX : rangeX),
								getPositionY() + getHeight() / 2));
		if (_skillUPBuffValue)
		{
			bullet->setnAttackValue(CCString::createWithFormat("%d", to_int(bullet->_nattackValue->getCString()) + _skillUPBuffValue));
		}

		bullet->scheduleOnce(schedule_selector(Bullet::setAttack), 0.5f);
		scheduleOnce(schedule_selector(CharacterBase::setBulletGroup), 0.2f);
		bullet->setEaseIn(224, 5.0f);
	}
	else if (strcmp(bulletType->getCString(), "FlyKnife") == 0 ||
			 strcmp(bulletType->getCString(), "TentenSRK") == 0)
	{
		bullet->setScale(0.8f);
		bullet->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32),
								getPositionY() + getHeight() / 2));

		bullet->setEaseIn(224, 2.0f);
		bullet->attack(NAttack);
	}
	else if (strcmp(bulletType->getCString(), "HiraishinKunai") == 0 ||
			 strcmp(bulletType->getCString(), "Shintenshin") == 0)
	{
		if (!_monsterArray)
		{
			_monsterArray = CCArray::create();
			_monsterArray->retain();
		}
		if (strcmp(bulletType->getCString(), "HiraishinKunai") == 0)
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
			bullet->setnAttackValue(CCString::createWithFormat("%d", to_int(bullet->_nattackValue->getCString()) + _skillUPBuffValue));
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

	clone->setDelegate(_delegate);
	clone->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32), getPositionY() - 1));

	if (strcmp(getCharacter()->getCString(), "SageNaruto") == 0 ||
		strcmp(getCharacter()->getCString(), "Naruto") == 0 ||
		(strcmp(getCharacter()->getCString(), "RikudoNaruto") == 0 && cloneTime == 10))
	{
		clone->setHP(CCString::create(getHP()->getCString()));
	}
	else
	{
		clone->setHP(CCString::create(getMaxHP()->getCString()));
	}

	clone->setMaxHP(CCString::create(getMaxHP()->getCString()));
	clone->_exp = _exp;
	clone->setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString())));
	clone->_gardValue = _gardValue;
	clone->_level = _level;
	clone->setHPbar();
	clone->_hpBar->getHPBAR()->setScaleX(clone->getHpPercent());

	if (strcmp(getCharacter()->getCString(), "RikudoNaruto") == 0 && cloneTime == 9)
	{
		if (clone->_hpBar)
		{
			clone->_hpBar->setPositionY(120);
		}
		clone->setnAttackValue(CCString::createWithFormat("1060"));
	}
	else if (strcmp(getCharacter()->getCString(), "Kakashi") == 0)
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
	CCDictionary *callValue = CCDictionary::create();
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
	CCDictionary *file = (CCDictionary *)data;
	CCString *monsterType = (CCString *)(file->objectForKey(1));
	const char *monsterName = monsterType->getCString();
	float monsterStayTime = _attackRangeY;

	if (!_monsterArray)
	{
		_monsterArray = CCArray::create();
		_monsterArray->retain();
	}

	Monster *monster = Monster::create();
	monster->setDelegate(_delegate);

	monster->setID(monsterType, CCString::create(ROLE_MON), _group);

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
			monster->setSecMaster((CharacterBase *)this);
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

	if (strcmp(monsterName, "FakeDeidara") == 0 ||
		strcmp(monsterName, "FakeKisame") == 0 ||
		strcmp(monsterName, "DeidaraBom") == 0 ||
		strcmp(monsterName, "ChuiDi") == 0 ||
		strcmp(monsterName, "SakuraBom") == 0 ||
		strcmp(monsterName, "Shoryu") == 0 ||
		strcmp(monsterName, "Stream") == 0 ||
		strcmp(monsterName, "FakeMinato") == 0)
	{
		monster->setPosition(ccp(getPositionX(), _originY ? _originY : getPositionY()));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "LeeBom") == 0)
	{
		//monster->setAnchorPoint(ccp(0.5,0.5f));
		monster->setPosition(ccp(getPositionX(), getPositionY()));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "FakeItachi") == 0)
	{
		monster->setPosition(ccp(getPositionX(), _originY ? _originY : getPositionY() - 4));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "Tenmu") == 0)
	{
		monster->setPosition(ccp(getPositionX(), _originY));
		monster->setAnchorPoint(ccp(0.5, -0.1f));
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "Kaiten") == 0)
	{
		monster->setPosition(ccp(getPositionX(), getPositionY()));
		monster->setAnchorPoint(ccp(0.5, 0.25f));
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "Crash") == 0 ||
			 strcmp(monsterName, "Crash2") == 0)
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -32 : 32), _originY ? _originY : getPositionY()));
		monster->setAnchorPoint(ccp(0.5, 0.25f));
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "SansyoRed") == 0)
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 240 : getPositionX() + 240, getPositionY() - 32));
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "SansyoGreen") == 0)
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 144 : getPositionX() + 144, getPositionY() - 32 + 1));
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "SansyoBlue") == 0)
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 48 : getPositionX() + 48, getPositionY() - 32 + 2));
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "SmallSlug") == 0)
	{
		if (_monsterArray && _monsterArray->count() < 3)
		{
			CCDictionary *callValue = CCDictionary::create();
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
	else if (strcmp(monsterName, "Kuroari") == 0)
	{
		CCDictionary *callValue = CCDictionary::create();
		callValue->setObject(CCString::create("smk"), 1);
		monster->setSkillEffect(monster, callValue);
		_monsterArray->addObject(monster);
		monster->doAI();
	}
	else if (strcmp(monsterName, "PaperRain") == 0 ||
			 strcmp(monsterName, "Steam") == 0)
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 16 : getPositionX() + 16, _originY));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "FireRain") == 0)
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 75 : getPositionX() + 75, _originY - 1));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "Tuji") == 0 ||
			 strcmp(monsterName, "Tuji2") == 0 ||
			 strcmp(monsterName, "Suiji") == 0)
	{
		monster->setPositionY(getPositionY() - 24);
		monster->setPositionX(getPositionX() + (_isFlipped ? -64 : 64));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "ThunderWave") == 0)
	{
		monster->setPosition(ccp(getPositionX(), getPositionY() - 1));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "Jibaku") == 0 ||
			 strcmp(monsterName, "JibakuEX") == 0 ||
			 strcmp(monsterName, "Shenwei") == 0)
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -96 : 96), getPositionY()));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "Bikyu") == 0)
	{
		monster->setFlipX(_isFlipped);
		monster->hasArmorBroken = true;
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -(16 + getContentSize().width) : (16 + getContentSize().width)), getPositionY() - 32));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "Qilin") == 0)
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped ? -4 : 4), getPositionY() - 6));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "SuiRyuDan") == 0 ||
			 strcmp(monsterName, "TodonPillar") == 0 ||
			 strcmp(monsterName, "Yataikuzu") == 0 ||
			 strcmp(monsterName, "Yominuma") == 0 ||
			 strcmp(monsterName, "Dogs") == 0 ||
			 strcmp(monsterName, "SandHand") == 0 ||
			 strcmp(monsterName, "KageFeng") == 0 ||
			 strcmp(monsterName, "Sanbao") == 0 ||
			 strcmp(monsterName, "SandBall") == 0 ||
			 strcmp(monsterName, "Sabaku") == 0 ||
			 strcmp(monsterName, "SandWave") == 0 ||
			 strcmp(monsterName, "Tsukuyomi") == 0 ||
			 strcmp(monsterName, "Shark") == 0)
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped == true ? -48 : 48), getPositionY() - 4));
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "Suijin") == 0 ||
			 strcmp(monsterName, "BugPillar") == 0)
	{
		monster->setPosition(ccp(getPositionX() + (_isFlipped == true ? -64 : 64), getPositionY() + 1));
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "Mine") == 0)
	{
		CCDictionary *callValue = CCDictionary::create();
		callValue->setObject(CCString::create("smk"), 1);
		monster->setSkillEffect(monster, callValue);
		_monsterArray->addObject(monster);
		monster->doAI();
		if (strcmp(getGroup()->getCString(), _delegate->currentPlayer->getGroup()->getCString()) != 0)
		{
			monster->setVisible(false);
		}
	}
	else if (strcmp(monsterName, "Kage") == 0)
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
	else if (strcmp(monsterName, "KageHand") == 0)
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
	else if (strcmp(monsterName, "KageHands") == 0)
	{
		if (getMaster())
		{
			_master->_monsterArray->addObject(monster);
		}

		monster->setPosition(ccp(getPositionX(), getPositionY()));
		monster->setAnchorPoint(ccp(0.5f, 0.15f));
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "QuanRen") == 0)
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 64 : getPositionX() + 64, _originY));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else if (strcmp(monsterName, "ItachiSusano") == 0 ||
			 strcmp(monsterName, "SasukeSusano") == 0)
	{
		_monsterArray->addObject(monster);
	}
	else if (strcmp(monsterName, "HiraishinMark") == 0)
	{
		_monsterArray->addObject(monster);
		_isCanSkill1 = true;
	}
	else if (strcmp(monsterName, "CircleMark") == 0)
	{
		monster->setPosition(ccp(getPositionX(), getPositionY()));
		monster->setAnchorPoint(ccp(0.5f, 0.5f));
		_monsterArray->addObject(monster);
		monster->attack(NAttack);

		if (strcmp(getRole()->getCString(), "Player") == 0)
		{
			_delegate->getHudLayer()->skill1Button->setLock();
		}
	}
	else if (strcmp(monsterName, "InkDragon") == 0)
	{
		monster->setPosition(ccp(_isFlipped ? getPositionX() - 128 : getPositionX() + 128, getPositionY()));
		monster->attack(NAttack);
		monster->setDirectMove(156, 2.0f, false);
	}
	else if (strcmp(monsterName, "BugTomado") == 0)
	{
		monster->attack(NAttack);
		monster->setDirectMove(128, 2.0f, false);
	}
	else if (strcmp(monsterName, "FudonSRK2") == 0 ||
			 strcmp(monsterName, "FudonSRK") == 0)
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
	else if (strcmp(monsterName, "Kubi") == 0)
	{
		monster->attack(NAttack);
		monster->setDirectMove(128, 0.8f, true);
	}
	else if (strcmp(monsterName, "Shark2") == 0)
	{
		monster->attack(NAttack);
		monster->setEaseIn(224, 3.0f);
	}
	else if (strcmp(monsterName, "WaterBullet") == 0 ||
			 strcmp(monsterName, "BoneBullet") == 0 ||
			 strcmp(monsterName, "WaterBom") == 0)
	{
		monster->attack(NAttack);
		monster->setEaseIn(224, 1.0f);
	}
	else if (strcmp(monsterName, "Hasan") == 0)
	{
		monster->attack(NAttack);
		monster->setAnchorPoint(ccp(0.5f, 0.28f));
		monster->setPosition(ccp(getPositionX() + (_isFlipped == true ? -24 : 24), getPositionY()));
		monster->setEaseIn(224, 1.0f);
	}
	else if (strcmp(monsterName, "Wave") == 0)
	{
		monster->attack(NAttack);
		monster->setAnchorPoint(ccp(0.5f, 0.1f));
		monster->setPosition(ccp(getPositionX() + (_isFlipped == true ? -24 : 24), getPositionY()));
		monster->setEaseIn(224, 1.0f);
	}
	else if (strcmp(monsterName, "InkBird") == 0 ||
			 strcmp(monsterName, "FakeTobirama") == 0 ||
			 strcmp(monsterName, "TamaBomb") == 0 ||
			 strcmp(monsterName, "Shenwei2") == 0)
	{
		_monsterArray->addObject(monster);
		monster->attack(NAttack);
	}
	else
	{
		_monsterArray->addObject(monster);
		monster->doAI();
	}

	if (strcmp(monsterName, "ItachiSusano") == 0)
	{
		monster->setFlipX(_isFlipped);
		monster->setAnchorPoint(ccp(0.5f, 0));
		monster->setPosition(ccp(146 / 2 - 10, -40));
		addChild(monster, -1000);
	}
	else if (strcmp(monsterName, "SasukeSusano") == 0)
	{
		monster->setFlipX(_isFlipped);
		monster->setAnchorPoint(ccp(0.5f, 0));
		monster->setPosition(ccp(141 / 2, -6));
		addChild(monster, -1000);
	}
	else if (strcmp(monsterName, "CircleMark") == 0 ||
			 strcmp(monsterName, "Yominuma") == 0)
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

	Monster *monster = Monster::create();
	monster->setDelegate(_delegate);

	if (strcmp(getCharacter()->getCString(), "Deidara") == 0)
	{
		monster->setID(CCString::create("Spider"), CCString::create(ROLE_MON), _group);
	}
	else if (strcmp(getCharacter()->getCString(), "Sai") == 0)
	{
		monster->setID(CCString::create("Mouse"), CCString::create(ROLE_MON), _group);
		CCDictionary *callValue2 = CCDictionary::create();
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
	CCDictionary *file = (CCDictionary *)data;
	CCString *trapType = (CCString *)(file->objectForKey(1));

	if (strcmp(trapType->getCString(), "Amaterasu") == 0)
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			CharacterBase *tempHero = (CharacterBase *)pObject;
			if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0 && (strcmp(tempHero->_role->getCString(), "Player") == 0 || strcmp(tempHero->_role->getCString(), "Com") == 0) && tempHero->_actionState != State::HURT && tempHero->_actionState != State::DEAD)
			{
				float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
				if (distanceX < winSize.width / 2)
				{
					if (!tempHero->_isVisable)
					{
						if (strcmp(tempHero->getCharacter()->getCString(), "Konan") == 0 ||
							strcmp(tempHero->getCharacter()->getCString(), "Deidara") == 0)
						{
							tempHero->unschedule(schedule_selector(CharacterBase::disableBuff));
						}

						tempHero->setOpacity(255);
						tempHero->setVisible(true);

						if (tempHero->_hpBar)
						{
							tempHero->_hpBar->setVisible(true);
						}
						if (tempHero->_shadow)
						{
							tempHero->_shadow->setVisible(true);
						}

						tempHero->_isVisable = true;
					}
				}
			}
		}

		if (strcmp(getCharacter()->getCString(), "ImmortalSasuke") == 0)
		{
			CCPoint targetPoint = _mainTarget ? _mainTarget->getPosition() : getPosition();

			for (int z = 0; z < 3; z++)
			{
				if (z == 0)
				{
					Bullet *trap = Bullet::create();
					trap->setDelegate(_delegate);
					trap->_master = this;
					trap->setID(trapType, CCString::create(ROLE_MON), _group);
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
						trap->setID(trapType, CCString::create(ROLE_MON), _group);
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
					trap->setID(trapType, CCString::create(ROLE_MON), _group);
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
					trap->setID(trapType, CCString::create(ROLE_MON), _group);

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
					trap->setID(trapType, CCString::create(ROLE_MON), _group);
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
				trap->setID(trapType, CCString::create(ROLE_MON), _group);
				trap->setPosition(ccp(getPositionX() + (_isFlipped ? -48 : 48), getPositionY() + 22));
				trap->idle();
				trap->attack(NAttack);
				trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 2.5f);
				_delegate->addChild(trap, -trap->getPositionY());
			}
		}
	}
	else if (strcmp(trapType->getCString(), "Kusuri") == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			Bullet *trap = Bullet::create();
			trap->setDelegate(_delegate);
			trap->setAnchorPoint(ccp(0.5f, 0));
			trap->_master = this;
			trap->setID(trapType, CCString::create(ROLE_MON), _group);

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
	else if (strcmp(trapType->getCString(), "KageBom") == 0)
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			Hero *tempHero = (Hero *)pObject;
			if (strcmp(_group->getCString(), tempHero->_group->getCString()) != 0 && (strcmp(tempHero->_role->getCString(), "Player") == 0 || strcmp(tempHero->_role->getCString(), "Com") == 0) && tempHero->_actionState != State::DEAD && tempHero->_isVisable && !tempHero->_isSticking)
			{
				float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
				float tempRange1 = winSize.width / 2;
				if (abs(distanceX) <= tempRange1)
				{
					Monster *trap = Monster::create();
					trap->setDelegate(_delegate);
					trap->_master = this;
					trap->setID(trapType, CCString::create(ROLE_MON), _group);
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
			Monster *mo = (Monster *)pObject;
			if (strcmp(mo->getCharacter()->getCString(), "Traps") != 0)
			{
				if (strcmp(getCharacter()->getCString(), "Kiba") == 0)
				{
					mo->attack(SKILL1);
				}
				else if (strcmp(getCharacter()->getCString(), "Kankuro") == 0)
				{
					if (strcmp(mo->getCharacter()->getCString(), "Karasu") == 0)
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
				else if (strcmp(getCharacter()->getCString(), "Chiyo") == 0)
				{
					if (strcmp(mo->getCharacter()->getCString(), "Parents") == 0)
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
				else if (strcmp(getCharacter()->getCString(), "Itachi") == 0 ||
						 strcmp(getCharacter()->getCString(), "ImmortalSasuke") == 0)
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

	if (strcmp(_character->getCString(), "Lee") == 0 ||
		strcmp(_character->getCString(), "RockLee") == 0)
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

	CCString *tempAttackValue = CCString::createWithFormat("%s", getnAttackValue()->getCString());
	if (strcmp(_character->getCString(), "Naruto") == 0)
		setID(CCString::create("SageNaruto"), _role, _group);
	else if (strcmp(_character->getCString(), "SageNaruto") == 0)
		setID(CCString::create("RikudoNaruto"), _role, _group);
	else if (strcmp(_character->getCString(), "Jiraiya") == 0)
		setID(CCString::create("SageJiraiya"), _role, _group);
	else if (strcmp(_character->getCString(), "Sasuke") == 0)
		setID(CCString::create("ImmortalSasuke"), _role, _group);
	else if (strcmp(_character->getCString(), "Lee") == 0)
		setID(CCString::create("RockLee"), _role, _group);
	else if (strcmp(_character->getCString(), "RockLee") == 0)
		setID(CCString::create("Lee"), _role, _group);
	else if (strcmp(_character->getCString(), "Pain") == 0)
		setID(CCString::create("Nagato"), _role, _group);

	setMaxHP(CCString::createWithFormat("%ld", to_uint(getMaxHP()->getCString())));
	setHP(CCString::createWithFormat("%ld", to_uint(getHP()->getCString())));

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

	if (_role && strcmp(_role->getCString(), "Player") == 0)
		_delegate->setHPLose(getHpPercent());

	setnAttackValue(tempAttackValue);

	if (strcmp(_character->getCString(), "RockLee") == 0)
		return;

	// Update HudLayer
	if (strcmp(_role->getCString(), "Player") == 0)
	{
		auto charName = _character->getCString();

		_delegate->getHudLayer()->skill1Button->setCD(CCString::createWithFormat("%d", _sattackcoldDown1 * 1000));
		_delegate->getHudLayer()->skill2Button->setCD(CCString::createWithFormat("%d", _sattackcoldDown2 * 1000));
		_delegate->getHudLayer()->skill3Button->setCD(CCString::createWithFormat("%d", _sattackcoldDown3 * 1000));

		_delegate->getHudLayer()->skill1Button->_isColdChanged = true;
		_delegate->getHudLayer()->skill2Button->_isColdChanged = true;
		_delegate->getHudLayer()->skill3Button->_isColdChanged = true;

		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s_skill1.png", charName)->getCString());
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
	if (strcmp(_role->getCString(), "Player") == 0 && type == NAttack)
	{
		if (!_delegate->getSkillFinish() && !_isOnlySkillLocked)
			return;
	}

	switch (type)
	{
	case NAttack:
		_attackValue = to_int(getnAttackValue()->getCString());
		_attackType = _nattackType;
		_attackRangeX = _nattackRangeX;
		_attackRangeY = _nattackRangeY;
		nAttack();
		break;
	case SKILL1:
		if (strcmp(_role->getCString(), "Player") == 0)
		{
			if (_isControlled)
				_delegate->getHudLayer()->skill1Button->click();
		}

		_attackValue = to_int(_sattackValue1->getCString());
		_attackType = _sattackType1;
		_attackRangeX = _sattackRangeX1;
		_attackRangeY = _sattackRangeY1;
		sAttack(SKILL1);
		break;
	case SKILL2:
		if (strcmp(_role->getCString(), "Player") == 0)
		{
			if (_isControlled)
				_delegate->getHudLayer()->skill2Button->click();
		}

		_attackValue = to_int(_sattackValue2->getCString());
		_attackType = _sattackType2;
		_attackRangeX = _sattackRangeX2;
		_attackRangeY = _sattackRangeY2;
		sAttack(SKILL2);
		break;
	case SKILL3:
		if (strcmp(_role->getCString(), "Player") == 0)
		{
			if (_isControlled)
				_delegate->getHudLayer()->skill3Button->click();
		}

		_attackValue = to_int(_sattackValue3->getCString());
		_attackType = _sattackType3;
		_attackRangeX = _sattackRangeX3;
		_attackRangeY = _sattackRangeY3;
		sAttack(SKILL3);
		break;
	case OUGIS1:
		if (strcmp(_role->getCString(), "Player") != 0 || _isAI)
		{
			float newValue = atof(getCKR()->getCString()) - 15000;
			;
			setCKR(CCString::createWithFormat("%f", newValue));
			if (atof(getCKR()->getCString()) < 15000)
			{
				_isCanOugis1 = false;
			}
		}

		_attackValue = to_int(_sattackValue4->getCString());
		_attackType = _sattackType4;
		_attackRangeX = _sattackRangeX4;
		_attackRangeY = _sattackRangeY4;
		oAttack(OUGIS1);
		break;
	case OUGIS2:
		if (strcmp(_role->getCString(), "Player") != 0 || _isAI)
		{
			float newValue = atof(getCKR2()->getCString()) - 25000;
			setCKR2(CCString::createWithFormat("%f", newValue));
			if (atof(getCKR2()->getCString()) < 25000)
			{
				_isCanOugis2 = false;
			}
		}

		_attackValue = to_int(_sattackValue5->getCString());
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
			if (strcmp(_role->getCString(), "Player") == 0)
			{
				_delegate->setSkillFinish(false);
			}
			if (strcmp(_role->getCString(), "Bullet") != 0)
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
			if (strcmp(getCharacter()->getCString(), "Konan") == 0 ||
				strcmp(getCharacter()->getCString(), "Deidara") == 0)
			{
				unschedule(schedule_selector(CharacterBase::disableBuff));
			}

			setOpacity(255);
			setVisible(true);

			if (_hpBar)
			{
				_hpBar->setVisible(true);
			}
			if (_shadow)
			{
				_shadow->setVisible(true);
			}

			_isVisable = true;
		}

		stopAllActions();

		switch (type)
		{
		case SKILL1:
			if (_isCanSkill1)
			{
				_actionState = State::SATTACK;
				if (strcmp(_role->getCString(), "Player") == 0)
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
				if (strcmp(_role->getCString(), "Player") == 0)
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
				if (strcmp(_role->getCString(), "Player") == 0)
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
		if (strcmp(_role->getCString(), "Player") == 0)
		{
			_delegate->setSkillFinish(false);
		}
		if (!_isVisable)
		{
			if (strcmp(getCharacter()->getCString(), "Konan") == 0 ||
				strcmp(getCharacter()->getCString(), "Deidara") == 0)
			{
				unschedule(schedule_selector(CharacterBase::disableBuff));
			}

			setOpacity(255);
			setVisible(true);

			if (_hpBar)
			{
				_hpBar->setVisible(true);
			}

			if (_shadow)
			{
				_shadow->setVisible(true);
			}
			_isVisable = true;
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

		bool isPlayer = strcmp(_role->getCString(), "Player") == 0;

		if (isPlayer)
		{
			if (!_isAllAttackLocked && !_isOnlySkillLocked)
			{
				_delegate->setSkillFinish(true);
			}
		}

		if (!_delegate->_isAttackButtonRelease &&
			isPlayer &&
			_attackType && !_isAllAttackLocked)
		{
			_delegate->setSkillFinish(true);
			attack(NAttack);
		}
		else
		{
			if (isPlayer && checkHasMovement())
				return;

			runAction(_idleAction);
		}
	}
}

void CharacterBase::walk(CCPoint direction)
{
	if (_actionState == State::IDLE || _actionState == State::WALK || (_actionState == State::NATTACK && strcmp(getRole()->getCString(), "Player") != 0))
	{
		isHurtingTower = false;

		if (_actionState == State::NATTACK &&
			(strcmp(getCharacter()->getCString(), "Suigetsu") == 0 ||
			 strcmp(getCharacter()->getCString(), "Jugo") == 0 ||
			 strcmp(getCharacter()->getCString(), "Hiruzen") == 0 ||
			 strcmp(getCharacter()->getCString(), "Kisame") == 0) &&
			_isOnlySkillLocked)
		{
			if (strcmp(getRole()->getCString(), "Player") != 0)
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

		if (strcmp(_character->getCString(), "Itachi") == 0 ||
			strcmp(_character->getCString(), "ImmortalSasuke") == 0 ||
			strcmp(_character->getCString(), "Chiyo") == 0)
		{
			if (getMonsterArray() && getMonsterArray()->count() > 0)
			{
				CCObject *pObject;
				CCARRAY_FOREACH(getMonsterArray(), pObject)
				{
					Monster *mo = (Monster *)pObject;
					if (strcmp(mo->getCharacter()->getCString(), "ItachiSusano") == 0 ||
						strcmp(mo->getCharacter()->getCString(), "SasukeSusano") == 0)
					{
						mo->setFlipX(_isFlipped);
					}
					else if (strcmp(mo->getCharacter()->getCString(), "Parents") == 0)
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
			Hero *tempHero = (Hero *)pObject;
			if (strcmp(_group->getCString(), tempHero->_group->getCString()) == 0 &&
				strcmp(tempHero->_character->getCString(), "Chiyo") == 0 &&
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
		if (strcmp(_character->getCString(), "Chiyo") == 0)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				Monster *mo = (Monster *)pObject;
				if (strcmp(mo->getCharacter()->getCString(), "Parents") == 0 && !mo->_skillChangeBuffValue && mo->getActionState() != State::SATTACK && mo->getActionState() != State::DEAD)
				{
					CCPoint sp = ccpSub(mo->getPosition(), getPosition());
					if (sp.x <= 48)
					{
						return false;
					}
				}
			}
		}

		if (strcmp(_role->getCString(), "Player") == 0)
		{
			_delegate->setSkillFinish(false);
		}

		_actionState = State::HURT;
		stopAllActions();
		if (_hurtAction)
		{
			CCArray *list = CCArray::create();
			list->addObject(_hurtAction);
			CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::idle));
			list->addObject(call);
			CCAction *seq = CCSequence::create(list);
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
			Hero *tempHero = (Hero *)pObject;
			if (strcmp(_group->getCString(), tempHero->_group->getCString()) == 0 &&
				strcmp(tempHero->_character->getCString(), "Chiyo") == 0 &&
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

		if (strcmp(_character->getCString(), "Chiyo") == 0)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				Monster *mo = (Monster *)pObject;
				if (strcmp(mo->getCharacter()->getCString(), "Parents") == 0 && !mo->_skillChangeBuffValue && mo->getActionState() != State::SATTACK && mo->getActionState() != State::DEAD)
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

		if (strcmp(_role->getCString(), "Player") == 0)
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
		CCArray *list = CCArray::create();

		if (isHurtAction)
		{
			list->addObject(_hurtAction);
		}
		else
		{
			_isSticking = true;
			CharacterBase *attacker = _slayer;
			CCString *path;
			if (strcmp(attacker->getCharacter()->getCString(), "Kakuzu") == 0)
			{
				path = CCString::createWithFormat("%s_AirHurt_02.png", getCharacter()->getCString());
			}
			else
			{
				path = CCString::createWithFormat("%s_Hurt_02.png", getCharacter()->getCString());
			}

			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path->getCString());
			CCArray *tempArray = CCArray::create();
			tempArray->addObject(frame);
			CCAnimation *tempAnimation = CCAnimation::createWithSpriteFrames(tempArray, 0.1f);
			CCAction *tempAction = CCAnimate::create(tempAnimation);
			list->addObject(tempAction);
		}

		if (isStun)
		{
			CCDictionary *callValue = CCDictionary::create();
			callValue->setObject(CCString::create("stun"), 1);
			callValue->retain();
			CCFiniteTimeAction *call = CCCallFuncND::create(this, callfuncND_selector(CharacterBase::setSkillEffect), (void *)callValue);
			list->addObject(call);
		}

		CCAction *delay = CCDelayTime::create(delayTime / 1000);
		list->addObject(delay);

		CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::idle));
		list->addObject(call);

		CCAction *seq = CCSequence::create(list);
		runAction(seq);

		return true;
	}

	return false;
}

void CharacterBase::airHurt()
{
	if (_actionState == State::FLOAT || _actionState == State::AIRHURT)
	{
		if (strcmp(_role->getCString(), "Player") == 0)
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

		if (strcmp(_role->getCString(), "Player") == 0)
		{
			_delegate->setSkillFinish(false);
		}
		_actionState = State::HURT;

		CCActionInterval *mv;

		CCArray *list = CCArray::create();
		if (isImmediate)
		{
			stopAllActions();
			mv = CCMoveTo::create(0.2f, position);
			list->addObject(_hurtAction);
			runAction(mv);
		}
		else
		{
			CCPoint direction = ccpSub(getPosition(), position);
			position.x = direction.x > 0 ? getPositionX() - 16 : getPositionX() + 16;
			position.y = direction.y > 0 ? getPositionY() - 8 : getPositionY() + 8;
			mv = CCMoveTo::create(0.2f, position);
			list->addObject(mv);
		}

		CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::idle));
		list->addObject(call);
		CCAction *seq = CCSequence::create(list);
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
			Hero *tempHero = (Hero *)pObject;
			if (strcmp(_group->getCString(), tempHero->_group->getCString()) == 0 &&
				strcmp(tempHero->_character->getCString(), "Chiyo") == 0 &&
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

		if (strcmp(_character->getCString(), "Chiyo") == 0)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				Monster *mo = (Monster *)pObject;
				if (strcmp(mo->getCharacter()->getCString(), "Parents") == 0 && !mo->_skillChangeBuffValue && mo->getActionState() != State::SATTACK && mo->getActionState() != State::DEAD)
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

		if (strcmp(_role->getCString(), "Player") == 0)
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

		CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::knockDown));
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
		if (strcmp(_controller->getRole()->getCString(), "Player") == 0)
		{
			if (strcmp(_controller->getCharacter()->getCString(), "Ino") == 0)
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

		if (strcmp(getRole()->getCString(), "Player") == 0)
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

	if (strcmp(getCharacter()->getCString(), "Minato") == 0)
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

	if (strcmp(_role->getCString(), "Player") == 0)
	{
		_delegate->setSkillFinish(false);
		_delegate->getHudLayer()->hpLabel->setString("0");
		_delegate->getHudLayer()->status_hpbar->setOpacity(0);
	}

	//kill all buffEffect
	if (strcmp(_role->getCString(), "Player") == 0 || strcmp(_role->getCString(), "Com") == 0)
	{
		unschedule(schedule_selector(CharacterBase::healBuff));
		_buffStartTime = 0;
		unschedule(schedule_selector(CharacterBase::dehealBuff));
		if (strcmp(getCharacter()->getCString(), "RockLee") != 0 &&
			strcmp(getCharacter()->getCString(), "Lee") != 0)
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

			if (strcmp(_role->getCString(), "Player") == 0)
			{
				const char *dl = _delegate->getHudLayer()->deadLabel->getString();
				int deads = to_int(dl) + 1;
				_delegate->getHudLayer()->deadLabel->setString(CCString::createWithFormat("%d", deads)->getCString());
			}
		}

		if (!_isVisable)
		{
			setOpacity(255);

			setVisible(true);
			if (_hpBar)
			{
				_hpBar->setVisible(true);
			}

			if (_shadow)
			{
				_shadow->setVisible(true);
			}
			_isVisable = true;
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

	if (strcmp(_role->getCString(), "Player") == 0 || strcmp(_role->getCString(), "Com") == 0)
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", this);
	}

	if (strcmp(_role->getCString(), ROLE_CLONE) != 0 &&
		strcmp(_role->getCString(), ROLE_SUMMON) != 0)
	{
		CCActionInterval *fadeOut = CCFadeOut::create(0.5);
		CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::dealloc));
		CCArray *seqArray = CCArray::create();
		seqArray->addObject(_deadAction);

		if (strcmp(_role->getCString(), ROLE_FLOG) == 0)
		{
			seqArray->addObject(fadeOut);
		}
		seqArray->addObject(call);
		CCAction *seq = CCSequence::create(seqArray);
		runAction(seq);
	}
	else
	{
		unschedule(schedule_selector(CharacterBase::removeClone));
		CCDictionary *callValue = CCDictionary::create();
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
		CCActionInterval *fadeOut = CCFadeOut::create(0.5);
		CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(CharacterBase::dealloc));
		CCArray *seqArray = CCArray::create();
		if (_deadAction)
		{
			seqArray->addObject(_deadAction);
		}
		if (strcmp(_role->getCString(), ROLE_FLOG) == 0)
		{
			seqArray->addObject(fadeOut);
		}
		seqArray->addObject(call);
		CCAction *seq = CCSequence::create(seqArray);
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
	if (strcmp("Hero", type) == 0)
	{
		list = _delegate->_CharacterArray;
	}
	else if (strcmp(ROLE_FLOG, type) == 0)
	{
		if (strcmp(Akatsuki, _group->getCString()) == 0)
		{
			list = _delegate->_KonohaFlogArray;
		}
		else
		{
			list = _delegate->_AkatsukiFlogArray;
		}
	}
	else if (strcmp("Tower", type) == 0)
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
		CharacterBase *target = (CharacterBase *)pObject;

		if (target->_actionState == State::DEAD ||
			target->_isVisable == false ||
			target->_isInvincible ||
			strcmp(target->_role->getCString(), ROLE_KUGUTSU) == 0)
		{
			continue;
		}
		if ((getActionState() == State::OATTACK ||
			 getActionState() == State::O2ATTACK) ||
			(getMaster() && (getMaster()->getActionState() == State::OATTACK ||
							 getActionState() == State::O2ATTACK)))
		{
			if (strcmp(target->_role->getCString(), ROLE_CLONE) == 0 ||
				strcmp(target->_role->getCString(), ROLE_SUMMON) == 0 ||
				strcmp(target->_role->getCString(), "Monster") == 0)
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
	if (findSome)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// NOTE: Use half the window width as the search range
bool CharacterBase::findEnemy2(const char *type)
{
	CCArray *list;
	if (strcmp("Hero", type) == 0)
	{
		list = _delegate->_CharacterArray;
	}
	else if (strcmp(ROLE_FLOG, type) == 0)
	{
		if (strcmp(Akatsuki, _group->getCString()) == 0)
		{
			list = _delegate->_KonohaFlogArray;
		}
		else
		{
			list = _delegate->_AkatsukiFlogArray;
		}
	}
	else if (strcmp("Tower", type) == 0)
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
		CharacterBase *target = (CharacterBase *)pObject;

		if (target->_actionState == State::DEAD ||
			target->_isVisable == false ||
			strcmp(target->_role->getCString(), ROLE_KUGUTSU) == 0)
		{
			continue;
		}

		distance = ccpDistance(target->getPosition(), getPosition());
		sp = ccpSub(target->getPosition(), getPosition());
		if (abs(sp.x) < winSize.width / 2)
		{
			if (strcmp(target->_role->getCString(), ROLE_CLONE) != 0 &&
				strcmp(target->_role->getCString(), ROLE_SUMMON) != 0)
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

				if (strcmp(_group->getCString(), target->_group->getCString()) == 0)
				{
					if (abs(sp.x) < _delegate->currentMap->getTileSize().width * 3)
					{
						if (strcmp(target->_character->getCString(), Guardian_Roshi) != 0 && strcmp(target->_character->getCString(), Guardian_Han) != 0)
						{
							friendCombatPoint += baseSkillCombatPoint + to_int(target->getHP()->getCString()) +
												 (atof(target->getCKR()->getCString()) / 15000) * target->_sattackCombatPoint4 + (atof(target->getCKR2()->getCString()) / 25000) * target->_sattackCombatPoint5;
						}
					}
				}
				else
				{
					if (strcmp(target->_character->getCString(), Guardian_Roshi) != 0 && strcmp(target->_character->getCString(), Guardian_Han) != 0)
					{
						enemyCombatPoint += baseSkillCombatPoint + to_int(target->getHP()->getCString()) + (atof(target->getCKR()->getCString()) / 15000) * target->_sattackCombatPoint4 + (atof(target->getCKR2()->getCString()) / 25000) * target->_sattackCombatPoint5;
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

	if (findSome)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CharacterBase::checkBase()
{
	CCArray *list = _delegate->_CharacterArray;
	CCObject *pObject;

	CCARRAY_FOREACH(list, pObject)
	{
		CharacterBase *target = (CharacterBase *)pObject;
		if (target->_actionState == State::DEAD)
		{
			continue;
		}
		if (strcmp(_group->getCString(), target->_group->getCString()) != 0)
		{
			if (strcmp(_group->getCString(), Konoha) == 0)
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

	if (strcmp(Akatsuki, _group->getCString()) == 0)
	{
		list = _delegate->_KonohaFlogArray;
	}
	else
	{
		list = _delegate->_AkatsukiFlogArray;
	}

	CCARRAY_FOREACH(list, pObject)
	{
		CharacterBase *target = (CharacterBase *)pObject;
		if (target->_actionState == State::DEAD)
		{
			continue;
		}
		if (strcmp(_group->getCString(), target->_group->getCString()) != 0)
		{
			if (strcmp(_group->getCString(), Konoha) == 0)
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
	if (strcmp("Hero", type) == 0)
	{
		list = _delegate->_CharacterArray;
	}
	else if (strcmp(ROLE_FLOG, type) == 0)
	{
		if (strcmp(Akatsuki, _group->getCString()) == 0)
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
		CharacterBase *target = (CharacterBase *)pObject;

		if (strcmp(_group->getCString(), target->_group->getCString()) != 0 &&
			strcmp(target->_role->getCString(), ROLE_KUGUTSU) != 0 &&
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
						if (strcmp(target->getCharacter()->getCString(), "Choji") == 0 ||
							strcmp(target->getCharacter()->getCString(), "Sakura") == 0)
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
						if (strcmp(target->getCharacter()->getCString(), "Choji") == 0 ||
							strcmp(target->getCharacter()->getCString(), "Sakura") == 0)
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
		if (findSome == true)
		{
			return true;
		}
		else
		{
			return false;
		}
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

	if (strcmp(Konoha, _group->getCString()) == 0)
	{
		moveDirection = ccpNormalize(ccp(1, 0));
	}
	else
	{
		moveDirection = ccpNormalize(ccp(-1, 0));
	}

	walk(moveDirection);
}

// [For AI] 使AI撤退，只有横向移动方向
bool CharacterBase::stepBack()
{
	if (_isControlled)
		return false;
	CCPoint moveDirection;

	if (strcmp(Konoha, _group->getCString()) == 0)
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

	if (strcmp(Konoha, _group->getCString()) == 0 && getPositionX() >= _delegate->currentMap->getTileSize().width * 2)
	{
		moveDirection = CCPoint(ccp(-1, _diretionY));
		walk(moveDirection);
		return true;
	}
	else if (strcmp(Akatsuki, _group->getCString()) == 0 && getPositionX() <= (_delegate->currentMap->getMapSize().width - 2) * _delegate->currentMap->getTileSize().width)
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
	if (_isCanItem1 && to_int(getCoin()->getCString()) >= 50)
	{
		if (_delegate->_isHardCoreGame)
		{
			if (battleCondiction >= 0)
			{
				if (!_isHealling)
				{
					if (to_uint(getMaxHP()->getCString()) - to_uint(getHP()->getCString()) >= 3000 + gearRecoverValue && getGearArray()->count() > 1)
						setItem(Item1);
					else if (to_uint(getHP()->getCString()) < 5000 && getGearArray()->count() > 0)
						setItem(Item1);
					else if (to_uint(getHP()->getCString()) < 1500)
						setItem(Item1);
				}
			}
			else
			{
				if (to_uint(getMaxHP()->getCString()) - to_uint(getHP()->getCString()) >= 3000 + gearRecoverValue && !_isHealling && getGearArray()->count() > 0)
					setItem(Item1);
				else if (to_uint(getHP()->getCString()) < 3000)
					setItem(Item1);
			}
		}
		else
		{
			if (to_uint(getHP()->getCString()) < 1500 && strcmp(getGroup()->getCString(), Konoha) == 0)
				setItem(Item1);
			if (to_uint(getHP()->getCString()) < 500 && strcmp(getGroup()->getCString(), Akatsuki) == 0)
				setItem(Item1);
		}
	}

	if (battleCondiction >= 0)
	{
		if (strcmp(Konoha, _group->getCString()) == 0)
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

	if (to_uint(getHP()->getCString()) < 1500 && !_isControlled)
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

	if (strcmp(_character->getCString(), "Itachi") == 0 ||
		strcmp(_character->getCString(), "ImmortalSasuke") == 0)
	{
		if (getMonsterArray() && getMonsterArray()->count() > 0)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				Monster *mo = (Monster *)pObject;
				if (strcmp(mo->getCharacter()->getCString(), "ItachiSusano") == 0 ||
					strcmp(mo->getCharacter()->getCString(), "SasukeSusano") == 0)

					mo->_isFlipped = _isFlipped;
				mo->setFlipX(_isFlipped);
			}
		}
	}
}

void CharacterBase::changeGroup()
{
	if (strcmp(getGroup()->getCString(), Konoha) == 0)
		setGroup(CCString::create(Akatsuki));
	else
		setGroup(CCString::create(Konoha));

	if (_hpBar && strcmp(getRole()->getCString(), "Player") != 0)
	{
		if (strcmp(getGroup()->getCString(), _delegate->currentPlayer->getGroup()->getCString()) != 0)
		{
			_hpBar->changeBar("hp_bar_r.png");
		}
		else if (strcmp(getRole()->getCString(), "Com") == 0)
		{
			_hpBar->changeBar("hp_bar_b.png");
		}
	}

	if (strcmp(getRole()->getCString(), "Player") == 0)
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
				CharacterBase *target = (CharacterBase *)pObject;
				if (target->_hpBar)
				{
					if (strcmp(_group->getCString(), target->_group->getCString()) != 0)
					{
						if (strcmp(target->getRole()->getCString(), ROLE_FLOG) == 0)
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
						if (strcmp(target->getRole()->getCString(), ROLE_FLOG) == 0)
						{
							target->_hpBar->changeBar("flog_bar.png");
						}
						else if (strcmp(target->getRole()->getCString(), "Tower") == 0)
						{
							target->_hpBar->changeBar("hp_bar.png");
						}
						else
						{
							if (strcmp(target->getRole()->getCString(), "Player") != 0)
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

void CharacterBase::autoFlip(CharacterBase* attacker)
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
