#pragma once
#include "Core/Unit.h"

class HPBar : public Sprite
{
public:
	bool init(const char *szImage);

	void changeBar(const char *szImage);
	void loseHP(float percent);

	PROP(Unit *, _delegate, Delegate);
	PROP_PTR(Sprite, hpBottom, HPBottom);
	PROP_PTR(Sprite, hpBar, HPBAR);

	static HPBar *create(const char *szImage);
};
