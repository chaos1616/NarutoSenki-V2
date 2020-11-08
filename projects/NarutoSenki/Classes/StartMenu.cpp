#include "StartMenu.h"

int Cheats = 0;
int MemberID = 0;
int GroupID = 0;
std::string PWord = "";
std::string CValue = "999999";
bool isFirst = false;
bool isPlayed = true;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "../../../cocos2dx/platform/android/jni/JniHelper.h"

extern "C"
{
	void Java_re_naruto_game_NarutoSenki_onBannerInit(JNIEnv *env, jobject thiz, jint points)
	{
		adResult = points;
	}
}
#endif

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
		this->initWithSpriteFrameName(szImage);
		this->setAnchorPoint(ccp(0.5, 0));

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
	CCSize size = this->getContentSize();
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
	if (!this->containsTouchLocation(touch))
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
		if (this->getBtnType() != HardCore)
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
		case Network:
			SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");
			_startMenu->onHardCoreCallBack();
			break;
		case HardCore:
			SimpleAudioEngine::sharedEngine()->playEffect(SELECT_SOUND);
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("menu05_text.png");
			_startMenu->menuText->setDisplayFrame(frame);

			if (CCUserDefault::sharedUserDefault()->getBoolForKey("isHardCore") == true)
			{
				CCUserDefault::sharedUserDefault()->setBoolForKey("isHardCore", false);
				if (_startMenu->hardCore_btn)
				{
					CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("menu02_2.png");
					_startMenu->hardCore_btn->setDisplayFrame(frame);
				}
			}
			else
			{
				_startMenu->onHardLayerCallBack();
			}

			break;
		}
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->playEffect(SELECT_SOUND);
		prePosY = 0;
		_startMenu->scrollMenu(this->getPositionY());
		_startMenu->isDrag = false;
	}
};

void MenuButton::playSound()
{

	SimpleAudioEngine::sharedEngine()->stopAllEffects();

	switch (_btnType)
	{
	case Training:
		SimpleAudioEngine::sharedEngine()->playEffect(TRAINING_SOUND);
		// if(this->getBtnType()==Training){
		// _delegate->hardCore_btn->setVisible(true);
		// }
		break;
	case Network:
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
		return NULL;
	}
}

/*----------------------
init StartMenu layer;
----------------------*/

