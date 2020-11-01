#pragma once
#include "Characters.h"

class AI_Parents : public Hero
{
	void perform();
};

void AI_Parents::perform()
{

	if (!this->findEnemy("Hero", winSize.width / 2 - 32, true))
	{

		if (!this->findEnemy("Flog", 48, true))
		{
			if (!this->findEnemy("Tower", 48, true))
			{
				this->_mainTarget = NULL;
			}
		}
	}

	CCPoint moveDirection;

	if (abs(ccpSub(_master->getPosition(), this->getPosition()).x) > 9 && !_skillChangeBuffValue)
	{
		if (this->getActionState() == ACTION_STATE_IDLE || this->getActionState() == ACTION_STATE_WALK || this->getActionState() == ACTION_STATE_ATTACK)
		{
			moveDirection = ccpNormalize(ccpSub(_master->getPosition(), this->getPosition()));
			this->walk(moveDirection);
			return;
		}
	}
	if (_mainTarget)
	{

		CCPoint sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY()),
							ccp(this->getPositionX(), _originY ? _originY : this->getPositionY()));

		if (strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0 || strcmp(_mainTarget->getRole()->getCString(), "Tower") == 0)
		{

			if (abs(sp.x) > 48 || abs(sp.y) > 32)
			{
			}
			else
			{
				if ((this->getActionState() == ACTION_STATE_IDLE || this->getActionState() == ACTION_STATE_WALK || this->getActionState() == ACTION_STATE_ATTACK) && !_skillChangeBuffValue)
				{
					this->changeSide(sp);
					this->attack(NAttack);
				}
			}
			return;
		}
		else
		{
			if (this->getActionState() == ACTION_STATE_IDLE || this->getActionState() == ACTION_STATE_WALK || this->getActionState() == ACTION_STATE_ATTACK)
			{
				if (_master->getActionState() == ACTION_STATE_IDLE ||
					_master->getActionState() == ACTION_STATE_WALK ||
					_master->getActionState() == ACTION_STATE_ATTACK)
				{

					if (_master->_isCanSkill3 && _mainTarget->getGP() < 5000 && (_master->_isControled || _master->_isAI == true) && !_skillChangeBuffValue)
					{

						this->changeSide(sp);

						_master->attack(SKILL3);
					}
					else if (abs(sp.x) > 48 || abs(sp.y) > 32)
					{
						if (_skillChangeBuffValue && this->getActionState() != ACTION_STATE_ATTACK)
						{
							moveDirection = ccpNormalize(sp);
							this->walk(moveDirection);
							return;
						}
					}
					else
					{

						if (_master->_isCanSkill2 && _mainTarget->getGP() < 5000 && (_master->_isControled || _master->_isAI == true) && !_skillChangeBuffValue)
						{

							this->changeSide(sp);
							_master->attack(SKILL2);
						}
						else
						{

							this->changeSide(sp);
							this->attack(NAttack);
						}
					}
				}
			}

			return;
		}
	}

	if (abs(ccpSub(_master->getPosition(), this->getPosition()).x) > 9)
	{
		if (this->getActionState() == ACTION_STATE_IDLE || this->getActionState() == ACTION_STATE_WALK)
		{
			moveDirection = ccpNormalize(ccpSub(_master->getPosition(), this->getPosition()));
			this->walk(moveDirection);
			return;
		}
	}

	if (this->_actionState == ACTION_STATE_WALK)
	{
		this->idle();
	}
}
