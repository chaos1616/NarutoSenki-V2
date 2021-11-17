#pragma once
#include "Defines.h"

struct SkillData
{
	string type;
	Value value;
	u16 rangeX;
	u16 rangeY;

	u16 cooldown;
	i32 combatPoint;
};
