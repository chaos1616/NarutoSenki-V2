#include <time.h>

#include "StartMenu.h"

USING_NS_CC_EXT;
using namespace CocosDenshion;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "../../../cocos2dx/platform/android/jni/JniHelper.h"
#endif

SelectLayer::SelectLayer(void)
{
	_heroHalf = NULL;
	_heroName = NULL;
	_selectImg = NULL;

	_selectList = NULL;

	_comSelector1 = NULL;
	_comLabel1 = NULL;

	_comSelector2 = NULL;
	_comLabel2 = NULL;

	isStart = false;
	_isHardCoreMode = true;
	_isRandomChar = false;

	SaveError = false;
	_playerSelect = NULL;
	_com1Select = NULL;
	_com2Select = NULL;
	selectArray = NULL;

	_pageLayer1 = NULL;
	_pageLayer2 = NULL;
	_pageLayer3 = NULL;

	isPosting = false;
	refreshBtn = NULL;

	_teamSelector = NULL;
}

SelectLayer::~SelectLayer(void)
{
	CC_SAFE_RELEASE(selectArray);
}

bool SelectLayer::init()
{

	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		lua_call_init_func;

		// if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		// {
		// if (KTools::checkMD5() == 0)
		// {
		// 	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		// 	CCDirector::sharedDirector()->end();
		// 	return false;
		// }
		// }

		const char *bg_src = "blue_bg.png";

		CCSprite *bgSprite = CCSprite::create(bg_src);
		FULL_SCREEN_SPRITE(bgSprite);
		bgSprite->setAnchorPoint(ccp(0, 0));
		bgSprite->setPosition(ccp(0, 0));
		this->addChild(bgSprite, -5);

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
		this->addChild(cloud_left, 2);

		CCActionInterval *cmv1 = CCMoveBy::create(1, ccp(-15, 0));
		CCAction *cseq1 = CCRepeatForever::create(CCSequence::create(cmv1, cmv1->reverse(), NULL));
		cloud_left->runAction(cseq1);

		CCSprite *cloud_right = CCSprite::createWithSpriteFrameName("cloud.png");
		cloud_right->setPosition(ccp(winSize.width - cloud_right->getContentSize().width, 15));
		cloud_right->setFlipY(true);
		cloud_right->setAnchorPoint(ccp(0, 0));
		this->addChild(cloud_right, 2);

		CCActionInterval *cmv2 = CCMoveBy::create(1, ccp(15, 0));
		CCAction *cseq2 = CCRepeatForever::create(CCSequence::create(cmv2, cmv2->reverse(), NULL));
		cloud_right->runAction(cseq2);

		CCSprite *cloud_top = CCSprite::createWithSpriteFrameName("cloud_top.png");
		cloud_top->setPosition(ccp(winSize.width / 2, winSize.height - (cloud_top->getContentSize().height + 12)));
		cloud_top->setAnchorPoint(ccp(0.5f, 0));
		this->addChild(cloud_top, 1);

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

		CCSprite *select_title = CCSprite::createWithSpriteFrameName("hcmode_title.png");

		select_title->setAnchorPoint(ccp(0, 0));
		select_title->setPosition(ccp(2, winSize.height - select_title->getContentSize().height - 2));
		this->addChild(select_title, 3);

		_selectList = CCArray::create();
		selectArray = CCArray::create();
		_pageLayer1 = CCLayer::create();
		_pageLayer2 = CCLayer::create();
		_pageLayer3 = CCLayer::create();

		const char *selectList[] = {
			// Page One
			"Naruto", "Sakura", "Sai", "Kakashi",
			"None", "None", "None",
			"Shikamaru", "Ino", "Choji", "Asuma",
			"Kiba", "Hinata", "Shino",
			"Neji", "Tenten", "Lee", "None",
			"None", "None", "None",
			// Page Two
			"None", "Tobirama", "Hiruzen", "Minato",
			"Jiraiya", "Tsunade", "Orochimaru",
			"None", "Deidara", "Kakuzu", "Hidan",
			"Tobi", "Konan", "Pain",
			"Itachi", "Kisame", "None", "None",
			"None", "None", "None",
			// Page Three
			"Sasuke", "Karin", "Suigetsu", "Jugo",
			"None", "None", "None",
			"Gaara", "None", "Kankuro", "Chiyo",
			"None", "None", "None",
			"None", "None", "None", "None",
			"None", "None", "None"};

		int num = sizeof(selectList) / sizeof(char *);

		int Column = 0;
		int Row = 0;
		int Page = 0;

		for (int i = 0; i < num; i++)
		{

			const char *charName;
			charName = selectList[i];

			_selectList->addObject(CCString::createWithFormat("%s", charName));

			CCString *path;

			path = CCString::createWithFormat("%s_select.png", charName);
			Column = i % 7;
			Row = i / 7;
			Page = int(i / 21);
			SelectButton *select_btn = SelectButton::create(path->getCString());
			select_btn->setDelegate1(this);
			select_btn->setCharName(CCString::createWithFormat("%s", charName));
			if (Page == 0)
			{
				select_btn->setPosition(ccp(winSize.width / 2 - 36 + (Column - 1) * 27 + Column / 4 * 10, winSize.height - 112 - (72 * Row)));
				_pageLayer1->addChild(select_btn, -Column);
			}
			else if (Page == 1)
			{
				select_btn->setPosition(ccp(winSize.width / 2 - 36 + (Column - 1) * 27 + Column / 4 * 10, winSize.height - 112 - (72 * (Row - 3))));
				_pageLayer2->addChild(select_btn, -Column);
			}
			else if (Page == 2)
			{
				select_btn->setPosition(ccp(winSize.width / 2 - 36 + (Column - 1) * 27 + Column / 4 * 10, winSize.height - 112 - (72 * (Row - 6))));
				_pageLayer3->addChild(select_btn, -Column);
			}
			// else if (Page == 3)
			// {
			// 	select_btn->setPosition(ccp(winSize.width / 2 - 36 + (Column - 1) * 27 + Column / 4 * 10, winSize.height - 112 - (72 * (Row - 9))));
			// 	_pageLayer4->addChild(select_btn, -Column);
			// }

			selectArray->addObject(select_btn);
		};

		this->addChild(_pageLayer1, 5);
		this->addChild(_pageLayer2, 5);
		this->addChild(_pageLayer3, 5);

		_pageLayer2->setVisible(false);
		_pageLayer3->setVisible(false);
		_pageLayer2->setPositionY(2000);
		_pageLayer3->setPositionY(2000);

		page1_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("page1_off.png"), CCSprite::createWithSpriteFrameName("page1_on.png"), this, menu_selector(SelectLayer::onPage1Btn));
		page2_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("page2_off.png"), CCSprite::createWithSpriteFrameName("page2_on.png"), this, menu_selector(SelectLayer::onPage2Btn));
		page3_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("page3_off.png"), CCSprite::createWithSpriteFrameName("page3_on.png"), this, menu_selector(SelectLayer::onPage3Btn));

		page_menu = CCMenu::create(page1_btn, page2_btn, page3_btn, NULL);

		page_menu->alignItemsHorizontallyWithPadding(20);
		page_menu->setPosition(ccp(winSize.width / 2 + 48, 42));
		this->addChild(page_menu, 10);
		page1_btn->selected();

		selectArray->retain();
		_selectList->retain();

		CCString *hero = (CCString *)_selectList->objectAtIndex(0);

		const char *path = CCString::createWithFormat("%s_half.png", hero->getCString())->getCString();
		_heroHalf = CCSprite::createWithSpriteFrameName(path);
		_heroHalf->setAnchorPoint(ccp(0, 0));
		_heroHalf->setPosition(ccp(10, 10));
		this->addChild(_heroHalf, 1);

		const char *namePath = CCString::createWithFormat("%s_font.png", hero->getCString())->getCString();
		_heroName = CCSprite::createWithSpriteFrameName(namePath);
		_heroName->setAnchorPoint(ccp(0.5f, 0));
		_heroName->setPosition(ccp(100, 20));
		this->addChild(_heroName, 5);

		_selectImg = CCSprite::createWithSpriteFrameName("1p.png");
		_selectImg->setAnchorPoint(ccp(0, 0));
		SelectButton *pObject = (SelectButton *)selectArray->objectAtIndex(0);
		_selectImg->setPosition(ccp(pObject->getPositionX() - 2, pObject->getPositionY() - 2));
		this->addChild(_selectImg, 500);

		_selectHero = pObject->getCharName()->getCString();

		CCActionInterval *blink = CCBlink::create(0.6f, 1);
		_selectImg->runAction(CCRepeatForever::create(blink));

		if (adResult == 1)
		{
			_teamSelector = CCLayer::create();

			CCSprite *_teamBg = CCSprite::createWithSpriteFrameName("team_bg.png");
			_teamBg->setAnchorPoint(ccp(0, 0));
			_teamBg->setPosition(ccp(0, 185));
			_teamSelector->addChild(_teamBg);

			_comSelector1 = CCSprite::createWithSpriteFrameName("unknow_select.png");
			_comSelector1->setAnchorPoint(ccp(0, 0));
			_comSelector1->setPosition(ccp(2, 194));
			_teamSelector->addChild(_comSelector1);

			_comLabel1 = CCSprite::createWithSpriteFrameName("com_label.png");
			_comLabel1->setAnchorPoint(ccp(0.5, 0.5f));
			_comLabel1->setPosition(ccp(_comSelector1->getPositionX() + _comSelector1->getContentSize().width + 2 + 18, _comSelector1->getPositionY() + _comSelector1->getContentSize().height / 2));
			_teamSelector->addChild(_comLabel1);

			_comSelector2 = CCSprite::createWithSpriteFrameName("unknow_select.png");
			_comSelector2->setAnchorPoint(ccp(0, 0));
			_comSelector2->setPosition(ccp(_comSelector1->getPositionX() + _comSelector1->getContentSize().width + 40, _comSelector1->getPositionY()));
			_teamSelector->addChild(_comSelector2);

			_comLabel2 = CCSprite::createWithSpriteFrameName("com_label.png");
			_comLabel2->setAnchorPoint(ccp(0.5, 0.5f));
			_comLabel2->setPosition(ccp(_comSelector2->getPositionX() + _comSelector2->getContentSize().width + 2 + 18, _comSelector2->getPositionY() + _comSelector2->getContentSize().height / 2));
			_teamSelector->addChild(_comLabel2);

			this->addChild(_teamSelector, 50);
		}
		CCMenuItem *ranking_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ranking_btn.png"), NULL, NULL, this, menu_selector(SelectLayer::onRankingBtn));
		CCMenu *menu3 = CCMenu::create(ranking_btn, NULL);
		ranking_btn->setAnchorPoint(ccp(1, 0.5f));
		menu3->setPosition(winSize.width - 15, winSize.height - 34);
		this->addChild(menu3, 5);

		CCMenuItem *start_bt = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("start_btn.png"), NULL, NULL, this, menu_selector(SelectLayer::onGameStart));
		CCMenu *menu = CCMenu::create(start_bt, NULL);
		menu->setAnchorPoint(ccp(0, 0));
		menu->setPosition(winSize.width - 40, 36);
		this->addChild(menu, 5);

		CCMenuItem *skill_bt = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("skill_btn.png"), NULL, NULL, this, menu_selector(SelectLayer::onSkillMenu));
		CCMenu *menu2 = CCMenu::create(skill_bt, NULL);
		menu2->setAnchorPoint(ccp(0, 0));
		menu2->setPosition(winSize.width - 35, 96);
		this->addChild(menu2, 5);

		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isBGM") != false)
		{
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(SELECT_MUSIC, true);
		}

		if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		{
			this->setKeypadEnabled(true);
		}

		bRet = true;
	} while (0);

	return bRet;
}