StartMenu::StartMenu()
{
	_menu_array = NULL;
	isClockwise = false;
	isDrag = false;
	hardCore_btn = NULL;
	hardCoreLayer = NULL;

	notice_layer = NULL;

	noticeLabel = NULL;

	login_btn = NULL;
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

		//CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		//CCSprite* bgSprite = CCSprite::create("red_bg.png");
		////pSprite->setPosition(ccp(winSize.width/2 + origin.x, winSize.height/2 + origin.y));
		// FULL_SCREEN_SPRITE(bgSprite);
		//bgSprite->setAnchorPoint(ccp(0,0));
		//bgSprite->setPosition(ccp(0,0));
		//this->addChild(bgSprite, -5);

		addSprites("Menu.plist");
		addSprites("Result.plist");
		addSprites("NamePlate.plist");
		//produce groud

		CCSprite *gold_left = CCSprite::createWithSpriteFrameName("gold_left.png");
		gold_left->setAnchorPoint(ccp(0, 0));
		gold_left->setPosition(ccp(0, 20));
		this->addChild(gold_left, 1);

		CCSprite *gold_right = CCSprite::createWithSpriteFrameName("gold_right.png");
		gold_right->setAnchorPoint(ccp(0, 1));
		gold_right->setPosition(ccp(winSize.width - gold_right->getContentSize().width - 20, winSize.height - 20));
		this->addChild(gold_right, 1);

		//produce the cloud
		CCSprite *cloud_left = CCSprite::createWithSpriteFrameName("cloud.png");
		cloud_left->setPosition(ccp(0, 15));
		cloud_left->setFlipX(true);
		cloud_left->setFlipY(true);
		cloud_left->setAnchorPoint(ccp(0, 0));
		this->addChild(cloud_left, 1);

		CCActionInterval *cmv1 = CCMoveBy::create(1, ccp(-15, 0));
		CCAction *cseq1 = CCRepeatForever::create(CCSequence::create(cmv1, cmv1->reverse(), NULL));
		cloud_left->runAction(cseq1);

		CCSprite *cloud_right = CCSprite::createWithSpriteFrameName("cloud.png");
		cloud_right->setPosition(ccp(winSize.width - cloud_right->getContentSize().width,
									 winSize.height - (cloud_right->getContentSize().height + 15)));
		cloud_right->setAnchorPoint(ccp(0, 0));
		this->addChild(cloud_right, 1);

		CCActionInterval *cmv2 = CCMoveBy::create(1, ccp(15, 0));
		CCAction *cseq2 = CCRepeatForever::create(CCSequence::create(cmv2, cmv2->reverse(), NULL));
		cloud_right->runAction(cseq2);

		//produce the menu_bar
		CCSprite *menu_bar_b = CCSprite::create("menu_bar2.png");
		menu_bar_b->setAnchorPoint(ccp(0, 0));
		FULL_SCREEN_SPRITE(menu_bar_b);
		this->addChild(menu_bar_b, 2);

		CCSprite *menu_bar_t = CCSprite::create("menu_bar3.png");
		menu_bar_t->setAnchorPoint(ccp(0, 0));
		menu_bar_t->setPosition(ccp(0, winSize.height - menu_bar_t->getContentSize().height));
		FULL_SCREEN_SPRITE(menu_bar_t);
		this->addChild(menu_bar_t, 2);

		CCSprite *startmenu_title = CCSprite::createWithSpriteFrameName("startmenu_title.png");
		startmenu_title->setAnchorPoint(ccp(0, 0));
		startmenu_title->setPosition(ccp(2, winSize.height - startmenu_title->getContentSize().height - 2));
		this->addChild(startmenu_title, 3);

		//produce the menu button

		this->setMenus(CCArray::createWithCapacity(3));

		MenuButton *network_btn = MenuButton::create("menu01.png");
		network_btn->setDelegate(this);
		network_btn->setBtnType(Network);
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

		/*if(!CCUserDefault::sharedUserDefault()->getBoolForKey("isHardCore")){
			CCUserDefault::sharedUserDefault()->setBoolForKey("isHardCore", false);
			CCUserDefault::sharedUserDefault()->flush();
		}
		

		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isHardCore")==true){
			hardCore_btn=MenuButton::create("menu02_1.png");
		}else{
			hardCore_btn=MenuButton::create("menu02_2.png");
		}

		hardCore_btn->setDelegate(this);
		hardCore_btn->setBtnType(HardCore);
		hardCore_btn->setPosition(ccp(146,_pos02-18));
		hardCore_btn->_isTop=true;
		this->addChild(hardCore_btn,10);*/

		MenuButton *exit_btn = MenuButton::create("menu03.png");
		exit_btn->setDelegate(this);
		exit_btn->setBtnType(Exit);
		exit_btn->setScale(0.5f);
		exit_btn->setPositionY(_pos01);
		_menu_array->addObject(exit_btn);

		menuText = CCSprite::createWithSpriteFrameName("menu02_text.png");
		menuText->setAnchorPoint(ccp(0, 0));
		menuText->setPosition(ccp(10, 2));
		this->addChild(menuText, 5);

		CCObject *pObject = NULL;
		CCARRAY_FOREACH(_menu_array, pObject)
		{
			MenuButton *menu = (MenuButton *)pObject;
			menu->setPositionX(105);
			this->addChild(menu, 2);
		};
		CCLabelBMFont *versionLabel = CCLabelBMFont::create(VERSION_CODE, "Fonts/1.fnt");
		versionLabel->setScale(0.3f);
		versionLabel->setPosition(winSize.width - 20, 10);
		this->addChild(versionLabel, 5);

		CCSprite *avator = CCSprite::createWithSpriteFrameName("avator1.png");
		avator->setAnchorPoint(ccp(0, 0));
		avator->setOpacity(0);
		avator->setPosition(ccp(winSize.width - avator->getContentSize().width, 19));
		this->addChild(avator, 1);

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
		CCMenuItem *news_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("news_btn.png"), NULL, NULL, this, menu_selector(StartMenu::onNewsBtn));
		CCMenu *menu = CCMenu::create(news_btn, NULL);
		news_btn->setAnchorPoint(ccp(0, 0.5f));
		menu->setPosition(15, winSize.height - 50);
		this->addChild(menu, 5);

		this->setNotice();

		login_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("login_btn.png"), NULL, NULL, this, menu_selector(StartMenu::onLoginBtn));
		CCMenu *menu2 = CCMenu::create(login_btn, NULL);
		login_btn->setAnchorPoint(ccp(1, 0.5f));
		menu2->setPosition(winSize.width - 15, winSize.height - 50);
		this->addChild(menu2, 5);

		if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		{
			this->setKeypadEnabled(true);
		}

		this->scheduleUpdate();

		bRet = true;

	} while (0);

	return bRet;
}

