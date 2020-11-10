#include "MyUtils/Cocos2dxHelper.hpp"
#include "StartMenu.h"
#include <time.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "../../../cocos2dx/platform/android/jni/JniHelper.h"
#endif

SelectLayer::SelectLayer()
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
	_isRandomChar = false;

	_playerSelect = NULL;
	_com1Select = NULL;
	_com2Select = NULL;
	selectButtons = NULL;
}

SelectLayer::~SelectLayer()
{
	CC_SAFE_RELEASE(selectButtons);
}

void SelectLayer::setSelected(CCObject *sender)
{
	SelectButton *btn = (SelectButton *)sender;
	if (_selectImg)
	{
		_selectImg->setPosition(ccp(btn->getPositionX() - 2, btn->getPositionY() - 2));
	}

	if (!enableCustomSelect && _playerSelect)
	{
		return;
	}

	_selectHero = btn->getCharName()->getCString();

	CCActionInterval *fd = CCFadeOut::create(1.0f);
	CCAction *seq = CCRepeatForever::create(CCSequence::create(fd, fd->reverse(), NULL));

	if (!_playerSelect)
	{

		if (btn->_clickTime >= 2)
		{
			_playerSelect = _selectHero;

			if (!enableCustomSelect)
			{
				_selectImg->removeFromParent();
				_selectImg = NULL;
			}
			else
			{
				_comLabel1->runAction(seq);
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
		_comSelector1->setDisplayFrame(frame);

		if (btn->_clickTime >= 2)
		{
			_com1Select = _selectHero;

			_comLabel1->stopAllActions();
			_comLabel1->setOpacity(255);
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("com_label2.png");
			_comLabel1->setDisplayFrame(frame);
			_comLabel2->runAction(seq);
		}
	}
	else if (!_com2Select)
	{

		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s_small.png", _selectHero)->getCString());
		_comSelector2->setDisplayFrame(frame);

		if (btn->_clickTime >= 2)
		{
			_com2Select = _selectHero;

			_comLabel2->stopAllActions();
			_comLabel2->setOpacity(255);
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("com_label2.png");
			_comLabel2->setDisplayFrame(frame);

			_selectImg->removeFromParent();
			_selectImg = NULL;
		}
	}
}

void SelectLayer::onGameStart()
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
			int num2 = _selectList->count();
			int index = random(num2);
			tmpChar = (CCString *)_selectList->objectAtIndex(index);
			do
			{
				srand((int)time(0));
				int num = _selectList->count();
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

				if (i == 0 && _com1Select)
				{
					hero = CCString::create(_com1Select);
				}
				else if (i == 1 && _com2Select)
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

		loadLayer->_isRandomChar = _isRandomChar;
		loadLayer->preloadAudio();
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, loadScene));
	}
}

void SelectLayer::keyBackClicked()
{
	lua_call_func("backToStartMenu")
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
