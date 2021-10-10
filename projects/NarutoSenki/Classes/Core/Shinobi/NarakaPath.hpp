#pragma once
#include "Hero.hpp"
#include "Shinobi/AnimalPath.hpp"
#include "Shinobi/AsuraPath.hpp"
#include "Shinobi/HumanPath.hpp"
#include "Shinobi/PertaPath.hpp"

class NarakaPath : public Hero
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
					bool isHaveKugutsu1 = false;
					bool isHaveKugutsu2 = false;
					bool isHaveKugutsu3 = false;
					bool isHaveKugutsu4 = false;

					if (hasMonsterArrayAny())
					{
						CCObject *pObject;
						CCARRAY_FOREACH(getMonsterArray(), pObject)
						{
							auto mo = (Monster *)pObject;
							if (mo->isCharacter("AnimalPath"))
							{
								isHaveKugutsu1 = true;
							}
							else if (mo->isCharacter("AsuraPath"))
							{
								isHaveKugutsu2 = true;
							}
							else if (mo->isCharacter("HumanPath"))
							{
								isHaveKugutsu3 = true;
							}

							else if (mo->isCharacter("PertaPath"))
							{
								isHaveKugutsu4 = true;
							}
						}
					}

					if (_isCanSkill1 && !isHaveKugutsu1)
					{
						attack(SKILL1);
						scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sattackcoldDown1);
					}
					else if (_isCanSkill2 && !isHaveKugutsu2)
					{
						changeSide(sp);
						attack(SKILL2);
						scheduleOnce(schedule_selector(CharacterBase::enableSkill2), _sattackcoldDown2);
					}
					else if (_isCanSkill3 && !isHaveKugutsu4)
					{

						this->changeSide(sp);
						this->attack(SKILL3);
						this->scheduleOnce(schedule_selector(CharacterBase::enableSkill3), _sattackcoldDown3);
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

		// TODO: How to balance the hero
		if (cloneTime == 0)
			clone = create<AnimalPath>(CCString::create("AnimalPath"), CCString::create(kRoleSummon), getGroup());
		else if (cloneTime == -1)
			clone = create<AsuraPath>(CCString::create("AsuraPath"), CCString::create(kRoleSummon), getGroup());
		else if (cloneTime == -2)
			clone = create<PertaPath>(CCString::create("PertaPath"), CCString::create(kRoleSummon), getGroup());
		else if (cloneTime == -3)
			clone = create<HumanPath>(CCString::create("HumanPath"), CCString::create(kRoleSummon), getGroup());

		_monsterArray->addObject(clone);
		clone->_isArmored = true;
		return clone;
	}
};
