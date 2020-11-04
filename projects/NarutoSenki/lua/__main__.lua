require 'config'

local function main()
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    log('--- Loaded Lua Scripts ---')

    local gameScene = GameScene:create()
    cc.Director:sharedDirector():runWithScene(gameScene)

    local hero = AIGenerator:create('Lee', 'Player', 'Konoha')
    log('\n\n\n---- hero isAI %s ----\n\n', hero:getCharacter():getCString())

end

xpcall(main, __G__TRACKBACK__)
