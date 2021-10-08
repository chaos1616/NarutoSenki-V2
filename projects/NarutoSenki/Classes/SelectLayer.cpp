#include <time.h>
#include "StartMenu.h"
#include "MyUtils/Cocos2dxHelper.hpp"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "../../../cocos2dx/platform/android/jni/JniHelper.h"
#endif

SelectLayer::SelectLayer()
{
	_playerSelect = nullptr;
	_selectList = nullptr;
	_com1Select = nullptr;
	_com2Select = nullptr;
	_com3Select = nullptr;

	isStart = false;
}

SelectLayer::~SelectLayer()
{
}

void SelectLayer::onGameStart()
{
	if (isStart)
		return;
	else
		isStart = true;

	setKeypadEnabled(false);

	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");

	CCScene *loadScene = CCScene::create();
	LoadLayer *loadLayer = LoadLayer::create();

	auto gameModeHandler = getGameModeHandler();
	gameModeHandler->selectLayer = this;
	gameModeHandler->onInitHeros();
	loadLayer->tempHeros = gameModeHandler->getHerosArray();
	loadScene->addChild(loadLayer);

	loadLayer->preloadAudio();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, loadScene));
}

void SelectLayer::keyBackClicked()
{
	lua_call_func("backToStartMenu");
}

SelectLayer *SelectLayer::create()
{
	SelectLayer *sl = new SelectLayer();
	if (sl->init())
	{
		sl->autorelease();
		return sl;
	}
	else
	{
		delete sl;
		return nullptr;
	}
}
