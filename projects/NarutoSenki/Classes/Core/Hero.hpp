#pragma once
#include "Element.h"

typedef std::function<void()> AIHandler;

class Hero : public Unit
{
	friend class CommandSystem;

private:
	Sprite *rebornSprite = nullptr;
	CCLabelBMFont *rebornLabel = nullptr;
	// Hero *proxy = nullptr;

public:
	bool init()
	{
		RETURN_FALSE_IF(!Sprite::init());

		setAnchorPoint(Vec2(0.5, 0));
		scheduleUpdate();

		return true;
	}

	virtual void setID(const string &name, Role role, Group group) override
	{
		clearActionData();
		setRole(role);
		setGroup(group);

		auto fileUtils = FileUtils::sharedFileUtils();
		string fpath = fileUtils->fullPathForFilename(format("Unit/Ninja/{}/{}.toml", name, name).c_str());
		if (!fileUtils->isFileExist(fpath))
		{
			fpath = fileUtils->fullPathForFilename(format("Unit/Kuchiyose/{}/{}.toml", name, name).c_str());
			if (!fileUtils->isFileExist(fpath))
			{
				fpath = fileUtils->fullPathForFilename(format("Unit/Kugutsu/{}/{}.toml", name, name).c_str());
				if (!fileUtils->isFileExist(fpath))
				{
					fpath = fileUtils->fullPathForFilename(format("Unit/Guardian/{}/{}.toml", name, name).c_str());
					if (!fileUtils->isFileExist(fpath))
					{
						CCLOGERROR("Not found file %s", fpath.c_str());
						return;
					}
				}
			}
		}
		auto metadata = UnitParser::fromToml(fpath);
		genActionBy(metadata);
		// init action
		setAction(ActionFlag::AllBasics);

		if (getName().empty()) // Set hp & chakar when character is not awaken
		{
			setMaxHP(metadata.hp);
			setHP(metadata.hp);
			setCKR(0);
			setCKR2(0);
		}
		setHPBarHeight(metadata.hpBarY);
		setWalkSpeed(metadata.speed);
		_originSpeed = metadata.speed;

		setKillNum(0);

		if (name == "Minato") // TODO: Move to Minato class
		{
			_sAttack1isDouble = true;
		}

		_isArmored = false;
		if (name == HeroEnum::Kiba)
		{
			_isArmored = true;
		}
		else if (name == HeroEnum::Kakuzu)
		{
			_heartEffect = newSprite("Heart_Effect_00");
			_heartEffect->setPosition(Vec2(getContentSize().width + 40, 70));
			addChild(_heartEffect);
		}

		// Heroes have 50 coins by default
		if (getLV() == 1 && getCoin() == 0) // TODO: Move to game layer
		{
			setCoin(50);
		}

		if (!getName().empty() && isPlayer())
		{
			auto oldCharName = getName();
			bool isUpdateUI = oldCharName != name;
			setName(name);

			if (isUpdateUI)
				getGameLayer()->updateHudSkillButtons();
		}
		else
		{
			setName(name);
		}

		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Unit::acceptAttack), "acceptAttack", nullptr);
	}

	void setShadows()
	{
		if (!_shadow)
		{
			_shadow = newSprite("shadows");
			_shadow->setAnchorPoint(Vec2(0.5, 0.5));
			_shadow->setPosition(getPosition());
			getGameLayer()->shadowBatch->addChild(_shadow);
		}
	}

	void setHPbar()
	{
		if (getGameLayer()->playerGroup != getGroup())
		{
			_hpBar = HPBar::create("hp_bar_r.png");
		}
		else if (isCom() || isClone() || isKugutsu() || isSummon())
		{
			_hpBar = HPBar::create("hp_bar_b.png");
		}
		else if (isPlayer())
		{
			_hpBar = HPBar::create("hp_bar.png");
		}
		_hpBar->setPositionY(getHPBarHeight());
		_hpBar->setDelegate(this);
		addChild(_hpBar);
		changeHPbar();
	}

	virtual void changeHPbar()
	{
		if (_exp >= 500 && _level == 1)
		{
			_level = 2;
			setCKR(getCKR() + 15000);
			_isCanOugis1 = true;
			if (isPlayer())
			{
				getGameLayer()->setCKRLose(false);
				getGameLayer()->removeOugisMark(1);
			}
			setMaxHPValue(getMaxHP() + 500);
			setNAttackValue(getNAttackValue() + 9);
			_rebornTime += 1;
		}
		else if (_exp >= 1000 && _level == 2)
		{
			_level = 3;
			setMaxHPValue(getMaxHP() + 1000);
			setNAttackValue(getNAttackValue() + 18);
			_rebornTime += 2;
		}
		else if (_exp >= 1500 && _level == 3)
		{
			_level = 4;
			setCKR2(getCKR2() + 25000);
			_isCanOugis2 = true;
			if (isPlayer())
			{
				getGameLayer()->setCKRLose(true);
				getGameLayer()->removeOugisMark(2);
			}
			setMaxHPValue(getMaxHP() + 2000);
			setNAttackValue(getNAttackValue() + 27);
			_rebornTime += 3;
		}
		else if (_exp >= 2000 && _level == 4)
		{
			_level = 5;
			setMaxHPValue(getMaxHP() + 2500);
			setNAttackValue(getNAttackValue() + 36);
			_rebornTime += 4;
		}
		else if (_exp >= 2500 && _level == 5)
		{
			_level = 6;
			setMaxHPValue(getMaxHP() + 3000);
			setNAttackValue(getNAttackValue() + 45);
			_rebornTime += 5;
		}

		if (_hpBar)
		{
			auto frame = getSpriteFrame("hp_bottom{}.png", _level);
			_hpBar->getHPBottom()->setDisplayFrame(frame);
		}
	}

	virtual void reborn(float dt)
	{
		if (!enableReborn)
		{
			// TODO: Spectating Mode
			// if (isPlayer())
			// getGameLayer()->getHudLayer()->enableSpectatingMode();
			return;
		}

		Unit::reborn(dt);
		// If the character has changed, then cleanup and return
		if (changeCharId > -1)
		{
			if (rebornSprite)
			{
				rebornSprite->removeFromParent();
				rebornSprite = nullptr;
			}
			checkRefCount(0);
			return;
		}

		setPosition(getSpawnPoint());

		if (getPosition().equals(getSpawnPoint()))
		{
			CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Unit::acceptAttack), "acceptAttack", nullptr);
			setOpacity(255);
			setHPValue(getMaxHP(), false);
			setHPbar();
			_state = State::HURT;

			if (getLV() < 4)
			{
				if (isKonohaGroup())
					setEXP(getEXP() + getGameLayer()->kEXPBound);
				else
					setEXP(getEXP() + getGameLayer()->aEXPBound);

				changeHPbar();

				if (isPlayer())
				{
					getGameLayer()->getHudLayer()->setEXPLose();
				}
			}

			if (isKonohaGroup())
			{
				if (_isFlipped)
				{
					setFlipX(false);
					_isFlipped = false;
				}
			}
			else
			{
				if (!_isFlipped)
				{
					setFlipX(true);
					_isFlipped = true;
				}
			}
			idle();
			if (rebornSprite)
			{
				unschedule(schedule_selector(Hero::countDown));
				rebornSprite->removeFromParent();
				rebornSprite = nullptr;
			}
			if (isNotPlayer())
			{
				doAI();
			}
			else
			{
				if (_isAI)
				{
					doAI();
				}
				getGameLayer()->getHudLayer()->status_hpbar->setOpacity(255);
				getGameLayer()->setHPLose(getHpPercent());
			}
			scheduleUpdate();
		}
		getGameLayer()->reorderChild(this, -getPositionY());
	}

	virtual void dealloc()
	{
		CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
		stopAllActions();
		_state = State::DEAD;

		if (!_monsterArray.empty() && getName() != HeroEnum::Minato)
		{
			for (auto mo : _monsterArray)
			{
				if (auto heroMo = dynamic_cast<Hero *>(mo))
				{
					heroMo->dealloc();
				}
				else
				{
					CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(mo);
					mo->stopAllActions();
					mo->unscheduleAllSelectors();
					mo->setState(State::DEAD);
					mo->removeFromParent();
				}
			}
			_monsterArray.clear();
		}

		if (isClone() || isKugutsu() || isSummon())
		{
			unschedule(schedule_selector(Unit::setAI));

			std::erase(getGameLayer()->_CharacterArray, this);
			getGameLayer()->clearAllFlogsMainTarget(this);

			if (_shadow)
				_shadow->removeFromParent();

			if (_master)
				_master->removeMon(this);

			removeFromParent();
		}
		else if (isNotGuardian())
		{
			if (rebornLabelTime == 3)
			{
				scheduleOnce(schedule_selector(Hero::reborn), 3.0f);
			}
			else
			{
				rebornLabelTime = getRebornTime();
				scheduleOnce(schedule_selector(Hero::reborn), getRebornTime());
			}
			if (!rebornSprite)
			{
				rebornSprite = Sprite::create();
				Sprite *skullSpirte = newSprite("skull.png");
				skullSpirte->setPosition(Vec2(0, 0));
				rebornSprite->addChild(skullSpirte);

				rebornLabel = CCLabelBMFont::create(to_cstr(rebornLabelTime), Fonts::Default);
				rebornLabel->setScale(0.3f);
				rebornLabel->setPosition(Vec2(skullSpirte->getContentSize().width, 0));
				rebornSprite->addChild(rebornLabel);

				rebornSprite->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2));
				addChild(rebornSprite);
			}
			schedule(schedule_selector(Hero::countDown), 1);
		}
		// Keep the guardian body
	}

	void doAI()
	{
		Unit::doAI();
		// Initial default AI handler
		aiHandler = std::bind(&Hero::perform, this);
	}

	/** Perform default AI logic (Hero::perform) */
	virtual void setAI(float dt)
	{
		// Not check nullable reference
		aiHandler();
		// proxy->perform(this);
	}

	/** Provide default AI logic */
	virtual void perform() = 0;

	/** Callback */

	/** Call on IGameModeHandler::onCharacterInit()
	 * @call_order:
	 * 	-> Unit::setID()
	 * 	-> IGameModeHandler::onCharacterInit()
	 */

	virtual bool isEnableSkill04()
	{
		return true;
	}

	virtual bool isEnableSkill05()
	{
		return true;
	}

	template <typename THero>
	static typename std::enable_if_t<std::is_base_of_v<Hero, THero>, THero *>
	create(const string &name, Role role, Group group)
	{
		THero *hero = new THero();
		if (hero->init())
		{
			hero->setID(name, role, group);
			hero->autorelease();
		}
		else
		{
			CCLOGERROR("Initial Hero %s error", typeof(THero));
			delete hero;
			return nullptr;
		}
		return hero;
	}

	template <typename THero>
	typename std::enable_if_t<std::is_base_of_v<Hero, THero>, THero *>
	createHero(const string &name, Role role) { return create<THero>(name, role, getGroup()); }

	template <typename THero>
	typename std::enable_if_t<std::is_base_of_v<Hero, THero>, THero *>
	createCloneHero(const string &name) { return createHero<THero>(name, Role::Clone); }

	template <typename THero>
	typename std::enable_if_t<std::is_base_of_v<Hero, THero>, THero *>
	createKugutsuHero(const string &name) { return createHero<THero>(name, Role::Kugutsu); }

	template <typename THero>
	typename std::enable_if_t<std::is_base_of_v<Hero, THero>, THero *>
	createSummonHero(const string &name) { return createHero<THero>(name, Role::Summon); }

