#pragma once
#include "Defines.h"

class HudLayer;

class JoyStick : public CCSprite, public CCTouchDelegate
{
public:
	CCPoint _direction;
	CCSprite *_joyStickControl;
	CCPoint _defaultPotion;

	bool init();
	void onEnter();
	void onExit();

	void keyUpdate(float direction);
	void keyEnded(float direction);

	CC_SYNTHESIZE(HudLayer *, _delegate, Delegate);

	CREATE_FUNC(JoyStick);

protected:
	bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	void ccTouchMoved(CCTouch *touch, CCEvent *event);
	void ccTouchEnded(CCTouch *touch, CCEvent *event);

	void updateDirectionForTouchLocation(CCTouch *touch);
	void updateJoyStick(float distance, CCPoint direction);
};
