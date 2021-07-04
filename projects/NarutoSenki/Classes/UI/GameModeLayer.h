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

    // static const GameModeData &from(const char *path);
};

class GameModeLayer : public CCLayer
{
public:
    CREATE_FUNC(GameModeLayer);

    GameModeLayer();
    ~GameModeLayer();

    bool init();
    void backToMenu();

    bool pushMode(const GameModeData &data);
    void removeMode(const GameModeData &data);

    void onEnterClassicMode();
    void onEnterHardCoreMode();
    void onEnterNotHardCoreMode();
    void onEnterInDevMode();
    void onEnterUnknownMode();

    CC_SYNTHESIZE_RETAIN(CCArray *, _menu_array, Menus);

    const int kMenuCount = 5;

private:
    inline bool setSelect() { return ++tapCount < 2; };

    int tapCount;

    vector<GameModeData> modes;
};
