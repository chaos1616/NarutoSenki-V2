#pragma once
#include "Hero.hpp"

class Akamaru : public Hero
{
	void perform() override
	{
		if (notFindHero(kAttackRange - 32, true))
		{
			if (notFindFlog(kAttackRange - 32, true))
			{
				if (notFindTower(kAttackRange - 32, true))
				{
					_mainTarget = nullptr;
				}
			}
		}

		Vec2 moveDirection;

		if (abs((_master->getPosition() - getPosition()).x) > kAttackRange - 48)
		{
			if (isFreeState())
			{
				moveDirection = getDirByMoveTo(_master);
				walk(moveDirection);
				return;
			}
		}

		if (_mainTarget)
		{
			Vec2 sp = getDistanceToTarget();

			if (_mainTarget->isFlog())
			{
				if (abs(sp.x) > 48 || abs(sp.y) > 32)
				{
					moveDirection = sp.getNormalized();
					walk(moveDirection);
				}
				else
				{
					if (isFreeState())
					{
						changeSide(sp);
						attack(NAttack);
					}
				}
			}
			else
			{
				if (abs(sp.x) > 48 || abs(sp.y) > 32)
				{
					moveDirection = sp.getNormalized();
					walk(moveDirection);
				}
				else
				{
					if (isFreeState())
					{
						if (_master->_isCanSkill2 && _mainTarget->getDEF() < 5000 &&
							(_master->_isControlled || _master->_isAI == true) &&
							_master->isFreeState())
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
			}

			return;
		}

		if (abs((_master->getPosition() - getPosition()).x) > kAttackRange - 64)
		{
			Vec2 moveDirection = getDirByMoveTo(_master);
			walk(moveDirection);
			return;
		}
		else
		{
			stepOn();
		}
	}

	void changeAction() override
	{
		_powerUPBuffValue = 360;
		setNAttackValue(getNAttackValue() + _powerUPBuffValue);
		setActionTo<ActionFlag::Idle, ActionFlag::Spc01>();
		setActionTo<ActionFlag::Walk, ActionFlag::Spc02>();
		setActionTo<ActionFlag::NAttack, ActionFlag::Spc03>();

		if (_state == State::NATTACK)
		{
			_state = State::WALK;
			idle();
		}
	}

	void resumeAction(float dt) override
	{
		if (_powerUPBuffValue)
		{
			setNAttackValue(getNAttackValue() - _powerUPBuffValue);
			setActionTo<ActionFlag::Idle, ActionFlag::Idle>();
			setActionTo<ActionFlag::Walk, ActionFlag::Walk>();
			setActionTo<ActionFlag::NAttack, ActionFlag::NAttack>();
			_powerUPBuffValue = 0;

			if (isFreeState())
			{
				_state = State::WALK;
				idle();
			}
		}
		Unit::resumeAction(dt);
	}

	void dealloc() override
	{
		_master->setActionResume();

		Hero::dealloc();
	}
};
