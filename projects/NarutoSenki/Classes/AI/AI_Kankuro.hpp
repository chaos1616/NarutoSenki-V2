#pragma once
#include "Characters.h"

class AI_Kankuro : public Hero
{
	void perform()
	{

		_mainTarget = NULL;
		findEnemy2("Hero");

		if (_isCanGear06)
		{
			if ((getActionState() == State::FLOAT_AIR ||
				 getActionState() == State::AIRHURT ||
				 getActionState() == State::HURT ||
				 getActionState() == State::KOCKDOWN) &&
				getHpPercent() < 0.5 && !_isBati && !_isWudi)
			{
				useGear(gear06);
			}
		}
		if (atoi(getCoin()->getCString()) >= 500 && !_isControled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear06);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear04);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear08);
			}
		}

		if (checkRetri())
		{
			if (_mainTarget != NULL)
			{
				if (stepBack2())
				{
					return;
				}
			}
			else
			{
				if (stepBack())
				{
					return;
				}
			}
		}

		if (isBaseDanger && checkBase() && !_isControled)
		{
			bool needBack = false;
			if (strcmp(Akatsuki, getGroup()->getCString()) == 0)
			{
				if (getPositionX() < 85 * 32)
				{
					needBack = true;
				}
			}
			else
			{
				if (getPositionX() > 11 * 32)
				{
					needBack = true;
				}
			}
			if (needBack)
			{
				if (stepBack2())
				{
					return;
				}
			}
		}

		bool isFound1 = false;
		bool isFound2 = false;
		bool isFound3 = false;

		if (getMonsterArray() && getMonsterArray()->count() > 0)
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
			{

				if (_isCanSkill3)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (_isCanSkill1 && !isFound1 && !_isControled)
				{
					attack(SKILL1);
					return;
				}
				else if (_isCanOugis1 && !_isControled && !isFound2)
				{
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanOugis2 && !_isControled && _delegate->_isOugis2Game && !isFound3)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 5000 && !_isHealling && !_isControled)
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
					else
					{
						changeSide(sp);
						attack(NAttack);
					}

					return;
				}
			}
		}
		_mainTarget = NULL;
		if (!findEnemy2("Flog"))
		{
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

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
			{
				if (_isCanOugis1 && !_isControled && !isFound2)
				{
					changeSide(sp);
					attack(OUGIS1);
				}
				else if (_isCanOugis2 && !_isControled && _delegate->_isOugis2Game && !isFound3)
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
			{
				idle();
			}
		}
		else
		{
			stepOn();
		}
	}
};
