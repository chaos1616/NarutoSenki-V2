--[[
    Initial UI
]]

local musicPerfix   = "Audio/Music/"
local soundPerfix   = "Audio/Menu/"

ns.music = {
    INTRO_MUSIC     = musicPerfix .. "intro_music.ogg",
    LOADING_MUSIC   = musicPerfix .. "loading_music.ogg",
    SELECT_MUSIC    = musicPerfix .. "select_music.ogg",
    RANKING_MUSIC   = musicPerfix .. "ranking_music.ogg",
    MENU_MUSIC      = musicPerfix .. "menu_music.ogg",
    CREDITS_MUSIC   = musicPerfix .. "credits_music.ogg",
    BATTLE_MUSIC    = musicPerfix .. "Battle1.ogg",
}

ns.menu = {
    SELECT_SOUND    = soundPerfix .. "select.ogg",
    TRAINING_SOUND  = soundPerfix .. "training.ogg",
    NETWORK_SOUND   = soundPerfix .. "arcade.ogg",
    CREDITS_SOUND   = soundPerfix .. "credits.ogg",
    EXIT_SOUND      = soundPerfix .. "exit.ogg",
    MENU_INTRO      = soundPerfix .. "intro.ogg",
}

require 'ui.GameScene'

require 'ui.StartMenu'
require 'ui.SelectLayer'
require 'ui.SkillLayer'
