#ifndef __ELEMENT_H__
#define __ELEMENT_H__
#include "CharacterBase.h"
#include "HPBar.h"
#include "Characters.h"

class HPBar;

typedef enum __AIFeatures
{
	NoFeature,
	HasClone,
} AIFeatures;

class Hero : public CharacterBase
{
private:
	virtual void perform() = 0;

public:
	Hero(void);
	~Hero(void);

	bool init();
	void initAction();
	void setHPbar();
	void setShadows();
	void changeHPbar();
	void neicun(float dt);
	virtual void setID(CCString *character, CCString *role, CCString *group);
	void setAI(float dt) { perform(); };

	CCSprite *rebornSprite;
	CCLabelBMFont *rebornLabel;
	void reborn(float dt);
	void dealloc();

	void setAIFeature(AIFeatures var) { features = var; };
	AIFeatures getAIFeature() const { return features; };

	virtual bool setSource(const char *target) = 0;

protected:
	AIFeatures features;

	void countDown(float dt);
};

class Flog : public CharacterBase
{
public:
	Flog(void);
	~Flog(void);

	CREATE_FUNC(Flog);
	bool init();
	void initAction();
	void setHPbar();

	float _mainPosY;
	float _randomPosX;
	float _randomPosY;

	void setID(CCString *character, CCString *role, CCString *group);

protected:
	void dealloc();
	void setAI(float dt);
};

class Tower : public CharacterBase
{
public:
	Tower(void);
	~Tower(void);

	CREATE_FUNC(Tower);
	bool init();
	void initAction();
	void setHPbar();
	void dealloc();
	void setID(CCString *character, CCString *role, CCString *group);
};

class Monster : public CharacterBase
{
public:
	Monster(void);
	~Monster(void);

	CREATE_FUNC(Monster);
	bool init();
	void initAction();
	void setID(CCString *character, CCString *role, CCString *group);
	void setHPbar();
	void changeHPbar();
	void setDirectMove(unsigned int length, float delay, bool isReverse);
	void setEaseIn(unsigned int length, float delay);
	void setDirectMoveBy(unsigned int length, float delay);

protected:
	void dealloc();
	void dealloc2();
	void setAI(float dt);
	void setResume();
};

class Bullet : public CharacterBase
{
public:
	Bullet(void);
	~Bullet(void);

	CREATE_FUNC(Bullet);
	bool init();
	void initAction();
	void setID(CCString *character, CCString *role, CCString *group);

	void setMove(unsigned int length, float delay, bool isReverse);
	void setEaseIn(unsigned int length, float delay);

	void setAttack(float dt);

protected:
	void dealloc();
	void dealloc2();
};
#endif
