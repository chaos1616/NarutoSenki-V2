#pragma once
#include "cocos2d.h"

class AppDelegate : private cocos2d::CCApplication
{
public:
	AppDelegate();
	~AppDelegate();

	bool applicationDidFinishLaunching();
	void applicationDidEnterBackground();
	void applicationWillEnterForeground();
};
