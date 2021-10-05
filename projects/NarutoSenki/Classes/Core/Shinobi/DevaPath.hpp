#pragma once
#include "Hero.hpp"
#include "Shinobi/AnimalPath.hpp"
#include "Shinobi/AsuraPath.hpp"

class DevaPath : public Hero
{
	void perform() override
	{
		if (notFindHero(0))
		{
			if (notFindFlog(0))
			{
				if (notFindTower(0))
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
				else if (isFreeActionState())
				{
					bool isHaveKuilei1 = false;
					bool isHaveKuilei2 = false;

					if (hasMonsterArrayAny())
					{
						CCObject *pObject;
						CCARRAY_FOREACH(getMonsterArray(), pObject)
						{
							auto mo = (Monster *)pObject;
							if (mo->isCharacter("AnimalPath"))
							{
								isHaveKuilei1 = true;
							}

							if (mo->isCharacter("AsuraPath"))
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

	Hero *createClone(int cloneTime) override
	{
		Hero *clone = nullptr;
		if (!_monsterArray)
		{
			_monsterArray = CCArray::create();
			_monsterArray->retain();
		}

		if (cloneTime == 0)
		{
			clone = create<AnimalPath>(CCString::create("AnimalPath"), CCString::create(kRoleSummon), getGroup());
		}
		else
		{
			clone = create<AsuraPath>(CCString::create("AsuraPath"), CCString::create(kRoleSummon), getGroup());
		}
		_monsterArray->addObject(clone);
		clone->_isArmored = true;
		return clone;
	}
};
