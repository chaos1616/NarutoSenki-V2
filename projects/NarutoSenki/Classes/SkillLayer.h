#pragma once
#include "Defines.h"

// declare menuButton
enum sbtnType
{
	Menu,
	Unlock1,
	Unlock2,
	skill1,
	skill2,
	skill3,
	Ougis1,
	Ougis2
};

class SelectLayer;

class SkillLayer : public CCLayer
{
public:
	SkillLayer();
	~SkillLayer();

	bool init();
	void initInterface();

	CREATE_FUNC(SkillLayer);

	void update(float dt);
	void setSkillExplain(sbtnType type);

	PROP(SelectLayer *, _selectLayer, Delegate);

private:
	const char *selectHero;

	CCSprite *_skillExplain;

	CCLabelBMFont *coinLabel;

	CCLayer *buyLayer;
	sbtnType _buyType;
	CCSprite *_heroFull;
	CCMenu *changemenu;
	bool _autoMove;

	CCSprite *fengSprite;
	CCSprite *fengSprite2;
	CCSprite *skillGroup;
	CCSprite *skillSprite;

	CCProgressTimer *bonds;

	void onCancel(CCObject *sender);

	void updateSkillGroup();
	void onChangeBtn(CCObject *sender);
	void onResume(CCObject *sender);
};

class SelectButton : public CCSprite, public CCTouchDelegate
{
public:
	SelectButton();
	~SelectButton();

	static SelectButton *create(const char *szImage);

	CC_SYNTHESIZE_RETAIN(CCString *, _charName, CharName);

	bool _isAviable;
	virtual bool init(const char *szImage);
	CCRect getRect();
	void click();
	int _clickTime;
	PROP(sbtnType, _btnType, BtnType);

	bool _isCanBuy;
	void setCanBuy(bool val) { _isCanBuy = val; };
	bool _isCanBuy2;
	void setCanBuy2(bool val) { _isCanBuy2 = val; };
	bool _isUnlock;
	void setUnlock(bool val) { _isUnlock = val; };

	PROP(SelectLayer *, _selectLayer, SelectLayer);
	PROP(SkillLayer *, _skillLayer, SkillLayer);

	void spriteToGrey();

protected:
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);

	inline bool containsTouchLocation(CCTouch *touch);
};
