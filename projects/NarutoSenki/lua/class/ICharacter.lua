--
-- CharacterBase
--
local ICharacter = CharacterBase or {}

ICharacter._actionState = ActionState.WALK

ICharacter._idleAction = nil
ICharacter._nattackAction = nil
ICharacter._walkAction = nil
ICharacter._hurtAction = nil
ICharacter._airHurtAction = nil
ICharacter._knockDownAction = nil
ICharacter._floatAction = nil
ICharacter._deadAction = nil
ICharacter._skill1Action = nil
ICharacter._skill2Action = nil
ICharacter._skill3Action = nil
ICharacter._skill4Action = nil
ICharacter._skill5Action = nil

ICharacter.gearCKRValue = 0
ICharacter.gearRecoverValue = 0
ICharacter.isAttackGainCKR = false
ICharacter.isGearCD = false
ICharacter.isPofang = false
ICharacter.isHujia = false
ICharacter.battleCondiction = 0
ICharacter.hearts = 0
ICharacter.isHurtingTower = false
ICharacter.damageEffectCount = 0
ICharacter.bamen = 0

ICharacter._isSuicide = false

ICharacter._charNO = 0
ICharacter._backY = 0
ICharacter._DiretionY = 0

ICharacter._isAllAttackLocked = false
ICharacter._isOnlySkillLocked = false
ICharacter._sattack1isDouble = false
ICharacter._sattack2isDouble = false
ICharacter._sattack3isDouble = false
ICharacter._sattack4isDouble = false

ICharacter._moveAction = nil
ICharacter._jumpUPAction = nil
ICharacter._floatUPAction = nil

ICharacter._hurtFromLeft = false
ICharacter._hurtFromRight = false
ICharacter._isFlipped = false
ICharacter._isHitOne = false
ICharacter._isCatchOne = false
ICharacter._isHealling = false
ICharacter._isVisable = true
ICharacter._isSticking = false
ICharacter._isControled = false

ICharacter._isCanSkill1 = true
ICharacter._isCanSkill2 = true
ICharacter._isCanSkill3 = true
ICharacter._isCanItem1 = true
ICharacter._isCanOugis1 = false
ICharacter._isCanOugis2 = false

ICharacter._isCanGear00 = false
ICharacter._isCanGear03 = false
ICharacter._isCanGear06 = false

ICharacter.enemyCombatPoint = 0
-- totalCombatPoint=0
ICharacter.friendCombatPoint = 0

ICharacter.isBaseDanger = false

ICharacter._sattackCombatPoint1 = 0
ICharacter._sattackCombatPoint2 = 0
ICharacter._sattackCombatPoint3 = 0
ICharacter._sattackCombatPoint4 = 0
ICharacter._sattackCombatPoint5 = 0

ICharacter._role = nil
ICharacter._group = nil
ICharacter._character = nil
ICharacter._killNum = nil
ICharacter._coin = nil

ICharacter._master = nil
ICharacter._controler = nil
ICharacter._secmaster = nil
ICharacter._slayer = nil
ICharacter._sticker = nil

ICharacter._mainTarget = nil

ICharacter._deadNum = 0
ICharacter._flogNum = 0

ICharacter._knockLength = 0
ICharacter._knockDiretion = nil

ICharacter._effectType = nil

ICharacter._damageArray = nil
ICharacter._monsterArray = nil

ICharacter._originY = 0

ICharacter._nattackValue = nil
ICharacter._sattackValue1 = nil
ICharacter._sattackValue2 = nil
ICharacter._sattackValue3 = nil
ICharacter._sattackValue4 = nil
ICharacter._sattackValue5 = nil
ICharacter._spcattackValue1 = nil
ICharacter._spcattackValue2 = nil
ICharacter._spcattackValue3 = nil
ICharacter._tempAttackValue1 = nil

ICharacter._healBuffEffect = nil
ICharacter._powerBuffEffect = nil
ICharacter._skillBuffEffect = nil
ICharacter._healItemEffect = nil
ICharacter._speedItemEffect = nil
ICharacter._dehealBuffEffect = nil

ICharacter._buffStartTime = 0
ICharacter._debuffStartTime = 0
ICharacter._heartEffect = nil

ICharacter._shadow = nil

