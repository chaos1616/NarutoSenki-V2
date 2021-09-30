#include "GearLayer.h"
#include "GameLayer.h"
#include "HudLayer.h"
#include "Core/Hero.hpp"

/*----------------------
init GearButton ;
----------------------*/
GearButton::GearButton()
{
	soIcon = nullptr;
	_isBuyed = false;
}

GearButton::~GearButton()
{
}

bool GearButton::init(const char *szImage)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCSprite::init());
		if (strcmp(szImage, "") != 0)
			initWithSpriteFrameName(szImage);

		setAnchorPoint(ccp(0, 0));

		bRet = true;

	} while (0);

	return bRet;
}

void GearButton::onEnter()
{
	CCSprite::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, true);
}

void GearButton::onExit()
{
	CCSprite::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

CCRect GearButton::getRect()
{
	CCSize size = getContentSize();
	return CCRect(0, 0, size.width, size.height);
}

bool GearButton::containsTouchLocation(CCTouch *touch)
{
	return getRect().containsPoint(convertTouchToNodeSpace(touch));
}

void GearButton::setBtnType(gearType type, gearbtnType type2, bool isBuyed)
{
	_gearType = type;
	_btnType = type2;

	if (_btnType == 0)
	{
		CCSprite *gearIcon = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("gear_%02d.png", gearType(_gearType))->getCString());
		gearIcon->setAnchorPoint(ccp(0.5f, 0.5f));
		gearIcon->setPosition(ccp(20, 30));
		addChild(gearIcon);
	}
	else
	{
		CCSprite *gearIcon = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("gear_%02d.png", gearType(_gearType))->getCString());
		gearIcon->setAnchorPoint(ccp(0.5f, 0.5f));
		gearIcon->setScale(0.75f);
		addChild(gearIcon);
	}

	if (isBuyed)
	{
		_isBuyed = true;
		soIcon = CCSprite::createWithSpriteFrameName("gear_so.png");
		soIcon->setAnchorPoint(ccp(0.5f, 0.5f));
		soIcon->setPosition(ccp(getContentSize().width / 2, getContentSize().height / 2));
		addChild(soIcon);
	}
}

gearType GearButton::getBtnType()
{
	return _gearType;
}

void GearButton::click()
{
	if (_delegate->currentGear != _gearType && CCUserDefault::sharedUserDefault()->getBoolForKey("isVoice"))
	{
		SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/select.ogg");
	}

	if (!_isBuyed)
	{
		_delegate->currentGear = _gearType;
	}

	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("gearDetail_%02d.png", gearType(_gearType))->getCString());
	_delegate->gearDetail->setDisplayFrame(frame);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	CCSpriteFrame *icon = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("gear_%02d.png", gearType(_gearType))->getCString());
	_delegate->gearDetailIcon->setDisplayFrame(icon);
#endif
}

bool GearButton::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	// touch area
	if (!containsTouchLocation(touch) || soIcon)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void GearButton::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
	// touch area
}

void GearButton::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
	click();
}

void GearButton::playSound()
{
}

GearButton *GearButton::create(const char *szImage)
{
	GearButton *mb = new GearButton();
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

ScrewLayer::ScrewLayer()
{
	_delegate = nullptr;
	_gearArray = nullptr;
}

ScrewLayer::~ScrewLayer()
{
}

bool ScrewLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		bRet = true;

	} while (0);

	return bRet;
}

void ScrewLayer::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void ScrewLayer::onExit()
{
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool ScrewLayer::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	prePosY = 0;
	return true;
}

void ScrewLayer::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
	// touch area
	CCPoint curPoint = touch->getLocation();
	if (prePosY == 0)
	{
		prePosY = curPoint.y;
	}
	else
	{
		float distanceY = curPoint.y - prePosY;
		if (getPositionY() < totalRow * 74 || distanceY < 0)
		{
			setPositionY(getPositionY() + distanceY);
		}
		if ((screwBar->getPositionY() > 90 || distanceY < 0) && screwBar->getPositionY() <= 122)
		{
			screwBar->setPositionY(screwBar->getPositionY() - distanceY);
		}

		if (screwBar->getPositionY() > 122)
		{
			screwBar->setPositionY(122);
		}

		if (screwBar->getPositionY() < 90)
		{
			screwBar->setPositionY(90);
		}

		prePosY = curPoint.y;
	}
};

