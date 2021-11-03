#include "Core/Hero.hpp"
#include "GameLayer.h"
#include "HudLayer.h"
#include "MyUtils/CCShake.h"

MiniIcon::MiniIcon()
{
}

MiniIcon::~MiniIcon()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "updateMap");
}

bool MiniIcon::init(const char *szImage, bool isNotification)
{
	RETURN_FALSE_IF(!CCSprite::init());

	initWithSpriteFrameName(szImage);

	if (isNotification)
	{
		setAnchorPoint(ccp(0.5f, 0));
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(MiniIcon::updateMap), "updateMap", nullptr);
	}
	else
	{
		setAnchorPoint(ccp(0.5f, 0.5f));
	}

	return true;
}

void MiniIcon::updateMap(CCObject *sender)
{
	auto poster = (CharacterBase *)sender;

	if (getCharId() == poster->getCharId())
	{
		if (poster->getActionState() == State::DEAD || poster->_isVisable == false)
		{
			setVisible(false);
		}
		else
		{
			setVisible(true);
			updatePosition(poster->getPosition());
		}
	}
}

void MiniIcon::updateState()
{
	auto frame = getSpriteFrame("tower_icon3.png");
	setDisplayFrame(frame);
}

void MiniIcon::updatePosition(CCPoint location)
{
	int x = floor(location.x / 32);
	int y = floor(location.y / 32) * 5;

	setPosition(ccp(x, y));
	getGameLayer()->reorderChild(this, 500);
}

MiniIcon *MiniIcon::create(const char *szImage, bool isNotification)
{
	MiniIcon *mi = new MiniIcon();
	if (mi && mi->init(szImage, isNotification))
	{
		mi->autorelease();
		return mi;
	}
	else
	{
		delete mi;
		return nullptr;
	}
}

HudLayer::HudLayer()
{
	_joyStick = nullptr;

	reportSPCSprite = nullptr;

	_isAllButtonLocked = false;

	skill4Button = nullptr;
	skill5Button = nullptr;
	ougisLayer = nullptr;

	gear1Button = nullptr;
	gear2Button = nullptr;
	gear3Button = nullptr;
	gearMenu = nullptr;

	item1Button = nullptr;
	item2Button = nullptr;
	item3Button = nullptr;
	item4Button = nullptr;
	openingSprite = nullptr;

	bcdLabel1 = nullptr;
	bcdLabel2 = nullptr;
}

HudLayer::~HudLayer()
{
}

void HudLayer::onEnter()
{
	if (getGameLayer()->_isExiting)
	{
		return;
	}
	CCLayer::onEnter();
}

void HudLayer::onExit()
{
	CCLayer::onExit();
	if (getGameLayer()->_isExiting)
	{
		_reportListArray.clear();
		_towerIconArray.clear();
	}
}

bool HudLayer::init()
{
	RETURN_FALSE_IF(!CCLayer::init());

	texUI = CCTextureCache::sharedTextureCache()->addImage("UI.png");
	// TODO: Remove batch node when upgrading to cocos2d-x V4
	uiBatch = CCSpriteBatchNode::createWithTexture(texUI);
	addChild(uiBatch);

	return true;
}

void HudLayer::JoyStickRelease()
{
	getGameLayer()->JoyStickRelease();
}

void HudLayer::JoyStickUpdate(CCPoint direction)
{
	getGameLayer()->JoyStickUpdate(direction);
}

void HudLayer::initGearButton(const string &charName)
{
	gearMenuSprite = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(format("{}_avator.png", charName).c_str()), nullptr, nullptr, this, menu_selector(HudLayer::gearButtonClick));
	if (gearMenuSprite == nullptr)
	{
		CCLOGERROR("Not found %s avator sprite", charName.c_str());
		return;
	}

	if (gearMenu)
		gearMenu->removeFromParent();
	gearMenuSprite->setAnchorPoint(ccp(0, 0));
	gearMenu = CCMenu::create(gearMenuSprite, nullptr);
	gearMenu->setPosition(ccp(0, winSize.height - gearMenuSprite->getContentSize().height));
	gearMenu->setTouchPriority(10);
	addChild(gearMenu, 100);
}

void HudLayer::playGameOpeningAnimation()
{
	auto tempArray = CCArray::create();

	int i = 1;
	while (i < ComCount)
	{
		auto frame = getSpriteFrame("gameStart_00{}.png", i);
		tempArray->addObject(frame);
		i += 1;
	}

	auto tempAnimation = CCAnimation::createWithSpriteFrames(tempArray, 0.1f);
	auto tempAction = CCAnimate::create(tempAnimation);

	openingSprite = CCSprite::createWithSpriteFrameName("gameStart_001.png");
	openingSprite->setPosition(ccp(winSize.width / 2 + 32, winSize.height / 2));
	addChild(openingSprite, 5000);
	openingSprite->runAction(tempAction);
}