void StartMenu::onEnter()
{
	CCLayer::onEnter();
	SimpleAudioEngine::sharedEngine()->end();

	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isBGM") != false)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MENU_MUSIC, true);
	}

	if (isPlayed)
	{
		isPlayed = false;

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		// JniMethodInfo minfo;

		// bool isHave = JniHelper::getStaticMethodInfo(minfo, "net/zakume/game/NarutoSenki", "showSpotAd", "()V");
		// if (isHave)
		// {
		// 	minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
		// }

#endif
	}
}

void StartMenu::onExit()
{
	CCLayer::onExit();
}

void StartMenu::onLoginBtn(CCObject *sender)
{

	addSprites("Result.plist");
	addSprites("Record.plist");
	addSprites("Record2.plist");
	addSprites("UI.plist");
	addSprites("Report.plist");
	addSprites("Ougis.plist");
	addSprites("Ougis2.plist");
	addSprites("Map.plist");
	addSprites("Gears.plist");
	CCScene *pscene = CCScene::create();
	RakingLayer *rakingLayer = RakingLayer::create();
	// rakingLayer->setDelegate(this);
	pscene->addChild(rakingLayer);
	CCDirector::sharedDirector()->pushScene(pscene);

	CCTips *tip = CCTips::create("ServerMainten");
	this->addChild(tip, 5000);
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

		CCClippingNode *clipper = CCClippingNode::create();
		CCNode *stencil = CCSprite::createWithSpriteFrameName("notice_mask.png");
		stencil->setAnchorPoint(ccp(0, 0));
		clipper->setStencil(stencil);

		noticeLabel = CCLabelTTF::create("", FONT_TYPE, 12);
		noticeLabel->setAnchorPoint(ccp(0, 0));
		clipper->addChild(noticeLabel);
		noticeLabel->retain();
		clipper->setPosition(ccp(35, 228));

		notice_layer->addChild(clipper);

		this->addChild(notice_layer);
		CCDictionary *strings = CCDictionary::createWithContentsOfFile("Element/strings.xml");
		const char *reply = ((CCString *)strings->objectForKey("Notice"))->m_sString.c_str();

		noticeLabel->setString(reply);
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
	CCUserDefault::sharedUserDefault()->setBoolForKey("isHardCore", true);
	if (hardCore_btn)
	{
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("menu02_1.png");
		hardCore_btn->setDisplayFrame(frame);
	}

	SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");
	if (hardCoreLayer)
	{
		hardCoreLayer->removeAllChildren();
		hardCoreLayer->removeFromParent();
		hardCoreLayer = NULL;
	}
}

