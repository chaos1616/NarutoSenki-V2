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

		tryUseGear6();
		tryBuyGear(gear06, gear07, gear04);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		bool isFound1 = false;

		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
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
							if (sp.x <= kAttackRange)
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
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 5000 && !_isHealing && !_isControlled)
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

		checkHealingState();
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
		auto clone = create<Parents>(CCString::create("Parents"), CCString::create(kRoleKugutsu), getGroup());
		clone->setPosition(ccp(getPositionX(), getPositionY() - 3));
		clone->_isArmored = true;
		_monsterArray.push_back(clone);
		return clone;
	}

private:
	void tryLockSkillButton()
	{
		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill2Button->setLock();
			getGameLayer()->getHudLayer()->skill3Button->setLock();
		}
	}
};