ICharacter._healBuffValue = 0
ICharacter._skillUPBuffValue = 0
ICharacter._skillChangeBuffValue = 0
ICharacter._dehealBuffValue = 0
ICharacter._powerUPBuffValue = 0
ICharacter._hpBar = nil
ICharacter._maxHP = nil
ICharacter._hp = nil
ICharacter._ckr = nil
ICharacter._ckr2 = nil

ICharacter._gardValue = 0
ICharacter._exp = 0
ICharacter._level = 1

ICharacter._isWudi = false
ICharacter._isTaunt = false
ICharacter._isBati = false

ICharacter._rebornTime = 5

ICharacter._markPoint = ccp(0, 0)
ICharacter._startPoint = ccp(0, 0)

ICharacter.rebornLabelTime = 0

ICharacter._isAI = false

ICharacter.cpLabel = nil

ICharacter._gearArray = nil

ICharacter._affectedByTower = false

--[[--
@type virtual
]]
function ICharacter:setID(character, role, group) end

--[[--
@type virtual
]]
function ICharacter:setHPbar() end

--[[--
@type virtual
]]
function ICharacter:changeHPbar() end

--[[--
@type virtual
]]
function ICharacter:setShadows() end

--[[--
@type virtual
]]
function ICharacter:getKillNum() end

--[[--
@type virtual
]]
function ICharacter:setKillNum(var) end

--[[--
@type virtual
]]
function ICharacter:getCoin() end

--[[--
@type virtual
]]
function ICharacter:setCoin(var) end

--[[--
@type virtual

@return unsigned
]]
function ICharacter:getCharNO() end

--[[--
@type virtual
]]
function ICharacter:setCharNO(var) end

--[[--
@type virtual

@return int
]]
function ICharacter:getKnockLength() end

--[[--
@type virtual
]]
function ICharacter:setKnockLength(var) end

--[[--
@type virtual

@return bool
]]
function ICharacter:getKnockDiretion() end

--[[--
@type virtual
]]
function ICharacter:setKnockDiretion(var) end

--[[--
@type virtual

@return CCLabelTTF*
]]
function ICharacter:getCPLabel() end

--[[--
@type virtual
]]
function ICharacter:setCPLabel(var) end

--[[--
@type virtual
]]
function ICharacter:getRole() end

--[[--
@type virtual
]]
function ICharacter:setRole(var) end

--[[--
@type virtual
]]
function ICharacter:getGroup() end

--[[--
@type virtual
]]
function ICharacter:setGroup(var) end

--[[--
@type virtual
]]
function ICharacter:getCharacter()
    print('\n\nInvoke ICharacter:getCharacter()')
    if self then
        print(self:getCharacter():getCString())
    else
        printError('self is nil')
    end
end

--[[--
@type virtual
]]
function ICharacter:setCharacter(var) end

--[[--
@type virtual

@return CCArray*
]]
function ICharacter:getGearArray() end

--[[--
@type virtual
]]
function ICharacter:setGearArray(var) end

--[[--
@type virtual

@return int
]]
function ICharacter:getWalkSpeed() end

--[[--
@type virtual
]]
function ICharacter:setWalkSpeed(var) end

--[[--
@type virtual
]]
function ICharacter:getMaxHP() end

--[[--
@type virtual
]]
function ICharacter:setMaxHP(var) end

--[[--
@type virtual
]]
function ICharacter:getHP() end

--[[--
@type virtual
]]
function ICharacter:setHP(var) end

--[[--
@type virtual
]]
function ICharacter:getCKR() end

--[[--
@type virtual
]]
function ICharacter:setCKR(var) end

--[[--
@type virtual
]]
function ICharacter:getCKR2() end

--[[--
@type virtual
]]
function ICharacter:setCKR2(var) end

--[[--
@type virtual

@return float
]]
function ICharacter:getGP() end

--[[--
@type virtual
]]
function ICharacter:setGP(var) end

--[[--
@type virtual

@return float
]]
function ICharacter:getEXP() end

--[[--
@type virtual
]]
function ICharacter:setEXP(var) end

--[[--
@type virtual

@return unsigned
]]
function ICharacter:getLV() end

--[[--
@type virtual
]]
function ICharacter:setLV(var) end

