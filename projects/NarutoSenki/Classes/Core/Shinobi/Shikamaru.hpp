#pragma once
#include "Hero.hpp"

class Shikamaru : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		if (getCoin() >= 500 && !_isControlled && getGameLayer()->_enableGear)
		{
			if (getGearArray().size() == 0)
				setGear(gear00);
			else if (getGearArray().size() == 1)
				setGear(gear07);
			else if (getGearArray().size() == 2)
				setGear(gear08);
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
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && !_mainTarget->_isSticking)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getGP() < 5000)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 32)
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
					attack(OUGIS1);
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
				else if (getLV() >= 2 && _isCanSkill1)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && !_mainTarget->_isSticking)
				{
					if (abs(sp.x) > 156 || abs(sp.y) > 32)
					{
						if (_isCanGear00)
						{
							useGear(gear00);
						}

						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 32)
					{
						stepBack();
						return;
					}

					changeSide(sp);
					attack(SKILL3);
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
				if (_isCanSkill2 && _mainTarget->isFlog() && isBaseDanger)
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
			if (_isCanGear00)
				useGear(gear00);
			stepOn();
		}
	}

	/**
	 * Callbacks
	 */

	void onSetTrap(const string &trapType) override
	{
		if (trapType == "KageBom")
		{
			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (isNotSameGroupAs(hero) && hero->isPlayerOrCom() && hero->getActionState() != State::DEAD && hero->_isVisable && !hero->_isSticking)
				{
					float distanceX = ccpSub(hero->getPosition(), getPosition()).x;
					float atkRangeX = kAttackRange;
					if (abs(distanceX) <= atkRangeX)
					{
						auto trap = Monster::create();
						trap->setMaster(this);
						trap->setID(CCString::create(trapType), CCString::create(kRoleMon), getGroup());
						trap->setPosition(ccp(hero->getPositionX(), hero->getPositionY()));
						trap->idle();
						trap->attack(NAttack);
						getGameLayer()->addChild(trap, -trap->getPositionY());
					}
				}
			}
		}
	}
};
