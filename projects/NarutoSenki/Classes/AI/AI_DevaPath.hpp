#pragma once
#include "Characters.h"

class AI_DevaPath : public Hero
{
	void perform();
};

void AI_DevaPath::perform()
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

			if (abs(sp.x) > 256 || abs(sp.y) > 16)
			{

				moveDirection = ccpNormalize(sp);
				this->walk(moveDirection);
				return;
			}
			else if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{

				moveDirection = ccpNormalize(sp);
				this->walk(moveDirection);
				return;
			}
			else if (this->getActionState() == ACTION_STATE_IDLE || this->getActionState() == ACTION_STATE_WALK || this->getActionState() == ACTION_STATE_ATTACK)
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

					this->attack(SKILL1);
					this->scheduleOnce(schedule_selector(Hero::enableSkill1), _sattackcoldDown1);
				}
				else if (_isCanSkill2 && !isHaveKuilei2)
				{

					this->changeSide(sp);
					this->attack(SKILL2);
					this->scheduleOnce(schedule_selector(Hero::enableSkill2), _sattackcoldDown2);
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