void StartMenu::onHardCoreOff(CCObject *sender)
{

	SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/cancel.ogg");
	if (hardCoreLayer)
	{
		hardCoreLayer->removeAllChildren();
		hardCoreLayer->removeFromParent();
		hardCoreLayer = NULL;
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

			CCMenu *confirm_menu = CCMenu::create(yes_btn, no_btn, NULL);
			confirm_menu->alignItemsHorizontallyWithPadding(24);
			confirm_menu->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 30));

			hardCoreLayer->addChild(confirm_bg, 600);
			hardCoreLayer->addChild(confirm_menu, 650);
			hardCoreLayer->addChild(hardcore_title, 650);
			hardCoreLayer->addChild(hardcore_text, 650);
			this->addChild(hardCoreLayer, 700);
		}
	}
}

void StartMenu::onHardCoreCallBack()
{
	// if (MemberID)
	// {
	addSprites("Select.plist");
	addSprites("UI.plist");
	addSprites("Report.plist");
	addSprites("Ougis.plist");
	addSprites("Ougis2.plist");
	addSprites("Map.plist");
	addSprites("Gears.plist");

	CCScene *selectScene = CCScene::create();
	SelectLayer *selectLayer = SelectLayer::create();

	selectScene->addChild(selectLayer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, selectScene));
	// }
	CCTips *tip = CCTips::create("ServerMainten");
	this->addChild(tip, 5000);
}

void StartMenu::onNormalCallBack(CCObject *sender)
{
	addSprites("Select.plist");
	addSprites("UI.plist");
	addSprites("Report.plist");
	addSprites("Ougis.plist");
	addSprites("Ougis2.plist");
	addSprites("Map.plist");
	addSprites("Gears.plist");

	CCScene *selectScene = CCScene::create();
	SelectLayer *selectLayer = SelectLayer::create();

	selectScene->addChild(selectLayer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, selectScene));
}

