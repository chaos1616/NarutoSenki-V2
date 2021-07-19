#pragma once
#include "Defines.h"
#include "GameMode/GameModeImpl.h"

using namespace std;

class ModeMenuButton;

class GameModeLayer : public CCLayer
{
public:
	const int kMenuCount = 5;

	CREATE_FUNC(GameModeLayer);

	GameModeLayer();
	~GameModeLayer();

	bool init();
	void backToMenu(CCObject *sender);

	void initModeData();
	bool pushMode(const GameModeData &data);
	void removeMode(const GameModeData &data);
	void selectMode(GameMode mode);

	void setHandler(int handler) { _handler = handler; }

private:
	inline bool setSelect(GameMode mode);

	CCLabelTTF *menuLabel;

	int _handler;
	vector<ModeMenuButton *> menuButtons = vector<ModeMenuButton *>(GameMode::_Internal_Max_Length);
	vector<GameModeData> modes = vector<GameModeData>(GameMode::_Internal_Max_Length);
};
