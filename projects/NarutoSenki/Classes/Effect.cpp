#include "Effect.h"
#include "CharacterBase.h"
#include "GameLayer.h"

Effect::Effect()
{
}

Effect::~Effect()
{
}

bool Effect::init(const char *name, CCObject *attacker)
{
	if (!CCSprite::init())
		return false;

	at = (CharacterBase *)attacker;

	if (strcmp(name, "n_hit") == 0 ||
		strcmp(name, "b_hit") == 0)
	{
		initWithSpriteFrameName("red_damge_01.png");
		setAnchorPoint(ccp(0.5f, 0));
		setScale(0.6f);
		float randomY = rand() % 16;
		float randomX = rand() % 4;
		setPosition(ccp(at->getPositionX() + randomX, at->getPositionY() + randomY));
		CCAction *effectAction = createEffectAnimation("red_damge_", 4, 14, false);
		runAction(effectAction);
	}
	else if (strcmp(name, "l_hit") == 0 ||
			 strcmp(name, "f_hit") == 0 ||
			 strcmp(name, "f2_hit") == 0 ||
			 strcmp(name, "c_hit") == 0 ||
			 strcmp(name, "o_hit") == 0 ||
			 strcmp(name, "o2_hit") == 0 ||
			 strcmp(name, "ob_hit") == 0 ||
			 strcmp(name, "ab_hit") == 0 ||
			 strcmp(name, "ac_hit") == 0 ||
			 strcmp(name, "ct_hit") == 0 ||
			 strcmp(name, "ts_hit") == 0 ||
			 strcmp(name, "s_hit") == 0)
	{
		setScale(0.8f);
		initWithSpriteFrameName("red_damge_01.png");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX(), at->getPositionY()));
		CCAction *effectAction = createEffectAnimation("red_damge_", 4, 14, false);
		runAction(effectAction);
	}
	else if (strcmp(name, "bl_hit") == 0 ||
			 strcmp(name, "bc_hit") == 0 ||
			 strcmp(name, "bf_hit") == 0 ||
			 strcmp(name, "sl_hit") == 0)
	{
		initWithSpriteFrameName("blue_damge_01.png");
		//setAnchorPoint(ccp(0.5f,0));
		setScale(0.6f);
		int randomInt = rand() % 30 + 10;
		setRotation(randomInt);
		setPosition(ccp(at->getPositionX(), at->getPositionY() + at->getContentSize().height / 2));
		CCAction *effectAction = createEffectAnimation("blue_damge_", 4, 14, false);
		runAction(effectAction);
	}
	else if (strcmp(name, "a_hit") == 0)
	{
		initWithSpriteFrameName("bottom_damage_01.png");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX() + 16, at->getPositionY()));
		CCAction *effectAction = createEffectAnimation("bottom_damage_", 6, 20, false);
		runAction(effectAction);
	}
	else if (strcmp(name, "Kagura") == 0)
	{
		initWithSpriteFrameName("Kagura_01.png");
		CCAction *effectAction = createEffectAnimation("Kagura_", 9, 10, false);
		setAnchorPoint(ccp(0.5f, 0.5f));
		runAction(effectAction);
	}
	else if (strcmp(name, "Hupo") == 0)
	{
		initWithSpriteFrameName("Hupo_01.png");
		CCAction *effectAction = createEffectAnimation("Hupo_", 7, 10, false);
		setAnchorPoint(ccp(0.5f, 0.5f));
		runAction(effectAction);
	}
	else if (strcmp(name, "hp_restore") == 0 ||
			 strcmp(name, "speedUp") == 0)
	{
		initWithSpriteFrameName(CCString::createWithFormat("%s_01.png", name)->getCString());
		CCAction *effectAction = createEffectAnimation(CCString::createWithFormat("%s_", name)->getCString(), 5, 5, false);
		CCFiniteTimeAction *call = CCCallFunc::create(at, callfunc_selector(CharacterBase::disableEffect));
		CCArray *seqArray = CCArray::create();
		seqArray->addObject(effectAction);
		seqArray->addObject(call);
		CCAction *seq = CCSequence::create(seqArray);
		runAction(seq);
	}
	else if (strcmp(name, "smk") == 0)
	{
		initWithSpriteFrameName("smk_01.png");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(at->getPosition());
		CCAction *effectAction = createEffectAnimation("smk_", 5, 10, false);
		runAction(effectAction);
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isVoice") != false)
		{
			SimpleAudioEngine::sharedEngine()->playEffect("Audio/Effect/poof.ogg");
		}
	}
	else if (strcmp(name, "tishen") == 0)
	{
		initWithSpriteFrameName("tishen_01.png");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(at->getPosition());
		CCAction *effectAction = createEffectAnimation("tishen_", 6, 10, false);
		runAction(effectAction);
	}
	else if (strcmp(name, "stun") == 0)
	{

		initWithSpriteFrameName("smk_01.png");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX(), at->getPositionY() + at->getContentSize().height - 2));
		CCAction *effectAction = createEffectAnimation("stun_", 5, 5, false);
		runAction(effectAction);
	}
	else if (strcmp(name, "DarkFlame") == 0)
	{

		initWithSpriteFrameName("DarkFlame_Effect_01.png");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX(), at->getPositionY()));
		CCAction *effectAction = createEffectAnimation("DarkFlame_Effect_", 5, 10, true);
		runAction(effectAction);

		CCDelayTime *delay = CCDelayTime::create(2.8f);
		CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(Effect::removeEffect));
		CCAction *seq = CCSequence::create(delay, call, nullptr);
		runAction(seq);
	}
	else if (strcmp(name, "Bagua") == 0)
	{
		initWithSpriteFrameName("Bagua_01.png");
		CCAction *effectAction = createEffectAnimation("Bagua_", 24, 10, false);
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX() + 2, at->getPositionY() - 52));
		runAction(effectAction);
	}
	else if (strcmp(name, "Kujiyose") == 0)
	{
		initWithSpriteFrameName("Kujiyose.png");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX(), at->getPositionY() - getContentSize().height / 2));
		CCDelayTime *delay = CCDelayTime::create(0.3f);
		CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(Effect::removeEffect));
		CCAction *seq = CCSequence::create(delay, call, nullptr);
		runAction(seq);
	}
	else if (strcmp(name, "kazi") == 0)
	{
		initWithSpriteFrameName("kazi.png");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX() + (at->_isFlipped ? -32 : 32),
						at->getPositionY() + at->getContentSize().height / 2));
		CCActionInterval *su = CCScaleBy::create(0.1f, 1.2f);
		CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(Effect::removeEffect));
		CCAction *seq = CCSequence::create(su, su->reverse(), call, nullptr);
		runAction(seq);
	}
	else if (strcmp(name, "sharingan") == 0 ||
			 strcmp(name, "sharingan2") == 0 ||
			 strcmp(name, "sharingan3") == 0 ||
			 strcmp(name, "sharingan4") == 0)
	{
		initWithSpriteFrameName(CCString::createWithFormat(("%s.png"), name)->getCString());
		setPosition(ccp(at->getPositionX() + (at->_isFlipped ? -32 : 32),
						at->getPositionY() + at->getContentSize().height));
		CCActionInterval *rt = CCRotateBy::create(0.3f, 180, 180);
		CCActionInterval *su = CCScaleBy::create(0.2f, 1.6f);
		CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(Effect::removeEffect));
		CCAction *seq = CCSequence::create(rt, su, call, nullptr);
		runAction(seq);
	}
	else if (strcmp(name, "Hiraishin") == 0 ||
			 strcmp(name, "Hiraishin2") == 0)
	{
		initWithSpriteFrameName(CCString::createWithFormat("%sEffect_01.png", name)->getCString());
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(at->getPosition());
		CCAction *effectAction = createEffectAnimation(CCString::createWithFormat("%sEffect_", name)->getCString(), 4, 10, false);
		runAction(effectAction);
	}
	else if (strcmp(name, "hBuff") == 0)
	{
		initWithSpriteFrameName(CCString::createWithFormat("%s_Effect_01.png", name)->getCString());
		setAnchorPoint(ccp(0.5f, 0));
		CCAction *effectAction = createEffectAnimation(CCString::createWithFormat("%s_Effect_", name)->getCString(), 4, 5, true);
		runAction(effectAction);
	}
	else if (strcmp(name, "sBuff") == 0)
	{
		initWithSpriteFrameName(CCString::createWithFormat("%s_Effect_01.png", name)->getCString());
		setAnchorPoint(ccp(0.5f, 0));
		CCAction *effectAction = createEffectAnimation(CCString::createWithFormat("%s_Effect_", name)->getCString(), 10, 10, true);
		runAction(effectAction);
	}
	else if (strcmp(name, "hsBuff") == 0 ||
			 strcmp(name, "tBuff") == 0)
	{
		initWithSpriteFrameName(CCString::createWithFormat("%s_Effect_01.png", name)->getCString());
		setAnchorPoint(ccp(0.5f, 0));
		CCAction *effectAction = createEffectAnimation(CCString::createWithFormat("%s_Effect_", name)->getCString(), 13, 10, true);
		runAction(effectAction);
	}
	else if (strcmp(name, "dcBuff") == 0)
	{
		initWithSpriteFrameName(CCString::createWithFormat("%s_Effect_01.png", name)->getCString());
		setAnchorPoint(ccp(0.5f, 0));
		CCAction *effectAction = createEffectAnimation(CCString::createWithFormat("%s_Effect_", name)->getCString(), 11, 10, true);
		runAction(effectAction);
	}
	else if (strcmp(name, "jdBuff") == 0 ||
			 strcmp(name, "bmBuff") == 0)
	{
		initWithSpriteFrameName(CCString::createWithFormat("%s_Effect_01.png", name)->getCString());
		setAnchorPoint(ccp(0.5f, 0));
		CCAction *effectAction = createEffectAnimation(CCString::createWithFormat("%s_Effect_", name)->getCString(), 9, 10, true);
		runAction(effectAction);
	}
	else if (strcmp(name, "dhBuff") == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			CCSprite *ef = CCSprite::createWithSpriteFrameName("FireEffect_01.png");
			ef->setAnchorPoint(ccp(0.5f, 0));
			if (i == 0)
			{
				ef->setPosition(ccp(10, 0));
			}
			else if (i == 1)
			{
				ef->setPosition(ccp(-10, 18));
			}
			else
			{
				ef->setPosition(ccp(10, 34));
			}
			CCAction *effectAction = createEffectAnimation("FireEffect_", 5, 10, true);
			ef->runAction(effectAction);
			addChild(ef);
		}
	}
	else
	{
		CCLOG("Create effect failed by name %s", name);
		return false;
	}

	return true;
}

