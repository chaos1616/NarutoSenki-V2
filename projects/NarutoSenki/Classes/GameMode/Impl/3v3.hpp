#pragma once
#include "GameMode/IGameModeHandler.hpp"

class Mode3v3 : public IGameModeHandler
{
public:
	void init()
	{
		CCLOG("Enter 3 VS 3 mode.");

		gd.isHardCore = true;
	}

	void onInitHeros()
	{
		initHeros(3, 3);
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
