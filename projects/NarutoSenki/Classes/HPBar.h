#pragma once
#include "CharacterBase.h"

class HPBar : public CCSprite
{
public:
	HPBar();
	~HPBar();
	static HPBar *create(const char *szImage);

	bool init(const char *szImage);

	void changeBar(const char *szImage);
	void loseHP(float percent);

	CC_SYNTHESIZE(CharacterBase *, _delegate, Delegate);
	CC_SYNTHESIZE_RETAIN(CCSprite *, hpBottom, HPBottom);
	CC_SYNTHESIZE_RETAIN(CCSprite *, hpBar, HPBAR);
};
