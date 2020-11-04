--[[--
	Basic Types
]]

--[[--
	abType
]]
for key, value in getmetatable(_G) do
    print(key,value)
end
attackType = {
    NAttack 	= _G['abType'].NAttack,
    Item1	 	= _G['abType'].Item1,
    GearItem 	= _G['abType'].GearItem,
    GearBtn 	= _G['abType'].GearBtn,
    SKILL1 		= _G['abType'].SKILL1,
    SKILL2 		= _G['abType'].SKILL2,
    SKILL3 		= _G['abType'].SKILL3,
    OUGIS1 		= _G['abType'].OUGIS1,
    OUGIS2 		= _G['abType'].OUGIS2
}

--[[--
	gearType
]]
gearType = {
    gear00 	= _G['gearType'].gear00,
    gear01 	= _G['gearType'].gear01,
    gear02 	= _G['gearType'].gear02,
    gear03 	= _G['gearType'].gear03,
    gear04 	= _G['gearType'].gear04,
    gear05 	= _G['gearType'].gear05,
    gear06 	= _G['gearType'].gear06,
    gear07 	= _G['gearType'].gear07,
    gear08 	= _G['gearType'].gear08,
    None 	= _G['gearType'].None
}

team = {
	Akatsuki = 'Akatsuki',
	Konoha = 'Konoha'
}

--[[--
	Action State
]]
State = {
    DEAD 		= _G['State'].DEAD,
    IDLE 		= _G['State'].IDLE,
    WALK 		= _G['State'].WALK,
    ATTACK 		= _G['State'].ATTACK,
    SATTACK 	= _G['State'].SATTACK,
    OATTACK 	= _G['State'].OATTACK,
    O2ATTACK 	= _G['State'].O2ATTACK,
    HURT 		= _G['State'].HURT,
    ABHURT 		= _G['State'].ABHURT,
    KOCKDOWN 	= _G['State'].KOCKDOWN,
    FLOAT 		= _G['State'].FLOAT,
    JUMP 		= _G['State'].JUMP,
    AIRHURT 	= _G['State'].AIRHURT
}
