require 'framework.debug'

--
-- Ktools
--
tools = {}

local kt = KTools
local sharedDirector = CCDirector:sharedDirector()
local sharedTextureCache = CCTextureCache:sharedTextureCache()
local sharedSpriteFrameCache = CCSpriteFrameCache:sharedSpriteFrameCache()
local sharedAnimationCache = CCAnimationCache:sharedAnimationCache()

function tools:readXMLToArray(filePath, array)
    if nil ~= filePath or array ~= nil then return nil end

    return kt:readXMLToArray(filePath, array)
end

function tools:loadOgg(name) kt:prepareFileOGG(name, false) end
function tools:unloadOgg(name) kt:prepareFileOGG(name, true) end

-- macros
function tools.addSprites(name, ...)
    -- assert(name ~= nil, 'addSprites: The name can not be nil')
    sharedSpriteFrameCache:addSpriteFramesWithFile(name)

    if ... and type(...) == 'table' then
        for _, v in pairs(...) do
            sharedSpriteFrameCache:addSpriteFramesWithFile(v)
        end
    end
end

function CCSprite:fullScreen()
    self:setScaleX(display.width / self:getContentSize().width)
end

function tools.is_c_type(userdata, cType)
    if type(userdata) == 'userdata' and tolua.type(userdata) == cType then
        return true
    end
    return false
end

function newCStr(str) return CCString:create(str) end

-- Defines
-- ns = {}
-- ns.CharacterBase = CharacterBase
-- ns.HeroElement = HeroElement -- Inheried CharacterBase
-- ns.Flog = Flog -- Inheried CharacterBase
-- ns.Tower = Tower -- Inheried CharacterBase
-- ns.Monster = Monster -- Inheried CharacterBase
-- ns.Bullet = Bullet -- Inheried CharacterBase
-- ns.Hero = Hero -- Inheried HeroElement

-- ns.HPBar = HPBar
