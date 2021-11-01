#include "Core/Hero.hpp"
#include "Defines.h"
#include "HudLayer.h"
#include "LoadLayer.h"

Monster::Monster()
{
}

Monster::~Monster()
{
	CC_SAFE_RELEASE(idleArray);
	CC_SAFE_RELEASE(walkArray);
	CC_SAFE_RELEASE(deadArray);
	CC_SAFE_RELEASE(nattackArray);
}

bool Monster::init()
{
	RETURN_FALSE_IF(!CCSprite::init());

	setAnchorPoint(ccp(0.5, 0));
	scheduleUpdate();

	return true;
}

void Monster::setID(CCString *character, CCString *role, CCString *group)
{
	setCharacter(character);
	setRole(role);
	setGroup(group);

	CCArray *animationArray = CCArray::create();
	auto filePath = format("Element/Monster/{}.xml", getCharacter()->getCString());
	KTools::readXMLToArray(filePath.c_str(), animationArray);

	// init Attribute; & indleFrame

	CCArray *tmpAction = (CCArray *)(animationArray->objectAtIndex(0));
	CCArray *tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
	idleArray = (CCArray *)(tmpAction->objectAtIndex(1));
	idleArray->retain();

	string unitName;
	CCString *tmpHpMax;
	int tmpWidth;
	int tmpHeight;
	uint32_t tmpSpeed;
	int tmpCombatPoint;

	readData(tmpData, unitName, tmpHpMax, tmpWidth, tmpHeight, tmpSpeed, tmpCombatPoint);

	setHPValue(getMaxHP(), false);
	setMaxHPValue(tmpHpMax->uintValue(), false);
	setCKR(0);
	setCKR2(0);
	setHeight(tmpHeight);
	setWalkSpeed(tmpSpeed);

	// init WalkFrame
	tmpAction = (CCArray *)(animationArray->objectAtIndex(1));
	walkArray = (CCArray *)(tmpAction->objectAtIndex(1));
	walkArray->retain();

	// init DeadFrame
	tmpAction = (CCArray *)(animationArray->objectAtIndex(6));
	deadArray = (CCArray *)(tmpAction->objectAtIndex(1));
	deadArray->retain();

	// init nAttack data & Frame Array
	tmpAction = (CCArray *)(animationArray->objectAtIndex(7));
	tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
	uint32_t tmpCD;
	CCString *tmpValue;
	readData(tmpData, _nattackType, tmpValue, _nattackRangeX, _nattackRangeY, tmpCD, tmpCombatPoint);
	setnAttackValue(tmpValue);
	nattackArray = (CCArray *)(tmpAction->objectAtIndex(1));
	nattackArray->retain();

	setCoin(50);

	initAction();
}

void Monster::initAction()
{
	setIdleAction(createAnimation(idleArray, 5.0, true, false));
	setWalkAction(createAnimation(walkArray, 10.0, true, false));
	setDeadAction(createAnimation(deadArray, 10.0f, false, false));
	if (isCharacter("Kage") ||
		isCharacter("KageHand") ||
		isCharacter("FutonSRK") ||
		isCharacter("FutonSRK2") ||
		isCharacter("Kubi"))
	{
		setNAttackAction(createAnimation(nattackArray, 10.0, false, false));
	}
	else
	{
		setNAttackAction(createAnimation(nattackArray, 10.0, false, true));
	}
}

void Monster::setHPbar()
{
	if (getGameLayer()->playerGroup != getGroup()->getCString())
	{
		_hpBar = HPBar::create("hp_bar_r.png");
	}
	else
	{
		_hpBar = HPBar::create("hp_bar_b.png");
	}

	_hpBar->setPositionY(getHeight());
	_hpBar->setDelegate(this);
	addChild(_hpBar);
	changeHPbar();
}

