#pragma once
#include "Defines.h"

class CharacterBase;

class Effect : public CCSprite
{
public:
	bool init(const string &szImage, CharacterBase *attacker);

	static Effect *create(const string &szImage, CharacterBase *attacker);

private:
	CCFiniteTimeAction *createEffectAnimation(const string &file, int frameCount, float fps, bool isRepeat);
	CCFiniteTimeAction *createFontAnimation();
	void removeEffect();
	void removeFontEffect();

	CharacterBase *at;
};
