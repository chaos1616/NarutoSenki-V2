#pragma once
#include "Defines.h"

using namespace std;

#define u8 char

namespace GameMode
{
    // 3 VS 3 (With gears)
    const u8 Classic = 0;
    // 4 VS 4 (Without gears)
    const u8 HardCore = 1;
    // 4 VS 4 (With gears)
    const u8 NotHardCore = 2;
    // 3 VS 3 ()
    const u8 InDev = 3;
    // 3 VS 3 ()
    const u8 Unknown = 4;
} // namespace GameMode

struct GameModeData
{
public:
    CCSprite *background;
    CCString *title;
    CCString *description;

    static const GameModeData &from(const char *path);
};

class GameModeLayer : public CCLayer
{
public:
    GameModeLayer();
    ~GameModeLayer();

    bool init();

    bool pushMode(const GameModeData &data);
    bool removeMode();

private:
    vector<GameModeData> modes;
};
