#pragma once
#include "Defines.h"

class AppDelegate : private CCApplication
{
public:
	AppDelegate();
	~AppDelegate();

	bool applicationDidFinishLaunching();
	void applicationDidEnterBackground();
	void applicationWillEnterForeground();
};
