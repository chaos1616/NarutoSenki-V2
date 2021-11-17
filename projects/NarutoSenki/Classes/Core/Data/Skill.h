#pragma once
#include "Defines.h"

struct SkillData
{
	static const SkillData Null;

	ActionFlag flag;
	string type;
	Value value;
	u16 rangeX;
	u16 rangeY;

	u16 cooldown;
	u16 combatPoint;
	bool isDouble;
};
