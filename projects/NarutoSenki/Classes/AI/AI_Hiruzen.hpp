#pragma once
#include "Characters.h"

class AI_Hiruzen : public Hero
{
	void perform()
	{

		_mainTarget = NULL;
		findEnemy2("Hero");
		if (atoi(getCoin()->getCString()) >= 500 && !_isControled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear00);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear02);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear08);
			}
		}

		if (checkRetri())
		{
			if (_mainTarget != NULL)
			{
				if (stepBack2())
				{
					return;
				}
			}
			else
			{
				if (_isCanGear00)
				{
					useGear(gear00);
				}
				if (stepBack())
				{
					return;
				}
			}
		}

		if (isBaseDanger && checkBase() && !_isControled)
		{
			bool needBack = false;
			if (strcmp(Akatsuki, getGroup()->getCString()) == 0)
			{
				if (getPositionX() < 85 * 32)
				{
					needBack = true;
				}
			}
			else
			{
				if (getPositionX() > 11 * 32)
				{
					needBack = true;
				}
			}

			if (needBack)
			{
				if (_isCanGear00)
				{
					useGear(gear00);
				}
				if (stepBack2())
				{
					return;
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

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
			{

				if (_isCanOugis2 && !_isControled && _delegate->_isOugis2Game && !_isBati && atoi(_mainTarget->getHP()->getCString()) < 10000 && !_mainTarget->_isCanGear06)
				{
					if (abs(sp.x) < 32)
					{
						stepBack();
						return;
					}
					else if (abs(sp.x) > 96 || abs(sp.y) > 32)
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
				else if (_isCanOugis1 && !_isControled && _mainTarget->getGP() < 5000 && !_isBati)
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
				else if (_isCanSkill3 && _mainTarget->getGP() < 5000 && !_isBati && !_skillChangeBuffValue)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControled)
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
					if (abs(sp.x) > 96 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanSkill1 && _mainTarget->getGP() < 5000 && !_isBati)
					{
						if ((abs(sp.x) > 32 || abs(sp.y) > 32))
						{

							moveDirection = ccpNormalize(sp);
							walk(moveDirection);
							return;
						}
						changeSide(sp);
						attack(SKILL1);
					}
					else if (_isCanSkill2 && _mainTarget->getGP() < 5000 && !_isBati)
					{
						if (abs(sp.x) < 32)
						{
							stepBack();
							return;
						}
						changeSide(sp);
						attack(SKILL2);
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
		_mainTarget = NULL;
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

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
			{
				if (strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0 && _isCanSkill1 && !_isBati)
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanSkill2 && _mainTarget->getGP() < 5000 && !_isBati && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0 && isBaseDanger)
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
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
};
