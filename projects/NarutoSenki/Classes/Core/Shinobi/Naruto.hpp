#pragma once
#include "Hero.hpp"
#include "Shinobi/Bunshin/NarutoClone.hpp"
#include "Shinobi/Bunshin/SageNarutoClone.hpp"
#include "Shinobi/Bunshin/RikudoNarutoClone.hpp"
#include "Kuchiyose/Kurama.hpp"

class Naruto : public Hero
{
	void setID(const string &name, Role role, Group group) override
	{
		Hero::setID(name, role, group);

		match_char_exp3(HeroEnum::Naruto, setAIHandler(Naruto::perform),
						HeroEnum::SageNaruto, setAIHandler(Naruto::perform_SageNaruto),
						HeroEnum::RikudoNaruto, setAIHandler(Naruto::perform_RikudoNaruto));
	}

	void changeAction() override
	{
		match_char_exp3(HeroEnum::Naruto, changeAction_Naruto(),
						HeroEnum::SageNaruto, changeAction_SageNaruto(),
						HeroEnum::RikudoNaruto, changeAction_RikudoNaruto());
	}

	void resumeAction(float dt) override
	{
		match_char_exp3(HeroEnum::Naruto, resumeAction_Naruto(dt),
						HeroEnum::SageNaruto, resumeAction_SageNaruto(dt),
						HeroEnum::RikudoNaruto, resumeAction_RikudoNaruto(dt));
	}

	Hero *createClone(int cloneTime) override
	{
		match_char_exp3(HeroEnum::Naruto, return createClone_Naruto(cloneTime),
						HeroEnum::SageNaruto, return createClone_SageNaruto(cloneTime),
						HeroEnum::RikudoNaruto, return createClone_RikudoNaruto(cloneTime));
		return nullptr;
	}

