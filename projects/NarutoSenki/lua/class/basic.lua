--[[--
	Basic Types
]]

--[[--
	abType
]] AttackType = {
    NAttack     = _G['NAttack'],
    Item1       = _G['Item1'],
    GearItem    = _G['GearItem'],
    GearBtn     = _G['GearBtn'],
    SKILL1      = _G['SKILL1'],
    SKILL2      = _G['SKILL2'],
    SKILL3      = _G['SKILL3'],
    OUGIS1      = _G['OUGIS1'],
    OUGIS2      = _G['OUGIS2']
}

--[[--
	gearType
]]
GearType = {
    gear00      = _G['gear00'],
    gear01      = _G['gear01'],
    gear02      = _G['gear02'],
    gear03      = _G['gear03'],
    gear04      = _G['gear04'],
    gear05      = _G['gear05'],
    gear06      = _G['gear06'],
    gear07      = _G['gear07'],
    gear08      = _G['gear08'],
    None        = _G['None']
}

Team = {
    Akatsuki    = 'Akatsuki',
    Konoha      = 'Konoha'}

--[[--
	Action State
]]
State = {
    DEAD        = _G['DEAD'],
    IDLE        = _G['IDLE'],
    WALK        = _G['WALK'],
    ATTACK      = _G['ATTACK'],
    SATTACK     = _G['SATTACK'],
    OATTACK     = _G['OATTACK'],
    O2ATTACK    = _G['O2ATTACK'],
    HURT        = _G['HURT'],
    ABHURT      = _G['ABHURT'],
    KOCKDOWN    = _G['KOCKDOWN'],
    FLOAT       = _G['FLOAT_AIR'], -- In windows it has the same define
    JUMP        = _G['JUMP'],
    AIRHURT     = _G['AIRHURT']
}
