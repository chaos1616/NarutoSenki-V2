#pragma once
#include "CharacterBase.h"
#include "HPBar.h"

class Flog : public CharacterBase
{
public:
    float _mainPosY;
    float _randomPosX;
    float _randomPosY;

    CREATE_FUNC(Flog);

    Flog()
    {
        _randomPosX = 0;
        _randomPosY = 0;
    }

    ~Flog()
    {
        CC_SAFE_RELEASE(callValue);
        CC_SAFE_RELEASE(_nattackType);
        CC_SAFE_RELEASE(_damageArray);
    }

    bool init()
    {
        bool bRet = false;
        do
        {

            CC_BREAK_IF(!CharacterBase::init());
            setAnchorPoint(ccp(0.5, 0));
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

        filePath = CCString::createWithFormat("Element/Flog/%s.xml", getCharacter()->getCString())->getCString();

        KTools::readXMLToArray(filePath, animationArray);

        //init Attribute; & indleFrame

        CCArray *tmpAction = (CCArray *)(animationArray->objectAtIndex(0));
        CCArray *tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
        idleArray = (CCArray *)(tmpAction->objectAtIndex(1));

        CCString *tmpName;
        CCString *tmpHpMax;
        int tmpWidth;
        int tmpHeight;
        unsigned int tmpSpeed;
        int tmpCombatPoint;

        readData(tmpData, tmpName, tmpHpMax, tmpWidth, tmpHeight, tmpSpeed, tmpCombatPoint);
        setMaxHP(CCString::createWithFormat("%ld", to_uint(tmpHpMax->getCString())));
        setHP(CCString::create(getMaxHP()->getCString()));
        setHeight(tmpHeight);
        setWalkSpeed(tmpSpeed);

        setKillNum(CCString::createWithFormat("%d", 0));

        if (!getCKR() && !getCKR2())
        {
            setCKR(CCString::create("0"));
            setCKR2(CCString::create("0"));
        }

        //init WalkFrame
        tmpAction = (CCArray *)(animationArray->objectAtIndex(1));
        walkArray = (CCArray *)(tmpAction->objectAtIndex(1));

        //init HurtFrame
        tmpAction = (CCArray *)(animationArray->objectAtIndex(2));
        hurtArray = (CCArray *)(tmpAction->objectAtIndex(1));

        //init AirHurtFrame
        tmpAction = (CCArray *)(animationArray->objectAtIndex(3));
        airHurtArray = (CCArray *)(tmpAction->objectAtIndex(1));

        //init KnockDownFrame
        tmpAction = (CCArray *)(animationArray->objectAtIndex(4));
        knockDownArray = (CCArray *)(tmpAction->objectAtIndex(1));

        //init FloatFrame
        tmpAction = (CCArray *)(animationArray->objectAtIndex(5));
        floatArray = (CCArray *)(tmpAction->objectAtIndex(1));

        //init DeadFrame
        tmpAction = (CCArray *)(animationArray->objectAtIndex(6));
        deadArray = (CCArray *)(tmpAction->objectAtIndex(1));

        //init nAttack data & Frame Array
        tmpAction = (CCArray *)(animationArray->objectAtIndex(7));
        tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
        unsigned int tmpCD;
        CCString *tmpValue;
        readData(tmpData, _nattackType, tmpValue, _nattackRangeX, _nattackRangeY, tmpCD, tmpCombatPoint);
        setnAttackValue(tmpValue);
        _nattackType->retain();
        nattackArray = (CCArray *)(tmpAction->objectAtIndex(1));

        _damageArray = CCArray::create();
        _damageArray->retain();

        setCoin(CCString::create("50"));

        initAction();
        CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CharacterBase::acceptAttack), "acceptAttack", nullptr);
    }

    void initAction()
    {

        setIdleAction(createAnimation(idleArray, 5.0, true, false));
        setWalkAction(createAnimation(walkArray, 10.0, true, false));
        setHurtAction(createAnimation(hurtArray, 10.0, false, true));

        setAirHurtAction(createAnimation(airHurtArray, 10.0f, false, false));
        setKnockDownAction(createAnimation(knockDownArray, 10.0f, false, true));
        setDeadAction(createAnimation(deadArray, 10.0f, false, false));

        setFloatAction(createAnimation(floatArray, 10.0f, false, false));

        setNAttackAction(createAnimation(nattackArray, 10.0, false, true));
    }

    void setHPbar()
    {
        if (strcmp(getGroup()->getCString(), _delegate->currentPlayer->getGroup()->getCString()) != 0)
        {
            _hpBar = HPBar::create("flog_bar_r.png");
        }
        else
        {
            _hpBar = HPBar::create("flog_bar.png");
        }
        _hpBar->setPositionY(getHeight());
        _hpBar->setDelegate(this);
        addChild(_hpBar);
    }

