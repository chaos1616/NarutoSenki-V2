#pragma once
#include "cocos2d.h"
#include "../../../scripting/lua/cocos2dx_support/CCLuaEngine.h"

USING_NS_CC;

#define addSprites(filePath) CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(filePath)

#define get_L auto L = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
#define lua_getL auto L = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();

#define lua_call(func_name)      \
    lua_getL;                    \
    lua_getglobal(L, func_name); \
    lua_pushlightuserdata(this); \
    lua_call(L, 0, 0);\
