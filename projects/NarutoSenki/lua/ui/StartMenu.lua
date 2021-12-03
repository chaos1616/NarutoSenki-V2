--
-- StartMenu
--
ns.StartMenu = StartMenu

function StartMenu:init()
    log('Initial StartMenu...')

    audio.setSoundsVolume(0.5)

    tools.addSprites('Menu.plist')
    tools.addSprites('Result.plist')
    tools.addSprites('NamePlate.plist')

    -- -- produce groud
    -- local gold_left = display.newSprite('#gold_left.png', 0, 20)
    -- gold_left:setAnchorPoint(0, 0)
    -- self:addChild(gold_left, 1)

    -- local gold_right = display.newSprite('#gold_right.png')
    -- gold_right:setAnchorPoint(0, 1)
    -- gold_right:setPosition(display.width - gold_right:getContentSize().width -
    --                            20, display.height - 20)
    -- self:addChild(gold_right, 1)

    -- -- produce the cloud
    -- local cloud_left = display.newSprite('#cloud.png', 0, 15)
    -- cloud_left:setFlipX(true)
    -- cloud_left:setFlipY(true)
    -- cloud_left:setAnchorPoint(0, 0)
    -- self:addChild(cloud_left, 1)

    -- local cmv1 = CCMoveBy:create(1, CCPoint(-15, 0))
    -- local cseq1 = CCRepeatForever:create(
    --                   transition.sequence({cmv1, cmv1:reverse()}))
    -- cloud_left:runAction(cseq1)

    -- local cloud_right = display.newSprite('#cloud.png')
    -- cloud_right:setPosition(display.width - cloud_right:getContentSize().width,
    --                         display.height -
    --                             (cloud_right:getContentSize().height + 15))
    -- cloud_right:setAnchorPoint(0, 0)
    -- self:addChild(cloud_right, 1)

    -- local cmv2 = CCMoveBy:create(1, CCPoint(15, 0))
    -- local cseq2 = CCRepeatForever:create(
    --                   transition.sequence({cmv2, cmv2:reverse()}))
    -- cloud_right:runAction(cseq2)

    -- -- produce the menu_bar
    -- local menu_bar_b = CCSprite:create('menu_bar2.png')
    -- menu_bar_b:setAnchorPoint(0, 0)
    -- menu_bar_b:fullScreen()
    -- self:addChild(menu_bar_b, 2)

    -- local menu_bar_t = CCSprite:create('menu_bar3.png')
    -- menu_bar_t:setAnchorPoint(0, 0)
    -- menu_bar_t:setPosition(0,
    --                        display.height - menu_bar_t:getContentSize().height)
    -- menu_bar_t:fullScreen()
    -- self:addChild(menu_bar_t, 2)

    -- local startmenu_title = display.newSprite('#startmenu_title.png')
    -- startmenu_title:setAnchorPoint(0, 0)
    -- startmenu_title:setPosition(2, display.height -
    --                                 startmenu_title:getContentSize().height - 2)
    -- self:addChild(startmenu_title, 3)
end

function enterSelectLayer(gameMode, enableCustomSelect)
    tools.addSprites('Select.plist')
    tools.addSprites('UI.plist')
    tools.addSprites('Report.plist')
    tools.addSprites('Ougis.plist')
    tools.addSprites('Ougis2.plist')
    tools.addSprites('Map.plist')
    tools.addSprites('Gears.plist')

    _G.mode = gameMode
    _G.enableCustomSelect = enableCustomSelect
    local selectScene = CCScene:create()
    local selectLayer = SelectLayer:create()
    hook.registerInitHandlerOnly(selectLayer)
    selectScene:addChild(selectLayer)
    director.replaceSceneWithFade(selectScene, 1.25)
end

function onGameOver()
    local menuScene = CCScene:create()
    local menuLayer = StartMenu:create()
    menuScene:addChild(menuLayer)
    director.replaceSceneWithFade(menuScene, 1.25)
end
