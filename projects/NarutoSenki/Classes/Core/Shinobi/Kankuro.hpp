#pragma once
#include "Hero.hpp"
#include "Kuchiyose/Karasu.hpp"
#include "Kuchiyose/Sanshouuo.hpp"
#include "Kuchiyose/Saso.hpp"

class Kankuro : public Hero
{
	void perform()
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
				setGear(gear04);
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

		bool isFound1 = false;
		bool isFound2 = false;
		bool isFound3 = false;

		if (hasMonsterArray())
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				Monster *mo = (Monster *)pObject;
				if (strcmp(mo->getCharacter()->getCString(), "Saso") == 0)
				{
					isFound3 = true;
				}
				if (strcmp(mo->getCharacter()->getCString(), "Sanshouuo") == 0)
				{
					isFound2 = true;
				}
				if (strcmp(mo->getCharacter()->getCString(), "Karasu") == 0)
				{
					isFound1 = true;
				}
			}
		}

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (isFreeActionState())
			{
				if (_isCanSkill3)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (_isCanSkill1 && !isFound1 && !_isControlled)
				{
					attack(SKILL1);
					return;
				}
				else if (_isCanOugis1 && !_isControlled && !isFound2)
				{
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && !isFound3)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 5000 && !_isHealling && !_isControlled)
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
				if (_isCanOugis1 && !_isControlled && !isFound2)
				{
					changeSide(sp);
					attack(OUGIS1);
				}
				else if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && !isFound3)
				{
					changeSide(sp);
					attack(OUGIS2);
				}
				else if (_isCanSkill1 && !isFound1)
				{
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

	void changeAction()
	{
		if (isPlayer())
		{
			_delegate->getHudLayer()->skill1Button->setLock();
			_delegate->getHudLayer()->skill2Button->unLock();
		}
	}

	void setActionResume()
	{
		if (isPlayer())
		{
			_delegate->getHudLayer()->skill1Button->unLock();
			_delegate->getHudLayer()->skill2Button->setLock();
		}
		_skillChangeBuffValue = 0;
	}

	Hero *createClone(int cloneTime)
	{
		Hero *clone = nullptr;

		if (!_monsterArray)
		{
			_monsterArray = CCArray::create();
			_monsterArray->retain();
		}

		if (cloneTime == 0)
		{
			clone = create<Karasu>(CCString::create("Karasu"), CCString::create(kRoleKugutsu), getGroup());
		}
		else if (cloneTime == 1)
		{
			clone = create<Sanshouuo>(CCString::create("Sanshouuo"), CCString::create(kRoleKugutsu), getGroup());
			if (isPlayer())
			{
				if (_delegate->getHudLayer()->skill4Button)
				{
					_delegate->getHudLayer()->skill4Button->setLock();
				}
			}
		}
		else if (cloneTime == 2)
		{
			clone = create<Saso>(CCString::create("Saso"), CCString::create(kRoleKugutsu), getGroup());
			if (isPlayer())
			{
				if (_delegate->getHudLayer()->skill5Button)
				{
					_delegate->getHudLayer()->skill5Button->setLock();
				}
			}
		}

		clone->_isArmored = true;
		_monsterArray->addObject(clone);
		return clone;
	}
};
