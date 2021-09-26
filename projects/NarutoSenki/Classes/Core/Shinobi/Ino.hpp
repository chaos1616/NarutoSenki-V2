#pragma once
#include "Hero.hpp"

class Ino : public Hero
{
	void dead()
	{
		CharacterBase::dead();

		// TODO: Support Ino controlled by the player can control other characters
		// if (is_player)
		// {
		// 	// Has controlled other hero
		// 	if (_delegate->currentPlayer != this)
		// 	{
		// 		auto other = _delegate->currentPlayer;
		// 		other->changeGroup();
		// 		other->doAI();

		// 		_delegate->currentPlayer = this;
		// 		_delegate->getHudLayer()->updateSkillButtons();
		// 	}
		// }
	}

	void perform()
	{
		_mainTarget = nullptr;
		findHero();

		if (_skillChangeBuffValue)
		{
			return;
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

		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled && _delegate->_enableGear)
		{
			if (getGearArray()->count() == 0)
				setGear(gear06);
			else if (getGearArray()->count() == 1)
				setGear(gear05);
			else if (getGearArray()->count() == 2)
				setGear(gear01);
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

		if (to_uint(getMaxHP()->getCString()) - to_uint(getHP()->getCString()) >= 3000 &&
			to_int(getCoin()->getCString()) >= 50 && !_isHealling && _isCanItem1 && _isArmored)
		{
			setItem(Item1);
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
				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 16)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else
					{
						changeSide(sp);
						attack(OUGIS2);
					}

					return;
				}
				else if (_mainTarget->getGP() < 5000 && (_isCanSkill3 || _isCanSkill2))
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 16)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanSkill2)
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else if (_isCanSkill3)
					{
						changeSide(sp);
						attack(SKILL3);
					}

					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControlled)
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

					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill1)
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
		if (!findFlog())
			findTower();

		if (_mainTarget)
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
				if (strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) == 0 && _isCanSkill1)
				{
					changeSide(sp);
					attack(SKILL1);
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
				idle();
		}
		else
		{
			stepOn();
		}
	}

	void resumeAction(float dt)
	{
		if (!_isArmored)
			return;

		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			Hero *tempHero = (Hero *)pObject;
			if (tempHero->_isControlled)
			{
				tempHero->_isControlled = false;
				if (strcmp(tempHero->getRole()->getCString(), "Player") == 0)
				{
					tempHero->_isAI = false;
					tempHero->unschedule(schedule_selector(Ino::setAI));
					_delegate->getHudLayer()->_isAllButtonLocked = false;
				}
				if (is_player)
				{
					// auto controlledHero = _delegate->currentPlayer;
					// controlledHero->_isAI = true;
					// controlledHero->doAI();
					// _isControlled = false;

					// _delegate->currentPlayer = this;
					_delegate->controlChar = nullptr;
					// _delegate->getHudLayer()->updateSkillButtons();
				}
				if (getActionState() != State::DEAD)
				{
					idle();
				}
				tempHero->changeGroup();
				tempHero->setController(nullptr);
			}
		}

		_isArmored = false;
	}

	void setActionResume()
	{
		unschedule(schedule_selector(Ino::resumeAction));
		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			Hero *tempHero = (Hero *)pObject;
			if (tempHero->_isControlled)
			{
				tempHero->_isControlled = false;
				tempHero->changeGroup();
				if (strcmp(tempHero->getRole()->getCString(), "Player") == 0)
				{
					tempHero->unschedule(schedule_selector(Ino::setAI));
					tempHero->_isAI = false;
					_delegate->getHudLayer()->_isAllButtonLocked = false;
				}
				if (is_player)
				{
					_delegate->controlChar = nullptr;
				}
				tempHero->setController(nullptr);
			}
		}

		_isArmored = false;
	}
};
