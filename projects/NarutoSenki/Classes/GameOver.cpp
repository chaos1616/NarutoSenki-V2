#include "GameOver.h"
#include "GameLayer.h"
#include "Core/Hero.hpp"
#include "GameMode/GameModeImpl.h"

#include <fstream>

GameOver::GameOver()
{
	exitLayer = nullptr;
	cheatLayer = nullptr;
	isPosting = false;
	refreshBtn = nullptr;
}

GameOver::~GameOver()
{
	CCAnimationCache::purgeSharedAnimationCache();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

bool GameOver::init(CCRenderTexture *snapshoot)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		SimpleAudioEngine::sharedEngine()->stopAllEffects();
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);

		CCTexture2D *bgTexture = snapshoot->getSprite()->getTexture();
		CCSprite *bg = CCSprite::createWithTexture(bgTexture);
		bg->setAnchorPoint(ccp(0, 0));
		bg->setFlipY(true);
		addChild(bg, 0);

		CCLayer *blend = CCLayerColor::create(ccc4(0, 0, 0, 150), winSize.width, winSize.height);
		addChild(blend, 1);

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

		CCSprite *result_title = CCSprite::createWithSpriteFrameName("result_title.png");
		result_title->setAnchorPoint(ccp(0, 0));
		result_title->setPosition(ccp(2, winSize.height - result_title->getContentSize().height - 2));
		addChild(result_title, 3);

		result_bg = CCSprite::createWithSpriteFrameName("gameover_bg.png");
		result_bg->setAnchorPoint(ccp(0.5f, 0.5f));
		result_bg->setScale(0.5f);
		result_bg->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 6));
		addChild(result_bg, 4);

		CCScaleTo *su = CCScaleTo::create(0.2f, 1.0);
		CCAction *seq = CCSequence::create(su, CCCallFunc::create(this, callfunc_selector(GameOver::listResult)), nullptr);
		result_bg->runAction(seq);

		bRet = true;
	} while (0);

	return bRet;
}

