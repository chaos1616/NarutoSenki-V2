#pragma once
#include "CharacterBase.h"
#include "Core/Warrior/Flog.hpp"
#include "Core/Utils/UnitEx.hpp"
#include "HPBar.h"
#include "HudLayer.h"

class Tower : public CharacterBase
{
public:
	CREATE_FUNC(Tower);

	bool init()
	{
		RETURN_FALSE_IF(!CCSprite::init());

		setAnchorPoint(ccp(0.5, 0.5));
		scheduleUpdate();

		return true;
	}

	void setID(const string &name, const string &role, const string &group)
	{
		setName(name);
		setRole(role);
		setGroup(group);

		CCArray *animationArray = CCArray::create();
		const char *filePath;

		if (getName() == TowerEnum::KonohaCenter || getName() == TowerEnum::AkatsukiCenter)
			filePath = "Element/Tower/CenterDate.xml";
		else
			filePath = "Element/Tower/TowerDate.xml";

		KTools::readXMLToArray(filePath, animationArray);

		CCArray *tmpAction = (CCArray *)(animationArray->objectAtIndex(0));
		CCArray *tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		idleArray = (CCArray *)(tmpAction->objectAtIndex(1));

		string unitName;
		uint32_t maxHP;
		int tmpWidth;
		int tmpHeight;
		uint32_t tmpSpeed;
		int tmpCombatPoint;

		readData(tmpData, unitName, maxHP, tmpWidth, tmpHeight, tmpSpeed, tmpCombatPoint);

		setMaxHPValue(maxHP, false);
		setHPValue(maxHP, false);
		setCKR(0);
		setCKR2(0);
		setHeight(tmpHeight);
		setWalkSpeed(tmpSpeed);

		// init DeadFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(6));
		deadArray = (CCArray *)(tmpAction->objectAtIndex(1));

		setCoin(50);

		initAction();

		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CharacterBase::acceptAttack), "acceptAttack", nullptr);
	}

	void initAction()
	{
		setDeadAction(createAnimation(deadArray, 10.0f, false, false));
		setIdleAction(createAnimation(idleArray, 5.0, true, false));
	}

	void setHPbar()
	{
		if (getGroup() != getGameLayer()->currentPlayer->getGroup())
			_hpBar = HPBar::create("hp_bar_r.png");
		else
			_hpBar = HPBar::create("hp_bar.png");
		_hpBar->getHPBAR()->setPosition(ccp(1, 1));
		_hpBar->setPositionY(getHeight());
		_hpBar->setDelegate(this);
		addChild(_hpBar);
	}

	void dealloc()
	{
		unschedule(schedule_selector(CharacterBase::setAI));
		setActionState(State::DEAD);
		stopAllActions();

		UnitEx::RemoveAllFlogsMainTarget(this);

		std::erase(getGameLayer()->_TowerArray, this);
		getGameLayer()->setTowerState(getCharId());
		getGameLayer()->checkTower();
		removeFromParent();
	}
};
