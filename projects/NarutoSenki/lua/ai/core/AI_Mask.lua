--
-- Drive Mask-Raiton, Mask-Katon, Mask-Futon
--
local AI_Mask = class('AI_Mask', function() return Hero:new() end)

function AI_Mask:perform()
    if self:getCharacter():getCString() == 'MaskRaidon' then
        if not self:findEnemy('Flog', 0) and not self:findEnemy('Hero', 0) and
            not self:findEnemy('Tower', 0) then
            -- set nil
            self._mainTarget = nil
        end
    else
        if not self:findEnemy('Hero', 0) and not self:findEnemy('Flog', 0) and
            not self:findEnemy('Tower', 0) then
            -- set nil
            self._mainTarget = nil
        end
    end

    if self._mainTarget then
        local moveDirection
        local sp

        if (self._mainTarget._originY) then
            sp = ccpSub(ccp(self._mainTarget:getPositionX(),
                            self._mainTarget._originY), self:getPosition())
        else
            sp = ccpSub(self._mainTarget:getPosition(), self:getPosition())
        end

        if self._mainTarget:getRole():getCString() == 'Tower' then
            if abs(sp.x) > 32 or abs(sp.y) > 32 then
                moveDirection = cc.PointNormalize(sp)
                self:walk(moveDirection)
            elseif self:getActionState() == State.IDLE or self:getActionState() ==
                State.WALK or self:getActionState() == State.ATTACK then
                self:changeSide(sp)
                self:attack(State.NAttack)
            end
            return
        else
            if abs(sp.x) > 96 or abs(sp.y) > 16 then
                moveDirection = cc.PointNormalize(sp)
                self:walk(moveDirection)
                return
            elseif abs(sp.x) > 48 or abs(sp.y) > 16 and not self._isCanSkill1 then
                moveDirection = cc.PointNormalize(sp)
                self:walk(moveDirection)
                return
            elseif self:getActionState() == State.IDLE or self:getActionState() ==
                State.WALK or self:getActionState() == State.ATTACK then
                if self._isCanSkill1 and self._mainTarget:getGP() < 5000 then
                    self:changeSide(sp)
                    self:attack(State.SKILL1)
                else
                    self:changeSide(sp)
                    self:attack(State.NAttack)
                end
            end
            return
        end
    end

    self:stepOn()
end
