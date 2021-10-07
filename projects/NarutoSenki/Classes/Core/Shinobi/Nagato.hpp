#pragma once
#include "Hero.hpp"
#include "Shinobi/DevaPath.hpp"

class Nagato : public Hero
{
	void perform() override
	{
	}

	Hero *createClone(int cloneTime) override
	{
		auto clone = create<DevaPath>(CCString::create("DevaPath"), CCString::create(kRoleClone), getGroup());
		clone->_isArmored = true;
		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill5Button->setLock();
		}

		_skillChangeBuffValue = 100;
		return clone;
	}
};
