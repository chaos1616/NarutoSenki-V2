#pragma once
#include "GameMode/IGameModeHandler.hpp"

class Mode1v1 : public IGameModeHandler
{
private:
	bool isAddCallback;

public:
	void init()
	{
		CCLOG("Enter 1 VS 1 mode.");

		isAddCallback = false;

		gd.isHardCore = true;
	}

	void onInitHeros()
	{
		initHeros(1, 1);
	}

	void onGameStart()
	{
	}

	void onGameOver()
	{
	}

	void onCharacterInit(CharacterBase *c)
	{
		if (!isAddCallback && !getGameLayer()->isHUDInit())
		{
			// NOTE: Following code won't get correct value
			// Because this function `onCharacterInit` is not in current stack
			// So this value always nullptr or wrong value
			//
			// getGameLayer()->onHUDInitialized(
			// 	[&c]()
			// 	{
			// 		c->setEXP(2500);
			// 		for (int i = 1; i < 6; i++)
			// 			c->changeHPbar();
			// 		c->increaseAllCkrs(50000);
			// 	});
			isAddCallback = true;
			getGameLayer()->onHUDInitialized(
				[&]()
				{
					CCObject *pObject;
					CCARRAY_FOREACH(getGameLayer()->_CharacterArray, pObject)
					{
						auto c = (Hero *)pObject;
						c->setCoinValue(3000);
						c->setEXP(2500);
						for (int i = 1; i < 6; i++)
							c->changeHPbar();
						c->setHP(c->getMaxHP());
						c->updateHpBar();
						c->increaseAllCkrs(25000);
						c->setRebornTime(10);
						getGameLayer()->getHudLayer()->setEXPLose();

						if (c->isPlayer())
						{
							if (!c->isEnableSkill04())
								getGameLayer()->getHudLayer()->skill4Button->setLock();
							if (!c->isEnableSkill05())
								getGameLayer()->getHudLayer()->skill5Button->setLock();

							getGameLayer()->setCoin("2950"); // Default hero has 50 coins
						}
					}
				});
		}
	}

	void onCharacterDead(CharacterBase *c)
	{
	}

	void onCharacterReborn(CharacterBase *c)
	{
	}
};
