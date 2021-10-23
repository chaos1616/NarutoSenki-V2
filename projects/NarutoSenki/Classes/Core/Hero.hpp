#pragma once
#include "Element.h"

typedef std::function<void()> AIHandler;

//TODO: 合并 HeroElement Hero
class Hero : public HeroElement
{
private:
	// Hero *proxy = nullptr;

public:
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

	virtual void setID(CCString *character, CCString *role, CCString *group)
	{
		setRole(role);
		setGroup(group);

		auto charName = character->getCString();

		CCArray *animationArray = CCArray::create();
		const char *filePath = CCString::createWithFormat("Element/%s/%s.xml", charName, charName)->getCString();
		KTools::readXMLToArray(filePath, animationArray);

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

		if (getKillNum() == nullptr)
		{
			setKillNum(to_ccstring(0));
		}

		if (!getCKR() && !getCKR2())
		{
			setCkrValue(0);
			setCkr2Value(0);
		}

		//init WalkFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(1));
		walkArray = (CCArray *)(tmpAction->objectAtIndex(1));
		walkArray->retain();

		//init HurtFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(2));
		hurtArray = (CCArray *)(tmpAction->objectAtIndex(1));
		hurtArray->retain();

		//init AirHurtFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(3));
		airHurtArray = (CCArray *)(tmpAction->objectAtIndex(1));

		//init KnockDownFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(4));
		knockDownArray = (CCArray *)(tmpAction->objectAtIndex(1));
		knockDownArray->retain();

		//init FloatFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(5));
		floatArray = (CCArray *)(tmpAction->objectAtIndex(1));

		//init DeadFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(6));
		deadArray = (CCArray *)(tmpAction->objectAtIndex(1));

		//init nAttack data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(7));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		CCString *tmpValue;
		uint32_t tmpCD;
		readData(tmpData, _nattackType, tmpValue, _nattackRangeX, _nattackRangeY, tmpCD, tmpCombatPoint);
		setnAttackValue(tmpValue);

		nattackArray = (CCArray *)(tmpAction->objectAtIndex(1));
		nattackArray->retain();

		//init skill1 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(8));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));

		readData(tmpData, _sattackType1, tmpValue, _sattackRangeX1, _sattackRangeY1, _sattackcooldown1, _sattackCombatPoint1);
		setsAttackValue1(tmpValue);

		skill1Array = (CCArray *)(tmpAction->objectAtIndex(1));

		//init skill2 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(9));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		readData(tmpData, _sattackType2, tmpValue, _sattackRangeX2, _sattackRangeY2, _sattackcooldown2, _sattackCombatPoint2);
		setsAttackValue2(tmpValue);
		skill2Array = (CCArray *)(tmpAction->objectAtIndex(1));

		if (is_same(charName, "Kakashi"))
		{
			skill1Array->retain();
			skill2Array->retain();
		}
		else if (is_same(charName, "Minato"))
		{
			skill1Array->retain();
			skill2Array->retain();
			_sattack1isDouble = true;
		}

		//init skill3 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(10));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		readData(tmpData, _sattackType3, tmpValue, _sattackRangeX3, _sattackRangeY3, _sattackcooldown3, _sattackCombatPoint3);
		setsAttackValue3(tmpValue);
		skill3Array = (CCArray *)(tmpAction->objectAtIndex(1));

		//init skill4 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(11));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		readData(tmpData, _sattackType4, tmpValue, _sattackRangeX4, _sattackRangeY4, _sattackcooldown4, _sattackCombatPoint4);
		setsAttackValue4(tmpValue);
		skill4Array = (CCArray *)(tmpAction->objectAtIndex(1));

		//init skill5 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(12));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		readData(tmpData, _sattackType5, tmpValue, _sattackRangeX5, _sattackRangeY5, _sattackcooldown5, _sattackCombatPoint5);
		setsAttackValue5(tmpValue);
		skill5Array = (CCArray *)(tmpAction->objectAtIndex(1));

		//initial specal animations
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

	/** Utilities functions */
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
			CCLOG("Initial Hero %s error", typeof(THero));
			delete hero;
			hero = nullptr;
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

/** UI Macros */
#define lockSkill4Button() \
	if (isPlayer())        \
		getGameLayer()->getHudLayer()->skill4Button->setLock();

#define unlockSkill4Button() \
	if (isPlayer())          \
		getGameLayer()->getHudLayer()->skill4Button->unLock();

#define lockSkill5Button() \
	if (isPlayer())        \
		getGameLayer()->getHudLayer()->skill5Button->setLock();

#define unlockSkill5Button() \
	if (isPlayer())          \
		getGameLayer()->getHudLayer()->skill5Button->unLock();

#define lockOugisButtons()                                      \
	if (isPlayer())                                             \
	{                                                           \
		getGameLayer()->getHudLayer()->skill4Button->setLock(); \
		getGameLayer()->getHudLayer()->skill5Button->setLock(); \
	}

#define unlockOugisButtons()                                   \
	if (isPlayer())                                            \
	{                                                          \
		getGameLayer()->getHudLayer()->skill4Button->unLock(); \
		getGameLayer()->getHudLayer()->skill5Button->unLock(); \
	}

protected:
	AIHandler aiHandler = nullptr;
};
