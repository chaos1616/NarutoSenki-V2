#pragma once
#include "Characters.h"

class AI_Ino : public Hero
{
	void perform()
	{

		_mainTarget = NULL;
		this->findEnemy2("Hero");

		if (_skillChangeBuffValue)
		{
			return;
		}

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
				this->setGear(gear05);
			}
			else if (this->getGearArray()->count() == 2)
			{
				this->setGear(gear01);
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

		if (atoi(this->getMaxHP()->getCString()) - atoi(this->getHP()->getCString()) >= 3000 &&
			atoi(this->getCoin()->getCString()) >= 50 && !_isHealling && _isCanItem1 && _isBati)
		{
			this->setItem(Item1);
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

				if (_isCanOugis2 && !_isControled && _delegate->_isOugis2Game)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 16)
					{
						moveDirection = ccpNormalize(sp);
						this->walk(moveDirection);
						return;
					}
					else
					{
						this->changeSide(sp);
						this->attack(OUGIS2);
					}

					return;
				}
				else if (_mainTarget->getGP() < 5000 && (_isCanSkill3 || _isCanSkill2))
				{

					if (abs(sp.x) > 96 || abs(sp.y) > 16)
					{
						moveDirection = ccpNormalize(sp);
						this->walk(moveDirection);
						return;
					}

					if (_isCanSkill2)
					{
						this->changeSide(sp);
						this->attack(SKILL2);
					}
					else if (_isCanSkill3)
					{
						this->changeSide(sp);
						this->attack(SKILL3);
					}

					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControled)
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

					if (_isCanOugis1 && !_isControled && _mainTarget->getGP() < 5000)
					{
						this->changeSide(sp);
						this->attack(OUGIS1);
					}
					else if (_isCanSkill1)
					{
						this->changeSide(sp);
						this->attack(SKILL1);
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
				if (strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0 && _isCanSkill1)
				{
					this->changeSide(sp);
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
