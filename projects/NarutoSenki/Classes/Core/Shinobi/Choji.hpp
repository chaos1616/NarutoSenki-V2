#pragma once
#include "Hero.hpp"

class Choji : public Hero
{
	void perform()
	{
		_mainTarget = nullptr;
		findEnemy2("Hero");

		if (_isCanGear06)
		{
			if ((getActionState() == State::FLOAT ||
				 getActionState() == State::AIRHURT ||
				 getActionState() == State::HURT ||
				 getActionState() == State::KNOCKDOWN) &&
				getHpPercent() < 0.5 && !_isArmored && !_isInvincible)
			{
				useGear(gear06);
			}
		}
		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear06);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear01);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear04);
			}
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

		if (_mainTarget && strcmp(_mainTarget->getRole()->getCString(), "Flog") != 0)
		{
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
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
					{
						stepBack2();
						return;
					}
					else
					{

						idle();
						return;
					}
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
					else if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && _mainTarget->getGP() < 5000 && !_isArmored)
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
			if (!findEnemy2("Flog"))
			{
				findEnemy2("Tower");
			}
		}
		else
		{
			_mainTarget = nullptr;
			findEnemy2("Tower");
		}

		if (_mainTarget)
		{
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

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				if (_isCanSkill2 && !_isArmored && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanOugis1 && !_isControlled && isBaseDanger && !_isArmored && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
				{
					changeSide(sp);
					attack(OUGIS1);
				}
				else if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && strcmp(_mainTarget->getRole()->getCString(), "Tower") == 0 && !_isArmored)
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				idle();
			}
		}
		else
		{
			stepOn();
		}
	}

	void changeAction()
	{
		_isArmored = true;
		setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));
		setIdleAction(createAnimation(skillSPC4Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 5.0f, true, false));

		_tempAttackType = _nattackType;
		_nattackType = _spcattackType3;

		setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) + 460));
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

	void resumeAction(float dt)
	{
		setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) - 460));
		_nattackRangeX = 16;
		_nattackRangeY = 48;
		_nattackType = _tempAttackType;
		_tempAttackType = nullptr;

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

	void setActionResume()
	{
		if (_skillChangeBuffValue == 0)
			return;

		unschedule(schedule_selector(Choji::resumeAction));

		setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) - 460));
		_nattackRangeX = 16;
		_nattackRangeY = 48;
		_nattackType = _tempAttackType;
		_tempAttackType = nullptr;

		_isOnlySkillLocked = false;
		_isArmored = false;
		_gardValue -= 5000;

		setWalkAction(createAnimation(walkArray, 10.0f, true, false));
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));

		lockOugisButtons();

		if (_hpBar)
		{
			_hpBar->setPositionY(getHeight());
		}

		_skillChangeBuffValue = 0;
	}
};
