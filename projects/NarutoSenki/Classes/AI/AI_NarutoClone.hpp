#pragma once
#include "Characters.h"

class AI_NarutoClone : public Hero
{
	void perform()
	{

		if (!findEnemy("Flog", 0))
		{
			if (!findEnemy("Hero", 0))
			{
				if (!findEnemy("Tower", 0))
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
			}
			else
			{
				if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::ATTACK)
				{
					changeSide(sp);
					attack(NAttack);
				}
			}
			return;
		}

		stepOn();
	}
};
