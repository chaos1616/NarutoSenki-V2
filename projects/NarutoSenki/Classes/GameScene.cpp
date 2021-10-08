#include "GameScene.h"

// on "init" you need to initialize your instance
bool GameScene::init()
{
	RETURN_FALSE_IF(!CCScene::init());

	lua_call_init_func;

	return true;
}
