#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class CharacterBase;

class Effect : public CCSprite
{
public:
	Effect();
	~Effect();

	virtual bool init(const char *szImage, CCObject *Attacker);
	static Effect *create(const char *szImage, CCObject *Attacker);

	CharacterBase *at;

private:
	void removeEffect();
	void removeFontEffect();
	CCAction *createEffectAnimation(const char *file, int frameCount, float fps, bool isRepeat);
	CCAction *createFontAnimation();
};