void SelectLayer::onPage1Btn(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(SELECT_SOUND);
	page2_btn->unselected();
	page3_btn->unselected();
	page1_btn->selected();

	_pageLayer1->setVisible(true);
	_pageLayer2->setVisible(false);
	_pageLayer3->setVisible(false);
	_pageLayer1->setPositionY(0);
	_pageLayer2->setPositionY(2000);
	_pageLayer3->setPositionY(2000);
}

void SelectLayer::onPage2Btn(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(SELECT_SOUND);
	page1_btn->unselected();
	page3_btn->unselected();
	page2_btn->selected();

	_pageLayer2->setVisible(true);
	_pageLayer1->setVisible(false);
	_pageLayer3->setVisible(false);
	_pageLayer2->setPositionY(0);
	_pageLayer1->setPositionY(2000);
	_pageLayer3->setPositionY(2000);
}

void SelectLayer::onPage3Btn(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(SELECT_SOUND);
	page1_btn->unselected();
	page2_btn->unselected();
	page3_btn->selected();

	_pageLayer3->setVisible(true);
	_pageLayer1->setVisible(false);
	_pageLayer2->setVisible(false);

	_pageLayer3->setPositionY(0);
	_pageLayer1->setPositionY(2000);
	_pageLayer2->setPositionY(2000);
}

