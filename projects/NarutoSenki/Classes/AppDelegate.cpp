#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "script_support/CCScriptSupport.h"

#include "System/Initializer.hpp"

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
	SimpleAudioEngine::sharedEngine()->end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// 1. initialize lua
	auto pEngine = LuaEngine::defaultEngine();
	CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

	auto pStack = pEngine->getLuaStack();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	pEngine->addSearchPath("../lua");
	FileUtils::sharedFileUtils()->addSearchPath("../lua");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// pStack->setXXTEAKeyAndSign("2dxLua", strlen("2dxLua"), "XXTEA", strlen("XXTEA"));
	pEngine->addSearchPath("lua");
	FileUtils::sharedFileUtils()->addSearchPath("lua");
	CCLOG("------ Android writable path -> %s", FileUtils::sharedFileUtils()->getWritablePath().c_str());
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pEngine->addSearchPath("../../lua");
	FileUtils::sharedFileUtils()->addSearchPath("../../");
	FileUtils::sharedFileUtils()->addSearchPath("../../Resources");
#endif
#ifdef USE_WIN32_CONSOLE
	CCLOG("---------------------------");
	CCLOG("------ DEBUG CONSOLE ------");
	CCLOG("---------------------------\n");

	auto cwd = FileUtils::sharedFileUtils()->getWritablePath();
	string end = "Debug.win32\\";
	// If found use visual studio debug
	// otherwise use visual studio code
	if (cwd.find(end) != string::npos)
	{
		cwd = cwd.substr(0, cwd.length() - end.length());
		auto luaPath = cwd + "projects\\NarutoSenki\\lua";
		auto resPath = cwd + "projects\\NarutoSenki\\Resources";
		auto root = cwd + "projects\\NarutoSenki";
		CCLOG("Lua path: %s", luaPath.c_str());
		CCLOG("Res path: %s", resPath.c_str());
		CCLOG("Root path: %s", root.c_str());
		pEngine->addSearchPath(luaPath.c_str());
		FileUtils::sharedFileUtils()->addSearchPath(luaPath.c_str());
		FileUtils::sharedFileUtils()->addSearchPath(resPath.c_str());
		FileUtils::sharedFileUtils()->addSearchPath(root.c_str());
	}
	CCLOG("Current work path: %s", cwd.c_str());
	CCLOG("---------------------------\n");

#endif

	auto eglView = GLView::sharedOpenGLView();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	// get window settings
	pEngine->executeScriptFile(FileUtils::sharedFileUtils()->fullPathForFilename("window.lua").c_str());

	// 2. initialize window
	bool isFullscreen = false;
	int width = 1280;
	int height = 720;
	const char *title = "Naruto Senki";

	lua_getL;
	lua_getglobal(L, "ENABLE_FULL_SCREEN");
	if (lua_isboolean(L, 1))
		isFullscreen = lua_toboolean(L, 1);
	lua_pop(L, 1);
	lua_getglobal(L, "WINDOW_WIDTH");
	if (lua_isnumber(L, 1))
		width = lua_tointeger(L, 1);
	lua_pop(L, 1);
	lua_getglobal(L, "WINDOW_HEIGHT");
	if (lua_isnumber(L, 1))
		height = lua_tointeger(L, 1);
	lua_pop(L, 1);
	lua_getglobal(L, "WINDOW_TITLE");
	if (lua_isstring(L, 1))
		title = lua_tostring(L, 1);
	lua_pop(L, 1);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	eglView->setViewName(title);
	if (!isFullscreen)
	{
		eglView->setFrameSize(width, height);
	}
	else
	{
		// Set the frame size to the full screen value
		eglView->setFrameSize(eglView->getFullscreenWidth(), eglView->getFullscreenHeight());
		eglView->enterFullscreen(0, 0);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	// TODO: Support Fullscreen
	eglView->setFrameSize(width, height);
	eglView->setTitle(title);
	eglView->setIcon("icon.png");
#endif
#endif

	// initialize director
	Director *pDirector = Director::sharedDirector();

	pDirector->setOpenGLView(eglView);
	// eglView->setDesignResolutionSize(480, 320, kResolutionFixedHeight);

	// turn on display FPS
	pDirector->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	// pDirector->setAnimationInterval(1.0 / 60);

	Internal::initAllSystems();

	// 3. execute main lua script
	string path = FileUtils::sharedFileUtils()->fullPathForFilename("main.lua");
	pEngine->executeScriptFile(path.c_str());

	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	Director::sharedDirector()->stopAnimation();

	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
	Director::sharedDirector()->startAnimation();

	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
