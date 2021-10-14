#pragma once
#include "GameMode/GameModeImpl.h"

class ModeMenuButton;

class GameModeLayer : public CCLayer
{
public:
	static const int kMenuCount = 5;

	CREATE_FUNC(GameModeLayer);

	bool init();
	void backToMenu(CCObject *sender);

	void initModeData();
	bool pushMode(const GameModeData &data);
	void removeMode(const GameModeData &data);
	void selectMode(GameMode mode);

private:
	inline bool setSelect(GameMode mode);

	CCLabelTTF *menuLabel;

	vector<ModeMenuButton *> menuButtons = vector<ModeMenuButton *>(GameMode::_Internal_Max_Length);
	vector<GameModeData> modes = vector<GameModeData>(GameMode::_Internal_Max_Length);
};
