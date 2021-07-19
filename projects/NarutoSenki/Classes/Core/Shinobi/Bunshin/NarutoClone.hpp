#pragma once
#include "Hero.hpp"

class NarutoClone : public Hero
{
	void perform()
	{
		if (!findEnemy(ROLE_FLOG, 0))
		{
			if (!findEnemy("Hero", 0))
			{
				if (!findEnemy("Tower", 0))
				{
					_mainTarget = nullptr;
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
				if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::NATTACK)
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
