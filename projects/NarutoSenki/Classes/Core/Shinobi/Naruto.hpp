#pragma once
#include "Hero.hpp"

#include "Shinobi/Bunshin/NarutoClone.hpp"
#include "Shinobi/Bunshin/SageNarutoClone.hpp"
#include "Shinobi/Bunshin/RikudoNarutoClone.hpp"

#include "Kuchiyose/Kurama.hpp"

class Naruto : public Hero
{
#define kNaruto______ "Naruto"
#define kSageNaruto__ "SageNaruto"
#define kRikudoNaruto "RikudoNaruto"

	void setID(CCString *character, CCString *role, CCString *group) override
	{
		Hero::setID(character, role, group);

		match_char_exp3(kNaruto______, setAIHandler(Naruto::perform),
						kSageNaruto__, setAIHandler(Naruto::perform_SageNaruto),
						kRikudoNaruto, setAIHandler(Naruto::perform_RikudoNaruto));
	}

	void changeAction() override
	{
		match_char_exp3(kNaruto______, changeAction_Naruto(),
						kSageNaruto__, changeAction_SageNaruto(),
						kRikudoNaruto, changeAction_RikudoNaruto());
	}

	void resumeAction(float dt) override
	{
		match_char_exp3(kNaruto______, resumeAction_Naruto(dt),
						kSageNaruto__, resumeAction_SageNaruto(dt),
						kRikudoNaruto, resumeAction_RikudoNaruto(dt));
	}

	Hero *createClone(int cloneTime) override
	{
		match_char_exp3(kNaruto______, return createClone_Naruto(cloneTime),
						kSageNaruto__, return createClone_SageNaruto(cloneTime),
						kRikudoNaruto, return createClone_RikudoNaruto(cloneTime));
		return nullptr;
	}

	// Naruto

	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();
		if (getCoinValue() >= 500 && !_isControlled && getGameLayer()->_enableGear)
		{
			if (getGearArray()->count() == 0)
				setGear(gear03);
			else if (getGearArray()->count() == 1)
				setGear(gear07);
			else if (getGearArray()->count() == 2)
				setGear(gear02);
		}

		if (checkRetri())
		{
			if (_mainTarget != nullptr)
			{
				if (stepBack2())
					return;
			}
			else
			{
				if (stepBack())
					return;
			}
		}

