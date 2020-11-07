#pragma once
#include "Characters.h"

class AI_Hidan : public Hero
{
	void perform()
	{

		_mainTarget = NULL;
		bool _isFound = false;
		if (getMonsterArray() && getMonsterArray()->count() > 0)
		{
			CCObject *pObject;
			CCARRAY_FOREACH(getMonsterArray(), pObject)
			{
				Monster *mo = (Monster *)pObject;
				if (strcmp(mo->getCharacter()->getCString(), "CircleMark") == 0)
				{
					_mainTarget = mo;
					_isFound = true;
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
					if ((abs(sp.x) > 8 || abs(sp.y) > 8))
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					else
					{
						if (_isBati)
						{

							CCObject *pObject;
							CCARRAY_FOREACH(_delegate->_CharacterArray, pObject)
							{
								CharacterBase *tempHero = (CharacterBase *)pObject;
								if (tempHero->getGroup() != getGroup() && atoi(tempHero->getHP()->getCString()) < 2000 && tempHero->getActionState() != State::DEAD && (strcmp(tempHero->getRole()->getCString(), "Player") == 0 || strcmp(tempHero->getRole()->getCString(), "Com") == 0))
								{
									attack(NAttack);
									return;
								}
							}

							idle();
							return;
						}
					}
				}
			}
		}

		if (!_isFound)
		{
			findEnemy2("Hero");
		}

		if (_isCanGear06)
		{
			if ((getActionState() == State::FLOAT_AIR ||
				 getActionState() == State::AIRHURT ||
				 getActionState() == State::HURT ||
				 getActionState() == State::KOCKDOWN) &&
				getHpPercent() < 0.5 && !_isBati && !_isWudi)
			{
				useGear(gear06);
			}
		}
		if (atoi(getCoin()->getCString()) >= 500 && !_isControled && _delegate->_isHardCoreGame)
		{
			if (getGearArray()->count() == 0)
			{
				setGear(gear06);
			}
			else if (getGearArray()->count() == 1)
			{
				setGear(gear01);
			}
			else if (getGearArray()->count() == 2)
			{
				setGear(gear07);
			}
		}

		if (checkRetri() && !_isBati && !_isFound)
		{
			if (_mainTarget != NULL)
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

		if (isBaseDanger && checkBase() && !_isControled && !_isBati && !_isFound)
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

				if (_isCanOugis2 && !_isControled && _delegate->_isOugis2Game && !_isBati)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					if (_isCanSkill1 && !_isBati && !_isFound)
					{
						changeSide(sp);
						attack(SKILL1);
						return;
					}
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getGP() < 5000 && !_isBati)
				{

					if (abs(sp.x) > 56 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControled && !_isBati && !_isFound)
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
					if ((abs(sp.x) > 48 || abs(sp.y) > 32) && !_isBati)
					{
						moveDirection = ccpNormalize(sp);
						walk(moveDirection);
						return;
					}
					if (_isCanOugis1 && !_isBati && !_isControled && _mainTarget->getGP() < 5000)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill3 && !_isBati)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else
					{
						if (!_isBati)
						{
							changeSide(sp);
							attack(NAttack);
						}
						else
						{
							idle();
						}
					}

					return;
				}
			}
		}
		if (!_mainTarget && !_isFound && !_isBati)
		{
			if (!findEnemy2("Flog"))
			{
				findEnemy2("Tower");
			}
		}

		if (_mainTarget && strcmp(_mainTarget->getRole()->getCString(), K_TAG_MON) != 0 && !_isBati)
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
				if (_isCanSkill3 && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0 && isBaseDanger && !_isBati)
				{
					changeSide(sp);
					attack(SKILL3);
				}
				else if (_isCanSkill2 && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0 && isBaseDanger && !_isBati)
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
		if (!_isBati)
		{
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
		else
		{
			if (_actionState == State::IDLE || _actionState == State::WALK || _actionState == State::ATTACK)
			{
				idle();
			}
		}
	}
};