--[[--
@type virtual

@return int
]]
function ICharacter:getHeight() end

--[[--
@type virtual
]]
function ICharacter:setHeight(var) end

--[[--
@type virtual

@return unsigned
]]
function ICharacter:getRebornTime() end

--[[--
@type virtual
]]
function ICharacter:setRebornTime(var) end

--[[--
@type virtual

@return CCPoint
]]
function ICharacter:getSpawnPoint() end

--[[--
@type virtual
]]
function ICharacter:setSpawnPoint(var) end

--[[--
@type virtual

@return HeroElement*
]]
function ICharacter:getMaster() end

--[[--
@type virtual
]]
function ICharacter:setMaster(var) end

--[[--
@type virtual

@return ICharacter*
]]
function ICharacter:getControler() end

--[[--
@type virtual
]]
function ICharacter:setControler(var) end

--[[--
@type virtual

@return ICharacter*
]]
function ICharacter:getSecMaster() end

--[[--
@type virtual
]]
function ICharacter:setSecMaster(var) end

--[[--
@type virtual
]]
function ICharacter:getnAttackValue() end

--[[--
@type virtual
]]
function ICharacter:setnAttackValue(var) end

--[[--
@type virtual
]]
function ICharacter:getnAttackType() end

--[[--
@type virtual
]]
function ICharacter:setnAttackType(var) end

--[[--
@type virtual
]]
function ICharacter:getsAttackValue1() end

--[[--
@type virtual
]]
function ICharacter:setsAttackValue1(var) end

--[[--
@type virtual
]]
function ICharacter:getsAttack1Type() end

--[[--
@type virtual
]]
function ICharacter:setsAttack1Type(var) end

--[[--
@type virtual
]]
function ICharacter:getAttackType() end

--[[--
@type virtual
]]
function ICharacter:setAttackType(var) end

--[[--
@type virtual
]]
function ICharacter:getsAttackValue2() end

--[[--
@type virtual
]]
function ICharacter:setsAttackValue2(var) end

--[[--
@type virtual
]]
function ICharacter:getsAttack2Type() end

--[[--
@type virtual
]]
function ICharacter:setsAttack2Type(var) end

--[[--
@type virtual
]]
function ICharacter:getsAttackValue3() end

--[[--
@type virtual
]]
function ICharacter:setsAttackValue3(var) end

--[[--
@type virtual
]]
function ICharacter:getsAttack3Type() end

--[[--
@type virtual
]]
function ICharacter:setsAttack3Type(var) end

--[[--
@type virtual
]]
function ICharacter:getsAttackValue4() end

--[[--
@type virtual
]]
function ICharacter:setsAttackValue4(var) end

--[[--
@type virtual
]]
function ICharacter:getsAttack4Type() end

--[[--
@type virtual
]]
function ICharacter:setsAttack4Type(var) end

--[[--
@type virtual
]]
function ICharacter:getsAttackValue5() end

--[[--
@type virtual
]]
function ICharacter:setsAttackValue5(var) end

--[[--
@type virtual
]]
function ICharacter:getsAttack5Type() end

--[[--
@type virtual
]]
function ICharacter:setsAttack5Type(var) end

--[[--
@type virtual
]]
function ICharacter:getspcAttackValue1() end

--[[--
@type virtual
]]
function ICharacter:setspcAttackValue1(var) end

--[[--
@type virtual
]]
function ICharacter:getspcAttack1Type() end

--[[--
@type virtual
]]
function ICharacter:setspcAttack1Type(var) end

--[[--
@type virtual
]]
function ICharacter:getspcAttackValue2() end

--[[--
@type virtual
]]
function ICharacter:setspcAttackValue2(var) end

--[[--
@type virtual
]]
function ICharacter:getspcAttack2Type() end

--[[--
@type virtual
]]
function ICharacter:setspcAttack2Type(var) end

--[[--
@type virtual
]]
function ICharacter:getspcAttackValue3() end

--[[--
@type virtual
]]
function ICharacter:setspcAttackValue3(var) end

--[[--
@type virtual
]]
function ICharacter:getspcAttack3Type() end

--[[--
@type virtual
]]
function ICharacter:setspcAttack3Type(var) end

--[[--
@type virtual
]]
function ICharacter:gettempAttackValue1() end

