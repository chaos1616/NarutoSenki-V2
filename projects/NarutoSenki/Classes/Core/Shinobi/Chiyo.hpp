#pragma once
#include "Hero.hpp"

#include "Kuchiyose/Parents.hpp"

class Chiyo : public Hero
{
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
				setGear(gear07);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear04);
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

		bool isFound1 = false;

		if (getMonsterArray() && getMonsterArray()->count() > 0)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				Monster *mo = (Monster *)pObject;
				if (strcmp(mo->getCharacter()->getCString(), "Parents") == 0)
				{
					isFound1 = true;
				}
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
				if (_isCanOugis1 && !_isControlled && !_buffStartTime)
				{

					CCObject *pObject;
					int countNum = 0;
					CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
					{
						Hero *tempHero = (Hero *)pObject;
						if (strcmp(getGroup()->getCString(), tempHero->getGroup()->getCString()) == 0 && (strcmp(tempHero->getRole()->getCString(), "Player") == 0 || strcmp(tempHero->getRole()->getCString(), "Com") == 0) && tempHero->getActionState() != State::DEAD && strcmp(tempHero->getCharacter()->getCString(), "Chiyo") != 0)
						{
							CCPoint sp = ccpSub(tempHero->getPosition(), getPosition());
							if (sp.x <= winSize.width / 2)
							{
								countNum++;
							}
						}
					}
					if (countNum >= 1)
					{
						attack(OUGIS1);
						return;
					}
				}
				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking)
				{

					if (abs(sp.x) > 96 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 48)
					{
						stepBack();
						return;
					}
					changeSide(sp);
					attack(OUGIS2);
				}
				else if (_isCanSkill1 && !isFound1 && !_isControlled)
				{
					attack(SKILL1);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 5000 && !_isHealling && !_isControlled)
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
				if (_isCanSkill1 && !isFound1)
				{
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
			{
				idle();
			}
		}
		else
		{
			stepOn();
		}
	}

	void changeAction()
	{

		if (is_player)
		{
			_delegate->getHudLayer()->skill1Button->setLock();
			_delegate->getHudLayer()->skill2Button->unLock();
			_delegate->getHudLayer()->skill3Button->unLock();
		}
	}

	void setActionResume()
	{

		if (is_player)
		{
			_delegate->getHudLayer()->skill1Button->unLock();
			_delegate->getHudLayer()->skill2Button->setLock();
			_delegate->getHudLayer()->skill3Button->setLock();
		}
		_skillChangeBuffValue = 0;
	}

	Hero *createClone(unsigned int cloneTime)
	{

		if (!_monsterArray)
		{
			_monsterArray = CCArray::create();
			_monsterArray->retain();
		}

		auto clone = create<Parents>(CCString::create("Parents"), CCString::create(ROLE_KUGUTSU), getGroup());
		clone->setPosition(ccp(getPositionX(), getPositionY() - 3));
		clone->_isArmored = true;
		_monsterArray->addObject(clone);
		return clone;
	}
};
