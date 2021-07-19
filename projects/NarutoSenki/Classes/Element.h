#pragma once
#include "CharacterBase.h"
#include "HPBar.h"

class HeroElement : public CharacterBase
{
public:
	HeroElement();
	~HeroElement();

	bool init();
	void initAction();
	void setHPbar();
	void setShadows();
	virtual void changeHPbar();
	void checkRefCount(float dt);

	CCSprite *rebornSprite;
	CCLabelBMFont *rebornLabel;
	void reborn(float dt);
	void dealloc();

protected:
	void countDown(float dt);
};

class Monster : public CharacterBase
{
public:
	Monster();
	~Monster();

	CREATE_FUNC(Monster);
	bool init();
	void initAction();
	void setID(CCString *character, CCString *role, CCString *group);
	void setHPbar();
	void changeHPbar();
	void setDirectMove(int32_t length, float delay, bool isReverse);
	void setEaseIn(int32_t length, float delay);
	void setDirectMoveBy(int32_t length, float delay);

protected:
	void dealloc();
	void dealloc2();
	void setAI(float dt);
	void setResume();
};

#include "Core/Tower/Tower.hpp"

#include "Core/Warrior/Flog.hpp"

#include "Core/Bullet/Bullet.hpp"
