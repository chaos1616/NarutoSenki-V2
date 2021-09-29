#pragma once
#include "Hero.hpp"
#include "Shinobi/DevaPath.hpp"

class Nagato : public Hero
{
	void perform()
	{
	}

	Hero *createClone(int cloneTime)
	{
		auto clone = create<DevaPath>(CCString::create("DevaPath"), CCString::create(kRoleClone), getGroup());
		clone->_isArmored = true;
		if (isPlayer())
		{
			if (_delegate->getHudLayer()->skill5Button)
				_delegate->getHudLayer()->skill5Button->setLock();
		}

		_skillChangeBuffValue = 100;
		return clone;
	}
};
