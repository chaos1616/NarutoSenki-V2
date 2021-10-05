#pragma once
#include "Hero.hpp"

class Itachi : public Hero
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

		if (getCoinValue() >= 500 && !_isControlled && _delegate->_enableGear)
		{
			if (getGearArray()->count() == 0)
				setGear(gear06);
			else if (getGearArray()->count() == 1)
				setGear(gear02);
			else if (getGearArray()->count() == 2)
				setGear(gear05);
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
				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && !_isArmored)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(OUGIS2);

					return;
				}
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS1);

					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isArmored && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128 || _isArmored)
				{
					if (abs(sp.x) > 196 || abs(sp.y) > 64)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 56 || abs(sp.y) > 32) && !_isArmored)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanSkill3 && !_isArmored && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else if (_isCanSkill2 && !_isArmored && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else if (_isCanSkill1 && !_isArmored && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL1);
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
		_mainTarget = nullptr;
		if (notFindFlogHalf())
			findTowerHalf();

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
				if (_isCanSkill3 && !_isArmored && _mainTarget->isFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL3);
				}
				else if (_isCanSkill2 && !_isArmored && _mainTarget->isFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanSkill1 && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL1);
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
		setIdleAction(createAnimation(skillSPC1Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));
		setKnockDownAction(createAnimation(skillSPC4Array, 10.0f, false, true));
		setWalkSpeed(112);
		_originSpeed = 112;

		_isOnlySkillLocked = true;

		settempAttackValue1(to_ccstring(getNAttackValue()));
		setnAttackValue(to_ccstring(560));

		_nattackRangeX = 128;
		_nattackRangeY = 64;

		_gardValue += 5000;
		_isArmored = true;

		lockOugisButtons();
	}

	void resumeAction(float dt) override
	{
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));

		_isOnlySkillLocked = false;

		unlockOugisButtons();

		setWalkSpeed(224);
		_originSpeed = 224;
		if (hasTempAttackValue1())
		{
			setnAttackValue(to_ccstring(getTempAttackValue1()));
			settempAttackValue1(nullptr);
		}
		_nattackRangeX = 16;
		_nattackRangeY = 48;
		_gardValue -= 5000;
		_isArmored = false;

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			knockDown();
		}

		setKnockDownAction(createAnimation(knockDownArray, 10.0f, false, true));

		if (hasMonsterArrayAny())
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				auto mo = (Monster *)pObject;
				mo->removeFromParent();
			}
			getMonsterArray()->removeAllObjects();
			setMonsterArray(nullptr);
		}
		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		if (_skillChangeBuffValue == 17)
		{
			unschedule(schedule_selector(Itachi::resumeAction));

			setIdleAction(createAnimation(idleArray, 5.0f, true, false));
			setWalkAction(createAnimation(walkArray, 10.0f, true, false));
			setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
			setKnockDownAction(createAnimation(knockDownArray, 10.0f, false, true));

			_isOnlySkillLocked = false;
			unlockOugisButtons();

			setWalkSpeed(224);

			_originSpeed = 224;
			if (hasTempAttackValue1())
			{
				setnAttackValue(to_ccstring(getTempAttackValue1()));
				settempAttackValue1(nullptr);
			}
			_nattackRangeX = 16;
			_nattackRangeY = 48;
			_gardValue -= 5000;
			_isArmored = false;

			_skillChangeBuffValue = 0;
		}
	}
};
