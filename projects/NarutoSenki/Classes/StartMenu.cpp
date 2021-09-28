#include "StartMenu.h"
#include "MyUtils/Cocos2dxHelper.hpp"

GameMode s_GameMode = GameMode::Classic;
IGameModeHandler *s_ModeHandlers[GameMode::_Internal_Max_Length] = {
	new Mode1v1(),
	new Mode3v3(),
	new Mode4v4(),
	new ModeHardCore(),
	new ModeBoss(),
	new ModeClone(false),
	new ModeDeathmatch(),
	new ModeRandomDeathmatch(),
};
int Cheats = 0;
bool enableCustomSelect = false;

/*----------------------
init MenuButton ;
----------------------*/
MenuButton::MenuButton()
{
	_isTop = false;
	_isBottom = false;
}

MenuButton::~MenuButton()
{
}

bool MenuButton::init(const char *szImage)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCSprite::init());
		initWithSpriteFrameName(szImage);
		setAnchorPoint(ccp(0.5, 0));

		bRet = true;
	} while (0);

	return bRet;
}

void MenuButton::onEnter()
{
	CCSprite::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10, true);

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	// JniMethodInfo minfo;

	// bool isHave = JniHelper::getStaticMethodInfo(minfo, "net/zakume/game/NarutoSenki", "showBanner", "()V");
	// if (isHave)
	// {
	// 	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	// }

#endif
}

void MenuButton::onExit()
{
	CCSprite::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

CCRect MenuButton::getRect()
{
	CCSize size = getContentSize();
	return CCRect(0, 0, size.width, size.height);
}

bool MenuButton::containsTouchLocation(CCTouch *touch)
{
	return getRect().containsPoint(convertTouchToNodeSpace(touch));
}

void MenuButton::setBtnType(btnType type)
{
	_btnType = type;
}

btnType MenuButton::getBtnType()
{
	return _btnType;
}

bool MenuButton::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	// touch area
	if (!containsTouchLocation(touch))
		return false;

	//click();

	prePosY = 0;

	return true;
}

void MenuButton::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
	// touch area
	if (prePosY == 0)
	{
		prePosY = touch->getLocation().y;
	}
	else
	{
		if (getBtnType() != HardCore)
		{
			if (abs(touch->getLocation().y - prePosY) > 16)
			{
				if (touch->getLocation().y < prePosY)
				{
					_startMenu->isClockwise = true;
				}
				else
				{
					_startMenu->isClockwise = false;
				}
				_startMenu->isDrag = true;
			}
		}
	}
}

void MenuButton::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
	if (_isTop && !_startMenu->isDrag)
	{
		switch (_btnType)
		{
		case Training:
			SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");
			_startMenu->onTrainingCallBack();
			break;
		case Credits:
			SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");
			_startMenu->onCreditsCallBack();
			break;
		case Exit:
			SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");
			_startMenu->onExitCallBack();
			break;
		case Custom:
			SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");
			_startMenu->enterCustomMode();
			break;
		case HardCore:
			SimpleAudioEngine::sharedEngine()->playEffect(SELECT_SOUND);
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("menu05_text.png");
			_startMenu->menuText->setDisplayFrame(frame);
			_startMenu->onHardLayerCallBack();
			break;
		}
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->playEffect(SELECT_SOUND);
		prePosY = 0;
		_startMenu->scrollMenu(getPositionY());
		_startMenu->isDrag = false;
	}
}

void MenuButton::playSound()
{
	SimpleAudioEngine::sharedEngine()->stopAllEffects();

	switch (_btnType)
	{
	case Training:
		SimpleAudioEngine::sharedEngine()->playEffect(TRAINING_SOUND);
		break;
	case Custom:
		SimpleAudioEngine::sharedEngine()->playEffect(NETWORK_SOUND);
		break;
	case Credits:
		SimpleAudioEngine::sharedEngine()->playEffect(CREDITS_SOUND);
		break;
	case Exit:
		SimpleAudioEngine::sharedEngine()->playEffect(EXIT_SOUND);
		break;
	}
}

