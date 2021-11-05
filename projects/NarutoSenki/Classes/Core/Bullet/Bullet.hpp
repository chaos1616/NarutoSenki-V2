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
		RETURN_FALSE_IF(!CCSprite::init());

		scheduleUpdate();

		return true;
	}

	void setID(const string &name, const string &role, const string &group)
	{
		setName(name);
		setRole(role);
		setGroup(group);

		CCArray *animationArray = CCArray::create();
		auto filePath = format("Element/Bullet/{}.xml", name);
		KTools::readXMLToArray(filePath, animationArray);

		CCArray *tmpAction = (CCArray *)(animationArray->objectAtIndex(0));
		CCArray *tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		idleArray = (CCArray *)(tmpAction->objectAtIndex(1));

		// init nAttack data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(7));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));

		uint32_t tmpValue;
		uint32_t tmpCD;
		int tmpCombatPoint;

		readData(tmpData, _nAttackType, tmpValue, _nAttackRangeX, _nAttackRangeY, tmpCD, tmpCombatPoint);
		setNAttackValue(tmpValue);
		nattackArray = (CCArray *)(tmpAction->objectAtIndex(1));

		if (getName() == ProjectileEnum::Amaterasu)
		{
			// init DeadFrame
			tmpAction = (CCArray *)(animationArray->objectAtIndex(6));
			deadArray = (CCArray *)(tmpAction->objectAtIndex(1));
		}

		setCoin(50);

		initAction();
	}

	void initAction()
	{
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setNAttackAction(createAnimation(nattackArray, 10.0f, true, false));
		if (getName() == ProjectileEnum::Amaterasu || getName() == ProjectileEnum::SusanoTama)
		{
			setDeadAction(createAnimation(deadArray, 10.0f, false, false));
		}
	}

	void setMove(int length, float delay, bool isReverse)
	{
		CCPoint direction = ccp(_isFlipped ? getPosition().x - length : getPosition().x + length, getPositionY());
		CCPoint direction2 = getPosition();
		auto mv = CCMoveTo::create(delay, direction);
		auto call = CallFunc::create(std::bind(&Bullet::dealloc, this));
		CCAction *moveAction;

		if (!isReverse)
		{
			moveAction = newSequence(mv, call);
		}
		else
		{
			auto mv2 = CCMoveTo::create(delay, direction2);
			moveAction = newSequence(mv, mv2, call);
		}

		runAction(moveAction);
	}

	void setEaseIn(int length, float delay)
	{
		CCPoint direction = ccp(_isFlipped ? getPosition().x - length : getPosition().x + length, getPositionY());
		auto mv = CCMoveTo::create(1.0f, direction);
		auto eo = CCEaseIn::create(mv, delay);
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
				if (_master->getActionState() == State::SATTACK)
				{
					_master->setActionState(State::NATTACK);
					_master->_markPoint = ccp(getPositionX(), _originY);
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
