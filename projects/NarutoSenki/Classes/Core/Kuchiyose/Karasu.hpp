#pragma once
#include "Hero.hpp"

class Karasu : public Hero
{
	void perform()
	{
		if (notFindHero(winSize.width / 2 - 32, true))
		{
			if (notFindFlog(winSize.width / 2 - 32, true))
			{
				_mainTarget = nullptr;
			}
		}

		if (_mainTarget)
		{
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
			CCPoint sp = getDistanceToTarget();

			if (_mainTarget->isFlog())
			{
				if (abs(sp.x) > 32 || abs(sp.y) > 32)
				{
					if (_master->getActionState() == State::IDLE ||
						_master->getActionState() == State::WALK ||
						_master->getActionState() == State::NATTACK ||
						_master->getActionState() == State::SATTACK ||
						_master->getActionState() == State::OATTACK ||
						_master->getActionState() == State::O2ATTACK)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
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
				if (abs(sp.x) > 32 || abs(sp.y) > 16)
				{
					if (_master->getActionState() == State::IDLE ||
						_master->getActionState() == State::WALK ||
						_master->getActionState() == State::NATTACK ||
						_master->getActionState() == State::SATTACK ||
						_master->getActionState() == State::OATTACK ||
						_master->getActionState() == State::O2ATTACK)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
				}
				else if (isFreeActionState())
				{
					if (_master->isFreeActionState())
					{
						if (_master->_isCanSkill2 && _mainTarget->getGP() < 5000 && (_master->_isControlled || _master->_isAI == true))
						{
							changeSide(sp);

							if (_master->isNotPlayer())
							{
								_master->attack(SKILL2);
							}
							else if (_master->isPlayer())
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
			if (
				_master->getActionState() == State::WALK ||
				_master->getActionState() == State::NATTACK ||
				_master->getActionState() == State::SATTACK ||
				_master->getActionState() == State::OATTACK)
			{
				stepOn();
			}
			else
			{
				if (_actionState == State::WALK ||
					_actionState == State::NATTACK)
				{
					idle();
				}
			}
		}
	}
};
