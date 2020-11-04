#include "Defines.h"
#include "StartMenu.h"
#include "MyUtils/KTools.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#include "glfw3.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "windows.h"
#endif

class GameScene : public CCScene
{
public:
	GameScene(void);
	~GameScene(void);

	virtual bool init();

	CREATE_FUNC(GameScene);
	CCLayer *introLayer;

	CC_SYNTHESIZE(StartMenu *, _menuLayer, StartMenu);
	void onPlayEffect2();
	void onFinish();
	void onLogo();
	void onPush(CCObject *sender);

	CCMenu *logoMenu;
	CCMenu *pushMenu;
	void onLogoClick(CCObject *sender);
};
