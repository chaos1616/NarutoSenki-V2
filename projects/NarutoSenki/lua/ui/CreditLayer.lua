
function CreditsLayer_BackToStartMenu()
    audio.playSound('Audio/Menu/cancel.ogg')
    local menuScene = CCScene:create()
    local menuLayer = StartMenu:create()

    hook.registerInitHandlerOnly(menuLayer, StartMenu.init)
    menuScene:addChild(menuLayer)
    director.replaceSceneWithFade(menuScene, 1.5)
end
