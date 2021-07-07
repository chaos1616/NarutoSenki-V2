#include "BGLayer.h"

BGLayer::BGLayer()
{
	texMap = nullptr;
}

BGLayer::~BGLayer()
{
}

bool BGLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		bRet = true;

	} while (0);

	return bRet;
}

void BGLayer::initBg()
{
	bgMap = CCSprite::create(GetMapBgPath(_delegate->mapId));
	bgMap->setAnchorPoint(ccp(0, 0));
	bgMap->setPosition(ccp(0, 192));
	addChild(bgMap);
}

void BGLayer::setDelegate(GameLayer *layer)
{
	_delegate = layer;
	initBg();
}