void HudLayer::initHeroInterface()
{
	auto winWidth = winSize.width;
	auto winHeight = winSize.height;
	float mScaleX = 1.0f;
	float mScaleY = 1.0f;

#if DEBUG || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	mScaleX = winWidth / 570;
	mScaleY = winHeight / 320;
	// init the joyStick
	_joyStick = JoyStick::create();
	// set relative position in large screen and small screen
	_joyStick->setPosition(ccp(mScaleX * 28, mScaleY * 16));
	_joyStick->setDelegate(this);
	uiBatch->addChild(_joyStick);
#endif

	// produce status bar
	status_bar = CCSprite::createWithSpriteFrameName("status_bar_bg.png");
	status_bar->setAnchorPoint(ccp(0, 0));
	status_bar->setPosition(ccp(0, winHeight - status_bar->getContentSize().height));
	uiBatch->addChild(status_bar);

	status_hpbar = CCSprite::createWithSpriteFrameName("status_hpbar.png");
	status_hpbar->setPosition(ccp(53, winHeight - 54));
	addChild(status_hpbar, 40);

	status_hpMark = CCSprite::createWithSpriteFrameName("status_hpMark.png");
	status_hpMark->setAnchorPoint(ccp(0, 0));
	status_hpMark->setPosition(ccp(54, winHeight - 105));
	addChild(status_hpMark, 45);

	CCSprite *tmpSprite = CCSprite::createWithSpriteFrameName("status_ckrbar.png");
	status_expbar = CCProgressTimer::create(tmpSprite);
	status_expbar->setType(kCCProgressTimerTypeRadial);
	status_expbar->setPercentage(0);
	status_expbar->setReverseDirection(true);
	status_expbar->setPosition(ccp(54, winHeight - 54));
	addChild(status_expbar, 50);
	CCMenuItem *menu_button = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("minimap_bg.png"), nullptr, nullptr, this, menu_selector(HudLayer::pauseButtonClick));
	menu_button->setAnchorPoint(ccp(1, 1));
	pauseNenu = CCMenu::create(menu_button, nullptr);
	pauseNenu->setPosition(ccp(winWidth, winHeight));
	addChild(pauseNenu);

	CCSprite *killIcon = CCSprite::createWithSpriteFrameName("kill_icon.png");
	killIcon->setAnchorPoint(ccp(0, 1));
	killIcon->setPosition(ccp(winWidth - 114, winHeight - 46));
	addChild(killIcon, 5000);

	killLabel = CCLabelBMFont::create("0", "Fonts/1.fnt");
	killLabel->setScale(0.26f);
	killLabel->setAnchorPoint(ccp(0, 1));
	killLabel->setPosition(ccp(killIcon->getPositionX() + killIcon->getContentSize().width / 2 + 5, winHeight - 56));
	addChild(killLabel, 5001);

	CCSprite *deadIcon = CCSprite::createWithSpriteFrameName("dead_icon.png");
	deadIcon->setAnchorPoint(ccp(0, 1));
	deadIcon->setPosition(ccp(winWidth - 114 + 26, winHeight - 47));
	addChild(deadIcon, 5000);

	deadLabel = CCLabelBMFont::create("0", "Fonts/1.fnt");
	deadLabel->setScale(0.26f);
	deadLabel->setAnchorPoint(ccp(0, 1));
	deadLabel->setPosition(ccp(deadIcon->getPositionX() + deadIcon->getContentSize().width / 2 + 5, winHeight - 56));
	addChild(deadLabel, 5001);

	KonoLabel = CCLabelBMFont::create("0", "Fonts/blue.fnt");
	KonoLabel->setScale(0.35f);

	AkaLabel = CCLabelBMFont::create("0", "Fonts/red.fnt");
	AkaLabel->setScale(0.35f);

	if (getGameLayer()->playerGroup == Group::Konoha)
	{
		KonoLabel->setAnchorPoint(ccp(1, 1));
		AkaLabel->setAnchorPoint(ccp(0, 1));
		KonoLabel->setPosition(ccp(winWidth - 42, winHeight - 46));
		AkaLabel->setPosition(ccp(winWidth - 32, winHeight - 46));
	}
	else
	{
		AkaLabel->setAnchorPoint(ccp(1, 1));
		KonoLabel->setAnchorPoint(ccp(0, 1));
		AkaLabel->setPosition(ccp(winWidth - 42, winHeight - 46));
		KonoLabel->setPosition(ccp(winWidth - 32, winHeight - 46));
	}

	addChild(KonoLabel, 5000);
	addChild(AkaLabel, 5000);
	auto hengLabel = CCLabelBMFont::create(":", "Fonts/1.fnt");
	hengLabel->setScale(0.5f);
	hengLabel->setAnchorPoint(ccp(0.5f, 1));
	hengLabel->setPosition(ccp(winWidth - 37, KonoLabel->getPositionY() + 2));
	addChild(hengLabel, 5000);

	auto currentPlayer = getGameLayer()->currentPlayer;
	auto currCharName = currentPlayer->getName();
	initGearButton(currCharName);

	hpLabel = CCLabelBMFont::create(currentPlayer->getHP_Value().asString().c_str(), "Fonts/1.fnt");
	hpLabel->setScale(0.35f);
	hpLabel->setPosition(ccp(0, winHeight - 54));
	hpLabel->setAnchorPoint(ccp(0, 0));

	addChild(hpLabel, 5000);

	int exp = currentPlayer->getEXP() - ((currentPlayer->getLV() - 1) * 500) / 500;
	expLabel = CCLabelBMFont::create(format("{}%", exp).c_str(), "Fonts/1.fnt");
	expLabel->setScale(0.35f);
	expLabel->setPosition(ccp(94, winHeight - 54));
	expLabel->setAnchorPoint(ccp(0.5f, 0));

	addChild(expLabel, 5000);

	gameClock = CCLabelBMFont::create("00:00", "Fonts/1.fnt");
	gameClock->setAnchorPoint(ccp(0.5f, 0));
	gameClock->setScale(0.4f);
	gameClock->setPosition(ccp(mScaleX * 25, 0));
	addChild(gameClock, 5000);

	coinLabel = CCLabelBMFont::create(currentPlayer->getCoin_Value().asString().c_str(), "Fonts/arial.fnt");
	coinLabel->setAnchorPoint(ccp(0, 0));
	coinLabel->setPosition(ccp(121, winHeight - 61));

	addChild(coinLabel, 5000);

	// init NATTACK Button
	nAttackButton = ActionButton::create("n_attack.png");
	nAttackButton->setDelegate(this);
	nAttackButton->setABType(NAttack);
	uiBatch->addChild(nAttackButton);

	// init SKIll Button

	skill1Button = ActionButton::create(currCharName + "_skill1.png");
	skill1Button->setDelegate(this);
	skill1Button->setABType(SKILL1);
	uiBatch->addChild(skill1Button);

	skill2Button = ActionButton::create(currCharName + "_skill2.png");
	skill2Button->setDelegate(this);
	skill2Button->setABType(SKILL2);
	uiBatch->addChild(skill2Button);

	skill3Button = ActionButton::create(currCharName + "_skill3.png");
	skill3Button->setDelegate(this);
	skill3Button->setABType(SKILL3);
	uiBatch->addChild(skill3Button);

	skill4Button = ActionButton::create(currCharName + "_skill4.png");
	skill4Button->setDelegate(this);
	skill4Button->setABType(OUGIS1);
	uiBatch->addChild(skill4Button);

	skill5Button = ActionButton::create(currCharName + "_skill5.png");
	skill5Button->setDelegate(this);
	skill5Button->setABType(OUGIS2);
	uiBatch->addChild(skill5Button);

	// init Item
	item1Button = ActionButton::create("item1.png");
	if (getGameLayer()->_isHardCoreGame)
	{
		item1Button->setCD(5000);
	}
	else
	{
		item1Button->setCD(3000);
	}

	item1Button->setDelegate(this);
	item1Button->setABType(Item1);
	item1Button->_cost = "50";
	uiBatch->addChild(item1Button);

	// init Item
	item2Button = ActionButton::create("item2.png");
	item2Button->setCD(15000);
	item2Button->setDelegate(this);
	item2Button->setABType(GearItem);
	item2Button->_gearType = None;
	item2Button->_isLock = true;
	uiBatch->addChild(item2Button);
	item2Button->setVisible(false);

	item3Button = ActionButton::create("item3.png");
	item3Button->setCD(15000);
	item3Button->setDelegate(this);
	item3Button->setABType(GearItem);
	item3Button->_gearType = None;
	item3Button->_isLock = true;
	uiBatch->addChild(item3Button);
	item3Button->setVisible(false);

	item4Button = ActionButton::create("item4.png");
	item4Button->setCD(15000);
	item4Button->setDelegate(this);
	item4Button->setABType(GearItem);
	item4Button->_gearType = None;
	item4Button->_isLock = true;
	uiBatch->addChild(item4Button);
	item4Button->setVisible(false);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	nAttackButton->setPosition(ccp(winWidth - 60, 8));
	skill1Button->setPosition(ccp(winWidth - skill1Button->getContentSize().width - 64, 2));
	skill2Button->setPosition(ccp(winWidth - 95, 50));
	skill3Button->setPosition(ccp(winWidth - 44, 8 + nAttackButton->getContentSize().height + 8));
	skill4Button->setPosition(ccp(skill1Button->getPositionX() - skill4Button->getContentSize().width - 8, 2));
	skill5Button->setPosition(ccp(skill4Button->getPositionX() - skill5Button->getContentSize().width - 8, 2));

	item1Button->setPosition(ccp(8, skill3Button->getPositionY() + skill3Button->getContentSize().height));
	item2Button->setPosition(ccp(winWidth - 44, skill3Button->getPositionY() + skill3Button->getContentSize().height + 8));
	if (skill5Button)
		item3Button->setPosition(ccp(skill5Button->getPositionX() - skill5Button->getContentSize().width - 8, 2));
	else if (skill4Button)
		item3Button->setPosition(ccp(skill4Button->getPositionX() - skill4Button->getContentSize().width - 8, 2));
	else
		item3Button->setPosition(ccp(skill1Button->getPositionX() - skill1Button->getContentSize().width - 8, 2));
	item4Button->setPosition(ccp(skill2Button->getPositionX() - skill2Button->getContentSize().width - 8, skill2Button->getPositionY()));
