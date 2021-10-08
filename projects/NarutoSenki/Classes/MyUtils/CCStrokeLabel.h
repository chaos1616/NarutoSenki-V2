#pragma once
#include "cocos2d.h"
#include "label_nodes/CCLabelTTF.h"

using namespace cocos2d;

class CCStrokeLabel : public CCNode
{
public:
	bool init();

	float getStrokeSize();
	void setStrokeSize(float strokeSize);

	static CCStrokeLabel *create(CCLabelTTF *labelTTF, ccColor3B fullColor, ccColor3B StrokeColor, float strokeSize);

private:
	CCSprite *m_sprite;
	CCLabelTTF *m_label;
	ccColor3B m_fullColor;
	ccColor3B m_StrokeColor;
	float m_strokeSize;
};
