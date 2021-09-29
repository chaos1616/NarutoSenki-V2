#pragma once
#include "Hero.hpp"

class Akamaru : public Hero
{
	void perform()
	{
		if (notFindHero(winSize.width / 2 - 32, true))
		{
			if (notFindFlog(winSize.width / 2 - 32, true))
			{
				if (notFindTower(winSize.width / 2 - 32, true))
				{
					_mainTarget = nullptr;
				}
			}
		}

		CCPoint moveDirection;

		if (abs(ccpSub(_master->getPosition(), getPosition()).x) > winSize.width / 2 - 48)
		{
			if (isFreeActionState())
			{
				moveDirection = getDirByMoveTo(_master);
				walk(moveDirection);
				return;
			}
		}

		if (_mainTarget)
		{
			CCPoint sp = getDistanceToTarget();

			if (_mainTarget->isFlog())
			{
				if (abs(sp.x) > 48 || abs(sp.y) > 32)
				{
					moveDirection = ccpNormalize(sp);
					walk(moveDirection);
				}
				else
				{
					if (isFreeActionState())
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
					if (isFreeActionState())
					{
						if (_master->_isCanSkill2 && _mainTarget->getGP() < 5000 &&
							(_master->_isControlled || _master->_isAI == true) &&
							_master->isFreeActionState())
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
			CCPoint moveDirection = getDirByMoveTo(_master);
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
		setnAttackValue(CCString::createWithFormat("%d", getNAttackValue() + _powerUPBuffValue));
		setIdleAction(createAnimation(skillSPC1Array, 5.0f, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));

		if (_actionState == State::NATTACK)
		{
			_actionState = State::WALK;
			idle();
		}
	}

	void resumeAction(float dt)
	{
		if (_powerUPBuffValue)
		{
			setnAttackValue(CCString::createWithFormat("%d", getNAttackValue() - _powerUPBuffValue));
			setIdleAction(createAnimation(idleArray, 5.0f, true, false));
			setWalkAction(createAnimation(walkArray, 10.0f, true, false));
			setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
			_powerUPBuffValue = 0;

			if (isFreeActionState())
			{
				_actionState = State::WALK;
				idle();
			}
		}
		CharacterBase::resumeAction(dt);
	}
};
