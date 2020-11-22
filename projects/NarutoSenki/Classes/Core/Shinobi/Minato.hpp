#pragma once
#include "Hero.hpp"

class Minato : public Hero
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
		if (getHpPercent() < 0.3f)
		{

			if (_isCanSkill1)
			{

				CCObject *pObject;
				bool isMark = false;
				if (getMonsterArray() && getMonsterArray()->count() > 0)
				{
					CCARRAY_FOREACH(getMonsterArray(), pObject)
					{
						Monster *mo = (Monster *)pObject;
						if (strcmp(mo->getCharacter()->getCString(), "HiraishinMark") == 0)
						{
							if (strcmp(getGroup()->getCString(), Konoha) == 0 && mo->getPositionX() < getPositionX())
							{
								isMark = true;
							}
							else if (strcmp(getGroup()->getCString(), Akatsuki) == 0 && mo->getPositionX() > getPositionX())
							{
								isMark = true;
							}
						}
					}
				}
				if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
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
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
			{

				CCObject *pObject;
				bool isMark = false;
				if (getMonsterArray() && getMonsterArray()->count() > 0)
				{
					CCARRAY_FOREACH(getMonsterArray(), pObject)
					{
						Monster *mo = (Monster *)pObject;
						if (strcmp(mo->getCharacter()->getCString(), "HiraishinMark") == 0)
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
					else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && to_int(getnAttackValue()->getCString()) < 260)
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
			if (_isCanSkill1)
			{

				CCObject *pObject;
				bool isMark = false;
				if (getMonsterArray() && getMonsterArray()->count() > 0)
				{
					CCARRAY_FOREACH(getMonsterArray(), pObject)
					{
						Monster *mo = (Monster *)pObject;
						if (strcmp(mo->getCharacter()->getCString(), "HiraishinMark") == 0)
						{

							if (strcmp(getGroup()->getCString(), Konoha) == 0 && mo->getPositionX() > getPositionX())
							{
								isMark = true;
							}
							else if (strcmp(getGroup()->getCString(), Akatsuki) == 0 && mo->getPositionX() < getPositionX())
							{
								isMark = true;
							}
						}
					}
				}
				if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
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

			if (is_player)
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

			setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) + 200));

			_nattackRangeX = 16;
			_nattackRangeY = 48;

			setNAttackAction(createAnimation(skillSPC3Array, 10.0f, false, true));
		}
	}

	void resumeAction(float dt)
	{

		setnAttackValue(CCString::createWithFormat("%d", to_int(getnAttackValue()->getCString()) - 200));
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