void SelectLayer::setSelected(CCObject *sender)
{

	SelectButton *btn = (SelectButton *)sender;
	if (_selectImg)
	{
		_selectImg->setPosition(ccp(btn->getPositionX() - 2, btn->getPositionY() - 2));
	}

	if (/* mode != CustomSelectMode && */ adResult != 1 && _playerSelect)
	{
		return;
	}

	_selectHero = btn->getCharName()->getCString();

	if (_isHardCoreMode)
	{

		CCActionInterval *fd = CCFadeOut::create(1.0f);
		CCAction *seq = CCRepeatForever::create(CCSequence::create(fd, fd->reverse(), NULL));

		if (!_playerSelect)
		{

			if (btn->_clickTime >= 2)
			{
				_playerSelect = _selectHero;

				if (adResult != 1)
				{
					_selectImg->removeFromParent();
					_selectImg = NULL;
				}
				else
				{
					this->getComLabel1()->runAction(seq);
				}
			}

			_heroHalf->removeFromParent();
			const char *charName = btn->getCharName()->getCString();

			const char *path = CCString::createWithFormat("%s_half.png", charName)->getCString();
			_heroHalf = CCSprite::createWithSpriteFrameName(path);

			_heroHalf->setAnchorPoint(ccp(0, 0));
			_heroHalf->setPosition(ccp(10, 10));
			this->addChild(_heroHalf, 1);

			_heroName->removeFromParent();
			const char *namePath = CCString::createWithFormat("%s_font.png", charName)->getCString();
			_heroName = CCSprite::createWithSpriteFrameName(namePath);
			_heroName->setAnchorPoint(ccp(0.5f, 0));
			_heroName->setPosition(ccp(100, 20));
			this->addChild(_heroName, 5);
		}
		else if (!_com1Select)
		{
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s_small.png", _selectHero)->getCString());
			this->getComSelector1()->setDisplayFrame(frame);

			if (btn->_clickTime >= 2)
			{
				_com1Select = _selectHero;

				this->getComLabel1()->stopAllActions();
				this->getComLabel1()->setOpacity(255);
				CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("com_label2.png");
				this->getComLabel1()->setDisplayFrame(frame);
				this->getComLabel2()->runAction(seq);
			}
		}
		else if (!_com2Select)
		{

			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s_small.png", _selectHero)->getCString());
			this->getComSelector2()->setDisplayFrame(frame);

			if (btn->_clickTime >= 2)
			{
				_com2Select = _selectHero;

				this->getComLabel2()->stopAllActions();
				this->getComLabel2()->setOpacity(255);
				CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("com_label2.png");
				this->getComLabel2()->setDisplayFrame(frame);

				_selectImg->removeFromParent();
				_selectImg = NULL;
			}
		}
	}
}

