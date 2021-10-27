#pragma once
#include "cocos2d.h"
#include "../../../scripting/lua/cocos2dx_support/CCLuaEngine.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <format>
#endif

using namespace cocos2d;
using namespace std;

#define nameof(varType) #varType
#define typeof(varType) typeid(varType).name()

#define to_uint(str) strtoul(str, nullptr, 10)
#define to_int(str) atoi(str)

#define RETURN_FALSE_IF(var) \
	if (var)                 \
		return false;

#define RETURN_TRUE_IF(var) \
	if (var)                \
		return true;

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

#define FULL_SCREEN_SPRITE(__SPRITE__) \
	__SPRITE__->setScaleX(winSize.width / __SPRITE__->getContentSize().width);

inline CCSpriteFrame *getSpriteFrame(const string &name)
{
	return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name.c_str());
}

inline CCSpriteFrame *getSpriteFrame(CCString *name)
{
	return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

template <class... _Types>
inline CCSpriteFrame *getSpriteFrame(const string_view _Fmt, const _Types &..._Args)
{
	return getSpriteFrame(format(_Fmt, _Args...));
}

#else

// For not support c++ 20 std::format platform
inline string format(const char *fmt, ...)
{
	return CCString::createWithFormat(fmt, va_list())->m_sString;
}

inline CCSpriteFrame *getSpriteFrame(const char *fmt, ...)
{
	return getSpriteFrame(format(fmt, va_list()));
}

#endif
