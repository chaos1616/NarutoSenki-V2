#pragma once
#include "Characters.h"

class AI_Kakuzu : public Hero
{
	void perform();
};

void AI_Kakuzu::perform()
{

	_mainTarget = NULL;
	if (_actionState == ACTION_STATE_IDLE || _actionState == ACTION_STATE_WALK || _actionState == ACTION_STATE_ATTACK)
	{

		if (this->getHpPercent() > 0.3f && !_isControled && _isCanSkill1)
		{
			CCObject *pObject;
			float distance;
			float curDistance = 0;
			CCPoint sp;

			CCARRAY_FOREACH(this->getDelegate()->_CharacterArray, pObject)
			{
				CharacterBase *target = (CharacterBase *)pObject;
				if ((strcmp(target->getRole()->getCString(), "Player") == 0 ||
					 strcmp(target->getRole()->getCString(), "Com") == 0) &&
					target->getActionState() == ACTION_STATE_DEAD)
				{
					distance = ccpDistance(target->getPosition(), this->getPosition());
					sp = ccpSub(target->getPosition(), this->getPosition());

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
					sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), this->getPosition());
				}
				else
				{
					sp = ccpSub(_mainTarget->getPosition(), this->getPosition());
				}

				if (abs(sp.x) > 32 || abs(sp.y) > 32)
				{
					moveDirection = ccpNormalize(sp);
					this->walk(moveDirection);
					return;
				}
				else
				{
					this->changeSide(sp);
					this->attack(SKILL1);
				}

				return;
			}
		}
	}

	this->findEnemy2("Hero");
	if (atoi(this->getCoin()->getCString()) >= 500 && !_isControled && _delegate->_isHardCoreGame)
	{
		if (this->getGearArray()->count() == 0)
		{
			this->setGear(gear03);
		}
		else if (this->getGearArray()->count() == 1)
		{
			this->setGear(gear08);
		}
		else if (this->getGearArray()->count() == 2)
		{
			this->setGear(gear04);
		}
	}

	if (this->checkRetri())
	{
		if (_mainTarget != NULL)
		{
			if (this->stepBack2())
			{
				return;
			}
		}
		else
		{
			if (this->stepBack())
			{
				return;
			}
		}
	}

	if (isBaseDanger && this->checkBase() && !_isControled)
	{
		bool needBack = false;
		if (strcmp("Akatsuki", this->getGroup()->getCString()) == 0)
		{
			if (this->getPositionX() < 85 * 32)
			{
				needBack = true;
			}
		}
		else
		{
			if (this->getPositionX() > 11 * 32)
			{
				needBack = true;
			}
		}
		if (needBack)
		{
			if (this->stepBack2())
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
			sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), this->getPosition());
		}
		else
		{
			sp = ccpSub(_mainTarget->getPosition(), this->getPosition());
		}
		if (_actionState == ACTION_STATE_IDLE || _actionState == ACTION_STATE_WALK || _actionState == ACTION_STATE_ATTACK)
		{

			if (_isCanSkill3)
			{
				this->changeSide(sp);
				this->attack(SKILL3);
				return;
			}
			else if (_isCanOugis1 && !_isControled && isSummonAble)
			{
				this->attack(OUGIS1);
				return;
			}
			else if (_isCanSkill2)
			{

				if (abs(sp.x) > 96 || abs(sp.y) > 32)
				{
					moveDirection = ccpNormalize(sp);
					this->walk(moveDirection);
					return;
				}

				if (_isCanGear03)
				{
					this->useGear(gear03);
				}

				this->changeSide(sp);
				this->attack(SKILL2);
				return;
			}
			else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 5000 && !_isHealling && !_isControled)
			{
				if (abs(sp.x) < 160)
				{
					this->stepBack2();
					return;
				}
				else
				{
					this->idle();
					return;
				}
			}
			else if (abs(sp.x) < 128)
			{
				if (abs(sp.x) > 32 || abs(sp.y) > 32)
				{
					moveDirection = ccpNormalize(sp);
					this->walk(moveDirection);
					return;
				}
				else
				{

					this->changeSide(sp);
					this->attack(NAttack);
				}

				return;
			}
		}
	}

	if (!this->findEnemy2("Flog"))
	{
		this->findEnemy2("Tower");
	}

	if (_mainTarget)
	{

		CCPoint moveDirection;
		CCPoint sp;

		if (_mainTarget->_originY)
		{
			sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), this->getPosition());
		}
		else
		{
			sp = ccpSub(_mainTarget->getPosition(), this->getPosition());
		}

		if (abs(sp.x) > 32 || abs(sp.y) > 32)
		{
			moveDirection = ccpNormalize(sp);
			this->walk(moveDirection);
			return;
		}

		if (_actionState == ACTION_STATE_IDLE || _actionState == ACTION_STATE_WALK || _actionState == ACTION_STATE_ATTACK)
		{
			if (_isCanOugis1 && !_isControled && !isSummonAble)
			{
				this->changeSide(sp);
				this->attack(OUGIS1);
			}
			else
			{
				this->changeSide(sp);
				this->attack(NAttack);
			}
		}
		return;
	}

	if (_isHealling && this->getHpPercent() < 1)
	{
		if (_actionState == ACTION_STATE_IDLE || _actionState == ACTION_STATE_WALK || _actionState == ACTION_STATE_ATTACK)
		{
			this->idle();
		}
	}
	else
	{
		this->stepOn();
	}
}