	// Naruto

	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryBuyGear(GearType::Gear03, GearType::Gear07, GearType::Gear02);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanSkill2 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isArmored && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 32 && (_isCanSkill1 || _isCanOugis1 || _isCanSkill3))
					{
						stepBack();
						return;
					}

					if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_isArmored)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanGear03)
					{
						useGear(GearType::Gear03);
					}
					else if (_isCanSkill3 && !_isArmored && _mainTarget->getDEF() < 5000)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else if (_isCanSkill1 && !_isArmored && _mainTarget->getDEF() < 5000)
					{
						changeSide(sp);
						attack(SKILL1);
					}
					else
					{
						changeSide(sp);
						attack(NAttack);
					}

					return;
				}
			}
		}

		_mainTarget = nullptr;
		if (notFindFlogHalf())
			findTowerHalf();

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
				if (_isCanSkill2 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else
				{
					changeSide(sp);
					attack(NAttack);
				}
			}

			return;
		}

		checkHealingState();
	}

	inline void changeAction_Naruto()
	{
		setActionTo<ActionFlag::Idle, ActionFlag::Spc01>();
		setActionTo<ActionFlag::Walk, ActionFlag::Spc02>();
		setActionTo<ActionFlag::NAttack, ActionFlag::Spc03>();
		setActionTo<ActionFlag::Knockdown, ActionFlag::Spc04>();

		setWalkSpeed(320);
		_originSpeed = 320;

		_isOnlySkillLocked = true;

		setTempAttackValue1(getNAttackValue());
		setNAttackValue(960);

		_nAttackRangeX = _spcAttackRangeX3;
		_nAttackRangeY = _spcAttackRangeY3;
		_originNAttackType = _nAttackType;
		_nAttackType = _spcAttackType3;

		_defense += 5000;
		_isArmored = true;

		lockOugisButtons();
	}

	inline void resumeAction_Naruto(float dt)
	{
		setActionTo<ActionFlag::Idle, ActionFlag::Idle>();
		setActionTo<ActionFlag::Walk, ActionFlag::Walk>();
		setActionTo<ActionFlag::NAttack, ActionFlag::NAttack>();

		_isOnlySkillLocked = false;

		unlockOugisButtons();

		setWalkSpeed(224);
		_originSpeed = 224;
		if (hasTempAttackValue1())
		{
			setNAttackValue(getTempAttackValue1());
			setTempAttackValue1(0);
		}
		hasArmorBroken = false;

		_nAttackRangeX = 16;
		_nAttackRangeY = 48;
		_nAttackType = _originNAttackType;
		resetDefenseValue(5000);
		_isArmored = false;

		if (_state != State::DEAD)
		{
			_state = State::WALK;
			knockdown();
		}

		setActionTo<ActionFlag::Knockdown, ActionFlag::Knockdown>();
		CharacterBase::resumeAction(dt);
	}

	inline Hero *createClone_Naruto(int cloneTime)
	{
		auto clone = createCloneHero<NarutoClone>(getName());
		return clone;
	}

	// Naruto Sage

	void perform_SageNaruto()
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryBuyGear(GearType::Gear03, GearType::Gear07, GearType::Gear02);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanSkill2 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (_isCanSkill3 && !_isArmored && _mainTarget->getDEF() < 5000)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isArmored && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 32 && _isCanSkill1)
					{
						stepBack();
						return;
					}
					if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_isArmored)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanGear03)
					{
						useGear(GearType::Gear03);
					}
					else if (_isCanSkill1 && !_isArmored && _mainTarget->getDEF() < 5000)
					{
						changeSide(sp);
						attack(SKILL1);
					}
					else
					{
						changeSide(sp);
						attack(NAttack);
					}

					return;
				}
			}
		}
		_mainTarget = nullptr;
		if (notFindFlogHalf())
			findTowerHalf();

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
				if (_isCanSkill2 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else
				{
					changeSide(sp);
					attack(NAttack);
				}
			}

			return;
		}

		checkHealingState();
	}

	inline void changeAction_SageNaruto()
	{
		_defense += 5000;
		_isArmored = true;
		hasArmorBroken = true;
		_isOnlySkillLocked = true;

		setActionTo<ActionFlag::Idle, ActionFlag::Spc04>();
		setActionTo<ActionFlag::Walk, ActionFlag::Spc02>();
		setActionTo<ActionFlag::NAttack, ActionFlag::Spc03>();

		setWalkSpeed(320);
		_originSpeed = 320;

		lockOugisButtons();
	}

	inline void resumeAction_SageNaruto(float dt)
	{
		setActionTo<ActionFlag::Idle, ActionFlag::Idle>();
		setActionTo<ActionFlag::Walk, ActionFlag::Walk>();
		setActionTo<ActionFlag::NAttack, ActionFlag::NAttack>();

		_isOnlySkillLocked = false;

		unlockOugisButtons();

		setWalkSpeed(224);
		_originSpeed = 224;

		resetDefenseValue(5000);
		_isArmored = false;
		hasArmorBroken = false;

		if (_state != State::DEAD)
		{
			_state = State::WALK;
			setActionTo<ActionFlag::Knockdown, ActionFlag::Spc05>();
			knockdown();
			setActionTo<ActionFlag::Knockdown, ActionFlag::Knockdown>();
		}
		else if (hasTempAttackValue1())
		{
			setNAttackValue(getTempAttackValue1());
			setTempAttackValue1(0);
		}
		CharacterBase::resumeAction(dt);
	}

	inline Hero *createClone_SageNaruto(int cloneTime)
	{
		auto clone = createCloneHero<SageNarutoClone>(getName());
		clone->setActionTo<ActionFlag::Skill01, ActionFlag::Spc01>();
		clone->setSAttackValue1(getSAttackValue1());
		clone->setSAttackType1(_spcAttackType1);
		clone->_sAttackCD1 = _spcAttackCD1;
		return clone;
	}

	// Naruto Rikutou

	void perform_RikudoNaruto()
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryBuyGear(GearType::Gear03, GearType::Gear07, GearType::Gear02);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanSkill2 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (_isCanSkill3 && !_isArmored && _mainTarget->getDEF() < 5000)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (_isCanSkill1 && !_isArmored && _mainTarget->getDEF() < 5000)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (_isCanGear03)
				{
					useGear(GearType::Gear03);
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isArmored && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if (abs(sp.x) > 32 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_isArmored)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else
					{
						changeSide(sp);
						attack(NAttack);
					}

					return;
				}
			}
		}
		_mainTarget = nullptr;
		if (notFindFlogHalf())
			findTowerHalf();

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
				if (_isCanSkill1 && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanSkill2 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else
				{
					changeSide(sp);
					attack(NAttack);
				}
			}

			return;
		}

		checkHealingState();
	}

	inline void changeAction_RikudoNaruto()
	{
		_defense += 5000;
		_isArmored = true;
		hasArmorBroken = true;
		_isOnlySkillLocked = true;

		setActionTo<ActionFlag::Idle, ActionFlag::Spc04>();
		setActionTo<ActionFlag::Walk, ActionFlag::Spc02>();
		setActionTo<ActionFlag::NAttack, ActionFlag::Spc03>();

		if (getName() == HeroEnum::RikudoNaruto)
		{
			setTempAttackValue1(getNAttackValue());
			setNAttackValue(560);
		}

		setWalkSpeed(320);
		_originSpeed = 320;

		lockOugisButtons();
	}

	inline void resumeAction_RikudoNaruto(float dt)
	{
		setActionTo<ActionFlag::Idle, ActionFlag::Idle>();
		setActionTo<ActionFlag::Walk, ActionFlag::Walk>();
		setActionTo<ActionFlag::NAttack, ActionFlag::NAttack>();

		_isOnlySkillLocked = false;

		unlockOugisButtons();

		setWalkSpeed(224);
		_originSpeed = 224;

		resetDefenseValue(5000);
		_isArmored = false;
		hasArmorBroken = false;

		if (_state != State::DEAD)
		{
			_state = State::WALK;
			idle();
		}

		if (hasTempAttackValue1())
		{
			setNAttackValue(getTempAttackValue1());
			setTempAttackValue1(0);
		}
		CharacterBase::resumeAction(dt);
	}

	inline Hero *createClone_RikudoNaruto(int cloneTime)
	{
		auto clone = createCloneHero<Kurama>(SummonEnum::Kurama);
		clone->setDEF(5000);
		clone->_isArmored = true;
		clone->setWalkSpeed(320);
		clone->_originSpeed = 320;
		clone->hasArmorBroken = true;
		return clone;
	}

private:
	string _originNAttackType;
};
