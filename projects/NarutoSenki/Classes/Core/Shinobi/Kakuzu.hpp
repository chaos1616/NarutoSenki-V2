#pragma once
#include "Hero.hpp"
#include "Kuchiyose/Mask.hpp"

class Kakuzu : public Hero
{
	void dead() override
	{
		CharacterBase::dead();

		if (_heartEffect)
		{
			auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Heart_Effect_%02d.png", hearts)->getCString());
			_heartEffect->setDisplayFrame(frame);
		}

		if (isPlayer() && getLV() >= 2)
		{
			_delegate->getHudLayer()->skill4Button->unLock();
		}
	}

	void changeHPbar() override
	{
		HeroElement::changeHPbar();

		if (isNotPlayer())
			return;

		// NOTE: The level was increased on base
		// We should do the same here
		if (_exp >= 500 && _level == 1 + 1)
		{
			if (hearts < 1)
			{
				_delegate->getHudLayer()->skill4Button->setLock();
			}
		}
		else if (_exp >= 1500 && _level == 3 + 1)
		{
			_delegate->getHudLayer()->skill5Button->setLock();
		}
	}

	void perform() override
	{
		_mainTarget = nullptr;
		if (isFreeActionState())
		{
			if (getHpPercent() > 0.3f && !_isControlled && _isCanSkill1)
			{
				CCObject *pObject;
				float distance;
				float curDistance = 0;
				CCPoint sp;

				CCARRAY_FOREACH(getDelegate()->_CharacterArray, pObject)
				{
					auto target = (CharacterBase *)pObject;
					if (target->isPlayerOrCom() &&
						target->getActionState() == State::DEAD)
					{
						distance = ccpDistance(target->getPosition(), getPosition());
						sp = ccpSub(target->getPosition(), getPosition());

						if (abs(sp.x) < (winSize.width / 2))
						{
							if (target->_isTaunt)
							{
								_mainTarget = target;
							}
							if (curDistance && abs(curDistance) > abs(distance))
							{
								_mainTarget = target;
								curDistance = distance;
							}
							else if (!curDistance)
							{
								curDistance = distance;
								_mainTarget = target;
							}
						}
					}
				}

				if (_mainTarget)
				{
					CCPoint moveDirection;
					if (_mainTarget->_originY)
					{
						sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
					}
					else
					{
						sp = ccpSub(_mainTarget->getPosition(), getPosition());
					}

					if (abs(sp.x) > 32 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else
					{
						changeSide(sp);
						attack(SKILL1);
					}

					return;
				}
			}
		}

		findHeroHalf();
		if (getCoinValue() >= 500 && !_isControlled && _delegate->_enableGear)
		{
			if (getGearArray()->count() == 0)
				setGear(gear03);
			else if (getGearArray()->count() == 1)
				setGear(gear08);
			else if (getGearArray()->count() == 2)
				setGear(gear04);
		}

		if (checkRetri())
		{
			if (_mainTarget != nullptr)
			{
				if (stepBack2())
					return;
			}
			else
			{
				if (stepBack())
					return;
			}
		}

		if (isBaseDanger && checkBase() && !_isControlled)
		{
			bool needBack = false;
			if (isAkatsukiGroup())
			{
				if (getPositionX() < 85 * 32)
					needBack = true;
			}
			else
			{
				if (getPositionX() > 11 * 32)
					needBack = true;
			}
			if (needBack)
			{
				if (stepBack2())
					return;
			}
		}

		bool isSummonAble = false;

		if (((getMonsterArray() && getMonsterArray()->count() < 3) || !_monsterArray) && hearts > 0)
		{
			isSummonAble = true;
		}

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (isFreeActionState())
			{
				if (_isCanSkill3)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (_isCanOugis1 && !_isControlled && isSummonAble)
				{
					attack(OUGIS1);
					return;
				}
				else if (_isCanSkill2)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanGear03)
					{
						useGear(gear03);
					}

					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 5000 && !_isHealling && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if (abs(sp.x) > 32 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else
					{
						changeSide(sp);
						attack(NAttack);
					}

					return;
				}
			}
		}

		if (notFindFlogHalf())
			findTowerHalf();

		if (_mainTarget)
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				walk(moveDirection);
				return;
			}

			if (isFreeActionState())
			{
				if (_isCanOugis1 && !_isControlled && !isSummonAble)
				{
					changeSide(sp);
					attack(OUGIS1);
				}
				else
				{
					changeSide(sp);
					attack(NAttack);
				}
			}
			return;
		}

		if (_isHealling && getHpPercent() < 1)
		{
			if (isFreeActionState())
				idle();
		}
		else
		{
			stepOn();
		}
	}

	void changeAction() override
	{
		setBuffEffect("jdBuff");
	}

	void resumeAction(float dt) override
	{
		removeBuffEffect("sBuff");
	}

	void setActionResume() override
	{
		if (_skillChangeBuffValue == 0)
			return;

		unschedule(schedule_selector(Kakuzu::resumeAction));
		removeBuffEffect("sBuff");

		_skillChangeBuffValue = 0;
	}

	Hero *createClone(int cloneTime) override
	{
		if (!_monsterArray)
		{
			_monsterArray = CCArray::create();
			_monsterArray->retain();
		}
		bool isRaiton = false;
		bool isFuton = false;
		bool isKaton = false;
		int countMon = 0;
		if (hasMonsterArrayAny())
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				auto mo = (Monster *)pObject;
				if (mo->isCharacter("MaskRaiton"))
				{
					countMon++;
					isRaiton = true;
				}
				if (mo->isCharacter("MaskFuton"))
				{
					countMon++;
					isFuton = true;
				}
				if (mo->isCharacter("MaskKaton"))
				{
					countMon++;
					isKaton = true;
				}
			}
		}

		Hero *clone = nullptr;
		if (hearts > 0 && (!isRaiton || !isKaton || !isFuton))
		{
			if (!isRaiton)
			{
				clone = create<Mask>(CCString::create("MaskRaiton"), CCString::create(kRoleKugutsu), getGroup());
			}
			else if (!isFuton)
			{
				clone = create<Mask>(CCString::create("MaskFuton"), CCString::create(kRoleKugutsu), getGroup());
			}
			else if (!isKaton)
			{
				clone = create<Mask>(CCString::create("MaskKaton"), CCString::create(kRoleKugutsu), getGroup());
			}
			clone->_isArmored = true;
			_monsterArray->addObject(clone);

			hearts -= 1;
			if (_heartEffect)
			{
				auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Heart_Effect_%02d.png", hearts)->getCString());
				_heartEffect->setDisplayFrame(frame);
			}

			if (hearts < 1 || countMon >= 2)
			{
				if (isPlayer())
				{
					_delegate->getHudLayer()->skill4Button->setLock();
				}
			}
		}

		return clone;
	}
};
