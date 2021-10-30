#pragma once
#include "GameOver.h"
#include "GearLayer.h"
#include "PauseLayer.h"
#include "Data/UnitData.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "glfw3.h"
#include <windows.h>
#define _isPressed(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)
#define isKeyDown(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)
#define getKeyUp(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#include "glfw3.h"
#define _isPressed(__WINDOW__, __KEY__) glfwGetKey(__WINDOW__, __KEY__)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../../../cocos2dx/platform/android/jni/JniHelper.h"
#endif

class BGLayer;
class CharacterBase;
class Hero;
class Flog;
class Tower;
class GameLayer;
class HudLayer;

extern GameLayer *_gLayer;
extern bool _isFullScreen;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
static GLFWwindow *_window = nullptr;
#endif

inline GameLayer *getGameLayer()
{
	return _gLayer;
}

class GameLayer : public CCLayer
{
	using OnHUDInitializedCallback = std::function<void()>;

	friend class LoadLayer;

public:
	GameLayer();
	~GameLayer();

	CCTMXTiledMap *currentMap;
	CharacterBase *currentPlayer;
	CCPoint spawnPoint;

	uint32_t _second;
	uint32_t _minute;
	int mapId;

	const char *kName;
	const char *aName;
	int kEXPBound;
	int aEXPBound;

	bool _isAttackButtonRelease;
	bool _hasSpawnedGuardian;
	// int _guardianNum;
	vector<Flog *> _KonohaFlogArray;
	vector<Flog *> _AkatsukiFlogArray;
	vector<Tower *> _TowerArray;
	vector<Hero *> _CharacterArray;

	bool _isShacking;

	int _playNum;
	void checkBackgroundMusic(float dt);

	CC_SYNTHESIZE(HudLayer *, _hudLayer, HudLayer);
	void onHUDInitialized(const OnHUDInitializedCallback &callback);
	bool isHUDInit();
	void setTowerState(int charNO);

	CC_SYNTHESIZE_RETAIN(CCString *, totalKills, TotalKills);
	CC_SYNTHESIZE_RETAIN(CCString *, totalTM, TotalTM);

	CCSpriteBatchNode *skillEffectBatch;
	CCSpriteBatchNode *damageEffectBatch;
	CCSpriteBatchNode *bulletBatch;
	CCSpriteBatchNode *shadowBatch;

	bool init();
	void initTileMap();
	void initHeros();
	void initFlogs();
	void initTower();
	void initGard();
	void initEffects();

	void updateViewPoint(float dt);
	void updateGameTime(float dt);

	Hero *addHero(CCString *character, CCString *role, CCString *group, CCPoint spawnPoint, int charNo);
	void addFlog(float dt);

	void attackButtonClick(abType type);
	void gearButtonClick(GearType type);
	void attackButtonRelease();

	void JoyStickRelease();
	void JoyStickUpdate(CCPoint direction);

	PROP(bool, _isSkillFinish, SkillFinish);
	void checkTower();

	void onPause();
	void onGear();
	void playGameOpeningAnimation(float dt);
	void onGameStart(float dt);
	void onGameOver(bool isWin);

	void updateHudSkillButtons();
	void setHPLose(float percent);
	void setCKRLose(bool isCRK2);

	void setReport(const char *name1, const char *name2, uint32_t killNum);
	void clearDoubleClick();
	void resetStatusBar();
	void setCoin(const char *value);
	void removeOugisMark(int type);
	void setOugis(CCNode *sender);
	void removeOugis();

	CCNode *ougisChar;
	CharacterBase *controlChar;
	CCLayer *blend;

	void onLeft();

	bool _isSurrender;

	bool _enableGear;
	bool _isOugis2Game;
	bool _isHardCoreGame;
	bool _isRandomChar;

	string playerGroup;
	bool _isStarted;
	bool _isExiting;

	inline const char *getGuardianGroup() { return playerGroup == Konoha ? "AkatsukiCenter" : "KonohaCenter"; }

	bool _isGear;
	bool _isPause;
	GearLayer *_gearLayer;

	CREATE_FUNC(GameLayer);
	static bool checkHasAnyMovement();
	static int getMapCount();

private:
	void onEnter();
	void onExit();

	void setKeyEventHandler();
	void removeKeyEventHandler();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	int _lastPressedMovementKey;

	static void keyEventHandle(GLFWwindow *window, int key, int scancode, int action, int modes);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static void LPFN_ACCELEROMETER_KEYHOOK(UINT message, WPARAM wParam, LPARAM lParam);
#endif

	void invokeAllCallbacks();

	inline CCPoint getCustomSpawnPoint(HeroData &data);

	bool isHUDInitialized = false;
	bool is4V4Mode = false;
	vector<OnHUDInitializedCallback> callbackssList;
};

#define BIND(funcName) std::bind(&funcName, this)
