#pragma once
#include "Hero.hpp"

class Konan : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();
		if (getCoin() >= 500 && !_isControlled && getGameLayer()->_enableGear)
		{
			if (getGearArray().size() == 0)
				setGear(gear03);
			else if (getGearArray().size() == 1)
				setGear(gear05);
			else if (getGearArray().size() == 2)
				setGear(gear02);
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
				else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking && !_isArmored)
				{
					if ((abs(sp.x) > 48 || abs(sp.y) > 16))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_mainTarget->getGP() < 5000 && !_isVisable && !_isArmored && (_isCanSkill3 || _isCanSkill2) &&
						 _mainTarget->getActionState() != State::KNOCKDOWN)
				{
					if ((abs(sp.x) > 128 || abs(sp.y) > 16))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 96)
					{
						stepBack();
						return;
					}

					if (_isCanSkill3)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else if (_isCanSkill2)
					{
						changeSide(sp);
						attack(SKILL2);
					}

					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if ((abs(sp.x) > 8 || abs(sp.y) > 8) && _isArmored)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 48 || abs(sp.y) > 32))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 32 && !_isArmored)
					{
						stepBack();
						return;
					}

					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isArmored)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill2 && !_isArmored && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else
					{
						if (_isCanGear03)
						{
							useGear(gear03);
						}
						if (!_isArmored)
						{
							changeSide(sp);
							attack(NAttack);
						}
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

			if ((abs(sp.x) > 8 || abs(sp.y) > 8) && _isArmored)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}
			else if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (isFreeActionState())
			{
				if (_isCanGear03)
				{
					useGear(gear03);
				}
				if (_isCanOugis1 && !_isControlled && !_isArmored && _mainTarget->isFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(OUGIS1);
				}
				else if (_isCanSkill2 && !_isArmored && _mainTarget->isFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (!_isArmored)
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
		_isAllAttackLocked = true;
		_isArmored = true;

		_attackType = _spcattackType2;
		_attackValue = getSpcAttackValue2();
		_attackRangeX = _spcattackRangeX2;
		_attackRangeY = _spcattackRangeY2;

		setWalkSpeed(320);
		_originSpeed = 320;

		setIdleAction(createAnimation(skillSPC1Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
		if (_hpBar)
		{
			_hpBar->setPositionY(90);
		}
		lockOugisButtons();
	}

	void resumeAction(float dt) override
	{
		_isAllAttackLocked = false;
		_isArmored = false;
		_originSpeed = 224;

		setWalkSpeed(224);

		unlockOugisButtons();

		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			idle();
		}

		if (_hpBar)
		{
			_hpBar->setPositionY(getHeight());
		}
		CharacterBase::resumeAction(dt);
	}
};
