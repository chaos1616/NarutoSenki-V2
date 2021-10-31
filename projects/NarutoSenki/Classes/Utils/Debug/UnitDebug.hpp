#pragma once
#include "Utils/Debug/Debug.h"

#if COCOS2D_DEBUG

DEBUG_NS_BEGIN

#include "CharacterBase.h"

void PrintDamgeInfo(CharacterBase *attacked, CharacterBase *attacker, int attackValue, uint32_t damage)
{
	if (attacked->isNotFlog() && attacker->isNotFlog())
	{
		if (damage >= attacked->getHPValue())
			NSLOG("Unit {:<9} killed   {:<9} -{:<4}HP [ Atk: {:<4}]", attacker->getCharacter()->getCString(), attacked->getCharacter()->getCString(), damage, attackValue);
		else
			NSLOG("Unit {:<9} attacked {:<9} -{:<4}HP [ Atk: {:<4}]", attacker->getCharacter()->getCString(), attacked->getCharacter()->getCString(), damage, attackValue);
	}
}

DEBUG_NS_END

#endif
