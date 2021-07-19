#pragma once
#include "Hero.hpp"

class Parents : public Hero
{
	void perform()
	{
		if (!findEnemy("Hero", winSize.width / 2 - 32, true))
		{
			if (!findEnemy(ROLE_FLOG, 48, true))
			{
				if (!findEnemy("Tower", 48, true))
				{
					_mainTarget = nullptr;
				}
			}
		}

		CCPoint moveDirection;

		if (abs(ccpSub(_master->getPosition(), getPosition()).x) > 9 && !_skillChangeBuffValue)
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
			CCPoint sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY()),
								ccp(getPositionX(), _originY ? _originY : getPositionY()));

			if (strcmp(_mainTarget->getRole()->getCString(), ROLE_FLOG) == 0 || strcmp(_mainTarget->getRole()->getCString(), "Tower") == 0)
			{
				if (abs(sp.x) > 48 || abs(sp.y) > 32)
				{
				}
				else
				{
					if ((getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::NATTACK) && !_skillChangeBuffValue)
					{
						changeSide(sp);
						attack(NAttack);
					}
				}
				return;
			}
			else
			{
				if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::NATTACK)
				{
					if (_master->getActionState() == State::IDLE ||
						_master->getActionState() == State::WALK ||
						_master->getActionState() == State::NATTACK)
					{
						if (_master->_isCanSkill3 && _mainTarget->getGP() < 5000 && (_master->_isControlled || _master->_isAI == true) && !_skillChangeBuffValue)
						{
							changeSide(sp);

							_master->attack(SKILL3);
						}
						else if (abs(sp.x) > 48 || abs(sp.y) > 32)
						{
							if (_skillChangeBuffValue && getActionState() != State::NATTACK)
							{
								moveDirection = ccpNormalize(sp);
								walk(moveDirection);
								return;
							}
						}
						else
						{
							if (_master->_isCanSkill2 && _mainTarget->getGP() < 5000 && (_master->_isControlled || _master->_isAI == true) && !_skillChangeBuffValue)
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

	void changeAction()
	{
		settempAttackValue1(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString())));
		setnAttackValue(CCString::createWithFormat("%d", 2460));

		_isOnlySkillLocked = true;

		_nattackRangeX = 16;
		_nattackRangeY = 48;

		setWalkAction(createAnimation(skillSPC1Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC2Array, 10.0f, false, true));

		if (strcmp(getMaster()->getRole()->getCString(), "Player") == 0)
		{
			if (_delegate->getHudLayer()->skill2Button)
			{
				_delegate->getHudLayer()->skill2Button->setLock();
			}
		}
		setWalkSpeed(460);
	}

	void setActionResume()
	{
		if (_skillChangeBuffValue)
		{
			if (gettempAttackValue1())
			{
				setnAttackValue(CCString::createWithFormat("%d", to_int(gettempAttackValue1()->getCString())));
				settempAttackValue1(nullptr);
			}
			_isOnlySkillLocked = false;

			_nattackRangeX = 16;
			_nattackRangeY = 48;

			setWalkAction(createAnimation(walkArray, 10.0f, true, false));
			setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));

			_skillChangeBuffValue = 0;

			setWalkSpeed(224);

			_originSpeed = 224;

			if (strcmp(getMaster()->getRole()->getCString(), "Player") == 0)
			{
				if (_delegate->getHudLayer()->skill2Button)
				{
					_delegate->getHudLayer()->skill2Button->unLock();
				}
			}
		}
	}
};
