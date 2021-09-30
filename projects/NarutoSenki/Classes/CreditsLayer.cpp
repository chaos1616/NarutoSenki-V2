#include "CreditsLayer.h"
#include "StartMenu.h"

CreditsLayer::CreditsLayer()
{
}

CreditsLayer::~CreditsLayer()
{
}

bool CreditsLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSprite *bgSprite = CCSprite::create("blue_bg.png");
		FULL_SCREEN_SPRITE(bgSprite);
		bgSprite->setAnchorPoint(ccp(0, 0));
		bgSprite->setPosition(ccp(0, 0));
		addChild(bgSprite, -5);

		//produce the cloud
		CCSprite *cloud_left = CCSprite::createWithSpriteFrameName("cloud.png");
		cloud_left->setPosition(ccp(0, 15));
		cloud_left->setFlipX(true);
		cloud_left->setFlipY(true);
		cloud_left->setAnchorPoint(ccp(0, 0));
		addChild(cloud_left, 1);

		auto cmv1 = CCMoveBy::create(1, ccp(-15, 0));
		auto cseq1 = CCRepeatForever::create(CCSequence::create(cmv1, cmv1->reverse(), nullptr));
		cloud_left->runAction(cseq1);

		CCSprite *cloud_right = CCSprite::createWithSpriteFrameName("cloud.png");
		cloud_right->setPosition(ccp(winSize.width - cloud_right->getContentSize().width,
									 winSize.height - (cloud_right->getContentSize().height + 15)));
		cloud_right->setAnchorPoint(ccp(0, 0));
		addChild(cloud_right, 1);

		auto cmv2 = CCMoveBy::create(1, ccp(15, 0));
		auto cseq2 = CCRepeatForever::create(CCSequence::create(cmv2, cmv2->reverse(), nullptr));
		cloud_right->runAction(cseq2);

		//produce the menu_bar
		CCSprite *menu_bar_b = CCSprite::create("menu_bar2.png");
		menu_bar_b->setAnchorPoint(ccp(0, 0));
		FULL_SCREEN_SPRITE(menu_bar_b);
		addChild(menu_bar_b, 2);

		CCSprite *menu_bar_t = CCSprite::create("menu_bar3.png");
		menu_bar_t->setAnchorPoint(ccp(0, 0));
		menu_bar_t->setPosition(ccp(0, winSize.height - menu_bar_t->getContentSize().height));
		FULL_SCREEN_SPRITE(menu_bar_t);
		addChild(menu_bar_t, 2);

		CCSprite *staff_title = CCSprite::createWithSpriteFrameName("staff_title.png");
		staff_title->setAnchorPoint(ccp(0, 0));
		staff_title->setPosition(ccp(2, winSize.height - staff_title->getContentSize().height - 2));
		addChild(staff_title, 3);

		CCSprite *credit01 = CCSprite::createWithSpriteFrameName("credits01.png");
		credit01->setPosition(ccp(winSize.width / 2 - 20, winSize.height / 2 + 80));
		addChild(credit01);

		CCSprite *credit02 = CCSprite::createWithSpriteFrameName("credits02.png");
		credit02->setPosition(ccp(winSize.width / 2 + 15, winSize.height / 2 - 60));
		addChild(credit02);
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isBGM"))
		{
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CREDITS_MUSIC, true);
		}

		setKeypadEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

void CreditsLayer::keyBackClicked()
{
	setKeypadEnabled(false);

	lua_call_func("CreditsLayer_BackToStartMenu")
}