void GameOver::listResult()
{
	if (_delegate->_isHardCoreGame)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/battle_over1.ogg");
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/battle_over.ogg");
	}

	CCString *path = CCString::createWithFormat("%s_half.png", _delegate->currentPlayer->getCharacter()->getCString());
	CCSprite *half = CCSprite::createWithSpriteFrameName(path->getCString());

	if (strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Konan") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Karin") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Suigetsu") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Hidan") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Tobirama") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Tsunade") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Kankuro") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "SageJiraiya") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Minato") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Tobi") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Lee") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "RockLee") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Hinata") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Asuma") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Chiyo") == 0 ||
		strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "Kisame") == 0)
	{
		half->setFlipX(true);
	}

	half->setAnchorPoint(ccp(0, 0));
	half->setPosition(ccp(winSize.width / 2 + result_bg->getContentSize().width / 2 - half->getContentSize().width, result_bg->getPositionY() - result_bg->getContentSize().height / 2 + 9));
	addChild(half, 5);

	CCSprite *list_bg = CCSprite::createWithSpriteFrameName("list_bg.png");
	list_bg->setAnchorPoint(ccp(0, 0));
	list_bg->setPosition(ccp(winSize.width / 2 - result_bg->getContentSize().width / 2 + 2, result_bg->getPositionY() - result_bg->getContentSize().height / 2 + 26));
	addChild(list_bg, 5);

	int _hour = _delegate->_minute / 60;
	int _minute = _delegate->_minute % 60;

	CCSprite *timeBG = CCSprite::createWithSpriteFrameName("time_bg.png");
	timeBG->setAnchorPoint(ccp(0, 0));
	timeBG->setPosition(ccp(winSize.width / 2 + result_bg->getContentSize().width / 2 - 11 - timeBG->getContentSize().width, result_bg->getPositionY() - result_bg->getContentSize().height / 2 + 46));
	addChild(timeBG, 6);

	CCString *tempTime = CCString::createWithFormat("%02d:%02d:%02d", _hour, _minute, _delegate->_second);

	CCLabelBMFont *gameClock = CCLabelBMFont::create(tempTime->getCString(), "Fonts/1.fnt");
	gameClock->setAnchorPoint(ccp(0.5f, 0));
	gameClock->setPosition(ccp(timeBG->getPositionX() + timeBG->getContentSize().width / 2, timeBG->getPositionY() + 3));
	gameClock->setScale(0.48f);
	addChild(gameClock, 7);

	float _totalSecond = _delegate->_minute * 60 + _delegate->_second;
	float resultScore = 0;
	int killDead = to_int(_delegate->currentPlayer->getKillNum()->getCString()) - _delegate->currentPlayer->_deadNum;

	if (_totalSecond != to_int(_delegate->getTotalTM()->getCString()))
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		CCDirector::sharedDirector()->end();
		return;
	}

	if (_delegate->_isHardCoreGame)
	{
		if (_totalSecond > 900.0)
		{
			resultScore = float((killDead / float(_totalSecond / 60)) / 3) * 100;
		}
		else
		{
			resultScore = float((killDead - ((_totalSecond / 60 - 15) * 3)) / 45) * 100;
		}
	}
	else
	{
		if (_totalSecond > 600.0)
		{
			resultScore = float((killDead / float(_totalSecond / 60)) / 4) * 100;
		}
		else
		{
			resultScore = float((killDead - ((_totalSecond / 60 - 10) * 4)) / 40) * 100;
		}
	}

	if (_totalSecond < 2 * 30 + 5 && _isWin)
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		CCDirector::sharedDirector()->end();
		return;
	}

	CCObject *pObject;
	int i = 0;
	int konohaKill = 0;
	int akatsukiKill = 0;

	CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
	{
		Hero *hero = (Hero *)pObject;
		if (strcmp(hero->getRole()->getCString(), ROLE_CLONE) == 0 ||
			strcmp(hero->getRole()->getCString(), ROLE_SUMMON) == 0 ||
			strcmp(hero->getRole()->getCString(), ROLE_KUGUTSU) == 0 ||
			strcmp(hero->getCharacter()->getCString(), Guardian_Han) == 0 ||
			strcmp(hero->getCharacter()->getCString(), Guardian_Roshi) == 0)
		{
			continue;
		}

		//4v4
		if (Cheats > 6)
		{
			if (strcmp(hero->getRole()->getCString(), "Player") != 0)
			{
				continue;
			}
		}

		if (hero->_isControlled)
		{
			hero->_isControlled = false;
			hero->changeGroup();
		}

		CCString *path = CCString::createWithFormat(("%s_small.png"), hero->getCharacter()->getCString());
		CCSprite *avator_small = CCSprite::createWithSpriteFrameName(path->getCString());
		avator_small->setAnchorPoint(ccp(0, 0));

		int realKillNum = to_int(hero->getKillNum()->getCString());

		if (strcmp(hero->getGroup()->getCString(), Konoha) == 0)
		{
			konohaKill += realKillNum;
		}
		else
		{
			akatsukiKill += realKillNum;
		}

		CCString *knum = CCString::createWithFormat("%d", realKillNum);
		CCLabelBMFont *killNum = CCLabelBMFont::create(knum->getCString(), "Fonts/1.fnt");
		killNum->setScale(0.3f);

		CCString *dnum = CCString::createWithFormat("%d", hero->_deadNum);
		CCLabelBMFont *deadNum = CCLabelBMFont::create(dnum->getCString(), "Fonts/1.fnt");
		deadNum->setScale(0.3f);

		CCString *fnum = CCString::createWithFormat("%d", hero->_flogNum);
		CCLabelBMFont *flogNum = CCLabelBMFont::create(fnum->getCString(), "Fonts/1.fnt");
		flogNum->setScale(0.3f);

		float posX = winSize.width / 2 - result_bg->getContentSize().width / 2 + 2;

		if (strcmp(hero->getGroup()->getCString(), Konoha) == 0)
		{
			avator_small->setPosition(ccp(posX, result_bg->getPositionY() - result_bg->getContentSize().height / 2 + 152 - (i * 25)));
			killNum->setPosition(ccp(posX + 44, avator_small->getPositionY() + avator_small->getContentSize().height / 2));
			deadNum->setPosition(ccp(posX + 68, avator_small->getPositionY() + avator_small->getContentSize().height / 2));
			flogNum->setPosition(ccp(posX + 94, avator_small->getPositionY() + avator_small->getContentSize().height / 2));
		}
		else
		{
			avator_small->setPosition(ccp(posX, result_bg->getPositionY() - result_bg->getContentSize().height / 2 + 76 - ((i - 3) * 25)));
			killNum->setPosition(ccp(posX + 44, avator_small->getPositionY() + avator_small->getContentSize().height / 2));
			deadNum->setPosition(ccp(posX + 68, avator_small->getPositionY() + avator_small->getContentSize().height / 2));
			flogNum->setPosition(ccp(posX + 94, avator_small->getPositionY() + avator_small->getContentSize().height / 2));
		}

		if (hero->getGearArray() && hero->getGearArray()->count() > 0)
		{
			CCObject *pObject;
			int i = 0;
			CCARRAY_FOREACH(hero->getGearArray(), pObject)
			{
				CCString *tmpGear = (CCString *)pObject;
				CCSprite *gearIcon = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("gear_%02d.png", to_int(tmpGear->getCString()))->getCString());
				gearIcon->setPosition(ccp(flogNum->getPositionX() + 22 + i * 19, flogNum->getPositionY() - 1));
				gearIcon->setScale(0.5f);
				addChild(gearIcon, 7);
				i++;
			}
		}

		addChild(avator_small, 7);
		addChild(killNum, 7);
		addChild(deadNum, 7);
		addChild(flogNum, 7);

		i++;
	}

	if (_totalSecond > 900 && _delegate->_isSurrender)
	{
		if (strcmp(_delegate->currentPlayer->getGroup()->getCString(), Konoha) == 0)
		{
			if (konohaKill > akatsukiKill)
			{
				_isWin = true;
			}
		}
		else
		{
			if (akatsukiKill > konohaKill)
			{
				_isWin = true;
			}
		}
	}

	if (Cheats <= 6)
	{
		if (akatsukiKill + konohaKill != to_int(_delegate->getTotalKills()->getCString()))
		{
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
			CCDirector::sharedDirector()->end();
			return;
		}

		int realKillNum = to_int(_delegate->currentPlayer->getKillNum()->getCString());

		std::string tempReward = "";
		if (_delegate->_isHardCoreGame)
		{
			tempReward = "FDDD";
		}
		else
		{
			tempReward = "ONNN";
		}

		KTools::decode(tempReward);

		CCString *cl = KTools::readFromSQLite();
		int rewardNum;
		if (_isWin)
		{
			rewardNum = realKillNum * 75 + to_int(tempReward.c_str());
		}
		else
		{
			rewardNum = realKillNum * 50;
		}

		CCSprite *coinBG = CCSprite::createWithSpriteFrameName("coin_bg.png");
		coinBG->setAnchorPoint(ccp(0, 0));
		coinBG->setPosition(ccp(winSize.width / 2 + result_bg->getContentSize().width / 2 - coinBG->getContentSize().width - 11, result_bg->getPositionY() - result_bg->getContentSize().height / 2 + 12));
		addChild(coinBG, 6);

		CCSprite *adExtra = CCSprite::createWithSpriteFrameName("adExtra.png");
		adExtra->setAnchorPoint(ccp(0.5f, 0));
		adExtra->setPosition(ccp(coinBG->getPositionX() + 70, coinBG->getPositionY() + 22));
		addChild(adExtra, 7);

		CCString *extraCoin;
		int tempCoin;
		if (_isWin)
		{
			std::string tempEtra = "idd4";
			KTools::decode(tempEtra);
			tempCoin = rewardNum + to_int(cl->getCString()) + to_int(tempEtra.c_str());
			extraCoin = CCString::createWithFormat("+%d", 500);
		}
		else
		{
			tempCoin = rewardNum + to_int(cl->getCString());
			extraCoin = CCString::createWithFormat("+%d", 0);
		}

		CCString *realCoin = CCString::createWithFormat("%d", tempCoin);
		KTools::saveToSQLite("GameRecord", "coin", realCoin->getCString(), false);

		CCLabelBMFont *extraLabel = CCLabelBMFont::create(extraCoin->getCString(), "Fonts/yellow.fnt");
		extraLabel->setScale(0.5f);
		extraLabel->setAnchorPoint(ccp(0.5f, 0));
		extraLabel->setPosition(ccp(coinBG->getPositionX() + 68, coinBG->getPositionY() + 3));
		addChild(extraLabel, 7);

		CCString *rewardCoin = CCString::createWithFormat("%d", rewardNum);
		CCLabelBMFont *rewardLabel = CCLabelBMFont::create(rewardCoin->getCString(), "Fonts/yellow.fnt");
		rewardLabel->setAnchorPoint(ccp(0.5f, 0));
		rewardLabel->setPosition(ccp(coinBG->getPositionX() + 28, coinBG->getPositionY() + 3));
		rewardLabel->setScale(0.55f);
		addChild(rewardLabel, 7);
	}

	const char *imgSrc;

	if (_isWin)
	{
		if (resultScore >= 140 && _delegate->_isHardCoreGame && _delegate->_isRandomChar && !_delegate->_enableGear)
			imgSrc = "result_SSSR.png";
		else if (resultScore >= 120 && _delegate->_isHardCoreGame && _delegate->_isRandomChar && !_delegate->_enableGear)
			imgSrc = "result_SSR.png";
		else if (resultScore >= 100 && _delegate->_isHardCoreGame && _delegate->_isRandomChar && !_delegate->_enableGear)
			imgSrc = "result_SR.png";
		else if (resultScore >= 140)
			imgSrc = "result_SSS.png";
		else if (resultScore >= 120)
			imgSrc = "result_SS.png";
		else if (resultScore >= 100)
			imgSrc = "result_S.png";
		else if (resultScore >= 80)
			imgSrc = "result_A.png";
		else if (resultScore >= 60)
			imgSrc = "result_B.png";
		else
			imgSrc = "result_C.png";
	}
	else if (!_isWin)
	{
		imgSrc = "result_Defeat.png";
	}

	if (imgSrc)
	{
		CCSprite *recordSprite = CCSprite::createWithSpriteFrameName(imgSrc);
		recordSprite->setAnchorPoint(ccp(0, 0));
		recordSprite->setPosition(ccp(winSize.width / 2 + result_bg->getContentSize().width / 2 - recordSprite->getContentSize().width - 12, result_bg->getPositionY() - result_bg->getContentSize().height / 2 + 88));
		addChild(recordSprite, 7);

		if (_isWin && _delegate->_isHardCoreGame)
		{
			finnalScore = resultScore + float(_delegate->currentPlayer->_flogNum) / 100;
			// CCString *recordString = CCString::createWithFormat("%0.2fPts", finnalScore);

			// CCLabelBMFont *recordScore = CCLabelBMFont::create(recordString->getCString(), "Fonts/1.fnt");
			// recordScore->setAnchorPoint(ccp(1, 0.5f));
			// recordScore->setPosition(ccp(recordSprite->getPositionX() + recordSprite->getContentSize().width, recordSprite->getPositionY() - 7));
			// recordScore->setScale(0.35f);
			// addChild(recordScore, 10);

			// upload_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("upload_btn.png"), CCSprite::createWithSpriteFrameName("upload_btn.png"), nullptr, this, menu_selector(GameOver::onUPloadBtn));
			// CCMenu *upMenu = CCMenu::create(upload_btn, nullptr);
			// upload_btn->setAnchorPoint(ccp(1.0, 0));
			// upMenu->setPosition(ccp(winSize.width / 2 + result_bg->getContentSize().width / 2 - 14, winSize.height / 2 + result_bg->getContentSize().height / 2 - 62));
			// addChild(upMenu, 7);

			// detailRecord = CCString::createWithFormat("%02d:%02d,%s,%d,%d", _minute, _delegate->_second, _delegate->currentPlayer->getKillNum()->getCString(), _delegate->currentPlayer->_deadNum, _delegate->currentPlayer->_flogNum)->getCString();
		}
		if (Cheats <= 6)
		{
			resultChar = _delegate->currentPlayer->getCharacter();
			if (strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "SageNaruto") == 0)
			{
				resultChar = CCString::create("Naruto");
			}
			else if (strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "RikudoNaruto") == 0)
			{
				resultChar = CCString::create("Naruto");
			}
			else if (strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "SageJiraiya") == 0)
			{
				resultChar = CCString::create("Jiraiya");
			}
			else if (strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "ImmortalSasuke") == 0)
			{
				resultChar = CCString::create("Sasuke");
			}
			else if (strcmp(_delegate->currentPlayer->getCharacter()->getCString(), "RockLee") == 0)
			{
				resultChar = CCString::create("Lee");
			}

			if (_isWin)
			{
				CCString *winNum = KTools::readSQLite("CharRecord", "name", resultChar->getCString(), "column1");
				int tempWin = 0;

				if (resultScore >= 140)
				{
					tempWin = to_int(winNum->getCString()) + 3;
				}
				else if (resultScore >= 120)
				{
					tempWin = to_int(winNum->getCString()) + 2;
				}
				else
				{
					tempWin = to_int(winNum->getCString()) + 1;
				}

				CCString *realWin = CCString::createWithFormat("%d", tempWin);
				KTools::saveSQLite("CharRecord", "name", resultChar->getCString(), "column1", (char *)realWin->getCString(), false);

				if (_delegate->_isRandomChar && resultScore >= 120)
				{
					CCObject *pObject;

					if (_delegate->currentPlayer->_isControlled)
					{
						_delegate->currentPlayer->_isControlled = false;
						_delegate->currentPlayer->changeGroup();
					}

					CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
					{
						Hero *hero = (Hero *)pObject;
						if (strcmp(hero->getRole()->getCString(), ROLE_CLONE) == 0 ||
							strcmp(hero->getRole()->getCString(), "Player") == 0 ||
							strcmp(hero->getRole()->getCString(), ROLE_SUMMON) == 0 ||
							strcmp(hero->getRole()->getCString(), ROLE_KUGUTSU) == 0 ||
							strcmp(hero->getCharacter()->getCString(), Guardian_Han) == 0 ||
							strcmp(hero->getCharacter()->getCString(), Guardian_Roshi) == 0)
						{
							continue;
						}

						if (hero->_isControlled)
						{
							hero->_isControlled = false;
							hero->changeGroup();
						}

						if (strcmp(hero->getGroup()->getCString(), _delegate->currentPlayer->getGroup()->getCString()) == 0)
						{
							CCString *winNum = KTools::readSQLite("CharRecord", "name", hero->getCharacter()->getCString(), "column1");
							int tempWin = 0;
							if (resultScore >= 140)
							{
								tempWin = to_int(winNum->getCString()) + 2;
							}
							else
							{
								tempWin = to_int(winNum->getCString()) + 1;
							}

							CCString *realWin = CCString::createWithFormat("%d", tempWin);
							KTools::saveSQLite("CharRecord", "name", hero->getCharacter()->getCString(), "column1", (char *)realWin->getCString(), false);
						}
					}
				}
				CCString *recordTime = KTools::readSQLite("CharRecord", "name", resultChar->getCString(), "column3");
				if (recordTime->length() == 0)
				{
					KTools::saveSQLite("CharRecord", "name", resultChar->getCString(), "column3", (char *)tempTime->getCString(), false);
				}
				else
				{
					std::string bestTime = (std::string)recordTime->getCString();
					auto recordHour = bestTime.substr(0, 2).c_str();
					auto recordMinute = bestTime.substr(3, 2).c_str();
					auto recordSecond = bestTime.substr(6, 2).c_str();
					bool isNewRecord = false;

					if (to_int(recordHour) > _hour)
					{
						isNewRecord = true;
					}
					else if (to_int(recordHour) == _hour)
					{
						if (to_int(recordMinute) > _minute)
						{
							isNewRecord = true;
						}
						else if (to_int(recordMinute) == _minute)
						{
							if (to_uint(recordSecond) > _delegate->_second)
							{
								isNewRecord = true;
							}
							else
							{
								isNewRecord = false;
							}
						}
						else
						{
							isNewRecord = false;
						}
					}
					else
					{
						isNewRecord = false;
					}

					if (isNewRecord)
					{
						KTools::saveSQLite("CharRecord", "name", resultChar->getCString(), "column3", (char *)tempTime->getCString(), false);
					}
				}
			}
		}
	}

	if (Cheats <= 6)
	{
		CCLabelBMFont *version = CCLabelBMFont::create(GAMEOVER_VER, "Fonts/1.fnt");
		version->setPosition(ccp(winSize.width / 2 + 94, result_bg->getPositionY() - result_bg->getContentSize().height / 2 + 6));
		version->setScale(0.3f);
		addChild(version, 5);
	}
	else
	{
		CCLabelBMFont *version = CCLabelBMFont::create("The Carnival", "Fonts/1.fnt");
		version->setPosition(ccp(winSize.width / 2 + 94, result_bg->getPositionY() - result_bg->getContentSize().height / 2 + 6));
		version->setScale(0.3f);
		addChild(version, 5);
	}

	CCMenuItem *btm_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("close_btn1.png"), CCSprite::createWithSpriteFrameName("close_btn2.png"), nullptr, this, menu_selector(GameOver::onBackToMenu));
	CCMenu *overMenu = CCMenu::create(btm_btn, nullptr);
	overMenu->setPosition(ccp(winSize.width / 2 + result_bg->getContentSize().width / 2 - 12, winSize.height / 2 + result_bg->getContentSize().height / 2 - 18));
	addChild(overMenu, 7);

	_delegate->_isSurrender = false;

	// Reset cheats value
	if (getGameMode() == GameMode::HardCore_4Vs4)
	{
		auto mode = ((Mode4v4 *)getGameModeHandler());
		if (mode)
			Cheats = mode->getOldCheats();
		else
			CCLOG("Current mode is not 4v4");
	}
}

