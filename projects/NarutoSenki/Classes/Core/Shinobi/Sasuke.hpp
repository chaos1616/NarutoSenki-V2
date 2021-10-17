#pragma once
#include "Hero.hpp"

class Sasuke : public Hero
{
#define kSasuke________ "Sasuke"
#define kImmortalSasuke "ImmortalSasuke"

	void setID(CCString *character, CCString *role, CCString *group) override
	{
		Hero::setID(character, role, group);

		match_char_exp(kSasuke________, setAIHandler(Sasuke::perform),
					   kImmortalSasuke, setAIHandler(Sasuke::perform_SasukeImmortal));
	}

	void changeAction() override
	{
		match_char_exp(kSasuke________, changeAction_Sasuke(),
					   kImmortalSasuke, changeAction_SasukeImmortal());
	}

	void resumeAction(float dt) override
	{
		match_char_exp(kSasuke________, resumeAction_Sasuke(dt),
					   kImmortalSasuke, resumeAction_SasukeImmortal(dt));
	}

	void setActionResume() override
	{
		match_char_exp(kSasuke________, setActionResume_Sasuke(),
					   kImmortalSasuke, setActionResume_SasukeImmortal());
	}

	// Sasuke

	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		if (_isCanGear06)
		{
			if ((_actionState == State::FLOAT ||
				 _actionState == State::AIRHURT ||
				 _actionState == State::HURT ||
				 _actionState == State::KNOCKDOWN) &&
				getHpPercent() < 0.5 && !_isArmored && !_isInvincible)
			{
				useGear(gear06);
			}
		}

