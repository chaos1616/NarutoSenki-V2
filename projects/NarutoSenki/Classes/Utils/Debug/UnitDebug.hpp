#pragma once
#include "CharacterBase.h"

namespace Debug
{
	inline void PrintDamgeInfo(CharacterBase *attacked, CharacterBase *attacker, int attackValue, uint32_t damage)
	{
		if (attacked->isNotFlog() && attacker->isNotFlog())
		{
			if (damage >= attacked->getHPValue())
				CCLOG("Unit %-10s killed %-10s -%uHP [ Atk: %u ]", attacker->getCharacter()->getCString(), attacked->getCharacter()->getCString(), attackValue, damage);
			else
				CCLOG("Unit %-10s attacked %-10s -%uHP", attacker->getCharacter()->getCString(), attacked->getCharacter()->getCString(), damage);
		}
	}
}
