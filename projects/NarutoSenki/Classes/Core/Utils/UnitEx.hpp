#pragma once
#include "CharacterBase.h"

namespace UnitEx
{
	inline void RemoveFlogsMainTarget(CharacterBase *target, const vector<Flog *> &list)
	{
		for (auto flog : list)
		{
			if (flog->_mainTarget)
			{
				if (flog->_mainTarget == target)
					flog->_mainTarget = nullptr;
			}
		}
	}

	inline void RemoveAllFlogsMainTarget(CharacterBase *target)
	{
		RemoveFlogsMainTarget(target, getGameLayer()->_KonohaFlogArray);
		RemoveFlogsMainTarget(target, getGameLayer()->_AkatsukiFlogArray);
	}
}
a