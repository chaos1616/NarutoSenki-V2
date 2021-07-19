#include "StartMenu.h"
#include "UI/GameModeLayer.h"
#include "UI/ModeMenuButton.hpp"

// const GameModeData &GameModeData::from(const char *path)
// {
//     GameModeData data = {}
//     return data;
// }

GameModeLayer::GameModeLayer()
{
}

GameModeLayer::~GameModeLayer()
{
}

bool GameModeLayer::init()
{
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	auto bgSprite = CCSprite::create("red_bg.png");
	FULL_SCREEN_SPRITE(bgSprite);
	bgSprite->setAnchorPoint(ccp(0, 0));
	bgSprite->setPosition(ccp(0, 0));
	addChild(bgSprite, -100);

	// menu bars
	auto menu_bar_b = CCSprite::create("menu_bar2.png");
	menu_bar_b->setAnchorPoint(ccp(0, 0));
	FULL_SCREEN_SPRITE(menu_bar_b);
	addChild(menu_bar_b, 2);

	auto menu_bar_t = CCSprite::create("menu_bar3.png");
	menu_bar_t->setAnchorPoint(ccp(0, 0));
	menu_bar_t->setPosition(ccp(0, winSize.height - menu_bar_t->getContentSize().height));
	FULL_SCREEN_SPRITE(menu_bar_t);
	addChild(menu_bar_t, 2);

	auto modemenu_title = CCSprite::createWithSpriteFrameName("startmenu_title.png");
	modemenu_title->setAnchorPoint(ccp(0, 0));
	modemenu_title->setPosition(ccp(2, winSize.height - modemenu_title->getContentSize().height - 2));
	addChild(modemenu_title, 3);

	initModeData();

	// init menus
	const int padding = -10;
	const int width = 100;
	const int offset = (winSize.width - 460) / 2 + 100 / 2;
	const float posY = (winSize.height / 2) + 30;
	for (int i = 0; i < 3; i++)
	{
		auto mode_btn = ModeMenuButton::create(CCString::createWithFormat("GameMode/%d.png", i + 1)->getCString());
		mode_btn->mode = (GameMode)i;
		mode_btn->setDelegate(this);
		mode_btn->setPositionX(offset);
		mode_btn->setPositionY((posY + 55 + 7.5f) - i * (55 + 7.5f));
		menuButtons[i] = mode_btn;
		addChild(mode_btn);
	}
	for (int i = 3; i < 6; i++)
	{
		auto mode_btn = ModeMenuButton::create(CCString::createWithFormat("GameMode/%d.png", i + 1)->getCString());
		mode_btn->mode = (GameMode)i;
		mode_btn->setDelegate(this);
		mode_btn->setPositionX(offset + 10 + (i - 2) * (80 + 5));
		mode_btn->setPositionY(posY);
		menuButtons[i] = mode_btn;
		addChild(mode_btn);
		// init animation
		// auto delay = CCDelayTime::create(i * 0.3f);
		// auto move = CCMoveTo::create(0.5f, ccp((i - 1) * (width + padding) + offset, posY + 30));
		// auto action = CCSequence::createWithTwoActions(delay, move);
		// mode_btn->runAction(action);
	}
	for (int i = 6; i < GameMode::_Internal_Max_Length; i++)
	{
		auto mode_btn = ModeMenuButton::create(CCString::createWithFormat("GameMode/%d.png", i + 1)->getCString());
		mode_btn->mode = (GameMode)i;
		mode_btn->setDelegate(this);
		mode_btn->setPositionX(offset + 20 + (80 + 5) * 4);
		mode_btn->setPositionY((posY + 47) - (i - 6) * (86 + 8.0f));
		menuButtons[i] = mode_btn;
		addChild(mode_btn);
	}

	for (size_t i = 0; i < menuButtons.size(); i++)
	{
		if (modes[i].isLocked)
		{
			menuButtons.at(i)->useMask2 = modes.at(i).useMask2;
			menuButtons.at(i)->lock();
		}
	}

	menuLabel = CCLabelTTF::create();
	menuLabel->setAnchorPoint(ccp(0, 0));
	menuLabel->setPosition(ccp(10, 1));
	addChild(menuLabel, 5);

	// init return button
	auto return_img = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("return_btn.png"), nullptr, nullptr, this, menu_selector(GameModeLayer::backToMenu));
	CCMenu *return_btn = CCMenu::create(return_img, nullptr);
	return_btn->setAnchorPoint(ccp(1, 0.5f));
	return_btn->setPosition(winSize.width - 38, 65);
	addChild(return_btn, 5);

	return CCLayer::init();
}

