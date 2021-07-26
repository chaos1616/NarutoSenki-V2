#pragma once
#include "CharacterBase.h"
#include "HPBar.h"

//TODO: Rename to 'Projectile'
class Bullet : public CharacterBase
{
public:
	CREATE_FUNC(Bullet);

	Bullet()
	{
	}

	~Bullet()
	{
	}

	bool init()
	{
		bool bRet = false;
		do
		{
			//CC_BREAK_IF(!CharacterBase::initWithSpriteFrameName("coin.png"));
			CC_BREAK_IF(!CharacterBase::init());
			scheduleUpdate();
			bRet = true;
		} while (0);

		return bRet;
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

		//init nAttack data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(7));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		uint32_t tmpCD;
		int tmpCombatPoint;
		CCString *tmpValue;

		readData(tmpData, _nattackType, tmpValue, _nattackRangeX, _nattackRangeY, tmpCD, tmpCombatPoint);
		setnAttackValue(tmpValue);
		_nattackType->retain();
		nattackArray = (CCArray *)(tmpAction->objectAtIndex(1));

		if (strcmp(getCharacter()->getCString(), "Amaterasu") == 0)
		{
			//init DeadFrame
			tmpAction = (CCArray *)(animationArray->objectAtIndex(6));
			deadArray = (CCArray *)(tmpAction->objectAtIndex(1));
		}

		setCoin(CCString::create("50"));

		initAction();
	}

	void initAction()
	{
		setIdleAction(createAnimation(idleArray, 5.0, true, false));
		setNAttackAction(createAnimation(nattackArray, 10.0, true, false));
		if (strcmp(getCharacter()->getCString(), "Amaterasu") == 0 ||
			strcmp(getCharacter()->getCString(), "SusanoTama") == 0)
		{
			setDeadAction(createAnimation(deadArray, 10.0f, false, false));
		}
	}

	void setMove(int length, float delay, bool isReverse)
	{
		CCPoint direction = ccp(_isFlipped ? getPosition().x - length : getPosition().x + length,
								getPositionY());
		CCPoint direction2 = getPosition();
		CCActionInterval *mv = CCMoveTo::create(delay, direction);
		CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(Bullet::dealloc));
		CCAction *seq;
		if (!isReverse)
		{
			seq = CCSequence::create(mv, call, nullptr);
		}
		else
		{
			CCActionInterval *mv2 = CCMoveTo::create(delay, direction2);
			seq = CCSequence::create(mv, mv2, call, nullptr);
		}

		runAction(seq);
	}

	void setEaseIn(int length, float delay)
	{
		CCPoint direction = ccp(_isFlipped ? getPosition().x - length : getPosition().x + length,
								getPositionY());
		CCActionInterval *mv = CCMoveTo::create(1.0f, direction);
		CCActionInterval *eo = CCEaseIn::create(mv, delay);

		CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(Bullet::dealloc));
		CCAction *seq = CCSequence::create(eo, call, nullptr);
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

		if (strcmp(getCharacter()->getCString(), "Amaterasu") == 0)
		{
			CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(Bullet::dealloc2));
			CCArray *seqArray = CCArray::create();
			seqArray->addObject(getDeadAction());
			seqArray->addObject(call);
			CCAction *seq = CCSequence::create(seqArray);
			runAction(seq);
		}
		else
		{
			if (strcmp(getCharacter()->getCString(), "HiraishinKunai") == 0)
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

			if (_master && _master->getMonsterArray())
			{
				int index = _master->getMonsterArray()->indexOfObject(this);
				if (index >= 0)
				{
					_master->getMonsterArray()->removeObjectAtIndex(index);
				}
			}
			removeFromParentAndCleanup(true);
		}
	}

	void dealloc2()
	{
		removeFromParentAndCleanup(true);
	}
};
