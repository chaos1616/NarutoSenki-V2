#pragma once
#include "cocos2d.h"
#include "../../../scripting/lua/cocos2dx_support/CCLuaEngine.h"

using namespace cocos2d;

#define nameof(varType) #varType
#define typeof(varType) typeid(varType).name()

#define SAFE_CLEAR_CCARRAY(arr)       \
	if (arr)                     \
	{                            \
		arr->removeAllObjects(); \
		arr = nullptr;           \
	}

#define addSprites(filePath) CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(filePath)
#define removeSprites(filePath) CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(filePath)

#define get_luastack CCLuaEngine::defaultEngine()->getLuaStack()
#define lua_getL auto L = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();

#define lua_call_func(func_name) \
	lua_getL;                    \
	lua_getglobal(L, func_name); \
	lua_call(L, 0, 0);

#define lua_call_init_func lua_call_handler_auto

#define lua_call_handler_auto                         \
	if (m_nScriptHandler != 0)                        \
	{                                                 \
		int handler = m_nScriptHandler;               \
		auto pStack = get_luastack;                   \
		pStack->executeFunctionByHandler(handler, 0); \
		m_nScriptHandler = 0; /* Only called once */  \
	}

#define lua_call_handler(handler) \
	auto pStack = get_luastack;   \
	pStack->executeFunctionByHandler(handler, 0);

/**
 * Sprite extension
 */
static inline CCSpriteFrame *getSrpiteFrame(std::string name)
{
	return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name.c_str());
}

static inline CCSpriteFrame *getSrpiteFrame(const char *name)
{
	return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
}
