--[[
    Initial UI
]]

--[[
    Function calls order of `init` operations

    ~~~ sample

    c++: GameScene::init()

    -> local scene = GameScene:create()  [lua]
    ->
    ----- Register callback
    ----- In c++ only called once that will
    ----- set handler to empty after called init fucntion
    -> hook.registerInitHandlerOnly(scene)
    ->
    -> GameScene::init()        [c++]
    -> GameScene::onEnter()     [c++]
    ->
    -> lua_call_init_func       [c++]
    ->
    -> GameScene:init()         [lua]
    -> ...
]]

local musicPerfix   = 'Audio/Music/'
local soundPerfix   = 'Audio/Menu/'

ns.music = {
    Perfix          = musicPerfix,
    INTRO_MUSIC     = musicPerfix .. 'intro_music.ogg',
    LOADING_MUSIC   = musicPerfix .. 'loading_music.ogg',
    SELECT_MUSIC    = musicPerfix .. 'select_music.ogg',
    RANKING_MUSIC   = musicPerfix .. 'ranking_music.ogg',
    MENU_MUSIC      = musicPerfix .. 'menu_music.ogg',
    CREDITS_MUSIC   = musicPerfix .. 'credits_music.ogg',
    BATTLE_MUSIC    = musicPerfix .. 'Battle1.ogg',
}

ns.menu = {
    Perfix          = soundPerfix,
    CONFIRM         = soundPerfix .. 'confirm.ogg',
    CREDITS_SOUND   = soundPerfix .. 'credits.ogg',
    EXIT_SOUND      = soundPerfix .. 'exit.ogg',
    LOGO_CLICK      = soundPerfix .. 'chang_btn.ogg',
    MENU_INTRO      = soundPerfix .. 'intro.ogg',
    MENU_INTRO2     = soundPerfix .. 'intro2.ogg',
    NETWORK_SOUND   = soundPerfix .. 'arcade.ogg',
    SELECT_SOUND    = soundPerfix .. 'select.ogg',
    TRAINING_SOUND  = soundPerfix .. 'training.ogg',
}

require 'ui.GameScene'

require 'ui.StartMenu'
require 'ui.CreditLayer'
require 'ui.SelectLayer'
require 'ui.SkillLayer'
require 'ui.SelectButton'
