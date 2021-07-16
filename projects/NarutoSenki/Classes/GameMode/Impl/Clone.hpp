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
	}

	void onInitHeros()
	{
		const char *playerGroup;
		const char *enemyGroup;
		getRandomGroups(playerGroup, enemyGroup);

		auto playerHero = selectLayer->_playerSelect ? selectLayer->_playerSelect : getRandomHero();
		auto enemyHero = getRandomHeroExcept(playerHero);

		addHero(playerHero, ROLE_PLAYER, playerGroup);
		addHeros(kGenerateCount - 1, playerHero, ROLE_COM, playerGroup);
		addHeros(kGenerateCount, enemyHero, ROLE_COM, enemyGroup);
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
