require 'base.cocos2dx'
cclog = function(...)print(string.format(...)) end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(msg) .. "\n")
    print(debug.traceback())
    print("----------------------------------------")
end

local function main()
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)

    local sceneGame = CCScene:create()
    CCDirector:sharedDirector():runWithScene(sceneGame)

    hero = class(CharacterBase, CCSprite)
    -- hero = AIGenerator:create(CCString:create('Lee'), CCString:create(''), CCString:create('Konoha'))
    cclog(hero.isHurtingTower)

    cclog('--- Loaded Lua Scripts ---')
end

xpcall(main, __G__TRACKBACK__)
