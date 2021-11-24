#pragma once
#include "Defines.h"

class Unit;

class Effect : public Sprite
{
public:
	bool init(const string &szImage, Unit *attacker);

	static Effect *create(const string &szImage, Unit *attacker);

private:
	FiniteTimeAction *createEffectAnimation(const string &file, uint16_t frameCount, uint8_t fps, bool isLoop);
	FiniteTimeAction *createFontAnimation();
	void removeEffect();
	void removeFontEffect();

	Unit *at = nullptr;
};
