#pragma once
#include "Characters.h"

class AI_Centipede : public Hero
{
	void perform();
};

void AI_Centipede::perform()
{

	if (!this->findEnemy("Flog", 0))
	{
		if (!this->findEnemy("Tower", 0))
		{
			_mainTarget = NULL;
		}
	}

	if (_mainTarget)
	{
		CCPoint moveDirection;
		CCPoint sp = ccpSub(_mainTarget->getPosition(), this->getPosition());

		if (strcmp(_mainTarget->getRole()->getCString(), "Tower") == 0 ||
			strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
		{

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{

				moveDirection = ccpNormalize(sp);
				this->walk(moveDirection);
			}
			else
			{

				this->changeSide(sp);
				this->attack(NAttack);
			}

			return;
		}
	}

	this->stepOn();
}
