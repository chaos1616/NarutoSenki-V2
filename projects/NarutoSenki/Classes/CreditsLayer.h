#pragma once
#include "Defines.h"

class GameLayer;
class CreditsLayer : public CCLayer
{
public:
	CreditsLayer();
	~CreditsLayer();

	bool init();

	CREATE_FUNC(CreditsLayer);

	virtual void keyBackClicked();
};