#else
	float width = skill1Button->getContentSize().width;

	nAttackButton->setPosition(ccp(winWidth + 100, -100));

	skill1Button->setPosition(ccp(winWidth / 2 - (width + 8) * 2, 2));
	skill1Button->setScale(DESKTOP_UI_SCALE);
	skill2Button->setPosition(ccp(winWidth / 2 - width - 8, 2));
	skill2Button->setScale(DESKTOP_UI_SCALE);
	skill3Button->setPosition(ccp(winWidth / 2, 2));
	skill3Button->setScale(DESKTOP_UI_SCALE);
	skill4Button->setPosition(ccp(winWidth / 2 + width + 8, 2));
	skill4Button->setScale(DESKTOP_UI_SCALE);
	skill5Button->setPosition(ccp(winWidth / 2 + (width + 8) * 2, 2));
	skill5Button->setScale(DESKTOP_UI_SCALE);

	item1Button->setScale(DESKTOP_UI_SCALE);
	item2Button->setScale(DESKTOP_UI_SCALE);
	item3Button->setScale(DESKTOP_UI_SCALE);
	item4Button->setScale(DESKTOP_UI_SCALE);

	// Ramen	Item
	item1Button->setPosition(ccp(8, 8 + nAttackButton->getContentSize().height + skill1Button->getContentSize().height));
	// First 	Item (Speed Up & Stealth)
	item3Button->setPosition(ccp(winWidth - skill1Button->getContentSize().width - 64, 2));
	// Second 	Item (変わり身の術)
	item4Button->setPosition(ccp(winWidth - 95, 50));
	// Third 	Item (Trap)
	item2Button->setPosition(ccp(winWidth - 44, 8 + nAttackButton->getContentSize().height + 8));
#endif

	// Set mask
	skill1Button->setMarkSprite("skill_freeze.png");
	skill2Button->setMarkSprite("skill_freeze.png");
	skill3Button->setMarkSprite("skill_freeze.png");
	skill4Button->setOugisMark();
	skill5Button->setOugisMark();

	item1Button->setMarkSprite("skill_freeze.png");
	item2Button->setMarkSprite("skill_freeze.png");
	item3Button->setMarkSprite("skill_freeze.png");
	item4Button->setMarkSprite("skill_freeze.png");

	// init gear
	updateGears();
	miniLayer = CCLayer::create();
	miniLayer->setAnchorPoint(ccp(0, 0));
	miniLayer->setPosition(ccp(winWidth - 112, winHeight - 38));

	for (auto tower : getGameLayer()->_TowerArray)
	{
		const char *path = "";
		MiniIcon *mi;
		if (tower->getGroup() == currentPlayer->getGroup())
			path = "tower_icon1.png";
		else
			path = "tower_icon2.png";
		mi = MiniIcon::create(path, false);
		mi->_delegate = miniLayer;
		miniLayer->addChild(mi);
		mi->updatePosition(tower->getSpawnPoint());
		mi->setCharId(tower->getCharId());

		_towerIconArray.push_back(mi);
	}

	for (auto player : getGameLayer()->_CharacterArray)
	{
		if (player->isPlayerOrCom())
		{
			MiniIcon *mi;
			const char *path = "";
			if (player->isPlayer())
			{
				path = "player_icon.png";
			}
			else if (player->isCom())
			{
				if (player->isGuardian())
				{
					path = "guardian_icon.png";
				}
				else
				{
					if (player->getGroup() == currentPlayer->getGroup())
					{
						path = "com_icon.png";
					}
					else
					{
						path = "enemy_icon.png";
					}
				}
			}

			mi = MiniIcon::create(path, true);
			mi->_delegate = miniLayer;
			miniLayer->addChild(mi);
			mi->updatePosition(player->getSpawnPoint());
			mi->setCharId(player->getCharId());
		}
	}

	addChild(miniLayer, 500);
	// Call after all addChild functions
	// thats can make ActionButton::setLock -> setMask work
	updateSpecialSkillButtons();

	_isInitPlayerHud = true;
}

