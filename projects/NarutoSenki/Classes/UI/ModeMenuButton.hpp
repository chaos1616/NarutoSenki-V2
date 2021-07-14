#pragma once
#include "UI/GameModeLayer.h"

class ModeMenuButton : public CCSprite, public CCTouchDelegate
{
private:
	CCSprite *lockMask;

public:
	CC_SYNTHESIZE(GameModeLayer *, _gameModeLayer, Delegate);

	GameMode mode;

	ModeMenuButton()
	{
		lockMask = nullptr;
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
		_gameModeLayer->selectMode(mode);
	}

	void lock()
	{
		if (lockMask == nullptr)
		{
			lockMask = CCSprite::create("GameMode/chain_mask.png");
			lockMask->setPosition(getPosition());
			_gameModeLayer->addChild(lockMask, 1000);
		}
	}

	void unlock()
	{
		if (lockMask)
		{
			_gameModeLayer->removeChild(lockMask, true);
			lockMask = nullptr;
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
