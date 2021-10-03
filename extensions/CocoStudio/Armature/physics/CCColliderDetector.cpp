/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCColliderDetector.h"
#include "../CCBone.h"
#include "../utils/CCTransformHelp.h"


NS_CC_EXT_BEGIN

ColliderBody::~ColliderBody()
{
    CC_SAFE_RELEASE(m_pContourData);
}

CCColliderDetector *CCColliderDetector::create()
{
    CCColliderDetector *pColliderDetector = new CCColliderDetector();
    if (pColliderDetector && pColliderDetector->init())
    {
        pColliderDetector->autorelease();
        return pColliderDetector;
    }
    CC_SAFE_DELETE(pColliderDetector);
    return NULL;
}

CCColliderDetector *CCColliderDetector::create(CCBone *bone)
{
    CCColliderDetector *pColliderDetector = new CCColliderDetector();
    if (pColliderDetector && pColliderDetector->init(bone))
    {
        pColliderDetector->autorelease();
        return pColliderDetector;
    }
    CC_SAFE_DELETE(pColliderDetector);
    return NULL;
}

CCColliderDetector::CCColliderDetector()
    : m_pColliderBodyList(NULL)
    , m_bActive(false)
{
}

CCColliderDetector::~CCColliderDetector()
{
    m_pColliderBodyList->removeAllObjects();
    CC_SAFE_DELETE(m_pColliderBodyList);
}

bool CCColliderDetector::init()
{
    m_pColliderBodyList = CCArray::create();
    CCAssert(m_pColliderBodyList, "create m_pColliderBodyList failed!");
    m_pColliderBodyList->retain();
    return true;
}

bool CCColliderDetector::init(CCBone *bone)
{
    init();
    setBone(bone);

    return true;
}

void CCColliderDetector::addContourData(CCContourData *contourData)
{
    ColliderBody *colliderBody = new ColliderBody(contourData);
    m_pColliderBodyList->addObject(colliderBody);
    colliderBody->release();
}

void CCColliderDetector::addContourDataList(CCArray *contourDataList)
{
    CCObject *object = NULL;
    CCARRAY_FOREACH(contourDataList, object)
    {
        addContourData((CCContourData *)object);
    }
}

void CCColliderDetector::removeContourData(CCContourData *contourData)
{
	CCObject *object = NULL;
	CCARRAY_FOREACH(m_pColliderBodyList, object)
	{
		ColliderBody *body = (ColliderBody*)object;
		if (body && body->getContourData() == contourData)
		{
			m_pColliderBodyList->removeObject(body);
		}
	}
}

void CCColliderDetector::removeAll()
{
    m_pColliderBodyList->removeAllObjects();
}


void CCColliderDetector::setActive(bool active)
{
    if (m_bActive == active)
    {
        return;
    }

    m_bActive = active;
}

bool CCColliderDetector::getActive()
{
    return m_bActive;
}

CCArray *CCColliderDetector::getColliderBodyList()
{
    return m_pColliderBodyList;
}

CCPoint helpPoint;

void CCColliderDetector::updateTransform(CCAffineTransform &t)
{
    if (!m_bActive)
    {
        return;
    }

    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pColliderBodyList, object)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;
        CCContourData *contourData = colliderBody->getContourData();

        int num = contourData->vertexList.count();
        CCContourVertex2 **vs = (CCContourVertex2 **)contourData->vertexList.data->arr;

        for (int i = 0; i < num; i++)
        {
            helpPoint.setPoint( vs[i]->x,  vs[i]->y);
            helpPoint = CCPointApplyAffineTransform(helpPoint, t);
        }
    }
}

NS_CC_EXT_END
