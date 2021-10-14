#pragma once
#include "GameLayer.h"

// TODO: Create a states panel in battle
class StatsLayer : public CCLayer
{
public:
	void update()
	{
	}

	CREATE_FUNC(StatsLayer);

private:
	void init()
	{
	}

	CCSprite *bg;
};
