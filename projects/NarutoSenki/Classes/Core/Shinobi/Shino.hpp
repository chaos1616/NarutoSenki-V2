#pragma once
#include "Hero.hpp"

class Shino : public Hero
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
				setGear(gear01);
			else if (getGearArray()->count() == 2)
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
				if (_isCanGear00)
				{
					useGear(gear00);
				}
				if (stepBack2())
					return;
			}
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
				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 16)
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
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 16)
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
				}
				else if (_isCanSkill2 && _mainTarget->getGP() < 5000)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getGP() < 5000)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 16)
					{
						if (_isCanGear00)
						{
							useGear(gear00);
						}
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else
					{
						changeSide(sp);
						attack(SKILL3);
					}
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControlled)
				{
					if (abs(sp.x) < 160)
					{
						stepBack2();
						return;
					}
					else
					{
						if (_skillChangeBuffValue)
						{
							changeSide(sp);
							attack(NAttack);
						}
						else
						{
							idle();
						}

						return;
					}
				}
				else if (_isCanSkill1)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if (to_uint(getMaxHP()->getCString()) - to_uint(getHP()->getCString()) >= 3000 &&
						to_int(getCoin()->getCString()) >= 50 && !_isHealling && _isCanItem1)
					{
						setItem(Item1);
					}
					if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_skillChangeBuffValue)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(NAttack);

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
				if (_isCanSkill3 && strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) == 0 && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL3);
				}
				else if (_isCanSkill2 && strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) == 0 && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanSkill1 && strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) == 0)
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
			if (_isCanGear00)
				useGear(gear00);
			stepOn();
		}
	}

	void changeAction()
	{
		setNAttackAction(createAnimation(skillSPC1Array, 10.0f, false, true));
	}

	void resumeAction(float dt)
	{
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
		CharacterBase::resumeAction(dt);
	}
};
