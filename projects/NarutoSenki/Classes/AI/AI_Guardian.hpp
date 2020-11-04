#pragma once
#include "Characters.h"

class AI_Guardian : public Hero
{
	void perform()
	{
		if (!this->findTargetEnemy("Hero", true))
		{
			if (!this->findTargetEnemy("Flog", true))
			{
				if (!this->findTargetEnemy("Flog", false))
				{
					if (!this->findTargetEnemy("Hero", false))
					{
						_mainTarget = NULL;
					}
				}
			}
		}

		if (_mainTarget)
		{
			CCPoint moveDirection;
			CCPoint sp = ccpSub(_mainTarget->getPosition(), this->getPosition());

			if (abs(sp.x) > 128 || abs(sp.y) > 16)
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
			else if (this->getActionState() == State::IDLE || this->getActionState() == State::WALK || this->getActionState() == State::ATTACK)
			{
				bool isTurn = false;

				CCObject *pObject;
				CCARRAY_FOREACH(_delegate->_TowerArray, pObject)
				{
					CharacterBase *target = (CharacterBase *)pObject;
					const char *gardTower;
					if (this->getDelegate()->zhenying > 0)
					{
						gardTower = "AkatsukiCenter";
					}
					else
					{
						gardTower = "KonohaCenter";
					}
					if (strcmp(target->getCharacter()->getCString(), gardTower) == 0 && target->getHpPercent() < 0.5f)
					{
						isTurn = true;
					}
				}

				if (_isCanSkill1 && !_skillChangeBuffValue && (this->getHpPercent() < 0.5f || isTurn))
				{
					this->changeSide(sp);
					this->attack(SKILL1);
					this->scheduleOnce(schedule_selector(Hero::enableSkill1), _sattackcoldDown1);
				}
				else if (_isCanSkill2 && _skillChangeBuffValue)
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
		else
		{
			CCPoint moveDirection;
			CCPoint sp = ccpSub(this->getSpawnPoint(), this->getPosition());
			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{

				moveDirection = ccpNormalize(sp);
				this->walk(moveDirection);
				return;
			}
			else
			{

				this->idle();
			}
		}
	}
};
