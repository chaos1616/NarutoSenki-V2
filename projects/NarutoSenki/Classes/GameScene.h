#include "Defines.h"
#include "StartMenu.h"
#include "MyUtils/KTools.h"
#include "SimpleAudioEngine.h"

class GameScene : public CCScene
{
public:
	virtual bool init();

	CREATE_FUNC(GameScene);

	CC_SYNTHESIZE(CCLayer *, introLayer, IntroLayer);

	void onFinish();

	CC_SYNTHESIZE(CCMenu *, logoMenu, LogoMenu);
	void onLogoClick(CCObject *sender);
};