void ScrewLayer::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
	prePosY = 0;
	//CCLOG("%f",getPositionY());
	//CCLOG("Height:%f",getContentSize().height);

	if (getPositionY() > totalRow * 74 - 74)
	{
		setPositionY(totalRow * 65);
	}
	if (getPositionY() < 76)
	{
		setPositionY(76);
	}

	if (screwBar->getPositionY() > 122)
	{
		screwBar->setPositionY(122);
	}

	if (screwBar->getPositionY() < 90)
	{
		screwBar->setPositionY(90);
	}
}

GearLayer::GearLayer()
{
	currentGear_layer = nullptr;
	currentGear = None;
}

GearLayer::~GearLayer()
{
	_delegate->_isGear = false;
}

bool GearLayer::init(CCRenderTexture *snapshoot)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		SimpleAudioEngine::sharedEngine()->stopAllEffects();

		CCTexture2D *bgTexture = snapshoot->getSprite()->getTexture();
		CCSprite *bg = CCSprite::createWithTexture(bgTexture);
		bg->setAnchorPoint(ccp(0, 0));
		bg->setFlipY(true);
		addChild(bg, 0);

		CCLayer *blend = CCLayerColor::create(ccc4(0, 0, 0, 150), winSize.width, winSize.height);
		addChild(blend, 1);

		CCLayer *gears_layer = CCLayer::create();

		gears_bg = CCSprite::createWithSpriteFrameName("gears_bg.png");
		gears_bg->setAnchorPoint(ccp(0.5f, 0.5f));
		gears_bg->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 12));
		gears_layer->addChild(gears_bg, 1);

		coinLabel = CCLabelBMFont::create("0", "Fonts/arial.fnt");
		coinLabel->setAnchorPoint(ccp(0, 0));
		coinLabel->setPosition(ccp(gears_bg->getPositionX() + 2, 58));
		gears_layer->addChild(coinLabel, 2);

		addChild(gears_layer, 10);

		CCClippingNode *clipper = CCClippingNode::create();
		CCNode *stencil = CCSprite::createWithSpriteFrameName("screwMask.png");
		stencil->setAnchorPoint(ccp(0, 0));
		clipper->setStencil(stencil);

		_screwLayer = ScrewLayer::create();
		_screwLayer->setAnchorPoint(ccp(0, 0));
		_screwLayer->setPositionY(76);
		_screwLayer->gearNum = 9;

		_screwLayer->screwBar = CCSprite::createWithSpriteFrameName("screwBar.png");
		_screwLayer->screwBar->setAnchorPoint(ccp(0.5f, 0));
		_screwLayer->screwBar->setPosition(ccp(gears_bg->getPositionX() + 25, 126));
		addChild(_screwLayer->screwBar, 600);

		gearDetail = CCSprite::createWithSpriteFrameName("gearDetail_00.png");
		gearDetail->setAnchorPoint(ccp(0.5f, 1));
		gearDetail->setPosition(ccp(gears_bg->getPositionX() + gears_bg->getContentSize().width / 2 - 54, 210));
		addChild(gearDetail, 600);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		gearDetailIcon = CCSprite::createWithSpriteFrameName("gear_00.png");
		gearDetailIcon->setAnchorPoint(ccp(0.5f, 0));
		gearDetailIcon->setPosition(ccp(gears_bg->getPositionX() + gears_bg->getContentSize().width / 2 - 54, 90));
		addChild(gearDetailIcon, 600);
#endif

		CCMenuItem *buy_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("gearBuy_btn.png"),
													   CCSprite::createWithSpriteFrameName("gearBuy_btn2.png"), this, menu_selector(GearLayer::onGearBuy));
		CCMenu *gearMenu = CCMenu::create(buy_btn, nullptr);
		gearMenu->setPosition(ccp(gears_bg->getPositionX() + 78, 65));
		addChild(gearMenu, 600);
		clipper->setPosition(ccp(gears_bg->getPositionX() - gears_bg->getContentSize().width / 2 + 4, 85));
		clipper->addChild(_screwLayer);
		addChild(clipper, 600);

		CCMenuItem *btm_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("close_btn1.png"),
													   CCSprite::createWithSpriteFrameName("close_btn2.png"), this, menu_selector(GearLayer::onResume));
		CCMenu *overMenu = CCMenu::create(btm_btn, nullptr);
		overMenu->setPosition(ccp(winSize.width / 2 + gears_bg->getContentSize().width / 2 - 12, winSize.height / 2 + gears_bg->getContentSize().height / 2 - 20));
		addChild(overMenu, 600);

		bRet = true;
	} while (0);

	return bRet;
}

