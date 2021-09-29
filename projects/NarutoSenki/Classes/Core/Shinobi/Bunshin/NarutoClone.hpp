#pragma once
#include "Hero.hpp"

class NarutoClone : public Hero
{
	void perform()
	{
		if (notFindFlog(0))
		{
			if (notFindHero(0))
			{
				if (notFindTower(0))
				{
					_mainTarget = nullptr;
				}
			}
		}

		if (_mainTarget)
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
			}
			else
			{
				if (isFreeActionState())
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
