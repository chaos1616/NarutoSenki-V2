#pragma once
#include "Core/Hero.hpp"
#include "Core/Unit.h"

// Detailed implementation of FindTarget module of unit base class

bool Unit::findEnemy(Role role, int searchRange, bool masterRange)
{
	if (role == Role::Hero)
	{
		return findEnemyBy(getGameLayer()->_CharacterArray, searchRange, masterRange);
	}
	else if (role == Role::Flog)
	{
		if (isAkatsukiGroup())
			return findEnemyBy(getGameLayer()->_KonohaFlogArray, searchRange, masterRange);
		else
			return findEnemyBy(getGameLayer()->_AkatsukiFlogArray, searchRange, masterRange);
	}
	else if (role == Role::Tower)
	{
		return findEnemyBy(getGameLayer()->_TowerArray, searchRange, masterRange);
	}

	return false;
}

template <typename T>
typename std::enable_if_t<std::is_base_of_v<Unit, T>, bool>
// template find ememy
Unit::findEnemyBy(const vector<T *> &list, int searchRange, bool masterRange)
{
	float distance;
	float curDistance = 0;
	Vec2 sp;
	bool findSome = false;

	for (auto target : list)
	{
		if (target->_state == State::DEAD ||
			target->_isVisable == false ||
			target->_isInvincible ||
			target->isKugutsu())
		{
			continue;
		}

		if ((_state == State::OATTACK || _state == State::O2ATTACK) ||
			(_master && (_master->_state == State::OATTACK || _state == State::O2ATTACK)))
		{
			if (target->isClone() ||
				target->isSummon() ||
				target->isMon())
			{
				continue;
			}
		}

		if (_group != target->_group)
		{
			if (masterRange && _master)
			{
				sp = target->getPosition() - _master->getPosition();
				distance = sp.getLength();
			}
			else
			{
				sp = target->getPosition() - getPosition();
				distance = sp.getLength();
			}

			if (abs(sp.x) < (searchRange ? searchRange : kAttackRange))
			{
				if (target->_isTaunt)
				{
					_mainTarget = target;
					return true;
				}
				if (curDistance && abs(curDistance) > abs(distance))
				{
					_mainTarget = target;
					curDistance = distance;
				}
				else if (!curDistance)
				{
					findSome = true;
					curDistance = distance;
					_mainTarget = target;
				}
			}
		}
	}

	return findSome;
}

// NOTE: Use half the window width as the search range
bool Unit::findEnemy2(Role role)
{
	if (role == Role::Hero)
	{
		return findEnemy2By(getGameLayer()->_CharacterArray);
	}
	else if (role == Role::Flog)
	{
		if (isAkatsukiGroup())
			return findEnemy2By(getGameLayer()->_KonohaFlogArray);
		else
			return findEnemy2By(getGameLayer()->_AkatsukiFlogArray);
	}
	else if (role == Role::Tower)
	{
		return findEnemy2By(getGameLayer()->_TowerArray);
	}

	return false;
}

template <typename T>
typename std::enable_if_t<std::is_base_of_v<Unit, T>, bool>
// template find ememy 2
Unit::findEnemy2By(const vector<T *> &list)
{
	float distance;
	float curDistance = 0;
	Vec2 sp;
	bool findSome = false;

	enemyCombatPoint = 0;
	friendCombatPoint = 0;

	for (auto target : list)
	{
		if (target->_state == State::DEAD ||
			target->_isVisable == false ||
			target->isKugutsu())
		{
			continue;
		}

		sp = target->getPosition() - getPosition();
		distance = sp.getLength();
		if (abs(sp.x) < kAttackRange)
		{
			if (target->isNotClone() && target->isNotSummon())
			{
				int baseSkillCombatPoint = 0;

				if (target->_isCanSkill1)
					baseSkillCombatPoint += _sAttackCombatPoint1;
				if (target->_isCanSkill2)
					baseSkillCombatPoint += _sAttackCombatPoint2;
				if (target->_isCanSkill2)
					baseSkillCombatPoint += _sAttackCombatPoint3;

				if (_group == target->_group)
				{
					if (abs(sp.x) < getGameLayer()->currentMap->getTileSize().width * 3)
					{
						if (target->isNotGuardian())
						{
							friendCombatPoint += baseSkillCombatPoint + target->getHP() +
												 (target->getCKR() / 15000) * target->_sAttackCombatPoint4 +
												 (target->getCKR2() / 25000) * target->_sAttackCombatPoint5;
						}
					}
				}
				else
				{
					if (target->isNotGuardian())
					{
						enemyCombatPoint += baseSkillCombatPoint + target->getHP() +
											(target->getCKR() / 15000) * target->_sAttackCombatPoint4 +
											(target->getCKR2() / 25000) * target->_sAttackCombatPoint5;
					}

					if (!target->_isInvincible && (target->getPositionX() >= getGameLayer()->currentMap->getTileSize().width * 3 && target->getPositionX() <= (getGameLayer()->currentMap->getMapSize().width - 3) * getGameLayer()->currentMap->getTileSize().width))
					{
						if (curDistance && curDistance > distance)
						{
							_mainTarget = target;
							curDistance = distance;
						}
						else if (!curDistance)
						{
							findSome = true;
							curDistance = distance;
							_mainTarget = target;
						}
					}
				}
			}
		}
	}

	return findSome;
}

bool Unit::findTargetEnemy(Role role, bool isTowerDected)
{
	if (role == Role::Hero)
	{
		return findTargetEnemyBy(getGameLayer()->_CharacterArray, isTowerDected);
	}
	else if (role == Role::Flog)
	{
		if (isAkatsukiGroup())
			return findTargetEnemyBy(getGameLayer()->_KonohaFlogArray, isTowerDected);
		else
			return findTargetEnemyBy(getGameLayer()->_AkatsukiFlogArray, isTowerDected);
	}

	return false;
}

template <typename T>
typename std::enable_if_t<std::is_base_of_v<Unit, T>, bool>
Unit::findTargetEnemyBy(const vector<T *> &list, bool isTowerDected)
{
	Vec2 sp;
	bool findSome = false;

	for (auto target : list)
	{
		if (getGroup() != target->getGroup() &&
			target->isNotKugutsu() &&
			target->_state != State::DEAD &&
			target->_isVisable && !target->_isInvincible)
		{
			// float gardZone
			bool found = getGameLayer()->playerGroup == Group::Konoha
							 ? target->getPositionX() >= 81 * 32
							 : target->getPositionX() <= 14 * 32;
			if (found)
			{
				findSome = true;
				if (target->isHurtingTower)
				{
					if (target->getName() == HeroEnum::Choji ||
						target->getName() == HeroEnum::Sakura)
					{
						_mainTarget = target;
						return true;
					}
					_mainTarget = target;
				}

				if (!isTowerDected)
				{
					_mainTarget = target;
				}
			}
		}
	}

	if (!isTowerDected)
		return findSome;
	else
		return false;
}
