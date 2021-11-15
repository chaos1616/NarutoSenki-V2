#pragma once
#include "Enums/Enums.h"

// menu sound
#define __SoundPerfix "Audio/Menu/"
constexpr auto SELECT_SOUND = __SoundPerfix "select.ogg";
constexpr auto TRAINING_SOUND = __SoundPerfix "training.ogg";
constexpr auto NETWORK_SOUND = __SoundPerfix "arcade.ogg";
constexpr auto CREDITS_SOUND = __SoundPerfix "credits.ogg";
constexpr auto EXIT_SOUND = __SoundPerfix "exit.ogg";
constexpr auto MENU_INTRO = __SoundPerfix "intro.ogg";

// music file
#define __MusicPerfix "Audio/Music/"
constexpr auto INTRO_MUSIC = __MusicPerfix "intro_music.ogg";
constexpr auto LOADING_MUSIC = __MusicPerfix "loading_music.ogg";
constexpr auto SELECT_MUSIC = __MusicPerfix "select_music.ogg";
constexpr auto RANKING_MUSIC = __MusicPerfix "ranking_music.ogg";
constexpr auto MENU_MUSIC = __MusicPerfix "menu_music.ogg";
constexpr auto CREDITS_MUSIC = __MusicPerfix "credits_music.ogg";
constexpr auto BATTLE_MUSIC = __MusicPerfix "Battle1.ogg";

namespace Audio
{
} // namespace Audio

namespace Music
{
} // namespace Music

#undef __SoundPerfix
#undef __MusicPerfix
