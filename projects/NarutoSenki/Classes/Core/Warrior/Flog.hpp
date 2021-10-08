#pragma once
#include "CharacterBase.h"
#include "HPBar.h"

class Flog : public CharacterBase
{
public:
	float _mainPosY;
	float _randomPosX;
	float _randomPosY;

	CREATE_FUNC(Flog);

	Flog()
	{
		_randomPosX = 0;
		_randomPosY = 0;
	}

	~Flog()
	{
		CC_SAFE_RELEASE(callValue);
		CC_SAFE_RELEASE(_nattackType);
		CC_SAFE_RELEASE(_damageArray);
	}

	bool init()
	{
		RETURN_FALSE_IF(!CharacterBase::init());

		setAnchorPoint(ccp(0.5, 0));
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

		filePath = CCString::createWithFormat("Element/Flog/%s.xml", getCharacter()->getCString())->getCString();

		KTools::readXMLToArray(filePath, animationArray);

		CCArray *tmpAction = (CCArray *)(animationArray->objectAtIndex(0));
		CCArray *tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		idleArray = (CCArray *)(tmpAction->objectAtIndex(1));

		CCString *tmpName;
		CCString *tmpHpMax;
		int tmpWidth;
		int tmpHeight;
		uint32_t tmpSpeed;
		int tmpCombatPoint;

		readData(tmpData, tmpName, tmpHpMax, tmpWidth, tmpHeight, tmpSpeed, tmpCombatPoint);
		setMaxHPValue(tmpHpMax->uintValue(), false);
		setHPValue(getMaxHPValue(), false);
		setHeight(tmpHeight);
		setWalkSpeed(tmpSpeed);

		setKillNum(to_ccstring(0));

		if (!getCKR() && !getCKR2())
		{
			setCkrValue(0);
			setCkr2Value(0);
		}

		//init WalkFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(1));
		walkArray = (CCArray *)(tmpAction->objectAtIndex(1));

		//init HurtFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(2));
		hurtArray = (CCArray *)(tmpAction->objectAtIndex(1));

		//init AirHurtFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(3));
		airHurtArray = (CCArray *)(tmpAction->objectAtIndex(1));

		//init KnockDownFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(4));
		knockDownArray = (CCArray *)(tmpAction->objectAtIndex(1));

		//init FloatFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(5));
		floatArray = (CCArray *)(tmpAction->objectAtIndex(1));

		//init DeadFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(6));
		deadArray = (CCArray *)(tmpAction->objectAtIndex(1));

		//init nAttack data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(7));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		uint32_t tmpCD;
		CCString *tmpValue;
		readData(tmpData, _nattackType, tmpValue, _nattackRangeX, _nattackRangeY, tmpCD, tmpCombatPoint);
		setnAttackValue(tmpValue);
		_nattackType->retain();
		nattackArray = (CCArray *)(tmpAction->objectAtIndex(1));

		_damageArray = CCArray::create();
		_damageArray->retain();

		setCoinValue(50);

		initAction();
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CharacterBase::acceptAttack), "acceptAttack", nullptr);
	}

	void initAction()
	{
		setIdleAction(createAnimation(idleArray, 5.0, true, false));
		setWalkAction(createAnimation(walkArray, 10.0, true, false));
		setHurtAction(createAnimation(hurtArray, 10.0, false, true));

		setAirHurtAction(createAnimation(airHurtArray, 10.0f, false, false));
		setKnockDownAction(createAnimation(knockDownArray, 10.0f, false, true));
		setDeadAction(createAnimation(deadArray, 10.0f, false, false));

		setFloatAction(createAnimation(floatArray, 10.0f, false, false));

		setNAttackAction(createAnimation(nattackArray, 10.0, false, true));
	}

	void setHPbar()
	{
		if (strcmp(getGroup()->getCString(), getGameLayer()->currentPlayer->getGroup()->getCString()) != 0)
			_hpBar = HPBar::create("flog_bar_r.png");
		else
			_hpBar = HPBar::create("flog_bar.png");
		_hpBar->setPositionY(getHeight());
		_hpBar->setDelegate(this);
		addChild(_hpBar);
	}

protected:
	void dealloc()
	{
		unschedule(schedule_selector(CharacterBase::setAI));
		setActionState(State::DEAD);
		stopAllActions();

		if (isKonohaGroup())
		{
			int index = getGameLayer()->_KonohaFlogArray->indexOfObject(this);
			getGameLayer()->_KonohaFlogArray->removeObjectAtIndex(index);
		}
		else
		{
			int index = getGameLayer()->_AkatsukiFlogArray->indexOfObject(this);
			getGameLayer()->_AkatsukiFlogArray->removeObjectAtIndex(index);
		}
		removeFromParent();
	}

	void setAI(float dt)
	{
		if (isFreeActionState())
		{
			if (!_randomPosY)
			{
				_randomPosY = rand() % 8 + 4;
				_randomPosX = rand() % 32 + 20;
			}

			bool hasTarget = false;

			if (_mainTarget)
			{
				if (_mainTarget->getActionState() != State::DEAD && !_mainTarget->_isInvincible && _mainTarget->_isVisable &&
					strcmp(_mainTarget->getGroup()->getCString(), getGroup()->getCString()) != 0)
				{
					hasTarget = true;
				}
			}

			if (!hasTarget)
			{
				if (notFindFlog(0))
				{
					if (notFindHero(64))
					{
						if (notFindTower(0))
						{
							_mainTarget = nullptr;
						}
					}
				}
			}

			CCPoint moveDirection;

			if (_mainTarget)
			{
				CCPoint sp = getDistanceToTargetAndIgnoreOriginY();
				if (abs(sp.x) > _randomPosX || abs(sp.y) > _randomPosY)
				{
					if (abs(sp.x) > 64 && _mainTarget->isNotFlog() && _mainTarget->isNotTower())
					{
						_mainTarget = nullptr;
						return;
					}

					moveDirection = ccpNormalize(sp);
					walk(moveDirection);
				}
				else
				{
					if (_actionState != State::NATTACK)
					{
						changeSide(sp);
						attack(NAttack);
					}
				}
				return;
			}

			// no target then step on
			if (abs(getPositionY() - _mainPosY) > 8)
			{
				if (isKonohaGroup())
					moveDirection = ccpNormalize(ccp(1, getPositionY() > _mainPosY ? -1 : 1));
				else
					moveDirection = ccpNormalize(ccp(-1, getPositionY() > _mainPosY ? -1 : 1));
			}
			else
			{
				if (isKonohaGroup())
					moveDirection = ccpNormalize(ccp(1, 0));
				else
					moveDirection = ccpNormalize(ccp(-1, 0));
			}
			walk(moveDirection);
		}
	}
};
