#pragma once
#include "Hero.hpp"

class Minato : public Hero
{
	void perform()
	{
		_mainTarget = nullptr;
		findHeroHalf();

		if (_isCanGear06)
		{
			if ((_actionState == State::FLOAT ||
				 _actionState == State::AIRHURT ||
				 _actionState == State::HURT ||
				 _actionState == State::KNOCKDOWN) &&
				getHpPercent() < 0.5 && !_isArmored && !_isInvincible)
			{
				useGear(gear06);
			}
		}

		if (getCoinValue() >= 500 && !_isControlled && _delegate->_enableGear)
		{
			if (getGearArray()->count() == 0)
				setGear(gear06);
			else if (getGearArray()->count() == 1)
				setGear(gear05);
			else if (getGearArray()->count() == 2)
				setGear(gear02);
		}

		if (getHpPercent() < 0.3f)
		{
			if (_isCanSkill1)
			{
				CCObject *pObject;
				bool isMark = false;
				if (hasMonsterArrayAny())
				{
					CCARRAY_FOREACH(getMonsterArray(), pObject)
					{
						Monster *mo = (Monster *)pObject;
						if (mo->isCharacter("HiraishinMark"))
						{
							if (isKonohaGroup() && mo->getPositionX() < getPositionX())
							{
								isMark = true;
							}
							else if (isAkatsukiGroup() && mo->getPositionX() > getPositionX())
							{
								isMark = true;
							}
						}
					}
				}
				if (isFreeActionState())
				{
					if (isMark)
					{
						attack(SKILL1);
						return;
					}
				}
			}
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

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (isFreeActionState())
			{
				CCObject *pObject;
				bool isMark = false;
				if (hasMonsterArrayAny())
				{
					CCARRAY_FOREACH(getMonsterArray(), pObject)
					{
						Monster *mo = (Monster *)pObject;
						if (mo->isCharacter("HiraishinMark"))
						{
							isMark = true;
						}
					}
				}

				if (_isCanSkill1 && !isMark)
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && _mainTarget->getGP() < 5000)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 16)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(OUGIS2);

					return;
				}
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 16)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getGP() < 5000)
				{
					if (abs(sp.y) > 16)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControlled && !_skillChangeBuffValue)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (_isCanSkill3)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else
				{
					if (abs(sp.x) > 352 || abs(sp.y) > 128)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && getNAttackValue() < 260)
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
		_mainTarget = nullptr;
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
				if (_isCanSkill3 && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL3);
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
			if (_isCanSkill1)
			{
				CCObject *pObject;
				bool isMark = false;
				if (hasMonsterArrayAny())
				{
					CCARRAY_FOREACH(getMonsterArray(), pObject)
					{
						Monster *mo = (Monster *)pObject;
						if (mo->isCharacter("HiraishinMark"))
						{
							if (isKonohaGroup() && mo->getPositionX() > getPositionX())
							{
								isMark = true;
							}
							else if (isAkatsukiGroup() && mo->getPositionX() < getPositionX())
							{
								isMark = true;
							}
						}
					}
				}
				if (isFreeActionState())
				{
					if (isMark)
					{
						attack(SKILL1);
						return;
					}
				}
			}

			stepOn();
		}
	}

	void changeAction()
	{
		if (_skillChangeBuffValue == 17)
		{
			setSkill1Action(createAnimation(skillSPC1Array, 10.0f, false, true));

			if (isPlayer())
			{
				CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Minato_skill1_1.png");
				_delegate->getHudLayer()->skill1Button->setDisplayFrame(frame);
				if (_delegate->getHudLayer()->skill1Button->_clickNum < 2)
				{
					_delegate->getHudLayer()->skill1Button->_clickNum++;
				}
			}
		}
		else if (_skillChangeBuffValue == 18)
		{
			setnAttackValue(CCString::createWithFormat("%d", getNAttackValue() + 200));

			_nattackRangeX = 16;
			_nattackRangeY = 48;

			setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));
		}
	}

	void resumeAction(float dt)
	{
		setnAttackValue(CCString::createWithFormat("%d", getNAttackValue() - 200));
		_nattackRangeX = 16;
		_nattackRangeY = 48;
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));

		_markPoint = ccp(0, 0);
		_startPoint = ccp(0, 0);
		CharacterBase::resumeAction(dt);
	}

	void setActionResume()
	{
		setSkill1Action(createAnimation(skill1Array, 10.0f, false, true));
		_skillChangeBuffValue = 0;
	}
};
