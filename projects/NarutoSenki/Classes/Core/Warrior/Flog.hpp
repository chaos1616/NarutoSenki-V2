#pragma once
#include "Core/Unit.h"
#include "HPBar.h"

class Flog : public Unit
{
public:
	float _mainPosY = 0;
	float _randomPosX = 0;
	float _randomPosY = 0;
#if COCOS2D_DEBUG
	string _targetName;
#endif

	CREATE_FUNC(Flog);

	bool init()
	{
		RETURN_FALSE_IF(!Sprite::init());

		setAnchorPoint(Vec2(0.5, 0));
		scheduleUpdate();

		return true;
	}

	void setID(const string &name, Role role, Group group) override
	{
		clearActionData();
		setName(name);
		setRole(role);
		setGroup(group);

		auto fpath = format("Unit/Flog/{}.toml", name);
		auto metadata = UnitParser::fromToml(fpath);
		genActionBy(metadata);
		// init action
		setAction(ActionFlag::Idle | ActionFlag::Walk | ActionFlag::Dead |
				  ActionFlag::Hurt | ActionFlag::AirHurt | ActionFlag::Knockdown |
				  ActionFlag::Float | ActionFlag::NAttack);

		setMaxHP(metadata.hp);
		setHP(metadata.hp);
		setCKR(0);
		setCKR2(0);
		setHPBarHeight(metadata.hpBarY);
		setWalkSpeed(metadata.speed);

		setKillNum(0);

		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Unit::acceptAttack), "acceptAttack", nullptr);
	}

	void setHPbar()
	{
		if (getGroup() != getGameLayer()->currentPlayer->getGroup())
			_hpBar = HPBar::create("flog_bar_r.png");
		else
			_hpBar = HPBar::create("flog_bar.png");
		_hpBar->setPositionY(getHPBarHeight());
		_hpBar->setDelegate(this);
		addChild(_hpBar);
	}

protected:
	void dealloc()
	{
		setState(State::DEAD);
		unscheduleAllSelectors();
		stopAllActions();

		if (isKonohaGroup())
			std::erase(getGameLayer()->_KonohaFlogArray, this);
		else
			std::erase(getGameLayer()->_AkatsukiFlogArray, this);

		removeFromParent();
	}

	void setAI(float dt)
	{
		if (isFreeState())
		{
			if (!_randomPosY)
			{
				_randomPosY = rand() % 8 + 4;
				_randomPosX = rand() % 32 + 20;
			}

			bool hasTarget = false;

			if (_mainTarget)
			{
				if (_mainTarget->getState() != State::DEAD && !_mainTarget->_isInvincible && _mainTarget->_isVisable &&
					_mainTarget->getGroup() != getGroup())
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
#if COCOS2D_DEBUG
			if (_mainTarget)
				_targetName = _mainTarget->getName();
#endif

			Vec2 moveDirection;

			if (_mainTarget)
			{
				Vec2 sp = getDistanceToTargetAndIgnoreOriginY();
				if (abs(sp.x) > _randomPosX || abs(sp.y) > _randomPosY)
				{
					if (abs(sp.x) > 64 && _mainTarget->isNotFlog() && _mainTarget->isNotTower())
					{
						_mainTarget = nullptr;
						return;
					}

					moveDirection = sp.getNormalized();
					walk(moveDirection);
				}
				else
				{
					if (_state != State::NATTACK)
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
					moveDirection = Vec2(1, getPositionY() > _mainPosY ? -1 : 1).getNormalized();
				else
					moveDirection = Vec2(-1, getPositionY() > _mainPosY ? -1 : 1).getNormalized();
			}
			else
			{
				if (isKonohaGroup())
					moveDirection = Vec2(1, 0).getNormalized();
				else
					moveDirection = Vec2(-1, 0).getNormalized();
			}
			walk(moveDirection);
		}
	}
};