void Monster::changeHPbar()
{
	if (_exp >= 500 && _level == 1)
	{
		_level = 2;
		setMaxHPValue(getMaxHP() + 1000);
		setnAttackValue(to_ccstring(getNAttackValue() + 9));
	}
	else if (_exp >= 1000 && _level == 2)
	{
		_level = 3;
		setMaxHPValue(getMaxHP() + 1500);
		setnAttackValue(to_ccstring(getNAttackValue() + 18));
	}
	else if (_exp >= 1500 && _level == 3)
	{
		_level = 4;
		setMaxHPValue(getMaxHP() + 2000);
		setnAttackValue(to_ccstring(getNAttackValue() + 27));
	}
	else if (_exp >= 2000 && _level == 4)
	{
		_level = 5;
		setMaxHPValue(getMaxHP() + 2500);
		setnAttackValue(to_ccstring(getNAttackValue() + 36));
	}
	else if (_exp >= 2500 && _level == 5)
	{
		_level = 6;
		setMaxHPValue(getMaxHP() + 3000);
		setnAttackValue(to_ccstring(getNAttackValue() + 48));
	}

	if (_hpBar)
	{
		auto frame = getSpriteFrame("hp_bottom{}.png", _level);
		_hpBar->getHPBottom()->setDisplayFrame(frame);
	}
}

void Monster::setAI(float dt)
{
	auto charName = getCharacter()->getCString();
	if (is_same(charName, "Kage"))
	{
		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (strcmp(getGroup()->getCString(), hero->getGroup()->getCString()) != 0 &&
				hero->getActionState() != State::DEAD &&
				hero->getActionState() != State::O2ATTACK &&
				!hero->_isInvincible &&
				!hero->_isArmored &&
				hero->_isVisable)
			{
				CCPoint sp = ccpSub(hero->getPosition(), getPosition());
				float distanceY = hero->_originY ? abs(getPositionY() - hero->_originY) : abs(sp.y);
				float distanceX = _isFlipped ? hero->getPositionX() - getPositionX() + getContentSize().width : hero->getPositionX() - getPositionX() - getContentSize().width;
				if (abs(distanceX) < 32 && distanceY < 48)
				{
					// if (_monsterArray.empty())
					// {
					setMon("KageHand");
					unschedule(schedule_selector(CharacterBase::setAI));
					// }
					return; // Need to return because _monsterArray is always empty
				}
			}
		}
		return;
	}
	else if (is_same(charName, "Mouse"))
	{
		if (notFindHero(0))
			_mainTarget = nullptr;
	}
	else if (is_same(charName, "Spider") ||
			 is_same(charName, "ClayBird"))
	{
		if (notFindHero(0))
		{
			if (notFindTower(0))
				_mainTarget = nullptr;
		}
	}
	else if (is_same(charName, "FutonSRK2") ||
			 is_same(charName, "FutonSRK"))
	{
	}
	else
	{
		if (notFindHero(0))
		{
			if (notFindFlog(0))
				_mainTarget = nullptr;
		}
	}

	CCPoint moveDirection;

	if (_mainTarget)
	{
		CCPoint sp;

		sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY()),
					ccp(getPositionX(), _originY ? _originY : getPositionY()));

		if (is_same(charName, "FutonSRK2") ||
			is_same(charName, "FutonSRK"))
		{
			if (abs(sp.x) > 48 || abs(sp.y) > 32)
			{
				setActionState(State::WALK);
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (_mainTarget->isPlayerOrCom())
			{
				stopAllActions();
				dealloc();
			}
		}
		else if (is_same(charName, "Traps"))
		{
			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
			}
			else
			{
				attack(NAttack);
			}
		}
		else if (abs(sp.x) > 32 || abs(sp.y) > 16)
		{
			if (!is_same(charName, "Dogs") &&
				!is_same(charName, "Mine") &&
				!is_same(charName, "Traps") &&
				!is_same(charName, "Yominuma") &&
				!is_same(charName, "Tsukuyomi"))
			{
				moveDirection = ccpNormalize(sp);

				walk(moveDirection);
			}
		}
		else
		{
			if (is_same(charName, "Mine"))
			{
				if (_mainTarget->isPlayerOrCom())
				{
					attack(NAttack);
					unschedule(schedule_selector(CharacterBase::setAI));
				}
			}
			else
			{
				changeSide(sp);
				attack(NAttack);

				if (!is_same(charName, "SmallSlug"))
				{
					unschedule(schedule_selector(CharacterBase::setAI));
				}
			}
		}
	}
	else
	{
		if (is_same(charName, "Rocket") ||
			is_same(charName, "Spider") ||
			is_same(charName, "ClayBird"))
		{
			stepOn();
		}
		else
		{
			idle();
		}
	}
}