MenuButton *MenuButton::create(const char *szImage)
{
	MenuButton *mb = new MenuButton();
	if (mb && mb->init(szImage))
	{
		mb->autorelease();
		return mb;
	}
	else
	{
		delete mb;
		return nullptr;
	}
}

/*----------------------
init StartMenu layer;
----------------------*/

StartMenu::StartMenu()
{
	_menu_array = nullptr;
	isClockwise = false;
	isDrag = false;
	hardCoreLayer = nullptr;

	notice_layer = nullptr;

	noticeLabel = nullptr;

	login_btn = nullptr;
}

StartMenu::~StartMenu()
{
}

bool StartMenu::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		addSprites("Menu.plist");
		addSprites("Result.plist");
		addSprites("NamePlate.plist");

		//CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		//CCSprite* bgSprite = CCSprite::create("red_bg.png");
		////pSprite->setPosition(ccp(winSize.width/2 + origin.x, winSize.height/2 + origin.y));
		// FULL_SCREEN_SPRITE(bgSprite);
		//bgSprite->setAnchorPoint(ccp(0,0));
		//bgSprite->setPosition(ccp(0,0));
		//addChild(bgSprite, -5);

		//produce groud
		CCSprite *gold_left = CCSprite::createWithSpriteFrameName("gold_left.png");
		gold_left->setAnchorPoint(ccp(0, 0));
		gold_left->setPosition(ccp(0, 20));
		addChild(gold_left, 1);

		CCSprite *gold_right = CCSprite::createWithSpriteFrameName("gold_right.png");
		gold_right->setAnchorPoint(ccp(0, 1));
		gold_right->setPosition(ccp(winSize.width - gold_right->getContentSize().width - 20, winSize.height - 20));
		addChild(gold_right, 1);

		//produce the cloud
		CCSprite *cloud_left = CCSprite::createWithSpriteFrameName("cloud.png");
		cloud_left->setPosition(ccp(0, 15));
		cloud_left->setFlipX(true);
		cloud_left->setFlipY(true);
		cloud_left->setAnchorPoint(ccp(0, 0));
		addChild(cloud_left, 1);

		CCActionInterval *cmv1 = CCMoveBy::create(1, ccp(-15, 0));
		CCAction *cseq1 = CCRepeatForever::create(CCSequence::create(cmv1, cmv1->reverse(), nullptr));
		cloud_left->runAction(cseq1);

		CCSprite *cloud_right = CCSprite::createWithSpriteFrameName("cloud.png");
		cloud_right->setPosition(ccp(winSize.width - cloud_right->getContentSize().width,
									 winSize.height - (cloud_right->getContentSize().height + 15)));
		cloud_right->setAnchorPoint(ccp(0, 0));
		addChild(cloud_right, 1);

		CCActionInterval *cmv2 = CCMoveBy::create(1, ccp(15, 0));
		CCAction *cseq2 = CCRepeatForever::create(CCSequence::create(cmv2, cmv2->reverse(), nullptr));
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

		CCSprite *startmenu_title = CCSprite::createWithSpriteFrameName("startmenu_title.png");
		startmenu_title->setAnchorPoint(ccp(0, 0));
		startmenu_title->setPosition(ccp(2, winSize.height - startmenu_title->getContentSize().height - 2));
		addChild(startmenu_title, 3);

		//produce the menu button

		setMenus(CCArray::createWithCapacity(3));

		MenuButton *network_btn = MenuButton::create("menu01.png");
		network_btn->setDelegate(this);
		network_btn->setBtnType(Custom);
		network_btn->setScale(0.5f);
		network_btn->setPositionY(_pos03);
		_menu_array->addObject(network_btn);

		MenuButton *credits_btn = MenuButton::create("menu04.png");
		credits_btn->setDelegate(this);
		credits_btn->setBtnType(Credits);
		credits_btn->setScale(0.5f);
		credits_btn->setVisible(false);
		credits_btn->_isBottom = true;
		credits_btn->setPositionY(_pos02);
		_menu_array->addObject(credits_btn);

		MenuButton *training_btn = MenuButton::create("menu02.png");
		training_btn->setDelegate(this);
		training_btn->setBtnType(Training);
		training_btn->_isTop = true;
		training_btn->setPositionY(_pos02);
		_menu_array->addObject(training_btn);

		MenuButton *exit_btn = MenuButton::create("menu03.png");
		exit_btn->setDelegate(this);
		exit_btn->setBtnType(Exit);
		exit_btn->setScale(0.5f);
		exit_btn->setPositionY(_pos01);
		_menu_array->addObject(exit_btn);

		menuText = CCSprite::createWithSpriteFrameName("menu02_text.png");
		menuText->setAnchorPoint(ccp(0, 0));
		menuText->setPosition(ccp(10, 2));
		addChild(menuText, 5);

		CCObject *pObject = nullptr;
		CCARRAY_FOREACH(_menu_array, pObject)
		{
			MenuButton *menu = (MenuButton *)pObject;
			menu->setPositionX(105);
			addChild(menu, 2);
		}
		CCLabelBMFont *versionLabel = CCLabelBMFont::create(VERSION_CODE, "Fonts/1.fnt");
		versionLabel->setScale(0.3f);
		versionLabel->setPosition(winSize.width - 25, 10);
		addChild(versionLabel, 5);

		CCSprite *avator = CCSprite::createWithSpriteFrameName("avator1.png");
		avator->setAnchorPoint(ccp(0, 0));
		avator->setOpacity(0);
		avator->setPosition(ccp(winSize.width - avator->getContentSize().width, 19));
		addChild(avator, 1);

		CCArray *tempArray = CCArray::create();

		int i = 1;

		CCArray *list = CCArray::create();
		while (i < 5)
		{
			CCString *path = CCString::createWithFormat("avator%d.png", i);
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path->getCString());
			tempArray->addObject(frame);
			CCAnimation *tempAnimation = CCAnimation::createWithSpriteFrames(tempArray, 0.1f);
			CCAction *tempAction = CCAnimate::create(tempAnimation);
			list->addObject(tempAction);
			CCActionInterval *fadeIn = CCFadeIn::create(0.8f);
			CCDelayTime *delay = CCDelayTime::create(1.0f);
			CCActionInterval *fadeOut = CCFadeOut::create(0.5f);
			list->addObject(fadeIn);
			list->addObject(delay);
			list->addObject(fadeOut);
			i += 1;
		}

		avator->runAction(CCRepeatForever::create(CCSequence::create(list)));
		CCMenuItem *news_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("news_btn.png"), nullptr, nullptr, this, menu_selector(StartMenu::onNewsBtn));
		CCMenu *menu = CCMenu::create(news_btn, nullptr);
		news_btn->setAnchorPoint(ccp(0, 0.5f));
		menu->setPosition(15, winSize.height - 50);
		addChild(menu, 5);

		setNotice();

		login_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("login_btn.png"), nullptr, nullptr, this, menu_selector(StartMenu::onLoginBtn));
		CCMenu *menu2 = CCMenu::create(login_btn, nullptr);
		login_btn->setAnchorPoint(ccp(1, 0.5f));
		menu2->setPosition(winSize.width - 15, winSize.height - 50);
		addChild(menu2, 5);

		if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		{
			setKeypadEnabled(true);
		}

		scheduleUpdate();

		bRet = true;

	} while (0);

	return bRet;
}