/** Macros */
// eg.
//
// yourHero.hpp
//
// setAIHandler(yourHero::perform);						// Default	handler
// setAIHandler(yourHero::yourAIHandlerFunctionName);	// Custom	handler
#define setAIHandler(funcName) aiHandler = std::bind(&funcName, this)

	/** Character Macros */

#define match_char_exp(_name, _expr, _name2, _expr2) \
	if (getName() == _name)                          \
		_expr;                                       \
	else if (getName() == _name2)                    \
		_expr2;

#define match_char_exp3(_name, _expr, _name2, _expr2, _name3, _expr3)          \
	match_char_exp(_name, _expr, _name2, _expr2) else if (getName() == _name3) \
		_expr3;

#define match_char_exp4(_name, _expr, _name2, _expr2, _name3, _expr3, _name4, _expr4)           \
	match_char_exp3(_name, _expr, _name2, _expr2, _name3, _expr3) else if (getName() == _name4) \
		_expr4;

protected:
	void checkRefCount(float dt)
	{
		CCLOG("[Ref Check] %s has %d references", getName().c_str(), retainCount());
	}

	void countDown(float dt)
	{
		rebornLabelTime -= 1;
		rebornLabel->setString(to_cstr(rebornLabelTime));
	}

	AIHandler aiHandler = nullptr;
};
