#include "PauseLayer.h"
#include "GameLayer.h"

bool PauseLayer::init(RenderTexture *snapshoot)
{
	if (!Layer::init())
		return false;

	SimpleAudioEngine::sharedEngine()->stopAllEffects();
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

	Texture2D *bgTexture = snapshoot->getSprite()->getTexture();
	Sprite *bg = Sprite::createWithTexture(bgTexture);
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setFlipY(true);
	addChild(bg, 0);

	Layer *blend = LayerColor::create(ccc4(0, 0, 0, 150), winSize.width, winSize.height);
	addChild(blend, 1);

	// produce the menu_bar
	Sprite *menu_bar_b = Sprite::create("menu_bar2.png");
	menu_bar_b->setAnchorPoint(Vec2(0, 0));
	FULL_SCREEN_SPRITE(menu_bar_b);
	addChild(menu_bar_b, 2);

	Sprite *menu_bar_t = Sprite::create("menu_bar3.png");
	menu_bar_t->setAnchorPoint(Vec2(0, 0));
	menu_bar_t->setPosition(Vec2(0, winSize.height - menu_bar_t->getContentSize().height));
	FULL_SCREEN_SPRITE(menu_bar_t);
	addChild(menu_bar_t, 2);

	Sprite *pause_title = newSprite("pause_title.png");
	pause_title->setAnchorPoint(Vec2(0, 0));
	pause_title->setPosition(Vec2(2, winSize.height - pause_title->getContentSize().height - 2));
	addChild(pause_title, 3);

	MenuItem *resume_btn = MenuItemSprite::create(newSprite("resume.png"), nullptr, nullptr, this, menu_selector(PauseLayer::onResume));
	MenuItem *btm_btn = MenuItemSprite::create(newSprite("btm.png"), nullptr, nullptr, this, menu_selector(PauseLayer::onBackToMenu));

	pauseMenu = Menu::create(resume_btn, btm_btn, nullptr);
	pauseMenu->alignItemsVerticallyWithPadding(26);
	pauseMenu->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 30));
	addChild(pauseMenu, 3);

	Sprite *surrender_text = newSprite("surrender_tips.png");
	surrender_text->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 23));
	addChild(surrender_text, 4);

	bgm_btn = MenuItemSprite::create(newSprite("bgm_on.png"), newSprite("bgm_off.png"), nullptr, this, menu_selector(PauseLayer::onBGM));
	voice_btn = MenuItemSprite::create(newSprite("voice_on.png"), newSprite("voice_off.png"), nullptr, this, menu_selector(PauseLayer::onVoice));
	soundMenu = Menu::create(bgm_btn, voice_btn, nullptr);
	soundMenu->alignItemsHorizontallyWithPadding(25);
	soundMenu->setPosition(Vec2(pauseMenu->getPositionX(), pauseMenu->getPositionY() - 80));
	addChild(soundMenu, 4);

	pre_btn = MenuItemSprite::create(newSprite("preload_on.png"), newSprite("preload_off.png"), nullptr, this, menu_selector(PauseLayer::onPreload));
	preMenu = Menu::create(pre_btn, nullptr);
	preMenu->alignItemsHorizontallyWithPadding(25);
	preMenu->setPosition(Vec2(pauseMenu->getPositionX(), preMenu->getPositionY() - 84));
	addChild(preMenu, 4);

	if (UserDefault::sharedUserDefault()->getBoolForKey("isBGM") == false)
	{
		bgm_btn->selected();
	}
	if (UserDefault::sharedUserDefault()->getBoolForKey("isVoice") == false)
	{
		voice_btn->selected();
	}

	if (UserDefault::sharedUserDefault()->getBoolForKey("isPreload") == false)
	{
		pre_btn->selected();
	}

	return true;
}

void PauseLayer::onBGM(Ref *sender)
{
	if (UserDefault::sharedUserDefault()->getBoolForKey("isBGM") == true)
	{
		UserDefault::sharedUserDefault()->setBoolForKey("isBGM", false);
		bgm_btn->selected();
	}
	else
	{
		UserDefault::sharedUserDefault()->setBoolForKey("isBGM", true);
		bgm_btn->unselected();
	}
}

void PauseLayer::onVoice(Ref *sender)
{
	if (UserDefault::sharedUserDefault()->getBoolForKey("isVoice") == true)
	{
		UserDefault::sharedUserDefault()->setBoolForKey("isVoice", false);
		voice_btn->selected();
	}
	else
	{
		UserDefault::sharedUserDefault()->setBoolForKey("isVoice", true);
		voice_btn->unselected();
	}
}

void PauseLayer::onPreload(Ref *sender)
{
	if (UserDefault::sharedUserDefault()->getBoolForKey("isPreload") == true)
	{
		UserDefault::sharedUserDefault()->setBoolForKey("isPreload", false);
		pre_btn->selected();
	}
	else
	{
		UserDefault::sharedUserDefault()->setBoolForKey("isPreload", true);
		pre_btn->unselected();
	}
}

void PauseLayer::onResume(Ref *sender)
{
	if (UserDefault::sharedUserDefault()->getBoolForKey("isBGM"))
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	if (UserDefault::sharedUserDefault()->getBoolForKey("isVoice"))
	{
		SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	}

	Director::sharedDirector()->popScene();
	getGameLayer()->_isPause = false;
}

void PauseLayer::onBackToMenu(Ref *sender)
{
	pauseMenu->setVisible(false);
	soundMenu->setVisible(false);
	SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/select.ogg");
	exitLayer = Layer::create();

	Sprite *exit_bg = newSprite("confirm_bg.png");
	exit_bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	Sprite *comfirm_title = newSprite("confirm_title.png");
	comfirm_title->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 38));

	Sprite *surrender_text = newSprite("surrender_text.png");
	surrender_text->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 8));

	MenuItem *yes_btn = MenuItemSprite::create(newSprite("yes_btn1.png"), newSprite("yes_btn2.png"), this, menu_selector(PauseLayer::onLeft));
	MenuItem *no_btn = MenuItemSprite::create(newSprite("no_btn1.png"), newSprite("no_btn2.png"), this, menu_selector(PauseLayer::onCancel));

	Menu *confirm_menu = Menu::create(yes_btn, no_btn, nullptr);
	confirm_menu->alignItemsHorizontallyWithPadding(24);
	confirm_menu->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 30));

	exitLayer->addChild(exit_bg, 1);
	exitLayer->addChild(confirm_menu, 2);
	exitLayer->addChild(comfirm_title, 2);
	exitLayer->addChild(surrender_text, 2);
	addChild(exitLayer, 500);
}

void PauseLayer::onLeft(Ref *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");
	getGameLayer()->_isSurrender = true;
	Director::sharedDirector()->popScene();

	getGameLayer()->_isPause = false;
}

void PauseLayer::onCancel(Ref *sender)
{
	pauseMenu->setVisible(true);
	soundMenu->setVisible(true);
	SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/cancel.ogg");
	exitLayer->removeFromParent();
}

PauseLayer *PauseLayer::create(RenderTexture *snapshoot)
{
	PauseLayer *pl = new PauseLayer();
	if (pl && pl->init(snapshoot))
	{
		pl->autorelease();
		return pl;
	}
	else
	{
		delete pl;
		return nullptr;
	}
}
