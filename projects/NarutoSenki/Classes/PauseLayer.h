#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class PauseLayer : public CCLayer
{
public:
	bool init(CCRenderTexture *snapshoot);

	CCMenu *pauseMenu = nullptr;
	CCMenu *soundMenu = nullptr;
	CCMenu *preMenu = nullptr;
	CCLayer *exitLayer = nullptr;
	CCMenuItem *bgm_btn = nullptr;
	CCMenuItem *voice_btn = nullptr;
	CCMenuItem *pre_btn = nullptr;

	static PauseLayer *create(CCRenderTexture *snapshoot);

private:
	void onResume(CCObject *sender);
	void onBackToMenu(CCObject *sender);
	void onLeft(CCObject *sender);
	void onCancel(CCObject *sender);
	void onBGM(CCObject *sender);
	void onPreload(CCObject *sender);
	void onVoice(CCObject *sender);
};
