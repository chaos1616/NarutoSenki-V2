#pragma once
#include "Hero.hpp"

class Choji : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

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
			if (getGearArray()->count() == 0)
				setGear(gear06);
			else if (getGearArray()->count() == 1)
				setGear(gear01);
			else if (getGearArray()->count() == 2)
				setGear(gear04);
		}

		if (checkRetri())
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

		if (isBaseDanger && checkBase() && !_isControlled)
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
				if (_isCanSkill1 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getGP() < 5000 && !_isArmored)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 16)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControlled && !_isArmored)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if (abs(sp.x) > 32 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isArmored)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill2 && _mainTarget->getGP() < 5000 && !_isArmored && _skillUPBuffValue)
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getGP() < 5000 && !_isArmored)
					{
						changeSide(sp);
						attack(OUGIS2);
					}
					else
					{
						changeSide(sp);
						attack(NAttack);
					}

					return;
				}
			}
		}

		if (battleCondiction >= 0)
		{
			_mainTarget = nullptr;
			if (notFindFlogHalf())
			{
				findTowerHalf();
			}
		}
		else
		{
			_mainTarget = nullptr;
			findTowerHalf();
		}

		if (_mainTarget)
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
				if (_isCanSkill2 && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanOugis1 && !_isControlled && isBaseDanger && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(OUGIS1);
				}
				else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->isTower() && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS2);
				}
				else
				{
					changeSide(sp);
					attack(NAttack);
				}
			}
			return;
		}

		if (_isHealling && getHpPercent() < 1)
		{
			if (isFreeActionState())
				idle();
		}
		else
		{
			stepOn();
		}
	}

	void changeAction() override
	{
		_isArmored = true;
		setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));
		setIdleAction(createAnimation(skillSPC4Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 5.0f, true, false));

		_originNAttackType = _nattackType->m_sString;
		_nattackType = _spcattackType3;

		setnAttackValue(to_ccstring(getNAttackValue() + 460));
		_nattackRangeX = 32;
		_nattackRangeY = 48;
		_isOnlySkillLocked = true;

		lockOugisButtons();
		_gardValue += 5000;

		if (_hpBar)
		{
			_hpBar->setPositionY(108);
		}
	}

	void resumeAction(float dt) override
	{
		setnAttackValue(to_ccstring(getNAttackValue() - 460));
		_nattackRangeX = 16;
		_nattackRangeY = 48;
		_nattackType->m_sString = _originNAttackType;

		_isOnlySkillLocked = false;
		_isArmored = false;
		_gardValue -= 5000;

		setWalkAction(createAnimation(walkArray, 10.0f, true, false));
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			idle();
		}

		unlockOugisButtons();

		if (_hpBar)
		{
			_hpBar->setPositionY(getHeight());
		}
		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		unschedule(schedule_selector(Choji::resumeAction));

		setnAttackValue(to_ccstring(getNAttackValue() - 460));
		_nattackRangeX = 16;
		_nattackRangeY = 48;

		_isOnlySkillLocked = false;
		_isArmored = false;
		_gardValue -= 5000;

		setWalkAction(createAnimation(walkArray, 10.0f, true, false));
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));

		unlockOugisButtons();

		if (_hpBar)
		{
			_hpBar->setPositionY(getHeight());
		}

		_skillChangeBuffValue = 0;
	}

private:
	string _originNAttackType;
};
