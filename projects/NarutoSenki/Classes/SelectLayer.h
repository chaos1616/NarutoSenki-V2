#pragma once
#include "Defines.h"
#include "LoadLayer.h"
#include "SkillLayer.h"

class SelectLayer : public CCLayer
{
public:
	SelectLayer();
	~SelectLayer();

	static SelectLayer *create();

	void setSelected(CCObject *sender);

	const char *_selectHero;
	const char *_playerSelect;
	const char *_com1Select;
	const char *_com2Select;

	PROP(CCArray *, selectButtons, SelectButtons);
	PROP(bool, _isRandomChar, IsRandomChar);

	void setSelectHero(const char *var) { _selectHero = var; };

	void setSelectList(CCArray *var) { _selectList = var; };
	void setComSelector1(CCSprite *var) { _comSelector1 = var; };
	void setComLabel1(CCSprite *var) { _comLabel1 = var; };
	void setComSelector2(CCSprite *var) { _comSelector2 = var; };
	void setComLabel2(CCSprite *var) { _comLabel2 = var; };
	void setHeroHalf(CCSprite *var) { _heroHalf = var; };
	void setHeroName(CCSprite *var) { _heroName = var; };
	void setSelectImg(CCSprite *var) { _selectImg = var; };

	void onGameStart();

	virtual void keyBackClicked();

private:
	bool isStart;

	CCArray *_selectList;

	CCSprite *_comSelector1;
	CCSprite *_comLabel1;
	CCSprite *_comSelector2;
	CCSprite *_comLabel2;

	CCSprite *_heroHalf;
	CCSprite *_heroName;
	CCSprite *_selectImg;

	void onBackToMenu(CCObject *sender);
};
