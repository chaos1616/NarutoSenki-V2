#include "GameScene.h"
using namespace CocosDenshion;

USING_NS_CC;

int adResult = 0;

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

void GameScene::onLogoClick(CCObject *sender)
{
	Cheats += 1;
	if (Cheats == 10)
	{
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
		logoMenu->removeFromParent();

		CCMenuItem *logo_btn = CCMenuItemSprite::create(CCSprite::create("logo2.png"), NULL, NULL, this, menu_selector(GameScene::onLogoClick));
		logo_btn->setAnchorPoint(ccp(0.5f, 0.5f));

		logoMenu = CCMenu::create(logo_btn, NULL);
		logoMenu->setPosition(ccp(winSize.width / 2, winSize.height - logo_btn->getContentSize().height / 2));
		introLayer->addChild(logoMenu, 3);
	}
	else if (Cheats > 10)
	{
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/chang_btn.ogg");
		lua_call_handler_auto;
	}
}