void StartMenu::onEnter()
{
	CCLayer::onEnter();
	// SimpleAudioEngine::sharedEngine()->end();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);

	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isBGM"))
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MENU_MUSIC, true);
	}
}

void StartMenu::onExit()
{
	CCLayer::onExit();
	SimpleAudioEngine::sharedEngine()->end();
}

void StartMenu::onLoginBtn(CCObject *sender)
{
	CCTips *tip = CCTips::create("ServerMainten");
	addChild(tip, 5000);
	return;
}

void StartMenu::update(float dt)
{
	if (!noticeLabel)
	{
		return;
	}

	float currentX = noticeLabel->getPositionX();
	//float contentX = getContentSize().width;
	float lableX = noticeLabel->getContentSize().width;

	if (noticeLabel->getPositionX() >= -lableX)
	{
		noticeLabel->setPositionX(noticeLabel->getPositionX() - 0.6f);
	}
	else
	{
		noticeLabel->setPositionX(190);
	}
}

void StartMenu::setNotice()
{
	if (!notice_layer)
	{
		notice_layer = CCLayer::create();
		CCSprite *notice_bg = CCSprite::createWithSpriteFrameName("notice_bg.png");
		notice_bg->setAnchorPoint(ccp(0, 0));
		notice_bg->setPosition(ccp(15, 228));
		notice_layer->addChild(notice_bg);

		// FIXME: CCClippingNode not working on android
		CCClippingNode *clipper = CCClippingNode::create();
		CCNode *stencil = CCSprite::createWithSpriteFrameName("notice_mask.png");
		stencil->setAnchorPoint(ccp(0, 0));
		clipper->setStencil(stencil);

		CCDictionary *strings = CCDictionary::createWithContentsOfFile("Element/strings.xml");
		const char *reply = ((CCString *)strings->objectForKey("Notice"))->m_sString.c_str();

		noticeLabel = CCLabelTTF::create(reply, FONT_TYPE, 12);
		noticeLabel->setAnchorPoint(ccp(0, 0));
		clipper->addChild(noticeLabel);
		noticeLabel->retain();
		clipper->setPosition(ccp(35, 228));

		notice_layer->addChild(clipper);

		addChild(notice_layer);
	}
}

