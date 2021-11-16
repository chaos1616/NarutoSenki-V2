#pragma once
#include "CharacterBase.h"

namespace UnitEx
{

template <typename T>
typename std::enable_if_t<std::is_base_of_v<CharacterBase, T>, void>
clearMainTarget(CharacterBase *target, const vector<T *> &list)
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
