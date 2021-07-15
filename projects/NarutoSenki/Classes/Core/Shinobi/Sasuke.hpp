#pragma once
#include "Hero.hpp"

class Sasuke : public Hero
{
#define kSasuke________ "Sasuke"
#define kImmortalSasuke "ImmortalSasuke"

	void setID(CCString *character, CCString *role, CCString *group)
	{
		Hero::setID(character, role, group);

		match_char_exp(kSasuke________, setAIHandler(Sasuke::perform),
					   kImmortalSasuke, setAIHandler(Sasuke::perform_SasukeImmortal));
	}

	void changeAction()
	{
		match_char_exp(kSasuke________, changeAction_Sasuke(),
					   kImmortalSasuke, changeAction_SasukeImmortal());
	}

	void resumeAction(float dt)
	{
		match_char_exp(kSasuke________, resumeAction_Sasuke(dt),
					   kImmortalSasuke, resumeAction_SasukeImmortal(dt));
	}

	void setActionResume()
	{
		match_char_exp(kSasuke________, setActionResume_Sasuke(),
					   kImmortalSasuke, setActionResume_SasukeImmortal());
	}

	// Sasuke

	void perform()
	{
		_mainTarget = nullptr;
		findEnemy2("Hero");

		if (_isCanGear06)
		{
			if ((getActionState() == State::FLOAT ||
				 getActionState() == State::AIRHURT ||
				 getActionState() == State::HURT ||
				 getActionState() == State::KNOCKDOWN) &&
				getHpPercent() < 0.5 && !_isArmored && !_isInvincible)
			{
				useGear(gear06);
			}
		}
		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear06);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear01);
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
				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isArmored && !_isControlled)
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
				if (_isCanSkill1 && !_isArmored && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanSkill2 && isBaseDanger && !_isArmored && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanSkill3 && !_isArmored && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
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

	inline void changeAction_Sasuke()
	{
		if (_skillChangeBuffValue == 17)
		{
			_isTaunt = true;
			setHurtAction(createAnimation(skillSPC5Array, 10.0f, false, true));

			CCObject *pObject;
			CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
			{
				CharacterBase *tempHero = (CharacterBase *)pObject;
				if (strcmp(getGroup()->getCString(), tempHero->getGroup()->getCString()) != 0 && (strcmp(tempHero->getRole()->getCString(), "Player") == 0 || strcmp(tempHero->getRole()->getCString(), "Com") == 0) && tempHero->getActionState() != State::HURT && tempHero->getActionState() != State::DEAD)
				{
					float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
					if (distanceX < winSize.width / 2)
					{
						if (!tempHero->_isVisable)
						{
							if (strcmp(tempHero->getCharacter()->getCString(), "Konan") == 0 ||
								strcmp(tempHero->getCharacter()->getCString(), "Deidara") == 0)
							{
								tempHero->unschedule(schedule_selector(CharacterBase::disableBuff));
							}

							tempHero->setOpacity(255);
							tempHero->setVisible(true);

							if (tempHero->_hpBar)
							{
								tempHero->_hpBar->setVisible(true);
							}
							if (tempHero->_shadow)
							{
								tempHero->_shadow->setVisible(true);
							}

							tempHero->_isVisable = true;
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
			settempAttackValue1(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString())));
			setnAttackValue(CCString::createWithFormat("%d", 560));

			_nattackRangeX = _spcattackRangeX3;
			_nattackRangeY = _spcattackRangeY3;
			_tempAttackType = _nattackType;
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
			if (gettempAttackValue1())
			{
				setnAttackValue(CCString::createWithFormat("%d", to_int(gettempAttackValue1()->getCString())));
				settempAttackValue1(nullptr);
			}
			_nattackRangeX = 16;
			_nattackRangeY = 48;
			_nattackType = _tempAttackType;
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
		findEnemy2("Hero");

		if (_isCanGear06)
		{
			if ((getActionState() == State::FLOAT ||
				 getActionState() == State::AIRHURT ||
				 getActionState() == State::HURT ||
				 getActionState() == State::KNOCKDOWN) &&
				getHpPercent() < 0.5 && !_isArmored && !_isInvincible)
			{
				useGear(gear06);
			}
		}
		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear06);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear01);
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
				if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && !_isArmored)
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
				if (_isCanSkill1 && !_isArmored && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanSkill2 && isBaseDanger && !_isArmored && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
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

	inline void changeAction_SasukeImmortal()
	{
		if (_skillChangeBuffValue == 17)
		{
			_isTaunt = true;
			setHurtAction(createAnimation(skillSPC1Array, 10.0f, false, true));

			CCObject *pObject;
			CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
			{
				CharacterBase *tempHero = (CharacterBase *)pObject;
				if (strcmp(getGroup()->getCString(), tempHero->getGroup()->getCString()) != 0 &&
					(strcmp(tempHero->getRole()->getCString(), "Player") == 0 || strcmp(tempHero->getRole()->getCString(), "Com") == 0) &&
					tempHero->getActionState() != State::HURT &&
					tempHero->getActionState() != State::DEAD)
				{
					float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
					if (distanceX < winSize.width / 2)
					{
						if (!tempHero->_isVisable)
						{
							if (strcmp(tempHero->getCharacter()->getCString(), "Konan") == 0 ||
								strcmp(tempHero->getCharacter()->getCString(), "Deidara") == 0)
							{
								tempHero->unschedule(schedule_selector(CharacterBase::disableBuff));
							}

							tempHero->setOpacity(255);
							tempHero->setVisible(true);

							if (tempHero->_hpBar)
							{
								tempHero->_hpBar->setVisible(true);
							}
							if (tempHero->_shadow)
							{
								tempHero->_shadow->setVisible(true);
							}

							tempHero->_isVisable = true;
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

			settempAttackValue1(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString())));
			setnAttackValue(CCString::createWithFormat("%d", 1160));

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
			if (gettempAttackValue1())
			{
				setnAttackValue(CCString::createWithFormat("%d", to_int(gettempAttackValue1()->getCString())));
				settempAttackValue1(nullptr);
			}
			_gardValue -= 5000;
			_isArmored = false;

			_nattackRangeX = 16;
			_nattackRangeY = 48;

			if (getMonsterArray() && getMonsterArray()->count() > 0)
			{
				CCObject *pObject;
				CCARRAY_FOREACH(getMonsterArray(), pObject)
				{
					Monster *mo = (Monster *)pObject;
					mo->removeFromParent();
				}
				getMonsterArray()->removeAllObjects();
				setMonsterArray(nullptr);
			}

			if (getActionState() != State::DEAD)
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
			lockOugisButtons();

			setWalkSpeed(224);

			_originSpeed = 224;
			if (gettempAttackValue1())
			{
				setnAttackValue(CCString::createWithFormat("%d", to_int(gettempAttackValue1()->getCString())));
				settempAttackValue1(nullptr);
			}
			_gardValue -= 5000;
			_isArmored = false;

			_nattackRangeX = 16;
			_nattackRangeY = 48;

			_skillChangeBuffValue = 0;
		}
	}
};
