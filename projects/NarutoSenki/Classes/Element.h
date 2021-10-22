#pragma once
#include "CharacterBase.h"
#include "GameLayer.h"
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
	bool init();
	void initAction();
	void setID(CCString *character, CCString *role, CCString *group);
	void setHPbar();
	void changeHPbar();
	void setDirectMove(int length, float delay, bool isReverse);
	void setEaseIn(int length, float delay);
	void setDirectMoveBy(int length, float delay);

	CREATE_FUNC(Monster);

protected:
	void dealloc();
	void dealloc2();
	void setAI(float dt);
	void setResume();
};

#include "Core/Tower/Tower.hpp"

#include "Core/Warrior/Flog.hpp"

#include "Core/Bullet/Bullet.hpp"
