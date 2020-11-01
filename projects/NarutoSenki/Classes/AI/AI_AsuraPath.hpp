#pragma once
#include "Characters.h"

class AI_AsuraPath : public Hero
{
	void perform();
};

void AI_AsuraPath::perform()
{

	if (!this->findEnemy("Hero", 0))
	{
		if (!this->findEnemy("Flog", 0))
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
				if (this->getActionState() == ACTION_STATE_IDLE || this->getActionState() == ACTION_STATE_WALK || this->getActionState() == ACTION_STATE_ATTACK)
				{
					this->changeSide(sp);
					this->attack(NAttack);
				}
			}
			return;
		}
		else
		{

			if (abs(sp.x) > 256 || abs(sp.y) > 32)
			{

				moveDirection = ccpNormalize(sp);
				this->walk(moveDirection);
				return;
			}
			else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_isCanSkill1)
			{

				moveDirection = ccpNormalize(sp);
				this->walk(moveDirection);
				return;
			}
			else if (this->getActionState() == ACTION_STATE_IDLE || this->getActionState() == ACTION_STATE_WALK || this->getActionState() == ACTION_STATE_ATTACK)
			{
				if (_isCanSkill1)
				{

					if (abs(sp.x) < 64 && this->getPositionX() > 64 &&
						this->getPositionX() < (95 * 32 - 64))
					{
						if (this->stepBack())
							return;
					}
				}

				if (_isCanSkill1)
				{
					this->changeSide(sp);

					this->attack(SKILL1);
					this->scheduleOnce(schedule_selector(Hero::enableSkill1), _sattackcoldDown1);
				}
				else
				{

					this->changeSide(sp);
					this->attack(NAttack);
				}
			}
			return;
		}
	}

	this->stepOn();
}
