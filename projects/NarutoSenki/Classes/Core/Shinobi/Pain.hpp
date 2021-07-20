#pragma once
#include "Hero.hpp"

class Pain : public Hero
{
#define kPain__ "Pain"
#define kNagato "Nagato"

	void perform()
	{
	}

	Hero *createClone(int32_t cloneTime) override
	{
		Hero *clone = nullptr;
		if (character_is(kNagato))
		{
			clone = create<DevaPath>(CCString::create("DevaPath"), CCString::create(ROLE_CLONE), getGroup());
			clone->_isArmored = true;
			if (is_player)
			{
				if (_delegate->getHudLayer()->skill5Button)
					_delegate->getHudLayer()->skill5Button->setLock();
			}

			_skillChangeBuffValue = 100;
		}

		return clone;
	}
};
