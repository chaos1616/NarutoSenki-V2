#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeHardCore : public IGameModeHandler
{
public:
	void init()
	{
		CCLOG("Enter HardCore mode.");

		Cheats = 11;
		isHardCoreGame = true;
	}

	CCArray *onInitHeros()
	{
		return initHeros(4, 4);
	}

	void onGameStart()
	{
	}

	void onGameOver()
	{
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