void SelectLayer::onError(CCObject *sender)
{

	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCDirector::sharedDirector()->end();
	return;
}

void SelectLayer::onSkillMenu(CCObject *sender)
{
	CCScene *pscene = CCScene::create();
	SkillLayer *skillLayer = SkillLayer::create();
	skillLayer->setDelegate(this);
	skillLayer->initInterface();
	pscene->addChild(skillLayer);

	CCDirector::sharedDirector()->pushScene(pscene);
}

void SelectLayer::onRankingBtn(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCScene *pscene = CCScene::create();
	RakingLayer *rakingLayer = RakingLayer::create();
	rakingLayer->setDelegate(this);
	pscene->addChild(rakingLayer);

	CCDirector::sharedDirector()->pushScene(pscene);
}

void SelectLayer::onQuestBtn(CCObject *sender)
{

	CCTips *tip = CCTips::create("ComingSoon");
	this->addChild(tip, 5000);
	return;
}

void SelectLayer::onGameStart(CCObject *sender)
{

	if (!isStart)
	{
		isStart = true;
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");

		CCDictionary *dic = CCDictionary::create();

		CCString *tmpChar;

		if (_playerSelect)
		{
			tmpChar = CCString::create(_playerSelect);
		}
		else
		{
			srand((int)time(0));
			int num2 = this->getSelectList()->count();
			int index = random(num2);
			tmpChar = (CCString *)_selectList->objectAtIndex(index);
			do
			{
				srand((int)time(0));
				int num = this->getSelectList()->count();
				int index = random(num);
				tmpChar = (CCString *)_selectList->objectAtIndex(index);
			} while (strcmp(tmpChar->getCString(), "Pain") == 0 ||
					 strcmp(tmpChar->getCString(), "Orochimaru") == 0 ||
					 strcmp(tmpChar->getCString(), "None") == 0);

			_playerSelect = tmpChar->getCString();
			_isRandomChar = true;
		}

		srand((int)time(0));
		int zhenying = 1;
		zhenying = random(2);

		const char *groupName;
		if (zhenying > 0)
		{
			groupName = Konoha;
		}
		else
		{
			groupName = Akatsuki;
		}

		CCString *tmpRole = CCString::create("Player");
		CCString *tmpGroup = CCString::create(groupName);

		dic->setObject(tmpChar, "character");
		dic->setObject(tmpRole, "role");
		dic->setObject(tmpGroup, "group");

		CCArray *tempHeros = CCArray::createWithObject(dic);

		CCArray *realHero = CCArray::create();

		for (int i = 0; i < heroNum; i++)
		{

			if (strcmp(_playerSelect, heroList[i]) == 0)
			{
				continue;
			}

			if (_com1Select)
			{
				if (strcmp(_com1Select, heroList[i]) == 0)
				{
					continue;
				}
			}
			if (_com2Select)
			{
				if (strcmp(_com2Select, heroList[i]) == 0)
				{
					continue;
				}
			}

			CCString *hero = CCString::create(heroList[i]);
			realHero->addObject(hero);
		}

		for (int i = 0; i < ComCount; i++)
		{
			CCString *hero;
			if (i < KonohaCount)
			{

				if (i == 0 && _isHardCoreMode && _com1Select)
				{
					hero = CCString::create(_com1Select);
				}
				else if (i == 1 && _isHardCoreMode && _com2Select)
				{
					hero = CCString::create(_com2Select);
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
					hero = (CCString *)tempObject;
					realHero->removeObjectAtIndex(index);
				}

				dic = CCDictionary::create();
				tmpChar = CCString::create(hero->getCString());
				tmpRole = CCString::create("Com");
				if (zhenying > 0)
				{
					tmpGroup = CCString::create(Konoha);
				}
				else
				{
					tmpGroup = CCString::create(Akatsuki);
				}
				dic->setObject(tmpChar, "character");
				dic->setObject(tmpRole, "role");
				dic->setObject(tmpGroup, "group");

				tempHeros->addObject(dic);
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
				if (zhenying > 0)
				{
					tmpGroup = CCString::create(Akatsuki);
				}
				else
				{
					tmpGroup = CCString::create(Konoha);
				}
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

		loadLayer->_isHardCoreMode = _isHardCoreMode;
		loadLayer->_isRandomChar = _isRandomChar;
		loadLayer->preloadAudio();
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, loadScene));
	}
}

void SelectLayer::keyBackClicked()
{
	SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/cancel.ogg");
	CCScene *menuScene = CCScene::create();
	CCLayer *menuLayer = StartMenu::create();
	menuScene->addChild(menuLayer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, menuScene));
}

SelectLayer *SelectLayer::create()
{

	SelectLayer *sl = new SelectLayer();
	if (sl && sl->init())
	{
		sl->autorelease();
		return sl;
	}
	else
	{
		delete sl;
		return NULL;
	}
}