void GameOver::onUPloadBtn(CCObject *sender)
{
	CCTips *tip = CCTips::create("ServerMainten");
	addChild(tip, 5000);

	return;
}

void GameOver::onBackToMenu(CCObject *sender)
{
	if (!exitLayer)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/select.ogg");
		exitLayer = CCLayer::create();

		CCSprite *exit_bg = CCSprite::createWithSpriteFrameName("confirm_bg.png");
		exit_bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));

		CCSprite *comfirm_title = CCSprite::createWithSpriteFrameName("confirm_title.png");
		comfirm_title->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 38));

		CCSprite *btm_text = CCSprite::createWithSpriteFrameName("btm_text.png");
		btm_text->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 8));

		CCMenuItem *yes_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("yes_btn1.png"), CCSprite::createWithSpriteFrameName("yes_btn2.png"), this, menu_selector(GameOver::onLeft));
		CCMenuItem *no_btn = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("no_btn1.png"), CCSprite::createWithSpriteFrameName("no_btn2.png"), this, menu_selector(GameOver::onCancel));

		CCMenu *confirm_menu = CCMenu::create(yes_btn, no_btn, nullptr);
		confirm_menu->alignItemsHorizontallyWithPadding(24);
		confirm_menu->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 30));

		exitLayer->addChild(exit_bg, 1);
		exitLayer->addChild(confirm_menu, 2);
		exitLayer->addChild(comfirm_title, 2);
		exitLayer->addChild(btm_text, 2);
		addChild(exitLayer, 500);
	}
};

void GameOver::onLeft(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/confirm.ogg");

	_delegate->_isExiting = true;
	CCDirector::sharedDirector()->popScene();
}

void GameOver::onCancel(CCObject *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("Audio/Menu/cancel.ogg");
	exitLayer->removeFromParent();
	exitLayer = nullptr;
}

GameOver *GameOver::create(CCRenderTexture *snapshoot)
{
	GameOver *pl = new GameOver();
	if (pl && pl->init(snapshoot))
	{
		pl->autorelease();
		return pl;
	}
	else
	{
		delete pl;
		return nullptr;
	}
}