		if (getCoinValue() >= 500 && !_isControlled && getGameLayer()->_enableGear)
		{
			if (getGearArray().size() == 0)
				setGear(gear06);
			else if (getGearArray().size() == 1)
				setGear(gear01);
			else if (getGearArray().size() == 2)
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
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isArmored && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (_isCanSkill3 && !_isTaunt && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL3);
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
					else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_isCanSkill1 && !_isCanSkill2)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isArmored)
					{
						if (abs(sp.x) > 32 || abs(sp.y) > 32)
						{
							moveDirection = ccpNormalize(sp);
							walk(moveDirection);
							return;
						}
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill2 && !_isArmored && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL2);
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
				if (_isCanSkill1 && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanSkill2 && isBaseDanger && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanSkill3 && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL3);
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

	inline void changeAction_Sasuke()
	{
		if (_skillChangeBuffValue == 17)
		{
			_isTaunt = true;
			setHurtAction(createAnimation(skillSPC5Array, 10.0f, false, true));

			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (isNotSameGroupAs(hero) &&
					hero->isPlayerOrCom() &&
					hero->getActionState() != State::HURT &&
					hero->getActionState() != State::DEAD)
				{
					float distanceX = ccpSub(hero->getPosition(), getPosition()).x;
					if (distanceX < winSize.width / 2)
					{
						if (!hero->_isVisable)
						{
							if (hero->isCharacter("Konan") ||
								hero->isCharacter("Deidara"))
							{
								hero->unschedule(schedule_selector(CharacterBase::disableBuff));
							}

							hero->setOpacity(255);
							hero->setVisible(true);

							if (hero->_hpBar)
								hero->_hpBar->setVisible(true);
							if (hero->_shadow)
								hero->_shadow->setVisible(true);

							hero->_isVisable = true;
						}
					}
				}
			}
		}
		else if (_skillChangeBuffValue == 18)
		{
			setIdleAction(createAnimation(skillSPC1Array, 5.0f, true, false));
			setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
			setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));
			setKnockDownAction(createAnimation(skillSPC4Array, 10.0f, false, true));

			setWalkSpeed(320);
			_originSpeed = 320;

			_isOnlySkillLocked = true;
			settempAttackValue1(to_ccstring(getNAttackValue()));
			setnAttackValue(to_ccstring(560));

			_nattackRangeX = _spcattackRangeX3;
			_nattackRangeY = _spcattackRangeY3;
			_originNAttackType = _nattackType;
			_nattackType = _spcattackType3;

			_gardValue += 5000;
			_isArmored = true;

			lockOugisButtons();
		}
	}

	inline void resumeAction_Sasuke(float dt)
	{
		if (_isTaunt)
		{
			_isTaunt = false;
			setHurtAction(createAnimation(hurtArray, 10.0f, false, true));
		}
		else if (_skillChangeBuffValue == 18)
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
			_nattackRangeX = 16;
			_nattackRangeY = 48;
			_nattackType = _originNAttackType;
			_gardValue -= 5000;
			_isArmored = false;

			if (_actionState != State::DEAD)
			{
				_actionState = State::WALK;
				knockDown();
			}

			setKnockDownAction(createAnimation(knockDownArray, 10.0f, false, true));
		}
		CharacterBase::resumeAction(dt);
	}

	inline void setActionResume_Sasuke()
	{
		if (_isTaunt)
		{
			unschedule(schedule_selector(Sasuke::resumeAction_Sasuke));
			_isTaunt = false;
			setHurtAction(createAnimation(hurtArray, 10.0f, false, true));
			_skillChangeBuffValue = 0;
		}
	}

	// Sasuke Immortal

	void perform_SasukeImmortal()
	{
		_mainTarget = nullptr;
		findHeroHalf();

		if (_isCanGear06)
		{
			if ((_actionState == State::FLOAT ||
				 _actionState == State::AIRHURT ||
				 _actionState == State::HURT ||
				 _actionState == State::KNOCKDOWN) &&
				getHpPercent() < 0.5 && !_isArmored && !_isInvincible)
			{
				useGear(gear06);
			}
		}

		if (getCoinValue() >= 500 && !_isControlled && getGameLayer()->_enableGear)
		{
			if (getGearArray().size() == 0)
				setGear(gear06);
			else if (getGearArray().size() == 1)
				setGear(gear01);
			else if (getGearArray().size() == 2)
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
				if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && !_isArmored)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(OUGIS2);
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
				else if (_isCanSkill3 && !_isArmored && !_isTaunt)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (abs(sp.x) < 128 || _isArmored)
				{
					if (abs(sp.x) > 196 || abs(sp.y) > 64)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 96 || abs(sp.y) > 32) && !_isArmored)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_isCanSkill1 && !_isCanSkill2)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanSkill2 && !_isArmored && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL2);
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
				if (_isCanSkill1 && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanSkill2 && isBaseDanger && !_isArmored && _mainTarget->isFlog())
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

	inline void changeAction_SasukeImmortal()
	{
		if (_skillChangeBuffValue == 17)
		{
			_isTaunt = true;
			setHurtAction(createAnimation(skillSPC1Array, 10.0f, false, true));

			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (isNotSameGroupAs(hero) &&
					hero->isPlayerOrCom() &&
					hero->getActionState() != State::HURT &&
					hero->getActionState() != State::DEAD)
				{
					float distanceX = ccpSub(hero->getPosition(), getPosition()).x;
					if (distanceX < winSize.width / 2)
					{
						if (!hero->_isVisable)
						{
							if (hero->isCharacter("Konan") ||
								hero->isCharacter("Deidara"))
							{
								hero->unschedule(schedule_selector(CharacterBase::disableBuff));
							}

							hero->setOpacity(255);
							hero->setVisible(true);

							if (hero->_hpBar)
								hero->_hpBar->setVisible(true);
							if (hero->_shadow)
								hero->_shadow->setVisible(true);

							hero->_isVisable = true;
						}
					}
				}
			}
		}
		else if (_skillChangeBuffValue == 18)
		{
			setIdleAction(createAnimation(skillSPC4Array, 5.0f, true, false));
			setWalkAction(createAnimation(skillSPC3Array, 10.0f, true, false));
			setNAttackAction(createAnimation(skillSPC2Array, 10.0f, false, true));
			setWalkSpeed(112);
			_originSpeed = 112;

			settempAttackValue1(to_ccstring(getNAttackValue()));
			setnAttackValue(to_ccstring(1160));

			_nattackRangeX = 156;
			_nattackRangeY = 64;

			_gardValue += 5000;
			_isArmored = true;
			_isOnlySkillLocked = true;

			lockOugisButtons();
		}
	}

	inline void resumeAction_SasukeImmortal(float dt)
	{
		if (_isTaunt)
		{
			_isTaunt = false;
			setHurtAction(createAnimation(hurtArray, 10.0f, false, true));
		}
		else if (_skillChangeBuffValue == 18)
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
			_gardValue -= 5000;
			_isArmored = false;

			_nattackRangeX = 16;
			_nattackRangeY = 48;

			if (hasMonsterArrayAny())
			{
				CCObject *pObject;
				CCARRAY_FOREACH(getMonsterArray(), pObject)
				{
					auto mo = (Monster *)pObject;
					mo->removeFromParent();
				}
				getMonsterArray()->removeAllObjects();
				setMonsterArray(nullptr);
			}

			if (_actionState != State::DEAD)
			{
				setActionState(State::WALK);
				idle();
			}
		}
		CharacterBase::resumeAction(dt);
	}

	inline void setActionResume_SasukeImmortal()
	{
		if (_isTaunt)
		{
			unschedule(schedule_selector(Sasuke::resumeAction_SasukeImmortal));
			_isTaunt = false;
			setHurtAction(createAnimation(hurtArray, 10.0f, false, true));
			_skillChangeBuffValue = 0;
		}
		else if (_skillChangeBuffValue && _skillChangeBuffValue == 18)
		{
			unschedule(schedule_selector(Sasuke::resumeAction_SasukeImmortal));

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
			_gardValue -= 5000;
			_isArmored = false;

			_nattackRangeX = 16;
			_nattackRangeY = 48;

			_skillChangeBuffValue = 0;
		}
	}

private:
	string _originNAttackType;
};
