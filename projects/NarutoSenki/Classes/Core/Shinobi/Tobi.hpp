#pragma once
#include "Hero.hpp"

class Tobi : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryBuyGear(gear03, gear02, gear05);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeActionState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getGP() < 5000 && !_mainTarget->_isArmored && _mainTarget->getActionState() != State::KNOCKDOWN && !_mainTarget->_isSticking)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 16)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getGP() < 5000)
				{
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanSkill3 && !_skillChangeBuffValue)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isControlled && !_skillChangeBuffValue)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 32 && (_isCanSkill2 && _mainTarget->getHpPercent() < 0.5f))
					{
						stepBack();
						return;
					}

					if (_isCanSkill2 && _mainTarget->getGP() < 5000 && (_mainTarget->getHpPercent() < 0.5f || !_skillChangeBuffValue))
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else if (_isCanSkill1 && _mainTarget->getGP() < 5000 && (_mainTarget->getHpPercent() < 0.5f || !_skillChangeBuffValue))
					{
						changeSide(sp);
						attack(SKILL1);
					}
					else
					{
						if (abs(sp.x) > 32 || abs(sp.y) > 32)
						{
							moveDirection = sp.getNormalized();
							walk(moveDirection);
							return;
						}

						if (_isCanGear03)
						{
							useGear(gear03);
						}

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
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = sp.getNormalized();
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
				else if (_isCanSkill1 && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else
				{
					if (_isCanGear03)
					{
						useGear(gear03);
					}
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
		setWalkAction(createAnimation(skillSPC1Array, 10.0f, true, false));

		setWalkSpeed(320);
		_originSpeed = 320;

		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (getGroup() != hero->getGroup() && hero->isPlayerOrCom() && hero->getActionState() != State::HURT && hero->getActionState() != State::DEAD)
			{
				float distanceX = (hero->getPosition() - getPosition()).x;
				if (distanceX < kAttackRange)
				{
					if (!hero->_isVisable)
					{
						if (hero->getName() == HeroEnum::Konan ||
							hero->getName() == HeroEnum::Deidara)
						{
							hero->unschedule(schedule_selector(CharacterBase::disableBuff));
						}

						hero->setOpacity(255);
						hero->setVisible(true);

						if (hero->_hpBar)
							hero->_hpBar->setVisible(true);
						if (hero->_shadow)
							hero->_shadow->setVisible(true);

						hero->_isVisable = true;
					}
				}
			}
		}
	}

	void resumeAction(float dt) override
	{
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));

		if (getOpacity() != 255)
			setOpacity(255);

		setWalkSpeed(224);
		_originSpeed = 224;

		if (_actionState == State::WALK)
			idle();
		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		unschedule(schedule_selector(Tobi::resumeAction));
		setWalkAction(createAnimation(walkArray, 10.0f, true, false));

		if (getOpacity() != 255)
			setOpacity(255);

		setWalkSpeed(224);
		_originSpeed = 224;

		_skillChangeBuffValue = 0;
	}

	/**
	 * Callbacks
	 */

	bool onAcceptAttack(CharacterBase *attacker) override
	{
		if (_skillChangeBuffValue &&
			(_actionState == State::IDLE ||
			 _actionState == State::WALK ||
			 _actionState == State::NATTACK))
		{
			if (getOpacity() == 255)
			{
				scheduleOnce(schedule_selector(CharacterBase::disableBuff), 0.2f);
			}

			setOpacity(150);
			return false;
		}

		return true;
	}
};
