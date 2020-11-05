#pragma once
#include "cocos2d.h"
#include "../../../scripting/lua/cocos2dx_support/CCLuaEngine.h"

USING_NS_CC;

#define addSprites(filePath) CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(filePath)

// Lua Heler
#define get_l auto L = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
