require 'utils.utils'

--
-- AI Module
--
AIGenerator = {}
AIDispatcher = {}

local ap = AIProvider
local info_table = {}
local t = tools

local switcher = {
    ['Jiraiya'] = function(n)
        addCharacterSprites('SageJiraiya')
        t:loadOgg("SageJiraiya")
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
        t:loadOgg("SageNaruto")
        t:loadOgg("RikudoNaruto")
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
        t:loadOgg("ImmortalSasuke")
    end,
    ['Kiba'] = function(n)
        addCharacterSprites('Akamaru')
        -- no extra audio
    end
}

function AIGenerator:create(character, role, group)
    addCharacterSprites(character)
    prepare_extra_files(character, false)
    return ap:createAI(newCStr(character), newCStr(role), newCStr(group))
end

function AIGenerator:addCustom(characterName, extraFiles)
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

