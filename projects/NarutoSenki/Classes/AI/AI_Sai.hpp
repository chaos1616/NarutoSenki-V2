#pragma once
#include "Characters.h"

class AI_Sai : public Hero
{
	void perform();
};

void AI_Sai::perform()
{

	_mainTarget = NULL;
	this->findEnemy2("Hero");

	if (_isCanGear06)
	{
		if ((this->getActionState() == ACTION_STATE_FLOAT ||
			 this->getActionState() == ACTION_STATE_AIRHURT ||
			 this->getActionState() == ACTION_STATE_HURT ||
			 this->getActionState() == ACTION_STATE_KOCKDOWN) &&
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

			if (_isCanOugis2 && !_isControled && _delegate->_isOugis2Game && !_isBati && _mainTarget->getGP() < 5000 && !_mainTarget->_isBati && _mainTarget->getActionState() != ACTION_STATE_KOCKDOWN && !_mainTarget->_isSticking)
			{
				if (abs(sp.x) > 48 || abs(sp.y) > 16)
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
			else if (_isCanSkill3 && _mainTarget->getGP() < 5000 && !_isBati)
			{

				if (abs(sp.x) > 64 || abs(sp.y) > 16)
				{
					moveDirection = ccpNormalize(sp);
					this->walk(moveDirection);
					return;
				}
				else
				{

					this->changeSide(sp);
					this->attack(SKILL3);
				}
				return;
			}
			else if (_isCanSkill2 && _mainTarget->getGP() < 5000 && !_isBati)
			{
				this->changeSide(sp);
				this->attack(SKILL2);
				return;
			}
			else if (_isCanOugis1 && !_isControled && _mainTarget->getGP() < 5000 && !_isBati)
			{

				this->changeSide(sp);
				this->attack(OUGIS1);
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

		if (_actionState == ACTION_STATE_IDLE || _actionState == ACTION_STATE_WALK || _actionState == ACTION_STATE_ATTACK)
		{
			if (strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0 && _isCanSkill1 && !_isBati)
			{
				this->changeSide(sp);
				this->attack(SKILL1);
			}
			else if (_isCanSkill2 && _mainTarget->getGP() < 5000 && !_isBati && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0 && isBaseDanger)
			{
				this->changeSide(sp);
				this->attack(SKILL2);
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
		this->stepOn();
	}
}
