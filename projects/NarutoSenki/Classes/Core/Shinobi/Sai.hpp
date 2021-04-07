#pragma once
#include "Hero.hpp"

class Sai : public Hero
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
				getHpPercent() < 0.5 && !_isBati && !_isWudi)
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
				setGear(gear05);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear01);
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

				if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && !_isBati && _mainTarget->getGP() < 5000 && !_mainTarget->_isBati && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 16)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else
					{
						changeSide(sp);

						attack(OUGIS2);
					}
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getGP() < 5000 && !_isBati)
				{

					if (abs(sp.x) > 64 || abs(sp.y) > 16)
					{
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
				else if (_isCanSkill2 && _mainTarget->getGP() < 5000 && !_isBati)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_isBati)
				{

					changeSide(sp);
					attack(OUGIS1);
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
							if (!_isBati)
							{
								changeSide(sp);
								attack(NAttack);
							}
						}
						idle();
						return;
					}
				}
				else if (_isCanSkill1 && !_isBati)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if ((abs(sp.x) > 8 || abs(sp.y) > 8) && _isBati)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_isCanSkill1 && !_skillChangeBuffValue)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (!_isBati)
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
				else if (!_isBati)
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
		if (_skillChangeBuffValue == 17)
		{
			setNAttackAction(createAnimation(skillSPC1Array, 10.0f, false, true));
		}
		else if (_skillChangeBuffValue == 18)
		{

			_isAllAttackLocked = true;
			_isBati = true;

			setWalkSpeed(320);
			_originSpeed = 320;

			lockOugisButtons();

			setIdleAction(createAnimation(skillSPC2Array, 5.0f, true, false));
			setWalkAction(createAnimation(skillSPC3Array, 5.0f, true, false));

			if (_hpBar)
			{
				_hpBar->setPositionY(120);
			}
			schedule(schedule_selector(Sai::setMonPer), 0.5f);
		}
	}

	void resumeAction(float dt)
	{

		if (_skillChangeBuffValue == 17)
		{
			setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
		}
		else if (_skillChangeBuffValue == 18)
		{

			_isBati = false;
			_isAllAttackLocked = false;
			_originSpeed = 224;

			setWalkSpeed(224);

			unlockOugisButtons();

			setIdleAction(createAnimation(idleArray, 5.0f, true, false));
			setWalkAction(createAnimation(walkArray, 10.0f, true, false));

			if (_actionState != State::DEAD)
			{
				_actionState = State::WALK;
				idle();
			}
			if (_hpBar)
			{
				_hpBar->setPositionY(getHeight());
			}

			unschedule(schedule_selector(Sai::setMonPer));
		}
		CharacterBase::resumeAction(dt);
	}

	void setActionResume()
	{

		if (_skillChangeBuffValue)
		{
			unschedule(schedule_selector(Sai::resumeAction));

			if (_skillChangeBuffValue == 17)
			{
				setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
			}
			else if (_skillChangeBuffValue == 18)
			{

				_isBati = false;
				_isAllAttackLocked = false;
				_originSpeed = 224;

				setWalkSpeed(224);

				lockOugisButtons();

				setIdleAction(createAnimation(idleArray, 5.0f, true, false));
				setWalkAction(createAnimation(walkArray, 10.0f, true, false));

				if (_hpBar)
				{
					_hpBar->setPositionY(getHeight());
				}
				unschedule(schedule_selector(Sai::setMonPer));
			}

			_skillChangeBuffValue = 0;
		}
	}
};
