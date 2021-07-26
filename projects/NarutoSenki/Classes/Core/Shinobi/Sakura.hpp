#pragma once
#include "Hero.hpp"

class Sakura : public Hero
{
	void perform()
	{
		_mainTarget = nullptr;
		findHero();
		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled&& _delegate->_enableGear)
		{
			if (getGearArray()->count() == 0)
				setGear(gear00);
			else if (getGearArray()->count() == 1)
				setGear(gear04);
			else if (getGearArray()->count() == 2)
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

		if (_mainTarget && (battleCondiction >= 0 || _isCanOugis1 || _isCanOugis2))
		{
			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			else
				sp = ccpSub(_mainTarget->getPosition(), getPosition());

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && !_skillChangeBuffValue && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 16)
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
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_skillChangeBuffValue)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 16)
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
				else if (getHpPercent() < 0.9 && _isCanSkill1)
				{
					attack(SKILL1);
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if ((abs(sp.x) > 64 || abs(sp.y) > 32) && (!_isCanSkill2 || _mainTarget->getGP() < 5000))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) > 32 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanSkill2 && !_skillChangeBuffValue && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else if (_isCanSkill3 && !_skillChangeBuffValue && getHpPercent() > 0.5)
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
			if (!findFlog())
			{
				findTower();
			}
		}
		else
		{
			_mainTarget = nullptr;
			findTower();
		}

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
				if (_isCanSkill1 && getHpPercent() < 0.9)
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) == 0 && _isCanSkill2)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (strcmp(_mainTarget->getRole()->getCString(), "Tower") == 0 && _isCanSkill3 && !_skillChangeBuffValue)
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
				idle();
		}
		else
		{
			if (_isCanGear00)
				useGear(gear00);
			stepOn();
		}
	}
};
