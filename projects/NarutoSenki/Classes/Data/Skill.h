#pragma once
#include "Defines.h"

struct SkillData
{
	Value attackValue;
	string attackType;
	u16 attackRangeX;
	u16 attackRangeY;

	u16 cooldown;
	i32 combatPoint;
};