void GearLayer::confirmPurchase()
{
	// this function for keyboard buy event
	onGearBuy(nullptr);
	// refresh HUB
	getDelegate()->getHudLayer()->updateGears();
}

void GearLayer::onResume(CCObject *sender)
{
	getDelegate()->getHudLayer()->updateGears();
	CCDirector::sharedDirector()->popScene();

	_delegate->_isGear = false;
}

void GearLayer::onGearBuy(CCObject *sender)
{
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isVoice"))
	{
		SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");
	}

	if (_delegate->currentPlayer->setGear(currentGear))
	{
		updatePlayerGear();
	}
}

void GearLayer::updatePlayerGear()
{
	if (_delegate->currentPlayer->getGearArray() && _delegate->currentPlayer->getGearArray()->count() > 0)
	{
		if (currentGear_layer != nullptr)
		{
			currentGear_layer->removeFromParentAndCleanup(true);
		}
		currentGear_layer = CCLayer::create();
		currentGear_layer->setAnchorPoint(ccp(0, 0));
		CCObject *pObject;
		int i = 0;
		CCARRAY_FOREACH(_delegate->currentPlayer->getGearArray(), pObject)
		{
			CCString *tmpGear = (CCString *)pObject;
			GearButton *btn = GearButton::create("");
			btn->setBtnType(gearType(to_int(tmpGear->getCString())), gearbtnType(1), false);
			btn->setPositionX(13 + i * 34);
			btn->setDelegate(this);
			currentGear_layer->addChild(btn);
			i++;
		}
		currentGear_layer->setPosition(ccp(gears_bg->getPositionX() - gears_bg->getContentSize().width / 2 + 8, 64));
		addChild(currentGear_layer, 800);
	}

	coinLabel->setString(to_ccstring(_delegate->currentPlayer->getCoinValue())->getCString());
	updateGearList();
}

void GearLayer::updateGearList()
{
	if (!_screwLayer->getGearArray())
	{
		_screwLayer->setGearArray(CCArray::create());
	}
	else
	{
		CCObject *pObject;
		CCARRAY_FOREACH(_screwLayer->getGearArray(), pObject)
		{
			GearButton *btn = (GearButton *)pObject;
			btn->removeFromParentAndCleanup(true);
		}
	}
	currentGear = None;
	_screwLayer->totalRow = 3;
	for (int i = 0; i < _screwLayer->gearNum; i++)
	{
		int row = int(floor(float(i) / 3));
		int column = abs(3 * row - i);

		GearButton *btn;
		if (column >= 1)
		{
			btn = GearButton::create("value_1000.png");
		}
		else
		{
			btn = GearButton::create("value_500.png");
		}
		bool isBuyed = false;
		if (_delegate->currentPlayer->getGearArray() && _delegate->currentPlayer->getGearArray()->count() > 0)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(_delegate->currentPlayer->getGearArray(), pObject)
			{
				CCString *tmpGear = (CCString *)pObject;
				if (to_int(tmpGear->getCString()) == i)
				{
					isBuyed = true;
				}
			}
		}

		if (currentGear == None && !isBuyed)
		{
			currentGear = gearType(i);
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("gearDetail_%02d.png", i)->getCString());
			gearDetail->setDisplayFrame(frame);
		}

		btn->setPosition(ccp(6 + column * 46, -row * 60));
		btn->setAnchorPoint(ccp(0, 0));
		btn->setBtnType(gearType(i), gearbtnType(0), isBuyed);
		btn->setDelegate(this);
		_screwLayer->getGearArray()->addObject(btn);
		_screwLayer->addChild(btn);
	}
}

GearLayer *GearLayer::create(CCRenderTexture *snapshoot)
{
	GearLayer *grl = new GearLayer();
	if (grl && grl->init(snapshoot))
	{
		grl->autorelease();
		return grl;
	}
	else
	{
		delete grl;
		return nullptr;
	}
}
