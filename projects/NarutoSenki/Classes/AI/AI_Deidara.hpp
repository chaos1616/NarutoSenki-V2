#pragma once
#include "Characters.h"

class AI_Deidara : public Hero
{
	void perform()
	{

		_mainTarget = NULL;
		this->findEnemy2("Hero");
		if (atoi(this->getCoin()->getCString()) >= 500 && !_isControled && _delegate->_isHardCoreGame)
		{
			if (this->getGearArray()->count() == 0)
			{
				this->setGear(gear00);
			}
			else if (this->getGearArray()->count() == 1)
			{
				this->setGear(gear01);
			}
			else if (this->getGearArray()->count() == 2)
			{
				this->setGear(gear05);
			}
		}

		if (this->checkRetri())
		{
			if (_mainTarget != NULL)
			{
				if (this->stepBack2())
				{
					if (_isCanGear00 && !_isBati)
					{
						this->useGear(gear00);
					}
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

		if (_mainTarget && (battleCondiction >= 0 || _isCanSkill3 || _isCanOugis1 || _isBati))
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

				if (_isCanOugis2 && !_isControled && _delegate->_isOugis2Game && _mainTarget->getGP() < 5000 && !_isBati)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 16)
					{
						if (_isCanGear00)
						{
							this->useGear(gear00);
						}
						moveDirection = ccpNormalize(sp);
						this->walk(moveDirection);
						return;
					}
					else
					{
						this->changeSide(sp);
						this->attack(OUGIS2);
					}
				}
				else if (_isCanOugis1 && !_isControled && _mainTarget->getGP() < 5000 && !_isBati)
				{
					this->changeSide(sp);
					this->attack(OUGIS1);
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getGP() < 5000 && !_isBati)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 16)
					{
						if (_isCanGear00)
						{
							this->useGear(gear00);
						}
						moveDirection = ccpNormalize(sp);
						this->walk(moveDirection);
						return;
					}

					this->changeSide(sp);
					this->attack(SKILL3);
					return;
				}
				else if (_isCanSkill2 && !_isBati)
				{
					this->changeSide(sp);
					this->attack(SKILL2);
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
						if (_skillChangeBuffValue)
						{
							if (!_isBati)
							{
								this->changeSide(sp);
								this->attack(NAttack);
							}
						}
						this->idle();
						return;
					}
				}
				else if (_isCanSkill1 && !_isBati)
				{
					this->changeSide(sp);
					this->attack(SKILL1);
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if ((abs(sp.x) > 8 || abs(sp.y) > 8) && _isBati)
					{
						moveDirection = ccpNormalize(sp);
						this->walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_isCanSkill1 && !_skillChangeBuffValue)
					{
						moveDirection = ccpNormalize(sp);
						this->walk(moveDirection);
						return;
					}

					if (!_isBati)
					{
						this->changeSide(sp);
						this->attack(NAttack);
					}

					return;
				}
			}
		}
		if (battleCondiction >= 0)
		{
			_mainTarget = NULL;
			if (!this->findEnemy2("Flog"))
			{
				this->findEnemy2("Tower");
			}
		}
		else
		{
			_mainTarget = NULL;
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
				if (strcmp(_mainTarget->getRole()->getCString(), "Tower") == 0 &&
					_isCanOugis2 &&
					!_isControled && _delegate->_isOugis2Game && !_isBati && isBaseDanger)
				{

					this->changeSide(sp);
					this->attack(OUGIS2);
				}
				else if (_isCanSkill1 && !_isBati && strcmp(_mainTarget->getRole()->getCString(), "Tower") == 0)
				{
					this->changeSide(sp);
					this->attack(SKILL1);
				}
				else if (_isCanSkill2 && !_isBati)
				{
					this->changeSide(sp);
					this->attack(SKILL2);
					return;
				}
				else if (!_isBati)
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
			if (_isCanGear00 && !_isBati)
			{
				this->useGear(gear00);
			}
			this->stepOn();
		}
	}
};
