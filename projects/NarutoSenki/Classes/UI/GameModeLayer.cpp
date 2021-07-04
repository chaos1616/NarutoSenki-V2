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
    _menu_array = nullptr;
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

    // init menus
    setMenus(CCArray::createWithCapacity(kMenuCount));

    auto classic_mode_btn = ModeMenuButton::create("GameMode/01.png");
    classic_mode_btn->mode = GameMode::Classic;
    classic_mode_btn->setDelegate(this);
    _menu_array->addObject(classic_mode_btn);

    auto hardCore_mode_btn = ModeMenuButton::create("GameMode/04.png");
    hardCore_mode_btn->mode = GameMode::HardCore;
    hardCore_mode_btn->setDelegate(this);
    _menu_array->addObject(hardCore_mode_btn);

    auto notHardCore_mode_btn = ModeMenuButton::create("GameMode/02.png");
    notHardCore_mode_btn->mode = GameMode::NotHardCore;
    notHardCore_mode_btn->setDelegate(this);
    _menu_array->addObject(notHardCore_mode_btn);

    auto indev_mode_btn = ModeMenuButton::create("GameMode/03.png");
    indev_mode_btn->mode = GameMode::InDev;
    indev_mode_btn->setDelegate(this);
    _menu_array->addObject(indev_mode_btn);

    auto unknown_mode_btn = ModeMenuButton::create("GameMode/03.png");
    unknown_mode_btn->mode = GameMode::Unknown;
    unknown_mode_btn->setDelegate(this);
    _menu_array->addObject(unknown_mode_btn);

    // menuText = CCSprite::createWithSpriteFrameName("menu02_text.png");
    // menuText->setAnchorPoint(ccp(0, 0));
    // menuText->setPosition(ccp(10, 2));
    // addChild(menuText, 5);

    const int padding = -10;
    const int width = 100;
    const int offset = 50 + 50;
    float posY = winSize.height / 2;
    int i = 0;
    CCObject *pObject = nullptr;
    CCARRAY_FOREACH(_menu_array, pObject)
    {
        auto menu = (ModeMenuButton *)pObject;
        menu->setPositionX(winSize.width + offset);
        menu->setPositionY(posY + 30);
        addChild(menu, -i);
        // init animation
        auto delay = CCDelayTime::create(i * 0.3f);
        auto move = CCMoveTo::create(0.5f, ccp(i * (width + padding) + offset, posY + 30));
        auto action = CCSequence::createWithTwoActions(delay, move);
        menu->runAction(action);

        i++;
    }

    // init return button
    auto return_img = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("return_btn.png"), nullptr, nullptr, this, menu_selector(GameModeLayer::backToMenu));
    CCMenu *return_btn = CCMenu::create(return_img, nullptr);
    return_btn->setAnchorPoint(ccp(1, 0.5f));
    return_btn->setPosition(winSize.width - 38, 65);
    addChild(return_btn, 5);

    return CCLayer::init();
}

void GameModeLayer::backToMenu()
{
    SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/cancel.ogg");

    auto menuScene = CCScene::create();
    auto menuLayer = StartMenu::create();
    menuScene->addChild(menuLayer);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, menuScene));
}

bool GameModeLayer::pushMode(const GameModeData &data)
{
    return true;
}

void GameModeLayer::removeMode(const GameModeData &data)
{
}

void GameModeLayer::onEnterClassicMode()
{
    if (!setSelect())
        return;
}

void GameModeLayer::onEnterHardCoreMode()
{
    if (!setSelect())
        return;
}

void GameModeLayer::onEnterNotHardCoreMode()
{
    if (!setSelect())
        return;
}

void GameModeLayer::onEnterInDevMode()
{
}

void GameModeLayer::onEnterUnknownMode()
{
}
