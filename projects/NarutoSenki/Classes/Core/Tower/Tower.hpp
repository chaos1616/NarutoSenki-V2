#pragma once
#include "CharacterBase.h"
#include "HPBar.h"
#include "HudLayer.h"

class Tower : public CharacterBase
{
public:
    CREATE_FUNC(Tower);

    Tower()
    {
    }

    ~Tower()
    {
    }

    bool init()
    {
        bool bRet = false;
        do
        {

            CC_BREAK_IF(!CharacterBase::init());
            setAnchorPoint(ccp(0.5, 0.5));
            scheduleUpdate();
            bRet = true;
        } while (0);

        return bRet;
    }

    void setID(CCString *character, CCString *role, CCString *group)
    {

        setCharacter(character);
        setRole(role);
        setGroup(group);

        CCArray *animationArray = CCArray::create();
        const char *filePath;

        if (strcmp(getCharacter()->getCString(), "KonohaCenter") == 0 || strcmp(getCharacter()->getCString(), "AkatsukiCenter") == 0)
        {
            filePath = "Element/Tower/CenterDate.xml";
        }
        else
        {
            filePath = "Element/Tower/TowerDate.xml";
        }

        KTools::readXMLToArray(filePath, animationArray);

        //init Attribute; & indleFrame

        CCArray *tmpAction = (CCArray *)(animationArray->objectAtIndex(0));
        CCArray *tmpDate = (CCArray *)(tmpAction->objectAtIndex(0));
        idleArray = (CCArray *)(tmpAction->objectAtIndex(1));

        CCString *tmpName;
        CCString *tmpHpMax;
        int tmpWidth;
        int tmpHeight;
        unsigned int tmpSpeed;
        int tmpCombatPoint;

        readDate(tmpDate, tmpName, tmpHpMax, tmpWidth, tmpHeight, tmpSpeed, tmpCombatPoint);
        setMaxHP(CCString::createWithFormat("%ld", to_uint(tmpHpMax->getCString())));
        setHP(CCString::create(getMaxHP()->getCString()));

        setHeight(tmpHeight);
        setWalkSpeed(tmpSpeed);

        if (!getCKR() && !getCKR2())
        {
            setCKR(CCString::create("0"));
            setCKR2(CCString::create("0"));
        }

        //init DeadFrame
        tmpAction = (CCArray *)(animationArray->objectAtIndex(6));
        deadArray = (CCArray *)(tmpAction->objectAtIndex(1));

        setCoin(CCString::create("50"));

        initAction();

        CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CharacterBase::acceptAttack), "acceptAttack", nullptr);
    }

    void initAction()
    {
        setDeadAction(createAnimation(deadArray, 10.0f, false, false));
        setIdleAction(createAnimation(idleArray, 5.0, true, false));
    }

    void setHPbar()
    {

        if (strcmp(getGroup()->getCString(), _delegate->currentPlayer->getGroup()->getCString()) != 0)
        {
            _hpBar = HPBar::create("hp_bar_r.png");
        }
        else
        {
            _hpBar = HPBar::create("hp_bar.png");
        }
        _hpBar->getHPBAR()->setPosition(ccp(1, 1));
        _hpBar->setPositionY(getHeight());
        _hpBar->setDelegate(this);
        addChild(_hpBar);
    }

    void dealloc()
    {
        unschedule(schedule_selector(CharacterBase::setAI));
        setActionState(State::DEAD);
        stopAllActions();

        CCObject *pObject;
        CCArray *list;
        for (int i = 0; i < 2; i++)
        {
            if (i == 0)
            {
                list = _delegate->_KonohaFlogArray;
            }
            else if (i == 1)
            {
                list = _delegate->_AkatsukiFlogArray;
            }

            CCARRAY_FOREACH(list, pObject)
            {
                CharacterBase *tempFlog = (CharacterBase *)pObject;
                if (tempFlog->_mainTarget)
                {
                    if (tempFlog->_mainTarget == (CharacterBase *)this)
                    {
                        tempFlog->_mainTarget = nullptr;
                    }
                }
            }
        }

        int index = _delegate->_TowerArray->indexOfObject(this);
        _delegate->_TowerArray->removeObjectAtIndex(index);
        // _delegate->getHudLayer()->setTowerState(getCharNO());
        _delegate->setTowerState(getCharNO());
        _delegate->checkTower();
        removeFromParentAndCleanup(true);
    }
};
