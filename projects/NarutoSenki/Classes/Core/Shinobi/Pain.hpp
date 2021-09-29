#pragma once
#include "Hero.hpp"

class Pain : public Hero
{
#define kPain__ "Pain"
#define kNagato "Nagato"

	void perform()
	{
	}

	Hero *createClone(int cloneTime) override
	{
		Hero *clone = nullptr;
		if (isCharacter(kNagato))
		{
			clone = create<DevaPath>(CCString::create("DevaPath"), CCString::create(kRoleClone), getGroup());
			clone->_isArmored = true;
			if (isPlayer())
			{
				if (_delegate->getHudLayer()->skill5Button)
					_delegate->getHudLayer()->skill5Button->setLock();
			}

			_skillChangeBuffValue = 100;
		}

		return clone;
	}
};
