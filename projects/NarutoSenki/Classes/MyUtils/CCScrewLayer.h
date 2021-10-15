#pragma once
#include "Defines.h"

class CCScrewLayer : public CCLayer
{
public:
	CCScrewLayer();
	~CCScrewLayer();

	float prePosY;
	float minY;
	int totalRow;
	int line_height;
	// PROP(vector<CCScrewItem *>, itemArray, ItemArray);

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

	CREATE_FUNC(CCScrewItem);

protected:
	void onEnter();
	void onExit();
	bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	void ccTouchEnded(CCTouch *touch, CCEvent *event);
	CCRect getRect2();

	inline bool containsTouchLocation(CCTouch *touch);
};
