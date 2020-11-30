#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "Lua_extensions_CCB.h"
#include "script_support/CCScriptSupport.h"

#include "Defines.h"
#include "GameScene.h"

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
	SimpleAudioEngine::sharedEngine()->end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();

	pDirector->setOpenGLView(pEGLView);
	// pEGLView->setDesignResolutionSize(480, 320, kResolutionFixedHeight);

	// turn on display FPS
	pDirector->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	// pDirector->setAnimationInterval(1.0 / 60);

	// init lua
	CCLuaEngine *pEngine = CCLuaEngine::defaultEngine();
	CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

	CCLuaStack *pStack = pEngine->getLuaStack();
	lua_State *tolua_s = pStack->getLuaState();
	tolua_extensions_ccb_open(tolua_s);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	pEngine->addSearchPath("../lua");
	CCFileUtils::sharedFileUtils()->addSearchPath("../lua");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	pStack->setXXTEAKeyAndSign("2dxLua", strlen("2dxLua"), "XXTEA", strlen("XXTEA"));
	pEngine->addSearchPath("lua");
	CCFileUtils::sharedFileUtils()->addSearchPath("lua");
	CCLOG("------ Android WritablePath -> %s", CCFileUtils::sharedFileUtils()->getWritablePath().c_str());
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pEngine->addSearchPath("../../lua");
	CCFileUtils::sharedFileUtils()->addSearchPath("../../");
	CCFileUtils::sharedFileUtils()->addSearchPath("../../Resources");
#endif
#ifdef USE_WIN32_CONSOLE
	CCLOG("---------------------------");
	CCLOG("------ DEBUG CONSOLE ------");
	CCLOG("---------------------------\n");

	auto cwd = CCFileUtils::sharedFileUtils()->getWritablePath();
	std::string end = "Debug.win32\\";
	cwd = cwd.substr(0, cwd.length() - end.length());
	CCLOG("Current work path -> %s", cwd.c_str());

	auto luaPath = cwd + "projects\\NarutoSenki\\lua";
	auto resPath = cwd + "projects\\NarutoSenki\\Resources";
	auto root = cwd + "projects\\NarutoSenki";
	CCLOG("Lua path -> %s", luaPath.c_str());
	CCLOG("Res path -> %s", resPath.c_str());
	CCLOG("Root path -> %s", root.c_str());
	CCLOG("---------------------------");
	CCLOG("\n\n");

	pEngine->addSearchPath(luaPath.c_str());
	CCFileUtils::sharedFileUtils()->addSearchPath(luaPath.c_str());
	CCFileUtils::sharedFileUtils()->addSearchPath(resPath.c_str());
	CCFileUtils::sharedFileUtils()->addSearchPath(root.c_str());
#endif

	std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("main.lua");
	pEngine->executeScriptFile(path.c_str());

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{

	CCDirector::sharedDirector()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
