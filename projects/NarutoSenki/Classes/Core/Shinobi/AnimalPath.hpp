#pragma once
#include "Hero.hpp"

class AnimalPath : public Hero
{
	void perform()
	{

		if (!findEnemy("Flog", 0))
		{
			if (!findEnemy("Tower", 0))
			{
				if (!findEnemy("Hero", 0))
				{
					_mainTarget = nullptr;
				}
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

						if (_isCanSkill1 && strcmp(_mainTarget->getRole()->getCString(), "Tower") != 0)
						{

							attack(SKILL1);
							scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sattackcoldDown1);
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
			else
			{

				if (abs(sp.x) > 256 || abs(sp.y) > 32)
				{

					moveDirection = ccpNormalize(sp);
					walk(moveDirection);
					return;
				}
				else if (abs(sp.x) > 32 || abs(sp.y) > 32)
				{

					moveDirection = ccpNormalize(sp);
					walk(moveDirection);
					return;
				}
				else if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::ATTACK)
				{

					if (_isCanSkill1)
					{

						attack(SKILL1);
						scheduleOnce(schedule_selector(CharacterBase::enableSkill1), 10.0f);
					}
					else
					{
						changeSide(sp);
						attack(NAttack);
					}
				}
				return;
			}
		}

		stepOn();
	}
};
