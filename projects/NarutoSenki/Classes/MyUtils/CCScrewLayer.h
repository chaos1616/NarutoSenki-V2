#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CCScrewLayer : public CCLayer
{
public:
	CCScrewLayer();
	~CCScrewLayer();

	float prePosY;
	float minY;
	int totalRow;
	int line_height;
	CC_SYNTHESIZE_RETAIN(CCArray *, itemArray, ItemArray);

	CREATE_FUNC(CCScrewLayer);

protected:
	bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	void ccTouchMoved(CCTouch *touch, CCEvent *event);
	void ccTouchEnded(CCTouch *touch, CCEvent *event);

	void onEnter();
	void onExit();
};

class CCScrewItem : public CCSprite, public CCTouchDelegate
{
public:
	CCScrewItem();
	~CCScrewItem();

	CCMenu *linemenu;
	CCSprite *lockItem;
	CC_SYNTHESIZE(CCScrewLayer *, _delegate, Delegate);

	CCRect getRect2();

	CREATE_FUNC(CCScrewItem);

protected:
	void onEnter();
	void onExit();
	bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	void ccTouchEnded(CCTouch *touch, CCEvent *event);

	bool containsTouchLocation(CCTouch *touch);
};
