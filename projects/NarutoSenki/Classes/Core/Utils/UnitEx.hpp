#pragma once
#include "Core/Unit.h"

namespace UnitEx
{

template <typename T>
typename std::enable_if_t<std::is_base_of_v<Unit, T>, void>
clearMainTarget(Unit *target, const vector<T *> &list)
{
	for (auto unit : list)
	{
		if (unit->_mainTarget)
		{
			if (unit->_mainTarget == target)
				unit->_mainTarget = nullptr;
		}
	}
}

} // namespace UnitEx
