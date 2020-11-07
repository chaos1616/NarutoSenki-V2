#pragma once
#include "Characters.h"

class AI_Sanshouuo : public Hero
{
	void perform()
	{

		if (!findEnemy("Hero", winSize.width / 2 - 32, true))
		{
			if (!findEnemy("Flog", winSize.width / 2 - 32, true))
			{
				_mainTarget = NULL;
			}
		}

		if (_mainTarget)
		{
			CCPoint moveDirection;
			if (abs(ccpSub(_master->getPosition(), getPosition()).x) > winSize.width / 2 - 64)
			{
				if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::ATTACK)
				{
					moveDirection = ccpNormalize(ccpSub(_master->getPosition(), getPosition()));
					walk(moveDirection);
					return;
				}
			}

			CCPoint sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY()),
								ccp(getPositionX(), _originY ? _originY : getPositionY()));

			if (strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
			{

				if (abs(sp.x) > 32 || abs(sp.y) > 32)
				{
					if (_master->getActionState() == State::IDLE ||
						_master->getActionState() == State::WALK ||
						_master->getActionState() == State::ATTACK ||
						_master->getActionState() == State::SATTACK ||
						_master->getActionState() == State::OATTACK ||
						_master->getActionState() == State::O2ATTACK)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
					}
				}
				else
				{
					if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::ATTACK)
					{
						changeSide(sp);
						attack(NAttack);
					}
				}
				return;
			}
			else
			{

				if (abs(sp.x) > 96 || abs(sp.y) > 32)
				{
					if (_master->getActionState() == State::IDLE ||
						_master->getActionState() == State::WALK ||
						_master->getActionState() == State::ATTACK ||
						_master->getActionState() == State::SATTACK ||
						_master->getActionState() == State::OATTACK ||
						_master->getActionState() == State::O2ATTACK)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
				}
				else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_isCanSkill1)
				{
					if (_master->getActionState() == State::WALK ||
						_master->getActionState() == State::ATTACK ||
						_master->getActionState() == State::SATTACK ||
						_master->getActionState() == State::OATTACK ||
						_master->getActionState() == State::O2ATTACK)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
				}
				else if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::ATTACK)
				{

					if (_isCanSkill1 && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);

						attack(SKILL1);
						scheduleOnce(schedule_selector(Hero::enableSkill1), _sattackcoldDown1);
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

		if (abs(ccpSub(_master->getPosition(), getPosition()).x) > winSize.width / 2 - 64)
		{
			CCPoint moveDirection = ccpNormalize(ccpSub(_master->getPosition(), getPosition()));
			walk(moveDirection);
			return;
		}
		else
		{
			if (_master->getActionState() == State::WALK ||
				_master->getActionState() == State::ATTACK ||
				_master->getActionState() == State::SATTACK ||
				_master->getActionState() == State::OATTACK)
			{
				stepOn();
			}
			else
			{
				if (_actionState == State::WALK || _actionState == State::ATTACK)
				{
					idle();
				}
			}
		}
	}
};
