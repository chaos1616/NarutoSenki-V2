#pragma once
#include "Characters.h"

class AI_Slug : public Hero
{
	void perform()
	{

		if (!findEnemy("Flog", 0))
		{
			if (!findEnemy("Tower", 0))
			{
				_mainTarget = NULL;
			}
		}

		if (_mainTarget)
		{
			CCPoint moveDirection;
			CCPoint sp = ccpSub(_mainTarget->getPosition(), getPosition());

			if (strcmp(_mainTarget->getRole()->getCString(), "Tower") == 0 ||
				strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
			{

				if (abs(sp.x) > 32 || abs(sp.y) > 32)
				{

					moveDirection = ccpNormalize(sp);
					walk(moveDirection);
				}
				else
				{
					if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::ATTACK)
					{

						if (_isCanSkill1)
						{

							attack(SKILL1);
							scheduleOnce(schedule_selector(Hero::enableSkill1), _sattackcoldDown1);
						}
						else if (_isCanSkill2)
						{

							attack(SKILL2);
							scheduleOnce(schedule_selector(Hero::enableSkill2), _sattackcoldDown2);
						}
						else
						{
							changeSide(sp);
							attack(NAttack);
						}
					}
				}

				return;
			}
		}

		stepOn();
	}
};
