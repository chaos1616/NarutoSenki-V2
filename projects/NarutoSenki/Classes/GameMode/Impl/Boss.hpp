#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeBoss : public IGameModeHandler
{
public:
	void init()
	{
		CCLOG("Enter Boss mode.");

		gd.isHardCore = false;
	}

	void onInitHeros()
	{
		initHeros(3, 1);
	}

	void onGameStart()
	{
	}

	void onGameOver()
	{
	}

	void onCharacterInit(Unit *c)
	{
	}

	void onCharacterDead(Unit *c)
	{
	}

	void onCharacterReborn(Unit *c)
	{
	}
};
