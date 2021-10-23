#pragma once
#include "Hero.hpp"

class Jiraiya : public Hero
{
#define kJiraiya____ "Jiraiya"
#define kSageJiraiya "SageJiraiya"

	void setID(CCString *character, CCString *role, CCString *group) override
	{
		Hero::setID(character, role, group);

		match_char_exp(kJiraiya____, setAIHandler(Jiraiya::perform),
					   kSageJiraiya, setAIHandler(Jiraiya::perform_SageJiraiya));
	}

	// Jiraiya

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
				setGear(gear02);
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
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game)
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
					else if (_isCanSkill3 && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else if (_isCanSkill1 && _mainTarget->getGP() < 5000)
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
				if (_isCanSkill3 && _mainTarget->isFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL3);
				}
				else if (_isCanSkill1 && _mainTarget->isFlog())
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
			if (isFreeActionState())
				idle();
		}
		else
		{
			stepOn();
		}
	}

	// Jiraiya Sage

	void perform_SageJiraiya()
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
				setGear(gear02);
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
				if (_isCanSkill2 && _mainTarget->getGP() < 5000)
				{
					changeSide(sp);
					attack(SKILL2);
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
					else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_isCanOugis2)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(OUGIS2);
						return;
					}
					else if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill3 && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else if (_isCanSkill1 && _mainTarget->getGP() < 5000)
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
						else
						{
							changeSide(sp);
							attack(NAttack);
						}
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
				if (_isCanSkill3 && _mainTarget->isFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL3);
				}
				else if (_isCanSkill1 && _mainTarget->isFlog())
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
			if (isFreeActionState())
				idle();
		}
		else
		{
			stepOn();
		}
	}
};
