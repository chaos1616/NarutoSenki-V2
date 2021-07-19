#pragma once

// #include "GameMode/Impl/Regular.hpp"
#include "GameMode/Impl/1v1.hpp"
#include "GameMode/Impl/3v3.hpp"
#include "GameMode/Impl/4v4.hpp"

#include "GameMode/Impl/HardCore.hpp"

#include "GameMode/Impl/Boss.hpp"
#include "GameMode/Impl/Clone.hpp"

#include "GameMode/Impl/Deathmatch.hpp"
#include "GameMode/Impl/RandomDeathmatch.hpp"

extern GameMode s_GameMode;

static IGameModeHandler *s_ModeHandlers[GameMode::_Internal_Max_Length] = {
	new Mode1v1(),
	new Mode3v3(),
	new Mode4v4(),
	new ModeHardCore(),
	new ModeBoss(),
	new ModeClone(false),
	new ModeDeathmatch(),
	new ModeRandomDeathmatch(),
};

static inline IGameModeHandler *getGameModeHandler()
{
	return s_ModeHandlers[s_GameMode];
}
