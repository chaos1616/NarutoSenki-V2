#pragma once
#include "Hero.hpp"

class Parents : public Hero
{
	void perform() override
	{
		if (notFindHero(kAttackRange - 32, true))
		{
			if (notFindFlog(48, true))
			{
				if (notFindTower(48, true))
				{
					_mainTarget = nullptr;
				}
			}
		}

		Vec2 moveDirection;

		if (abs(ccpSub(_master->getPosition(), getPosition()).x) > 9 && !_skillChangeBuffValue)
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
			Vec2 sp = ccpSub(Vec2(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY()),
								Vec2(getPositionX(), _originY ? _originY : getPositionY()));

			if (_mainTarget->isFlog() || _mainTarget->isTower())
			{
				if (abs(sp.x) > 48 || abs(sp.y) > 32)
				{
				}
				else
				{
					if ((isFreeActionState()) && !_skillChangeBuffValue)
					{
						changeSide(sp);
						attack(NAttack);
					}
				}
				return;
			}
			else
			{
				if (isFreeActionState())
				{
					if (_master->isFreeActionState())
					{
						if (_master->_isCanSkill3 && _mainTarget->getGP() < 5000 && (_master->_isControlled || _master->_isAI == true) && !_skillChangeBuffValue)
						{
							changeSide(sp);

							_master->attack(SKILL3);
						}
						else if (abs(sp.x) > 48 || abs(sp.y) > 32)
						{
							if (_skillChangeBuffValue && _actionState != State::NATTACK)
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
			if (_actionState == State::IDLE || _actionState == State::WALK)
			{
				moveDirection = getDirByMoveTo(_master);
				walk(moveDirection);
				return;
			}
		}

		if (_actionState == State::WALK)
			idle();
	}

	void changeAction() override
	{
		setTempAttackValue1(getNAttackValue());
		setNAttackValue(2460);

		_isOnlySkillLocked = true;

		_nAttackRangeX = 16;
		_nAttackRangeY = 48;

		setWalkAction(createAnimation(skillSPC1Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC2Array, 10.0f, false, true));

		if (_master->isPlayer())
		{
			getGameLayer()->getHudLayer()->skill2Button->setLock();
		}
		setWalkSpeed(460);
	}

	void setActionResume() override
	{
		if (_skillChangeBuffValue == 0)
			return;

		if (hasTempAttackValue1())
		{
			setNAttackValue(getTempAttackValue1());
			setTempAttackValue1(0);
		}
		_isOnlySkillLocked = false;

		_nAttackRangeX = 16;
		_nAttackRangeY = 48;

		setWalkAction(createAnimation(walkArray, 10.0f, true, false));
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));

		_skillChangeBuffValue = 0;

		setWalkSpeed(224);
		_originSpeed = 224;

		if (_master->isPlayer())
		{
			getGameLayer()->getHudLayer()->skill2Button->unLock();
		}
	}

	void dealloc() override
	{
		_master->setActionResume();

		Hero::dealloc();
	}
};