--[[--
@type virtual
]]
function ICharacter:settempAttackValue1(var) end

--[[--
@type virtual
]]
function ICharacter:getTempAttackType() end

--[[--
@type virtual
]]
function ICharacter:setTempAttackType(var) end

--[[--
@type virtual
]]
function ICharacter:getEffectType() end

--[[--
@type virtual
]]
function ICharacter:setEffectType(var) end

--[[--
@type virtual

@return CCArray*
]]
function ICharacter:getDamageArray() end

--[[--
@type virtual
]]
function ICharacter:setDamageArray(var) end

--[[--
@type virtual

@return CCArray*
]]
function ICharacter:getMonsterArray() end

--[[--
@type virtual
]]
function ICharacter:setMonsterArray(var) end

--[[--
@type virtual

@return CCPoint
]]
function ICharacter:getVelocity() end

--[[--
@type virtual
]]
function ICharacter:setVelocity(var) end

--[[--
@type virtual

@return CCPoint
]]
function ICharacter:getDesiredPosition() end

--[[--
@type virtual
]]
function ICharacter:setDesiredPosition(var) end

--[[--
@type virtual

@return State
]]
function ICharacter:getActionState() end

--[[--
@type virtual
]]
function ICharacter:setActionState(state) end

--[[--
@type virtual

@return GameLayer*
]]
function ICharacter:getDelegate() end

