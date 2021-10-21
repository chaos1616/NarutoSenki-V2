#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class CharacterBase;

class Effect : public CCSprite
{
public:
	bool init(const char *szImage, CharacterBase *attacker);

	static Effect *create(const char *szImage, CharacterBase *attacker);

private:
	void removeEffect();
	void removeFontEffect();
	CCAction *createEffectAnimation(const char *file, int frameCount, float fps, bool isRepeat);
	CCAction *createFontAnimation();

	CharacterBase *at;
};
