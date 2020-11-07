#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Defines.h"
#include "cocos-ext.h"
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID) 
#include "../../../cocos2dx/platform/android/jni/JniHelper.h" 
#endif  
USING_NS_CC;
USING_NS_CC_EXT;


class GameLayer;

class GameOver : public CCLayer{

public:
	GameOver();
	~GameOver();

	bool	init(CCRenderTexture* snapshoot);
	CC_SYNTHESIZE(bool,_isWin,Win);

	static GameOver*	create(CCRenderTexture* snapshoot);
	
	CCLayer* exitLayer;
	CCLayer* cheatLayer;
	CCSprite* result_bg;

	bool isPosting;
	CCSprite* refreshBtn;

	CCMenuItem* upload_btn;

	//CC_SYNTHESIZE_RETAIN(CCString*,detailRecord,DetialRecord);
	 std::string detailRecord;
	float finnalScore;
	CC_SYNTHESIZE_RETAIN(CCString*,resultChar,ResultChar);

private:
	void	onBackToMenu(CCObject* sender);
	void	listResult();
	void	onCancel(CCObject* sender);
	void	onLeft(CCObject* sender);
	void	onUPloadBtn(CCObject* sender);
	CC_SYNTHESIZE(GameLayer*,_delegate,Delegate);
	void onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response);
};

