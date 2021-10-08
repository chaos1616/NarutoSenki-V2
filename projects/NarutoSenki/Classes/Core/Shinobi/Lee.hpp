#pragma once
#include "Hero.hpp"

class Lee : public Hero
{
#define kLee____ "Lee"
#define kRockLee "RockLee"

	static const uint8_t kMax_Lee_HachimonTonkouLevel = 5;

	// Hachimon tonkou level
	uint8_t htLv = 0;

	void setID(CCString *character, CCString *role, CCString *group) override
	{
		Hero::setID(character, role, group);

		match_char_exp(kLee____, setAIHandler(Lee::perform),
					   kRockLee, setAIHandler(Lee::perform_RockLee));

		// NOTE: Because Lee can transform to RockLee
		if (getGameLayer()->isHUDInit())
			tryLockSkillButton();
		else
			getGameLayer()->onHUDInitialized(BIND(Lee::tryLockSkillButton));
	}

	void dead() override
	{
		CharacterBase::dead();

		if (htLv > 0)
		{
			if (htLv == 5)
			{
				setWalkSpeed(224);
				_originSpeed = 224;
				setWalkAction(createAnimation(walkArray, 10.0f, true, false));
				setsAttackValue3(to_ccstring(getSAttackValue3() - 100));
				setsAttackValue2(to_ccstring(getSAttackValue2() - 100));
				setnAttackValue(to_ccstring(getNAttackValue() - 60));
			}
			else if (htLv == 4)
			{
				setsAttackValue3(to_ccstring(getSAttackValue3() - 100));
				setsAttackValue2(to_ccstring(getSAttackValue2() - 100));
			}
			else if (htLv == 3)
			{
				setTransform();

				if (isPlayer())
				{
					getGameLayer()->getHudLayer()->skill3Button->setLock();
				}

				if (_skillBuffEffect)
				{
					_skillBuffEffect->removeFromParent();
					_skillBuffEffect = nullptr;
				}
			}
			else if (htLv == 2)
			{
				setsAttackValue2(to_ccstring(getSAttackValue2() - 100));
			}
			else if (htLv == 1)
			{
				if (isPlayer())
				{
					getGameLayer()->getHudLayer()->skill4Button->setLock();
				}
				setnAttackValue(to_ccstring(getNAttackValue() - 30));
			}
			htLv--;

			if (htLv == 0)
			{
				_heartEffect->removeFromParent();
				_heartEffect = nullptr;
			}
			else
			{
				auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Bamen_Effect_%02d.png", htLv - 1)->getCString());
				_heartEffect->setDisplayFrame(frame);
			}
		}
	}

	void changeHPbar() override
	{
		HeroElement::changeHPbar();

		if (isNotPlayer())
			return;

		if (isCharacter(kLee____))
		{
			// NOTE: See `Kakuzu::changeHPbar()`
			if (_exp >= 500 && _level == 1 + 1)
			{
				if (htLv < 1)
					getGameLayer()->getHudLayer()->skill4Button->setLock();
			}
			else if (_exp >= 1500 && _level == 3 + 1)
			{
				if (htLv < 3)
					getGameLayer()->getHudLayer()->skill5Button->setLock();
			}
		}
	}

	void changeAction() override
	{
		if (htLv == 0 && !_heartEffect)
		{
			_heartEffect = CCSprite::createWithSpriteFrameName("Bamen_Effect_00.png");
			_heartEffect->setPosition(ccp(getContentSize().width + 40, 60));
			addChild(_heartEffect);
		}

		if (htLv < kMax_Lee_HachimonTonkouLevel)
		{
			htLv++;
			auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Bamen_Effect_%02d.png", htLv - 1)->getCString());
			_heartEffect->setDisplayFrame(frame);
		}
		else
		{
			return;
		}

		if (htLv == 1)
		{
			setnAttackValue(to_ccstring(getNAttackValue() + 30));

			if (isPlayer())
			{
				getGameLayer()->getHudLayer()->skill4Button->unLock();
			}
		}
		else if (htLv == 2)
		{
			setsAttackValue2(to_ccstring(getSAttackValue2() + 100));
		}
		else if (htLv == 3)
		{
			if (!_skillBuffEffect)
			{
				setBuffEffect("bmBuff");
			}
			setTransform();

			if (isPlayer())
				getGameLayer()->getHudLayer()->skill3Button->unLock();

			unlockSkill5Button();
		}
		else if (htLv == 4)
		{
			setsAttackValue2(to_ccstring(getSAttackValue2() + 100));
			setsAttackValue3(to_ccstring(getSAttackValue3() + 100));
		}
		else if (htLv == 5)
		{
			setWalkAction(createAnimation(skillSPC1Array, 10.0f, true, false));
			setWalkSpeed(320);
			_originSpeed = 320;
			setsAttackValue2(to_ccstring(getSAttackValue2() + 100));
			setsAttackValue3(to_ccstring(getSAttackValue3() + 100));
			setnAttackValue(to_ccstring(getNAttackValue() + 60));
		}
	}

	void setRestore2(float dt) override
	{
		CharacterBase::setRestore2(dt);

		uint32_t hp = getHPValue();

		// TODO: Make Maito Gai
		// if (htLv >= 8)
		// {
		// 	setHPValue(hp > 1000 ? hp - 1000 : 100);
		// }
		if (htLv >= 5)
		{
			setHPValue(hp > 200 ? hp - 200 : 100);
		}
		else if (htLv >= 4)
		{
			setHPValue(hp > 150 ? hp - 150 : 100);
		}
		else if (htLv >= 3)
		{
			setHPValue(hp > 100 ? hp - 100 : 100);
		}
	}

	// Lee

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
			if (getGearArray()->count() == 0)
				setGear(gear06);
			else if (getGearArray()->count() == 1)
				setGear(gear07);
			else if (getGearArray()->count() == 2)
				setGear(gear02);
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

			if ((isFreeActionState()) && abs(sp.x) < 128)
			{
				if (_isCanSkill1 && htLv < 5)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking && htLv >= 1)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill2)
					{
						changeSide(sp);
						attack(SKILL2);
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
				if (_isCanSkill2 && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL2);
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

	// RockLee

	void perform_RockLee()
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
			if (getGearArray()->count() == 0)
				setGear(gear06);
			else if (getGearArray()->count() == 1)
				setGear(gear07);
			else if (getGearArray()->count() == 2)
				setGear(gear02);
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
				if (_isCanSkill1 && htLv < 5)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking && htLv >= 3)
				{
					changeSide(sp);
					attack(OUGIS2);
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128 || htLv >= 5)
				{
					if (abs(sp.x) > 46 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking && htLv >= 1)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill2)
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else if (_isCanSkill3 && htLv >= 3)
					{
						changeSide(sp);
						attack(SKILL3);
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
				if (_isCanSkill2 && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanSkill3 && htLv >= 3 && isBaseDanger && _mainTarget->isFlog())
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
			stepOn();
		}
	}

private:
	inline void tryLockSkillButton()
	{
		if (htLv < 3 && isPlayer())
		{
			getGameLayer()->getHudLayer()->skill3Button->setLock();
		}
	}
};
