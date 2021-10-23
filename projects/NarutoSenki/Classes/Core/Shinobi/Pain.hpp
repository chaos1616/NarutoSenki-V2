#pragma once
#include "Hero.hpp"
#include "Shinobi/NarakaPath.hpp"

class Pain : public Hero
{
#define kPain__ "Pain"
#define kNagato "Nagato"

	void setID(CCString *character, CCString *role, CCString *group) override
	{
		Hero::setID(character, role, group);

		match_char_exp(kPain__, setAIHandler(Pain::perform),
					   kNagato, setAIHandler(Pain::perform_Nagato));
	}

	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(gear06, gear05, gear01);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (isFreeActionState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanSkill1)
				{
					changeSide(sp);
					attack(SKILL1);
				}
				if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000)
				{
					if ((abs(sp.x) > 196 || abs(sp.y) > 64))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if ((_isCanSkill2 || _isCanSkill3) && _mainTarget->getGP() < 5000 && _skillUPBuffValue)
				{
					if ((abs(sp.x) > 128 || abs(sp.y) > 32))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					if (_isCanSkill2)
					{
						changeSide(sp);
						attack(SKILL2);
						return;
					}

					if (_isCanSkill3)
					{
						changeSide(sp);
						attack(SKILL3);
						return;
					}
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isControlled)
				{
					if (abs(sp.x) < 160)
					{
						stepBack2();
						return;
					}
					else
					{
						idle();
						return;
					}
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
				if (_isCanSkill2 && _mainTarget->isFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanSkill3 && _mainTarget->isFlog() && isBaseDanger)
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

		checkHealingState();
	}

	void perform_Nagato()
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(gear06, gear05, gear07);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			CCPoint moveDirection;
			CCPoint sp = getDistanceToTarget();

			if (isFreeActionState())
			{
				if (_isCanSkill1 && !_buffStartTime)
				{
					int countNum = 0;
					for (auto hero : getGameLayer()->_CharacterArray)
					{
						if (isSameGroupAs(hero) == 0 &&
							hero->isPlayerOrCom() &&
							hero->getActionState() == State::DEAD)
						{
							CCPoint sp = ccpSub(hero->getPosition(), getPosition());
							if (abs(sp.x) == winSize.width || abs(sp.y) == winSize.height)
							{
								countNum++;
							}
						}
					}
					if (countNum >= 1)
					{
						attack(SKILL1);
						return;
					}
				}

				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game)
				{
					changeSide(sp);

					attack(OUGIS2);
					return;
				}
				if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000)
				{
					if ((abs(sp.x) > 196 || abs(sp.y) > 64))
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
					if ((abs(sp.x) > 128 || abs(sp.y) > 64))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getGP() < 5000)
				{
					if ((abs(sp.x) > 128 || abs(sp.y) > 64))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isControlled)
				{
					if (abs(sp.x) < 160)
					{
						stepBack2();
						return;
					}
					else
					{
						idle();
						return;
					}
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
				if (_isCanSkill2 && _mainTarget->isNotFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanSkill3 && _mainTarget->isNotFlog() && isBaseDanger)
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

		checkHealingState();
	}

	void changeAction() override
	{
		// TODO: New Pain
		// if (isCharacter("Nagato"))
		// {
		// 	if (_skillChangeBuffValue == 17)
		// 	{
		// 		setSkill1Action(createAnimation(skillSPC1Array, 10.0f, false, true));
		// 		setSkill2Action(createAnimation(skillSPC2Array, 10.0f, false, true));
		// 		setSkill3Action(createAnimation(skillSPC3Array, 10.0f, false, true));
		// 		settempAttackValue1(to_ccstring(to_int(_sattackValue1->getCString())));
		// 		setsAttackValue1(_spcattackValue1);
		// 		setsAttackValue2(_spcattackValue2);
		// 		setsAttackValue3(_spcattackValue3);

		// 		if (isPlayer())
		// 		{
		// 			auto cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		// 			auto frame = cache->spriteFrameByName("Nagato_skill1_1.png");
		// 			getGameLayer()->getHudLayer()->skill1Button->setDisplayFrame(frame);
		// 			frame = cache->spriteFrameByName("Nagato_skill2_1.png");
		// 			getGameLayer()->getHudLayer()->skill2Button->setDisplayFrame(frame);
		// 			frame = cache->spriteFrameByName("Nagato_skill3_1.png");
		// 			getGameLayer()->getHudLayer()->skill3Button->setDisplayFrame(frame);
		// 		}
		// 	}
		// }
	}

	void setActionResume() override
	{
		// TODO: New Pain
		// if (isCharacter("Nagato"))
		// {
		// 	if (_skillChangeBuffValue == 17)
		// 	{
		// 		this->setSkill1Action(createAnimation(skill1Array, 10.0f, false, true));
		// 		this->setSkill2Action(createAnimation(skill2Array, 10.0f, false, true));
		// 		this->setSkill3Action(createAnimation(skill3Array, 10.0f, false, true));

		// 		if (isPlayer())
		// 		{
		// 			auto cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		// 			auto frame = cache->spriteFrameByName("Nagato_skill1.png");
		// 			getGameLayer()->getHudLayer()->skill1Button->setDisplayFrame(frame);
		// 			frame = cache->spriteFrameByName("Nagato_skill2.png");
		// 			getGameLayer()->getHudLayer()->skill2Button->setDisplayFrame(frame);
		// 			frame = cache->spriteFrameByName("Nagato_skill3.png");
		// 			getGameLayer()->getHudLayer()->skill3Button->setDisplayFrame(frame);
		// 		}
		// 	}

		// 	_skillChangeBuffValue = 0;
		// }
	}

	Hero *createClone(int cloneTime) override
	{
		Hero *clone = nullptr;

		// TODO: New Pain
		// if (isCharacter(kPain__))
		// {
		// 	clone = create<NarakaPath>(CCString::create("NarakaPath"), CCString::create(kRoleClone), getGroup());
		// 	clone->_isArmored = true;

		// 	if (isPlayer())
		// 	{
		// 		getGameLayer()->getHudLayer()->skill5Button->setLock();
		// 	}
		// }
		if (isCharacter(kNagato)) // Old Nagato skill
		{
			clone = create<NarakaPath>(CCString::create("NarakaPath"), CCString::create(kRoleClone), getGroup());
			clone->_isArmored = true;

			if (isPlayer())
			{
				getGameLayer()->getHudLayer()->skill5Button->setLock();
			}

			_skillChangeBuffValue = 100;
		}

		return clone;
	}
};
