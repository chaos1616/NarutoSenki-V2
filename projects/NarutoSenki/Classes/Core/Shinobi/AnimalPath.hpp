#pragma once
#include "Hero.hpp"

class AnimalPath : public Hero
{
	void perform()
	{
		if (notFindFlog(0))
		{
			if (notFindTower(0))
			{
				if (notFindHero(0))
				{
					_mainTarget = nullptr;
				}
			}
		}

		if (_mainTarget)
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTargetAndIgnoreOriginY();

			if (_mainTarget->isTower() ||
				_mainTarget->isFlog())
			{
				if (abs(sp.x) > 32 || abs(sp.y) > 32)
				{
					moveDirection = ccpNormalize(sp);
					walk(moveDirection);
				}
				else
				{
					if (isFreeActionState())
					{
						if (_isCanSkill1 && strcmp(_mainTarget->getRole()->getCString(), kRoleTower) != 0)
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
				else if (isFreeActionState())
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
