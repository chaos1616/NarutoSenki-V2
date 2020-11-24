#pragma once
#include "Hero.hpp"

class Guardian : public Hero
{
	void perform()
	{
		if (!findTargetEnemy("Hero", true))
		{
			if (!findTargetEnemy("Flog", true))
			{
				if (!findTargetEnemy("Flog", false))
				{
					if (!findTargetEnemy("Hero", false))
					{
						_mainTarget = nullptr;
					}
				}
			}
		}

		if (_mainTarget)
		{
			CCPoint moveDirection;
			CCPoint sp = ccpSub(_mainTarget->getPosition(), getPosition());

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
			else if (getActionState() == State::IDLE || getActionState() == State::WALK || getActionState() == State::NATTACK)
			{
				bool isTurn = false;

				CCObject *pObject;
				CCARRAY_FOREACH(_delegate->_TowerArray, pObject)
				{
					CharacterBase *target = (CharacterBase *)pObject;
					const char *gardTower;
					if (getDelegate()->team > 0)
					{
						gardTower = "AkatsukiCenter";
					}
					else
					{
						gardTower = "KonohaCenter";
					}
					if (strcmp(target->getCharacter()->getCString(), gardTower) == 0 && target->getHpPercent() < 0.5f)
					{
						isTurn = true;
					}
				}

				if (_isCanSkill1 && !_skillChangeBuffValue && (getHpPercent() < 0.5f || isTurn))
				{
					changeSide(sp);
					attack(SKILL1);
					scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sattackcoldDown1);
				}
				else if (_isCanSkill2 && _skillChangeBuffValue)
				{
					changeSide(sp);
					attack(SKILL2);
					scheduleOnce(schedule_selector(CharacterBase::enableSkill2), _sattackcoldDown2);
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
			else
			{

				idle();
			}
		}
	}

	void changeAction()
	{
		setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) + 700));
		_nattackRangeX = 0;
		_nattackRangeY = 48;
		_tempAttackType = _nattackType;
		_nattackType = _spcattackType2;

		_isBati = true;
		isPofang = true;
		if (_hpBar)
		{
			_hpBar->setPositionY(120);
		}
		setWalkAction(createAnimation(skillSPC1Array, 10.0f, true, false));
		setNAttackAction(createAnimation(skillSPC2Array, 10.0f, false, true));
		setIdleAction(createAnimation(skillSPC3Array, 5.0f, true, false));
	}
};