void HudLayer::addMapIcon()
{
	for (auto player : getGameLayer()->_CharacterArray)
	{
		if (player->isGuardian())
		{
			MiniIcon *mi;
			const char *path = "guardian_icon.png";
			mi = MiniIcon::create(path, true);
			mi->_delegate = miniLayer;
			miniLayer->addChild(mi);
			mi->updatePosition(player->getSpawnPoint());
			mi->setCharId(player->getCharId());
		}
	}
}

void HudLayer::updateGears()
{
	if (!gear1Button && !gear2Button && !gear3Button)
	{
		gear1Button = ActionButton::create("gearbg.png");
		gear1Button->setPosition(ccp(0, winSize.height - 92));
		gear1Button->setDelegate(this);
		gear1Button->setCD(15000);
		gear1Button->setABType(GearBtn);

		gear1Button->setMarkSprite("gear_freeze.png");
		gear1Button->_gearType = None;
		addChild(gear1Button, 200);

		gear2Button = ActionButton::create("gearbg.png");
		gear2Button->setPosition(ccp(35, winSize.height - 112));
		gear2Button->setDelegate(this);
		gear2Button->setCD(15000);
		gear2Button->_gearType = None;
		gear2Button->setABType(GearBtn);
		gear2Button->setMarkSprite("gear_freeze.png");

		addChild(gear2Button, 200);

		gear3Button = ActionButton::create("gearbg.png");
		gear3Button->setPosition(ccp(70, winSize.height - 92));
		gear3Button->setCD(15000);
		gear3Button->setDelegate(this);
		gear3Button->_gearType = None;

		gear3Button->setABType(GearBtn);
		gear3Button->setMarkSprite("gear_freeze.png");
		addChild(gear3Button, 200);

		return;
	}

	int i = 0;
	for (auto gear : getGameLayer()->currentPlayer->getGearArray())
	{
		if (gear != gear1Button->_gearType && i == 0)
		{
			gear1Button->setGearType(gear);
		}
		else if (gear != gear2Button->_gearType && i == 1)
		{
			gear2Button->setGearType(gear);
		}
		else if (gear != gear3Button->_gearType && i == 2)
		{
			gear3Button->setGearType(gear);
		}

		if (gear == 6 && getItem2Button()->_gearType == None)
		{
			getItem2Button()->_gearType = gear;
			getItem2Button()->setVisible(true);
			getItem2Button()->_isLock = false;
		}
		else if (gear == 0 && getItem3Button()->_gearType == None)
		{
			getItem3Button()->_gearType = gear;
			getItem3Button()->_isLock = false;
			getItem3Button()->setVisible(true);
		}
		else if (gear == 3 && getItem4Button()->_gearType == None)
		{
			getItem4Button()->setVisible(true);
			getItem4Button()->_gearType = gear;
			getItem4Button()->_isLock = false;
		}

		i++;
	}
}

void HudLayer::setHPLose(float percent)
{
	CCRotateTo *ra = CCRotateTo::create(0.2f, -((1 - percent) * 180), -((1 - percent) * 180));
	status_hpbar->runAction(ra);

	uint32_t hp = getGameLayer()->currentPlayer->getHP();
	hpLabel->setString(to_cstr(hp));
}

void HudLayer::setCKRLose(bool isCRK2)
{
	if (!isCRK2)
	{
		if (skill4Button)
		{
			if (skill4Button->lockLabel1)
			{
				skill4Button->ougismarkSprite->setVisible(false);
				skill4Button->_isMarkVisable = false;
				auto su = CCScaleBy::create(0.2f, 1.1f);
				auto call = CallFunc::create(std::bind(&ActionButton::setProgressMark, skill4Button));
				auto seq = newSequence(su, su->reverse(), call);
				skill4Button->runAction(seq);
			}
			else
			{
				skill4Button->updateProgressMark();
			}
		}
	}
	else
	{
		if (skill5Button)
		{
			if (skill5Button->lockLabel1)
			{
				skill5Button->ougismarkSprite->setVisible(false);
				skill5Button->_isMarkVisable = false;
				auto su = CCScaleBy::create(0.2f, 1.1f);
				auto call = CallFunc::create(std::bind(&ActionButton::setProgressMark, skill5Button));
				auto seq = newSequence(su, su->reverse(), call);
				skill5Button->runAction(seq);
			}
			else
			{
				skill5Button->updateProgressMark();
			}
		}
	}
}

void HudLayer::setEXPLose()
{
	int exp = getGameLayer()->currentPlayer->getEXP();
	int lvExp = (getGameLayer()->currentPlayer->getLV() - 1) * 500;
	float Percent = (exp - lvExp) / 500.0f * 100;
	if (Percent > 100)
		Percent = 100;

	// CCRotateTo* ra=CCRotateTo::create(0.2f,((1-Percent/100)*90),((1-Percent/100)*90));
	// status_expbar->runAction(ra);
	status_expbar->setPercentage((1 + Percent / 100) * 50);

	if (exp >= 2500)
	{
		status_expbar->setPercentage(100);
		expLabel->setString("Max");
	}
	else
	{
		expLabel->setString(format("{}%", (int)Percent).c_str());
	}
}

void HudLayer::setTowerState(int charId)
{
	for (auto mi : _towerIconArray)
	{
		if (mi->getCharId() == charId)
		{
			mi->updateState();
		}
	}
}

