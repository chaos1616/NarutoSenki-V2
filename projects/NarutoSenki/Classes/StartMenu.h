#pragma once
#include "SelectLayer.h"
#include "CreditsLayer.h"
#include "UI/GameModeLayer.h"
#include "MyUtils/KTools.h"
#include "MyUtils/CCStrokeLabel.h"
#include "MyUtils/CCScrewLayer.h"

// declare menuButton
enum btnType
{
	Custom,
	Training,
	Exit,
	Credits,
	HardCore
};

class StartMenu;

class MenuButton : public CCSprite, public CCTouchDelegate
{
public:
	MenuButton();
	~MenuButton();

	bool _isTop;
	bool _isBottom;
	btnType _btnType;

	virtual bool init(const char *szImage);
	static MenuButton *create(const char *szImage);

	CCRect getRect();

	void setBtnType(btnType type);
	btnType getBtnType();
	void playSound();

	float prePosY;

	CC_SYNTHESIZE(StartMenu *, _startMenu, Delegate);

protected:
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
	virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);

	inline bool containsTouchLocation(CCTouch *touch);
};

class StartMenu : public CCLayer
{
public:
	StartMenu();
	~StartMenu();

	bool init();

	void onTrainingCallBack();
	void onHardCoreOn(CCObject *sender);
	void onHardCoreOff(CCObject *sender);
	void onHardLayerCallBack();

	void enterCustomMode();
	void enterTrainingMode();
	void enterSelectLayer();

	void onCreditsCallBack();
	void onExitCallBack();

	void onNewsBtn(CCObject *sender);
	void onLoginBtn(CCObject *sender);

	void scrollMenu(int posY);
	CCSprite *menuText;

	CCLayer *hardCoreLayer;

	static const int _pos01 = 48;
	static const int _pos02 = 92;
	static const int _pos03 = 150;

	bool isClockwise;
	bool isDrag;

	CCMenuItem *login_btn;
	void setNotice();

	CCLayer *notice_layer;
	void update(float dt);
	CCLabelTTF *noticeLabel;

	virtual void keyBackClicked();

	void setHandle(LUA_FUNCTION handler) { _handler = handler; }
	void setCheats(int cheats);

	CC_SYNTHESIZE_RETAIN(CCArray *, _menu_array, Menus);
	CREATE_FUNC(StartMenu);

protected:
	void onEnter();
	void onExit();

private:
	int _handler;
};
