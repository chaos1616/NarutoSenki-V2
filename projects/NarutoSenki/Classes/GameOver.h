#pragma once
#include "Defines.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../../../cocos2dx/platform/android/jni/JniHelper.h"
#endif

class GameOver : public Layer
{
public:
	GameOver();
	~GameOver();

	bool init(RenderTexture *snapshoot);

	PROP(bool, _isWin, Win);

	Layer *exitLayer;
	Layer *cheatLayer;
	Sprite *result_bg;

	bool isPosting;
	Sprite *refreshBtn;
	MenuItem *upload_btn;

	// CC_SYNTHESIZE_RETAIN(CCString*,detailRecord,DetialRecord);
	string detailRecord;
	float finnalScore;

	static GameOver *create(RenderTexture *snapshoot);

private:
	const char *resultChar;

	void onBackToMenu(Ref *sender);
	void listResult();
	void onCancel(Ref *sender);
	void onLeft(Ref *sender);
	void onUPloadBtn(Ref *sender);
};
