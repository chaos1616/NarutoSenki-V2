-- GameScene
local gameScene = GameScene

gameScene.pushMenu = nil

function GameScene:init()
    log('Initial GameScene ...')

    local ud = CCUserDefault:sharedUserDefault()
    if not ud:getBoolForKey('isHavingSave') then
        ud:setBoolForKey('isHavingSave', true)
        ud:setBoolForKey('isBGM', true)
        ud:setBoolForKey('isVoice', true)
        ud:flush()
    end

    local introLayer = display.newLayer()
    self:setIntroLayer(introLayer)

    local logoImage = display.newSprite('zakume.png', display.width / 2,
                                        display.height / 2)

    local seq = transition.sequence({
        CCFadeIn:create(1.5), CCFadeOut:create(1.5),
        CCCallFunc:create(handler(self, GameScene.onLogo))
    })
    introLayer:addChild(logoImage)
    logoImage:runAction(seq)
    self:addChild(introLayer)
end

function GameScene:onLogo()
    local logo_btn = ui.newImageMenuItem(
                         {
            image = 'logo.png',
            listener = handler(self, GameScene.onLogoClick),
            sound = ns.menu.MENU_INTRO
        })
    logo_btn:setAnchorPoint(0.5, 0.5)

    local logoMenu = ui.newMenu({logo_btn})
    logoMenu:setPosition(display.width / 2,
                         display.height - logo_btn:getContentSize().height / 2)
    self:getIntroLayer():addChild(logoMenu, 3)
    self:setLogoMenu(logoMenu)

    -- register c++ handler to onFinish function
    hook.registerInitHandlerOnly(self, GameScene.onFinish)

    local seq = transition.sequence({
        CCFadeIn:create(1.5), CCDelayTime:create(2.0),
        CCCallFunc:create(handler(self, GameScene.onFinish))
    })
    logo_btn:runAction(seq)
end

function GameScene:onPlayEffect() audio.playEffect('Audio/Menu/intro2.ogg') end

function GameScene:onFinish()
    local pushMenu = self.pushMenu
    if not pushMenu then
        audio.playMusic(ns.music.INTRO_MUSIC, true)

        local btm_btn = ui.newImageMenuItem(
                            {
                image = 'push_start.png',
                listener = handler(self, GameScene.onPush)
            })
        pushMenu = ui.newMenu({btm_btn})
        pushMenu:setPosition(display.width / 2, display.height / 2 - 100)
        self:getIntroLayer():addChild(pushMenu)

        local fade = CCFadeOut:create(0.5)
        local seq = transition.sequence({fade, fade:reverse()})
        btm_btn:runAction(CCRepeatForever:create(seq))
    end
end

function GameScene:onPush()
    audio.playSound('Audio/Menu/confirm.ogg')

    tools.initSqliteDB()

    audio:stopMusic(true)

    local menuScene = CCScene:create()
    local menuLayer = StartMenu:create()
    menuScene:addChild(menuLayer)

    -- auto call c++ layer StartMenu::init after lua called
    -- hook.registerInitHandlerOnly(menuLayer, StartMenu.init)

    CCDirector:sharedDirector():replaceScene(
        CCTransitionFade:create(1.0, menuScene))
end
