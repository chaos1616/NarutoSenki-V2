#pragma once
#include "GameLayer.h"

// TODO: Create a states panel in battle
class StatsLayer : public Layer
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

	Sprite *bg;
};
