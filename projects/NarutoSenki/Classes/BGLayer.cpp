#include "BGLayer.h"

void BGLayer::initBg(int mapId)
{
	bgMap = CCSprite::create(GetMapBgPath(mapId));
	bgMap->setAnchorPoint(ccp(0, 0));
	bgMap->setPosition(ccp(0, 192));
	addChild(bgMap);
}
