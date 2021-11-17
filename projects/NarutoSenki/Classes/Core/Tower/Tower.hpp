#pragma once
#include "Core/Unit.h"
#include "Core/Utils/UnitEx.hpp"
#include "Core/Warrior/Flog.hpp"
#include "HPBar.h"
#include "HudLayer.h"

class Tower : public Unit
{
public:
	CREATE_FUNC(Tower);

	bool init()
	{
		RETURN_FALSE_IF(!Sprite::init());

		setAnchorPoint(Vec2(0.5, 0.5));
		scheduleUpdate();

		return true;
	}

	void setID(const string &name, Role role, Group group) override
	{
		clearActionData();
		setName(name);
		setRole(role);
		setGroup(group);

		string fpath;
		if (getName() == TowerEnum::KonohaCenter || getName() == TowerEnum::AkatsukiCenter)
			fpath = "Unit/Tower/InnerTower.toml";
		else
			fpath = "Unit/Tower/OuterTower.toml";
		auto metadata = UnitParser::fromToml(fpath);
		genActionBy(metadata);
		// init action
		setAction(ActionFlag::Idle | ActionFlag::Dead);

		setMaxHP(metadata.hp);
		setHP(metadata.hp);
		setCKR(0);
		setCKR2(0);
		setHPBarHeight(metadata.hpBarY);
		setWalkSpeed(metadata.speed);

		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Unit::acceptAttack), "acceptAttack", nullptr);
	}

	void setHPbar()
	{
		if (getGroup() != getGameLayer()->currentPlayer->getGroup())
			_hpBar = HPBar::create("hp_bar_r.png");
		else
			_hpBar = HPBar::create("hp_bar.png");
		_hpBar->getHPBAR()->setPosition(Vec2(1, 1));
		_hpBar->setPositionY(getHPBarHeight());
		_hpBar->setDelegate(this);
		addChild(_hpBar);
	}

	void dealloc()
	{
		unschedule(schedule_selector(Unit::setAI));
		setState(State::DEAD);
		stopAllActions();

		getGameLayer()->clearAllFlogsMainTarget(this);

		std::erase(getGameLayer()->_TowerArray, this);
		getGameLayer()->setTowerState(getCharId());
		getGameLayer()->checkTower();
		removeFromParent();
	}
};
