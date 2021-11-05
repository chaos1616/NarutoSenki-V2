#pragma once
#include "Defines.h"

class CCScrewLayer : public CCLayer
{
public:
	float prePosY;
	float minY = 154;
	int totalRow = 100;
	int line_height = 26;
	// PROP_Vector(vector<CCScrewItem *>, itemArray, ItemArray);

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
	CCMenu *linemenu;
	CCSprite *lockItem;
	CC_SYNTHESIZE(CCScrewLayer *, _delegate, Delegate);

	CREATE_FUNC(CCScrewItem);

protected:
	void onEnter();
	void onExit();
	bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	void ccTouchEnded(CCTouch *touch, CCEvent *event);
	CCRect getRect2();

	inline bool containsTouchLocation(CCTouch *touch);
};
