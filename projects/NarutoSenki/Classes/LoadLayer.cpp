#include "LoadLayer.h"
#include "GameMode/GameModeImpl.h"

LoadLayer::LoadLayer()
{
	tempHeros = nullptr;
	loadNum = 0;
	_hudLayer = nullptr;
	_bgLayer = nullptr;
	_hudLayer = nullptr;
	_isHardCoreMode = true;
	_enableGear = true;
}

LoadLayer::~LoadLayer()
{
	CC_SAFE_RELEASE(tempHeros);
}

bool LoadLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

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

		CCSprite *loading_title = CCSprite::createWithSpriteFrameName("loading_title.png");
		loading_title->setAnchorPoint(ccp(0, 0));
		loading_title->setPosition(ccp(2, winSize.height - loading_title->getContentSize().height - 2));
		addChild(loading_title, 3);

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

		bRet = true;
	} while (0);

	auto &gd = getGameModeHandler()->getGameData();
	_enableGear = gd.enableGear;
	_isHardCoreMode = gd.isHardCore;

	return bRet;
}

void LoadLayer::preloadIMG()
{
	int count = tempHeros->count();
	if (count == 2) // 1v1
		count = 0;
	else if (count == 4) // Boss mode (3v1)
		count = 3;
	else if (count == 5) // Boss mode (4v1)
		count = 4;
	else if (count == 6) // 3v3
		count = 3;
	else if (count == 8) // 4v4
		count = 4;

	if (tempHeros)
	{
		int i = 0;
		CCObject *pObject = nullptr;
		CCARRAY_FOREACH(tempHeros, pObject)
		{
			auto tempdict = (CCDictionary *)pObject;
			auto player = tempdict->valueForKey("character")->getCString();
			perloadCharIMG(player);

			if (i == 0 || (i < count && _enableGear))
				setLoadingAnimation(player, i);
			i++;
		}
		tempHeros->retain();
	}

	if (_isHardCoreMode)
	{
		addSprites("Element/Roshi/Roshi.plist");
		addSprites("Element/Han/Han.plist");
		KTools::prepareFileOGG(kGuardian_Han);
		KTools::prepareFileOGG(kGuardian_Roshi);
	}
	addSprites(kFlog_Kotetsu);
	addSprites(kFlog_FemalePain);

	addSprites(kFlog_Izumo);
	addSprites(kFlog_Kakashi);

	addSprites(kFlog_Pain);
	addSprites(kFlog_Obito);

	KTools::prepareFileOGG("Effect");
	KTools::prepareFileOGG("Ougis");

	try
	{
		setRand();
		int num = rand() % 3 + 1;
		CCSprite *tips = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("tip%d.png", num)->getCString());
		tips->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		addChild(tips);
	}
	catch (...)
	{
		CCLOG("error");
	}

	CCSprite *loading = CCSprite::createWithSpriteFrameName("loading_font.png");

	loading->setPosition(ccp(winSize.width - 120, 45));
	auto fade = CCFadeOut::create(1.0f);
	auto fadeseq = CCRepeatForever::create(CCSequence::create(fade, fade->reverse(), nullptr));
	addChild(loading);
	loading->runAction(fadeseq);

	scheduleOnce(schedule_selector(LoadLayer::playBGM), 1.0f);
	scheduleOnce(schedule_selector(LoadLayer::onLoadFinish), 3.0f);
}

void LoadLayer::perloadCharIMG(const char *player)
{
	if (!player)
	{
		CCLOG("Perload a null character images !");
		return;
	}

	CCTexture2D::PVRImagesHavePremultipliedAlpha(true);

	const char *path = CCString::createWithFormat("Element/Skills/%s_Skill.plist", player)->getCString();
	if (CCFileUtils::sharedFileUtils()->isFileExist(path))
		addSprites(path);
	else
		CCLOG("Not found file %s", path);

	KTools::prepareFileOGG(player);

	path = CCString::createWithFormat("Element/%s/%s.plist", player, player)->getCString();
	addSprites(path);
	// Add extra sprites
	if (is_same(player, "Jiraiya"))
	{
		addSprites(mkpath(SageJiraiya));
		KTools::prepareFileOGG("SageJiraiya");
	}
	else if (is_same(player, "Kankuro"))
	{
		addSprites(mkpath(Karasu));
		addSprites(mkpath(Sanshouuo));
		addSprites(mkpath(Saso));
	}
	else if (is_same(player, "Chiyo"))
	{
		addSprites(mkpath(Parents));
	}
	else if (is_same(player, "Kakuzu"))
	{
		addSprites(mkpath(MaskRaiton));
		addSprites(mkpath(MaskFuton));
		addSprites(mkpath(MaskKaton));
	}
	else if (is_same(player, "Naruto"))
	{
		addSprites(mkpath(RikudoNaruto));
		addSprites(mkpath(SageNaruto));
		addSprites(mkpath(Kurama));
		KTools::prepareFileOGG("SageNaruto");
		KTools::prepareFileOGG("RikudoNaruto");
	}
	else if (is_same(player, "Lee"))
	{
		addSprites(mkpath(RockLee));
	}
	else if (is_same(player, "Tsunade"))
	{
		addSprites(mkpath(Slug));
	}
	else if (is_same(player, "Kakashi"))
	{
		addSprites(mkpath(DogWall));
	}
	else if (is_same(player, "Deidara"))
	{
		addSprites(mkpath(Centipede));
	}
	else if (is_same(player, "Pain"))
	{
		addSprites(mkpath(DevaPath));
		addSprites(mkpath(AsuraPath));
		addSprites(mkpath(AnimalPath));
		addSprites(mkpath(Nagato));
		KTools::prepareFileOGG("Nagato");
	}
	else if (is_same(player, "Sasuke"))
	{
		addSprites(mkpath(ImmortalSasuke));
		KTools::prepareFileOGG("ImmortalSasuke");
	}
	else if (is_same(player, "Kiba"))
	{
		addSprites(mkpath(Akamaru));
	}
}

