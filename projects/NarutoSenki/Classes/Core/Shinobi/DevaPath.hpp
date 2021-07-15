#pragma once
#include "Hero.hpp"
#include "Shinobi/AnimalPath.hpp"
#include "Shinobi/AsuraPath.hpp"

class DevaPath : public Hero
{
	void perform()
	{
		if (!findEnemy("Hero", 0))
		{
			if (!findEnemy("Flog", 0))
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
				strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
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
				else if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::NATTACK)
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
						scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sattackcoldDown1);
					}
					else if (_isCanSkill2 && !isHaveKuilei2)
					{

						changeSide(sp);
						attack(SKILL2);
						scheduleOnce(schedule_selector(CharacterBase::enableSkill2), _sattackcoldDown2);
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

	Hero *createClone(unsigned int cloneTime)
	{
		Hero *clone = nullptr;
		if (!_monsterArray)
		{
			_monsterArray = CCArray::create();
			_monsterArray->retain();
		}
		if (cloneTime == 0)
		{
			clone = create<AnimalPath>(CCString::create("AnimalPath"), CCString::create(ROLE_SUMMON), getGroup());
		}
		else
		{
			clone = create<AsuraPath>(CCString::create("AsuraPath"), CCString::create(ROLE_SUMMON), getGroup());
		}
		_monsterArray->addObject(clone);
		clone->_isArmored = true;
		return clone;
	}
};
