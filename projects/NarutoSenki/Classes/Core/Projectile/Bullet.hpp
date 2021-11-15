#pragma once
#include "CharacterBase.h"
#include "HPBar.h"

// TODO: Rename to 'Projectile'
class Bullet : public CharacterBase
{
public:
	CREATE_FUNC(Bullet);

	bool init()
	{
		RETURN_FALSE_IF(!Sprite::init());

		scheduleUpdate();

		return true;
	}

	void setID(const string &name, Role role, Group group) override
	{
		clearActionData();
		setName(name);
		setRole(role);
		setGroup(group);

		auto fpath = format("Unit/Projectile/{}.toml", name);
		auto metadata = UnitParser::fromToml(fpath);
		genActionBy(metadata);
		// init action
		setAction(ActionFlag::Idle | ActionFlag::Dead | ActionFlag::NAttack);
	}

	void setMove(int length, float delay, bool isReverse)
	{
		Vec2 direction = Vec2(_isFlipped ? getPosition().x - length : getPosition().x + length, getPositionY());
		Vec2 direction2 = getPosition();
		auto mv = MoveTo::create(delay, direction);
		auto call = CallFunc::create(std::bind(&Bullet::dealloc, this));
		Action *moveAction;

		if (!isReverse)
		{
			moveAction = newSequence(mv, call);
		}
		else
		{
			auto mv2 = MoveTo::create(delay, direction2);
			moveAction = newSequence(mv, mv2, call);
		}

		runAction(moveAction);
	}

	void setEaseIn(int length, float delay)
	{
		Vec2 direction = Vec2(_isFlipped ? getPosition().x - length : getPosition().x + length, getPositionY());
		auto mv = MoveTo::create(1.0f, direction);
		auto eo = EaseIn::create(mv, delay);
		auto call = CallFunc::create(std::bind(&Bullet::dealloc, this));
		auto moveAction = newSequence(eo, call);
		runAction(moveAction);
	}

	void setAttack(float dt)
	{
		attack(NAttack);
	}

protected:
	void dealloc()
	{
		stopAllActions();

		if (getName() == ProjectileEnum::Amaterasu)
		{
			auto call = CallFunc::create(std::bind(&Bullet::removeFromParent, this));
			auto seq = newSequence(getDeadAction(), call);
			runAction(seq);
		}
		else
		{
			if (getName() == ProjectileEnum::HiraishinKunai)
			{
				if (_master->getState() == State::SATTACK)
				{
					_master->setState(State::NATTACK);
					_master->_markPoint = Vec2(getPositionX(), _originY);
					_master->changeAction2();
					_master->_isCanSkill2 = true;
					_master->sAttack(SKILL2);
				}
			}

			if (_master)
				_master->removeMon(this);
			removeFromParent();
		}
	}
};
