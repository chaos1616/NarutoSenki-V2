#pragma once
#include "Characters.h"

class AI_NarutoClone : public Hero
{
	void perform();
};

void AI_NarutoClone::perform()
{

	if (!this->findEnemy("Flog", 0))
	{
		if (!this->findEnemy("Hero", 0))
		{
			if (!this->findEnemy("Tower", 0))
			{
				_mainTarget = NULL;
			}
		}
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
		}
		else
		{
			if (this->getActionState() == ACTION_STATE_IDLE || this->getActionState() == ACTION_STATE_WALK || this->getActionState() == ACTION_STATE_ATTACK)
			{
				this->changeSide(sp);
				this->attack(NAttack);
			}
		}
		return;
	}

	this->stepOn();
}
