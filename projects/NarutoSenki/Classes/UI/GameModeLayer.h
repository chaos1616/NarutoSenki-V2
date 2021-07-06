#pragma once
#include "Defines.h"
#include "GameMode/GameModeImpl.hpp"

using namespace std;

class GameModeLayer : public CCLayer
{
public:
    CREATE_FUNC(GameModeLayer);

    GameModeLayer();
    ~GameModeLayer();

    bool init();
    void backToMenu();

    void initModeData();
    bool pushMode(const GameModeData &data);
    void removeMode(const GameModeData &data);
    void selectMode(GameMode mode);

    const int kMenuCount = 5;

private:
    inline bool setSelect(GameMode mode);

    CCLabelTTF *menuLabel;

    vector<GameModeData> modes = vector<GameModeData>(GameMode::_Internal_Max_Length);
};
