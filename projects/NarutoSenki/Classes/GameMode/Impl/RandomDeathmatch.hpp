#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeRandomDeathmatch : public IGameModeHandler
{
public:
	void init()
	{
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

	void onCharacterInit(CharacterBase *c)
	{
		// NOTE: Not implement
		// CCLOG("[Character Init] %s, %s, %s", c->getCharacter(), c->getRole(), c->getGroup());
	}

	void onCharacterDead(CharacterBase *c)
	{
		CCLOG("[Character %s Dead] %s, %s", c->getCharacter()->getCString(), c->getRole()->getCString(), c->getGroup()->getCString());
	}

	void onCharacterReborn(CharacterBase *c)
	{
		CCLOG("[Character %s Reborn] %s, %s", c->getCharacter()->getCString(), c->getRole()->getCString(), c->getGroup()->getCString());
	}
};
