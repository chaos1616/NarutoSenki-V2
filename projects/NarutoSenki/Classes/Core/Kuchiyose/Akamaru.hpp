#pragma once
#include "Hero.hpp"

class Akamaru : public Hero
{
	void perform()
	{
		if (!findEnemy("Hero", winSize.width / 2 - 32, true))
		{
			if (!findEnemy(ROLE_FLOG, winSize.width / 2 - 32, true))
			{
				if (!findEnemy("Tower", winSize.width / 2 - 32, true))
				{
					_mainTarget = nullptr;
				}
			}
		}

		CCPoint moveDirection;

		if (abs(ccpSub(_master->getPosition(), getPosition()).x) > winSize.width / 2 - 48)
		{
			if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::NATTACK)
			{
				moveDirection = ccpNormalize(ccpSub(_master->getPosition(), getPosition()));
				walk(moveDirection);
				return;
			}
		}

		if (_mainTarget)
		{
			CCPoint sp;
			if (_mainTarget->_originY)
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			else
				sp = ccpSub(_mainTarget->getPosition(), getPosition());

			if (strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) == 0)
			{
				if (abs(sp.x) > 48 || abs(sp.y) > 32)
				{
					moveDirection = ccpNormalize(sp);
					walk(moveDirection);
				}
				else
				{
					if (getActionState() == State::IDLE || getActionState() == State::WALK || _actionState == State::NATTACK)
					{
						changeSide(sp);
						attack(NAttack);
					}
				}
				return;
			}
			else
			{
				if (abs(sp.x) > 48 || abs(sp.y) > 32)
				{
					moveDirection = ccpNormalize(sp);
					walk(moveDirection);
					return;
				}
				else
				{
					if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::NATTACK)
					{
						if (_master->_isCanSkill2 && _mainTarget->getGP() < 5000 && (_master->_isControlled || _master->_isAI == true) &&
							(_master->getActionState() == State::IDLE || _master->getActionState() == State::WALK || _master->getActionState() == State::NATTACK))
						{
							changeSide(sp);
							if (strcmp(_master->getRole()->getCString(), "Player") != 0)
							{
								_master->attack(SKILL2);
							}
							else if (strcmp(_master->getRole()->getCString(), "Player") == 0)
							{
								_master->attack(SKILL2);
							}
						}
						else
						{
							changeSide(sp);
							attack(NAttack);
						}
					}
				}

				return;
			}
		}

		if (abs(ccpSub(_master->getPosition(), getPosition()).x) > winSize.width / 2 - 64)
		{
			CCPoint moveDirection = ccpNormalize(ccpSub(_master->getPosition(), getPosition()));
			walk(moveDirection);
			return;
		}
		else
		{
			stepOn();
		}
	}

	void changeAction()
	{
		_powerUPBuffValue = 360;
		setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) + _powerUPBuffValue));
		setIdleAction(createAnimation(skillSPC1Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));

		if (getActionState() == State::NATTACK)
		{
			_actionState = State::WALK;
			idle();
		}
	}

	void resumeAction(float dt)
	{
		if (_powerUPBuffValue)
		{
			setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) - _powerUPBuffValue));
			setIdleAction(createAnimation(idleArray, 5.0f, true, false));
			setWalkAction(createAnimation(walkArray, 10.0f, true, false));
			setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
			_powerUPBuffValue = 0;

			if (_actionState == State::IDLE ||
				_actionState == State::WALK ||
				_actionState == State::NATTACK)
			{
				_actionState = State::WALK;
				idle();
			}
		}
		CharacterBase::resumeAction(dt);
	}
};