void StartMenu::onNewsBtn(CCObject *sender)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	// JniMethodInfo minfo;

	// bool isHave = JniHelper::getStaticMethodInfo(minfo, "net/zakume/game/NarutoSenki", "getInstance", "()Lnet/zakume/game/NarutoSenki;");
	// jobject jobj;
	// if (isHave)
	// {
	// 	jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

	// 	isHave = JniHelper::getMethodInfo(minfo, "net/zakume/game/NarutoSenki", "openWebview", "()V");
	// 	if (isHave)
	// 	{
	// 		minfo.env->CallVoidMethod(jobj, minfo.methodID);
	// 	}
	// }

#endif
}

void StartMenu::onHardCoreOn(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");
	if (hardCoreLayer)
	{
		hardCoreLayer->removeAllChildren();
		hardCoreLayer->removeFromParent();
		hardCoreLayer = nullptr;
	}
}

void StartMenu::onHardCoreOff(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/cancel.ogg");
	if (hardCoreLayer)
	{
		hardCoreLayer->removeAllChildren();
		hardCoreLayer->removeFromParent();
		hardCoreLayer = nullptr;
	}
}

void StartMenu::onHardLayerCallBack()
{
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isHardCore") == false)
	{
		if (!hardCoreLayer)
		{
			hardCoreLayer = CCLayer::create();

			CCSprite *confirm_bg = CCSprite::createWithSpriteFrameName("confirm_bg.png");
			confirm_bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));

			CCSprite *hardcore_title = CCSprite::createWithSpriteFrameName("hardcore_title.png");
			hardcore_title->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 38));

			CCSprite *hardcore_text = CCSprite::createWithSpriteFrameName("hardcore_text.png");
			hardcore_text->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 8));

			CCMenuItem *yes_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("yes_btn1.png"), CCSprite::createWithSpriteFrameName("yes_btn2.png"), this, menu_selector(StartMenu::onHardCoreOn));
			CCMenuItem *no_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("no_btn1.png"), CCSprite::createWithSpriteFrameName("no_btn2.png"), this, menu_selector(StartMenu::onHardCoreOff));

			CCMenu *confirm_menu = CCMenu::create(yes_btn, no_btn, nullptr);
			confirm_menu->alignItemsHorizontallyWithPadding(24);
			confirm_menu->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 30));

			hardCoreLayer->addChild(confirm_bg, 600);
			hardCoreLayer->addChild(confirm_menu, 650);
			hardCoreLayer->addChild(hardcore_title, 650);
			hardCoreLayer->addChild(hardcore_text, 650);
			addChild(hardCoreLayer, 700);
		}
	}
}

