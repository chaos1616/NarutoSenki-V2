#pragma once
#include "GameLayer.h"

class BGLayer : public CCLayer
{
public:
	CCSprite *bgMap;

	void initBg(int mapId);

	CREATE_FUNC(BGLayer);
};
