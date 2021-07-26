#pragma once
#include "Hero.hpp"
#include "Kuchiyose/Slug.hpp"

class Tsunade : public Hero
{
	void perform()
	{
		_mainTarget = nullptr;
		findHero();
		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled&& _delegate->_enableGear)
		{
			if (getGearArray()->count() == 0)
				setGear(gear03);
			else if (getGearArray()->count() == 1)
				setGear(gear02);
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
			if (strcmp(Akatsuki, getGroup()->getCString()) == 0)
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

		if (_mainTarget && strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) != 0)
		{
			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			else
				sp = ccpSub(_mainTarget->getPosition(), getPosition());

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && _mainTarget->getGP() < 5000 && !_isArmored)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 16)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else
					{
						changeSide(sp);
						attack(OUGIS2);
					}
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getGP() < 5000 && !_isArmored)
				{
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
					if (abs(sp.x) > 64 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 32) || (abs(sp.y) > 32 && !_isCanSkill2 && !_isArmored && !_isCanOugis1))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					if (_isCanGear03)
					{
						useGear(gear03);
					}
					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isArmored)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill2 && !_isArmored)
					{
						changeSide(sp);
						attack(SKILL2);
						return;
					}
					else if (_isCanSkill1 && !_isArmored)
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
		if (!findFlog())
			findTower();

		if (_mainTarget)
		{
			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			else
				sp = ccpSub(_mainTarget->getPosition(), getPosition());

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				if (_isCanGear03)
				{
					useGear(gear03);
				}
				if (strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) == 0 && _isCanSkill1 && !_isArmored && isBaseDanger)
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
				idle();
		}
		else
		{
			stepOn();
		}
	}

	void changeAction()
	{
		setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) + 250));
		_isOnlySkillLocked = true;
		_nattackRangeX = 32;
		_nattackRangeY = 48;
		_tempAttackType = _nattackType;
		_nattackType = _spcattackType3;

		_isArmored = true;
		_healBuffValue = 3000;
		schedule(schedule_selector(CharacterBase::healBuff), 1);

		setIdleAction(createAnimation(skillSPC1Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));

		lockOugisButtons();
	}

	void resumeAction(float dt)
	{
		setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) - 250));
		_nattackRangeX = 16;
		_nattackRangeY = 48;
		_nattackType = _tempAttackType;
		_tempAttackType = nullptr;

		_isOnlySkillLocked = false;

		unlockOugisButtons();
		_isArmored = false;

		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			idle();
		}
		CharacterBase::resumeAction(dt);
	}

	Hero *createClone(int cloneTime)
	{
		auto clone = create<Slug>(CCString::create("Slug"), CCString::create(ROLE_SUMMON), getGroup());
		clone->_isArmored = true;
		return clone;
	}
};
