#include "GameScene.h"

// on "init" you need to initialize your instance
bool GameScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCScene::init());

		lua_call_init_func;

		bRet = true;
	} while (0);

	return bRet;
}
