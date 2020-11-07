require 'framework.debug'

--
-- Ktools
--
tools = {}

local kt = KTools
local tips = CCTips
local sharedDirector = CCDirector:sharedDirector()
local sharedTextureCache = CCTextureCache:sharedTextureCache()
local sharedSpriteFrameCache = CCSpriteFrameCache:sharedSpriteFrameCache()
local sharedAnimationCache = CCAnimationCache:sharedAnimationCache()

function tools.readXMLToArray(filePath, array)
    if nil ~= filePath or array ~= nil then
        return kt:readXMLToArray(filePath, array)
    end
end

function tools.loadOgg(name) kt:prepareFileOGG(name, false) end
function tools.unloadOgg(name) kt:prepareFileOGG(name, true) end

-- macros
function tools.addSprites(...)
    assert(not ... ~= nil, 'addSprites: The table can not be nil')
    for _, v in ipairs {...} do
        sharedSpriteFrameCache:addSpriteFramesWithFile(v)
    end
end

function tools.setTip(str) tips:create(str) end

function tools.is_c_type(userdata, cType)
    if type(userdata) == 'userdata' and tolua.type(userdata) == cType then
        return true
    end
    return false
end

function tools.initSqliteDB()
    kt:initTableInDB()
    kt:initColumeInDB()
end

function tools.printTable(mt)
    if type(mt) == 'table' then
        for key, value in pairs(mt) do
            print(' table -> ', key, ' : ', value)
        end
    else
        log('Invalid type %s is not a table object', type(mt))
    end
end

function tools.printUserdata(ud)
    if type(ud) == 'userdata' then
        for key, value in pairs(getmetatable(ud)) do
            print(' table -> ', key, value)
        end
    else
        log('Invalid type %s is not a userdata object', type(ud))
    end
end

function CCSprite:fullScreen()
    self:setScaleX(display.width / self:getContentSize().width)
end

function table:has(val)
    for _, v in ipairs(self) do if v == val then return true end end
    return false
end

-- Defines
ns = {}

-- ns.CharacterBase = CharacterBase
-- ns.HeroElement = HeroElement -- Inheried CharacterBase
-- ns.Flog = Flog -- Inheried CharacterBase
-- ns.Tower = Tower -- Inheried CharacterBase
-- ns.Monster = Monster -- Inheried CharacterBase
-- ns.Bullet = Bullet -- Inheried CharacterBase
-- ns.Hero = Hero -- Inheried HeroElement

-- ns.HPBar = HPBar
