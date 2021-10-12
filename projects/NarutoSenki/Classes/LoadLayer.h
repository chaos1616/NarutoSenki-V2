#pragma once
#include "BGLayer.h"
#include "GameLayer.h"
#include "HudLayer.h"

class CharacterBase;

class LoadLayer : public CCLayer
{
public:
	LoadLayer();
	~LoadLayer();

	bool init();

	int loadNum;
	CCArray *tempHeros;

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
	static void perloadCharIMG(const char *player);
	static void unloadCharIMG(const CharacterBase *player);

private:
	void setLoadingAnimation(const char *player, int index);

	std::vector<std::string> loadVector;
};
