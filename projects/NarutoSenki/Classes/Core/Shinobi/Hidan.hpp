#pragma once
#include "Hero.hpp"

class Hidan : public Hero
{
	void perform()
	{
		_mainTarget = nullptr;
		bool _isFound = false;
		if (getMonsterArray() && getMonsterArray()->count() > 0)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				Monster *mo = (Monster *)pObject;
				if (strcmp(mo->getCharacter()->getCString(), "CircleMark") == 0)
				{
					_mainTarget = mo;
					_isFound = true;
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
					if ((abs(sp.x) > 8 || abs(sp.y) > 8))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else
					{
						if (_isArmored)
						{
							CCObject *pObject;
							CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
							{
								CharacterBase *tempHero = (CharacterBase *)pObject;
								if (tempHero->getGroup() != getGroup() && to_uint(tempHero->getHP()->getCString()) < 2000 && tempHero->getActionState() != State::DEAD && (strcmp(tempHero->getRole()->getCString(), "Player") == 0 || strcmp(tempHero->getRole()->getCString(), "Com") == 0))
								{
									attack(NAttack);
									return;
								}
							}

							idle();
							return;
						}
					}
				}
			}
		}

		if (!_isFound)
		{
			findHero();
		}

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

		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled&& _delegate->_enableGear)
		{
			if (getGearArray()->count() == 0)
				setGear(gear06);
			else if (getGearArray()->count() == 1)
				setGear(gear01);
			else if (getGearArray()->count() == 2)
				setGear(gear07);
		}

		if (checkRetri() && !_isArmored && !_isFound)
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

		if (isBaseDanger && checkBase() && !_isControlled && !_isArmored && !_isFound)
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

		if (_mainTarget && strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) != 0)
		{
			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			else
				sp = ccpSub(_mainTarget->getPosition(), getPosition());

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && !_isArmored)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					if (_isCanSkill1 && !_isArmored && !_isFound)
					{
						changeSide(sp);
						attack(SKILL1);
						return;
					}
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getGP() < 5000 && !_isArmored)
				{
					if (abs(sp.x) > 56 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControlled && !_isArmored && !_isFound)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if ((abs(sp.x) > 48 || abs(sp.y) > 32) && !_isArmored)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					if (_isCanOugis1 && !_isArmored && !_isControlled && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill3 && !_isArmored)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else
					{
						if (!_isArmored)
						{
							changeSide(sp);
							attack(NAttack);
						}
						else
						{
							idle();
						}
					}

					return;
				}
			}
		}

		if (!_mainTarget && !_isFound && !_isArmored)
		{
			if (!findFlog())
			{
				findTower();
			}
		}

		if (_mainTarget && strcmp(_mainTarget->getRole()->getCString(), ROLE_MON) != 0 && !_isArmored)
		{
			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			else
				sp = ccpSub(_mainTarget->getPosition(), getPosition());

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				if (_isCanSkill3 && strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) == 0 && isBaseDanger && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL3);
				}
				else if (_isCanSkill2 && strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) == 0 && isBaseDanger && !_isArmored)
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

		if (!_isArmored)
		{
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
		else
		{
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
				idle();
		}
	}

	void changeAction()
	{
		_isArmored = true;
		_isTaunt = true;
		_isOnlySkillLocked = true;
		setIdleAction(createAnimation(skillSPC1Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));

		lockOugisButtons();
	}

	void resumeAction(float dt)
	{
		_isArmored = false;
		_isTaunt = false;
		_isOnlySkillLocked = false;
		unlockOugisButtons();

		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));

		if (getMonsterArray() && getMonsterArray()->count() > 0)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				CharacterBase *mo = (CharacterBase *)pObject;
				int index = _delegate->_CharacterArray->indexOfObject(mo);
				if (index >= 0)
				{
					_delegate->_CharacterArray->removeObjectAtIndex(index);
				}
				mo->setActionState(State::DEAD);
				CCNotificationCenter::sharedNotificationCenter()->removeObserver(mo, "acceptAttack");
				mo->removeFromParent();
				mo = nullptr;
			}

			getMonsterArray()->removeAllObjects();
			_monsterArray = nullptr;
		}

		if (is_player)
		{
			_delegate->getHudLayer()->skill1Button->unLock();
		}

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			idle();
		}
		CharacterBase::resumeAction(dt);
	}

	void setActionResume()
	{
		if (_skillChangeBuffValue == 0)
			return;

		unschedule(schedule_selector(Hidan::resumeAction));
		_isArmored = false;
		_isTaunt = false;
		_isOnlySkillLocked = false;
		lockOugisButtons();
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));

		if (getMonsterArray() && getMonsterArray()->count() > 0)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				CharacterBase *mo = (CharacterBase *)pObject;
				int index = _delegate->_CharacterArray->indexOfObject(mo);
				if (index >= 0)
				{
					_delegate->_CharacterArray->removeObjectAtIndex(index);
				}
				mo->setActionState(State::DEAD);
				CCNotificationCenter::sharedNotificationCenter()->removeObserver(mo, "acceptAttack");
				mo->removeFromParent();
				mo = nullptr;
			}
			getMonsterArray()->removeAllObjects();
			_monsterArray = nullptr;
		}

		if (is_player)
		{
			_delegate->getHudLayer()->skill1Button->unLock();
		}

		if (_actionState != State::DEAD)
		{
			_actionState = State::WALK;
			idle();
		}

		_skillChangeBuffValue = 0;
	}
};
