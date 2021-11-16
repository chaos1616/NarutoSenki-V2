#pragma once
#include "cocos2d.h"
#include "Utils/CCDeprecated.h"
#include "../../../scripting/lua/cocos2dx_support/CCLuaEngine.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <format>
#else
#define FMT_HEADER_ONLY
#define FMT_CONSTEVAL
#include "fmt/core.h"

using namespace fmt;
#endif

using namespace cocos2d;
using namespace std;

#define nameof(varType) #varType
#define typeof(varType) typeid(varType).name()

#define to_uint(str) strtoul(str, nullptr, 10)
#define to_int(str)	 atoi(str)

#define RETURN_FALSE_IF(var) \
	if (var)                 \
		return false;

#define RETURN_TRUE_IF(var) \
	if (var)                \
		return true;

#define get_luastack LuaEngine::defaultEngine()->getLuaStack()
#define lua_getL	 auto L = LuaEngine::defaultEngine()->getLuaStack()->getLuaState();

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
 * Sprite helpers
 */

#define FULL_SCREEN_SPRITE(__SPRITE__) \
	__SPRITE__->setScaleX(winSize.width / __SPRITE__->getContentSize().width);

static inline void addSprites(const string &plistName)
{
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistName.c_str());
}

static inline void removeSprites(const string &plistName)
{
	SpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(plistName.c_str());
}

static inline Sprite *newSprite(const string &spriteName)
{
	return Sprite::createWithSpriteFrameName(spriteName);
}

static inline SpriteFrame *getSpriteFrame(const string &name)
{
	return SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

template <class... _Types>
static inline SpriteFrame *getSpriteFrame(const string_view _Fmt, const _Types &..._Args)
{
	return getSpriteFrame(format(_Fmt, _Args...));
}

#else

// Use fmt lib for not support c++ 20 std::format platform

template <class... _Types>
static inline SpriteFrame *getSpriteFrame(fmt::format_string<_Types...> _Fmt, _Types &&..._Args)
{
	return getSpriteFrame(fmt::format(_Fmt, _Args...));
}

#endif
