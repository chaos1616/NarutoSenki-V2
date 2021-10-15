#pragma once
#include "Defines.h"

class HudLayer;

class ActionButton : public CCSprite, public CCTouchDelegate
{
public:
	ActionButton();
	~ActionButton();

	int _clickNum;
	float _clickTime;
	CCProgressTimer *markSprite;
	CCSprite *ougismarkSprite;
	CCSprite *proressmarkSprite;
	CCSprite *proressblinkSprite;
	CCSprite *progressPointSprite;
	CCSprite *proressblinkMask;
	const char *_cost;
	CCClippingNode *clipper;
	bool _isLock;

	bool _isColdChanged;

	bool init(const char *szImage);
	bool isCanClick();
	CCRect getRect();

	void click();
	void setMarkSprite(const char *mark);
	void setOugisMark();
	void setProgressMark();
	void updateProgressMark();
	void reset();

	CCSprite *gearSign;
	CCLabelBMFont *cdLabel;

	CCLabelBMFont *lockLabel1;
	CCLabelBMFont *lockLabel2;

	bool _isMarkVisable;

	PROP(abType, _abType, ABType);
	gearType _gearType;

	CC_SYNTHESIZE_RETAIN(CCString *, _cooldown, CD);
	PROP(bool, _isDoubleSkill, DoubleSkill);
	CC_SYNTHESIZE_RETAIN(CCString *, _timeCout, TimeCout);

	void setLock();
	void unLock();
	void clearOugisMark();
	void setGearType(int tmpGearType);

	CC_SYNTHESIZE_RETAIN(CCAction *, _freezeAction, FreezeAction);
	//CC_SYNTHESIZE_RETAIN(CCProgressTimer*,markSprite,MarkSprite);
	CC_SYNTHESIZE(HudLayer *, _delegate, Delegate);
	void beganAnimation(bool isLock = false);
	void updateCDLabel(float dt);

	static ActionButton *create(const char *szImage);

protected:
	void onEnter();
	void onExit();
	bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	void ccTouchEnded(CCTouch *touch, CCEvent *event);

	void createFreezeAnimation();
	void clearClick();

	bool containsTouchLocation(CCTouch *touch);
};
