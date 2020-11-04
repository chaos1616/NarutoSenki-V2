#include "AppDelegate.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "CCLuaEngine.h"
#include "Lua_extensions_CCB.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
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

    // create a scene. it's an autorelease object
    // CCScene *pScene = GameScene::create();

    // run
    // pDirector->runWithScene(pScene);

    // init lua
    CCLuaEngine *pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

    CCLuaStack *pStack = pEngine->getLuaStack();
    lua_State *tolua_s = pStack->getLuaState();
    tolua_extensions_ccb_open(tolua_s);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    pEngine->addSearchPath("lua");
    pEngine->addSearchPath("../lua");
    CCFileUtils::sharedFileUtils()->addSearchPath("lua");
    CCFileUtils::sharedFileUtils()->addSearchPath("../lua");
#endif

    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("../lua/__main__.lua");
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
