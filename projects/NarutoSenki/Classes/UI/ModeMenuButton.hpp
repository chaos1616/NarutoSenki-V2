#pragma once
#include "UI/GameModeLayer.h"

class ModeMenuButton : public CCSprite, public CCTouchDelegate
{
public:
    CC_SYNTHESIZE(GameModeLayer *, _gameModeLayer, Delegate);

    u8 mode;

    ModeMenuButton()
    {
    }

    ~ModeMenuButton()
    {
    }

    bool init(const char *szImage)
    {
        bool bRet = false;
        do
        {
            CC_BREAK_IF(!CCSprite::initWithFile(szImage));
            // initWithSpriteFrameName(szImage);
            setAnchorPoint(ccp(0.5, 0.5));

            bRet = true;
        } while (0);

        return bRet;
    }

    void onEnter()
    {
        CCSprite::onEnter();
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10, true);
    }

    void onExit()
    {
        CCSprite::onExit();
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    }

    CCRect getRect()
    {
        CCSize size = getContentSize();
        return CCRect(0, 0, size.width, size.height);
    }

    bool ccTouchBegan(CCTouch *touch, CCEvent *event)
    {
        return getRect().containsPoint(convertTouchToNodeSpace(touch));
    }

    void ccTouchEnded(CCTouch *touch, CCEvent *event)
    {
        SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");

        switch (mode)
        {
        case GameMode::Classic:
            _gameModeLayer->onEnterClassicMode();
            break;
        case GameMode::HardCore:
            _gameModeLayer->onEnterHardCoreMode();
            break;
        case GameMode::NotHardCore:
            _gameModeLayer->onEnterNotHardCoreMode();
            break;
        case GameMode::InDev:
            _gameModeLayer->onEnterInDevMode();
            break;
        case GameMode::Unknown:
            _gameModeLayer->onEnterUnknownMode();
            break;
        }
    }

    static ModeMenuButton *create(const char *szImage)
    {
        ModeMenuButton *mb = new ModeMenuButton();
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
};
