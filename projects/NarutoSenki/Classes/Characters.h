#ifndef __CHARACTERS__
#define __CHARACTERS__
#include "cocos2d.h"
#include "Element.h"

#include <utility>
#include <functional>

USING_NS_CC;

class Hero : public HeroElement
{
private:
    virtual void perform(){};
public:
	bool init()
    {
	    bool bRet = false;
        do
        {
            CC_BREAK_IF(!HeroElement::init());
            this->setAnchorPoint(ccp(0.5, 0));

            //this->schedule(schedule_selector(Hero::neicun),0.5f);
            bRet = true;
        } while (0);

        return bRet;
    };

	virtual void setAI(float dt) { perform(); };
	void setID(CCString *character, CCString *role, CCString *group){};
};
#endif