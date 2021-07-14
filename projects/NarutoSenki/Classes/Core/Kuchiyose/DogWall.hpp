#pragma once
#include "Hero.hpp"

class DogWall : public Hero
{
	void perform()
	{
		attack(NAttack);
	}

	void setAI(float dt)
	{
		attack(NAttack);
	}
};
