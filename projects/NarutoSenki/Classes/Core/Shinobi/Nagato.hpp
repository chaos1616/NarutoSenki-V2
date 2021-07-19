#pragma once
#include "Hero.hpp"
#include "Shinobi/DevaPath.hpp"

class Nagato : public Hero
{
	void perform()
	{
	}

	Hero *createClone(int32_t cloneTime)
	{
		auto clone = create<DevaPath>(CCString::create("DevaPath"), CCString::create(ROLE_CLONE), getGroup());
		clone->_isArmored = true;
		if (is_player)
		{
			if (_delegate->getHudLayer()->skill5Button)
			{
				_delegate->getHudLayer()->skill5Button->setLock();
			}
		}

		_skillChangeBuffValue = 100;
		return clone;
	}
};
