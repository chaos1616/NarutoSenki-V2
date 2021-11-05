#include "CCScrewLayer.h"

void CCScrewLayer::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}

void CCScrewLayer::onExit()
{
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool CCScrewLayer::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	prePosY = 0;
	return true;
}

void CCScrewLayer::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
	// touch area
	CCPoint curPoint = touch->getLocation();
	if (prePosY == 0)
	{
		prePosY = curPoint.y;
	}
	else
	{
		float distanceY = curPoint.y - prePosY;
		if (getPositionY() < totalRow * line_height || distanceY < 0)
		{
			setPositionY(getPositionY() + distanceY);
		}

		prePosY = curPoint.y;
	}
}

void CCScrewLayer::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
	prePosY = 0;

	// CCLOG("y:%f",getPositionY());
	if (getPositionY() > totalRow * line_height - line_height)
	{
		setPositionY(totalRow * line_height);
	}
	if (getPositionY() < minY)
	{
		setPositionY(minY);
	}
}

/*----------------------
init CCScrewItem ;
----------------------*/

void CCScrewItem::onEnter()
{
	CCSprite::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void CCScrewItem::onExit()
{
	CCSprite::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

CCRect CCScrewItem::getRect2()
{
	CCSize size = getContentSize();
	return CCRect(0, 0, size.width, size.height);
}

bool CCScrewItem::containsTouchLocation(CCTouch *touch)
{
	return getRect2().containsPoint(convertTouchToNodeSpace(touch));
}

bool CCScrewItem::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	// touch area
	if (!containsTouchLocation(touch))
		return false;

	return true;
}

void CCScrewItem::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
	linemenu->setVisible(true);
}