void StartMenu::enterCustomMode()
{
	// Enter game mode scene
	auto modeScene = CCScene::create();
	auto gameModeLayer = GameModeLayer::create();
	gameModeLayer->setHandler(_handler);
	modeScene->addChild(gameModeLayer);

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, modeScene));
}

void StartMenu::enterTrainingMode()
{
	s_GameMode = GameMode::Classic;

	enableCustomSelect = true;
	enterSelectLayer();
}

void StartMenu::enterSelectLayer()
{
	// call lua StartMenu:enterSelectPanel
	if (_handler != 0)
	{
		auto pStack = get_luastack;
		pStack->pushBoolean(enableCustomSelect);
		pStack->executeFunctionByHandler(_handler, 1);
	}
	else
	{
		addSprites("Select.plist");
		addSprites("UI.plist");
		addSprites("Report.plist");
		addSprites("Ougis.plist");
		addSprites("Ougis2.plist");
		addSprites("Map.plist");
		addSprites("Gears.plist");

		auto selectScene = CCScene::create();
		CCNode *selectLayer = SelectLayer::create();
		selectScene->addChild(selectLayer);

		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, selectScene));
		CCLOG("StartMenu lua handler can not be null");
	}
}

void StartMenu::onTrainingCallBack()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);

	enterSelectLayer();
}

void StartMenu::onCreditsCallBack()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCScene *creditsScene = CCScene::create();
	CreditsLayer *creditsLayer = CreditsLayer::create();
	creditsScene->addChild(creditsLayer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, creditsScene));
}

