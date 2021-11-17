#include "Core/Hero.hpp"
#include "HudLayer.h"
#include "LoadLayer.h"

// TODO: Rename to `Skill`
bool Monster::init()
{
	RETURN_FALSE_IF(!Sprite::init());

	setAnchorPoint(Vec2(0.5, 0));
	scheduleUpdate();

	return true;
}

void Monster::setID(const string &name, Role role, Group group)
{
	clearActionData();
	setName(name);
	setRole(role);
	setGroup(group);

	auto fpath = format("Unit/Mon/{}.toml", name);
	auto metadata = UnitParser::fromToml(fpath);
	genActionBy(metadata);
	// init action
	setAction(ActionFlag::Idle | ActionFlag::Walk | ActionFlag::Dead | ActionFlag::NAttack);

	setMaxHP(metadata.hp);
	setHP(metadata.hp);
	setCKR(0);
	setCKR2(0);
	setHPBarHeight(metadata.hpBarY);
	setWalkSpeed(metadata.speed);
}

void Monster::setHPbar() // Mon does not have hp bar
{
	if (getGameLayer()->playerGroup != getGroup())
	{
		_hpBar = HPBar::create("hp_bar_r.png");
	}
	else
	{
		_hpBar = HPBar::create("hp_bar_b.png");
	}

	_hpBar->setPositionY(getHPBarHeight());
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
		setNAttackValue(getNAttackValue() + 9);
	}
	else if (_exp >= 1000 && _level == 2)
	{
		_level = 3;
		setMaxHPValue(getMaxHP() + 1500);
		setNAttackValue(getNAttackValue() + 18);
	}
	else if (_exp >= 1500 && _level == 3)
	{
		_level = 4;
		setMaxHPValue(getMaxHP() + 2000);
		setNAttackValue(getNAttackValue() + 27);
	}
	else if (_exp >= 2000 && _level == 4)
	{
		_level = 5;
		setMaxHPValue(getMaxHP() + 2500);
		setNAttackValue(getNAttackValue() + 36);
	}
	else if (_exp >= 2500 && _level == 5)
	{
		_level = 6;
		setMaxHPValue(getMaxHP() + 3000);
		setNAttackValue(getNAttackValue() + 48);
	}

	if (_hpBar)
	{
		auto frame = getSpriteFrame("hp_bottom{}.png", _level);
		_hpBar->getHPBottom()->setDisplayFrame(frame);
	}
}

