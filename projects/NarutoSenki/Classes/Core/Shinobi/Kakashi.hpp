#pragma once
#include "Hero.hpp"
#include "Kuchiyose/DogWall.hpp"

class Kakashi : public Hero
{
	void perform()
	{
		_mainTarget = nullptr;
		findEnemy2("Hero");

		if (_isCanGear06)
		{
			if ((getActionState() == State::FLOAT ||
				 getActionState() == State::AIRHURT ||
				 getActionState() == State::HURT ||
				 getActionState() == State::KOCKDOWN) &&
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
				setGear(gear05);
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
				{
					return;
				}
			}
			else
			{
				if (stepBack())
				{
					return;
				}
			}
		}

		if (isBaseDanger && checkBase() && !_isControlled)
		{
			bool needBack = false;
			if (strcmp(Akatsuki, getGroup()->getCString()) == 0)
			{
				if (getPositionX() < 85 * 32)
				{
					needBack = true;
				}
			}
			else
			{
				if (getPositionX() > 11 * 32)
				{
					needBack = true;
				}
			}

			if (needBack)
			{
				if (stepBack2())
				{
					return;
				}
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

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
			{

				if (_isCanSkill3)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getGP() < 5000)
				{
					changeSide(sp);
					attack(SKILL2);
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
					if ((abs(sp.x) > 64 || abs(sp.y) > 32))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					if (_isCanOugis2 && !_isControlled && _delegate->_isOugis2Game && _mainTarget->getGP() < 5000 && !_mainTarget->_isBati && _mainTarget->getActionState() != State::KOCKDOWN && !_mainTarget->_isSticking)
					{
						changeSide(sp);
						attack(OUGIS2);
					}
					else if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill1 && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(SKILL1);
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

			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
			{
				if (_isCanSkill3 && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
				{
					changeSide(sp);
					attack(SKILL3);
				}
				else if (_isCanSkill1 && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0)
				{
					changeSide(sp);
					attack(SKILL1);
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
			{
				idle();
			}
		}
		else
		{
			stepOn();
		}
	}

	void changeAction()
	{

		setSkill1Action(createAnimation(skillSPC1Array, 10.0f, false, true));
		setSkill2Action(createAnimation(skillSPC2Array, 10.0f, false, true));
		setIdleAction(createAnimation(skillSPC3Array, 5.0f, true, false));
		settempAttackValue1(CCString::createWithFormat("%d", to_int(getsAttackValue1()->getCString())));
		setsAttackValue1(getspcAttackValue1());

		CCObject *pObject;
		CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
		{
			CharacterBase *tempHero = (CharacterBase *)pObject;
			if (strcmp(getGroup()->getCString(), tempHero->getGroup()->getCString()) != 0 &&
				(strcmp(tempHero->getRole()->getCString(), "Player") == 0 || strcmp(tempHero->getRole()->getCString(), "Com") == 0) &&
				tempHero->getActionState() != State::HURT &&
				tempHero->getActionState() != State::DEAD)
			{
				float distanceX = ccpSub(tempHero->getPosition(), getPosition()).x;
				if (distanceX < winSize.width / 2)
				{
					if (!tempHero->_isVisable)
					{
						if (strcmp(tempHero->getCharacter()->getCString(), "Konan") == 0 ||
							strcmp(tempHero->getCharacter()->getCString(), "Deidara") == 0)
						{
							tempHero->unschedule(schedule_selector(CharacterBase::disableBuff));
						}

						tempHero->setOpacity(255);
						tempHero->setVisible(true);

						if (tempHero->_hpBar)
						{
							tempHero->_hpBar->setVisible(true);
						}
						if (tempHero->_shadow)
						{
							tempHero->_shadow->setVisible(true);
						}

						tempHero->_isVisable = true;
					}
				}
			}
		}

		if (strcmp(getRole()->getCString(), "Player") == 0)
		{
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Kakashi_skill1_1.png");
			_delegate->getHudLayer()->skill1Button->setDisplayFrame(frame);
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Kakashi_skill2_1.png");
			_delegate->getHudLayer()->skill2Button->setDisplayFrame(frame);
		}
	}

	void resumeAction(float dt)
	{
		setIdleAction(createAnimation(idleArray, 5.0f, true, false));
		setSkill1Action(createAnimation(skill1Array, 10.0f, false, true));
		setSkill2Action(createAnimation(skill2Array, 10.0f, false, true));

		setsAttackValue1(CCString::createWithFormat("%d", to_int(gettempAttackValue1()->getCString())));

		if (strcmp(getRole()->getCString(), "Player") == 0)
		{

			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Kakashi_skill1.png");
			_delegate->getHudLayer()->skill1Button->setDisplayFrame(frame);
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Kakashi_skill2.png");
			_delegate->getHudLayer()->skill2Button->setDisplayFrame(frame);
		}
		CharacterBase::resumeAction(dt);
	}

	Hero *createClone(unsigned int cloneTime)
	{
		auto clone = create<DogWall>(CCString::create("DogWall"), CCString::create("Summon"), getGroup());
		clone->setPosition(ccp(getPositionX() + (_isFlipped ? -56 : 56), getPositionY()));
		clone->setAnchorPoint(ccp(0.5f, 0.1f));
		clone->_isBati = true;
		return clone;
	}
};
