#pragma once
#include "cocos2d.h"
// #include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Data/Config.h"
#include "Data/Types.h"
#include "Data/UnitDefines.h"
#include "Data/Version.h"
#include "Enums/Audio.hpp"
#include "Enums/Character.hpp"
#include "MyUtils/Cocos2dxHelper.hpp"
#include "MyUtils/Keyboard.h"
#include "MyUtils/Macros.h"
#include "Utils/Utils.h"

#include <format>

using namespace cocos2d;
// using namespace cocos2d::extension;
using namespace CocosDenshion;
using namespace std;

#define winSize CCDirector::sharedDirector()->getWinSize()
#define random(x) (rand() % x)
#define setRand() srand((uint32_t)time(0))

#define is_same(__Str1, __Str2) (strcmp(__Str1, __Str2) == 0)
#define to_cstr(var) (std::to_string(var).c_str())
#define to_ccstring(var) CCString::create(std::to_string(var))

// Tile maps (Made with Tiled)
#define GetMapPath(mapId) format("Tiles/{}.tmx", mapId).c_str()
#define GetMapBgPath(mapId) format("Tiles/map_bg{}.png", mapId).c_str()
