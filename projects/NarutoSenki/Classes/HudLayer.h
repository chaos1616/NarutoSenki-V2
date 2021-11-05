#pragma once
#include "ActionButton.h"
#include "JoyStick.h"

#define DESKTOP_UI_SCALE 0.8f
#define DESKTOP_UI_MASK_SCALE 0.8f + 0.04f

class MiniIcon : public CCSprite
{
public:
	MiniIcon();
	~MiniIcon();

	bool init(const char *szImage, bool isNotification);

	PROP(int, _charId, CharId);

	void updateMap(CCObject *sender);
	void updateState();
	void updatePosition(CCPoint location);

	static MiniIcon *create(const char *szImage, bool isNotification);

	CCLayer *_delegate = nullptr;
};

struct ReportData
{
	string slayer;
	string dead;
	int char1Id = 0;
	uint32_t num = 0;
	uint32_t kills = 0;

	bool isDisplay = false;
};

class HudLayer : public CCLayer
{
public:
	HudLayer();

	CCSprite *status_bar;
	CCSprite *status_hpbar;
	CCSprite *status_hpMark;
	CCProgressTimer *status_expbar;

	ActionButton *nAttackButton;
	ActionButton *skill1Button;
	ActionButton *skill2Button;
	ActionButton *skill3Button;
	ActionButton *skill4Button;
	ActionButton *skill5Button;

	ActionButton *item1Button;
	CC_SYNTHESIZE_RETAIN(ActionButton *, item2Button, Item2Button);
	CC_SYNTHESIZE_RETAIN(ActionButton *, item3Button, Item3Button);
	CC_SYNTHESIZE_RETAIN(ActionButton *, item4Button, Item4Button);

	CCMenuItemSprite *gearMenuSprite;
	ActionButton *gear1Button;
	ActionButton *gear2Button;
	ActionButton *gear3Button;
	CCSprite *reportSprite;
	CCSprite *reportSPCSprite;

	int _buffCount = 0;

	CCLabelBMFont *hpLabel;
	CCLabelBMFont *expLabel;

	CCLabelBMFont *coinLabel;
	CCLabelBMFont *killLabel;
	CCLabelBMFont *deadLabel;

	CCLabelBMFont *KonoLabel;
	CCLabelBMFont *AkaLabel;

	CCLabelBMFont *gameClock;
	CCMenu *pauseNenu;
	CCMenu *gearMenu;

	CCLayer *miniLayer;
	JoyStick *_joyStick;

	CCTexture2D *texUI;
	CCSpriteBatchNode *uiBatch;

	void setHPLose(float percent);
	void setCKRLose(bool isCRK2);
	void setEXPLose();

	void initHeroInterface();
	void attackButtonClick(abType type);
	void gearButtonClick(GearType type);
	void attackButtonRelease();
	void pauseButtonClick(CCObject *sender);
	void gearButtonClick(CCObject *sender);
	void setReport(const string &slayer, const string &dead, uint32_t killNum);
	void setReportCache();
	void setBuffDisplay(const char *buffName, float buffStayTime);
	void clearSPCReport();
	void clearBuffDisplay(CCSprite *bs);

	void updateBuffDisplay(float dt);
	void updateBuffDisplay2(float dt);
	void stopSPCReport();
	void updateSPCReprot(float dt);
	void setTowerState(int charId);
	void playGameOpeningAnimation();

	CCLabelBMFont *bcdLabel1;
	CCLabelBMFont *bcdLabel2;

	void JoyStickRelease();
	void JoyStickUpdate(CCPoint direction);
	CCSprite *openingSprite;

	CCSprite *createReport(const string &slayer, const string &dead, float &length);
	CCSprite *createSPCReport(uint32_t killNum, int num);

	bool getSkillFinish();
	bool getOugisEnable(bool isCKR2);

	CCLayer *ougisLayer;
	void setOugis(const string &name, Group group);
	void removeOugis();

	bool _isAllButtonLocked;

	void addMapIcon();

	void costCKR(uint32_t value, bool isCKR2);
	void setCoin(const char *value);
	bool offCoin(const char *value);

	bool init();

	void updateGears();
	void initGearButton(const string &charName);

	void initSkillButtons();
	void setSkillButtons(bool isVisable);
	void updateSkillButtons();
	void updateSpecialSkillButtons();
	void resetSkillButtons();

	CREATE_FUNC(HudLayer);

private:
	void onEnter();
	void onExit();

	bool _isInitPlayerHud = false;
	vector<ReportData> _reportListArray;
	vector<MiniIcon *> _towerIconArray;
};