void HudLayer::setCoin(const char *value)
{
	auto cl = coinLabel->getString();
	int tempCoin = to_int(cl) + to_int(value);
	coinLabel->setString(to_cstr(tempCoin));
}

bool HudLayer::offCoin(const char *value)
{
	auto cl = coinLabel->getString();
	int tempCoin = to_int(cl);
	if (tempCoin - to_int(value) >= 0)
	{
		tempCoin -= to_int(value);
		coinLabel->setString(to_cstr(tempCoin));
		getGameLayer()->currentPlayer->minusCoin(to_uint(value));
		return true;
	}
	else
	{
		return false;
	}
}

void HudLayer::setReport(const string &name1, const string &name2, uint32_t killNum)
{
	bool isDisplay = _reportListArray.empty();

	if (isDisplay)
	{
		float length;
		reportSprite = createReport(name1, name2, length);
		reportSprite->setPosition(ccp(winSize.width / 2 - length / 2, winSize.height - 80));
		addChild(reportSprite, 500);

		auto su = CCScaleBy::create(0.2f, 1.0f);
		auto delay = CCDelayTime::create(2.0f);
		auto call = CallFunc::create(std::bind(&HudLayer::setReportCache, this));
		auto seq = newSequence(su, su->reverse(), delay, call);
		reportSprite->runAction(seq);
	}

	_reportListArray.push_back({
		.name1 = name1,
		// .char1Id = charId,
		.name2 = name2,
		.num = 1,
		.kills = killNum,
		.isDisplay = isDisplay,
	});
}

void HudLayer::setReportCache()
{
	reportSprite->removeFromParent();

	for (auto &data : _reportListArray)
	{
		if (data.isDisplay) // TODO: Improve performance
			continue;

		float length;
		reportSprite = createReport(data.name1, data.name2, length);
		reportSprite->setPosition(ccp(winSize.width / 2 - length / 2, winSize.height - 80));
		addChild(reportSprite, 500);

		auto su = CCScaleBy::create(0.2f, 1.1f);
		auto delay = CCDelayTime::create(2.0f);
		auto call = CallFunc::create(std::bind(&HudLayer::setReportCache, this));
		auto seq = newSequence(su, su->reverse(), delay, call);

		reportSprite->runAction(seq);

		if (data.name2 != kRoleTower)
		{
			int num2 = 0;
			for (auto &data2 : _reportListArray)
			{
				if (data2.name1 == data.name1 &&
					// data2.charId == data.charId &&
					data2.name2 != kRoleTower &&
					data2.isDisplay)
				{
					num2 += 1;
				}
			}

			if (num2 == 1)
			{
				if (reportSPCSprite)
				{
					reportSPCSprite->stopAllActions();
					reportSPCSprite->removeFromParent();
				}
				reportSPCSprite = createSPCReport(data.kills, num2);
				reportSPCSprite->setPosition(ccp(winSize.width / 2, winSize.height - 115));
				addChild(reportSPCSprite, 500);
				auto fn = CCFadeIn::create(0.8f);
				auto mv = CCMoveBy::create(0.8f, ccp(0, 10));
				auto sp = CCSpawn::createWithTwoActions(fn, mv);
				auto delay2 = CCDelayTime::create(1.6f);
				auto call2 = CallFunc::create(std::bind(&HudLayer::clearSPCReport, this));
				auto seq2 = newSequence(sp, delay2, call2);
				reportSPCSprite->runAction(seq2);
			}
			else if (num2 >= 2)
			{
				if (reportSPCSprite)
				{
					reportSPCSprite->stopAllActions();
					reportSPCSprite->removeFromParent();
				}

				reportSPCSprite = createSPCReport(data.kills, num2);
				reportSPCSprite->setScale(2.0);
				reportSPCSprite->setPosition(ccp(winSize.width / 2, winSize.height - 105));
				addChild(reportSPCSprite, 500);
				auto st = CCScaleTo::create(0.8f, 1.0f, 1.0f);
				auto call2 = CallFunc::create(std::bind(&HudLayer::stopSPCReport, this));
				auto seq2 = newSequence(st, call2);
				reportSPCSprite->runAction(seq2);

				auto sk = CCRepeatForever::create(CCShake::create(0.2f, 4));
				reportSPCSprite->runAction(sk);

				schedule(schedule_selector(HudLayer::updateSPCReprot), 0.2f);
			}
		}

		data.isDisplay = true;
		return;
	}

	_reportListArray.clear();
}

void HudLayer::setBuffDisplay(const char *buffName, float buffStayTime)
{
	// TODO: Display buff sprite
	return;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	float scale = 0.35f;
#else
	float scale = 0.40f;
#endif

	auto buffSprite = CCSprite::createWithSpriteFrameName(format("{}_{}.png", getGameLayer()->currentPlayer->getName(), buffName).c_str());
	if (buffSprite == nullptr)
		return;
	buffSprite->setAnchorPoint(ccp(0, 0));
	buffSprite->setPosition(ccp(8, item1Button->getPositionY() + 76 - 28 * _buffCount));
	if (buffStayTime != 0)
	{
		if (_buffCount == 0)
		{
			bcdLabel1 = CCLabelBMFont::create(to_cstr(buffStayTime), "Fonts/1.fnt");
			bcdLabel1->setScale(scale);
			bcdLabel1->setPosition(ccp(5, 5));
			bcdLabel1->setAnchorPoint(ccp(0.5, 0.5));
			buffSprite->addChild(bcdLabel1);
			schedule(schedule_selector(HudLayer::updateBuffDisplay), 1.0f);
		}
		else
		{
			bcdLabel2 = CCLabelBMFont::create(to_cstr(buffStayTime), "Fonts/1.fnt");
			bcdLabel2->setScale(scale);
			bcdLabel2->setPosition(ccp(5, 5));
			bcdLabel2->setAnchorPoint(ccp(0.5, 0.5));
			buffSprite->addChild(bcdLabel2);
			schedule(schedule_selector(HudLayer::updateBuffDisplay2), 1.0f);
		}
	}

	auto delay = CCDelayTime::create(buffStayTime - 3);
	auto call = CallFunc::create(std::bind(&HudLayer::clearBuffDisplay, this, buffSprite));
	auto seq = newSequence(delay, call);
	buffSprite->runAction(seq);
	buffSprite->setTag(0);

	buffSprite->retain();
	addChild(buffSprite, 500);
	_buffCount++;
}

