#pragma once
#include "Hero.hpp"

class Karasu : public Hero
{
	void perform()
	{
		if (!findEnemy("Hero", winSize.width / 2 - 32, true))
		{
			if (!findEnemy("Flog", winSize.width / 2 - 32, true))
			{
				_mainTarget = nullptr;
			}
		}

		if (_mainTarget)
		{
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
			CCPoint sp;
			if (_mainTarget->_originY)
			{
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			}
			else
			{
				sp = ccpSub(_mainTarget->getPosition(), getPosition());
			}

			if (strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
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
					if (getActionState() == State::IDLE ||
						getActionState() == State::WALK ||
						getActionState() == State::NATTACK)
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
				else if (getActionState() == State::IDLE ||
						 getActionState() == State::WALK ||
						 getActionState() == State::NATTACK)
				{

					if (_master->getActionState() == State::IDLE ||
						_master->getActionState() == State::WALK ||
						_master->getActionState() == State::NATTACK)
					{

						if (_master->_isCanSkill2 && _mainTarget->getGP() < 5000 && (_master->_isControlled || _master->_isAI == true))
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
