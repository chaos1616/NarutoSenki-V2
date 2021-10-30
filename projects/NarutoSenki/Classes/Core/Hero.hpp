#pragma once
#include "Element.h"

typedef std::function<void()> AIHandler;

class Hero : public CharacterBase
{
	friend class CommandSystem;

private:
	CCSprite *rebornSprite = nullptr;
	CCLabelBMFont *rebornLabel = nullptr;
	// Hero *proxy = nullptr;

public:
	Hero()
	{
	}

	~Hero()
	{
		CC_SAFE_RELEASE(idleArray);
		CC_SAFE_RELEASE(walkArray);
		CC_SAFE_RELEASE(deadArray);
		CC_SAFE_RELEASE(hurtArray);
		CC_SAFE_RELEASE(airHurtArray);
		CC_SAFE_RELEASE(floatArray);
		CC_SAFE_RELEASE(knockDownArray);
		CC_SAFE_RELEASE(nattackArray);
		CC_SAFE_DELETE(skillSPC1Array);
		CC_SAFE_RELEASE(skillSPC2Array);
		CC_SAFE_RELEASE(skillSPC3Array);
		CC_SAFE_RELEASE(skillSPC4Array);
		CC_SAFE_RELEASE(skillSPC5Array);
		CC_SAFE_RELEASE(skill1Array);
		CC_SAFE_RELEASE(skill2Array);
		CC_SAFE_RELEASE(skill3Array);
		CC_SAFE_RELEASE(skill4Array);
		CC_SAFE_RELEASE(skill5Array);
	}

	bool init()
	{
		RETURN_FALSE_IF(!CharacterBase::init());

		setAnchorPoint(ccp(0.5, 0));
		scheduleUpdate();

		return true;
	}

