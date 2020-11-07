#pragma once
#include "Characters.h"

class AI_DevaPath : public Hero
{
	void perform()
	{

		if (!findEnemy("Hero", 0))
		{
			if (!findEnemy("Flog", 0))
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
						changeSide(sp);
						attack(NAttack);
					}
				}
				return;
			}
			else
			{

				if (abs(sp.x) > 256 || abs(sp.y) > 16)
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

					bool isHaveKuilei1 = false;
					bool isHaveKuilei2 = false;

					if (getMonsterArray() && getMonsterArray()->count() > 0)
					{
						CCObject *pObject;
						CCARRAY_FOREACH(getMonsterArray(), pObject)
						{
							Monster *mo = (Monster *)pObject;
							if (strcmp(mo->getCharacter()->getCString(), "AnimalPath") == 0)
							{
								isHaveKuilei1 = true;
							}

							if (strcmp(mo->getCharacter()->getCString(), "AsuraPath") == 0)
							{
								isHaveKuilei2 = true;
							}
						}
					}

					if (_isCanSkill1 && !isHaveKuilei1)
					{

						attack(SKILL1);
						scheduleOnce(schedule_selector(Hero::enableSkill1), _sattackcoldDown1);
					}
					else if (_isCanSkill2 && !isHaveKuilei2)
					{

						changeSide(sp);
						attack(SKILL2);
						scheduleOnce(schedule_selector(Hero::enableSkill2), _sattackcoldDown2);
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