void StartMenu::onTrainingCallBack()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	addSprites("Select.plist");

	// int i = 1;
	int i = 0;

	// if (adResult != 1)
	// {
	// 	Cheats = 0;
	// }

	if (Cheats > 10)
	{
		i = 2;
	}

	if (i == 0)
	{
		this->onNormalCallBack(NULL);
	}
	else if (i == 1)
	{
		addSprites("UI.plist");
		addSprites("Report.plist");
		addSprites("Ougis.plist");
		addSprites("Ougis2.plist");
		addSprites("Map.plist");
		addSprites("Gears.plist");

		CCDictionary *dic = CCDictionary::create();

		srand((int)time(0));
		CCString *tmpChar = CCString::create("Gaara");
		CCString *tmpRole = CCString::create("Player");
		CCString *tmpGroup = CCString::create("Konoha");

		dic->setObject(tmpChar, "character");
		dic->setObject(tmpRole, "role");
		dic->setObject(tmpGroup, "group");

		CCArray *tempHeros = CCArray::createWithObject(dic);

		CCArray *realHero = CCArray::create();
		for (int i = 0; i < heroNum; i++)
		{
			if (strcmp(tmpChar->getCString(), heroList[i]) == 0)
			{
				continue;
			}
			CCString *hero = CCString::create(heroList[i]);
			realHero->addObject(hero);
		}
		char *heroList2[] = {"Naruto", "Deidara", "Konan"};

		CCArray *enemyHero = CCArray::create();
		int num2 = sizeof(heroList2) / sizeof(char *);
		for (int x = 0; x < num2; x++)
		{
			if (strcmp(tmpChar->getCString(), heroList2[x]) == 0)
			{
				continue;
			}
			CCString *hero = CCString::create(heroList2[x]);
			enemyHero->addObject(hero);
		}
		//--------------

		for (int i = 0; i < ComCount; i++)
		{

			if (i < KonohaCount)
			{
				int length = realHero->count();
				srand((int)time(0));
				int index = random(length);
				if (index == (int)realHero->count())
				{

					index = realHero->count() - 1;
				}

				CCObject *tempObject = realHero->objectAtIndex(index);
				CCString *hero = (CCString *)tempObject;

				dic = CCDictionary::create();
				tmpChar = CCString::create(hero->getCString());
				tmpRole = CCString::create("Com");
				tmpGroup = CCString::create("Konoha");

				dic->setObject(tmpChar, "character");
				dic->setObject(tmpRole, "role");
				dic->setObject(tmpGroup, "group");

				tempHeros->addObject(dic);
				realHero->removeObjectAtIndex(index);
			}
			else
			{

				int length = realHero->count();
				srand((int)time(0));
				int index = random(length);
				if (index == (int)realHero->count())
				{
					index = realHero->count() - 1;
				}

				CCObject *tempObject = realHero->objectAtIndex(index);
				CCString *hero = (CCString *)tempObject;

				dic = CCDictionary::create();
				tmpChar = CCString::create(hero->getCString());
				tmpRole = CCString::create("Com");
				tmpGroup = CCString::create("Akatsuki");

				dic->setObject(tmpChar, "character");
				dic->setObject(tmpRole, "role");
				dic->setObject(tmpGroup, "group");

				tempHeros->addObject(dic);
				realHero->removeObjectAtIndex(index);
				// int length=enemyHero->count();
				// srand((int)time(0));
				// int index=random(length);
				// if(index==(int)enemyHero->count()){
				// 	index=enemyHero->count()-1;
				// }

				// CCObject* tempObject=enemyHero->objectAtIndex(index);
				// CCString* hero=(CCString*) tempObject;

				// dic=CCDictionary::create();
				// tmpChar=CCString::create(hero->getCString());
				// tmpRole=CCString::create("Com");
				// tmpGroup=CCString::create("Akatsuki");

				// dic->setObject(tmpChar,"character");
				// dic->setObject(tmpRole,"role");
				// dic->setObject(tmpGroup,"group");

				// tempHeros->addObject(dic);
				// enemyHero->removeObjectAtIndex(index);

				////---------
			}
		}

		CCScene *loadScene = CCScene::create();
		LoadLayer *loadLayer = LoadLayer::create();
		loadLayer->tempHeros = tempHeros;
		loadLayer->_isHardCoreMode = true;
		loadScene->addChild(loadLayer);
		loadLayer->preloadAudio();
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, loadScene));
	}
	else if (i == 2)
	{

		//4v4
		addSprites("UI.plist");
		addSprites("Report.plist");
		addSprites("Ougis.plist");
		addSprites("Ougis2.plist");
		addSprites("Map.plist");
		addSprites("Gears.plist");

		CCDictionary *dic = CCDictionary::create();

		char *heroList1[] = {"Konan", "Sakura", "Naruto", "Sai", "Deidara",
							 "Kakashi", "Itachi", "Tenten", "Jiraiya", "Suigetsu",
							 "Tsunade", "Tobirama", "Neji", "Ino", "Asuma", "Gaara",
							 "Karin", "Sasuke", "Hidan", "Choji", "Kankuro",
							 "Shino", "Minato", "Tobi", "Kakuzu", "Hinata",
							 "Shikamaru", "Chiyo", "Kisame",
							 "Hiruzen", "Kiba", "Jugo", "Lee"};

		srand((int)time(0));
		int index2 = random(sizeof(heroList1) / sizeof(char *));
		CCString *tmpChar = CCString::create(heroList1[index2]);
		CCString *tmpRole = CCString::create("Player");
		CCString *tmpGroup = CCString::create("Konoha");

		dic->setObject(tmpChar, "character");
		dic->setObject(tmpRole, "role");
		dic->setObject(tmpGroup, "group");

		CCArray *tempHeros = CCArray::createWithObject(dic);

		CCArray *realHero = CCArray::create();
		int num = sizeof(heroList1) / sizeof(char *);
		for (int i = 0; i < num; i++)
		{
			if (strcmp(tmpChar->getCString(), heroList1[i]) == 0)
			{
				continue;
			}
			CCString *hero = CCString::create(heroList1[i]);
			realHero->addObject(hero);
		}
		char *heroList2[] = {"Naruto", "Deidara", "Konan"};

		CCArray *enemyHero = CCArray::create();
		int num2 = sizeof(heroList2) / sizeof(char *);
		for (int x = 0; x < num2; x++)
		{
			if (strcmp(tmpChar->getCString(), heroList2[x]) == 0)
			{
				continue;
			}
			CCString *hero = CCString::create(heroList2[x]);
			enemyHero->addObject(hero);
		}
		//--------------

		for (int i = 0; i < 7; i++)
		{

			if (i < 3)
			{
				int length = realHero->count();
				srand((int)time(0));
				int index = random(length);
				if (index == (int)realHero->count())
				{

					index = realHero->count() - 1;
				}

				CCObject *tempObject = realHero->objectAtIndex(index);
				CCString *hero = (CCString *)tempObject;

				dic = CCDictionary::create();
				tmpChar = CCString::create(hero->getCString());
				tmpRole = CCString::create("Com");
				tmpGroup = CCString::create("Konoha");

				dic->setObject(tmpChar, "character");
				dic->setObject(tmpRole, "role");
				dic->setObject(tmpGroup, "group");

				tempHeros->addObject(dic);
				realHero->removeObjectAtIndex(index);
			}
			else
			{

				int length = realHero->count();
				srand((int)time(0));
				int index = random(length);
				if (index == (int)realHero->count())
				{
					index = realHero->count() - 1;
				}

				CCObject *tempObject = realHero->objectAtIndex(index);
				CCString *hero = (CCString *)tempObject;

				dic = CCDictionary::create();
				tmpChar = CCString::create(hero->getCString());
				tmpRole = CCString::create("Com");
				tmpGroup = CCString::create("Akatsuki");

				dic->setObject(tmpChar, "character");
				dic->setObject(tmpRole, "role");
				dic->setObject(tmpGroup, "group");

				tempHeros->addObject(dic);
				realHero->removeObjectAtIndex(index);
			}
		}

		CCScene *loadScene = CCScene::create();
		LoadLayer *loadLayer = LoadLayer::create();
		loadLayer->tempHeros = tempHeros;
		loadScene->addChild(loadLayer);
		loadLayer->preloadAudio();
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, loadScene));
	}
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
	CCObject *pObject = NULL;
	if (posY > _pos02 || (isDrag && isClockwise))
	{
		CCARRAY_FOREACH(_menu_array, pObject)
		{
			MenuButton *menu = (MenuButton *)pObject;
			if (menu->getPositionY() == _pos01)
			{
				CCActionInterval *spn = CCMoveTo::create(0.5, ccp(105, _pos02));
				this->reorderChild(menu, 1);
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
					NULL);
				this->reorderChild(menu, 3);
				menu->_isTop = true;

				/*if(menu->getBtnType()!=Training){
						hardCore_btn->setVisible(false);
					}*/

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
				this->reorderChild(menu, 1);
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
					NULL);
				this->reorderChild(menu, 1);
				menu->_isTop = false;
				menu->runAction(spn);
			}
		};
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
					NULL);
				this->reorderChild(menu, 3);
				menu->_isTop = true;
				/*	if(menu->getBtnType()!=Training){
						hardCore_btn->setVisible(false);
					}*/

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
				this->reorderChild(menu, 1);
				menu->_isBottom = true;
				CCFadeOut *fo = CCFadeOut::create(0.3f);
				CCSpawn *seq = CCSpawn::createWithTwoActions(spn, fo);
				menu->runAction(seq);
			}
			else if (menu->getPositionY() == _pos02 && menu->_isBottom)
			{

				CCActionInterval *spn = CCMoveTo::create(0.5, ccp(105, _pos01));
				this->reorderChild(menu, 2);
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
					NULL);
				this->reorderChild(menu, 2);
				menu->_isTop = false;
				menu->runAction(spn);
			}
		};
	};
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
			case Network:
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
#endif
};

void StartMenu::onExitCallBack()
{

	this->keyBackClicked();
}
