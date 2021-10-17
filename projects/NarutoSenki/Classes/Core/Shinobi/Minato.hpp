#pragma once
#include "Hero.hpp"

class Minato : public Hero
{
	void perform() override
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

		if (getCoinValue() >= 500 && !_isControlled && getGameLayer()->_enableGear)
		{
			if (getGearArray().size() == 0)
				setGear(gear06);
			else if (getGearArray().size() == 1)
				setGear(gear05);
			else if (getGearArray().size() == 2)
				setGear(gear02);
		}

		if (getHpPercent() < 0.3f)
		{
			if (_isCanSkill1)
			{
				bool isMark = false;
				if (hasMonsterArrayAny())
				{
					for (auto mo : _monsterArray)
					{
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
				bool isMark = false;
				if (hasMonsterArrayAny())
				{
					for (auto mo : _monsterArray)
					{
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
				else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getGP() < 5000)
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
				bool isMark = false;
				if (hasMonsterArrayAny())
				{
					for (auto mo : _monsterArray)
					{
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

	void changeAction() override
	{
		if (_skillChangeBuffValue == 17)
		{
			setSkill1Action(createAnimation(skillSPC1Array, 10.0f, false, true));

			if (isPlayer())
			{
				auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Minato_skill1_1.png");
				getGameLayer()->getHudLayer()->skill1Button->setDisplayFrame(frame);
				if (getGameLayer()->getHudLayer()->skill1Button->_clickNum < 2)
				{
					getGameLayer()->getHudLayer()->skill1Button->_clickNum++;
				}
			}
		}
		else if (_skillChangeBuffValue == 18)
		{
			setnAttackValue(to_ccstring(getNAttackValue() + 200));

			_nattackRangeX = 16;
			_nattackRangeY = 48;

			setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));
		}
	}

	void resumeAction(float dt) override
	{
		setnAttackValue(to_ccstring(getNAttackValue() - 200));
		_nattackRangeX = 16;
		_nattackRangeY = 48;
		setNAttackAction(createAnimation(nattackArray, 10.0f, false, true));

		_markPoint = ccp(0, 0);
		_startPoint = ccp(0, 0);
		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		setSkill1Action(createAnimation(skill1Array, 10.0f, false, true));
		_skillChangeBuffValue = 0;
	}
};
