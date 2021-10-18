#pragma once
#include "Hero.hpp"

class Hidan : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		bool _isFound = false;
		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
				if (mo->isCharacter("CircleMark"))
				{
					_mainTarget = mo;
					_isFound = true;
					CCPoint moveDirection;
					CCPoint sp;

					if (_mainTarget->_originY)
					{
						sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
					}
					else
					{
						sp = ccpSub(_mainTarget->getPosition(), getPosition());
					}
					if ((abs(sp.x) > 8 || abs(sp.y) > 8))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else
					{
						if (_isArmored)
						{
							for (auto hero : getGameLayer()->_CharacterArray)
							{
								if (hero->getGroup() != getGroup() && hero->getHPValue() < 2000 && hero->getActionState() != State::DEAD && hero->isPlayerOrCom())
								{
									attack(NAttack);
									return;
								}
							}

							idle();
							return;
						}
					}
				}
			}
		}

		if (!_isFound)
		{
			findHeroHalf();
		}

		if (_isCanGear06)
		{
			if ((_actionState == State::FLOAT ||
				 _actionState == State::AIRHURT ||
				 _actionState == State::HURT ||
				 _actionState == State::KNOCKDOWN) &&
				getHpPercent() < 0.5 && !_isArmored && !_isInvincible)
			{
				useGear(gear06);
			}
		}

		if (getCoinValue() >= 500 && !_isControlled && getGameLayer()->_enableGear)
		{
			if (getGearArray().size() == 0)
				setGear(gear06);
			else if (getGearArray().size() == 1)
				setGear(gear01);
			else if (getGearArray().size() == 2)
				setGear(gear07);
		}

		if (checkRetri() && !_isArmored && !_isFound)
		{
			if (_mainTarget != nullptr)
			{
				if (stepBack2())
					return;
			}
			else
			{
				if (stepBack())
					return;
			}
		}

		if (isBaseDanger && checkBase() && !_isControlled && !_isArmored && !_isFound)
		{
			bool needBack = false;
			if (isAkatsukiGroup())
			{
				if (getPositionX() < 85 * 32)
					needBack = true;
			}
			else
			{
				if (getPositionX() > 11 * 32)
					needBack = true;
			}

			if (needBack)
			{
				if (stepBack2())
					return;
			}
		}

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (isFreeActionState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && !_isArmored)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					if (_isCanSkill1 && !_isArmored && !_isFound)
					{
						changeSide(sp);
						attack(SKILL1);
						return;
					}
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getGP() < 5000 && !_isArmored)
				{
					if (abs(sp.x) > 56 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControlled && !_isArmored && !_isFound)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if ((abs(sp.x) > 48 || abs(sp.y) > 32) && !_isArmored)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					if (_isCanOugis1 && !_isArmored && !_isControlled && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill3 && !_isArmored)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else
					{
						if (!_isArmored)
						{
							changeSide(sp);
							attack(NAttack);
						}
						else
						{
							idle();
						}
					}

					return;
				}
			}
		}

		if (!_mainTarget && !_isFound && !_isArmored)
		{
			if (notFindFlogHalf())
			{
				findTowerHalf();
			}
		}

		if (_mainTarget && _mainTarget->isNotMon() && !_isArmored)
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (isFreeActionState())
			{
				if (_isCanSkill3 && _mainTarget->isFlog() && isBaseDanger && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL3);
				}
				else if (_isCanSkill2 && _mainTarget->isFlog() && isBaseDanger && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else
				{
					changeSide(sp);
					attack(NAttack);
				}
			}
			return;
		}

		if (!_isArmored)
		{
			if (_isHealling && getHpPercent() < 1)
			{
				if (isFreeActionState())
				{
					idle();
				}
			}
			else
			{
				stepOn();
			}
		}
		else
		{
			if (isFreeActionState())
				idle();
		}
	}

	void changeAction() override
	{
		_isArmored = true;
		_isTaunt = true;
		_isOnlySkillLocked = true;
		setIdleAction(createAnimation(skillSPC1Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));

		lockOugisButtons();
	}

	void resumeAction(float dt) override
	{
		_isArmored = false;
		_isTaunt = false;
		_isOnlySkillLocked = false;
		unlockOugisButtons();

		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));

		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
				std::erase(getGameLayer()->_CharacterArray, mo);

				CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(mo);
				mo->setActionState(State::DEAD);
				mo->removeFromParent();
			}
			_monsterArray.clear();
		}

		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill1Button->unLock();
		}

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			idle();
		}
		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		unschedule(schedule_selector(Hidan::resumeAction));
		_isArmored = false;
		_isTaunt = false;
		_isOnlySkillLocked = false;
		unlockOugisButtons();

		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));

		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
				std::erase(getGameLayer()->_CharacterArray, mo);

				CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(mo);
				mo->setActionState(State::DEAD);
				mo->removeFromParent();
			}
			_monsterArray.clear();
		}

		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill1Button->unLock();
		}

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			idle();
		}

		_skillChangeBuffValue = 0;
	}

	/**
	 * Callbacks
	 */

	bool onHit(CharacterBase *attacker) override
	{
		if (_skillChangeBuffValue <= 0)
			return true;

		bool _isCounter = false;
		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
				float distanceX = ccpSub(mo->getPosition(), getPosition()).x;
				float distanceY = ccpSub(mo->getPosition(), getPosition()).y;
				if (abs(distanceX) < 40 && abs(distanceY) < 15)
				{
					_isCounter = true;
				}
			}
		}

		if (_isCounter && attacker->isNotGuardian())
		{
			if (attacker->getMaster() && attacker->getMaster()->getActionState() != State::DEAD)
			{
				attacker->getMaster()->setDamage(this, attacker->getEffectType(), attacker->_attackValue, attacker->_isFlipped);
			}
			else if (!attacker->getMaster())
			{
				if (attacker->getActionState() != State::DEAD)
				{
					attacker->setDamage(this, attacker->getEffectType(), attacker->_attackValue, attacker->_isFlipped);
				}
			}

			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (isNotSameGroupAs(hero) && hero->isPlayerOrCom() && hero->getActionState() != State::DEAD)
				{
					hero->setDamage(this, attacker->getEffectType(), attacker->_attackValue / 2, attacker->_isFlipped);
				}
			}

			return false;
		}

		return true;
	}

	bool onBulletHit(CharacterBase *attacker) override
	{
		if (_skillChangeBuffValue <= 0)
			return true;

		bool _isCounter = false;
		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
				float distanceX = ccpSub(mo->getPosition(), getPosition()).x;
				float distanceY = ccpSub(mo->getPosition(), getPosition()).y;
				if (abs(distanceX) < 40 && abs(distanceY) < 15)
				{
					_isCounter = true;
				}
			}
		}

		if (_isCounter)
		{
			if (attacker->getMaster() && attacker->getMaster()->getActionState() != State::DEAD)
			{
				attacker->getMaster()->setDamage(this, attacker->getEffectType(), attacker->_attackValue, attacker->_isFlipped);
			}

			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (isNotSameGroupAs(hero) && hero->isPlayerOrCom() && hero->getActionState() != State::DEAD)
				{
					hero->setDamage(this, attacker->getEffectType(), attacker->_attackValue / 2, attacker->_isFlipped);
				}
			}

			return false;
		}

		return true;
	}
};