protected:
    void dealloc()
    {
        unschedule(schedule_selector(CharacterBase::setAI));
        setActionState(State::DEAD);
        stopAllActions();

        if (strcmp(getGroup()->getCString(), Konoha) == 0)
        {
            int index = _delegate->_KonohaFlogArray->indexOfObject(this);
            _delegate->_KonohaFlogArray->removeObjectAtIndex(index);
        }
        else
        {
            int index = _delegate->_AkatsukiFlogArray->indexOfObject(this);
            _delegate->_AkatsukiFlogArray->removeObjectAtIndex(index);
        }
        removeFromParent();
    }

    void setAI(float dt)
    {
        if (getActionState() == State::IDLE || getActionState() == State::WALK ||
            getActionState() == State::NATTACK)
        {

            if (!_randomPosY)
            {
                _randomPosY = rand() % 8 + 4;
                _randomPosX = (rand() % 32 + 20);
            }

            bool hasTarget = false;

            if (_mainTarget)
            {
                if (_mainTarget->getActionState() != State::DEAD && !_mainTarget->_isWudi && _mainTarget->_isVisable &&
                    strcmp(_mainTarget->getGroup()->getCString(), getGroup()->getCString()) != 0)
                {

                    hasTarget = true;
                }
            }

            if (!hasTarget)
            {

                if (!findEnemy("Flog", 0))
                {

                    if (!findEnemy("Hero", 64))
                    {

                        if (!findEnemy("Tower", 0))
                        {

                            _mainTarget = nullptr;
                        }
                    }
                }
            }

            CCPoint moveDirection;

            if (_mainTarget)
            {
                CCPoint sp = ccpSub(_mainTarget->getPosition(), getPosition());
                if (abs(sp.x) > _randomPosX || abs(sp.y) > _randomPosY)
                {

                    if (abs(sp.x) > 64 && strcmp(_mainTarget->getRole()->getCString(), "Flog") != 0 && strcmp(_mainTarget->getRole()->getCString(), "Tower") != 0)
                    {
                        _mainTarget = nullptr;
                        return;
                    }

                    moveDirection = ccpNormalize(sp);
                    walk(moveDirection);
                }
                else
                {
                    if (getActionState() != State::NATTACK)
                    {
                        changeSide(sp);
                        attack(NAttack);
                    }
                }
                return;
            }

            // no target then step on

            if (abs(getPositionY() - _mainPosY) > 8)
            {
                if (strcmp(getGroup()->getCString(), Konoha) == 0)
                {
                    moveDirection = ccpNormalize(ccp(1, getPositionY() > _mainPosY ? -1 : 1));
                }
                else
                {
                    moveDirection = ccpNormalize(ccp(-1, getPositionY() > _mainPosY ? -1 : 1));
                }
            }
            else
            {
                if (strcmp(getGroup()->getCString(), Konoha) == 0)
                {
                    moveDirection = ccpNormalize(ccp(1, 0));
                }
                else
                {
                    moveDirection = ccpNormalize(ccp(-1, 0));
                }
            }
            walk(moveDirection);
        }
    }
};
