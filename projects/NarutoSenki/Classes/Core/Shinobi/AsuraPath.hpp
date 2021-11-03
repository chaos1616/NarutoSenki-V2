#pragma once
#include "Hero.hpp"

class AsuraPath : public Hero
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
				else if (isFreeActionState())
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
						scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sAttackCD1);
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

	// NOTE: AsuraPath will destroy Rocket after death
	// void dealloc() override
	// {
	// 	if (hasMonsterArrayAny())
	// 	{
	// 		vector<CharacterBase *> removeList;
	// 		auto &monsterArray = getMonsterArray();
	// 		for (auto mo : monsterArray)
	// 		{
	// 			if (mo->getName() == "Rocket")
	// 			{
	// 				mo->setMaster(nullptr);
	// 				removeList.push_back(mo);
	// 			}
	// 		}
	// 		for (auto mo : removeList)
	// 			std::erase(monsterArray, mo);
	// 	}

	// 	Hero::dealloc();
	// }
};