void HudLayer::updateBuffDisplay(float dt)
{
	if (bcdLabel1)
	{
		int bcdValue1 = to_int(bcdLabel1->getString());
		if (bcdValue1 > 0)
		{
			bcdLabel1->setString(to_cstr(bcdValue1 - 1));
		}
		else
		{
			bcdLabel1->removeFromParent();
			bcdLabel1 = nullptr;
			_buffCount--;
		}
	}
}

void HudLayer::updateBuffDisplay2(float dt)
{
	if (bcdLabel2)
	{
		int bcdValue2 = to_int(bcdLabel2->getString());
		if (bcdValue2 > 0)
		{
			bcdLabel2->setString(to_cstr(bcdValue2 - 1));
		}
		else
		{
			bcdLabel2->removeFromParent();
			bcdLabel2 = nullptr;
			_buffCount--;
		}
	}
}

void HudLayer::clearBuffDisplay(CCSprite *bs)
{
	if (bs->getTag() == 0)
	{
		auto call = CallFunc::create(std::bind(&HudLayer::clearBuffDisplay, this, bs));
		auto delay = CCDelayTime::create(4.0f);
		bs->setTag(1);
		auto fade = CCFadeOut::create(0.5f);
		auto fadeseq = CCRepeatForever::create(newSequence(fade, fade->reverse()));
		auto seq = newSequence(delay, call);
		bs->runAction(seq);
		bs->runAction(fadeseq);
	}
	else
	{
		bs->removeFromParent();
	}
}

void HudLayer::clearSPCReport()
{
	if (reportSPCSprite)
	{
		reportSPCSprite->stopAllActions();
		reportSPCSprite->removeFromParent();
		reportSPCSprite = nullptr;
	}
}

void HudLayer::stopSPCReport()
{
	if (reportSPCSprite)
	{
		reportSPCSprite->stopAllActions();
		unschedule(schedule_selector(HudLayer::updateSPCReprot));
		reportSPCSprite->setPosition(ccp(winSize.width / 2, winSize.height - 105));
		reportSPCSprite->setScale(1.0f);
		auto delay = CCDelayTime::create(1.6f);
		auto call = CallFunc::create(std::bind(&HudLayer::clearSPCReport, this));
		reportSPCSprite->runAction(newSequence(delay, call));
	}
}

void HudLayer::updateSPCReprot(float dt)
{
	if (reportSPCSprite)
	{
		reportSPCSprite->setPosition(ccp(winSize.width / 2, winSize.height - 105));
	}
}

CCSprite *HudLayer::createSPCReport(uint32_t killNum, int num)
{
	bool isBrocast = false;
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isVoice"))
	{
		isBrocast = true;
	}

	if (num == 1)
	{
		if (killNum < 10)
		{
			reportSPCSprite = CCSprite::createWithSpriteFrameName("DoubleKill_rpf.png");
			if (isBrocast)
				SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/kill2_1.ogg");
		}
		else if (killNum < 20)
		{
			reportSPCSprite = CCSprite::createWithSpriteFrameName("KillingSpree_rpf.png");
			if (isBrocast)
				SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/kill2_2.ogg");
		}
		else if (killNum < 30)
		{
			reportSPCSprite = CCSprite::createWithSpriteFrameName("Unstoppable_rpf.png");
			if (isBrocast)
				SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/kill2_3.ogg");
		}
		else if (killNum >= 30)
		{
			reportSPCSprite = CCSprite::createWithSpriteFrameName("Godlike_rpf.png");
			if (isBrocast)
				SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/kill2_4.ogg");
		}
	}
	else if (num == 2)
	{
		if (killNum < 10)
		{
			reportSPCSprite = CCSprite::createWithSpriteFrameName("TripeKill_rpf.png");
			if (isBrocast)
				SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/kill3_1.ogg");
		}
		else if (killNum < 20)
		{
			reportSPCSprite = CCSprite::createWithSpriteFrameName("Domination_rpf.png");
			if (isBrocast)
				SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/kill3_2.ogg");
		}
		else if (killNum < 30)
		{
			reportSPCSprite = CCSprite::createWithSpriteFrameName("Rampage_rpf.png");
			if (isBrocast)
				SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/kill3_3.ogg");
		}
		else if (killNum >= 30)
		{
			reportSPCSprite = CCSprite::createWithSpriteFrameName("Holyshit_rpf.png");
			if (isBrocast)
				SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/kill3_4.ogg");
		}
	}
	else
	{
		reportSPCSprite = CCSprite::createWithSpriteFrameName("MonsterKill_rpf.png");
		if (isBrocast)
			SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/kill4.ogg");
	}

	return reportSPCSprite;
}

