#pragma once
#include "Core/Hero.hpp"
#include "Core/Unit.h"

// Detailed implementation of AI module of unit base class

// [For AI] 检查己方Inner Tower附近是否有敌人
bool Unit::checkBase()
{
	for (auto target : getGameLayer()->_CharacterArray)
	{
		if (target->_state == State::DEAD)
			continue;

		if (_group != target->_group)
		{
			if (isKonohaGroup())
			{
				if (target->getPositionX() <= 11 * 32)
				{
					_mainTarget = target;
					return true;
				}
			}
			else
			{
				if (target->getPositionX() >= 85 * 32)
				{
					_mainTarget = target;
					return true;
				}
			}
		}
	}

	auto &flogArray = isAkatsukiGroup()
						  ? getGameLayer()->_KonohaFlogArray
						  : getGameLayer()->_AkatsukiFlogArray;
	for (auto target : flogArray)
	{
		if (target->_state == State::DEAD)
			continue;

		if (_group != target->_group)
		{
			if (isKonohaGroup())
			{
				if (target->getPositionX() <= 11 * 32)
				{
					_mainTarget = target;
					return true;
				}
			}
			else
			{
				if (target->getPositionX() >= 85 * 32)
				{
					_mainTarget = target;
					return true;
				}
			}
		}
	}

	return false;
}

// [For AI] 血量充足后，使AI前进
void Unit::stepOn()
{
	Vec2 moveDirection;

	if (isKonohaGroup())
		moveDirection = Vec2(1, 0).getNormalized();
	else
		moveDirection = Vec2(-1, 0).getNormalized();

	walk(moveDirection);
}

// [For AI] 使AI撤退，只有横向移动方向
bool Unit::stepBack()
{
	if (_isControlled)
		return false;
	Vec2 moveDirection;

	if (isKonohaGroup())
		moveDirection = Vec2(-1, 0).getNormalized();
	else
		moveDirection = Vec2(1, 0).getNormalized();

	if (getPositionX() >= getGameLayer()->currentMap->getTileSize().width * 2 &&
		getPositionX() <= (getGameLayer()->currentMap->getMapSize().width - 2) * getGameLayer()->currentMap->getTileSize().width)
	{
		walk(moveDirection);
		return true;
	}
	else
	{
		return false;
	}
}

// [For AI] 使AI撤退
bool Unit::stepBack2()
{
	if (_isControlled)
		return false;

	Vec2 moveDirection;
	setRand();
	int randomDirection = random(10);

	if (!_backY)
	{
		if (randomDirection > 5)
		{
			if (getPositionY() + 96 < getGameLayer()->currentMap->getTileSize().height * 5.5)
			{
				_diretionY = 1;
				_backY = getPositionY() + 96;
			}
			else
			{
				_diretionY = -1;
				_backY = getPositionY() - 96;
			}
		}
		else
		{
			if (getPositionY() - 96 > 16)
			{
				_diretionY = -1;
				_backY = getPositionY() - 96;
			}
			else
			{
				_diretionY = 1;
				_backY = getPositionY() + 96;
			}
		}
	}
	else
	{
		if (randomDirection > 5)
		{
			if (_diretionY == 1 && (getPositionY() >= _backY || getPositionY() > getGameLayer()->currentMap->getTileSize().height * 5))
			{
				_diretionY = -1;
				_backY = getPositionY() - 96;
			}
			else if (_diretionY == -1 && (getPositionY() <= _backY || getPositionY() < 16))
			{
				_diretionY = 1;
				_backY = getPositionY() + 96;
			}
		}
		else
		{
			if (_diretionY == 1 && getPositionY() <= getGameLayer()->currentMap->getTileSize().height * 5)
			{
				_diretionY = 1;
				_backY = getGameLayer()->currentMap->getTileSize().height * 5;
			}
			else if (getPositionY() > 16)
			{
				_diretionY = -1;
				_backY = 16;
			}
		}
	}

	if (isKonohaGroup() && getPositionX() >= getGameLayer()->currentMap->getTileSize().width * 2)
	{
		moveDirection = Vec2(-1, _diretionY);
		walk(moveDirection);
		return true;
	}
	else if (isAkatsukiGroup() && getPositionX() <= (getGameLayer()->currentMap->getMapSize().width - 2) * getGameLayer()->currentMap->getTileSize().width)
	{
		moveDirection = Vec2(1, _diretionY);
		walk(moveDirection);
		return true;
	}
	else
	{
		return false;
	}
}

// [For AI] 检查角色是否需要使用【拉面】回血，若血量低于界限，则返回true
bool Unit::checkRetri()
{
	if (_isCanItem1 && getCoin() >= 50)
	{
		if (getGameLayer()->_isHardCoreGame)
		{
			if (battleCondiction >= 0)
			{
				if (!_isHealing)
				{
					if (getMaxHP() - getHP() >= 3000 + gearRecoverValue && getGearArray().size() > 1)
						setItem(Item1);
					else if (getHP() < 5000 && getGearArray().size() > 0)
						setItem(Item1);
					else if (getHP() < 1500)
						setItem(Item1);
				}
			}
			else
			{
				if (getMaxHP() - getHP() >= 3000 + gearRecoverValue && !_isHealing && getGearArray().size() > 0)
					setItem(Item1);
				else if (getHP() < 3000)
					setItem(Item1);
			}
		}
		else
		{
			if (getHP() < 1500 && isKonohaGroup())
				setItem(Item1);
			if (getHP() < 500 && isAkatsukiGroup())
				setItem(Item1);
		}
	}

	if (battleCondiction >= 0)
	{
		if (isKonohaGroup())
		{
			if (getPositionX() >= getGameLayer()->currentMap->getTileSize().width * 60)
				return false;
		}
		else
		{
			if (getPositionX() <= getGameLayer()->currentMap->getTileSize().width * 36)
				return false;
		}
	}

	if (getHP() < 1500 && !_isControlled)
		return true;
	return false;
}
