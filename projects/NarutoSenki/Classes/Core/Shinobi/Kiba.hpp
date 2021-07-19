#pragma once
#include "Hero.hpp"
#include "Kuchiyose/Akamaru.hpp"

class Kiba : public Hero
{
	void perform()
	{
		_mainTarget = nullptr;
		findEnemy2("Hero");
		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear00);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear04);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear08);
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

		if (_mainTarget && (battleCondiction >= 0 || _isCanOugis1 || _isCanOugis2))
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
				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && !_powerUPBuffValue && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking)
				{
					if (abs(sp.x) > 32 || abs(sp.y) > 32)
					{
						if (_isCanGear00)
						{
							useGear(gear00);
						}
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					changeSide(sp);

					attack(OUGIS2);
					return;
				}
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_powerUPBuffValue)
				{
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanSkill1 && _isArmored)
				{
					attack(SKILL1);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControlled)
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
						if (_isCanGear00)
						{
							useGear(gear00);
						}
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanSkill3 && !_powerUPBuffValue && !_isArmored && getHpPercent() > 0.5)
					{
						changeSide(sp);
						attack(SKILL3);
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
		if (battleCondiction >= 0)
		{
			_mainTarget = nullptr;
			if (!findEnemy2(ROLE_FLOG))
			{
				findEnemy2("Tower");
			}
		}
		else
		{
			_mainTarget = nullptr;
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
				if (_isCanSkill1 && _isArmored)
				{
					attack(SKILL1);
				}
				else if (strcmp(_mainTarget->getRole()->getCString(), "Tower") == 0 && _isCanSkill3 && !_powerUPBuffValue && !_isArmored)
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
			if (_isCanGear00)
			{
				useGear(gear00);
			}
			stepOn();
		}
	}

	void changeAction()
	{
		if (_skillChangeBuffValue == 17)
		{
			_isArmored = false;

			if (is_player)
			{
				_delegate->getHudLayer()->skill1Button->setLock();
				_delegate->getHudLayer()->skill2Button->unLock();
				_delegate->getHudLayer()->skill3Button->unLock();
			}

			setIdleAction(createAnimation(skillSPC1Array, 5.0f, true, false));
			setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
			setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));
			if (_hpBar)
			{
				_hpBar->setPositionY(65);
			}
			_skillChangeBuffValue = 0;
		}
		else if (_skillChangeBuffValue == 18)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				Monster *mo = (Monster *)pObject;
				if (strcmp(mo->getCharacter()->getCString(), "Akamaru") == 0)
				{
					mo->attack(SKILL2);
				}
			}

			_powerUPBuffValue = 360;
			setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) + _powerUPBuffValue));
			setNAttackAction(createAnimation(skillSPC4Array, 10.0f, false, true));
		}
	}

	void resumeAction(float dt)
	{
		if (_powerUPBuffValue)
		{
			setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) - _powerUPBuffValue));
			setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));
			_powerUPBuffValue = 0;
		}

		if (_actionState == State::IDLE ||
			_actionState == State::WALK ||
			_actionState == State::NATTACK)
		{
			_actionState = State::WALK;
			idle();
		}
		CharacterBase::resumeAction(dt);
	}

	void setActionResume()
	{
		if (_powerUPBuffValue)
		{
			unschedule(schedule_selector(Kiba::resumeAction));
			setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) - _powerUPBuffValue));
			_powerUPBuffValue = 0;
		}
		_isArmored = true;
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));

		if (is_player)
		{
			_delegate->getHudLayer()->skill1Button->unLock();
			_delegate->getHudLayer()->skill2Button->setLock();
			_delegate->getHudLayer()->skill3Button->setLock();
		}
		if (_hpBar)
		{
			_hpBar->setPositionY(getHeight());
		}

		if (_actionState == State::IDLE ||
			_actionState == State::WALK ||
			_actionState == State::NATTACK)
		{
			_actionState = State::WALK;
			idle();
		}

		_skillChangeBuffValue = 0;
	}

	Hero *createClone(int32_t cloneTime)
	{
		if (!_monsterArray)
		{
			_monsterArray = CCArray::create();
			_monsterArray->retain();
		}

		auto clone = create<Akamaru>(CCString::create("Akamaru"), CCString::create(ROLE_CLONE), getGroup());
		clone->_isArmored = true;
		_monsterArray->addObject(clone);
		return clone;
	}
};
