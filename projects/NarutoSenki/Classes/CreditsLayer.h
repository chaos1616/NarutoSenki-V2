#pragma once
#include "Defines.h"

class GameLayer;
class CreditsLayer : public CCLayer
{
public:
	bool init();

	void keyBackClicked();

	CREATE_FUNC(CreditsLayer);
};
