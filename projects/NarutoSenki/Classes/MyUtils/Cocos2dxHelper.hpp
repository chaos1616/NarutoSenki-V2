#pragma once
#include "cocos2d.h"
#include "../../../scripting/lua/cocos2dx_support/CCLuaEngine.h"
using namespace cocos2d;

#define nameof(varType) #varType
#define typeof(varType) typeid(varType).name()

/** PROPERTY is used to declare a protected variable.
 We can use getter to read the variable, and use the setter to change the variable.
 @param varType : the type of variable.
 @param varName : variable name.
 @param funName : "get + funName" is the name of the getter.
 "set + funName" is the name of the setter.
 @warning : The getter and setter are public  inline functions.
 The variables and methods declared after PROPERTY are all public.
 If you need protected or private, please declare.
 */
#define PROPERTY(varType, varName, funName)                      \
protected:                                                       \
	varType varName;                                             \
                                                                 \
public:                                                          \
	virtual varType get##funName(void) const { return varName; } \
	virtual void set##funName(varType var) { varName = var; }

#define addSprites(filePath) CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(filePath)

#define get_luastack CCLuaEngine::defaultEngine()->getLuaStack()
#define lua_getL auto L = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();

#define lua_callfunc(func_name)  \
	lua_getL;                    \
	lua_getglobal(L, func_name); \
	lua_call(L, 0, 0);

#define lua_call_init_func lua_call_handler_auto

#define lua_call_handler_auto                                  \
	if (m_nScriptHandler != 0)                                 \
	{                                                          \
		auto pStack = get_luastack;                            \
		pStack->pushCCObject(this, typeof(this));              \
		pStack->executeFunctionByHandler(m_nScriptHandler, 1); \
		m_nScriptHandler = 0; /* Only called once */           \
	}

#define lua_call_handler                                       \
	if (m_nScriptHandler != 0)                                 \
	{                                                          \
		auto pStack = get_luastack;                            \
		pStack->pushCCObject(this, typeof(this));              \
		pStack->executeFunctionByHandler(m_nScriptHandler, 1); \
	}