void LoadLayer::unloadCharIMG(const CharacterBase *c)
{
	if (c == nullptr)
		return;

	auto roleName = c->getRole()->getCString();
	auto charName = c->getCharacter()->getCString();

	if (is_same(roleName, kRoleClone) ||
		is_same(roleName, kRoleSummon))
	{
		return;
	}

	auto path = CCString::createWithFormat("Element/%s/%s.plist", charName, charName)->getCString();
	removeSprites(path);

	if (is_same(roleName, kRoleCom) ||
		is_same(roleName, kRolePlayer))
	{
		KTools::prepareFileOGG(charName, true);
	}

	if (is_same(charName, "Jiraiya"))
	{
		removeSprites("Element/SageJiraiya/SageJiraiya.plist");
		KTools::prepareFileOGG("SageJiraiya", true);
	}
	else if (is_same(charName, "Kankuro"))
	{
		removeSprites("Element/Karasu/Karasu.plist");
		removeSprites("Element/Sanshouuo/Sanshouuo.plist");
	}
	else if (is_same(charName, "Kakuzu"))
	{
		removeSprites("Element/MaskFuton/MaskFuton.plist");
		removeSprites("Element/MaskRaiton/MaskRaiton.plist");
		removeSprites("Element/MaskKaton/MaskKaton.plist");
	}
	else if (is_same(charName, "Naruto"))
	{
		removeSprites("Element/SageNaruto/SageNaruto.plist");
		removeSprites("Element/RikudoNaruto/RikudoNaruto.plist");
		KTools::prepareFileOGG("SageNaruto", true);
		KTools::prepareFileOGG("RikudoNaruto", true);
	}
	else if (is_same(charName, "RockLee"))
	{
		removeSprites("Element/Lee/Lee.plist");
	}
	else if (is_same(charName, "Lee"))
	{
		removeSprites("Element/RockLee/RockLee.plist");
	}
	else if (is_same(charName, "Sasuke"))
	{
		KTools::prepareFileOGG("ImmortalSasuke", true);
		removeSprites("Element/ImmortalSasuke/ImmortalSasuke.plist");
	}
	else if (is_same(charName, "Pain"))
	{
		KTools::prepareFileOGG("Nagato", true);
		removeSprites("Element/AnimalPath/AnimalPath.plist");
		removeSprites("Element/AsuraPath/AsuraPath.plist");
		removeSprites("Element/DevaPath/DevaPath.plist");
		removeSprites("Element/Nagato/Nagato.plist");
	}
	else if (is_same(charName, "Nagato"))
	{
		removeSprites("Element/AnimalPath/AnimalPath.plist");
		removeSprites("Element/AsuraPath/AsuraPath.plist");
		removeSprites("Element/DevaPath/DevaPath.plist");
	}
}

void LoadLayer::setLoadingAnimation(const char *player, int index)
{
	CCSprite *loadingAvator = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s_Walk_01.png", player)->getCString());
	loadingAvator->setFlipX(true);
	loadingAvator->setPosition(ccp(winSize.width - 100 + index * 16, 30));
	loadingAvator->setAnchorPoint(ccp(0, 0));

	CCArray *animeFrames = CCArray::create();
	CCString *str;

	const char *file = CCString::createWithFormat("%s_Walk_", player)->getCString();
	int frameCount;
	//FIXME: use the other way get animation frame count
	if (is_same(player, "Konan"))
		frameCount = 1;
	else
		frameCount = 7;

	for (int i = 1; i < frameCount; i++)
	{
		str = CCString::createWithFormat("%s%02d.png", file, i);
		auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
		animeFrames->addObject(frame);
	}

	auto tempAnimation = CCAnimation::createWithSpriteFrames(animeFrames, float(1.0 / 10.0));
	auto tempAction = CCAnimate::create(tempAnimation);
	auto seqArray = CCArray::createWithObject(tempAction);
	auto seq = CCRepeatForever::create(CCSequence::create(seqArray));

	addChild(loadingAvator);
	loadingAvator->runAction(seq);
}

void LoadLayer::playBGM(float dt)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(LOADING_MUSIC, false);
}

void LoadLayer::preloadAudio()
{
	auto bg_src = _enableGear ? "blue_bg.png" : "red_bg.png";
	CCSprite *bgSprite = CCSprite::create(bg_src);

	FULL_SCREEN_SPRITE(bgSprite);
	bgSprite->setAnchorPoint(ccp(0, 0));
	bgSprite->setPosition(ccp(0, 0));
	addChild(bgSprite, -5);

	preloadIMG();
}

void LoadLayer::onLoadFinish(float dt)
{
	CCScene *gameScene = CCScene::create();

	_hudLayer = HudLayer::create();

	_gameLayer = GameLayer::create();
	_gameLayer->setHudLayer(_hudLayer);
	_gameLayer->setTotalKills(CCString::create("0"));
	_gameLayer->setTotalTM(CCString::create("0"));
	_gameLayer->Heros = tempHeros;
	_gameLayer->initHeros();

	_bgLayer = BGLayer::create();
	_bgLayer->initBg(_gameLayer->mapId);

	_hudLayer->initHeroInterface();
	_gameLayer->invokeAllCallbacks();

	gameScene->addChild(_gameLayer, GlTag);
	gameScene->addChild(_bgLayer, BgTag);
	gameScene->addChild(_hudLayer, HudTag);

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, gameScene));
}
