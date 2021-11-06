#pragma once
#include "Hero.hpp"

class Sakura : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryBuyGear(gear00, gear04, gear08);

		if (needBackToTowerToRestoreHP())
			return;

		if (_mainTarget && (battleCondiction >= 0 || _isCanOugis1 || _isCanOugis2))
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeActionState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && !_skillChangeBuffValue && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking)
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
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isControlled)
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
					else if (_isCanSkill3 && !_skillChangeBuffValue && getHpPercent() > 0.5f)
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
			if (notFindFlogHalf())
			{
				findTowerHalf();
			}
		}
		else
		{
			_mainTarget = nullptr;
			findTowerHalf();
		}

		if (_mainTarget)
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (isFreeActionState())
			{
				if (_isCanSkill1 && getHpPercent() < 0.9)
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_mainTarget->isFlog() && _isCanSkill2)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_mainTarget->isTower() && _isCanSkill3 && !_skillChangeBuffValue)
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

		checkHealingState();
	}
};
