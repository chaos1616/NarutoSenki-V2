#pragma once
#include "Hero.hpp"

class Hiruzen : public Hero
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
				setGear(gear02);
			else if (getGearArray()->count() == 2)
				setGear(gear08);
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
				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && !_isArmored && _mainTarget->getHPValue() < 10000 && !_mainTarget->_isCanGear06)
				{
					if (abs(sp.x) < 32)
					{
						stepBack();
						return;
					}
					else if (abs(sp.x) > 96 || abs(sp.y) > 32)
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
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isArmored)
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
				else if (_isCanSkill3 && _mainTarget->getGP() < 5000 && !_isArmored && !_skillChangeBuffValue)
				{
					changeSide(sp);
					attack(SKILL3);
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
					if (abs(sp.x) > 96 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanSkill1 && _mainTarget->getGP() < 5000 && !_isArmored)
					{
						if ((abs(sp.x) > 32 || abs(sp.y) > 32))
						{
							moveDirection = ccpNormalize(sp);
							walk(moveDirection);
							return;
						}
						changeSide(sp);
						attack(SKILL1);
					}
					else if (_isCanSkill2 && _mainTarget->getGP() < 5000 && !_isArmored)
					{
						if (abs(sp.x) < 32)
						{
							stepBack();
							return;
						}
						changeSide(sp);
						attack(SKILL2);
					}
					else
					{
						if (abs(sp.x) > 32 || abs(sp.y) > 32)
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
				if (_mainTarget->isFlog() && _isCanSkill1 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanSkill2 && _mainTarget->getGP() < 5000 && !_isArmored && _mainTarget->isFlog() && isBaseDanger)
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
		_isArmored = true;
		_nattackRangeX = 16;
		_nattackRangeY = 48;
		settempAttackValue1(CCString::createWithFormat("%d", getNAttackValue()));
		setnAttackValue(CCString::createWithFormat("%d", 560));

		_isOnlySkillLocked = true;

		setIdleAction(createAnimation(skillSPC1Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));

		lockOugisButtons();
	}

	void setActionResume()
	{
		if (_skillChangeBuffValue == 0)
			return;

		_isArmored = false;
		_isOnlySkillLocked = false;
		if (getTempAttackValue1())
		{
			setnAttackValue(CCString::createWithFormat("%d", getTempAttackValue1()));
			settempAttackValue1(nullptr);
		}
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));

		lockOugisButtons();

		_skillChangeBuffValue = 0;
	}
};
