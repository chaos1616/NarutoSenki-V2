#pragma once
#include "Hero.hpp"

#include "Kuchiyose/Parents.hpp"

class Chiyo : public Hero
{
	void setID(CCString *character, CCString *role, CCString *group) override
	{
		Hero::setID(character, role, group);

		getGameLayer()->onHUDInitialized(BIND(Chiyo::tryLockSkillButton));
	}

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
				setGear(gear07);
			else if (getGearArray().size() == 2)
				setGear(gear04);
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

		bool isFound1 = false;

		if (hasMonsterArrayAny())
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				auto mo = (Monster *)pObject;
				if (mo->isCharacter("Parents"))
				{
					isFound1 = true;
				}
			}
		}

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (isFreeActionState())
			{
				if (_isCanOugis1 && !_isControlled && !_buffStartTime)
				{
					int countNum = 0;
					for (auto hero : getGameLayer()->_CharacterArray)
					{
						if (isSameGroupAs(hero) &&
							hero->isPlayerOrCom() &&
							hero->getActionState() != State::DEAD &&
							hero->isNotCharacter("Chiyo"))
						{
							CCPoint sp = ccpSub(hero->getPosition(), getPosition());
							if (sp.x <= winSize.width / 2)
								countNum++;
						}
					}
					if (countNum >= 1)
					{
						attack(OUGIS1);
						return;
					}
				}
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking)
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
			if (isFreeActionState())
				idle();
		}
		else
		{
			stepOn();
		}
	}

	void changeAction() override
	{
		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill1Button->setLock();
			getGameLayer()->getHudLayer()->skill2Button->unLock();
			getGameLayer()->getHudLayer()->skill3Button->unLock();
		}
	}

	void setActionResume() override
	{
		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill1Button->unLock();
			getGameLayer()->getHudLayer()->skill2Button->setLock();
			getGameLayer()->getHudLayer()->skill3Button->setLock();
		}
		_skillChangeBuffValue = 0;
	}

	Hero *createClone(int cloneTime) override
	{
		if (!_monsterArray)
		{
			_monsterArray = CCArray::create();
			_monsterArray->retain();
		}

		auto clone = create<Parents>(CCString::create("Parents"), CCString::create(kRoleKugutsu), getGroup());
		clone->setPosition(ccp(getPositionX(), getPositionY() - 3));
		clone->_isArmored = true;
		_monsterArray->addObject(clone);
		return clone;
	}

private:
	inline void tryLockSkillButton()
	{
		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill2Button->setLock();
			getGameLayer()->getHudLayer()->skill3Button->setLock();
		}
	}
};
