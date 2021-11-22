#include "CreditsLayer.h"
#include "StartMenu.h"

bool CreditsLayer::init()
{
	RETURN_FALSE_IF(!Layer::init());

	auto bgSprite = Sprite::create("blue_bg.png");
	FULL_SCREEN_SPRITE(bgSprite);
	bgSprite->setAnchorPoint(Vec2(0, 0));
	bgSprite->setPosition(Vec2(0, 0));
	addChild(bgSprite, -5);

	// produce the cloud
	auto cloud_left = newSprite("cloud.png");
	cloud_left->setPosition(Vec2(0, 15));
	cloud_left->setFlippedX(true);
	cloud_left->setFlippedY(true);
	cloud_left->setAnchorPoint(Vec2(0, 0));
	addChild(cloud_left, 1);

	auto cmv1 = MoveBy::create(1, Vec2(-15, 0));
	auto cseq1 = RepeatForever::create(newSequence(cmv1, cmv1->reverse()));
	cloud_left->runAction(cseq1);

	auto cloud_right = newSprite("cloud.png");
	cloud_right->setPosition(Vec2(winSize.width - cloud_right->getContentSize().width,
								  winSize.height - (cloud_right->getContentSize().height + 15)));
	cloud_right->setAnchorPoint(Vec2(0, 0));
	addChild(cloud_right, 1);

	auto cmv2 = MoveBy::create(1, Vec2(15, 0));
	auto cseq2 = RepeatForever::create(newSequence(cmv2, cmv2->reverse()));
	cloud_right->runAction(cseq2);

	// produce the menu_bar
	auto menu_bar_b = Sprite::create("menu_bar2.png");
	menu_bar_b->setAnchorPoint(Vec2(0, 0));
	FULL_SCREEN_SPRITE(menu_bar_b);
	addChild(menu_bar_b, 2);

	auto menu_bar_t = Sprite::create("menu_bar3.png");
	menu_bar_t->setAnchorPoint(Vec2(0, 0));
	menu_bar_t->setPosition(Vec2(0, winSize.height - menu_bar_t->getContentSize().height));
	FULL_SCREEN_SPRITE(menu_bar_t);
	addChild(menu_bar_t, 2);

	auto staff_title = newSprite("staff_title.png");
	staff_title->setAnchorPoint(Vec2(0, 0));
	staff_title->setPosition(Vec2(2, winSize.height - staff_title->getContentSize().height - 2));
	addChild(staff_title, 3);

	auto credit01 = newSprite("credits01.png");
	credit01->setPosition(Vec2(winSize.width / 2 - 20, winSize.height / 2 + 80));
	addChild(credit01);

	auto credit02 = newSprite("credits02.png");
	credit02->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 50));
	addChild(credit02);

	if (UserDefault::sharedUserDefault()->getBoolForKey("isBGM"))
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CREDITS_MUSIC, true);

	return true;
}

void CreditsLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	setKeypadEnabled(true);
}

void CreditsLayer::keyBackClicked()
{
	setKeypadEnabled(false);

	lua_call_func("CreditsLayer_BackToStartMenu")
}
