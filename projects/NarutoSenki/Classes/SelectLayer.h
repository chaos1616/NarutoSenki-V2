#pragma once
#include "Defines.h"
#include "LoadLayer.h"

class SelectLayer : public CCLayer
{
public:
	static SelectLayer *create();

	SelectLayer();
	~SelectLayer();

	const char *_selectHero = nullptr;
	const char *_playerSelect = nullptr;
	const char *_com1Select = nullptr;
	const char *_com2Select = nullptr;
	const char *_com3Select = nullptr;
	CCArray *_selectList;

	void setSelectHero(const char *var) { _playerSelect = var; };
	void setCom1Select(const char *var) { _com1Select = var; };
	void setCom2Select(const char *var) { _com2Select = var; };
	void setCom3Select(const char *var) { _com3Select = var; };
	void setSelectList(CCArray *var) { _selectList = var; };

	void onGameStart();
	void setPlayerSelected(const char *charName){};

	void keyBackClicked();

private:
	bool isStart;

	void onBackToMenu(CCObject *sender);
};
