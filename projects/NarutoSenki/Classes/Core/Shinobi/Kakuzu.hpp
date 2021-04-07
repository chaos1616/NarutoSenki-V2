#pragma once
#include "Hero.hpp"
#include "Kuchiyose/Mask.hpp"

class Kakuzu : public Hero
{
	void dead()
	{
		CharacterBase::dead();

		if (_heartEffect)
		{
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Heart_Effect_%02d.png", hearts)->getCString());
			_heartEffect->setDisplayFrame(frame);
		}

		if (is_player && getLV() >= 2)
		{
			if (_delegate->getHudLayer()->skill4Button)
			{
				_delegate->getHudLayer()->skill4Button->unLock();
			}
		}
	}

	void changeHPbar()
	{
		HeroElement::changeHPbar();

		if (not_player)
			return;

		if (_exp >= 500 && _level == 1)
		{
			if (hearts < 1)
			{
				if (_delegate->getHudLayer()->skill4Button)
				{
					_delegate->getHudLayer()->skill4Button->setLock();
				}
			}
		}
		else if (_exp >= 1500 && _level == 3)
		{
			if (_delegate->getHudLayer()->skill5Button)
			{
				_delegate->getHudLayer()->skill5Button->setLock();
			}
		}
	}

	void perform()
	{

		_mainTarget = nullptr;
		if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK)
		{

			if (getHpPercent() > 0.3f && !_isControlled && _isCanSkill1)
			{
				CCObject *pObject;
				float distance;
				float curDistance = 0;
				CCPoint sp;

				CCARRAY_FOREACH(getDelegate()->_CharacterArray, pObject)
				{
					CharacterBase *target = (CharacterBase *)pObject;
					if ((strcmp(target->getRole()->getCString(), "Player") == 0 ||
						 strcmp(target->getRole()->getCString(), "Com") == 0) &&
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

		findEnemy2("Hero");
		if (to_int(getCoin()->getCString()) >= 500 && !_isControlled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear03);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear08);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear04);
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

		bool isSummonAble = false;

		if (((getMonsterArray() && getMonsterArray()->count() < 3) || !_monsterArray) && hearts > 0)
		{
			isSummonAble = true;
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

	void changeAction()
	{

		setBuffEffect("jdBuff");
	}

	void resumeAction(float dt)
	{
		removeBuffEffect("sBuff");
	}

	void setActionResume()
	{
		if (_skillChangeBuffValue == 0)
			return;

		unschedule(schedule_selector(Kakuzu::resumeAction));
		removeBuffEffect("sBuff");

		_skillChangeBuffValue = 0;
	}

	Hero *createClone(unsigned int cloneTime)
	{
		if (!_monsterArray)
		{
			_monsterArray = CCArray::create();
			_monsterArray->retain();
		}
		bool isRaidon = false;
		bool isFudon = false;
		bool isKadon = false;
		int countMon = 0;
		if (getMonsterArray() && getMonsterArray()->count() > 0)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				Monster *mo = (Monster *)pObject;
				if (strcmp(mo->getCharacter()->getCString(), "MaskRaidon") == 0)
				{
					countMon++;
					isRaidon = true;
				}
				if (strcmp(mo->getCharacter()->getCString(), "MaskFudon") == 0)
				{
					countMon++;
					isFudon = true;
				}
				if (strcmp(mo->getCharacter()->getCString(), "MaskKadon") == 0)
				{
					countMon++;
					isKadon = true;
				}
			}
		}

		Hero *clone = nullptr;
		if (hearts > 0 && (!isRaidon || !isKadon || !isFudon))
		{
			if (!isRaidon)
			{
				clone = create<Mask>(CCString::create("MaskRaidon"), CCString::create("Kugutsu"), getGroup());
			}
			else if (!isFudon)
			{
				clone = create<Mask>(CCString::create("MaskFudon"), CCString::create("Kugutsu"), getGroup());
			}
			else if (!isKadon)
			{
				clone = create<Mask>(CCString::create("MaskKadon"), CCString::create("Kugutsu"), getGroup());
			}
			clone->_isBati = true;
			_monsterArray->addObject(clone);

			hearts -= 1;
			if (_heartEffect)
			{
				CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Heart_Effect_%02d.png", hearts)->getCString());
				_heartEffect->setDisplayFrame(frame);
			}

			if (hearts < 1 || countMon >= 2)
			{

				if (is_player)
				{
					if (_delegate->getHudLayer()->skill4Button)
					{
						_delegate->getHudLayer()->skill4Button->setLock();
					}
				}
			}
		}

		return clone;
	}
};