		if (isBaseDanger && checkBase() && !_isControlled)
		{
			bool needBack = false;
			if (isAkatsukiGroup())
			{
				if (getPositionX() < 85 * 32)
					needBack = true;
			}
			else
			{
				if (getPositionX() > 11 * 32)
					needBack = true;
			}

			if (needBack)
			{
				if (stepBack2())
					return;
			}
		}

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (isFreeActionState())
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
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isArmored && !_isControlled)
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
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 32 && (_isCanSkill1 || _isCanOugis1 || _isCanSkill3))
					{
						stepBack();
						return;
					}

					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isArmored)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanGear03)
					{
						useGear(gear03);
					}
					else if (_isCanSkill3 && !_isArmored && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else if (_isCanSkill1 && !_isArmored && _mainTarget->getGP() < 5000)
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
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (isFreeActionState())
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

		if (_isHealling && getHpPercent() < 1)
		{
			if (isFreeActionState())
				idle();
		}
		else
		{
			stepOn();
		}
	}

	inline void changeAction_Naruto()
	{
		setIdleAction(createAnimation(skillSPC1Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));
		setKnockDownAction(createAnimation(skillSPC4Array, 10.0f, false, true));

		setWalkSpeed(320);
		_originSpeed = 320;

		_isOnlySkillLocked = true;

		settempAttackValue1(to_ccstring(getNAttackValue()));
		setnAttackValue(to_ccstring(960));

		_nattackRangeX = _spcattackRangeX3;
		_nattackRangeY = _spcattackRangeY3;
		_originNAttackType = _nattackType->m_sString;
		_nattackType = _spcattackType3;

		_gardValue += 5000;
		_isArmored = true;

		lockOugisButtons();
	}

	inline void resumeAction_Naruto(float dt)
	{
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));

		_isOnlySkillLocked = false;

		unlockOugisButtons();

		setWalkSpeed(224);
		_originSpeed = 224;
		if (hasTempAttackValue1())
		{
			setnAttackValue(to_ccstring(getTempAttackValue1()));
			settempAttackValue1(nullptr);
		}
		hasArmorBroken = false;

		_nattackRangeX = 16;
		_nattackRangeY = 48;
		_nattackType->m_sString = _originNAttackType;
		_gardValue -= 5000;
		_isArmored = false;

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			knockDown();
		}

		setKnockDownAction(createAnimation(knockDownArray, 10.0f, false, true));
		CharacterBase::resumeAction(dt);
	}

	inline Hero *createClone_Naruto(int cloneTime)
	{
		auto clone = create<NarutoClone>(getCharacter(), CCString::create(kRoleClone), getGroup());
		return clone;
	}

	// Naruto Sage

	void perform_SageNaruto()
	{
		_mainTarget = nullptr;
		findHeroHalf();
		if (getCoinValue() >= 500 && !_isControlled && getGameLayer()->_enableGear)
		{
			if (getGearArray()->count() == 0)
				setGear(gear03);
			else if (getGearArray()->count() == 1)
				setGear(gear07);
			else if (getGearArray()->count() == 2)
				setGear(gear02);
		}

		if (checkRetri())
		{
			if (_mainTarget != nullptr)
			{
				if (stepBack2())
					return;
			}
			else
			{
				if (stepBack())
					return;
			}
		}

		if (isBaseDanger && checkBase() && !_isControlled)
		{
			bool needBack = false;
			if (isAkatsukiGroup())
			{
				if (getPositionX() < 85 * 32)
					needBack = true;
			}
			else
			{
				if (getPositionX() > 11 * 32)
					needBack = true;
			}

			if (needBack)
			{
				if (stepBack2())
					return;
			}
		}

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (isFreeActionState())
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
				else if (_isCanSkill3 && !_isArmored && _mainTarget->getGP() < 5000)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isArmored && !_isControlled)
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
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 32 && _isCanSkill1)
					{
						stepBack();
						return;
					}
					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isArmored)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanGear03)
					{
						useGear(gear03);
					}
					else if (_isCanSkill1 && !_isArmored && _mainTarget->getGP() < 5000)
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
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (isFreeActionState())
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

		if (_isHealling && getHpPercent() < 1)
		{
			if (isFreeActionState())
				idle();
		}
		else
		{
			stepOn();
		}
	}

	inline void changeAction_SageNaruto()
	{
		_gardValue += 5000;
		_isArmored = true;
		hasArmorBroken = true;
		_isOnlySkillLocked = true;

		setIdleAction(createAnimation(skillSPC4Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));

		setWalkSpeed(320);
		_originSpeed = 320;

		lockOugisButtons();
	}

	inline void resumeAction_SageNaruto(float dt)
	{
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));

		_isOnlySkillLocked = false;

		unlockOugisButtons();

		setWalkSpeed(224);
		_originSpeed = 224;

		_gardValue -= 5000;
		_isArmored = false;
		hasArmorBroken = false;

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			setKnockDownAction(createAnimation(skillSPC5Array, 10.0f, false, true));
			knockDown();
			setKnockDownAction(createAnimation(knockDownArray, 10.0f, false, true));
		}
		else if (hasTempAttackValue1())
		{
			setnAttackValue(to_ccstring(getTempAttackValue1()));
			settempAttackValue1(nullptr);
		}
		CharacterBase::resumeAction(dt);
	}

	inline Hero *createClone_SageNaruto(int cloneTime)
	{
		auto clone = create<SageNarutoClone>(getCharacter(), CCString::create(kRoleClone), getGroup());
		clone->setSkill1Action(clone->createAnimation(clone->skillSPC1Array, 10.0f, false, true));
		clone->setsAttackValue1(getSAttackValue1Str());
		clone->setsAttack1Type(_spcattackType1);
		clone->_sattackcooldown1 = _spcattackcooldown1;
		return clone;
	}

	// Naruto Rikutou

	void perform_RikudoNaruto()
	{
		_mainTarget = nullptr;
		findHeroHalf();
		if (getCoinValue() >= 500 && !_isControlled && getGameLayer()->_enableGear)
		{
			if (getGearArray()->count() == 0)
				setGear(gear03);
			else if (getGearArray()->count() == 1)
				setGear(gear07);
			else if (getGearArray()->count() == 2)
				setGear(gear02);
		}

		if (checkRetri())
		{
			if (_mainTarget != nullptr)
			{
				if (stepBack2())
					return;
			}
			else
			{
				if (_isCanGear00)
				{
					useGear(gear00);
				}
				if (stepBack())
					return;
			}
		}

		if (isBaseDanger && checkBase() && !_isControlled)
		{
			bool needBack = false;
			if (isAkatsukiGroup())
			{
				if (getPositionX() < 85 * 32)
					needBack = true;
			}
			else
			{
				if (getPositionX() > 11 * 32)
					needBack = true;
			}

			if (needBack)
			{
				if (stepBack2())
					return;
			}
		}

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (isFreeActionState())
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
				else if (_isCanSkill3 && !_isArmored && _mainTarget->getGP() < 5000)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (_isCanSkill1 && !_isArmored && _mainTarget->getGP() < 5000)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (_isCanGear03)
				{
					useGear(gear03);
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isArmored && !_isControlled)
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
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isArmored)
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
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (isFreeActionState())
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

		if (_isHealling && getHpPercent() < 1)
		{
			if (isFreeActionState())
				idle();
		}
		else
		{
			stepOn();
		}
	}

	inline void changeAction_RikudoNaruto()
	{
		_gardValue += 5000;
		_isArmored = true;
		hasArmorBroken = true;
		_isOnlySkillLocked = true;

		setIdleAction(createAnimation(skillSPC4Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));

		if (isCharacter(kRikudoNaruto))
		{
			settempAttackValue1(to_ccstring(getNAttackValue()));
			setnAttackValue(to_ccstring(560));
		}

		setWalkSpeed(320);
		_originSpeed = 320;

		lockOugisButtons();
	}

	inline void resumeAction_RikudoNaruto(float dt)
	{
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));

		_isOnlySkillLocked = false;

		unlockOugisButtons();

		setWalkSpeed(224);
		_originSpeed = 224;

		_gardValue -= 5000;
		_isArmored = false;
		hasArmorBroken = false;

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			idle();
		}

		if (hasTempAttackValue1())
		{
			setnAttackValue(to_ccstring(getTempAttackValue1()));
			settempAttackValue1(nullptr);
		}
		CharacterBase::resumeAction(dt);
	}

	inline Hero *createClone_RikudoNaruto(int cloneTime)
	{
		auto clone = create<Kurama>(CCString::create("Kurama"), CCString::create(kRoleClone), getGroup());
		clone->setGP(5000);
		clone->_isArmored = true;
		clone->setWalkSpeed(320);
		clone->_originSpeed = 320;
		clone->hasArmorBroken = true;
		return clone;
	}

private:
	std::string _originNAttackType;
};
