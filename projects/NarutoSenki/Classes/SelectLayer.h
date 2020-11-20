#pragma once
#include "Defines.h"
#include "LoadLayer.h"

class SelectLayer : public CCLayer
{
public:
	SelectLayer();
	~SelectLayer();

	static SelectLayer *create();

	const char *_selectHero;
	const char *_playerSelect;
	const char *_com1Select;
	const char *_com2Select;

	PROP(bool, _isRandomChar, IsRandomChar);

	void setSelectHero(const char *var) { _playerSelect = var; };
	void setCom1Select(const char *var) { _com1Select = var; };
	void setCom2Select(const char *var) { _com2Select = var; };

	void setSelectList(CCArray *var) { _selectList = var; };

	void onGameStart();

	virtual void keyBackClicked();

private:
	bool isStart;

	CCArray *_selectList;

	void onBackToMenu(CCObject *sender);
};
