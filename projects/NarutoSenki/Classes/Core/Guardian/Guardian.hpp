#pragma once
#include "Hero.hpp"
#include "Core/Tower/Tower.hpp"

class Guardian : public Hero
{
	void perform() override
	{
		if (!findTargetEnemy(kRoleHero, true))
		{
			if (!findTargetEnemy(kRoleFlog, true))
			{
				if (!findTargetEnemy(kRoleFlog, false))
				{
					if (!findTargetEnemy(kRoleHero, false))
					{
						_mainTarget = nullptr;
					}
				}
			}
		}

		if (_mainTarget)
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTargetAndIgnoreOriginY();

			if (abs(sp.x) > 128 || abs(sp.y) > 16)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}
			else if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (isFreeActionState())
			{
				bool isTurn = false;
				auto gardTower = getGameLayer()->getGuardianGroup();

				for (auto targetTower : getGameLayer()->_TowerArray)
				{
					if (targetTower->isCharacter(gardTower) && targetTower->getHpPercent() < 0.5f)
					{
						isTurn = true;
					}
				}

				if (_isCanSkill1 && !_skillChangeBuffValue && (getHpPercent() < 0.5f || isTurn))
				{
					changeSide(sp);
					attack(SKILL1);
					scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sattackcooldown1);
				}
				else if (_isCanSkill2 && _skillChangeBuffValue)
				{
					changeSide(sp);
					attack(SKILL2);
					scheduleOnce(schedule_selector(CharacterBase::enableSkill2), _sattackcooldown2);
				}
				else
				{
					changeSide(sp);
					attack(NAttack);
				}
			}

			return;
		}
		else
		{
			CCPoint moveDirection;
			CCPoint sp = ccpSub(getSpawnPoint(), getPosition());

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			idle();
		}
	}

	void changeAction() override
	{
		setnAttackValue(to_ccstring(getNAttackValue() + 700));
		_nattackRangeX = 0;
		_nattackRangeY = 48;
		_originNAttackType = _nattackType;
		_nattackType = _spcattackType2;

		_isArmored = true;
		hasArmorBroken = true;
		if (_hpBar)
		{
			_hpBar->setPositionY(120);
		}
		setWalkAction(createAnimation(skillSPC1Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC2Array, 10.0f, false, true));
		setIdleAction(createAnimation(skillSPC3Array, 5.0f, true, false));
	}

private:
	string _originNAttackType;
};
