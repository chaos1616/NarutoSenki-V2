#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class PauseLayer : public CCLayer
{
public:
	bool init(CCRenderTexture *snapshoot);

	CCMenu *pauseMenu;
	CCMenu *soundMenu;
	CCMenu *preMenu;
	CCLayer *exitLayer;
	CCMenuItem *bgm_btn;
	CCMenuItem *voice_btn;
	CCMenuItem *pre_btn;

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