	virtual void setID(CCString *character, CCString *role, CCString *group)
	{
		setRole(role);
		setGroup(group);

		auto charName = character->getCString();

		CCArray *animationArray = CCArray::create();
		auto filePath = format("Element/{}/{}.xml", charName, charName);
		KTools::readXMLToArray(filePath.c_str(), animationArray);

		// init
		CCArray *tmpAction = (CCArray *)(animationArray->objectAtIndex(0));
		CCArray *tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		idleArray = (CCArray *)(tmpAction->objectAtIndex(1));
		idleArray->retain();

		CCString *tmpName;
		CCString *tmpHpMax;
		int tmpWidth;
		int tmpHeight;
		uint32_t tmpSpeed;
		int tmpCombatPoint;
		readData(tmpData, tmpName, tmpHpMax, tmpWidth, tmpHeight, tmpSpeed, tmpCombatPoint);
		if (!getCharacter()) // Set hp when character is not awaken
		{
			setMaxHPValue(tmpHpMax->uintValue(), false);
			setHPValue(getMaxHPValue(), false);
		}
		setHeight(tmpHeight);
		setWalkSpeed(tmpSpeed);
		_originSpeed = tmpSpeed;

		setKillNum(0);

		if (!getCKR() && !getCKR2())
		{
			setCkrValue(0);
			setCkr2Value(0);
		}

		// init WalkFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(1));
		walkArray = (CCArray *)(tmpAction->objectAtIndex(1));
		walkArray->retain();

		// init HurtFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(2));
		hurtArray = (CCArray *)(tmpAction->objectAtIndex(1));
		hurtArray->retain();

		// init AirHurtFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(3));
		airHurtArray = (CCArray *)(tmpAction->objectAtIndex(1));

		// init KnockDownFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(4));
		knockDownArray = (CCArray *)(tmpAction->objectAtIndex(1));
		knockDownArray->retain();

		// init FloatFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(5));
		floatArray = (CCArray *)(tmpAction->objectAtIndex(1));
		floatArray->retain();

		// init DeadFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(6));
		deadArray = (CCArray *)(tmpAction->objectAtIndex(1));
		deadArray->retain();

		// init nAttack data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(7));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		CCString *tmpValue;
		uint32_t tmpCD;
		readData(tmpData, _nattackType, tmpValue, _nattackRangeX, _nattackRangeY, tmpCD, tmpCombatPoint);
		setnAttackValue(tmpValue);

		nattackArray = (CCArray *)(tmpAction->objectAtIndex(1));
		nattackArray->retain();

		// init skill1 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(8));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));

		readData(tmpData, _sattackType1, tmpValue, _sattackRangeX1, _sattackRangeY1, _sattackcooldown1, _sattackCombatPoint1);
		setsAttackValue1(tmpValue);

		skill1Array = (CCArray *)(tmpAction->objectAtIndex(1));
		skill1Array->retain();

		// init skill2 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(9));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		readData(tmpData, _sattackType2, tmpValue, _sattackRangeX2, _sattackRangeY2, _sattackcooldown2, _sattackCombatPoint2);
		setsAttackValue2(tmpValue);
		skill2Array = (CCArray *)(tmpAction->objectAtIndex(1));
		skill2Array->retain();

		if (is_same(charName, "Kakashi"))
		{
		}
		else if (is_same(charName, "Minato"))
		{
			_sattack1isDouble = true;
		}

		// init skill3 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(10));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		readData(tmpData, _sattackType3, tmpValue, _sattackRangeX3, _sattackRangeY3, _sattackcooldown3, _sattackCombatPoint3);
		setsAttackValue3(tmpValue);
		skill3Array = (CCArray *)(tmpAction->objectAtIndex(1));
		skill3Array->retain();

		// init skill4 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(11));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		readData(tmpData, _sattackType4, tmpValue, _sattackRangeX4, _sattackRangeY4, _sattackcooldown4, _sattackCombatPoint4);
		setsAttackValue4(tmpValue);
		skill4Array = (CCArray *)(tmpAction->objectAtIndex(1));
		skill4Array->retain();

		// init skill5 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(12));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		readData(tmpData, _sattackType5, tmpValue, _sattackRangeX5, _sattackRangeY5, _sattackcooldown5, _sattackCombatPoint5);
		setsAttackValue5(tmpValue);
		skill5Array = (CCArray *)(tmpAction->objectAtIndex(1));
		skill5Array->retain();

		// initial specal animations
		while (1)
		{
			CC_BREAK_IF(animationArray->count() <= 17);
			tmpAction = (CCArray *)(animationArray->objectAtIndex(17));
			tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
			readData(tmpData, _spcattackType1, tmpValue, _spcattackRangeX1, _spcattackRangeY1, _spcattackcooldown1, tmpCombatPoint);
			if (!_spcattackType1.empty())
			{
				skillSPC1Array = (CCArray *)(tmpAction->objectAtIndex(1));
				setspcAttackValue1(tmpValue);
				skillSPC1Array->retain();
			}
			CC_BREAK_IF(animationArray->count() <= 18);
			tmpAction = (CCArray *)(animationArray->objectAtIndex(18));
			tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
			readData(tmpData, _spcattackType2, tmpValue, _spcattackRangeX2, _spcattackRangeY2, _spcattackcooldown2, tmpCombatPoint);
			if (!_spcattackType2.empty())
			{
				skillSPC2Array = (CCArray *)(tmpAction->objectAtIndex(1));
				setspcAttackValue2(tmpValue);
				skillSPC2Array->retain();
			}
			CC_BREAK_IF(animationArray->count() <= 19);
			tmpAction = (CCArray *)(animationArray->objectAtIndex(19));
			tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
			readData(tmpData, _spcattackType3, tmpValue, _spcattackRangeX3, _spcattackRangeY3, _spcattackcooldown3, tmpCombatPoint);
			if (!_spcattackType3.empty())
			{
				skillSPC3Array = (CCArray *)(tmpAction->objectAtIndex(1));
				setspcAttackValue3(tmpValue);
				skillSPC3Array->retain();
			}
			break;
		}

		if (is_same(charName, "Itachi") ||
			is_same(charName, "Choji") ||
			is_same(charName, "Kiba") ||
			is_same(charName, "Naruto") ||
			is_same(charName, "SageNaruto") ||
			is_same(charName, "RikudoNaruto") ||
			is_same(charName, "Sasuke") ||
			is_same(charName, "ImmortalSasuke"))
		{
			tmpAction = (CCArray *)(animationArray->objectAtIndex(16));
			skillSPC4Array = (CCArray *)(tmpAction->objectAtIndex(1));
			skillSPC4Array->retain();
		}

		if (is_same(charName, "Sasuke") ||
			is_same(charName, "SageNaruto"))
		{
			tmpAction = (CCArray *)(animationArray->objectAtIndex(15));
			skillSPC5Array = (CCArray *)(tmpAction->objectAtIndex(1));
			skillSPC5Array->retain();
		}
		else if (is_same(charName, "Kiba"))
		{
			_isArmored = true;
		}
		else if (is_same(charName, "Kakuzu"))
		{
			_heartEffect = CCSprite::createWithSpriteFrameName("Heart_Effect_00");
			_heartEffect->setPosition(ccp(getContentSize().width + 40, 70));
			addChild(_heartEffect);
		}
		else
		{
			// reset value
			_isArmored = false;
		}

		if (getLV() == 1 && !getCoin())
		{
			setCoin(50);
		}

		if (getCharacter())
		{
			// update player UI
			if (isPlayer())
			{
				auto oldCharName = getCharacter()->getCString();
				bool isUpdateUI = strcmp(oldCharName, charName) != 0;
				setCharacter(character);

				if (isUpdateUI)
					getGameLayer()->updateHudSkillButtons();
			}
		}
		else
		{
			setCharacter(character);
		}

		initAction();
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CharacterBase::acceptAttack), "acceptAttack", nullptr);
	}

	void initAction()
	{
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));
		setHurtAction(createAnimation(hurtArray, 10.0f, false, false));

		setAirHurtAction(createAnimation(airHurtArray, 10.0f, false, false));
		setKnockDownAction(createAnimation(knockDownArray, 10.0f, false, true));
		setDeadAction(createAnimation(deadArray, 10.0f, false, false));
		setFloatAction(createAnimation(floatArray, 10.0f, false, false));

		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));
		setSkill1Action(createAnimation(skill1Array, 10.0f, false, true));
		setSkill2Action(createAnimation(skill2Array, 10.0f, false, true));
		setSkill3Action(createAnimation(skill3Array, 10.0f, false, true));
		setSkill4Action(createAnimation(skill4Array, 10.0f, false, true));
		setSkill5Action(createAnimation(skill5Array, 10.0f, false, true));
	}

	void setShadows()
	{
		if (!_shadow)
		{
			_shadow = CCSprite::createWithSpriteFrameName("shadows");
			_shadow->setAnchorPoint(ccp(0.5, 0.5));
			_shadow->setPosition(getPosition());
			getGameLayer()->shadowBatch->addChild(_shadow);
		}
	}

	void setHPbar()
	{
		if (getGameLayer()->playerGroup != getGroup()->getCString())
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
		_hpBar->setPositionY(getHeight());
		_hpBar->setDelegate(this);
		addChild(_hpBar);
		changeHPbar();
	}

	virtual void changeHPbar()
	{
		if (_exp >= 500 && _level == 1)
		{
			_level = 2;
			uint32_t newValue = getCkrValue() + 15000;
			setCkrValue(newValue);
			_isCanOugis1 = true;
			if (isPlayer())
			{
				getGameLayer()->setCKRLose(false);
				getGameLayer()->removeOugisMark(1);
			}
			uint32_t tempMaxHP = getMaxHPValue();
			tempMaxHP += 500;
			setMaxHPValue(tempMaxHP);
			setnAttackValue(to_ccstring(getNAttackValue() + 9));
			_rebornTime += 1;
		}
		else if (_exp >= 1000 && _level == 2)
		{
			_level = 3;
			uint32_t tempMaxHP = getMaxHPValue();
			tempMaxHP += 1000;
			setMaxHPValue(tempMaxHP);
			setnAttackValue(to_ccstring(getNAttackValue() + 18));
			_rebornTime += 2;
		}
		else if (_exp >= 1500 && _level == 3)
		{
			_level = 4;
			uint32_t newValue = getCkr2Value() + 25000;
			setCkr2Value(newValue);
			_isCanOugis2 = true;
			if (isPlayer())
			{
				getGameLayer()->setCKRLose(true);
				getGameLayer()->removeOugisMark(2);
			}
			uint32_t tempMaxHP = getMaxHPValue();
			tempMaxHP += 2000;
			setMaxHPValue(tempMaxHP);
			setnAttackValue(to_ccstring(getNAttackValue() + 27));
			_rebornTime += 3;
		}
		else if (_exp >= 2000 && _level == 4)
		{
			_level = 5;
			uint32_t tempMaxHP = getMaxHPValue();
			tempMaxHP += 2500;
			setMaxHPValue(tempMaxHP);
			setnAttackValue(to_ccstring(getNAttackValue() + 36));
			_rebornTime += 4;
		}
		else if (_exp >= 2500 && _level == 5)
		{
			_level = 6;
			uint32_t tempMaxHP = getMaxHPValue();
			tempMaxHP += 3000;
			setMaxHPValue(tempMaxHP);
			setnAttackValue(to_ccstring(getNAttackValue() + 45));
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

		CharacterBase::reborn(dt);
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
			CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CharacterBase::acceptAttack), "acceptAttack", nullptr);
			setOpacity(255);
			setHPValue(getMaxHPValue(), false);
			setHPbar();
			_actionState = State::HURT;

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
		_actionState = State::DEAD;

		if (isNotCharacter("Minato"))
		{
			for (auto mo : _monsterArray)
			{
				CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(mo);
				if ((Hero *)mo != nullptr)
					std::erase(getGameLayer()->_CharacterArray, (Hero *)mo);
				mo->stopAllActions();
				mo->unscheduleAllSelectors();
				mo->setActionState(State::DEAD);
				mo->removeFromParent();
			}
			_monsterArray.clear();
		}

		if (isClone() || isKugutsu() || isSummon())
		{
			unschedule(schedule_selector(CharacterBase::setAI));

			std::erase(getGameLayer()->_CharacterArray, this);

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
				rebornSprite = CCSprite::create();
				CCSprite *skullSpirte = CCSprite::createWithSpriteFrameName("skull.png");
				skullSpirte->setPosition(ccp(0, 0));
				rebornSprite->addChild(skullSpirte);

				rebornLabel = CCLabelBMFont::create(to_cstr(rebornLabelTime), "Fonts/1.fnt");
				rebornLabel->setScale(0.3f);
				rebornLabel->setPosition(ccp(skullSpirte->getContentSize().width, 0));
				rebornSprite->addChild(rebornLabel);

				rebornSprite->setPosition(ccp(getContentSize().width / 2, getContentSize().height / 2));
				addChild(rebornSprite);
			}
			schedule(schedule_selector(Hero::countDown), 1);
		}
	}

	void doAI()
	{
		CharacterBase::doAI();
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
	 * 	-> CharacterBase::setID()
	 * 	-> IGameModeHandler::onCharacterInit()
	 */

	virtual bool isEnableSkill04() { return true; }
	virtual bool isEnableSkill05() { return true; }

	template <typename THero>
	typename std::enable_if<std::is_base_of<Hero, THero>::value, THero *>::type
	// typename enable_if<!is_same<Hero, THero>::value && is_base_of<Hero, THero>::value, THero *>::type
	create(CCString *character, CCString *role, CCString *group)
	{
		THero *hero = new THero();
		if (hero->init())
		{
			hero->setID(character, role, group);
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

/** Macros */
// eg.
//
// yourHero.hpp
//
// setAIHandler(yourHero::perform);						// Default	handler
// setAIHandler(yourHero::yourAIHandlerFunctionName);	// Custom	handler
#define setAIHandler(funcName) aiHandler = std::bind(&funcName, this)

	/** Character Macros */

#define match_char_exp(_name, _fn, _name2, _fn2) \
	if (isCharacter(_name))                      \
		_fn;                                     \
	else if (isCharacter(_name2))                \
		_fn2;

#define match_char_exp3(_name, _fn, _name2, _fn2, _name3, _fn3)            \
	match_char_exp(_name, _fn, _name2, _fn2) else if (isCharacter(_name3)) \
		_fn3;

#define match_char_exp4(_name, _fn, _name2, _fn2, _name3, _fn3, _name4, _fn4)             \
	match_char_exp3(_name, _fn, _name2, _fn2, _name3, _fn3) else if (isCharacter(_name4)) \
		_fn4;

protected:
	void checkRefCount(float dt)
	{
		CCLOG("[Ref Check] %s has %d references", getCharacter()->getCString(), retainCount());
	}

	void countDown(float dt)
	{
		rebornLabelTime -= 1;
		rebornLabel->setString(to_cstr(rebornLabelTime));
	}

	AIHandler aiHandler = nullptr;
};
