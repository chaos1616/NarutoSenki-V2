#pragma once
#include "Characters.h"

class AI_Karasu : public Hero
{
	void perform();
};

void AI_Karasu::perform()
{

	if (!this->findEnemy("Hero", winSize.width / 2 - 32, true))
	{
		if (!this->findEnemy("Flog", winSize.width / 2 - 32, true))
		{
			this->_mainTarget = NULL;
		}
	}

	if (_mainTarget)
	{
		CCPoint moveDirection;
		if (abs(ccpSub(_master->getPosition(), this->getPosition()).x) > winSize.width / 2 - 48)
		{
			if (this->getActionState() == ACTION_STATE_IDLE || this->getActionState() == ACTION_STATE_WALK || this->getActionState() == ACTION_STATE_ATTACK)
			{
				moveDirection = ccpNormalize(ccpSub(_master->getPosition(), this->getPosition()));
				this->walk(moveDirection);
				return;
			}
		}
		CCPoint sp;
		if (_mainTarget->_originY)
		{
			sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), this->getPosition());
		}
		else
		{
			sp = ccpSub(_mainTarget->getPosition(), this->getPosition());
		}

		if (strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
		{

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				if (this->_master->getActionState() == ACTION_STATE_IDLE ||
					this->_master->getActionState() == ACTION_STATE_WALK ||
					this->_master->getActionState() == ACTION_STATE_ATTACK ||
					this->_master->getActionState() == ACTION_STATE_SATTACK ||
					this->_master->getActionState() == ACTION_STATE_OATTACK ||
					this->_master->getActionState() == ACTION_STATE_O2ATTACK)
				{

					moveDirection = ccpNormalize(sp);
					this->walk(moveDirection);
					return;
				}
			}
			else
			{
				if (this->getActionState() == ACTION_STATE_IDLE ||
					this->getActionState() == ACTION_STATE_WALK ||
					this->getActionState() == ACTION_STATE_ATTACK)
				{
					this->changeSide(sp);
					this->attack(NAttack);
				}
			}
			return;
		}
		else
		{

			if (abs(sp.x) > 32 || abs(sp.y) > 16)
			{
				if (this->_master->getActionState() == ACTION_STATE_IDLE ||
					this->_master->getActionState() == ACTION_STATE_WALK ||
					this->_master->getActionState() == ACTION_STATE_ATTACK ||
					this->_master->getActionState() == ACTION_STATE_SATTACK ||
					this->_master->getActionState() == ACTION_STATE_OATTACK ||
					this->_master->getActionState() == ACTION_STATE_O2ATTACK)
				{
					moveDirection = ccpNormalize(sp);
					this->walk(moveDirection);
					return;
				}
			}
			else if (this->getActionState() == ACTION_STATE_IDLE ||
					 this->getActionState() == ACTION_STATE_WALK ||
					 this->getActionState() == ACTION_STATE_ATTACK)
			{

				if (_master->getActionState() == ACTION_STATE_IDLE ||
					_master->getActionState() == ACTION_STATE_WALK ||
					_master->getActionState() == ACTION_STATE_ATTACK)
				{

					if (_master->_isCanSkill2 && _mainTarget->getGP() < 5000 && (_master->_isControled || _master->_isAI == true))
					{

						this->changeSide(sp);

						if (strcmp(_master->getRole()->getCString(), "Player") != 0)
						{
							_master->attack(SKILL2);
						}
						else if (strcmp(_master->getRole()->getCString(), "Player") == 0)
						{
							_master->attack(SKILL2);
						}
					}
					else
					{

						this->changeSide(sp);
						this->attack(NAttack);
					}
				}
			}
			return;
		}
	}

	if (abs(ccpSub(_master->getPosition(), this->getPosition()).x) > winSize.width / 2 - 64)
	{
		CCPoint moveDirection = ccpNormalize(ccpSub(_master->getPosition(), this->getPosition()));
		this->walk(moveDirection);
		return;
	}
	else
	{
		if (
			this->_master->getActionState() == ACTION_STATE_WALK ||
			this->_master->getActionState() == ACTION_STATE_ATTACK ||
			this->_master->getActionState() == ACTION_STATE_SATTACK ||
			this->_master->getActionState() == ACTION_STATE_OATTACK)
		{
			this->stepOn();
		}
		else
		{
			if (this->_actionState == ACTION_STATE_WALK ||
				this->_actionState == ACTION_STATE_ATTACK)
			{
				this->idle();
			}
		}
	}
}
