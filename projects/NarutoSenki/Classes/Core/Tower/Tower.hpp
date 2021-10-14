#pragma once
#include "CharacterBase.h"
#include "Core/Warrior/Flog.hpp"
#include "HPBar.h"
#include "HudLayer.h"

class Tower : public CharacterBase
{
public:
	CREATE_FUNC(Tower);

	bool init()
	{
		RETURN_FALSE_IF(!CharacterBase::init());

		setAnchorPoint(ccp(0.5, 0.5));
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

		if (isCharacter("KonohaCenter", "AkatsukiCenter"))
			filePath = "Element/Tower/CenterDate.xml";
		else
			filePath = "Element/Tower/TowerDate.xml";

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

		if (!getCKR() && !getCKR2())
		{
			setCkrValue(0);
			setCkr2Value(0);
		}

		//init DeadFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(6));
		deadArray = (CCArray *)(tmpAction->objectAtIndex(1));

		setCoinValue(50);

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
		if (strcmp(getGroup()->getCString(), getGameLayer()->currentPlayer->getGroup()->getCString()) != 0)
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

		vector<Flog *> list;
		for (int i = 0; i < 2; i++)
		{
			if (i == 0)
				list = getGameLayer()->_KonohaFlogArray;
			else if (i == 1)
				list = getGameLayer()->_AkatsukiFlogArray;

			for (auto flog : list)
			{
				if (flog->_mainTarget)
				{
					if (flog->_mainTarget == (CharacterBase *)this)
					{
						flog->_mainTarget = nullptr;
					}
				}
			}
		}

		std::erase(getGameLayer()->_TowerArray, this);
		getGameLayer()->setTowerState(getCharNO());
		getGameLayer()->checkTower();
		removeFromParentAndCleanup(true);
	}
};
