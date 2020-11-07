#pragma once
#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class GameLayer;

class BGLayer : public CCLayer
{

public:
	BGLayer();
	~BGLayer();

	CCTexture2D *texMap;
	CCSprite *bgMap;

	GameLayer *_delegate;

	void setDelegate(GameLayer *layer);
	void initBg();
	virtual bool init();

	CREATE_FUNC(BGLayer);
};
