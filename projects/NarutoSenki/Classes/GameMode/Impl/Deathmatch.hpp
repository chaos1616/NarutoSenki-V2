#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeDeathmatch : public IGameModeHandler
{
public:
	void init()
	{
	}

	CCArray *onInitHeros()
	{
		return initHeros(3, 3);
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
		CCLOG("[Character Dead] %s %s %s", c->getCharacter(), c->getRole(), c->getGroup());
	}

	void onCharacterReborn(CharacterBase *c)
	{
		CCLOG("[Character Reborn] %s, %s, %s", c->getCharacter(), c->getRole(), c->getGroup());
	}
};
