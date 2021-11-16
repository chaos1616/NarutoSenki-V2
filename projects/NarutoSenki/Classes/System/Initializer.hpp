#pragma once
#include "System/CommandSystem.hpp"

namespace Internal
{
static void initAllSystems()
{
	CommandSystem::reset();
}
} // namespace Internal