CCSprite *HudLayer::createReport(const string &name1, const string &name2, float &length)
{
	CCSprite *reportSprite = CCSprite::create();

	CCSprite *slain_p = CCSprite::createWithSpriteFrameName(format("{}_rp.png", name1).c_str());
	slain_p->setAnchorPoint(ccp(0, 0.5f));
	slain_p->setPosition(ccp(0, 0));
	reportSprite->addChild(slain_p);

	CCSprite *slain_pf = CCSprite::createWithSpriteFrameName(format("{}_rpf.png", name1).c_str());
	slain_pf->setPosition(ccp(slain_p->getContentSize().width, 0));
	slain_pf->setAnchorPoint(ccp(0, 0.5f));
	reportSprite->addChild(slain_pf);

	CCSprite *slain;
	if (name2 != kRoleTower)
	{
		slain = CCSprite::createWithSpriteFrameName("slain.png");
		reportSprite->addChild(slain);
	}
	else
	{
		slain = CCSprite::createWithSpriteFrameName("destroy.png");
		reportSprite->addChild(slain);
	}
	slain->setAnchorPoint(ccp(0, 0.5f));
	slain->setPosition(ccp(slain_pf->getPositionX() + slain_pf->getContentSize().width, 0));

	CCSprite *death_pf = CCSprite::createWithSpriteFrameName(format("{}_rpf.png", name2).c_str());
	death_pf->setAnchorPoint(ccp(0, 0.5f));
	death_pf->setPosition(ccp(slain->getPositionX() + slain->getContentSize().width, 0));
	reportSprite->addChild(death_pf);
	CCSprite *death_p;
	if (name2 != kRoleTower)
	{
		death_p = CCSprite::createWithSpriteFrameName(format("{}_rp.png", name2).c_str());
		death_p->setAnchorPoint(ccp(0, 0.5f));
		death_p->setPosition(ccp(death_pf->getPositionX() + death_pf->getContentSize().width, 0));
		reportSprite->addChild(death_p);
	}

	if (name2 != kRoleTower)
	{
		length = slain_p->getContentSize().width + slain_pf->getContentSize().width + slain->getContentSize().width + death_pf->getContentSize().width + death_p->getContentSize().width;
	}
	else
	{
		length = slain_p->getContentSize().width + slain_pf->getContentSize().width + slain->getContentSize().width + death_pf->getContentSize().width;
	}

	return reportSprite;
}

void HudLayer::attackButtonClick(abType type)
{
	getGameLayer()->attackButtonClick(type);
}

void HudLayer::gearButtonClick(GearType type)
{
	getGameLayer()->gearButtonClick(type);
}

void HudLayer::attackButtonRelease()
{
	getGameLayer()->attackButtonRelease();
}

void HudLayer::pauseButtonClick(CCObject *sender)
{
	getGameLayer()->onPause();
}

void HudLayer::gearButtonClick(CCObject *sender)
{
	if (!_isAllButtonLocked)
	{
		getGameLayer()->onGear();
	}
}

bool HudLayer::getSkillFinish()
{
	return getGameLayer()->getSkillFinish();
}

bool HudLayer::getOugisEnable(bool isCKR2)
{
	if (!isCKR2)
	{
		uint32_t ckr = getGameLayer()->currentPlayer->getCKR();
		return ckr >= 15000;
	}
	else
	{
		uint32_t ckr2 = getGameLayer()->currentPlayer->getCKR2();
		return ckr2 >= 25000;
	}
}

void HudLayer::costCKR(uint32_t value, bool isCKR2)
{
	if (!isCKR2)
	{
		uint32_t ckr = getGameLayer()->currentPlayer->getCKR();
		ckr = ckr >= value ? ckr - value : 0;

		getGameLayer()->currentPlayer->setCKR(ckr);
		setCKRLose(false);
	}
	else
	{
		uint32_t ckr2 = getGameLayer()->currentPlayer->getCKR2();
		ckr2 = ckr2 >= value ? ckr2 - value : 0;

		getGameLayer()->currentPlayer->setCKR2(ckr2);
		setCKRLose(true);
	}
}

void HudLayer::setOugis(const string &name, const string &group)
{
	if (!ougisLayer)
	{
		CCObject *pObject;
		CCArray *childArray = getChildren();
		CCARRAY_FOREACH(childArray, pObject)
		{
			CCNode *object = (CCNode *)pObject;
			object->pauseSchedulerAndActions();
		}

		ougisLayer = CCLayer::create();
		int startPosY = 0;
		int startPosX = 0;
		int endPosX = 0;
		CCSprite *CutBg;
		const char *cutPath1;
		const char *cutPath2;
		if (getGameLayer()->playerGroup == Group::Konoha)
		{
			cutPath1 = "CutBg.png";
			cutPath2 = "CutBg2.png";
		}
		else
		{
			cutPath1 = "CutBg2.png";
			cutPath2 = "CutBg.png";
		}

		bool isKonohaGroup = group == Group::Konoha;
		if (isKonohaGroup)
		{
			startPosY = 0;
			startPosX = -48;
			endPosX = 0;
			CutBg = CCSprite::createWithSpriteFrameName(cutPath1);
			CutBg->setAnchorPoint(ccp(0, 0));
		}
		else
		{
			startPosY = winSize.height / 2;
			startPosX = winSize.width + 48;
			endPosX = winSize.width;
			CutBg = CCSprite::createWithSpriteFrameName(cutPath2);
			CutBg->setFlipX(true);
			CutBg->setAnchorPoint(ccp(1, 0.5f));
		}

		CutBg->setPosition(ccp(startPosX, startPosY));
		CutBg->runAction(CCMoveTo::create(0.3f, ccp(endPosX, startPosY)));
		ougisLayer->addChild(CutBg);

		CCArray *animeFrames = CCArray::create();
		for (int i = 1; i <= 8; i++)
		{
			auto frame = getSpriteFrame("CutLine_{:02d}.png", i);
			animeFrames->addObject(frame);
		}

		auto tempAnimation = CCAnimation::createWithSpriteFrames(animeFrames, 0.1f);
		auto tempAction = CCAnimate::create(tempAnimation);

		CCSprite *CutLine = CCSprite::createWithSpriteFrameName("CutLine_01.png");
		if (isKonohaGroup)
		{
			CutLine->setAnchorPoint(ccp(0, 0));
			CutLine->setPosition(ccp(-48, 0));
			CutLine->runAction(tempAction);
			CutLine->runAction(CCMoveTo::create(0.3f, ccp(0, 0)));
		}
		else
		{
			CutLine->setFlipX(true);
			CutLine->setAnchorPoint(ccp(1, 0.5f));
			CutLine->setPosition(ccp(winSize.width + 48, winSize.height / 2));
			CutLine->runAction(tempAction);
			CutLine->runAction(CCMoveTo::create(0.3f, ccp(winSize.width, winSize.height / 2)));
		}

		ougisLayer->addChild(CutLine);

		CCSprite *CutLineUP = CCSprite::createWithSpriteFrameName("CutLineUP.png");
		if (isKonohaGroup)
		{
			CutLineUP->setAnchorPoint(ccp(0, 0));
			CutLineUP->setPosition(ccp(-48, 2));
			CutLineUP->runAction(CCMoveTo::create(0.3f, ccp(-1, 1)));
		}
		else
		{
			CutLineUP->setFlipX(true);
			CutLineUP->setAnchorPoint(ccp(1, 0.5f));
			CutLineUP->setPosition(ccp(winSize.width + 48, winSize.height / 2 + 2));
			CutLineUP->runAction(CCMoveTo::create(0.3f, ccp(winSize.width + 1, winSize.height / 2 + 1)));
		}

		ougisLayer->addChild(CutLineUP);

		CCSprite *CutIn = CCSprite::createWithSpriteFrameName(format("{}_CutIn.png", name).c_str());
		if (isKonohaGroup)
		{
			CutIn->setAnchorPoint(ccp(0, 0));
			CutIn->setPosition(ccp(-200, 10));
			CutIn->runAction(CCMoveTo::create(0.3f, ccp(0, 10)));
		}
		else
		{
			CutIn->setAnchorPoint(ccp(1, 0));
			CutIn->setPosition(ccp(winSize.width + 200, winSize.height / 2 + 10 - CutBg->getContentSize().height / 2));
			CutIn->runAction(CCMoveTo::create(0.3f, ccp(winSize.width, winSize.height / 2 + 10 - CutBg->getContentSize().height / 2)));
		}
		ougisLayer->addChild(CutIn);

		CCSprite *CutLineDown = CCSprite::createWithSpriteFrameName("CutLineDown.png");
		if (isKonohaGroup)
		{
			CutLineDown->setAnchorPoint(ccp(0, 0));
			CutLineDown->setPosition(ccp(-48, 0));
			CutLineDown->runAction(CCMoveTo::create(0.3f, ccp(0, 0)));
		}
		else
		{
			CutLineDown->setFlipX(true);
			CutLineDown->setAnchorPoint(ccp(1, 0));
			CutLineDown->setPosition(ccp(winSize.width + 48, winSize.height / 2 - CutBg->getContentSize().height / 2));
			CutLineDown->runAction(CCMoveTo::create(0.3f, ccp(winSize.width, winSize.height / 2 - CutBg->getContentSize().height / 2)));
		}

		ougisLayer->addChild(CutLineDown);

		ougisLayer->setPosition(ccp(0, 0));
		addChild(ougisLayer, -100);

		auto delay = CCDelayTime::create(1.0f);
		auto call = CallFunc::create(std::bind(&HudLayer::removeOugis, this));
		ougisLayer->runAction(newSequence(delay, call));
	}
}

