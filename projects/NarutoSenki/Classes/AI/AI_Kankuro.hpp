#pragma once
#include "Characters.h"

class AI_Kankuro : public Hero
{
	void perform()
	{

		_mainTarget = NULL;
		this->findEnemy2("Hero");

		if (_isCanGear06)
		{
			if ((this->getActionState() == State::FLOAT_AIR ||
				 this->getActionState() == State::AIRHURT ||
				 this->getActionState() == State::HURT ||
				 this->getActionState() == State::KOCKDOWN) &&
				this->getHpPercent() < 0.5 && !_isBati && !_isWudi)
			{
				this->useGear(gear06);
			}
		}
		if (atoi(this->getCoin()->getCString()) >= 500 && !_isControled && _delegate->_isHardCoreGame)
		{
			if (this->getGearArray()->count() == 0)
			{
				this->setGear(gear06);
			}
			else if (this->getGearArray()->count() == 1)
			{
				this->setGear(gear04);
			}
			else if (this->getGearArray()->count() == 2)
			{
				this->setGear(gear08);
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
			if (strcmp(Akatsuki, this->getGroup()->getCString()) == 0)
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
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), this->getPosition());
			}
			else
			{
				sp = ccpSub(_mainTarget->getPosition(), this->getPosition());
			}
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
			{

				if (_isCanSkill3)
				{
					this->changeSide(sp);
					this->attack(SKILL3);
					return;
				}
				else if (_isCanSkill1 && !isFound1 && !_isControled)
				{
					this->attack(SKILL1);
					return;
				}
				else if (_isCanOugis1 && !_isControled && !isFound2)
				{
					this->changeSide(sp);
					this->attack(OUGIS1);
					return;
				}
				else if (_isCanOugis2 && !_isControled && _delegate->_isOugis2Game && !isFound3)
				{
					this->changeSide(sp);
					this->attack(OUGIS2);
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
		_mainTarget = NULL;
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

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
			{
				if (_isCanOugis1 && !_isControled && !isFound2)
				{
					this->changeSide(sp);
					this->attack(OUGIS1);
				}
				else if (_isCanOugis2 && !_isControled && _delegate->_isOugis2Game && !isFound3)
				{
					this->changeSide(sp);
					this->attack(OUGIS2);
				}
				else if (_isCanSkill1 && !isFound1)
				{
					this->attack(SKILL1);
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
			{
				this->idle();
			}
		}
		else
		{
			this->stepOn();
		}
	}
};