void Monster::dealloc()
{
	stopAllActions();
	unschedule(schedule_selector(CharacterBase::setAI));
	setActionState(State::DEAD);

	if (isCharacter("FutonSRK", "FutonSRK2"))
	{
		auto call = CallFunc::create(std::bind(&Monster::removeFromParent, this));
		auto seq = newSequence(getDeadAction(), call);
		runAction(seq);
		return;
	}
	if (isCharacter("HiraishinMark"))
	{
		_master->_isCanSkill1 = false;
		_master->setActionResume();
		_master->scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sattackcooldown1);

		if (_master->isPlayer())
		{
			auto frame = getSpriteFrame("Minato_skill1.png");
			getGameLayer()->getHudLayer()->skill1Button->setDisplayFrame(frame);
			getGameLayer()->getHudLayer()->skill1Button->_clickNum++;
			getGameLayer()->clearDoubleClick();
		}

		_master->removeAllMonAndCleanup("HiraishinMark");

		return;
	}

	if (isCharacter("SmallSlug"))
	{
		if (_secmaster)
			_secmaster->removeMon(this);
	}
	else
	{
		if (_master)
			_master->removeMon(this);
	}

	if (isCharacter("KageHand", "Kage"))
	{
		auto call = CallFunc::create(std::bind(&Monster::setResume, this));
		auto call2 = CallFunc::create(std::bind(&Monster::removeFromParent, this));
		auto seq = newSequence(getDeadAction(), call, call2);
		runAction(seq);
	}
	else
	{
		removeFromParent();
	}
}

void Monster::setDirectMove(int length, float delay, bool isReverse)
{
	CCPoint direction = ccp(_isFlipped ? getPosition().x - length : getPosition().x + length, getPositionY());
	CCPoint direction2 = getPosition();
	auto mv = CCMoveTo::create(delay, direction);
	auto call = CallFunc::create(std::bind(&Monster::dealloc, this));
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

void Monster::setEaseIn(int length, float delay)
{
	CCPoint direction = ccp(_isFlipped ? getPosition().x - length : getPosition().x + length,
							getPositionY());
	auto mv = CCMoveTo::create(1.0f, direction);
	auto eo = CCEaseIn::create(mv, delay);

	auto call = CallFunc::create(std::bind(&Monster::dealloc, this));
	auto seq = newSequence(eo, call);
	runAction(seq);
}

void Monster::setDirectMoveBy(int length, float delay)
{
	CCPoint direction = ccp(_isFlipped ? getPosition().x - length : getPosition().x + length,
							getPositionY());

	if (_mainTarget)
	{
		auto mv = CCMoveBy::create(0.1f, ccp(_mainTarget->getPositionX() > getPositionX() ? 16 : -16, _mainTarget->getPositionY() > getPositionY() ? 16 : -16));

		runAction(CCRepeatForever::create(mv));

		_mainTarget = nullptr;
		_master->_mainTarget = nullptr;
	}
	else
	{
		auto mv = CCMoveBy::create(0.1f, ccp(_isFlipped ? -16 : 16, 0));

		runAction(CCRepeatForever::create(mv));
	}

	auto delayTime = CCDelayTime::create(delay);
	auto call = CallFunc::create(std::bind(&Monster::dealloc, this));
	auto seq = newSequence(delayTime, call);
	runAction(seq);
}

void Monster::setResume()
{
	if (getSecMaster())
	{
		getSecMaster()->dealloc();
	}
	else
	{
		if (_master && _master->isCharacter("Shikamaru"))
		{
			_master->idle();
		}
	}
}
