#include "Effect.h"
#include "CharacterBase.h"
#include "GameLayer.h"

bool Effect::init(const char *name, CharacterBase *attacker)
{
	RETURN_FALSE_IF(!CCSprite::init());

	at = attacker;

	if (is_same(name, "n_hit") ||
		is_same(name, "b_hit"))
	{
		initWithSpriteFrameName("red_damge_01");
		setAnchorPoint(ccp(0.5f, 0));
		setScale(0.6f);
		float randomY = rand() % 16;
		float randomX = rand() % 4;
		setPosition(ccp(at->getPositionX() + randomX, at->getPositionY() + randomY));
		auto effectAction = createEffectAnimation("red_damge_", 4, 14, false);
		runAction(effectAction);
	}
	else if (is_same(name, "l_hit") ||
			 is_same(name, "f_hit") ||
			 is_same(name, "f2_hit") ||
			 is_same(name, "c_hit") ||
			 is_same(name, "o_hit") ||
			 is_same(name, "o2_hit") ||
			 is_same(name, "ob_hit") ||
			 is_same(name, "ab_hit") ||
			 is_same(name, "ac_hit") ||
			 is_same(name, "ct_hit") ||
			 is_same(name, "ts_hit") ||
			 is_same(name, "s_hit"))
	{
		setScale(0.8f);
		initWithSpriteFrameName("red_damge_01");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX(), at->getPositionY()));
		auto effectAction = createEffectAnimation("red_damge_", 4, 14, false);
		runAction(effectAction);
	}
	else if (is_same(name, "bl_hit") ||
			 is_same(name, "bc_hit") ||
			 is_same(name, "bf_hit") ||
			 is_same(name, "sl_hit"))
	{
		initWithSpriteFrameName("blue_damge_01");
		// setAnchorPoint(ccp(0.5f,0));
		setScale(0.6f);
		int randomInt = rand() % 30 + 10;
		setRotation(randomInt);
		setPosition(ccp(at->getPositionX(), at->getPositionY() + at->getContentSize().height / 2));
		auto effectAction = createEffectAnimation("blue_damge_", 4, 14, false);
		runAction(effectAction);
	}
	else if (is_same(name, "a_hit"))
	{
		initWithSpriteFrameName("bottom_damage_01");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX() + 16, at->getPositionY()));
		auto effectAction = createEffectAnimation("bottom_damage_", 6, 20, false);
		runAction(effectAction);
	}
	else if (is_same(name, "Kagura"))
	{
		initWithSpriteFrameName("Kagura_01");
		auto effectAction = createEffectAnimation("Kagura_", 9, 10, false);
		setAnchorPoint(ccp(0.5f, 0.5f));
		runAction(effectAction);
	}
	else if (is_same(name, "Hupo"))
	{
		initWithSpriteFrameName("Hupo_01");
		auto effectAction = createEffectAnimation("Hupo_", 7, 10, false);
		setAnchorPoint(ccp(0.5f, 0.5f));
		runAction(effectAction);
	}
	else if (is_same(name, "hp_restore") ||
			 is_same(name, "speedUp"))
	{
		initWithSpriteFrameName(CCString::createWithFormat("%s_01", name)->getCString());
		auto effectAction = createEffectAnimation(CCString::createWithFormat("%s_", name)->getCString(), 5, 5, false);
		auto call = CallFunc::create(std::bind(&CharacterBase::disableEffect, at));
		auto seqArray = CCArray::create();
		seqArray->addObject(effectAction);
		seqArray->addObject(call);
		auto seq = CCSequence::create(seqArray);
		runAction(seq);
	}
	else if (is_same(name, "smk"))
	{
		initWithSpriteFrameName("smk_01");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(at->getPosition());
		auto effectAction = createEffectAnimation("smk_", 5, 10, false);
		runAction(effectAction);
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isVoice"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("Audio/Effect/poof.ogg");
		}
	}
	else if (is_same(name, "tishen"))
	{
		initWithSpriteFrameName("tishen_01");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(at->getPosition());
		auto effectAction = createEffectAnimation("tishen_", 6, 10, false);
		runAction(effectAction);
	}
	else if (is_same(name, "stun"))
	{
		initWithSpriteFrameName("smk_01");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX(), at->getPositionY() + at->getContentSize().height - 2));
		auto effectAction = createEffectAnimation("stun_", 5, 5, false);
		runAction(effectAction);
	}
	else if (is_same(name, "DarkFlame"))
	{
		initWithSpriteFrameName("DarkFlame_Effect_01");
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX(), at->getPositionY()));
		auto effectAction = createEffectAnimation("DarkFlame_Effect_", 5, 10, true);
		runAction(effectAction);

		auto delay = CCDelayTime::create(2.8f);
		auto call = CallFunc::create(std::bind(&Effect::removeEffect, this));
		auto seq = CCSequence::create(delay, call, nullptr);
		runAction(seq);
	}
	else if (is_same(name, "Bagua"))
	{
		initWithSpriteFrameName("Bagua_01");
		auto effectAction = createEffectAnimation("Bagua_", 24, 10, false);
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX() + 2, at->getPositionY() - 52));
		runAction(effectAction);
	}
	else if (is_same(name, "Kujiyose"))
	{
		initWithSpriteFrameName(name);
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX(), at->getPositionY() - getContentSize().height / 2));
		auto delay = CCDelayTime::create(0.3f);
		auto call = CallFunc::create(std::bind(&Effect::removeEffect, this));
		auto seq = CCSequence::create(delay, call, nullptr);
		runAction(seq);
	}
	else if (is_same(name, "kazi"))
	{
		initWithSpriteFrameName(name);
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(ccp(at->getPositionX() + (at->_isFlipped ? -32 : 32),
						at->getPositionY() + at->getContentSize().height / 2));
		auto su = CCScaleBy::create(0.1f, 1.2f);
		auto call = CallFunc::create(std::bind(&Effect::removeEffect, this));
		auto seq = CCSequence::create(su, su->reverse(), call, nullptr);
		runAction(seq);
	}
	else if (is_same(name, "sharingan") ||
			 is_same(name, "sharingan2") ||
			 is_same(name, "sharingan3") ||
			 is_same(name, "sharingan4"))
	{
		initWithSpriteFrameName(name);
		setPosition(ccp(at->getPositionX() + (at->_isFlipped ? -32 : 32),
						at->getPositionY() + at->getContentSize().height));
		auto rt = CCRotateBy::create(0.3f, 180, 180);
		auto su = CCScaleBy::create(0.2f, 1.6f);
		auto call = CallFunc::create(std::bind(&Effect::removeEffect, this));
		auto seq = CCSequence::create(rt, su, call, nullptr);
		runAction(seq);
	}
	else if (is_same(name, "Hiraishin") ||
			 is_same(name, "Hiraishin2"))
	{
		initWithSpriteFrameName(CCString::createWithFormat("%sEffect_01", name)->getCString());
		setAnchorPoint(ccp(0.5f, 0));
		setPosition(at->getPosition());
		auto effectAction = createEffectAnimation(CCString::createWithFormat("%sEffect_", name)->getCString(), 4, 10, false);
		runAction(effectAction);
	}
	else if (is_same(name, "hBuff"))
	{
		initWithSpriteFrameName(CCString::createWithFormat("%s_Effect_01", name)->getCString());
		setAnchorPoint(ccp(0.5f, 0));
		auto effectAction = createEffectAnimation(CCString::createWithFormat("%s_Effect_", name)->getCString(), 4, 5, true);
		runAction(effectAction);
	}
	else if (is_same(name, "sBuff"))
	{
		initWithSpriteFrameName(CCString::createWithFormat("%s_Effect_01", name)->getCString());
		setAnchorPoint(ccp(0.5f, 0));
		auto effectAction = createEffectAnimation(CCString::createWithFormat("%s_Effect_", name)->getCString(), 10, 10, true);
		runAction(effectAction);
	}
	else if (is_same(name, "hsBuff") ||
			 is_same(name, "tBuff"))
	{
		initWithSpriteFrameName(CCString::createWithFormat("%s_Effect_01", name)->getCString());
		setAnchorPoint(ccp(0.5f, 0));
		auto effectAction = createEffectAnimation(CCString::createWithFormat("%s_Effect_", name)->getCString(), 13, 10, true);
		runAction(effectAction);
	}
	else if (is_same(name, "dcBuff"))
	{
		initWithSpriteFrameName(CCString::createWithFormat("%s_Effect_01", name)->getCString());
		setAnchorPoint(ccp(0.5f, 0));
		auto effectAction = createEffectAnimation(CCString::createWithFormat("%s_Effect_", name)->getCString(), 11, 10, true);
		runAction(effectAction);
	}
	else if (is_same(name, "jdBuff") ||
			 is_same(name, "bmBuff"))
	{
		initWithSpriteFrameName(CCString::createWithFormat("%s_Effect_01", name)->getCString());
		setAnchorPoint(ccp(0.5f, 0));
		auto effectAction = createEffectAnimation(CCString::createWithFormat("%s_Effect_", name)->getCString(), 9, 10, true);
		runAction(effectAction);
	}
	else if (is_same(name, "dhBuff"))
	{
		for (int i = 0; i < 3; i++)
		{
			CCSprite *ef = CCSprite::createWithSpriteFrameName("FireEffect_01");
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
			auto effectAction = createEffectAnimation("FireEffect_", 5, 10, true);
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
		str = CCString::createWithFormat("%s%02d", file, i);
		auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
		animeFrames->addObject(frame);
	}

	auto tempAnimation = CCAnimation::createWithSpriteFrames(animeFrames, 1.0 / fps);
	auto tempAction = CCAnimate::create(tempAnimation);
	auto seqArray = CCArray::createWithObject(tempAction);
	CCAction *seq;
	if (isRepeat)
	{
		seq = CCRepeatForever::create(CCSequence::create(seqArray));
	}
	else
	{
		auto call = CallFunc::create(std::bind(&Effect::removeEffect, this));
		seqArray->addObject(call);
		seq = CCSequence::create(seqArray);
	}

	return seq;
};

CCAction *Effect::createFontAnimation()
{
	auto delay = CCDelayTime::create(0.3f);
	auto call = CallFunc::create(std::bind(&Effect::removeFontEffect, this));
	auto seq = CCSequence::create(delay, call, nullptr);
	return seq;
}

void Effect::removeEffect()
{
	if (at->damageEffectCount > 0)
	{
		at->damageEffectCount--;
	}
	stopAllActions();
	removeFromParent();
}

void Effect::removeFontEffect()
{
	stopAllActions();
	removeFromParent();
}

Effect *Effect::create(const char *szImage, CharacterBase *attacker)
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
