#pragma once
#include "Defines.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../../../cocos2dx/platform/android/jni/JniHelper.h"
#endif

class GameLayer;

class GameOver : public CCLayer
{
public:
	GameOver();
	~GameOver();

	bool init(CCRenderTexture *snapshoot);
	PROP(bool, _isWin, Win);

	CCLayer *exitLayer;
	CCLayer *cheatLayer;
	CCSprite *result_bg;

	bool isPosting;
	CCSprite *refreshBtn;
	CCMenuItem *upload_btn;

	//CC_SYNTHESIZE_RETAIN(CCString*,detailRecord,DetialRecord);
	string detailRecord;
	float finnalScore;

	static GameOver *create(CCRenderTexture *snapshoot);

private:
	const char *resultChar;

	void onBackToMenu(CCObject *sender);
	void listResult();
	void onCancel(CCObject *sender);
	void onLeft(CCObject *sender);
	void onUPloadBtn(CCObject *sender);
};
