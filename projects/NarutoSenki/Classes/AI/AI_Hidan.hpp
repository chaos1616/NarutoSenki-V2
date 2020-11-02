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
						sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), this->getPosition());
					}
					else
					{
						sp = ccpSub(_mainTarget->getPosition(), this->getPosition());
					}
					if ((abs(sp.x) > 8 || abs(sp.y) > 8))
					{
						moveDirection = ccpNormalize(sp);
						this->walk(moveDirection);
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
								if (tempHero->getGroup() != this->getGroup() && atoi(tempHero->getHP()->getCString()) < 2000 && tempHero->getActionState() != ACTION_STATE_DEAD && (strcmp(tempHero->getRole()->getCString(), "Player") == 0 || strcmp(tempHero->getRole()->getCString(), "Com") == 0))
								{
									this->attack(NAttack);
									return;
								}
							}

							this->idle();
							return;
						}
					}
				}
			}
		}

		if (!_isFound)
		{
			this->findEnemy2("Hero");
		}

		if (_isCanGear06)
		{
			if ((this->getActionState() == ACTION_STATE_FLOAT ||
				 this->getActionState() == ACTION_STATE_AIRHURT ||
				 this->getActionState() == ACTION_STATE_HURT ||
				 this->getActionState() == ACTION_STATE_KOCKDOWN) &&
				this->getHpPercent() < 0.5 && !_isBati && !_isWudi)
			{
				this->useGear(gear06);
			}
		}
		if (atoi(this->getCoin()->getCString()) >= 500 && !_isControled && _delegate->_isHardCoreGame)
		{
			if (this->getGearArray()->count() == 0)
			{
				this->setGear(gear06);
			}
			else if (this->getGearArray()->count() == 1)
			{
				this->setGear(gear01);
			}
			else if (this->getGearArray()->count() == 2)
			{
				this->setGear(gear07);
			}
		}

		if (this->checkRetri() && !_isBati && !_isFound)
		{
			if (_mainTarget != NULL)
			{
				if (this->stepBack2())
				{
					return;
				}
			}
			else
			{
				if (this->stepBack())
				{
					return;
				}
			}
		}

		if (isBaseDanger && this->checkBase() && !_isControled && !_isBati && !_isFound)
		{
			bool needBack = false;
			if (strcmp(Akatsuki, this->getGroup()->getCString()) == 0)
			{
				if (this->getPositionX() < 85 * 32)
				{
					needBack = true;
				}
			}
			else
			{
				if (this->getPositionX() > 11 * 32)
				{
					needBack = true;
				}
			}

			if (needBack)
			{
				if (this->stepBack2())
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
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), this->getPosition());
			}
			else
			{
				sp = ccpSub(_mainTarget->getPosition(), this->getPosition());
			}
			if (_actionState == ACTION_STATE_IDLE || _actionState == ACTION_STATE_WALK || _actionState == ACTION_STATE_ATTACK)
			{

				if (_isCanOugis2 && !_isControled && _delegate->_isOugis2Game && !_isBati)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						this->walk(moveDirection);
						return;
					}
					if (_isCanSkill1 && !_isBati && !_isFound)
					{
						this->changeSide(sp);
						this->attack(SKILL1);
						return;
					}
					this->changeSide(sp);
					this->attack(OUGIS2);
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getGP() < 5000 && !_isBati)
				{

					if (abs(sp.x) > 56 || abs(sp.y) > 32)
					{
						moveDirection = ccpNormalize(sp);
						this->walk(moveDirection);
						return;
					}

					this->changeSide(sp);
					this->attack(SKILL2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealling && !_isControled && !_isBati && !_isFound)
				{
					if (abs(sp.x) < 160)
					{
						this->stepBack2();
						return;
					}
					else
					{

						this->idle();
						return;
					}
				}
				else if (abs(sp.x) < 128)
				{
					if ((abs(sp.x) > 48 || abs(sp.y) > 32) && !_isBati)
					{
						moveDirection = ccpNormalize(sp);
						this->walk(moveDirection);
						return;
					}
					if (_isCanOugis1 && !_isBati && !_isControled && _mainTarget->getGP() < 5000)
					{
						this->changeSide(sp);
						this->attack(OUGIS1);
					}
					else if (_isCanSkill3 && !_isBati)
					{
						this->changeSide(sp);
						this->attack(SKILL3);
					}
					else
					{
						if (!_isBati)
						{
							this->changeSide(sp);
							this->attack(NAttack);
						}
						else
						{
							this->idle();
						}
					}

					return;
				}
			}
		}
		if (!_mainTarget && !_isFound && !_isBati)
		{
			if (!this->findEnemy2("Flog"))
			{
				this->findEnemy2("Tower");
			}
		}

		if (_mainTarget && strcmp(_mainTarget->getRole()->getCString(), "Mon") != 0 && !_isBati)
		{

			CCPoint moveDirection;
			CCPoint sp;

			if (_mainTarget->_originY)
			{
				sp = ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), this->getPosition());
			}
			else
			{
				sp = ccpSub(_mainTarget->getPosition(), this->getPosition());
			}

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = ccpNormalize(sp);
				this->walk(moveDirection);
				return;
			}

			if (_actionState == ACTION_STATE_IDLE || _actionState == ACTION_STATE_WALK || _actionState == ACTION_STATE_ATTACK)
			{
				if (_isCanSkill3 && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0 && isBaseDanger && !_isBati)
				{
					this->changeSide(sp);
					this->attack(SKILL3);
				}
				else if (_isCanSkill2 && strcmp(_mainTarget->getRole()->getCString(), "Flog") == 0 && isBaseDanger && !_isBati)
				{
					this->changeSide(sp);
					this->attack(SKILL2);
				}
				else
				{
					this->changeSide(sp);
					this->attack(NAttack);
				}
			}
			return;
		}
		if (!_isBati)
		{
			if (_isHealling && this->getHpPercent() < 1)
			{
				if (_actionState == ACTION_STATE_IDLE || _actionState == ACTION_STATE_WALK || _actionState == ACTION_STATE_ATTACK)
				{
					this->idle();
				}
			}
			else
			{
				this->stepOn();
			}
		}
		else
		{
			if (_actionState == ACTION_STATE_IDLE || _actionState == ACTION_STATE_WALK || _actionState == ACTION_STATE_ATTACK)
			{
				this->idle();
			}
		}
	}
};
