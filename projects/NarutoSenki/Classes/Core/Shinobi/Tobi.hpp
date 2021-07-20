#pragma once
#include "Hero.hpp"

class Tobi : public Hero
{
	void perform()
	{
		_mainTarget = nullptr;
		findEnemy2("Hero");
		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled&& _delegate->_enableGear)
		{
			if (getGearArray()->count() == 0)
				setGear(gear03);
			else if (getGearArray()->count() == 1)
				setGear(gear02);
			else if (getGearArray()->count() == 2)
				setGear(gear05);
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
					if (abs(sp.x) > 48 || abs(sp.y) > 16)
					{
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
					changeSide(sp);

					attack(OUGIS1);
					return;
				}
				else if (_isCanSkill3 && !_skillChangeBuffValue)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControlled && !_skillChangeBuffValue)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 32 && (_isCanSkill2 && _mainTarget->getHpPercent() < 0.5f))
					{
						stepBack();
						return;
					}

					if (_isCanSkill2 && _mainTarget->getGP() < 5000 && (_mainTarget->getHpPercent() < 0.5f || !_skillChangeBuffValue))
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else if (_isCanSkill1 && _mainTarget->getGP() < 5000 && (_mainTarget->getHpPercent() < 0.5f || !_skillChangeBuffValue))
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

						if (_isCanGear03)
						{
							useGear(gear03);
						}

						changeSide(sp);
						attack(NAttack);
					}

					return;
				}
			}
		}
		_mainTarget = nullptr;
		if (!findEnemy2(ROLE_FLOG))
			findEnemy2("Tower");

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
				if (_isCanSkill2 && strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) == 0 && isBaseDanger)
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
					if (_isCanGear03)
					{
						useGear(gear03);
					}
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
			stepOn();
		}
	}

	void changeAction()
	{
		setWalkAction(createAnimation(skillSPC1Array, 10.0f, true, false));

		setWalkSpeed(320);

		_originSpeed = 320;

		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			CharacterBase *tempHero = (CharacterBase *)pObject;
			if (strcmp(getGroup()->getCString(), tempHero->getGroup()->getCString()) != 0 && (strcmp(tempHero->getRole()->getCString(), "Player") == 0 || strcmp(tempHero->getRole()->getCString(), "Com") == 0) && tempHero->getActionState() != State::HURT && tempHero->getActionState() != State::DEAD)
			{
				float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
				if (distanceX < winSize.width / 2)
				{
					if (!tempHero->_isVisable)
					{
						if (strcmp(tempHero->getCharacter()->getCString(), "Konan") == 0 ||
							strcmp(tempHero->getCharacter()->getCString(), "Deidara") == 0)
						{
							tempHero->unschedule(schedule_selector(CharacterBase::disableBuff));
						}

						tempHero->setOpacity(255);
						tempHero->setVisible(true);

						if (tempHero->_hpBar)
						{
							tempHero->_hpBar->setVisible(true);
						}
						if (tempHero->_shadow)
						{
							tempHero->_shadow->setVisible(true);
						}

						tempHero->_isVisable = true;
					}
				}
			}
		}
	}

	void resumeAction(float dt)
	{
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));

		if (getOpacity() != 255)
		{
			setOpacity(255);
		}

		setWalkSpeed(224);

		_originSpeed = 224;

		if (getActionState() == State::WALK)
		{
			idle();
		}
		CharacterBase::resumeAction(dt);
	}

	void setActionResume()
	{
		if (_skillChangeBuffValue == 0)
			return;

		unschedule(schedule_selector(Tobi::resumeAction));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));

		if (getOpacity() != 255)
		{
			setOpacity(255);
		}

		setWalkSpeed(224);

		_originSpeed = 224;

		_skillChangeBuffValue = 0;
	}
};
