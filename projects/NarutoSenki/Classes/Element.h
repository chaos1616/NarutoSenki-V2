#pragma once
#include "cocos2d.h"
#include "CharacterBase.h"
#include "HPBar.h"
#include "cocos-ext.h"

USING_NS_CC;

class HPBar;

class HeroElement : public CharacterBase  {
public:
	HeroElement(void);
	~HeroElement(void);

	//CREATE_FUNC(HeroElement);
	bool	init();
	void	initAction();
	void	setHPbar();
	void	setShadows();
	void    changeHPbar();
	void	neicun(float dt);
	virtual void setID(CCString* character,CCString* role,CCString* group);
	virtual void setAI(float dt);


	CCSprite* rebornSprite;
	CCLabelBMFont* rebornLabel;
	void	reborn(float dt);
	void	dealloc();

protected: 
	
	
	void	countDown(float dt);
};


class Flog: public CharacterBase{
public:
	Flog(void);
	~Flog(void);

	CREATE_FUNC(Flog);
	bool	init();
	void	initAction();
	void	setHPbar();

	float   _mainPosY;
	float	_randomPosX;
	float	_randomPosY;

	void	setID(CCString* character,CCString* role,CCString* group);
	

protected: 
	void	dealloc();
	void	setAI(float dt);


};

class Tower: public CharacterBase{
public:
	Tower(void);
	~Tower(void);

	CREATE_FUNC(Tower);
	bool	init();
	void	initAction();
	void	setHPbar();
	void	dealloc();    
	void	setID(CCString* character,CCString* role,CCString* group);

};


class Monster: public CharacterBase{
public:
	Monster(void);
	~Monster(void);

	CREATE_FUNC(Monster);
	bool	init();
	void	initAction(); 
	void	setID(CCString* character,CCString* role,CCString* group);
	void	setHPbar();
	void    changeHPbar();
	void	setDirectMove(unsigned int length,float delay,bool isReverse);
	void	setEaseIn(unsigned int length,float delay);
	void	setDirectMoveBy(unsigned int length,float delay);
protected: 
	void	dealloc();
	void	dealloc2();
	void	setAI(float dt);
	void	setResume();
	
};

class Bullet: public CharacterBase{
public:
	Bullet(void);
	~Bullet(void);

	CREATE_FUNC(Bullet);
	bool	init();
	void	initAction(); 
	void	setID(CCString* character,CCString* role,CCString* group);
	
	void	setMove(unsigned int length,float delay,bool isReverse);
	void	setEaseIn(unsigned int length,float delay);
	
	void    setAttack(float dt);

protected: 
	
	void	dealloc();
	void    dealloc2();

};