CCAction *Effect::createEffectAnimation(const char *file, int frameCount, float fps, bool isRepeat)
{
	CCArray *animeFrames = CCArray::create();
	CCString *str;

	for (int i = 1; i < frameCount; i++)
	{
		str = CCString::createWithFormat("%s%02d.png", file, i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
		animeFrames->addObject(frame);
	}

	CCAnimation *tempAnimation = CCAnimation::createWithSpriteFrames(animeFrames, float(1.0 / fps));
	CCAction *tempAction = CCAnimate::create(tempAnimation);
	CCArray *seqArray = CCArray::createWithObject(tempAction);
	CCAction *seq;
	if (isRepeat)
	{
		seq = CCRepeatForever::create(CCSequence::create(seqArray));
	}
	else
	{

		CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(Effect::removeEffect));
		seqArray->addObject(call);
		seq = CCSequence::create(seqArray);
	}

	return seq;
};

CCAction *Effect::createFontAnimation()
{

	CCDelayTime *delay = CCDelayTime::create(0.3f);
	CCFiniteTimeAction *call = CCCallFunc::create(this, callfunc_selector(Effect::removeFontEffect));
	CCAction *seq = CCSequence::create(delay, call, nullptr);

	return seq;
}

void Effect::removeEffect()
{
	if (at->damageEffectCount > 0)
	{
		at->damageEffectCount--;
	}
	stopAllActions();
	removeFromParentAndCleanup(true);
}

void Effect::removeFontEffect()
{
	stopAllActions();
	removeFromParentAndCleanup(true);
}

Effect *Effect::create(const char *szImage, CCObject *attacker)
{
	Effect *ef = new Effect();
	if (ef && ef->init(szImage, attacker))
	{
		ef->autorelease();
		return ef;
	}
	else
	{
		delete ef;
		return nullptr;
	}
}