void Monster::setAI(float dt)
{
	auto charName = getName();
	if (charName == SkillEnum::Kage)
	{
		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (getGroup() != hero->getGroup() &&
				hero->getState() != State::DEAD &&
				hero->getState() != State::O2ATTACK &&
				!hero->_isInvincible &&
				!hero->_isArmored &&
				hero->_isVisable)
			{
				Vec2 sp = hero->getPosition() - getPosition();
				float distanceY = hero->_originY ? abs(getPositionY() - hero->_originY) : abs(sp.y);
				float distanceX = _isFlipped ? hero->getPositionX() - getPositionX() + getContentSize().width : hero->getPositionX() - getPositionX() - getContentSize().width;
				if (abs(distanceX) < 32 && distanceY < 48)
				{
					// if (_monsterArray.empty())
					// {
					setMon(SkillEnum::KageHand);
					unschedule(schedule_selector(Unit::setAI));
					// }
					return; // Need to return because _monsterArray is always empty
				}
			}
		}
		return;
	}
	else if (charName == SkillEnum::Mouse)
	{
		if (notFindHero(0))
			_mainTarget = nullptr;
	}
	else if (charName == SkillEnum::Spider ||
			 charName == SkillEnum::ClayBird)
	{
		if (notFindHero(0))
		{
			if (notFindTower(0))
				_mainTarget = nullptr;
		}
	}
	else if (charName == SkillEnum::FutonSRK2 ||
			 charName == SkillEnum::FutonSRK)
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

	Vec2 moveDirection;

	if (_mainTarget)
	{
		Vec2 sp = Vec2(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY()) -
				  Vec2(getPositionX(), _originY ? _originY : getPositionY());

		if (charName == SkillEnum::FutonSRK2 ||
			charName == SkillEnum::FutonSRK)
		{
			if (abs(sp.x) > 48 || abs(sp.y) > 32)
			{
				setState(State::WALK);
				moveDirection = sp.getNormalized();
				walk(moveDirection);
				return;
			}

			if (_mainTarget->isPlayerOrCom())
			{
				stopAllActions();
				dealloc();
			}
		}
		else if (charName == "Traps")
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
			// Traps AI
			if (charName != "Dogs" &&
				charName != "Mine" &&
				charName != "Traps" &&
				charName != "Yominuma" &&
				charName != "Tsukuyomi")
			{
				moveDirection = sp.getNormalized();

				walk(moveDirection);
			}
		}
		else
		{
			if (charName == "Mine")
			{
				if (_mainTarget->isPlayerOrCom())
				{
					attack(NAttack);
					unschedule(schedule_selector(Unit::setAI));
				}
			}
			else
			{
				changeSide(sp);
				attack(NAttack);

				if (charName != SummonEnum::SmallSlug)
				{
					unschedule(schedule_selector(Unit::setAI));
				}
			}
		}
	}
	else
	{
		if (charName == "Rocket" ||
			charName == "Spider" ||
			charName == "ClayBird")
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
	unschedule(schedule_selector(Unit::setAI));
	setState(State::DEAD);

	if (getName() == SkillEnum::FutonSRK || getName() == SkillEnum::FutonSRK2) // TODO: improve
	{
		auto call = CallFunc::create(std::bind(&Monster::removeFromParent, this));
		auto seq = newSequence(getDeadAction(), call);
		runAction(seq);
		return;
	}
	if (getName() == SkillEnum::HiraishinMark)
	{
		_master->_isCanSkill1 = false;
		_master->setActionResume();
		_master->scheduleOnce(schedule_selector(Unit::enableSkill1), _sAttackCD1);

		if (_master->isPlayer())
		{
			auto frame = getSpriteFrame("Minato_skill1.png");
			getGameLayer()->getHudLayer()->skill1Button->setDisplayFrame(frame);
			getGameLayer()->getHudLayer()->skill1Button->_clickNum++;
			getGameLayer()->clearDoubleClick();
		}

		_master->removeAllMonAndCleanup(SkillEnum::HiraishinMark);

		return;
	}

	if (getName() == SummonEnum::SmallSlug)
	{
		if (_secmaster)
			_secmaster->removeMon(this);
	}
	else
	{
		if (_master)
			_master->removeMon(this);
	}

	if (getName() == SkillEnum::KageHand || getName() == SkillEnum::Kage) // TODO: improve
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
	Vec2 direction = Vec2(_isFlipped ? getPosition().x - length : getPosition().x + length, getPositionY());
	Vec2 direction2 = getPosition();
	auto mv = MoveTo::create(delay, direction);
	auto call = CallFunc::create(std::bind(&Monster::dealloc, this));
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

void Monster::setEaseIn(int length, float delay)
{
	Vec2 direction = Vec2(_isFlipped ? getPosition().x - length : getPosition().x + length,
						  getPositionY());
	auto mv = MoveTo::create(1.0f, direction);
	auto eo = EaseIn::create(mv, delay);

	auto call = CallFunc::create(std::bind(&Monster::dealloc, this));
	auto seq = newSequence(eo, call);
	runAction(seq);
}

void Monster::setDirectMoveBy(int length, float delay)
{
	// Vec2 direction = Vec2(_isFlipped ? getPosition().x - length : getPosition().x + length,
	// 					  getPositionY());

	if (_mainTarget)
	{
		auto mv = MoveBy::create(0.1f, Vec2(_mainTarget->getPositionX() > getPositionX() ? 16 : -16, _mainTarget->getPositionY() > getPositionY() ? 16 : -16));

		runAction(RepeatForever::create(mv));

		_mainTarget = nullptr;
		_master->_mainTarget = nullptr;
	}
	else
	{
		auto mv = MoveBy::create(0.1f, Vec2(_isFlipped ? -16 : 16, 0));

		runAction(RepeatForever::create(mv));
	}

	auto delayTime = DelayTime::create(delay);
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
		if (_master && _master->getName() == HeroEnum::Shikamaru)
		{
			_master->idle();
		}
	}
}
