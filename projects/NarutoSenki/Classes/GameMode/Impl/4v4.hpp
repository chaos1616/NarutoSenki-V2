#pragma once
#include "GameMode/IGameModeHandler.hpp"

class Mode4v4 : public IGameModeHandler
{
public:
	void init()
	{
		CCLOG("Enter 4 VS 4 mode.");

		Cheats = 7;
		gd.isHardCore = true;
		gd.use4v4SpawnLayout = true;
	}

	void onInitHeros()
	{
		initHeros(4, 4);
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
