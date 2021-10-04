#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class CharacterBase;

class Effect : public CCSprite
{
public:
	Effect();
	~Effect();

	virtual bool init(const char *szImage, CCObject *attacker);
	static Effect *create(const char *szImage, CCObject *attacker);

	CharacterBase *at;

private:
	void removeEffect();
	void removeFontEffect();
	CCAction *createEffectAnimation(const char *file, int frameCount, float fps, bool isRepeat);
	CCAction *createFontAnimation();
};