void HudLayer::removeOugis()
{
	ougisLayer->removeFromParent();
	ougisLayer = nullptr;

	CCObject *pObject;
	CCArray *childArray = getChildren();
	CCARRAY_FOREACH(childArray, pObject)
	{
		CCNode *object = (CCNode *)pObject;
		object->resumeSchedulerAndActions();
	}

	getGameLayer()->removeOugis();
}

void HudLayer::initSkillButtons()
{
	// TODO: For Ino ougi2 (Player can control other character's skills)
}

void HudLayer::setSkillButtons(bool isVisable)
{
	// skills
	skill1Button->setVisible(isVisable);
	skill2Button->setVisible(isVisable);
	skill3Button->setVisible(isVisable);
	skill4Button->setVisible(isVisable);
	skill5Button->setVisible(isVisable);
	// items
	item1Button->setVisible(isVisable);
	item2Button->setVisible(isVisable);
	item3Button->setVisible(isVisable);
	item4Button->setVisible(isVisable);
}

void HudLayer::updateSkillButtons()
{
	auto player = getGameLayer()->currentPlayer;
	if (!player)
		return;
	auto charName = player->getName();
	if (charName.length() == 0)
		return;

	// update avator
	auto avator = CCSprite::createWithSpriteFrameName((charName + "_avator.png").c_str());
	if (avator)
		gearMenuSprite->setNormalImage(avator);

	auto cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCSpriteFrame *frame;

#define updateButtonInfo(index)                                                    \
	frame = cache->spriteFrameByName((charName + "_skill" #index ".png").c_str()); \
	if (skill##index##Button)                                                      \
	{                                                                              \
		if (frame != nullptr)                                                      \
			skill##index##Button->setDisplayFrame(frame);                          \
		skill##index##Button->setCD(player->_sAttackCD##index * 1000);             \
		skill##index##Button->_isColdChanged = true;                               \
	}

#define updateOugiButtonInfo(index)                                                \
	frame = cache->spriteFrameByName((charName + "_skill" #index ".png").c_str()); \
	if (skill##index##Button)                                                      \
	{                                                                              \
		if (frame != nullptr)                                                      \
			skill##index##Button->setDisplayFrame(frame);                          \
		skill##index##Button->_isColdChanged = true;                               \
	}

	updateButtonInfo(1);
	updateButtonInfo(2);
	updateButtonInfo(3);
	updateOugiButtonInfo(4);
	updateOugiButtonInfo(5);
	updateSpecialSkillButtons();
}

void HudLayer::updateSpecialSkillButtons()
{
	auto currentPlayer = getGameLayer()->currentPlayer;
	if (currentPlayer == nullptr)
	{
		CCLOGERROR("Current player is null.");
		return;
	}

	skill1Button->setDoubleSkill(currentPlayer->_sAttack1isDouble);
	skill2Button->setDoubleSkill(currentPlayer->_sAttack2isDouble);
	skill3Button->setDoubleSkill(currentPlayer->_sAttack3isDouble);
	skill1Button->setCD(currentPlayer->_sAttackCD1 * 1000);
	skill2Button->setCD(currentPlayer->_sAttackCD2 * 1000);
	skill3Button->setCD(currentPlayer->_sAttackCD3 * 1000);
	skill1Button->_isColdChanged = true;
	skill2Button->_isColdChanged = true;
	skill3Button->_isColdChanged = true;
	if (skill1Button->_isLock)
		skill1Button->unLock();
	if (skill2Button->_isLock)
		skill2Button->unLock();
	if (skill3Button->_isLock)
		skill3Button->unLock();
}

void HudLayer::resetSkillButtons()
{
	skill1Button->reset();
	skill2Button->reset();
	skill3Button->reset();
	skill4Button->reset();
	skill5Button->reset();
}
