--[[--
	Basic Types
]]

--[[--
	abType
]]
for key, value in getmetatable(_G) do
    print(key,value)
end

local abType = _G['abType']
local gearType = _G['gearType']
local actionState = _G['State']

AttackType = {
    NAttack 	= abType.NAttack,
    Item1	 	= abType.Item1,
    GearItem 	= abType.GearItem,
    GearBtn 	= abType.GearBtn,
    SKILL1 		= abType.SKILL1,
    SKILL2 		= abType.SKILL2,
    SKILL3 		= abType.SKILL3,
    OUGIS1 		= abType.OUGIS1,
    OUGIS2 		= abType.OUGIS2
}

--[[--
	gearType
]]
GearType = {
    gear00 	= gearType.gear00,
    gear01 	= gearType.gear01,
    gear02 	= gearType.gear02,
    gear03 	= gearType.gear03,
    gear04 	= gearType.gear04,
    gear05 	= gearType.gear05,
    gear06 	= gearType.gear06,
    gear07 	= gearType.gear07,
    gear08 	= gearType.gear08,
    None 	= gearType.None
}

Team = {
	Akatsuki = 'Akatsuki',
	Konoha = 'Konoha'
}

--[[--
	Action State
]]
ActionState = {
    DEAD 		= actionState.DEAD,
    IDLE 		= actionState.IDLE,
    WALK 		= actionState.WALK,
    ATTACK 		= actionState.ATTACK,
    SATTACK 	= actionState.SATTACK,
    OATTACK 	= actionState.OATTACK,
    O2ATTACK 	= actionState.O2ATTACK,
    HURT 		= actionState.HURT,
    ABHURT 		= actionState.ABHURT,
    KOCKDOWN 	= actionState.KOCKDOWN,
    FLOAT 		= actionState.FLOAT,
    JUMP 		= actionState.JUMP,
    AIRHURT 	= actionState.AIRHURT
}
