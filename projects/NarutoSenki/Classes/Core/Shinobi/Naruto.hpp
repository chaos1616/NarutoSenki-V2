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

	void setID(CCString *character, CCString *role, CCString *group)
	{
		Hero::setID(character, role, group);

		match_char_exp3(kNaruto______, setAIHandler(Naruto::perform),
						kSageNaruto__, setAIHandler(Naruto::perform_SageNaruto),
						kRikudoNaruto, setAIHandler(Naruto::perform_RikudoNaruto));
	}

	void changeAction()
	{
		match_char_exp3(kNaruto______, changeAction_Naruto(),
						kSageNaruto__, changeAction_SageNaruto(),
						kRikudoNaruto, changeAction_RikudoNaruto());
	}

	void resumeAction(float dt)
	{
		match_char_exp3(kNaruto______, resumeAction_Naruto(dt),
						kSageNaruto__, resumeAction_SageNaruto(dt),
						kRikudoNaruto, resumeAction_RikudoNaruto(dt));
	}

	Hero *createClone(unsigned int cloneTime)
	{
		match_char_exp3(kNaruto______, return createClone_Naruto(cloneTime),
						kSageNaruto__, return createClone_SageNaruto(cloneTime),
						kRikudoNaruto, return createClone_RikudoNaruto(cloneTime));
	}

	// Naruto

	void perform()
	{

		_mainTarget = nullptr;
		findEnemy2("Hero");
		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear03);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear07);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear02);
			}
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
			if (strcmp(Akatsuki, getGroup()->getCString()) == 0)
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

		if (_mainTarget && strcmp(_mainTarget->getRole()->getCString(), "Flog") != 0)
		{
			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
			{
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			}
			else
			{
				sp = ccpSub(_mainTarget->getPosition(), getPosition());
			}
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{

				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && !_isBati)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanSkill2 && !_isBati)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isBati && !_isControlled)
				{
					if (abs(sp.x) < 160)
					{
						stepBack2();
						return;
					}
					else
					{
						idle();
						return;
					}
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

					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isBati)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanGear03)
					{
						useGear(gear03);
					}
					else if (_isCanSkill3 && !_isBati && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else if (_isCanSkill1 && !_isBati && _mainTarget->getGP() < 5000)
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
		if (!findEnemy2("Flog"))
		{
			findEnemy2("Tower");
		}

		if (_mainTarget)
		{

			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
			{
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			}
			else
			{
				sp = ccpSub(_mainTarget->getPosition(), getPosition());
			}

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				if (_isCanSkill2 && !_isBati)
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				idle();
			}
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

		settempAttackValue1(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString())));
		setnAttackValue(CCString::createWithFormat("%d", 960));

		_nattackRangeX = _spcattackRangeX3;
		_nattackRangeY = _spcattackRangeY3;
		_tempAttackType = _nattackType;
		_nattackType = _spcattackType3;

		_gardValue += 5000;
		_isBati = true;

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
		if (gettempAttackValue1())
		{
			setnAttackValue(CCString::createWithFormat("%d", to_int(gettempAttackValue1()->getCString())));
			settempAttackValue1(nullptr);
		}
		isPofang = false;

		_nattackRangeX = 16;
		_nattackRangeY = 48;
		_nattackType = _tempAttackType;
		_gardValue -= 5000;
		_isBati = false;

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			knockDown();
		}

		setKnockDownAction(createAnimation(knockDownArray, 10.0f, false, true));
		CharacterBase::resumeAction(dt);
	}

	inline Hero *createClone_Naruto(unsigned int cloneTime)
	{
		auto clone = create<NarutoClone>(getCharacter(), CCString::create(K_TAG_CLONE), getGroup());
		return clone;
	}

	// Naruto Sage

	void perform_SageNaruto()
	{

		_mainTarget = nullptr;
		findEnemy2("Hero");
		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear03);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear07);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear02);
			}
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
			if (strcmp(Akatsuki, getGroup()->getCString()) == 0)
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

		if (_mainTarget && strcmp(_mainTarget->getRole()->getCString(), "Flog") != 0)
		{
			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
			{
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			}
			else
			{
				sp = ccpSub(_mainTarget->getPosition(), getPosition());
			}
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{

				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && !_isBati)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanSkill2 && !_isBati)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (_isCanSkill3 && !_isBati && _mainTarget->getGP() < 5000)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isBati && !_isControlled)
				{
					if (abs(sp.x) < 160)
					{
						stepBack2();
						return;
					}
					else
					{
						idle();
						return;
					}
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
					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isBati)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanGear03)
					{
						useGear(gear03);
					}
					else if (_isCanSkill1 && !_isBati && _mainTarget->getGP() < 5000)
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
		if (!findEnemy2("Flog"))
		{
			findEnemy2("Tower");
		}

		if (_mainTarget)
		{

			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
			{
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			}
			else
			{
				sp = ccpSub(_mainTarget->getPosition(), getPosition());
			}

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				if (_isCanSkill2 && !_isBati)
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				idle();
			}
		}
		else
		{
			stepOn();
		}
	}

	inline void changeAction_SageNaruto()
	{
		_gardValue += 5000;
		_isBati = true;
		isPofang = true;
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
		_isBati = false;
		isPofang = false;

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			setKnockDownAction(createAnimation(skillSPC5Array, 10.0f, false, true));
			knockDown();
			setKnockDownAction(createAnimation(knockDownArray, 10.0f, false, true));
		}
		else if (gettempAttackValue1())
		{
			setnAttackValue(CCString::createWithFormat("%d", to_int(gettempAttackValue1()->getCString())));
			settempAttackValue1(nullptr);
		}
		CharacterBase::resumeAction(dt);
	}

	inline Hero *createClone_SageNaruto(unsigned int cloneTime)
	{
		auto clone = create<SageNarutoClone>(getCharacter(), CCString::create(K_TAG_CLONE), getGroup());
		clone->setSkill1Action(clone->createAnimation(clone->skillSPC1Array, 10.0f, false, true));
		clone->setsAttackValue1(getsAttackValue1());
		clone->setsAttack1Type(_spcattackType1);
		clone->_sattackcoldDown1 = _spcattackcoldDown1;
		return clone;
	}

	// Naruto Rikutou

	void perform_RikudoNaruto()
	{

		_mainTarget = nullptr;
		findEnemy2("Hero");
		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear03);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear07);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear02);
			}
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
			if (strcmp(Akatsuki, getGroup()->getCString()) == 0)
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

		if (_mainTarget && strcmp(_mainTarget->getRole()->getCString(), "Flog") != 0)
		{
			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
			{
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			}
			else
			{
				sp = ccpSub(_mainTarget->getPosition(), getPosition());
			}
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{

				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && !_isBati)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanSkill2 && !_isBati)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (_isCanSkill3 && !_isBati && _mainTarget->getGP() < 5000)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (_isCanSkill1 && !_isBati && _mainTarget->getGP() < 5000)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (_isCanGear03)
				{
					useGear(gear03);
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isBati && !_isControlled)
				{
					if (abs(sp.x) < 160)
					{
						stepBack2();
						return;
					}
					else
					{
						idle();
						return;
					}
				}
				else if (abs(sp.x) < 128)
				{
					if (abs(sp.x) > 32 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isBati)
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
		if (!findEnemy2("Flog"))
		{
			findEnemy2("Tower");
		}

		if (_mainTarget)
		{

			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
			{
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			}
			else
			{
				sp = ccpSub(_mainTarget->getPosition(), getPosition());
			}

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				if (_isCanSkill1 && !_isBati && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanSkill2 && !_isBati)
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				idle();
			}
		}
		else
		{
			stepOn();
		}
	}

	inline void changeAction_RikudoNaruto()
	{
		_gardValue += 5000;
		_isBati = true;
		isPofang = true;
		_isOnlySkillLocked = true;

		setIdleAction(createAnimation(skillSPC4Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));

		if (strcmp(getCharacter()->getCString(), "RikudoNaruto") == 0)
		{
			settempAttackValue1(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString())));
			setnAttackValue(CCString::createWithFormat("%d", 560));
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
		_isBati = false;
		isPofang = false;

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			idle();
		}

		if (gettempAttackValue1())
		{
			setnAttackValue(CCString::createWithFormat("%d", to_int(gettempAttackValue1()->getCString())));
			settempAttackValue1(nullptr);
		}
		CharacterBase::resumeAction(dt);
	}

	inline Hero *createClone_RikudoNaruto(unsigned int cloneTime)
	{
		auto clone = create<Kurama>(CCString::create("Kurama"), CCString::create(K_TAG_CLONE), getGroup());
		clone->setGP(5000);
		clone->_isBati = true;
		clone->setWalkSpeed(320);
		clone->_originSpeed = 320;
		clone->isPofang = true;
		return clone;
	}
};