void GameModeLayer::backToMenu(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/cancel.ogg");

	auto menuScene = CCScene::create();
	auto menuLayer = StartMenu::create();
	menuScene->addChild(menuLayer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, menuScene));
}

void GameModeLayer::initModeData()
{
	// init mode text data
	auto lang = CCApplication::sharedApplication()->getCurrentLanguage();
	if (lang == LanguageType::kLanguageChinese)
	{
		modes[GameMode::OneVsOne] = {"1 VS 1", ""};
		modes[GameMode::Classic] = {"3 VS 3", "经典模式"};
		modes[GameMode::FourVsFour] = {"4 VS 4", ""};
		modes[GameMode::HardCore_4Vs4] = {"硬核模式 (4 VS 4)", "禁用装备"};
		modes[GameMode::Boss] = {"Boss模式 (3 VS 1)", ""};
		modes[GameMode::Clone] = {"克隆模式 (3 VS 3)", ""};
		modes[GameMode::Deathmatch] = {"死亡竞赛 (3 VS 3)", ""};
		modes[GameMode::RandomDeathmatch] = {"随机死亡竞赛 (3 VS 3)", ""};
	}
	else if (lang == LanguageType::kLanguageJapanese)
	{
		modes[GameMode::OneVsOne] = {"1 VS 1", ""};
		modes[GameMode::Classic] = {"3 VS 3", "Classic Mode"};
		modes[GameMode::FourVsFour] = {"4 VS 4", ""};
		modes[GameMode::HardCore_4Vs4] = {"HardCore (4 VS 4)", "Disabled gear"};
		modes[GameMode::Boss] = {"Boss (3 VS 3)", ""};
		modes[GameMode::Clone] = {"Clone (3 VS 3)", ""};
		modes[GameMode::Deathmatch] = {"Deathmatch (3 VS 3)", ""};
		modes[GameMode::RandomDeathmatch] = {"Random Deathmatch (3 VS 3)", ""};
	}
	else // English
	{
		modes[GameMode::OneVsOne] = {"1 VS 1", ""};
		modes[GameMode::Classic] = {"3 VS 3", "Classic Mode"};
		modes[GameMode::FourVsFour] = {"4 VS 4", ""};
		modes[GameMode::HardCore_4Vs4] = {"HardCore (4 VS 4)", "Disabled gear"};
		modes[GameMode::Boss] = {"Boss (3 VS 3)", ""};
		modes[GameMode::Clone] = {"Clone (3 VS 3)", ""};
		modes[GameMode::Deathmatch] = {"Deathmatch (3 VS 3)", ""};
		modes[GameMode::RandomDeathmatch] = {"Random Deathmatch (3 VS 3)", ""};
	}

	// init in developtment game modes
	modes[GameMode::Boss].isLocked = true;
	modes[GameMode::Deathmatch].isLocked = true;
	modes[GameMode::Deathmatch].useMask2 = true;

	// init mode handlers
	for (size_t i = 0; i < GameMode::_Internal_Max_Length; i++)
	{
		auto &data = modes.at(i);
		if (data.isLocked)
			data.description += " (In developtment)";
		// data.handler = s_ModeHandlers[i];
	}
}

bool GameModeLayer::pushMode(const GameModeData &data)
{
	return true;
}

void GameModeLayer::removeMode(const GameModeData &data)
{
}

void GameModeLayer::selectMode(GameMode mode)
{
	auto data = modes[(size_t)mode];
	std::string label = data.title;
	if (data.description.size() > 0)
	{
		label += " | ";
		label += data.description;
	}
	menuLabel->setString(label.c_str());

	if (setSelect(mode))
	{
		CCLOG("Selected %s mode", data.title.c_str());
		s_GameMode = mode;
		getGameModeHandler()->init();

		bool enableCustomSelect = false; // TODO: Enable custom select mode
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
			auto selectLayer = SelectLayer::create();
			selectScene->addChild(selectLayer);

			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, selectScene));
			CCLOG("GameModeLayer lua handler can not be null");
		}
	}
}

bool GameModeLayer::setSelect(GameMode mode)
{
	auto &data = modes.at(mode);
	if (!data.isLocked && data.hasSelected)
		return true;

	for (size_t i = 0; i < modes.size(); i++)
		modes.at(i).hasSelected = false;
	data.hasSelected = true;
	return false;
}
