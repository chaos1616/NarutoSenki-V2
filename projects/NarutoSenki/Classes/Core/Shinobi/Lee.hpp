#pragma once
#include "Hero.hpp"

class Lee : public Hero
{
#define kLee____ "Lee"
#define kRockLee "RockLee"

	unsigned int bamen = 0;

	void setID(CCString *character, CCString *role, CCString *group)
	{
		Hero::setID(character, role, group);

		match_char_exp(kLee____, setAIHandler(Lee::perform),
					   kRockLee, setAIHandler(Lee::perform_RockLee));
	}

	void dead()
	{
		CharacterBase::dead();

		if (bamen > 0)
		{
			if (bamen == 5)
			{

				setWalkSpeed(224);
				_originSpeed = 224;
				setWalkAction(createAnimation(walkArray, 10.0f, true, false));
				setsAttackValue3(CCString::createWithFormat("%d", to_int(getsAttackValue3()->getCString()) - 100));
				setsAttackValue2(CCString::createWithFormat("%d", to_int(getsAttackValue2()->getCString()) - 100));
				setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) - 60));
			}
			else if (bamen == 4)
			{
				setsAttackValue3(CCString::createWithFormat("%d", to_int(getsAttackValue3()->getCString()) - 100));
				setsAttackValue2(CCString::createWithFormat("%d", to_int(getsAttackValue2()->getCString()) - 100));
			}
			else if (bamen == 3)
			{
				setTransform();

				if (is_player)
				{
					if (_delegate->getHudLayer()->skill3Button)
					{
						_delegate->getHudLayer()->skill3Button->setLock();
					}
				}

				if (_skillBuffEffect)
				{
					_skillBuffEffect->removeFromParent();
					_skillBuffEffect = nullptr;
				}
			}
			else if (bamen == 2)
			{
				setsAttackValue2(CCString::createWithFormat("%d", to_int(getsAttackValue2()->getCString()) - 100));
			}
			else if (bamen == 1)
			{
				if (is_player)
				{
					if (_delegate->getHudLayer()->skill4Button)
					{
						_delegate->getHudLayer()->skill4Button->setLock();
					}
				}
				setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) - 30));
			}
			bamen -= 1;
			if (bamen == 0)
			{
				_heartEffect->removeFromParent();
				_heartEffect = nullptr;
			}
			else
			{
				CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Bamen_Effect_%02d.png", bamen - 1)->getCString());
				_heartEffect->setDisplayFrame(frame);
			}
		}
	}

	void changeHPbar()
	{
		HeroElement::changeHPbar();

		if (not_player)
			return;

		if (character_is(kLee____))
		{
			if (_exp >= 500 && _level == 1)
			{
				if (bamen < 1)
				{
					if (_delegate->getHudLayer()->skill4Button)
					{
						_delegate->getHudLayer()->skill4Button->setLock();
					}
				}
			}
			else if (_exp >= 1500 && _level == 3)
			{
				if (bamen < 3)
				{
					if (_delegate->getHudLayer()->skill5Button)
					{
						_delegate->getHudLayer()->skill5Button->setLock();
					}
				}
			}
		}
	}

	void changeAction()
	{
		if (bamen == 0 && !_heartEffect)
		{
			_heartEffect = CCSprite::createWithSpriteFrameName("Bamen_Effect_00.png");
			_heartEffect->setPosition(ccp(getContentSize().width + 40, 60));
			addChild(_heartEffect);
		}
		if (bamen < 5)
		{
			bamen += 1;
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Bamen_Effect_%02d.png", bamen - 1)->getCString());
			_heartEffect->setDisplayFrame(frame);
		}
		else
		{
			return;
		}

		if (bamen == 1)
		{
			setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) + 30));
			if (is_player)
			{
				if (_delegate->getHudLayer()->skill4Button)
				{
					_delegate->getHudLayer()->skill4Button->unLock();
				}
			}
		}
		else if (bamen == 2)
		{
			setsAttackValue2(CCString::createWithFormat("%d", to_int(getsAttackValue2()->getCString()) + 100));
		}
		else if (bamen == 3)
		{
			if (!_skillBuffEffect)
			{
				setBuffEffect("bmBuff");
			}
			setTransform();

			if (is_player)
			{
				_delegate->getHudLayer()->skill3Button->unLock();
			}

			if (is_player)
			{
				if (_delegate->getHudLayer()->skill5Button)
				{
					_delegate->getHudLayer()->skill5Button->unLock();
				}
			}
		}
		else if (bamen == 4)
		{
			setsAttackValue2(CCString::createWithFormat("%d", to_int(getsAttackValue2()->getCString()) + 100));
			setsAttackValue3(CCString::createWithFormat("%d", to_int(getsAttackValue3()->getCString()) + 100));
		}
		else if (bamen == 5)
		{
			setWalkAction(createAnimation(skillSPC1Array, 10.0f, true, false));
			setWalkSpeed(320);
			_originSpeed = 320;
			setsAttackValue2(CCString::createWithFormat("%d", to_int(getsAttackValue2()->getCString()) + 100));
			setsAttackValue3(CCString::createWithFormat("%d", to_int(getsAttackValue3()->getCString()) + 100));
			setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) + 60));
		}
	}

	void setRestore2(float dt)
	{
		CharacterBase::setRestore2(dt);

		if (!_hpBar)
			return;

		if (bamen >= 8)
		{
			if (to_uint(getHP()->getCString()) - 1000 > 0)
			{
				setHP(CCString::createWithFormat("%ld", to_uint(getHP()->getCString()) - 1000));
				_hpBar->loseHP(getHpPercent());
			}
			else
			{
				setHP(CCString::createWithFormat("%d", 100));
				_hpBar->loseHP(getHpPercent());
			}
		}
		else if (bamen >= 5)
		{
			if (to_uint(getHP()->getCString()) - 200 > 0)
			{
				setHP(CCString::createWithFormat("%ld", to_uint(getHP()->getCString()) - 200));
				_hpBar->loseHP(getHpPercent());
			}
			else
			{
				setHP(CCString::createWithFormat("%d", 100));
				_hpBar->loseHP(getHpPercent());
			}
		}
		else if (bamen >= 4)
		{
			if (to_uint(getHP()->getCString()) - 150 > 0)
			{
				setHP(CCString::createWithFormat("%ld", to_uint(getHP()->getCString()) - 150));
				_hpBar->loseHP(getHpPercent());
			}
			else
			{
				setHP(CCString::createWithFormat("%d", 100));
				_hpBar->loseHP(getHpPercent());
			}
		}
		else if (bamen >= 3)
		{
			if (to_uint(getHP()->getCString()) - 100 > 0)
			{
				setHP(CCString::createWithFormat("%ld", to_uint(getHP()->getCString()) - 100));
				_hpBar->loseHP(getHpPercent());
			}
			else
			{
				setHP(CCString::createWithFormat("%d", 100));
				_hpBar->loseHP(getHpPercent());
			}
		}
	}

	// Lee

	void perform()
	{

		_mainTarget = nullptr;
		findEnemy2("Hero");

		if (_isCanGear06)
		{
			if ((getActionState() == State::FLOAT ||
				 getActionState() == State::AIRHURT ||
				 getActionState() == State::HURT ||
				 getActionState() == State::KNOCKDOWN) &&
				getHpPercent() < 0.5 && !_isBati && !_isWudi)
			{
				useGear(gear06);
			}
		}
		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear06);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear07);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear02);
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
			if (strcmp(Akatsuki, getGroup()->getCString()) == 0)
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

		if (_mainTarget && strcmp(_mainTarget->getRole()->getCString(), "Flog") != 0)
		{
			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
			{
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			}
			else
			{
				sp = ccpSub(_mainTarget->getPosition(), getPosition());
			}
			if ((_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK) && abs(sp.x) < 128)
			{
				if (_isCanSkill1 && bamen < 5)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControlled)
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
					if (abs(sp.x) > 48 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_mainTarget->_isBati && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking && bamen >= 1)
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
		if (!findEnemy2("Flog"))
		{
			findEnemy2("Tower");
		}

		if (_mainTarget)
		{

			CCPoint moveDirection;
			CCPoint sp;

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

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				if (_isCanSkill2 && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				idle();
			}
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
		findEnemy2("Hero");

		if (_isCanGear06)
		{
			if ((getActionState() == State::FLOAT ||
				 getActionState() == State::AIRHURT ||
				 getActionState() == State::HURT ||
				 getActionState() == State::KNOCKDOWN) &&
				getHpPercent() < 0.5 && !_isBati && !_isWudi)
			{
				useGear(gear06);
			}
		}
		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear06);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear07);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear02);
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
			if (strcmp(Akatsuki, getGroup()->getCString()) == 0)
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

		if (_mainTarget && strcmp(_mainTarget->getRole()->getCString(), "Flog") != 0)
		{
			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
			{
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition());
			}
			else
			{
				sp = ccpSub(_mainTarget->getPosition(), getPosition());
			}
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				if (_isCanSkill1 && bamen < 5)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && _mainTarget->getGP() < 5000 && !_mainTarget->_isBati && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking && bamen >= 3)
				{

					changeSide(sp);

					attack(OUGIS2);
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControlled)
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
				else if (abs(sp.x) < 128 || bamen >= 5)
				{

					if (abs(sp.x) > 46 || abs(sp.y) > 32)
					{

						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000 && !_mainTarget->_isBati && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking && bamen >= 1)
					{

						changeSide(sp);

						attack(OUGIS1);
					}
					else if (_isCanSkill2)
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else if (_isCanSkill3 && bamen >= 3)
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
		if (!findEnemy2("Flog"))
		{
			findEnemy2("Tower");
		}

		if (_mainTarget)
		{

			CCPoint moveDirection;
			CCPoint sp;

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

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				if (_isCanSkill2 && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanSkill3 && bamen >= 3 && isBaseDanger && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
			{
				idle();
			}
		}
		else
		{
			stepOn();
		}
	}
};
