#pragma once
#include "Characters.h"

class AI_Kakuzu : public Hero
{
	void perform()
	{

		_mainTarget = NULL;
		if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
		{

			if (getHpPercent() > 0.3f && !_isControled && _isCanSkill1)
			{
				CCObject *pObject;
				float distance;
				float curDistance = 0;
				CCPoint sp;

				CCARRAY_FOREACH(getDelegate()->_CharacterArray, pObject)
				{
					CharacterBase *target = (CharacterBase *)pObject;
					if ((strcmp(target->getRole()->getCString(), "Player") == 0 ||
						 strcmp(target->getRole()->getCString(), "Com") == 0) &&
						target->getActionState() == State::DEAD)
					{
						distance = ccpDistance(target->getPosition(), getPosition());
						sp = ccpSub(target->getPosition(), getPosition());

						if (abs(sp.x) < (winSize.width / 2))
						{
							if (target->_isTaunt)
							{
								_mainTarget = target;
							}
							if (curDistance && abs(curDistance) > abs(distance))
							{
								_mainTarget = target;
								curDistance = distance;
							}
							else if (!curDistance)
							{
								curDistance = distance;
								_mainTarget = target;
							}
						}
					}
				}

				if (_mainTarget)
				{
					CCPoint moveDirection;
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
					else
					{
						changeSide(sp);
						attack(SKILL1);
					}

					return;
				}
			}
		}

		findEnemy2("Hero");
		if (atoi(getCoin()->getCString()) >= 500 && !_isControled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear03);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear08);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear04);
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

		bool isSummonAble = false;

		if (((getMonsterArray() && getMonsterArray()->count() < 3) || !_monsterArray) && hearts > 0)
		{
			isSummonAble = true;
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
				else if (_isCanOugis1 && !_isControled && isSummonAble)
				{
					attack(OUGIS1);
					return;
				}
				else if (_isCanSkill2)
				{

					if (abs(sp.x) > 96 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanGear03)
					{
						useGear(gear03);
					}

					changeSide(sp);
					attack(SKILL2);
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
				if (_isCanOugis1 && !_isControled && !isSummonAble)
				{
					changeSide(sp);
					attack(OUGIS1);
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
