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

		addHero(playerHero, kRolePlayer, playerGroup);
		if (Cheats >= MaxCheats)
		{
			addHeros(3, playerHero, kRoleCom, playerGroup);
			addHeros(4, enemyHero, kRoleCom, enemyGroup);
		}
		else
		{
			addHeros(kGenerateCount - 1, playerHero, kRoleCom, playerGroup);
			addHeros(kGenerateCount, enemyHero, kRoleCom, enemyGroup);
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
