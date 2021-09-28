#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeClone : public IGameModeHandler
{
private:
	const int kGenerateCount = 3;

	bool isOneForAllGroups;

public:
	ModeClone(bool isOneForAllGroups)
	{
		this->isOneForAllGroups = isOneForAllGroups;
	}

	void init()
	{
		CCLOG("Enter Clone mode.");

		gd.isHardCore = true;
	}

	void onInitHeros()
	{
		const char *playerGroup;
		const char *enemyGroup;
		getRandomGroups(playerGroup, enemyGroup);

		auto playerHero = getSelectOrRandomHero();
		auto enemyHero = getRandomHeroExcept(playerHero);

		addHero(playerHero, ROLE_PLAYER, playerGroup);
		if (Cheats > 6)
		{
			addHeros(3, playerHero, ROLE_COM, playerGroup);
			addHeros(4, enemyHero, ROLE_COM, enemyGroup);
		}
		else
		{
			addHeros(kGenerateCount - 1, playerHero, ROLE_COM, playerGroup);
			addHeros(kGenerateCount, enemyHero, ROLE_COM, enemyGroup);
		}
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
