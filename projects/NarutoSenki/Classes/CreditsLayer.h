#pragma once
#include "Defines.h"

class CreditsLayer : public CCLayer
{
public:
	bool init();

	CREATE_FUNC(CreditsLayer);

private:
	void onEnterTransitionDidFinish();

	void keyBackClicked();
};
