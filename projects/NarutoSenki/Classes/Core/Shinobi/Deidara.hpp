#pragma once
#include "Hero.hpp"
#include "Kuchiyose/Centipede.hpp"

class Deidara : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryBuyGear(GearType::Gear00, GearType::Gear01, GearType::Gear05);

		if (needBackToTowerToRestoreHP())
			return;

		if (_mainTarget && (battleCondiction >= 0 || _isCanSkill3 || _isCanOugis1 || _isArmored))
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getDEF() < 5000 && !_isArmored)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 16)
					{
						if (_isCanGear00)
							useGear(GearType::Gear00);

						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else
					{
						changeSide(sp);
						attack(OUGIS2);
					}
				}
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getDEF() < 5000 && !_isArmored)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 16)
					{
						if (_isCanGear00)
							useGear(GearType::Gear00);

						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (_isCanSkill2 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isControlled)
				{
					if (abs(sp.x) < 160)
					{
						stepBack2();
						return;
					}
					else
					{
						if (_skillChangeBuffValue)
						{
							if (!_isArmored)
							{
								changeSide(sp);
								attack(NAttack);
							}
						}
						idle();
						return;
					}
				}
				else if (_isCanSkill1 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if ((abs(sp.x) > 8 || abs(sp.y) > 8) && _isArmored)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_isCanSkill1 && !_skillChangeBuffValue)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					if (!_isArmored)
					{
						changeSide(sp);
						attack(NAttack);
					}

					return;
				}
			}
		}

		if (battleCondiction >= 0)
		{
			_mainTarget = nullptr;
			if (notFindFlogHalf())
			{
				findTowerHalf();
			}
		}
		else
		{
			_mainTarget = nullptr;
			findTowerHalf();
		}

		if (_mainTarget)
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = sp.getNormalized();
				walk(moveDirection);
				return;
			}

			if (isFreeState())
			{
				if (_mainTarget->isTower() &&
					_isCanOugis2 &&
					!_isControlled && getGameLayer()->_isOugis2Game && !_isArmored && isBaseDanger)
				{
					changeSide(sp);
					attack(OUGIS2);
				}
				else if (_isCanSkill1 && !_isArmored && _mainTarget->isTower())
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanSkill2 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (!_isArmored)
				{
					changeSide(sp);
					attack(NAttack);
				}
			}

			return;
		}

		checkHealingState();
	}

	void changeAction() override
	{
		if (_skillChangeBuffValue == 17)
		{
			setActionTo<ActionFlag::NAttack, ActionFlag::Spc01>();
		}
		else if (_skillChangeBuffValue == 18)
		{
			_isAllAttackLocked = true;
			_isArmored = true;

			setWalkSpeed(320);
			_originSpeed = 320;

			lockOugisButtons();

			setActionTo<ActionFlag::Idle, ActionFlag::Spc02>();
			setActionTo<ActionFlag::Walk, ActionFlag::Spc03>();

			if (_hpBar)
			{
				_hpBar->setPositionY(120);
			}
			schedule(schedule_selector(Deidara::setMonPer), 0.5f);
		}
	}

	void resumeAction(float dt) override
	{
		if (_skillChangeBuffValue == 17)
		{
			setActionTo<ActionFlag::NAttack, ActionFlag::NAttack>();
		}
		else if (_skillChangeBuffValue == 18)
		{
			_isArmored = false;
			_isAllAttackLocked = false;
			setWalkSpeed(224);
			_originSpeed = 224;

			unlockOugisButtons();

			setActionTo<ActionFlag::Idle, ActionFlag::Idle>();
			setActionTo<ActionFlag::Walk, ActionFlag::Walk>();

			if (_state != State::DEAD)
			{
				_state = State::WALK;
				idle();
			}
			if (_hpBar)
			{
				_hpBar->setPositionY(getHPBarHeight());
			}

			unschedule(schedule_selector(Deidara::setMonPer));
		}
		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		if (_skillChangeBuffValue == 0)
			return;

		unschedule(schedule_selector(Deidara::resumeAction));

		if (_skillChangeBuffValue == 17)
		{
			setActionTo<ActionFlag::NAttack, ActionFlag::NAttack>();
		}
		else if (_skillChangeBuffValue == 18)
		{
			_isArmored = false;
			_isAllAttackLocked = false;
			setWalkSpeed(224);
			_originSpeed = 224;

			unlockOugisButtons();

			setActionTo<ActionFlag::Idle, ActionFlag::Idle>();
			setActionTo<ActionFlag::Walk, ActionFlag::Walk>();

			if (_hpBar)
			{
				_hpBar->setPositionY(getHPBarHeight());
			}
			unschedule(schedule_selector(Deidara::setMonPer));
		}

		_skillChangeBuffValue = 0;
	}

	Hero *createClone(int cloneTime) override
	{
		auto clone = createSummonHero<Centipede>(SummonEnum::Centipede);
		clone->_isArmored = true;
		return clone;
	}
};
