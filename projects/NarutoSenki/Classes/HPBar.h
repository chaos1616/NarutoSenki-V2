#pragma once
#include "cocos2d.h"
#include "CharacterBase.h"

class HPBar : public CCSprite
{
	HPBar();
	~HPBar();

	CC_SYNTHESIZE(CharacterBase *, _delegate, Delegate);
	virtual bool init(const char *szImage);
	static HPBar *create(const char *szImage);
	void changeBar(const char *szImage);
	void loseHP(float percent);
	CC_SYNTHESIZE_RETAIN(CCSprite *, hpBottom, HPBottom);
	CC_SYNTHESIZE_RETAIN(CCSprite *, hpBar, HPBAR);
};
