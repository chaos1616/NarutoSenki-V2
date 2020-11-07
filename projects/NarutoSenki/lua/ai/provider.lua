require 'utils.utils'

--
-- AI Module
--
AIGenerator = {}
AIDispatcher = {}

local ap = AIProvider
local infoTable = {}
local t = tools

local switcher = {
    ['Jiraiya'] = function(n)
        addCharacterSprites('SageJiraiya')
        t.loadOgg('SageJiraiya')
    end,
    ['Kankuro'] = function(n)
        addCharacterSprites('Karasu')
        addCharacterSprites('Sanshouuo')
        addCharacterSprites('Saso')
    end,
    ['Chiyo'] = function(n)
        addCharacterSprites('Parents')
        -- no extra audio
    end,
    ['Kakuzu'] = function(n)
        addCharacterSprites('MaskRaidon')
        addCharacterSprites('MaskFudon')
        addCharacterSprites('MaskKadon')
    end,
    ['Naruto'] = function(n)
        addCharacterSprites('RikudoNaruto')
        addCharacterSprites('SageNaruto')
        addCharacterSprites('Kurama')
        t.loadOgg('SageNaruto')
        t.loadOgg('RikudoNaruto')
    end,
    ['Lee'] = function(n)
        addCharacterSprites('RockLee')
        -- no extra audio
    end,
    ['Tsunade'] = function(n)
        addCharacterSprites('Slug')
        -- no extra audio
    end,
    ['Kakashi'] = function(n)
        addCharacterSprites('DogWall')
        -- no extra audio
    end,
    ['Deidara'] = function(n)
        addCharacterSprites('Centipede')
        -- no extra audio
    end,
    ['Pain'] = function(n)
        addCharacterSprites('DevaPath')
        addCharacterSprites('AsuraPath')
        addCharacterSprites('AnimalPath')
    end,
    ['Sasuke'] = function(n)
        addCharacterSprites('ImmortalSasuke')
        t.loadOgg('ImmortalSasuke')
    end,
    ['Kiba'] = function(n)
        addCharacterSprites('Akamaru')
        -- no extra audio
    end
}

-- if device.platform == 'android' then
--     ap.extraPath = device.writablePath .. 'NarutoSenki/extra.ini'
-- else
--     ap.extraPath = 'config/extra.ini'
-- end

function AIGenerator.create(character, role, group)
    addCharacterSprites(character)
    prepare_extra_files(character, false)
    local heroAI = ap:createAI( -- create a exist AI
    CCString:create(character), -- character name
    CCString:create(role), -- character tag
    CCString:create(group) -- character team
    )
    local x, y = 432, 80
    heroAI:setPosition(x, y)
    heroAI:setSpawnPoint(x, y)
    -- this:addChild(heroAI, -heroAI:getPositionY())
    -- heroAI:setHPbar()
    -- heroAI:setShadows()
    -- heroAI:idle()
    -- heroAI:setCharNO(i + 1)
    -- heroAI:schedule(self:setRestore2, 1.0)
    return heroAI
end

function AIGenerator.addCustom(characterName, extraFiles)
    -- TODO
end

-- Add extra sprites
function prepare_extra_files(name, type)
    local handler = switcher[name]
    if not handler then
        log('not found character %s', name)
        return
    end
    handler(name)
end

function mkpath(name)
    -- name = info_table[name]
    return 'Element/' .. name .. '/' .. name .. '.plist'
end

function addCharacterSprites(name) t:addSprites(mkpath(name)) end

--[[
	params = {
		name 	= 'Naruto',		-- character name
		ai		= nil
		-- if not set `ai` default is `AI_ + name`
		-- ai	 	= 'AI_Naruto'
	}
]]
function addAIInfo(params)
    local name = params.name
    local ai = params.ai
end

function createAI(character, role, group)
    -- HeroElement *pAI
    local pAI

    local name = character:getCString()

    -- try set AI
    if name == nil then
        log('Character AI name can not be nil [ role: %s, team: %s]',
            role:getCString(), group:getCString())
        return
    end

    if not table.hasKey(infoTable, name) then
        log('Not foudn character AI %s', name)
        return
    end

    local _class = infoTable[name]
    if _class == nil then _class = 'AI_' .. name end
    local newClass = 'return ' .. _class .. ':new()'
    pAI = loadstring(newClass)

    if pAI == nil then
        log('New AI %s is nil, not found class %s', _class, _class)
        return
    end

    local function hasTag(name) return role:getCString() == name end

    if not pAI then
        log('not found AI %s', name)
        return nil
    end

    if pAI:init() then
        pAI:setID(character, role, group)
        pAI:autorelease()
        return pAI
    else
        log('Set AI %s not found', name)
        -- delete pAI
        pAI = nil
        return nil
    end
end

function AIProvider.init()
    ap.initialExtra()

    local function Add_Global_AI_Info(name, implName, onCloneTag)
        if not implName then implName = 'AI_' .. name end

        if onCloneTag then
            local t = type(onCloneTag)
            local _class
            if t == 'string' then
                _class = onCloneTag
                -- goto check
            elseif t == 'boolean' and onCloneTag then
                _class = implName .. 'Clone'
                -- ::check::
                if ap.hasClass(_class) then onCloneTag = _class end
            else
                log('Invaild onCloneTag type in AIProvider:init() -> ' ..
                        'Add_Global_AI_Info()')
            end
        end
    end

    -- local tags = ns.CharacterTags
    local push = Add_Global_AI_Info

    -- push('', {[tags.Clone] = ''})
    -- push Shinobi
    push('Asuma')
    push('Chiyo')
    push('Choji')
    push('Deidara')
    push('Gaara')
    push('Hidan')
    push('Hinata')
    push('Hiruzen')
    push('ImmortalSasuke')
    push('Ino')
    push('Itachi')
    push('Jiraiya')
    push('Jugo')
    push('Kakashi')
    push('Kakuzu')
    push('Kankuro')
    push('Karin')
    push('Kisame')
    push('Konan')
    push('Lee')
    push('Minato')
    push('Nagato')
    push('Naruto', 'AI_Naruto', true)
    push('Neji')
    push('Orochimaru')
    push('Pain')
    push('RikudoNaruto', 'AI_RikudoNaruto', true)
    push('RockLee')
    push('SageJiraiya')
    push('SageNaruto', 'AI_SageNaruto', true)
    push('Sai')
    push('Sakura')
    push('Sasuke')
    push('Shikamaru')
    push('Shino')
    push('Suigetsu')
    push('Tenten')
    push('Tobi')
    push('Tobirama')
    push('Tsunade')
    -- push Guardian
    push('Han', 'AI_Guardian')
    push('Roshi', 'AI_Guardian')
    -- push Summon
    push('Akamaru')
    push('AnimalPath')
    push('AsuraPath')
    push('Centipede')
    push('DevaPath')
    push('DogWall')
    push('Karasu')
    push('Kiba')
    push('Kurama')
    push('MaskFudon', 'AI_Mask')
    push('MaskKadon', 'AI_Mask')
    push('MaskRaidon', 'AI_Mask')
    push('Parents')
    push('Sanshouuo')
    push('Saso')
    push('Slug')
end

function AIProvider.hasClass(name) return _G[name] ~= nil end

function AIProvider.initialExtra()
    -- if io.exists(ap.extraPath) then
    -- else
    -- end
end

function AIProvider.pushExtra(name) end
