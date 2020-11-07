#pragma once
#include "Characters.h"

class AI_Parents : public Hero
{
	void perform()
	{

		if (!findEnemy("Hero", winSize.width / 2 - 32, true))
		{

			if (!findEnemy("Flog", 48, true))
			{
				if (!findEnemy("Tower", 48, true))
				{
					_mainTarget = NULL;
				}
			}
		}

		CCPoint moveDirection;

		if (abs(ccpSub(_master->getPosition(), getPosition()).x) > 9 && !_skillChangeBuffValue)
		{
			if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::ATTACK)
			{
				moveDirection = ccpNormalize(ccpSub(_master->getPosition(), getPosition()));
				walk(moveDirection);
				return;
			}
		}
		if (_mainTarget)
		{

			CCPoint sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY()),
								ccp(getPositionX(), _originY ? _originY : getPositionY()));

			if (strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0 || strcmp(_mainTarget->getRole()->getCString(), "Tower") == 0)
			{

				if (abs(sp.x) > 48 || abs(sp.y) > 32)
				{
				}
				else
				{
					if ((getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::ATTACK) && !_skillChangeBuffValue)
					{
						changeSide(sp);
						attack(NAttack);
					}
				}
				return;
			}
			else
			{
				if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::ATTACK)
				{
					if (_master->getActionState() == State::IDLE ||
						_master->getActionState() == State::WALK ||
						_master->getActionState() == State::ATTACK)
					{

						if (_master->_isCanSkill3 && _mainTarget->getGP() < 5000 && (_master->_isControled || _master->_isAI == true) && !_skillChangeBuffValue)
						{

							changeSide(sp);

							_master->attack(SKILL3);
						}
						else if (abs(sp.x) > 48 || abs(sp.y) > 32)
						{
							if (_skillChangeBuffValue && getActionState() != State::ATTACK)
							{
								moveDirection = ccpNormalize(sp);
								walk(moveDirection);
								return;
							}
						}
						else
						{

							if (_master->_isCanSkill2 && _mainTarget->getGP() < 5000 && (_master->_isControled || _master->_isAI == true) && !_skillChangeBuffValue)
							{

								changeSide(sp);
								_master->attack(SKILL2);
							}
							else
							{

								changeSide(sp);
								attack(NAttack);
							}
						}
					}
				}

				return;
			}
		}

		if (abs(ccpSub(_master->getPosition(), getPosition()).x) > 9)
		{
			if (getActionState() == State::IDLE || getActionState() == State::WALK)
			{
				moveDirection = ccpNormalize(ccpSub(_master->getPosition(), getPosition()));
				walk(moveDirection);
				return;
			}
		}

		if (_actionState == State::WALK)
		{
			idle();
		}
	}
};
