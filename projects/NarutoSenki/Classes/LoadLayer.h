#pragma once
#include "BGLayer.h"
#include "GameLayer.h"
#include "HudLayer.h"

class CharacterBase;
class Hero;

class LoadLayer : public CCLayer
{
public:
	LoadLayer();
	~LoadLayer();

	bool init();

	int loadNum;

	CC_SYNTHESIZE_RETAIN(GameLayer *, _gameLayer, GameLayer);
	CC_SYNTHESIZE_RETAIN(BGLayer *, _bgLayer, BGLayer);
	CC_SYNTHESIZE_RETAIN(HudLayer *, _hudLayer, HudLayer);

	bool _isHardCoreMode;
	bool _enableGear;

	void preloadAudio();
	void preloadIMG();
	void playBGM(float dt);
	void onLoadFinish(float dt);

	CREATE_FUNC(LoadLayer);
	static void perloadCharIMG(const string &name);
	static void unloadCharIMG(CharacterBase *player);
	static void unloadAllCharsIMG(const vector<Hero *> &players);

private:
	void setLoadingAnimation(const char *player, int index);

	vector<string> loadVector;
};