--[[--
@type virtual
]]
function ICharacter:setDelegate(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getIdleAction() end

--[[--
@type virtual
]]
function ICharacter:setIdleAction(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getNAttackAction() end

--[[--
@type virtual
]]
function ICharacter:setNAttackAction(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getWalkAction() end

--[[--
@type virtual
]]
function ICharacter:setWalkAction(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getHurtAction() end

--[[--
@type virtual
]]
function ICharacter:setHurtAction(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getKnockDownAction() end

--[[--
@type virtual
]]
function ICharacter:setKnockDownAction(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getAirHurtAction() end

--[[--
@type virtual
]]
function ICharacter:setAirHurtAction(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getFloatAction() end

--[[--
@type virtual
]]
function ICharacter:setFloatAction(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getDeadAction() end

--[[--
@type virtual
]]
function ICharacter:setDeadAction(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getSkill1Action() end

--[[--
@type virtual
]]
function ICharacter:setSkill1Action(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getSkill2Action() end

--[[--
@type virtual
]]
function ICharacter:setSkill2Action(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getSkill3Action() end

--[[--
@type virtual
]]
function ICharacter:setSkill3Action(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getSkill4Action() end

--[[--
@type virtual
]]
function ICharacter:setSkill4Action(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getSkill5Action() end

--[[--
@type virtual
]]
function ICharacter:setSkill5Action(var) end

--[[--
@type virtual

@return CCActionInterval*
]]
function ICharacter:getMoveAction() end

--[[--
@type virtual
]]
function ICharacter:setMoveAction(var) end

--[[--
@type virtual

@return CCAction*
]]
function ICharacter:getFloatUPAction() end

--[[--
@type virtual
]]
function ICharacter:setFloatUPAction(var) end

--[[--
@type virtual

@return CCActionInterval*
]]
function ICharacter:getJumpUPAction() end

--[[--
@type virtual
]]
function ICharacter:setJumpUPAction(var) end

function ICharacter:update(dt) end
function ICharacter:updateHpBarPosition(dt) end
function ICharacter:acceptAttack(object) end

--[[--
@return float
]]
function ICharacter:getHpPercent() end

--[[--
@return bool
]]
function ICharacter:checkHasMovement() end

function ICharacter:idle() end
function ICharacter:walk(direction) end
function ICharacter:attack(type) end
function ICharacter:sAttack(type) end
function ICharacter:nAttack() end
function ICharacter:oAttack(type) end

--[[--
@return bool
]]
function ICharacter:hurt() end

--[[--
@return bool
]]
function ICharacter:hardHurt(delayTime, isHurtAction, isCatch, isStick, isStun) end

function ICharacter:absorb(position, isImmediate) end
-- void jump() -- No reference
function ICharacter:knockDown() end
function ICharacter:dead() end
function ICharacter:floatUP(floatHeight, isCancelSkill) end
function ICharacter:airHurt() end
function ICharacter:doAI() end

--[[--
@type virtual
]]
function ICharacter:changeAction() end

function ICharacter:changeAction2() end
function ICharacter:changeGroup() end
function ICharacter:resumeAction(dt) end
function ICharacter:setActionResume() end
function ICharacter:setActionResume2() end
function ICharacter:reCatched(dt) end
function ICharacter:setShadow(sender, data) end
function ICharacter:disableShadow(sender) end
function ICharacter:enableShadow(sender) end
function ICharacter:setItem(type) end
function ICharacter:disableEffect() end
function ICharacter:disableHpBar(dt) end
function ICharacter:disableShack() end
function ICharacter:disableDebuff(dt) end
function ICharacter:enableSkill1(dt) end
function ICharacter:enableSkill2(dt) end
function ICharacter:enableSkill3(dt) end
function ICharacter:enableItem1(dt) end
function ICharacter:enableGear00(dt) end
function ICharacter:enableGear03(dt) end
function ICharacter:enableGear06(dt) end
function ICharacter:disableGear1(dt) end
function ICharacter:disableGear2(dt) end
function ICharacter:disableGear3(dt) end

--[[--
@return bool
]]
function ICharacter:setGear(gearType) end

function ICharacter:useGear(gearType) end
function ICharacter:setCoinDisplay(num) end
function ICharacter:addCoin(num) end
function ICharacter:minusCoin(num) end

--[[--
@type virtual
]]
function ICharacter:dealloc() end

--[[--
@type virtual
]]
function ICharacter:reborn(dt) end

function ICharacter:resumePauseStuff(dt) end
function ICharacter:lostBlood(dt) end
function ICharacter:removeLostBlood(dt) end

--[[--
@type virtual
]]
function ICharacter:setAI(dt) end

function ICharacter:setSkillEffect(sender, data) end
function ICharacter:setRestore2(dt) end

-- protected:
-- 	void readDate(tmpDate, attackType, attackValue, attackRangeX, attackRangeY, coldDown, combatPoint)

-- 	CCAction* createAnimation(ationArray, fps, isRepeat, isReturn)

-- 	CCDictionary* callValue

-- 	void setSound(sender, data)
-- 	void setDSound(sender, data)
-- 	void setMove(sender, data)
-- 	void setCharge(sender, data)
-- 	void setChargeB(sender, data)
-- 	void getCollider()
-- 	void getSticker(dt)
-- 	void stopMove(dt)
-- 	void stopJump(sender, data)
-- 	void setAttackBox(sender, data)
-- 	void setDamage(effectType, attackValue, isFlipped)
-- 	void setDamgeDisplay(value, type)

-- 	void setItemEffect(sender, data)
-- 	void setDamgeEffect(type)
-- 	void setMonAttack(sender, data)
-- 	void setTransform()
-- 	void setOugis(sender)

-- 	void setCharFlip()

-- 	void setClone(sender, data)
-- 	void setMon(sender, data)
-- 	void setMonPer(dt)
-- 	void setBullet(sender, data)
-- 	void setBulletGroup(dt)

-- 	void setTrap(sender, data)

-- 	void setBuff(sender, data)
-- 	void setCommand(sender, data)
-- 	void setBuffEffect(type)
-- 	void removeBuffEffect(type)
-- 	void disableBuff(dt)
-- 	void healBuff(dt)
-- 	void dehealBuff(dt)

-- 	void removeClone(dt)
-- 	void removeSelf(dt)
-- 	void setJump(sender, data)

-- 	void removeCoinDisplay(sender, data)

-- 	CCRect setHalfBox()
-- 	CCRect setHitBox()

-- 	void checkActionFinish(dt)

-- 	void setRestore(dt)

-- 	bool findEnemy(type, searchRange, masterRange)
-- 	bool findEnemy2(type)
-- 	bool findTargetEnemy(type, isTowerDected)
-- 	bool checkBase()

-- 	bool stepBack()
-- 	bool stepBack2()
-- 	bool checkRetri()
-- 	void stepOn()
-- 	void changeSide(sp)

-- 	void removeDamageDisplay()

-- 	void onEnter()
-- 	void onExit()

return ICharacter
