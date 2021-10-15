#pragma once
#include "Defines.h"

class GameLayer;
class ScrewLayer;

enum class GearButtonType
{
	Buy,
	Sell
};

class GearLayer : public CCLayer
{
public:
	GearLayer();
	~GearLayer();

	bool init(CCRenderTexture *snapshoot);

	CCLayer *gears_layer = nullptr;
	CCLayer *currentGear_layer = nullptr;
	CCLabelBMFont *coinLabel = nullptr;

	CCSprite *gearDetail = nullptr;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	CCSprite *gearBigIcon;
#endif
	CCSprite *gears_bg = nullptr;

	ScrewLayer *_screwLayer = nullptr;
	gearType currentGear = None;
	void updatePlayerGear();
	void updateGearList();
	void confirmPurchase();

	static GearLayer *create(CCRenderTexture *snapshoot);

private:
	void onResume(CCObject *sender);
	void onGearBuy(CCObject *sender);
};

class GearButton : public CCSprite, public CCTouchDelegate
{
public:
	bool init(const char *szImage);

	bool _isBuyed;
	gearType _gearType;
	GearButtonType _btnType;
	CCSprite *soIcon;
	CC_SYNTHESIZE(GearLayer *, _delegate, Delegate);

	CCRect getRect();
	void setBtnType(gearType gearType, GearButtonType btnType, bool isBuyed);
	gearType getBtnType();
	void playSound();
	void click();

	static GearButton *create(const char *szImage);

protected:
	void onEnter();
	void onExit();
	bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	void ccTouchMoved(CCTouch *touch, CCEvent *event);
	void ccTouchEnded(CCTouch *touch, CCEvent *event);

	inline bool containsTouchLocation(CCTouch *touch);
};

class ScrewLayer : public CCLayer
{
public:
	bool init();

	float prePosY;
	CC_SYNTHESIZE(GearLayer *, _delegate, Delegate);

	CCSprite *screwBar;

	int totalRow;
	int gearNum;
	PROP_SREF(vector<GearButton *>, _gearArray, GearArray);

	CREATE_FUNC(ScrewLayer);

protected:
	bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	void ccTouchMoved(CCTouch *touch, CCEvent *event);
	void ccTouchEnded(CCTouch *touch, CCEvent *event);

	void onEnter();
	void onExit();
};