void StartMenu::scrollMenu(int posY)
{
	CCObject *pObject = nullptr;
	if (posY > _pos02 || (isDrag && isClockwise))
	{
		CCARRAY_FOREACH(_menu_array, pObject)
		{
			MenuButton *menu = (MenuButton *)pObject;
			if (menu->getPositionY() == _pos01)
			{
				CCActionInterval *spn = CCMoveTo::create(0.5, ccp(105, _pos02));
				reorderChild(menu, 1);
				menu->_isBottom = true;
				CCFadeOut *fo = CCFadeOut::create(0.3f);
				CCSpawn *seq = CCSpawn::createWithTwoActions(spn, fo);
				menu->runAction(seq);
			}
			else if (menu->getPositionY() == _pos03)
			{
				CCAction *spn = CCSpawn::create(
					CCMoveTo::create(0.5, ccp(105, _pos02)),
					CCScaleTo::create(0.5, 1),
					nullptr);
				reorderChild(menu, 3);
				menu->_isTop = true;

				CCFiniteTimeAction *call = CCCallFunc::create(menu, callfunc_selector(MenuButton::playSound));
				CCArray *seqArray = CCArray::create();
				seqArray->addObject(spn);
				seqArray->addObject(call);
				CCActionInterval *seq = CCSequence::create(seqArray);
				menu->runAction(seq);
			}
			else if (menu->getPositionY() == _pos02 && menu->_isBottom)
			{
				CCActionInterval *spn = CCMoveTo::create(0.5, ccp(105, _pos03));
				reorderChild(menu, 1);
				menu->setVisible(true);
				CCFadeIn *fi = CCFadeIn::create(0.3f);
				CCSpawn *seq = CCSpawn::createWithTwoActions(spn, fi);
				menu->_isBottom = false;
				menu->runAction(seq);
			}
			else if (menu->getPositionY() == _pos02 && !menu->_isBottom)
			{
				CCAction *spn = CCSpawn::create(
					CCMoveTo::create(0.5, ccp(105, _pos01)),
					CCScaleTo::create(0.5, 0.5),
					nullptr);
				reorderChild(menu, 1);
				menu->_isTop = false;
				menu->runAction(spn);
			}
		}
	}
	else
	{
		CCARRAY_FOREACH(_menu_array, pObject)
		{
			MenuButton *menu = (MenuButton *)pObject;
			if (menu->getPositionY() == _pos01)
			{
				CCAction *spn = CCSpawn::create(
					CCMoveTo::create(0.5, ccp(105, _pos02)),
					CCScaleTo::create(0.5, 1),
					nullptr);
				reorderChild(menu, 3);
				menu->_isTop = true;

				CCFiniteTimeAction *call = CCCallFunc::create(menu, callfunc_selector(MenuButton::playSound));
				CCArray *seqArray = CCArray::create();
				seqArray->addObject(spn);
				seqArray->addObject(call);
				CCActionInterval *seq = CCSequence::create(seqArray);
				menu->runAction(seq);
			}
			else if (menu->getPositionY() == _pos03)
			{
				CCActionInterval *spn = CCMoveTo::create(0.5, ccp(105, _pos02));
				reorderChild(menu, 1);
				menu->_isBottom = true;
				CCFadeOut *fo = CCFadeOut::create(0.3f);
				CCSpawn *seq = CCSpawn::createWithTwoActions(spn, fo);
				menu->runAction(seq);
			}
			else if (menu->getPositionY() == _pos02 && menu->_isBottom)
			{
				CCActionInterval *spn = CCMoveTo::create(0.5, ccp(105, _pos01));
				reorderChild(menu, 2);
				menu->setVisible(true);
				CCFadeIn *fi = CCFadeIn::create(0.3f);
				CCSpawn *seq = CCSpawn::createWithTwoActions(spn, fi);
				menu->_isBottom = false;
				menu->runAction(seq);
			}

			else if (menu->getPositionY() == _pos02 && !menu->_isBottom)
			{
				CCAction *spn = CCSpawn::create(
					CCMoveTo::create(0.5, ccp(105, _pos03)),
					CCScaleTo::create(0.5, 0.5),
					nullptr);
				reorderChild(menu, 2);
				menu->_isTop = false;
				menu->runAction(spn);
			}
		}
	}
	std::string src = "";
	CCARRAY_FOREACH(_menu_array, pObject)
	{
		MenuButton *menu = (MenuButton *)pObject;

		if (menu->_isTop)
		{
			switch (menu->getBtnType())
			{
			case Training:
				src = "menu02_text.png";
				break;
			case Custom:
				src = "menu01_text.png";
				break;
			case Credits:
				src = "menu04_text.png";
				break;
			case Exit:
				src = "menu03_text.png";
				break;
			}
		}
	}

	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(src.c_str());
	menuText->setDisplayFrame(frame);
}

void StartMenu::keyBackClicked()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	// JniMethodInfo minfo;
	// bool isHave = JniHelper::getStaticMethodInfo(minfo, "net/zakume/game/DialogUtils", "showTipDialog", "(Ljava/lang/String;Ljava/lang/String;)V");

	// if (isHave)
	// {
	// 	jstring jTitle = minfo.env->NewStringUTF("Exit Game");
	// 	jstring jMsg = minfo.env->NewStringUTF("Do you really want to exit?");
	// 	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jTitle, jMsg);
	// 	minfo.env->DeleteLocalRef(jTitle);
	// 	minfo.env->DeleteLocalRef(jMsg);
	// }
#else
	CCDirector::sharedDirector()->end();
	exit(0);
#endif
}

void StartMenu::setCheats(int cheats)
{
	Cheats = cheats;
}

void StartMenu::onExitCallBack()
{
	keyBackClicked();
}
