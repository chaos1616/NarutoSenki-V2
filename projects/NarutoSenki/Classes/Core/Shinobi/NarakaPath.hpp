#pragma once
#include "Hero.hpp"
#include "Shinobi/AnimalPath.hpp"
#include "Shinobi/AsuraPath.hpp"
#include "Shinobi/HumanPath.hpp"
#include "Shinobi/PertaPath.hpp"

class NarakaPath : public Hero
{
	enum class NarakaKugutsu
	{
		None,
		AnimalPath = 1 << 0,
		AsuraPath = 1 << 1,
		HumanPath = 1 << 2,
		PertaPath = 1 << 3,
	};

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
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTargetAndIgnoreOriginY();

			if (_mainTarget->isTower() ||
				_mainTarget->isFlog())
			{
				if (abs(sp.x) > 32 || abs(sp.y) > 32)
				{
					moveDirection = sp.getNormalized();
					walk(moveDirection);
				}
				else
				{
					if (isFreeState())
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
					moveDirection = sp.getNormalized();
					walk(moveDirection);
					return;
				}
				else if (abs(sp.x) > 32 || abs(sp.y) > 32)
				{
					moveDirection = sp.getNormalized();
					walk(moveDirection);
					return;
				}
				else if (isFreeState())
				{
					NarakaKugutsu flag;
					if (hasMonsterArrayAny())
					{
						for (auto mo : _monsterArray)
						{
							if (mo->getName() == HeroEnum::AnimalPath) flag |= NarakaKugutsu::AnimalPath;
							else if (mo->getName() == HeroEnum::AsuraPath) flag |= NarakaKugutsu::AsuraPath;
							else if (mo->getName() == HeroEnum::HumanPath) flag |= NarakaKugutsu::HumanPath;
							else if (mo->getName() == HeroEnum::PertaPath) flag |= NarakaKugutsu::PertaPath;
						}
					}

					if (_isCanSkill1 && notHasFlag(flag, NarakaKugutsu::AnimalPath))
					{
						attack(SKILL1);
						scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sAttackCD1);
					}
					else if (_isCanSkill2 && notHasFlag(flag, NarakaKugutsu::AsuraPath))
					{
						changeSide(sp);
						attack(SKILL2);
						scheduleOnce(schedule_selector(CharacterBase::enableSkill2), _sAttackCD2);
					}
					else if (_isCanSkill3 && notHasFlag(flag, NarakaKugutsu::PertaPath))
					{

						this->changeSide(sp);
						this->attack(SKILL3);
						this->scheduleOnce(schedule_selector(CharacterBase::enableSkill3), _sAttackCD3);
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

	void dealloc() override
	{
		_master->_skillChangeBuffValue = 0;
		_master->unlockSkill5Button();

		Hero::dealloc();
	}

	Hero *createClone(int cloneTime) override
	{
		Hero *clone = nullptr;

		// TODO: How to balance the hero
		if (cloneTime == 0) clone = createSummonHero<AnimalPath>(HeroEnum::AnimalPath);
		else if (cloneTime == -1) clone = createSummonHero<AsuraPath>(HeroEnum::AsuraPath);
		else if (cloneTime == -2) clone = createSummonHero<PertaPath>(HeroEnum::PertaPath);
		else if (cloneTime == -3) clone = createSummonHero<HumanPath>(HeroEnum::HumanPath);

		_monsterArray.push_back(clone);
		clone->_isArmored = true;
		return clone;
	}
};
