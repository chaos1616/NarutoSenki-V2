#pragma once
#include "Core/Unit.h"

// Detailed implementation of Physics module of unit base class

void Unit::acceptAttack(Ref *object)
{
	auto attacker = (Unit *)object;
	bool isCannotMiss = false;

	if (!onAcceptAttack(attacker))
		return;

	if (attacker->getName() == HeroEnum::Hiruzen && attacker->_state == State::O2ATTACK)
	{
		isCannotMiss = true; // TODO: Add this as a parameter of Unit::acceptAttack
	}

	if (getGroup() == attacker->getGroup() ||
		!_isVisable ||
		(_isInvincible && !isCannotMiss) ||
		_state == State::DEAD)
	{
		return;
	}

	// Tower
	if (isTower()) // TODO: Move to Tower class
	{
		bool isHit = false;
		if (attacker->_attackType == "nAttack" &&
			attacker->_effectType != "f_hit" &&
			attacker->_effectType != "c_hit" &&
			attacker->_effectType != "o_hit" &&
			attacker->_effectType != "b_hit" &&
			attacker->_effectType != "bc_hit")
		{
			if (setHitBox().intersectsRect(attacker->setHalfBox()))
			{
				isHit = true;
			}
		}
		else if (attacker->_effectType == "n_hit")
		{
			bool isHitX = false;
			float distanceX = (attacker->getPosition() - getPosition()).x;

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
				auto call = CallFunc::create(std::bind(&Unit::disableShack, this));
				auto delay = DelayTime::create(0.5f);
				auto seq = newSequence(CCShake::createWithStrength(0.1f, 2, 0), delay, call);
				runAction(seq);
			}
		}

		return;
	}
	// Bullet
	if (attacker->isBullet()) // TODO: Move to Projectile class
	{
		if (setHitBox().intersectsRect(attacker->setHitBox()))
		{
			if (!onBulletHit(attacker))
				return;
			setDamage(attacker);

			if (attacker->getName() == ProjectileEnum::HiraishinKunai ||
				attacker->getName() == ProjectileEnum::Shintenshin)
			{
				if (isPlayerOrCom() && isNotGuardian() && _state != State::DEAD)
				{
					attacker->stopAllActions();
					attacker->dealloc();

					if (attacker->getName() == ProjectileEnum::Shintenshin && !attacker->_isCatchOne)
					{
						attacker->_isCatchOne = true;
						if (attacker->_master)
						{
							attacker->_master->_mainTarget = this;
							attacker->_master->changeAction();
						}
					}
				}
			}
		}

		return;
	}
	// Hero
	{
		bool isHitX = false;

		float distanceX = (attacker->getPosition() - getPosition()).x;

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

		if (!isHitX)
		{
			return;
		}

		float attackerPosY;
		float currentPosY;
		if (attacker->_state == State::JUMP)
			attackerPosY = attacker->_originY;
		else
			attackerPosY = attacker->getPositionY();

		if (_state == State::FLOAT || _state == State::JUMP || _state == State::AIRHURT)
			currentPosY = _originY;
		else
			currentPosY = getPositionY();

		if (abs(currentPosY - attackerPosY) > attacker->_attackRangeY)
		{
			return;
		}

		auto hitType = attacker->_effectType;

		attacker->_isHitOne = true;
		// record the slayer
		_slayer = attacker;

		// flog hurt
		if (isFlog())
		{
			if (hitType == "o_hit")
			{
				setKnockLength(48);
				setKnockDirection(attacker->_isFlipped);
				hurt();
			}
			else if (hitType == "ac_hit")
			{
				airHurt();
			}
			else if (hitType == "f_hit" || hitType == "bf_hit")
			{
				autoFlip(attacker);
				floatUP(64, true);
			}
			else if (hitType == "f2_hit")
			{
				autoFlip(attacker);
				floatUP(128, true);
			}
			else if (hitType == "b_hit")
			{
				autoFlip(attacker);
				floatUP(16, false);
			}
			else if (hitType == "ab_hit")
			{
				absorb(attacker->getPosition(), true);
			}
			else if (hitType == "s_hit")
			{
				absorb(attacker->getPosition(), false);
			}
		}
		// hero hurt
		else if (isPlayerOrCom() || isClone())
		{
			if (hitType == "l_hit")
			{
				if (!_isArmored)
				{
					setKnockLength(32);
				}
				hurt();
			}
			else if (hitType == "c_hit" ||
					 hitType == "bc_hit")
			{
				if (!_isArmored)
				{
					setKnockLength(1);
				}

				if (attacker->getName() == HeroEnum::Kakuzu && _sticker)
				{
					Unit *stHero = _sticker;
					if (stHero->getName() == HeroEnum::Kakuzu && stHero->hearts <= 4)
					{
						attacker->hearts += 1;

						if (attacker->_heartEffect)
						{
							auto frame = getSpriteFrame("Heart_Effect_{:02d}", attacker->hearts);
							attacker->_heartEffect->setDisplayFrame(frame);
						}
					}

					if (attacker->isPlayer() && attacker->hearts > 0)
					{
						int monCount = 0;
						for (auto mo : attacker->getMonsterArray())
						{
							if (mo->getName() != "Traps")
							{
								monCount++;
							}
						}

						if (monCount < 3 && attacker->getLV() >= 2)
						{
							getGameLayer()->getHudLayer()->skill4Button->unLock();
						}
					}
				}
				else if (attacker->getName() == HeroEnum::Nagato && _sticker)
				{
					Unit *stHero = _sticker;
					if (stHero->getName() == HeroEnum::Nagato && stHero->hearts <= 2)
						attacker->hearts += 1;
				}

				hurt();
			}
			else if (hitType == "ts_hit")
			{
				if (!_isArmored)
				{
					setKnockLength(1);
				}
				if (hurt() &&
					(!attacker->_isCatchOne || attacker->getName() == SkillEnum::FakeMinato))
				{
					attacker->_isCatchOne = true;
					if (attacker->_master)
					{
						if (attacker->getName() == SkillEnum::FakeMinato)
						{
							setPosition(Vec2(attacker->_master->_isFlipped ? attacker->_master->getPositionX() - 64 : attacker->_master->getPositionX() + 64,
											 attacker->_master->getPositionY() + 2));
						}
						else
						{
							setPosition(Vec2(attacker->_master->_isFlipped ? attacker->_master->getPositionX() - 48 : attacker->_master->getPositionX() + 48,
											 attacker->_master->getPositionY()));
						}

						CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", this);
						getGameLayer()->reorderChild(this, -getPositionY());
					}
				}
			}
			else if (hitType == "sl_hit")
			{
				if (!_isArmored)
				{
					setKnockLength(1);
				}
				hurt();
				if (getWalkSpeed() == 224)
				{
					setWalkSpeed(112);
					schedule(schedule_selector(Unit::disableDebuff), 3);
				}
			}
			else if (hitType == "ac_hit")
			{
				if (_state == State::FLOAT || _state == State::AIRHURT)
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
			else if (hitType == "o_hit")
			{
				if (_state != State::OATTACK ||
					(_state == State::OATTACK &&
					 (attacker->_state == State::O2ATTACK ||
					  attacker->_state == State::OATTACK)))
				{
					if (!_isArmored)
					{
						setKnockLength(48);
					}
					setKnockDirection(attacker->_isFlipped);
					hardHurt(500, true, false, false, false);
				}
			}
			else if (hitType == "o2_hit")
			{
				if (!_isArmored)
				{
					setKnockLength(1);
				}
				setKnockDirection(attacker->_isFlipped);
				hardHurt(1000, true, false, false, true);
			}
			else if (hitType == "ob_hit")
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
					schedule(schedule_selector(Unit::dehealBuff), 1);
				}
				scheduleOnce(schedule_selector(Unit::disableBuff), 5);
			}
			else if (hitType == "ct_hit")
			{
				if (_state != State::OATTACK ||
					(_state == State::OATTACK &&
					 (attacker->_state == State::O2ATTACK ||
					  attacker->_state == State::OATTACK)))
				{
					if (attacker->_isCatchOne == false ||
						attacker->getName() == SkillEnum::Shenwei)
					{
						if (attacker->_master)
						{
							if (attacker->getName() == SkillEnum::Kuroari ||
								attacker->getName() == SkillEnum::Shenwei ||
								attacker->getName() == SkillEnum::Sabaku ||
								attacker->getName() == SkillEnum::Shenwei2)
							{
								if (hardHurt(3000, false, true, false, false))
								{
									attacker->_isCatchOne = true;
									scheduleOnce(schedule_selector(Unit::reCatched), 2.9f);
								}
							}
							else if (attacker->getName() == SkillEnum::SandBall)
							{
								if (hardHurt(1000, false, true, false, false))
								{
									attacker->_isCatchOne = true;
									scheduleOnce(schedule_selector(Unit::reCatched), 0.9f);
								}
							}
							else if (attacker->_master->getName() == HeroEnum::Shikamaru)
							{
								bool underAttack = false;
								if (attacker->getName() == SkillEnum::KageHand)
								{
									underAttack = hardHurt(6000, false, false, true, false);
									if (underAttack)
									{
										attacker->stopAllActions();
										attacker->schedule(schedule_selector(Unit::getSticker), 0.1f);
										lbAttackerId = attacker->_master->getCharId();
										schedule(schedule_selector(Unit::lostBlood), 1.0f);
										lostBloodValue = 400;
										scheduleOnce(schedule_selector(Unit::removeLostBlood), 6.0f);
									}
								}
								else if (attacker->getName() == SkillEnum::QuanRen ||
										 attacker->getName() == SkillEnum::KageBom)
								{
									underAttack = hardHurt(3000, false, false, true, false);
								}

								if (underAttack)
								{
									attacker->_isCatchOne = true;
									setPosition(Vec2(attacker->getPositionX(), attacker->getPositionY() + 1));
									getGameLayer()->reorderChild(this, -getPositionY());
								}
							}
							else if (attacker->_master->getName() == HeroEnum::Itachi ||
									 attacker->_master->getName() == HeroEnum::Chiyo)
							{
								bool underAttack = false;

								if (attacker->_master->getName() == HeroEnum::Chiyo)
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
									setPosition(Vec2(attacker->getPositionX() + 2, attacker->getPositionY() - 2));
									getGameLayer()->reorderChild(this, -getPositionY());
								}
							}
							else if (attacker->_master->getName() == HeroEnum::Nagato)
							{
								bool underAttack = false;

								if (attacker->getName() == HeroEnum::NarakaPath)
									underAttack = hardHurt(2000, false, false, true, false);

								if (underAttack)
								{
									attacker->_isCatchOne = true;
									setPosition(Vec2(getPositionX() + (_isFlipped ? -30 : 30), getPositionY() - 10));
									getGameLayer()->reorderChild(this, -getPositionY());
								}
							}
						}
						else
						{
							if (attacker->getName() == HeroEnum::Lee ||
								attacker->getName() == HeroEnum::RockLee)
							{
								if (hardHurt(1000, false, true, false, false))
								{
									attacker->_isCatchOne = true;
									scheduleOnce(schedule_selector(Unit::reCatched), 1.1f);
								}
							}
							else if (attacker->getName() == HeroEnum::Kakuzu)
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
									setPosition(Vec2(attacker->getPositionX() + (attacker->_isFlipped ? -28 : 28), attacker->getPositionY() - 1));
									setFlipX(attacker->_isFlipped ? false : true);
									getGameLayer()->reorderChild(this, -getPositionY());
								}
							}
							else if (attacker->getName() == HeroEnum::Tobi)
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
			else if (hitType == "f_hit" || hitType == "bf_hit")
			{
				autoFlip(attacker);
				if (_state != State::OATTACK ||
					(_state == State::OATTACK &&
					 (attacker->_state == State::O2ATTACK ||
					  attacker->_state == State::OATTACK)))
				{
					floatUP(64, true);
				}
			}
			else if (hitType == "f2_hit")
			{
				autoFlip(attacker);
				if (_state != State::OATTACK ||
					(_state == State::OATTACK &&
					 (attacker->_state == State::O2ATTACK ||
					  attacker->_state == State::OATTACK)))
				{
					floatUP(128, true);
				}
			}
			else if (hitType == "b_hit")
			{
				autoFlip(attacker);

				if (_state != State::OATTACK ||
					(_state == State::OATTACK &&
					 (attacker->_state == State::O2ATTACK ||
					  attacker->_state == State::OATTACK)))
				{
					floatUP(16, false);
				}
			}
			else if (hitType == "ab_hit")
			{
				absorb(attacker->getPosition(), true);
			}
			else if (hitType == "s_hit")
			{
				absorb(attacker->getPosition(), false);
			}
		}

		if (onHit(attacker))
			setDamage(attacker);
	}
}

Rect Unit::setHalfBox()
{
	Rect halfbox = Rect(_isFlipped ? getPositionX() - getContentSize().width / 2 : getPositionX(),
						getPositionY() + getContentSize().height / 2,
						getContentSize().width / 2,
						getContentSize().height / 2);
	return halfbox;
}

Rect Unit::setHitBox()
{
	Rect hitbox = boundingBox();
	return hitbox;
}
