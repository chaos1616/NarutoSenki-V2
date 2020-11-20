--
-- Ktools
--
tools = {}
device = CCDevice
director = {}
tips = {}
fmt = string.format

local kt = KTools
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

function tools.addSprites(...)
    assert(not ... ~= nil, 'addSprites: The table can not be nil')
    for _, v in ipairs {...} do
        sharedSpriteFrameCache:addSpriteFramesWithFile(v)
    end
end

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

-- Sqlite Utils

--[[
@param string table     = 'GameRecord'
@param string column    = nil
@param string value     = nil

@return string
]]
function tools.readFromSQLite(table, column, value)
    local ret =
        kt:readFromSQLite(table and table or "GameRecord", column, value)
    return ret and ret:getCString() or nil
end

--[[
@param string table
@param string column
@param string value
@param string targetColumn

@return string
]]
function tools.readSQLite(table, column, value, targetColumn)
    local ret = kt:readSQLite(table, column, value, targetColumn)
    return ret and ret:getCString() or nil
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

function CCNode:setTip(str)
    local tip = CCTips:create(str)
    self:addChild(tip, 5000)
end

--[[
    check has value in table
]]
function table:has(val)
    for _, v in ipairs(self) do if v == val then return true end end
    return false
end

--[[
    check has key in table
]]
function table:hasKey(key)
    for k, _ in ipairs(self) do if k == key then return true end end
    return false
end

function table.toCCArray(table)
    local arr = CCArray:create()
    arr:retain()
    for _, value in pairs(table) do arr:addObject(CCString:create(value)) end
    return arr
end

function director.replaceSceneWithFade(scene, time)
    if scene ~= nil and type(time) == 'number' and time > 0 then
        sharedDirector:replaceScene(CCTransitionFade:create(time, scene))
    end
end

function director.pushScene(scene)
    if scene ~= nil then sharedDirector:pushScene(scene) end
end

function director.popScene() sharedDirector:popScene() end

function director.sharedDirector() return sharedDirector end

function director.exit() sharedDirector:endToLua() end
