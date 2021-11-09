#pragma once
#include "CharacterBase.h"

class HPBar : public Sprite
{
public:
	bool init(const char *szImage);

	void changeBar(const char *szImage);
	void loseHP(float percent);

	PROP(CharacterBase *, _delegate, Delegate);
	CC_SYNTHESIZE_RETAIN(Sprite *, hpBottom, HPBottom);
	CC_SYNTHESIZE_RETAIN(Sprite *, hpBar, HPBAR);

	static HPBar *create(const char *szImage);
};
