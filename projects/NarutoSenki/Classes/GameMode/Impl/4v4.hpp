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
		resetCheats();
	}

	void onCharacterInit(CharacterBase *c)
	{
	}

	void onCharacterDead(CharacterBase *c)
	{
	}

	void onCharacterReborn(CharacterBase *c)
	{
	}
};
