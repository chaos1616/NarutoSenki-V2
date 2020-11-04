#pragma once
#include "Characters.h"

class AI_Saso : public Hero
{
	void perform()
	{

		if (!this->findEnemy("Hero", winSize.width / 2 - 32, true))
		{
			if (!this->findEnemy("Flog", winSize.width / 2 - 32, true))
			{
				this->_mainTarget = NULL;
			}
		}

		CCPoint moveDirection;
		if (abs(ccpSub(_master->getPosition(), this->getPosition()).x) > 64)
		{
			if (this->getActionState() == State::IDLE || this->getActionState() == State::WALK || this->getActionState() == State::ATTACK)
			{
				moveDirection = ccpNormalize(ccpSub(_master->getPosition(), this->getPosition()));
				this->walk(moveDirection);
				return;
			}
		}

		if (_mainTarget)
		{

			CCPoint sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY()),
								ccp(this->getPositionX(), _originY ? _originY : this->getPositionY()));

			if (strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
			{

				if (abs(sp.x) > 48 || abs(sp.y) > 16)
				{
					if (this->_master->getActionState() == State::IDLE ||
						this->_master->getActionState() == State::WALK ||
						this->_master->getActionState() == State::ATTACK ||
						this->_master->getActionState() == State::SATTACK ||
						this->_master->getActionState() == State::OATTACK ||
						this->_master->getActionState() == State::O2ATTACK)
					{

						moveDirection = ccpNormalize(sp);
						this->walk(moveDirection);
					}
				}
				else
				{
					if (this->getActionState() == State::IDLE || this->getActionState() == State::WALK || this->getActionState() == State::ATTACK)
					{
						this->changeSide(sp);
						this->attack(NAttack);
					}
				}
				return;
			}
			else
			{

				if ((abs(sp.x) > 48 || abs(sp.y) > 16))
				{
					if (this->_master->getActionState() == State::IDLE ||
						this->_master->getActionState() == State::WALK ||
						this->_master->getActionState() == State::ATTACK ||
						this->_master->getActionState() == State::SATTACK ||
						this->_master->getActionState() == State::OATTACK ||
						this->_master->getActionState() == State::O2ATTACK)
					{
						moveDirection = ccpNormalize(sp);
						this->walk(moveDirection);
						return;
					}
				}
				else if (this->getActionState() == State::IDLE || this->getActionState() == State::WALK || this->getActionState() == State::ATTACK)
				{

					if (_isCanSkill1 && _mainTarget->getGP() < 5000)
					{
						this->changeSide(sp);

						this->attack(SKILL1);
						this->scheduleOnce(schedule_selector(Hero::enableSkill1), this->_sattackcoldDown1);
					}
					else
					{

						this->changeSide(sp);
						this->attack(NAttack);
					}
				}
				return;
			}
		}

		if (abs(ccpSub(_master->getPosition(), this->getPosition()).x) > winSize.width / 2 - 64)
		{
			CCPoint moveDirection = ccpNormalize(ccpSub(_master->getPosition(), this->getPosition()));
			this->walk(moveDirection);
			return;
		}
		else
		{

			if (this->_actionState == State::WALK ||
				this->_actionState == State::ATTACK)
			{
				this->idle();
			}
		}
	}
};
