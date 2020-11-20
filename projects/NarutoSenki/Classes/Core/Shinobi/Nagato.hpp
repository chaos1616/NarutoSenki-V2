#pragma once
#include "Hero.hpp"
#include "Shinobi/DevaPath.hpp"

class Nagato : public Hero
{
	void perform()
	{
	}

	Hero *createClone(unsigned int cloneTime)
	{
		auto clone = create<DevaPath>(CCString::create("DevaPath"), CCString::create(K_TAG_CLONE), getGroup());
		clone->_isBati = true;
		if (strcmp(getRole()->getCString(), "Player") == 0)
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
