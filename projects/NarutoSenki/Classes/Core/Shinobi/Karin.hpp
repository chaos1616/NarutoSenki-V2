#pragma once
#include "Hero.hpp"

class Karin : public Hero
{
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

		if (getCoin() >= 500 && !_isControlled && getGameLayer()->_enableGear)
		{
			if (getGearArray().size() == 0)
				setGear(gear06);
			else if (getGearArray().size() == 1)
				setGear(gear01);
			else if (getGearArray().size() == 2)
				setGear(gear07);
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
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 16)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (getHpPercent() < 0.9 && _isCanOugis1 && !_isControlled && !_buffStartTime && !_isHealling)
				{
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getGP() < 5000)
				{
					if ((abs(sp.x) > 128 || abs(sp.y) > 16))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(SKILL3);
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
					if (abs(sp.x) > 96 || abs(sp.y) > 32)
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
					else if (_isCanSkill1)
					{
						changeSide(sp);
						attack(SKILL1);
					}
					else
					{
						if (abs(sp.x) > 32 || abs(sp.y) > 32)
						{
							moveDirection = ccpNormalize(sp);
							walk(moveDirection);
							return;
						}
						changeSide(sp);
						attack(NAttack);
					}

					return;
				}
			}
		}

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
				if (_isCanSkill1 && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanSkill2 && _mainTarget->isFlog() && isBaseDanger)
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

	/**
	 * Callbacks
	 */

	void onSetTrap(const string &trapType) override
	{
		if (trapType == "Kusuri")
		{
			for (int i = 0; i < 3; i++)
			{
				auto trap = Bullet::create();
				trap->setAnchorPoint(ccp(0.5f, 0));
				trap->setMaster(this);
				trap->setID(CCString::create(trapType), CCString::create(kRoleMon), getGroup());

				if (i == 0)
					trap->setPosition(ccp(getPositionX() + (_isFlipped ? -24 : 24), getPositionY() - 24));
				else if (i == 1)
					trap->setPosition(ccp(getPositionX() + (_isFlipped ? 24 : -24), getPositionY() - 24));
				else if (i == 2)
					trap->setPosition(ccp(getPositionX(), getPositionY() + 24));

				trap->attack(NAttack);
				getGameLayer()->addChild(trap, -trap->getPositionY());
			}
		}
	}
};
