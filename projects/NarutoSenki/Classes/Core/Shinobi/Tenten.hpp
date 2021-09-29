#pragma once
#include "Hero.hpp"

class Tenten : public Hero
{
	void perform()
	{
		_mainTarget = nullptr;
		findHeroHalf();
		if (getCoinValue() >= 500 && !_isControlled && _delegate->_enableGear)
		{
			if (getGearArray()->count() == 0)
				setGear(gear00);
			else if (getGearArray()->count() == 1)
				setGear(gear05);
			else if (getGearArray()->count() == 2)
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
				if (_isCanGear00)
				{
					useGear(gear00);
				}
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
				if (_isCanGear00)
				{
					useGear(gear00);
				}
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
				if (_isCanSkill1)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && _mainTarget->getGP() < 5000 && !_skillChangeBuffValue)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 16)
					{
						if (_isCanGear00)
						{
							useGear(gear00);
						}
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanOugis1 && !_isControlled && !_mainTarget->_isArmored && _mainTarget->getGP() < 5000 && !_skillChangeBuffValue)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 16)
					{
						if (_isCanGear00)
						{
							useGear(gear00);
						}
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(OUGIS1);

					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_skillChangeBuffValue && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if ((abs(sp.x) > 96 || abs(sp.y) > 16) && !_skillChangeBuffValue)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanSkill2 && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else if (_isCanSkill3 && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else
					{
						if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_skillChangeBuffValue)
						{
							moveDirection = ccpNormalize(sp);
							walk(moveDirection);
							return;
						}
						else
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

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (isFreeActionState())
			{
				if (_mainTarget->isFlog() && _isCanSkill1)
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_mainTarget->isFlog() && _isCanSkill3)
				{
					changeSide(sp);
					attack(SKILL3);
				}
				else if (_mainTarget->isFlog() && _isCanSkill2 && isBaseDanger)
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

		if (_isHealling && getHpPercent() < 1)
		{
			if (isFreeActionState())
				idle();
		}
		else
		{
			if (_isCanGear00)
				useGear(gear00);
			stepOn();
		}
	}

	void changeAction()
	{
		setNAttackAction(createAnimation(skillSPC1Array, 10.0f, false, true));
	}

	void resumeAction(float dt)
	{
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
		CharacterBase::resumeAction(dt);
	}
};
