#ifndef __CHARACTERS_H__
#define __CHARACTERS_H__
#include "Element.h"

typedef enum __AIFeatures
{
	NoFeature,
	/* Heor Awaken */
	Transform,
} AIFeatures;

class Hero;

class AI
{
public:
	virtual void perform(Hero *self) = 0;
};

class Hero : public HeroElement
{
private:
	AIFeatures feature = AIFeatures::NoFeature;
	AI *proxy = nullptr;

	virtual void perform() = 0;

public:
	AIFeatures getFeature() { return feature; };
	void setFeature(AIFeatures var) { feature = var; };

	virtual void setAI(float dt)
	{
		perform();
		// proxy->perform(this);
	};

	void setID(CCString *character, CCString *role, CCString *group)
	{
		this->setCharacter(character);
		this->setRole(role);
		this->setGroup(group);

		CCArray *animationArray = CCArray::create();
		const char *filePath;

		filePath = CCString::createWithFormat("Element/%s/%s.xml", this->getCharacter()->getCString(), this->getCharacter()->getCString())->getCString();

		// std::string key = KTools::getKeycode(filePath);
		// int id = KTools::checkMD5(filePath);

		// if(strcmp(key.c_str(),_delegate->KeyList[id])!=0){
		//return;
		// }

		KTools::readXMLToArray(filePath, animationArray);

		//init Attribute; & indleFrame

		CCArray *tmpAction = (CCArray *)(animationArray->objectAtIndex(0));
		CCArray *tmpDate = (CCArray *)(tmpAction->objectAtIndex(0));
		idleArray = (CCArray *)(tmpAction->objectAtIndex(1));

		CCString *tmpName;
		CCString *tmpHpMax;
		int tmpWidth;
		int tmpHeight;
		unsigned int tmpSpeed;
		int tmpCombatPoint;
		this->readDate(tmpDate, tmpName, tmpHpMax, tmpWidth, tmpHeight, tmpSpeed, tmpCombatPoint);
		this->setMaxHP(CCString::createWithFormat("%d", atoi(tmpHpMax->getCString())));
		this->setHP(CCString::create(this->getMaxHP()->getCString()));

		this->setHeight(tmpHeight);
		this->setWalkSpeed(tmpSpeed);
		_originSpeed = tmpSpeed;
		if (this->getKillNum() == NULL)
		{
			this->setKillNum(CCString::createWithFormat("%d", 0));
		}

		if (!this->getCKR() && !this->getCKR2())
		{
			this->setCKR(CCString::create("0"));
			this->setCKR2(CCString::create("0"));
		}

		//init WalkFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(1));
		walkArray = (CCArray *)(tmpAction->objectAtIndex(1));

		//init HurtFrame
		tmpAction = (CCArray *)(animationArray->objectAtIndex(2));
		hurtArray = (CCArray *)(tmpAction->objectAtIndex(1));

		if (strcmp(this->getCharacter()->getCString(), "Sasuke") == 0 ||
			strcmp(this->getCharacter()->getCString(), "ImmortalSasuke") == 0)
		{
			hurtArray->retain();
		}

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
		tmpDate = (CCArray *)(tmpAction->objectAtIndex(0));
		CCString *tmpValue;
		unsigned int tmpCD;
		this->readDate(tmpDate, _nattackType, tmpValue, _nattackRangeX, _nattackRangeY, tmpCD, tmpCombatPoint);
		this->setnAttackValue(tmpValue);
		_nattackType->retain();

		nattackArray = (CCArray *)(tmpAction->objectAtIndex(1));

		//init skill1 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(8));
		tmpDate = (CCArray *)(tmpAction->objectAtIndex(0));

		this->readDate(tmpDate, _sattackType1, tmpValue, _sattackRangeX1, _sattackRangeY1, _sattackcoldDown1, _sattackCombatPoint1);
		this->setsAttackValue1(tmpValue);
		_sattackType1->retain();

		skill1Array = (CCArray *)(tmpAction->objectAtIndex(1));

		//init skill2 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(9));
		tmpDate = (CCArray *)(tmpAction->objectAtIndex(0));
		this->readDate(tmpDate, _sattackType2, tmpValue, _sattackRangeX2, _sattackRangeY2, _sattackcoldDown2, _sattackCombatPoint2);
		_sattackType2->retain();
		this->setsAttackValue2(tmpValue);
		skill2Array = (CCArray *)(tmpAction->objectAtIndex(1));

		if (strcmp(this->getCharacter()->getCString(), "Kakashi") == 0)
		{
			skill1Array->retain();
			skill2Array->retain();
		}
		else if (strcmp(this->getCharacter()->getCString(), "Minato") == 0)
		{
			skill1Array->retain();
			skill2Array->retain();
			_sattack1isDouble = true;
		}

		//init skill3 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(10));
		tmpDate = (CCArray *)(tmpAction->objectAtIndex(0));
		this->readDate(tmpDate, _sattackType3, tmpValue, _sattackRangeX3, _sattackRangeY3, _sattackcoldDown3, _sattackCombatPoint3);
		_sattackType3->retain();
		this->setsAttackValue3(tmpValue);
		skill3Array = (CCArray *)(tmpAction->objectAtIndex(1));

		//init skill4 data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(11));
		tmpDate = (CCArray *)(tmpAction->objectAtIndex(0));
		this->readDate(tmpDate, _sattackType4, tmpValue, _sattackRangeX4, _sattackRangeY4, _sattackcoldDown4, _sattackCombatPoint4);
		this->setsAttackValue4(tmpValue);
		_sattackType4->retain();
		skill4Array = (CCArray *)(tmpAction->objectAtIndex(1));

		//init skill5 data & Frame Array

		tmpAction = (CCArray *)(animationArray->objectAtIndex(12));
		tmpDate = (CCArray *)(tmpAction->objectAtIndex(0));
		this->readDate(tmpDate, _sattackType5, tmpValue, _sattackRangeX5, _sattackRangeY5, _sattackcoldDown5, _sattackCombatPoint5);
		this->setsAttackValue5(tmpValue);
		_sattackType5->retain();
		skill5Array = (CCArray *)(tmpAction->objectAtIndex(1));

		//init specal Frame

		if (
			strcmp(this->getCharacter()->getCString(), "Tenten") == 0 ||
			strcmp(this->getCharacter()->getCString(), "DevaPath") == 0 ||
			strcmp(this->getCharacter()->getCString(), "Ino") == 0 ||
			strcmp(this->getCharacter()->getCString(), "Sakura") == 0 ||
			strcmp(this->getCharacter()->getCString(), "Tobi") == 0 ||
			strcmp(this->getCharacter()->getCString(), "RockLee") == 0)
		{
			tmpAction = (CCArray *)(animationArray->objectAtIndex(17));
			tmpDate = (CCArray *)(tmpAction->objectAtIndex(0));
			this->readDate(tmpDate, _spcattackType1, tmpValue, _spcattackRangeX1, _spcattackRangeY1, _spcattackcoldDown1, tmpCombatPoint);
			this->setspcAttackValue1(tmpValue);
			_spcattackType1->retain();
			skillSPC1Array = (CCArray *)(tmpAction->objectAtIndex(1));
			skillSPC1Array->retain();
		}
		else if (strcmp(this->getCharacter()->getCString(), "Sai") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Deidara") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "SageNaruto") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "RikudoNaruto") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Suigetsu") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Jugo") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Kakashi") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Itachi") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Minato") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "ImmortalSasuke") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Sasuke") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Choji") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Tsunade") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Gaara") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Hidan") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Shino") == 0 ||
				 strcmp(this->getCharacter()->getCString(), Guardian_Roshi) == 0 ||
				 strcmp(this->getCharacter()->getCString(), Guardian_Han) == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Hiruzen") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Kiba") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Akamaru") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Konan") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Naruto") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Parents") == 0 ||
				 strcmp(this->getCharacter()->getCString(), "Kisame") == 0)
		{

			tmpAction = (CCArray *)(animationArray->objectAtIndex(17));
			tmpDate = (CCArray *)(tmpAction->objectAtIndex(0));
			this->readDate(tmpDate, _spcattackType1, tmpValue, _spcattackRangeX1, _spcattackRangeY1, _spcattackcoldDown1, tmpCombatPoint);
			this->setspcAttackValue1(tmpValue);
			_spcattackType1->retain();
			skillSPC1Array = (CCArray *)(tmpAction->objectAtIndex(1));
			skillSPC1Array->retain();

			tmpAction = (CCArray *)(animationArray->objectAtIndex(18));
			tmpDate = (CCArray *)(tmpAction->objectAtIndex(0));
			this->readDate(tmpDate, _spcattackType2, tmpValue, _spcattackRangeX2, _spcattackRangeY2, _spcattackcoldDown2, tmpCombatPoint);
			skillSPC2Array = (CCArray *)(tmpAction->objectAtIndex(1));
			this->setspcAttackValue2(tmpValue);
			_spcattackType2->retain();
			skillSPC2Array->retain();

			tmpAction = (CCArray *)(animationArray->objectAtIndex(19));
			tmpDate = (CCArray *)(tmpAction->objectAtIndex(0));
			this->readDate(tmpDate, _spcattackType3, tmpValue, _spcattackRangeX3, _spcattackRangeY3, _spcattackcoldDown3, tmpCombatPoint);
			skillSPC3Array = (CCArray *)(tmpAction->objectAtIndex(1));
			this->setspcAttackValue3(tmpValue);
			_spcattackType3->retain();
			skillSPC3Array->retain();
		}

		if (strcmp(this->getCharacter()->getCString(), "Itachi") == 0 ||
			strcmp(this->getCharacter()->getCString(), "Choji") == 0 ||
			strcmp(this->getCharacter()->getCString(), "Kiba") == 0 ||
			strcmp(this->getCharacter()->getCString(), "Naruto") == 0 ||
			strcmp(this->getCharacter()->getCString(), "SageNaruto") == 0 ||
			strcmp(this->getCharacter()->getCString(), "RikudoNaruto") == 0 ||
			strcmp(this->getCharacter()->getCString(), "Sasuke") == 0 ||
			strcmp(this->getCharacter()->getCString(), "ImmortalSasuke") == 0)
		{
			tmpAction = (CCArray *)(animationArray->objectAtIndex(16));
			skillSPC4Array = (CCArray *)(tmpAction->objectAtIndex(1));
			skillSPC4Array->retain();
		}

		if (strcmp(this->getCharacter()->getCString(), "Sasuke") == 0 ||
			strcmp(this->getCharacter()->getCString(), "SageNaruto") == 0)
		{
			tmpAction = (CCArray *)(animationArray->objectAtIndex(15));
			skillSPC5Array = (CCArray *)(tmpAction->objectAtIndex(1));
			skillSPC5Array->retain();
		}

		if (strcmp(this->getCharacter()->getCString(), "Kiba") == 0)
		{
			_isBati = true;
		}
		if (strcmp(this->getCharacter()->getCString(), "Kakuzu") == 0)
		{
			_heartEffect = CCSprite::createWithSpriteFrameName("Heart_Effect_00.png");
			_heartEffect->setPosition(ccp(this->getContentSize().width + 40, 70));
			this->addChild(_heartEffect);
		}

		_damageArray = CCArray::create();
		_damageArray->retain();

		if (this->getLV() == 1 && !this->getCoin())
		{
			this->setGearArray(CCArray::create());
			this->setCoin(CCString::create("50"));
		}

		this->initAction();
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CharacterBase::acceptAttack), "acceptAttack", NULL);

		checkFeature();
	};

	void checkFeature()
	{
		// Check hero's feature
		switch (feature)
		{
		case AIFeatures::Transform:
			// proxy = AIProvider::create(getCharacter(), getRole(), getGroup());
			break;
		case AIFeatures::NoFeature:
		default:
			// if (proxy == nullptr)
			// {
			// 	proxy = AIProvider::create(getCharacter(), getRole(), getGroup());
			// }
			break;
		}
	};
};

#endif
