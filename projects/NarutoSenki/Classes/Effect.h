#pragma once
#include "Defines.h"

class CharacterBase;

class Effect : public Sprite
{
public:
	bool init(const string &szImage, CharacterBase *attacker);

	static Effect *create(const string &szImage, CharacterBase *attacker);

private:
	FiniteTimeAction *createEffectAnimation(const string &file, int frameCount, float fps, bool isRepeat);
	FiniteTimeAction *createFontAnimation();
	void removeEffect();
	void removeFontEffect();

	CharacterBase *at;
};
