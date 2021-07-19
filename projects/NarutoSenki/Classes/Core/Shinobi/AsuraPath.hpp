#pragma once
#include "Hero.hpp"

class AsuraPath : public Hero
{
	void perform()
	{
		if (!findEnemy("Hero", 0))
		{
			if (!findEnemy(ROLE_FLOG, 0))
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
			CCPoint sp = ccpSub(_mainTarget->getPosition(), getPosition());

			if (strcmp(_mainTarget->getRole()->getCString(), "Tower") == 0 ||
				strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) == 0)
			{
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
			else
			{
				if (abs(sp.x) > 256 || abs(sp.y) > 32)
				{
					moveDirection = ccpNormalize(sp);
					walk(moveDirection);
					return;
				}
				else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_isCanSkill1)
				{
					moveDirection = ccpNormalize(sp);
					walk(moveDirection);
					return;
				}
				else if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::NATTACK)
				{
					if (_isCanSkill1)
					{
						if (abs(sp.x) < 64 && getPositionX() > 64 &&
							getPositionX() < (95 * 32 - 64))
						{
							if (stepBack())
								return;
						}
					}

					if (_isCanSkill1)
					{
						changeSide(sp);

						attack(SKILL1);
						scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sattackcoldDown1);
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
