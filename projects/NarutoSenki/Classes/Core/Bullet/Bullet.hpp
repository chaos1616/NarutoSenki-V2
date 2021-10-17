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
		RETURN_FALSE_IF(!CharacterBase::init());

		scheduleUpdate();

		return true;
	}

	void setID(CCString *character, CCString *role, CCString *group)
	{
		setCharacter(character);
		setRole(role);
		setGroup(group);

		CCArray *animationArray = CCArray::create();
		const char *filePath;

		filePath = CCString::createWithFormat("Element/Bullet/%s.xml", getCharacter()->getCString())->getCString();

		KTools::readXMLToArray(filePath, animationArray);

		CCArray *tmpAction = (CCArray *)(animationArray->objectAtIndex(0));
		CCArray *tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		idleArray = (CCArray *)(tmpAction->objectAtIndex(1));

		// init nAttack data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(7));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		uint32_t tmpCD;
		int tmpCombatPoint;
		CCString *tmpValue;

		readData(tmpData, _nattackType, tmpValue, _nattackRangeX, _nattackRangeY, tmpCD, tmpCombatPoint);
		setnAttackValue(tmpValue);
		nattackArray = (CCArray *)(tmpAction->objectAtIndex(1));

		if (isCharacter("Amaterasu"))
		{
			// init DeadFrame
			tmpAction = (CCArray *)(animationArray->objectAtIndex(6));
			deadArray = (CCArray *)(tmpAction->objectAtIndex(1));
		}

		setCoinValue(50);

		initAction();
	}

	void initAction()
	{
		setIdleAction(createAnimation(idleArray, 5.0, true, false));
		setNAttackAction(createAnimation(nattackArray, 10.0, true, false));
		if (isCharacter("Amaterasu", "SusanoTama"))
		{
			setDeadAction(createAnimation(deadArray, 10.0f, false, false));
		}
	}

	void setMove(int length, float delay, bool isReverse)
	{
		CCPoint direction = ccp(_isFlipped ? getPosition().x - length : getPosition().x + length,
								getPositionY());
		CCPoint direction2 = getPosition();
		auto mv = CCMoveTo::create(delay, direction);
		auto call = CCCallFunc::create(this, callfunc_selector(Bullet::dealloc));
		CCAction *seq;
		if (!isReverse)
		{
			seq = CCSequence::create(mv, call, nullptr);
		}
		else
		{
			auto mv2 = CCMoveTo::create(delay, direction2);
			seq = CCSequence::create(mv, mv2, call, nullptr);
		}

		runAction(seq);
	}

	void setEaseIn(int length, float delay)
	{
		CCPoint direction = ccp(_isFlipped ? getPosition().x - length : getPosition().x + length,
								getPositionY());
		auto mv = CCMoveTo::create(1.0f, direction);
		auto eo = CCEaseIn::create(mv, delay);

		auto call = CCCallFunc::create(this, callfunc_selector(Bullet::dealloc));
		auto seq = CCSequence::create(eo, call, nullptr);
		runAction(seq);
	}

	void setAttack(float dt)
	{
		attack(NAttack);
	}

protected:
	void dealloc()
	{
		stopAllActions();

		if (isCharacter("Amaterasu"))
		{
			auto call = CCCallFunc::create(this, callfunc_selector(Bullet::dealloc2));
			auto seqArray = CCArray::create();
			seqArray->addObject(getDeadAction());
			seqArray->addObject(call);
			auto seq = CCSequence::create(seqArray);
			runAction(seq);
		}
		else
		{
			if (isCharacter("HiraishinKunai"))
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

	void dealloc2()
	{
		removeFromParent();
	}
};
