#include "Core/Provider.hpp"
#include "GameLayer.h"
#include "GameMode/GameModeImpl.h"
#include "HudLayer.h"
#include "MyUtils/CCShake.h"
#include "System/CommandSystem.hpp"
#include "Utils/Debug/UnitDebug.hpp"

const SkillData SkillData::Null = {
	.value = Value::Null,
	.rangeX = 0,
	.rangeY = 0,
	.cooldown = 0,
	.isDouble = false,
};

Unit::Unit()
{
	_state = State::WALK;

	_idleAction = nullptr;
	_nAttackAction = nullptr;
	_walkAction = nullptr;
	_hurtAction = nullptr;
	_airHurtAction = nullptr;
	_knockdownAction = nullptr;
	_floatAction = nullptr;
	_deadAction = nullptr;
	_skill1Action = nullptr;
	_skill2Action = nullptr;
	_skill3Action = nullptr;
	_skill4Action = nullptr;
	_skill5Action = nullptr;

	gearCKRValue = 0;
	gearRecoverValue = 0;
	isAttackGainCKR = false;
	isGearCD = false;
	hasArmorBroken = false;
	hasArmor = false;
	battleCondiction = 0;
	hearts = 0;
	isHurtingTower = false;
	damageEffectCount = 0;

	_isSuicide = false;

	_charId = 0;
	_backY = 0;
	_diretionY = 0;

	_isAllAttackLocked = false;
	_isOnlySkillLocked = false;
	_sAttack1isDouble = false;
	_sAttack2isDouble = false;
	_sAttack3isDouble = false;
	_sAttack4isDouble = false;
	_sAttack5isDouble = false;

	_moveAction = nullptr;
	_jumpUPAction = nullptr;
	_floatUPAction = nullptr;

	_hurtFromLeft = false;
	_hurtFromRight = false;
	_isHitOne = false;
	_isCatchOne = false;
	_isHealing = false;
	_isVisable = true;
	_isSticking = false;
	_isControlled = false;

	_isCanSkill1 = true;
	_isCanSkill2 = true;
	_isCanSkill3 = true;
	_isCanItem1 = true;
	_isCanOugis1 = false;
	_isCanOugis2 = false;

	_isCanGear00 = false;
	_isCanGear03 = false;
	_isCanGear06 = false;

	enemyCombatPoint = 0;
	// totalCombatPoint = 0;
	friendCombatPoint = 0;

	isBaseDanger = false;

	_sAttackCombatPoint1 = 0;
	_sAttackCombatPoint2 = 0;
	_sAttackCombatPoint3 = 0;
	_sAttackCombatPoint4 = 0;
	_sAttackCombatPoint5 = 0;

	_master = nullptr;
	_controller = nullptr;
	_secmaster = nullptr;
	_slayer = nullptr;
	_sticker = nullptr;

	_mainTarget = nullptr;

	_deadNum = 0;
	_flogNum = 0;

	_knockLength = 0;
	_knockDirection = false;

	_originY = 0;

	_tempAttackValue1 = nullptr;

	_healBuffEffect = nullptr;
	_powerBuffEffect = nullptr;
	_skillBuffEffect = nullptr;
	_healItemEffect = nullptr;
	_speedItemEffect = nullptr;
	_dehealBuffEffect = nullptr;

	_buffStartTime = 0;
	_debuffStartTime = 0;
	_heartEffect = nullptr;

	_shadow = nullptr;

	_healBuffValue = 0;
	_skillUPBuffValue = 0;
	_skillChangeBuffValue = 0;
	_dehealBuffValue = 0;
	_powerUPBuffValue = 0;
	_hpBar = nullptr;

	_defense = 0;
	_exp = 0;
	_level = 1;

	_isInvincible = false;
	_isTaunt = false;
	_isArmored = false;

	_rebornTime = 5;

	_markPoint = Vec2(0, 0);
	_startPoint = Vec2(0, 0);

	rebornLabelTime = 0;

	_isAI = false;

	_actionFlag = ActionFlag::None;

	_affectedByTower = false;
}

void Unit::updateDataByLVOnly()
{
	uint32_t maxHP = getMaxHP();
	uint32_t nAtkValue = getNAttackValue();
	if (_level >= 2)
	{
		_isCanOugis1 = true;
		if (isPlayer())
		{
			getGameLayer()->setCKRLose(false);
			getGameLayer()->removeOugisMark(1);
		}
		maxHP += 500;
		nAtkValue += 9;
		_rebornTime += 1;
	}
	if (_level >= 3)
	{
		maxHP += 1000;
		nAtkValue += 18;
		_rebornTime += 2;
	}
	if (_level >= 4)
	{
		_isCanOugis2 = true;
		if (isPlayer())
		{
			getGameLayer()->setCKRLose(true);
			getGameLayer()->removeOugisMark(2);
		}
		maxHP += 2000;
		nAtkValue += 27;
		_rebornTime += 3;
	}
	if (_level >= 5)
	{
		maxHP += 2500;
		nAtkValue += 36;
		_rebornTime += 4;
	}
	if (_level >= 6)
	{
		maxHP += 3000;
		nAtkValue += 45;
		_rebornTime += 5;
	}
	setMaxHPValue(maxHP, false);
	setNAttackValue(nAtkValue);
}

void Unit::update(float dt)
{
	if (_healBuffEffect)
	{
		_healBuffEffect->setPositionX(getContentSize().width / 2 + (isFlip() ? 2 : -2));
	}
	if (_powerBuffEffect)
	{
		_powerBuffEffect->setPositionX(getContentSize().width / 2 + (isFlip() ? 2 : -2));
	}
	if (_skillBuffEffect)
	{
		_skillBuffEffect->setPositionX(getContentSize().width / 2);
	}

	if (_heartEffect)
	{
		_heartEffect->setPositionX(getContentSize().width / 2 + (isFlip() ? 22 : -22));
	}

	if (_healItemEffect)
	{
		_healItemEffect->setPosition(Vec2(isFlip() ? getContentSize().width / 2 + 16 : getContentSize().width / 2 - 16,
										  _hpBarHeight));
	}

	if (_speedItemEffect)
	{
		_speedItemEffect->setPosition(Vec2(isFlip() ? getContentSize().width / 2 + 16 : getContentSize().width / 2 - 16,
										   _hpBarHeight));
	}

	/*if(_kaguraEffect){
		_kaguraEffect->setPosition(Vec2(getPositionX(),getPositionY()+getContentSize().height/2));
	}*/

	if (_dehealBuffEffect)
	{
		_dehealBuffEffect->setPositionX(getContentSize().width / 2);
	}

	if (_shadow)
	{
		_shadow->setPosition(Vec2(getPositionX(), _originY ? _originY : getPositionY()));
	}

	if (!_isControlled && _state != State::DEAD)
	{
		if (isPlayerOrCom())
		{
			if (isNotGuardian())
			{
				if (isKonohaGroup() && getPositionX() <= 11 * 32)
				{
					_isHealing = true;
					if (getHpPercent() < 1.0f)
					{
						scheduleOnce(schedule_selector(Unit::setRestore), 1.0f);
					}
				}
				else if (isAkatsukiGroup() && getPositionX() >= 85 * 32)
				{
					_isHealing = true;
					if (getHpPercent() < 1.0f)
					{
						scheduleOnce(schedule_selector(Unit::setRestore), 1.0f);
					}
				}
				else
				{
					_isHealing = false;
				}
			}
		}
	}

	if (_state == State::WALK)
	{
		_desiredPosition = getPosition() + (_velocity * dt);

		if (isPlayer() && !_isAI && !_isInvincible && !_isArmored)
		{
			// save the stop Area
			for (auto tower : getGameLayer()->_TowerArray)
			{
				if (tower)
				{
					int metaWidth = 96;
					int metaHeight = 128;
					int metaX = tower->getPositionX() - metaWidth / 2;
					int metaY = tower->getPositionY() - metaHeight / 2;
					Rect rect = Rect(metaX, metaY + 32, metaWidth, metaHeight - 64);

					if (rect.containsPoint(_desiredPosition))
					{
						_affectedByTower = true;

						float anchorYpoint = metaY + metaHeight / 2;
						if (getPositionY() > anchorYpoint)
						{
							_velocity = Vec2(0, 1 * _walkSpeed * kSpeedBase);
						}
						else
						{
							_velocity = Vec2(0, -1 * _walkSpeed * kSpeedBase);
						}
						_desiredPosition = getPosition() + (_velocity * dt);
					}
				}
			}

			if (_affectedByTower && checkHasMovement())
			{
				_affectedByTower = false;
			}
		}

		float posX = MIN(getGameLayer()->currentMap->getMapSize().width * getGameLayer()->currentMap->getTileSize().width,
						 MAX(0, _desiredPosition.x));

		// map height		: 10
		// backgroud height	: 4.5
		// floor height		: 5.5
		float poxY = MIN(getGameLayer()->currentMap->getTileSize().height * 5.5, MAX(0, _desiredPosition.y));

		setPosition(Vec2(posX, poxY));
		getGameLayer()->reorderChild(this, -getPositionY());
		if (isPlayerOrCom())
		{
			CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", this);
		}
	}

	if (_hpBar)
	{
		_hpBar->setPositionX(getContentSize().width / 2 - _hpBar->getHPBottom()->getContentSize().width / 2);
	}
}

void Unit::updateHpBarPosition(float dt)
{
	if (_hpBar)
	{
		_hpBar->setPositionX(getContentSize().width / 2 - _hpBar->getHPBottom()->getContentSize().width / 2);
		_hpBar->setPositionY(getHPBarHeight());
	}
}

void Unit::setCharFlip()
{
	if (isFlip())
		setFlippedX(false);
	else
		setFlippedX(true);
}

void Unit::setShadow(SpriteFrame *frame)
{
	auto charN = Sprite::createWithSpriteFrame(frame);
	charN->setVisible(false);
	if (isKonohaGroup())
	{
		charN->setColor(ccGREEN);
	}
	else
	{
		charN->setColor(ccRED);
	}

	charN->setOpacity(180);
	charN->setAnchorPoint(Vec2(0.5, 0));
	charN->setFlippedX(isFlip());
	charN->setPosition(getPosition());
	auto delay = DelayTime::create(0.1f);
	auto call = CallFunc::create(std::bind(&Unit::enableShadow, this, charN));
	auto seq = newSequence(delay, call);
	charN->runAction(seq);
	getGameLayer()->addChild(charN, -getPositionY() - 1);
}

void Unit::enableShadow(Sprite *charN)
{
	charN->setVisible(true);
	auto delay = DelayTime::create(0.1f);
	auto call = CallFunc::create(std::bind(&Unit::disableShadow, this, charN));
	auto seq = newSequence(delay, call);
	charN->runAction(seq);
}

void Unit::disableShadow(Sprite *charN)
{
	charN->stopAllActions();
	charN->removeFromParent();
}

void Unit::setOugis()
{
	getGameLayer()->setOugis(this);
}

void Unit::disableHpBar(float dt)
{
	if (_hpBar)
		_hpBar->setVisible(false);
}

void Unit::setDamage(Unit *attacker)
{
	setDamage(attacker, attacker->_effectType, attacker->_attackValue, isFlip());
}

void Unit::setDamage(Unit *attacker, const string &effectType, int attackValue, bool isFlipped)
{
	if (isTower())
	{
		if (_hpBar)
			_hpBar->setVisible(true);

		unschedule(schedule_selector(Unit::disableHpBar));
		scheduleOnce(schedule_selector(Unit::disableHpBar), 2.0f);
	}

	int criticalValue;
	uint32_t realValue;

	_slayer = attacker;
	Unit *currentAttacker;
	if (attacker->_master)
		currentAttacker = attacker->_master;
	else
		currentAttacker = attacker;

	if (attacker->isGearCD || (attacker->_master && attacker->_master->isGearCD))
		criticalValue = rand() % 60 + 10;
	else
		criticalValue = rand() % 50;

	if (attacker->getName() == HeroEnum::Hidan && attacker->_skillChangeBuffValue)
	{
		realValue = attackValue + criticalValue;
	}
	else
	{
		bool isCannotMiss = false; // is this attack has 100 percent accuracy
		if (attacker->getName() == HeroEnum::Hiruzen && attacker->_state == State::O2ATTACK)
		{
			isCannotMiss = true;
		}

		if (isCannotMiss)
		{
			realValue = attackValue + criticalValue;
		}
		else if ((attacker->_master || attacker->_state == State::NATTACK) &&
				 attacker->hasArmorBroken)
		{
			realValue = attackValue + criticalValue;
		}
		else
		{
			if (attackValue <= _defense)
			{
				realValue = criticalValue;
			}
			else
			{
				realValue = attackValue - _defense + criticalValue;
				float decreaseRating = 0;
				if (hasArmor)
					decreaseRating += 0.25f;

				if (getName() == HeroEnum::Kakuzu && _skillChangeBuffValue)
					decreaseRating += 0.25f;

				if (getName() == HeroEnum::Chiyo)
				{
					for (auto mo : _monsterArray)
					{
						if (mo->getName() == KugutsuEnum::Parents && !mo->_skillChangeBuffValue && mo->_state != State::SATTACK)
						{
							Vec2 sp = mo->getPosition() - getPosition();
							if (sp.x <= 48)
								decreaseRating += 0.25f;
						}
					}
				}

				if (realValue < realValue * decreaseRating)
					realValue = 0;
				else
					realValue -= realValue * decreaseRating;
			}
		}
	}

#if COCOS2D_DEBUG
	Debug::PrintDamgeInfo(this, attacker, currentAttacker, attackValue, realValue, effectType);
#endif
	setHPValue(getHP() <= realValue ? 0 : getHP() - realValue);

	if (isClone() && _master && !_master->_isControlled)
	{
		uint32_t boundValue = 0;
		if (getName() == HeroEnum::Naruto)
			boundValue = realValue * 15 / 100;
		else if (getName() == HeroEnum::SageNaruto)
			boundValue = realValue * 25 / 100;
		else if (getName() == HeroEnum::RikudoNaruto)
			boundValue = realValue * 35 / 100;

		// 4v4
		if (Cheats >= kMaxCheats)
			boundValue = boundValue / 2;

		if (currentAttacker->isAttackGainCKR)
		{
			if (boundValue > boundValue * 25 / 100)
				boundValue -= boundValue * 25 / 100;
			else
				boundValue = 0;
		}

		_master->increaseAllCkrs(boundValue);
	}
	else if (!_isControlled)
	{
		uint32_t boundValue;

		if (_level == 5)
			boundValue = realValue + realValue * 5 / 100;
		else if (_level == 6)
			boundValue = realValue + realValue * 10 / 100;
		else
			boundValue = realValue;

		boundValue += realValue * gearCKRValue / 100;

		// 4v4
		if (Cheats >= kMaxCheats)
			boundValue = boundValue / 2;

		if (currentAttacker->isAttackGainCKR)
		{
			if (boundValue > boundValue * 25 / 100)
				boundValue -= boundValue * 25 / 100;
			else
				boundValue = 0;
		}

		bool isGainable = true;
		if (getName() == HeroEnum::Tsunade && _skillChangeBuffValue)
			isGainable = false;
		if (attacker->getName() == HeroEnum::Hinata && attacker->_skillUPBuffValue)
			isGainable = false;

		if (isGainable)
			increaseAllCkrs(boundValue);
	}

	if (isPlayerOrCom() && !currentAttacker->_isControlled)
	{
		uint32_t gainValue = 0;

		if (attacker->getName() == HeroEnum::Kisame && attacker->_skillChangeBuffValue)
		{
			if (currentAttacker->isAttackGainCKR)
				gainValue = realValue * 80 / 100;
			else
				gainValue = realValue * 65 / 100;
		}
		else if (currentAttacker->isAttackGainCKR)
		{
			gainValue = realValue * 15 / 100;
		}

		if (gainValue != 0)
			currentAttacker->increaseAllCkrs(gainValue);
	}

	if (isPlayer() || (isNotTower() &&
					   abs((getPosition() - getGameLayer()->currentPlayer->getPosition()).x) < winSize.width / 2))
	{
		// create damage value display
		bool _isDisplay = false;

		if (attacker->isPlayer() || isPlayer())
		{
			_isDisplay = true;
		}
		if (attacker->_master)
		{
			if (attacker->_master->isPlayer())
				_isDisplay = true;
		}

		if (_isDisplay)
		{
			if (criticalValue <= 20)
				setDamgeDisplay(realValue, Fonts::White);
			else if (criticalValue <= 40)
				setDamgeDisplay(realValue, Fonts::Yellow);
			else
				setDamgeDisplay(realValue, Fonts::Red);
		}

		// create damage effect
		if (isFlog() && attacker->isNotFlog())
		{
			if (effectType == "a_hit")
			{
				setDamgeEffect("a_hit");
			}
		}
		else if (attacker->isNotFlog())
		{
			setDamgeEffect(effectType);
		}
	}
}

void Unit::setCoinDisplay(int num)
{
	Sprite *coinDisplay = Sprite::create();

	Sprite *coinSprite = newSprite("coin");
	coinSprite->setPosition(Vec2(14, 0));
	coinDisplay->addChild(coinSprite);

	auto rewardLabel = CCLabelBMFont::create(format("+{}", num).c_str(), Fonts::Yellow);
	rewardLabel->setPosition(Vec2(0, 0));
	rewardLabel->setScale(0.3f);
	coinDisplay->addChild(rewardLabel);

	coinDisplay->setPosition(Vec2(getPositionX(), getPositionY() + getContentSize().height / 2));
	getGameLayer()->addChild(coinDisplay, 5000);

	auto mv = MoveBy::create(0.5f, Vec2(0, 12));
	auto fadeOut = FadeOut::create(0.8f);
	auto call = CallFunc::create(std::bind(&Unit::removeCoinDisplay, this, coinDisplay));
	auto sp = Spawn::create(fadeOut, mv, nullptr);
	auto seq = newSequence(sp, call);
	coinDisplay->runAction(seq);
}

void Unit::removeCoinDisplay(Sprite *coinDisplay)
{
	coinDisplay->removeFromParent();
}

void Unit::setDamgeDisplay(int value, const char *font)
{
	if (_damageArray.size() < 6)
	{
		auto damageFont = CCLabelBMFont::create(to_cstr(value), font);
		damageFont->setAnchorPoint(Vec2(0.5, 0.5));

		if (isFlog())
		{
			damageFont->setScale(0.6f);
			damageFont->setPosition(Vec2(getPositionX() + rand() % 16, getPositionY() + getHPBarHeight() + rand() % 4));
		}
		else
		{
			damageFont->setScale(0.8f);
			damageFont->setPosition(Vec2(getPositionX() + rand() % 16, getPositionY() + getHPBarHeight() + rand() % 16));
		}

		getGameLayer()->addChild(damageFont, kNumberOrder);
		_damageArray.push_back(damageFont);

		auto sd = ScaleBy::create(0.2f, 0.5f);
		auto call = CallFunc::create(std::bind(&Unit::removeDamageDisplay, this));
		auto mv = MoveBy::create(0.4f, Vec2(0, 12));
		auto fadeOut = FadeOut::create(0.4f);
		auto sp = Spawn::create(fadeOut, mv, nullptr);
		auto seq = newSequence(sd, sp, call);
		damageFont->runAction(seq);
	}
}

void Unit::removeDamageDisplay()
{
	if (_damageArray.size() > 0)
	{
		auto damageFont = _damageArray.at(0);
		damageFont->removeFromParent();
		_damageArray.erase(_damageArray.begin());
	}
}

void Unit::setDamgeEffect(const string &type)
{
	if (isPlayer() ||
		abs((getPosition() - getGameLayer()->currentPlayer->getPosition()).x) < winSize.width / 2)
	{
		if (damageEffectCount < 2)
		{
			if (isNotFlog())
			{
				Effect *ef = Effect::create(type, this);
				getGameLayer()->damageEffectBatch->addChild(ef, 5000);
			}
			else
			{
				Effect *ef = Effect::create(type, this);
				getGameLayer()->damageEffectBatch->addChild(ef);
			}

			damageEffectCount++;
		}
	}
}

void Unit::setSkillEffect(const string &type)
{
	if (isPlayer() ||
		abs((getPosition() - getGameLayer()->currentPlayer->getPosition()).x) < winSize.width / 2)
	{
		Effect *ef = Effect::create(type, this);
		if (type == "Bagua" ||
			type == "Kujiyose")
		{
			getGameLayer()->addChild(ef, -500);
		}
		else if (type == "DarkFlame")
		{
			getGameLayer()->addChild(ef, -ef->getPositionY());
		}
		else
		{
			getGameLayer()->skillEffectBatch->addChild(ef);
		}
	}
}

void Unit::setItem(ABType type)
{
	if (_isControlled)
		return;

	if (getName() == HeroEnum::Kankuro ||
		getName() == HeroEnum::Chiyo ||
		getName() == HeroEnum::Kiba ||
		getName() == HeroEnum::Kakuzu)
	{
		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
				if (mo->getName() != "Traps")
				{
					mo->setItem(Item1);
				}
			}
		}
	}
	_isCanItem1 = false;
	if (isPlayer())
	{
		if (_isAI)
		{
			getGameLayer()->getHudLayer()->offCoin(to_cstr(50));
		}
	}
	else
	{
		minusCoin(50);
	}
	scheduleOnce(schedule_selector(Hero::enableItem1), 5.0f);

	if (_hpBar)
	{
		uint32_t hpRestore = 3000 + gearRecoverValue;
		increaseHpAndUpdateUI(hpRestore);

		if (!_isHealing && !_healItemEffect)
		{
			_healItemEffect = Effect::create("hp_restore", this);
			_healItemEffect->setPosition(Vec2(isFlip() ? getContentSize().width / 2 + 16 : getContentSize().width / 2 - 16,
											  _hpBarHeight));
			addChild(_healItemEffect);
			//_isHealing=true;
		}
	}
}

bool Unit::setGear(GearType type)
{
	uint32_t gearCost;
	// The cost of [ 00 03 06 ] is 500
	if (type % 3 == 0)
		gearCost = 500;
	else
		gearCost = 1000;

	if (getGearArray().size() <= 2 && getCoin() >= gearCost)
	{
		getGearArray().push_back(type);

		if (isPlayer())
			getGameLayer()->getHudLayer()->offCoin(to_cstr(gearCost));
		else
			minusCoin(gearCost);

		switch (type)
		{
		case GearType::Gear00:
			_isCanGear00 = true;
			break;
		case GearType::Gear01:
			gearCKRValue = 25;
			break;
		case GearType::Gear02:
			isAttackGainCKR = true;
			break;
		case GearType::Gear03:
			_isCanGear03 = true;
			break;
		case GearType::Gear04:
			if (hasTempAttackValue1())
			{
				setTempAttackValue1(getTempAttackValue1() + 160);
			}
			setNAttackValue(getNAttackValue() + 160);
			hasArmorBroken = true;
			break;
		case GearType::Gear05:
			isGearCD = true;
			_sAttackCD1 -= 5;
			_sAttackCD2 -= 5;
			_sAttackCD3 -= 5;

			if (isPlayer())
			{
				getGameLayer()->getHudLayer()->skill1Button->setCD(_sAttackCD1 * 1000);
				getGameLayer()->getHudLayer()->skill2Button->setCD(_sAttackCD2 * 1000);
				getGameLayer()->getHudLayer()->skill3Button->setCD(_sAttackCD3 * 1000);

				getGameLayer()->getHudLayer()->skill1Button->_isColdChanged = true;
				getGameLayer()->getHudLayer()->skill2Button->_isColdChanged = true;
				getGameLayer()->getHudLayer()->skill3Button->_isColdChanged = true;
			}
			break;
		case GearType::Gear06:
			_isCanGear06 = true;
			break;
		case GearType::Gear07:
			gearRecoverValue = 3000;
			getGameLayer()->getHudLayer()->item1Button->setCD(3000);
			getGameLayer()->getHudLayer()->item1Button->_isColdChanged = true;
			break;
		case GearType::Gear08:
			setMaxHPValue(getMaxHP() + 6000);
			hasArmor = true;
			break;
		default:
			break;
		}

		return true;
	}
	else
	{
		return false;
	}
}

void Unit::useGear(GearType type)
{
	if (_isControlled)
		return;

	if (type == GearType::Gear00)
	{
		if (_state == State::NATTACK ||
			_state == State::WALK ||
			_state == State::IDLE)
		{
			if (getWalkSpeed() == 224)
			{
				setWalkSpeed(320);

				_isCanGear00 = false;

				_speedItemEffect = Effect::create("speedUp", this);
				addChild(_speedItemEffect);

				scheduleOnce(schedule_selector(Unit::enableGear00), 15.0f);
				if (isPlayer() || getGroup() == getGameLayer()->currentPlayer->getGroup())
					setOpacity(150);
				else
					setVisible(false);

				if (_hpBar)
					_hpBar->setVisible(false);
				if (_shadow)
					_shadow->setVisible(false);

				_isVisable = false;

				setSound("Audio/Effect/suzou_effect.ogg");
				schedule(schedule_selector(Unit::disableGear1), 3.0f);
			}
		}
	}
	else if (type == GearType::Gear03)
	{
		_isCanGear03 = false;
		setMon("Traps");
		scheduleOnce(schedule_selector(Unit::enableGear03), 15.0f);
	}
	else if (type == GearType::Gear06)
	{
		_isCanGear06 = false;
		scheduleOnce(schedule_selector(Unit::enableGear06), 15.0f);

		if (!_isInvincible && !_isArmored)
		{
			if (_state == State::IDLE ||
				_state == State::WALK ||
				_state == State::FLOAT ||
				_state == State::AIRHURT ||
				_state == State::HURT ||
				_state == State::KNOCKDOWN)
			{
				if (_isSticking)
				{
					_isSticking = false;
				}
				if (_state == State::FLOAT ||
					_state == State::AIRHURT)
				{
					setPositionY(_originY);
					_originY = 0;
					getGameLayer()->reorderChild(this, -getPositionY());
				}

				idle();

				setSkillEffect("tishen");
				scheduleOnce(schedule_selector(Unit::disableGear2), 1.0f);
				setSound("Audio/Effect/poof2.ogg");

				if (isPlayer() || getGroup() == getGameLayer()->currentPlayer->getGroup())
					setOpacity(150);
				else
					setVisible(false);

				if (_hpBar)
					_hpBar->setVisible(false);
				if (_shadow)
					_shadow->setVisible(false);

				_isVisable = false;
			}
		}
	}
}

void Unit::disableGear1(float dt)
{
	if (!_isVisable && _state != State::HURT)
	{
		setOpacity(255);
		setVisible(true);
		_isVisable = true;

		if (_hpBar)
			_hpBar->setVisible(true);
		if (_shadow)
			_shadow->setVisible(true);
	}
	else
	{
		unschedule(schedule_selector(Unit::disableGear1));
		if (getWalkSpeed() == 320)
		{
			setWalkSpeed(224);
		}
	}
}

void Unit::disableGear2(float dt)
{
	setOpacity(255);
	setVisible(true);
	_isVisable = true;

	if (_hpBar)
		_hpBar->setVisible(true);
	if (_shadow)
		_shadow->setVisible(true);
}

void Unit::disableGear3(float dt)
{
}

void Unit::enableGear00(float dt)
{
	_isCanGear00 = true;
}

void Unit::enableGear03(float dt)
{
	_isCanGear03 = true;
}

void Unit::enableGear06(float dt)
{
	_isCanGear06 = true;
}

void Unit::addCoin(uint32_t num)
{
	setCoin(getCoin() + num);
}

void Unit::minusCoin(uint32_t num)
{
	if (getCoin() > num)
		setCoin(getCoin() - num);
	else
		setCoin(0);
}

void Unit::setRestore(float dt)
{
	if (_hpBar)
	{
		increaseHpAndUpdateUI(800);

		_healItemEffect = Effect::create("hp_restore", this);
		_healItemEffect->setPosition(Vec2(isFlip() ? getContentSize().width / 2 + 16 : getContentSize().width / 2 - 16,
										  _hpBarHeight));
		addChild(_healItemEffect);
	}
}

void Unit::setRestore2(float dt)
{
	if (_hpBar)
	{
		bool isZone = false;
		if (isAkatsukiGroup() && getPositionX() <= getGameLayer()->currentMap->getTileSize().width * 2)
			isZone = true;
		else if (isKonohaGroup() && getPositionX() >= (getGameLayer()->currentMap->getMapSize().width - 2) * getGameLayer()->currentMap->getTileSize().width)
			isZone = true;

		if (isZone)
			setHPValue(getHP() > 1000 ? getHP() - 1000 : 100);

		if (_state == State::IDLE && getHpPercent() < 1)
		{
			increaseHpAndUpdateUI(300);
		}
	}
}

void Unit::disableEffect()
{
	if (_healItemEffect)
	{
		_healItemEffect->removeFromParent();
		_healItemEffect = nullptr;
	}

	if (_speedItemEffect)
	{
		_speedItemEffect->removeFromParent();
		_speedItemEffect = nullptr;
	}
}

void Unit::setSound(const string &file)
{
	if (UserDefault::sharedUserDefault()->getBoolForKey("isVoice"))
	{
		bool _isPlayable = false;
		if (isPlayer() ||
			abs((getPosition() - getGameLayer()->currentPlayer->getPosition()).x) < winSize.width / 2)
		{
			_isPlayable = true;
		}
		if (getGameLayer()->controlChar)
		{
			if (abs((getPosition() - getGameLayer()->controlChar->getPosition()).x) < winSize.width / 2)
			{
				_isPlayable = true;
			}
		}

		if (_isPlayable)
		{
			SimpleAudioEngine::sharedEngine()->preloadEffect(file.c_str());
			SimpleAudioEngine::sharedEngine()->playEffect(file.c_str());
		}
	}
}

void Unit::setDSound(const string &file)
{
	if (UserDefault::sharedUserDefault()->getBoolForKey("isVoice"))
	{
		bool _isPlayable = false;
		if (isPlayer() ||
			abs((getPosition() - getGameLayer()->currentPlayer->getPosition()).x) < winSize.width / 2)
		{
			_isPlayable = true;
		}
		if (getGameLayer()->controlChar)
		{
			if (abs((getPosition() - getGameLayer()->controlChar->getPosition()).x) < winSize.width / 2)
			{
				_isPlayable = true;
			}
		}

		if (_isPlayable && _isHitOne)
		{
			SimpleAudioEngine::sharedEngine()->preloadEffect(file.c_str());
			SimpleAudioEngine::sharedEngine()->playEffect(file.c_str());
		}
	}
}

void Unit::setAttackBox(const string &effectType)
{
	_effectType = effectType;

	if (_state == State::HURT)
	{
		if (getName() == HeroEnum::Sasuke ||
			getName() == HeroEnum::ImmortalSasuke ||
			getName() == HeroEnum::NarakaPath)
		{
			increaseHpAndUpdateUI(260);

			if (isPlayer())
			{
				getGameLayer()->setHPLose(getHpPercent());
			}

			_attackType = _spcAttackType1;
			_attackValue = getSpcAttackValue1();
			_attackRangeX = _spcAttackRangeX1;
			_attackRangeY = _spcAttackRangeY1;
		}
	}

	CCNotificationCenter::sharedNotificationCenter()->postNotification("acceptAttack", this);

	if (isPlayer())
	{
		if ((_state == State::OATTACK || _state == State::O2ATTACK) && _isHitOne == true && !getGameLayer()->_isShacking)
		{
			getGameLayer()->_isShacking = true;
			Scene *f = Director::sharedDirector()->getRunningScene();
			auto call = CallFunc::create(std::bind(&Unit::disableShack, this));
			f->runAction(newSequence(CCShake::create(0.05f, 12), call));
		}
		if (getGameLayer()->_isAttackButtonRelease && _state == State::NATTACK && !_isOnlySkillLocked && !_isAI)
		{
			idle();
			return;
		}
	}
}

void Unit::getSticker(float dt)
{
	for (auto hero : getGameLayer()->_CharacterArray)
	{
		Unit *tempSticker = nullptr;
		if (hero->_sticker)
		{
			tempSticker = hero->_sticker;
		}
		if (tempSticker && tempSticker->getName() == getName() && hero->_isSticking)
		{
			return;
		}
	}

	unschedule(schedule_selector(Unit::getSticker));
	dealloc();
}

void Unit::disableShack()
{
	getGameLayer()->_isShacking = false;
	if (isTower())
	{
		_isHitOne = false;
	}
}

void Unit::setMove(int moveLength)
{
	if (getKnockLength())
	{
		if (getKnockLength() == 1)
			return;

		moveLength = getKnockLength();
	}

	if (getPositionX() > getGameLayer()->currentMap->getTileSize().width &&
		getPositionX() < (getGameLayer()->currentMap->getMapSize().width - 1) * getGameLayer()->currentMap->getTileSize().width)
	{
		ActionInterval *mv;
		if (_state == State::HURT)
		{
			if (!_knockDirection)
				mv = MoveBy::create(0.1f, Vec2(_hurtFromRight ? -moveLength : moveLength, 0));
			else
				mv = MoveBy::create(0.1f, Vec2(_knockDirection ? -moveLength : moveLength, 0));
			runAction(mv);
		}
		else
		{
			mv = MoveBy::create(0.1f, Vec2(isFlip() ? -moveLength : moveLength, 0));
			runAction(mv);
		}
	}
}

void Unit::setJump(bool jumpDirection)
{
	if (_state != State::FLOAT &&
		_state != State::AIRHURT &&
		_state != State::HURT &&
		_state != State::DEAD)
	{
		_state = State::JUMP;

		float posX = getPositionX();
		float posY = getPositionY();
		_originY = posY;

		if (jumpDirection) // Jump forward
		{
			_jumpUPAction = JumpTo::create(0.8f, Vec2(posX + (isFlip() ? -64 : 64), posY), 64, 1);
		}
		else // Jump back
		{
			_jumpUPAction = JumpTo::create(0.8f, Vec2(posX + (isFlip() ? 64 : -64), posY), 64, 1);
		}

		runAction(_jumpUPAction);
	}
}

void Unit::setCharge(int moveLength)
{
	if ((getPositionX() < getGameLayer()->currentMap->getTileSize().width && isFlip()) ||
		(getPositionX() > (getGameLayer()->currentMap->getMapSize().width - 1) * getGameLayer()->currentMap->getTileSize().width && !isFlip()))
	{
		return;
	}
	else
	{
		_moveAction = MoveBy::create(0.1f, Vec2(isFlip() ? -moveLength * kSpeedBase : moveLength * kSpeedBase, 0));
		runAction(_moveAction);
	}
}

// without getCollider
void Unit::setChargeB(int moveLength)
{
	if ((getPositionX() < getGameLayer()->currentMap->getTileSize().width && isFlip()) ||
		(getPositionX() > (getGameLayer()->currentMap->getMapSize().width - 1) * getGameLayer()->currentMap->getTileSize().width && !isFlip()))
	{
		return;
	}
	else
	{
		float delay = (_state == State::OATTACK || _state == State::O2ATTACK)
						  ? 0.4f
						  : 0.1f;
		_moveAction = MoveBy::create(delay, Vec2(isFlip() ? -moveLength * kSpeedBase : moveLength * kSpeedBase, 0));
		runAction(_moveAction);
	}
}

void Unit::setCommand(const string &cmd)
{
	CommandSystem::invoke(cmd, this);
}

void Unit::setBuff(int buffValue)
{
	float buffStayTime = _attackRangeY;

	if (_attackType == "hBuff")
	{
		_healBuffValue = buffValue;
		schedule(schedule_selector(Unit::healBuff), 1);
		setBuffEffect("hBuff");
	}
	else if (_attackType == "sBuff" ||
			 _attackType == "rsBuff" ||
			 _attackType == "hsBuff" ||
			 _attackType == "dcBuff")
	{
		_skillUPBuffValue = buffValue;
		scheduleOnce(schedule_selector(Unit::disableBuff), buffStayTime);
		setBuffEffect(_attackType);

		setSAttackValue1(getSAttackValue1() + _skillUPBuffValue);
		setSAttackValue2(getSAttackValue2() + _skillUPBuffValue);
		setSAttackValue3(getSAttackValue3() + _skillUPBuffValue);

		if (_attackType == "hsBuff")
		{
			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (getGroup() != hero->getGroup() && hero->isPlayerOrCom() && hero->_state != State::HURT && hero->_state != State::DEAD)
				{
					float distanceX = (hero->getPosition() - getPosition()).x;
					if (distanceX < kAttackRange)
					{
						if (!hero->_isVisable)
						{
							if (hero->getName() == HeroEnum::Konan ||
								hero->getName() == HeroEnum::Deidara)
							{
								hero->unschedule(schedule_selector(Unit::disableBuff));
							}

							hero->setOpacity(255);
							hero->setVisible(true);
							hero->_isVisable = true;

							if (hero->_hpBar)
								hero->_hpBar->setVisible(true);
							if (hero->_shadow)
								hero->_shadow->setVisible(true);
						}
					}
				}
			}
			if (getName() == HeroEnum::Neji)
			{
				_isArmored = true;
			}
		}
	}
	else if (_attackType == "cBuff") // change action buff
	{
		_skillChangeBuffValue = buffValue;

		if (getName() == HeroEnum::Shino ||
			getName() == HeroEnum::Sai ||
			getName() == HeroEnum::Deidara)
		{
			if (_skillChangeBuffValue == 17)
			{
				scheduleOnce(schedule_selector(Unit::resumeAction), buffStayTime);
			}
			else if (_skillChangeBuffValue == 18)
			{
				unschedule(schedule_selector(Unit::resumeAction));
				setActionTo<ActionFlag::NAttack, ActionFlag::NAttack>();
				scheduleOnce(schedule_selector(Unit::resumeAction), buffStayTime);
			}
		}
		else if (getName() == HeroEnum::Kiba)
		{
			if (_skillChangeBuffValue == 18)
			{
				scheduleOnce(schedule_selector(Unit::resumeAction), buffStayTime);
			}
		}
		else if ((getName() == HeroEnum::ImmortalSasuke ||
				  getName() == HeroEnum::Sasuke) &&
				 _skillChangeBuffValue == 18)
		{
			unschedule(schedule_selector(Unit::resumeAction));
			unschedule(schedule_selector(Unit::disableBuff));

			_isTaunt = false;
			// setHurtAction(createAnimation(hurtArray, 10, false, true));
			auto call = CallFunc::create(std::bind(&Unit::idle, this));
			auto autoReturnIdleHurtAction = Sequence::create(getAction(ActionFlag::Hurt), call);
			setHurtAction(autoReturnIdleHurtAction);
			// setActionTo<ActionFlag::Hurt, ActionFlag::Hurt>();
			disableBuff(0);

			scheduleOnce(schedule_selector(Unit::resumeAction), buffStayTime);
		}
		else if (getName() == HeroEnum::Minato)
		{
			if (_skillChangeBuffValue == 18)
			{
				scheduleOnce(schedule_selector(Unit::resumeAction), buffStayTime);
			}
		}
		else
		{
			if (isNotGuardian() &&
				getName() != HeroEnum::Kankuro &&
				getName() != HeroEnum::Chiyo &&
				getName() != HeroEnum::Hiruzen &&
				getName() != HeroEnum::Suigetsu &&
				getName() != HeroEnum::Jugo &&
				getName() != HeroEnum::Kisame &&
				getName() != KugutsuEnum::Parents &&
				getName() != HeroEnum::Lee &&
				getName() != HeroEnum::RockLee &&
				getName() != HeroEnum::Nagato)
			{
				scheduleOnce(schedule_selector(Unit::resumeAction), buffStayTime);
			}
		}

		changeAction();
	}
	else if (_attackType == "tBuff") // change action buff
	{
		_skillChangeBuffValue = buffValue;
		scheduleOnce(schedule_selector(Unit::resumeAction), buffStayTime);
		scheduleOnce(schedule_selector(Unit::disableBuff), buffStayTime);
		setBuffEffect(_attackType);

		changeAction();
	}
	// else if (_attackType == "gBuff") // TODO: New Nagato
	// {
	// 	_skillChangeBuffValue = buffValue;
	// 	if (getName() == HeroEnum::Nagato)
	// 	{
	// 		if (_skillChangeBuffValue == 18 && hearts == 1)
	// 		{
	// 			scheduleOnce(schedule_selector(Unit::resumeAction), buffStayTime);
	// 		}
	// 	}
	// 	changeAction2();
	// }
	else if (_attackType == "stBuff")
	{
		if (isPlayer() || getGroup() == getGameLayer()->currentPlayer->getGroup())
			setOpacity(150);
		else
			setVisible(false);

		if (_hpBar)
			_hpBar->setVisible(false);

		if (_shadow)
			_shadow->setVisible(false);

		_isVisable = false;
		scheduleOnce(schedule_selector(Unit::disableBuff), buffStayTime);
	}
	else if (_attackType == "GroupHeal" ||
			 _attackType == "GroupBuff")
	{
		if (_healBuffValue)
			_healBuffValue += buffValue;
		else
			_healBuffValue = buffValue;

		schedule(schedule_selector(Unit::healBuff), 1);
	}

	if (isPlayer())
		getGameLayer()->getHudLayer()->setBuffDisplay(_attackType, buffStayTime);
}

void Unit::setBuffEffect(const string &type)
{
	if (_skillBuffEffect)
	{
		_skillBuffEffect->removeFromParent();
		_skillBuffEffect = nullptr;
	}

	if (_healBuffEffect)
	{
		_healBuffEffect->removeFromParent();
		_healBuffEffect = nullptr;
	}

	if (type == "hBuff")
	{
		_healBuffEffect = Effect::create(type, this);
		addChild(_healBuffEffect);
	}
	else if (type == "hsBuff")
	{
		_skillBuffEffect = Effect::create(type, this);
		_skillBuffEffect->setPositionY(14);
		addChild(_skillBuffEffect);
	}
	else if (type == "tBuff" ||
			 type == "dcBuff" ||
			 type == "jdBuff" ||
			 type == "bmBuff")
	{
		_skillBuffEffect = Effect::create(type, this);
		addChild(_skillBuffEffect);
	}
	else if (type == "dhBuff")
	{
		_dehealBuffEffect = Effect::create(type, this);
		addChild(_dehealBuffEffect);
	}
	else if (type == "sBuff")
	{
		_skillBuffEffect = Effect::create(type, this);
		addChild(_skillBuffEffect);
	}
}

void Unit::removeBuffEffect(const string &type)
{
	if (type == "hBuff" && _healBuffEffect)
	{
		_healBuffEffect->removeFromParent();
		_healBuffEffect = nullptr;
	}
	else if (type == "sBuff" && _skillBuffEffect)
	{
		_skillBuffEffect->removeFromParent();
		_skillBuffEffect = nullptr;
	}
	else if (type == "dhBuff" && _dehealBuffEffect)
	{
		_dehealBuffEffect->removeFromParent();
		_dehealBuffEffect = nullptr;
	}

	else if (type == "all")
	{
		if (_healBuffEffect)
		{
			_healBuffEffect->removeFromParent();
			_healBuffEffect = nullptr;
			_healBuffValue = 0;
			_buffStartTime = 0;
		}
		if (_powerBuffEffect)
		{
			_powerBuffEffect->removeFromParent();
			_powerBuffEffect = nullptr;
		}
		if (_skillBuffEffect)
		{
			_skillBuffEffect->removeFromParent();
			_skillBuffEffect = nullptr;
		}
		if (_dehealBuffEffect)
		{
			_dehealBuffEffect->removeFromParent();
			_dehealBuffValue = 0;
			_dehealBuffEffect = nullptr;
			_debuffStartTime = 0;
		}
	}
}

void Unit::disableBuff(float dt)
{
	if (_skillUPBuffValue)
	{
		setSAttackValue1(getSAttackValue1() - _skillUPBuffValue);
		setSAttackValue2(getSAttackValue2() - _skillUPBuffValue);
		setSAttackValue3(getSAttackValue3() - _skillUPBuffValue);
		_skillUPBuffValue = 0;

		if (getName() == HeroEnum::Neji)
		{
			_isArmored = false;
		}
		removeBuffEffect("sBuff");
	}
	else if (_skillBuffEffect)
	{
		removeBuffEffect("sBuff");
	}
	else if (!_isVisable && _state != State::HURT)
	{
		setOpacity(255);
		setVisible(true);
		_isVisable = true;

		if (_hpBar)
			_hpBar->setVisible(true);
		if (_shadow)
			_shadow->setVisible(true);
	}
	else if (_skillChangeBuffValue && getName() == HeroEnum::Tobi)
	{
		setOpacity(255);
	}
}

void Unit::disableDebuff(float dt)
{
	if ((getName() == HeroEnum::ImmortalSasuke || getName() == HeroEnum::Itachi) && _isArmored)
	{
		return;
	}

	if (getWalkSpeed() == 112)
		setWalkSpeed(224);
}

void Unit::healBuff(float dt)
{
	cc_timeval timeVal;
	CCTime::gettimeofdayCocos2d(&timeVal, 0);
	float curTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;

	if (!_buffStartTime)
	{
		_buffStartTime = curTime;
	}
	int limitTime = 10000;

	if (getName() == HeroEnum::Tsunade)
	{
		limitTime = 15000;
	}

	if (_buffStartTime && curTime - _buffStartTime >= limitTime)
	{
		unschedule(schedule_selector(Unit::healBuff));
		removeBuffEffect("hBuff");
		_healBuffValue = 0;
		_buffStartTime = 0;
		return;
	}

	if (getName() == HeroEnum::Karin)
	{
		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (getGroup() == hero->getGroup() && hero->isPlayerOrCom() && hero->_state != State::DEAD)
			{
				float distanceX = (hero->getPosition() - getPosition()).x;
				float atkRangeX = 128 + getContentSize().width / 2;
				if (abs(distanceX) <= atkRangeX &&
					abs(hero->getPositionY() - getPositionY()) <= 128)
				{
					hero->increaseHpAndUpdateUI(_healBuffValue);

					if (hero->isPlayer())
						getGameLayer()->setHPLose(hero->getHpPercent());

					if (hero->_isVisable)
					{
						Effect *tmpEffect = Effect::create("Kagura", hero);
						if (hero->isPlayer())
						{
							tmpEffect->setOpacity(150);
						}
						tmpEffect->setPosition(Vec2(hero->getContentSize().width / 2, hero->getContentSize().height / 2));
						hero->addChild(tmpEffect);
					}
				}
			}
		}
	}
	else if (getName() == HeroEnum::Chiyo)
	{
		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (getGroup() == hero->getGroup() &&
				hero->isPlayerOrCom() &&
				hero->getName() != HeroEnum::Chiyo)
			{
				Vec2 sp = hero->getPosition() - getPosition();
				if (abs(sp.x) <= kAttackRange)
				{
					hero->increaseAllCkrs(_healBuffValue);

					if (hero->_isVisable)
					{
						Effect *tmpEffect = Effect::create("Hupo", hero);
						if (hero->isPlayer())
						{
							tmpEffect->setOpacity(150);
						}
						tmpEffect->setPosition(Vec2(hero->getContentSize().width / 2, hero->getContentSize().height / 2 + 6));
						hero->addChild(tmpEffect);
					}
				}
			}
		}
	}
	else if (getName() == SummonEnum::Slug)
	{
		auto list = isAkatsukiGroup()
						? getGameLayer()->_AkatsukiFlogArray
						: getGameLayer()->_KonohaFlogArray;
		for (auto flog : list)
		{
			if (getGroup() == flog->getGroup() && flog->_state != State::DEAD)
			{
				float distanceX = (flog->getPosition() - getPosition()).x;
				float atkRangeX = 128 + getContentSize().width / 2;
				if (abs(distanceX) <= atkRangeX &&
					abs(flog->getPositionY() - getPositionY()) <= 128)
				{
					flog->increaseHpAndUpdateUI(_healBuffValue);
				}
			}
		}
	}
	else if (getName() == HeroEnum::Sakura ||
			 getName() == HeroEnum::Tsunade)
	{
		increaseHpAndUpdateUI(_healBuffValue);
	}
}

void Unit::dehealBuff(float dt)
{
	cc_timeval timeVal;
	CCTime::gettimeofdayCocos2d(&timeVal, 0);
	float curTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;

	if (!_debuffStartTime)
		_debuffStartTime = curTime;

	if (_debuffStartTime && abs(_debuffStartTime - curTime) > 10000)
	{
		unschedule(schedule_selector(Unit::dehealBuff));
		setWalkSpeed(_originSpeed);
		removeBuffEffect("dhBuff");
		_dehealBuffValue = 0;
		_debuffStartTime = 0;
		return;
	}

	for (auto hero : getGameLayer()->_CharacterArray)
	{
		if (hero->getName() == HeroEnum::Asuma)
			_slayer = hero;
	}

	if (getHP() <= _dehealBuffValue)
		setDamage(_slayer, "c_hit", _dehealBuffValue, false);
	else
		setDamage(_slayer, "c_hit", _dehealBuffValue, false);

	if (isPlayer())
		getGameLayer()->setHPLose(getHpPercent());
}

// FIXME: Only for Shikamaru's KageHand
void Unit::lostBlood(float dt)
{
	if (lbAttackerId == -1)
		return;

	for (auto hero : getGameLayer()->_CharacterArray)
	{
		if (hero->getCharId() == lbAttackerId && hero->getName() == HeroEnum::Shikamaru)
		{
			_slayer = hero;
			lbAttackerId = -1;
		}
	}

	CCAssert(lbAttackerId == -1, "Not found Shikamaru");
	if (lbAttackerId != -1)
		return;

	setDamage(_slayer, "c_hit", lostBloodValue, false);

	if (isPlayer())
		getGameLayer()->setHPLose(getHpPercent());
}

void Unit::removeLostBlood(float dt)
{
	lostBloodValue = 0;
	lbAttackerId = -1;
	unschedule(schedule_selector(Unit::lostBlood));
}

void Unit::changeAction()
{
}

void Unit::changeAction2()
{
	if (getName() == HeroEnum::Minato)
	{
		_attackValue = getSpcAttackValue2();
		setAttackType(getSpcAttack2Type());
		_attackRangeX = _spcAttackRangeX2;
		_attackRangeY = _spcAttackRangeY2;
		setActionTo<ActionFlag::Skill02, ActionFlag::Spc02>();
	}
	// else if (getName() == HeroEnum::Nagato) // TODO: New Nagato
	// {
	// 	if (_skillChangeBuffValue == 18)
	// 	{
	// 		setActionTo<ActionFlag::Hurt, ActionFlag::Spc04>();
	// 	}
	// }
}

// Release catched characters
void Unit::reCatched(float dt)
{
	setVisible(true);
	_isVisable = true;

	if (_shadow)
		_shadow->setVisible(true);
}

void Unit::resumeAction(float dt)
{
	_skillChangeBuffValue = 0;
}

void Unit::setActionResume()
{
}

void Unit::setActionResume2()
{
	if (getName() == HeroEnum::Minato)
	{
		setActionTo<ActionFlag::Skill02, ActionFlag::Spc02>();
	}
	// else if (getName() == HeroEnum::Nagato) // TODO: New Nagato
	// {
	// 	if (_skillChangeBuffValue == 18)
	// 	{
	// 		hearts -= 1;
	// 		setHurtAction(createAnimation(hurtArray, 10, false, true));
	// 	}
	// 	_skillChangeBuffValue = 0;
	// }
}

void Unit::getCollider()
{
	schedule(schedule_selector(Unit::stopMove), 0.0f);
}

void Unit::stopMove(float dt)
{
	if (getPositionX() <= getGameLayer()->currentMap->getTileSize().width ||
		getPositionX() >= (getGameLayer()->currentMap->getMapSize().width - 1) * getGameLayer()->currentMap->getTileSize().width)
	{
		unschedule(schedule_selector(Unit::stopMove));
		getActionManager()->removeAction(_moveAction);
		return;
	}

	for (auto hero : getGameLayer()->_CharacterArray)
	{
		if (getGroup() != hero->getGroup() && hero->_isVisable && hero->_state != State::DEAD && hero->_state != State::JUMP && !hero->_isInvincible)
		{
			float distanceX = (hero->getPosition() - getPosition()).x;
			float atkRangeX = _attackRangeX + getContentSize().width / 2;
			if (abs(distanceX) <= atkRangeX &&
				abs(hero->getPositionY() - getPositionY()) <= _attackRangeY)
			{
				unschedule(schedule_selector(Unit::stopMove));
				getActionManager()->removeAction(_moveAction);
				return;
			}
		}
	}
}

void Unit::stopJump(int stopTime)
{
	if (_state == State::JUMP)
	{
		getActionManager()->pauseTarget(this);
		scheduleOnce(schedule_selector(Unit::resumePauseStuff), stopTime / 100.0f);
	}
}

void Unit::setBullet(const string &name)
{
	auto projectile = Bullet::create();
	projectile->setID(name, Role::Bullet, _group);
	projectile->idle();
	projectile->_master = _master ? _master : this;

	if (isFlip())
	{
		projectile->setFlippedX(true);
	}

	getGameLayer()->addChild(projectile, -getPositionY());

	if (name == "PaperSrk")
	{
		projectile->setScale(0.8f);
		projectile->setPosition(Vec2(getPositionX() + (isFlip() ? -32 : 32),
									 getPositionY() + 52));
		projectile->attack(NAttack);
		projectile->setMove(192, 2.0f, false);
	}
	else if (name == "PaperSpear")
	{
		projectile->setScale(0.8f);
		projectile->setPosition(Vec2(getPositionX() + (isFlip() ? -68 : 68),
									 getPositionY() + 42));
		projectile->attack(NAttack);
		projectile->setMove(192, 2.0f, false);
	}
	else if (name == "HugeSRK")
	{
		projectile->setScale(0.8f);
		projectile->setPosition(Vec2(getPositionX() + (isFlip() ? -76 : 76),
									 getPositionY() + getHPBarHeight() / 2));
		if (_skillUPBuffValue)
			projectile->setNAttackValue(projectile->getNAttackValue() + _skillUPBuffValue);

		projectile->scheduleOnce(schedule_selector(Bullet::setAttack), 0.5f);
		scheduleOnce(schedule_selector(Unit::setBulletGroup), 0.2f);
		projectile->setEaseIn(224, 5.0f);
	}
	else if (name == "FlyKnife" ||
			 name == "TentenSRK")
	{
		projectile->setScale(0.8f);
		projectile->setPosition(Vec2(getPositionX() + (isFlip() ? -32 : 32),
									 getPositionY() + getHPBarHeight() / 2));

		projectile->setEaseIn(224, 2.0f);
		projectile->attack(NAttack);
	}
	else if (name == ProjectileEnum::HiraishinKunai ||
			 name == ProjectileEnum::Shintenshin)
	{
		if (name == ProjectileEnum::HiraishinKunai)
		{
			projectile->setScale(0.8f);
			projectile->setPosition(Vec2(getPositionX() + (isFlip() ? -42 : 42),
										 getPositionY() + getHPBarHeight() / 2));
		}
		else
		{
			projectile->setAnchorPoint(Vec2(0.5f, 0));
			projectile->setPosition(Vec2(getPositionX() + (isFlip() ? -42 : 42),
										 getPositionY()));
		}

		projectile->_originY = getPositionY();
		projectile->setEaseIn(196, 2.0f);
		projectile->attack(NAttack);
		_monsterArray.push_back(projectile);
	}
	else
	{
		projectile->setPosition(Vec2(getPositionX() + (isFlip() ? -32 : 32),
									 getPositionY() + getContentSize().height / 2));

		projectile->attack(NAttack);
		projectile->setMove(192, 2.0f, false);
	}
}

void Unit::setBulletGroup(float dt)
{
	for (int i = 0; i < 2; i++)
	{
		auto projectile = Bullet::create();
		float rangeX = 0;

		projectile->setID("HugeSRK", Role::Bullet, _group);
		rangeX = 76;

		projectile->_master = this;
		projectile->setScale(0.8f);

		if (isFlip())
		{
			projectile->setFlippedX(true);
		}
		if (i == 0)
		{
			Vec2 location = Vec2(getPositionX() + (isFlip() ? -rangeX : rangeX), getPositionY() + (getHPBarHeight() / 2 + 23));
			projectile->setPosition(location);
		}
		else
		{
			Vec2 location = Vec2(getPositionX() + (isFlip() ? -rangeX : rangeX), getPositionY() + (getHPBarHeight() / 2 - 23));
			projectile->setPosition(location);
		}
		getGameLayer()->addChild(projectile, kSkillEffectOrder);
		projectile->idle();
		if (_skillUPBuffValue)
		{
			projectile->setNAttackValue(projectile->getNAttackValue() + _skillUPBuffValue);
		}

		projectile->scheduleOnce(schedule_selector(Bullet::setAttack), 0.5f);
		projectile->setEaseIn(352, 5.0f);
	}
}

Hero *Unit::createClone(int cloneTime)
{
	return nullptr;
}

void Unit::setClone(int cloneTime)
{
	Hero *clone = createClone(cloneTime);
	if (clone == nullptr)
	{
		CCLOG("Current character %s can not create clone", getName().c_str());
		return;
	}

	if (_master)
	{
		clone->setMaster(this);
		clone->setSecMaster(_master);
	}
	else
	{
		clone->setMaster(this);
	}

	clone->setPosition(Vec2(getPositionX() + (isFlip() ? -32 : 32), getPositionY() - 1));

	if ((getName() == HeroEnum::SageNaruto || getName() == HeroEnum::Naruto) ||
		(getName() == HeroEnum::RikudoNaruto && cloneTime == 10))
	{
		clone->setHPValue(getHP(), false);
	}
	else
	{
		clone->setHPValue(getMaxHP(), false);
	}

	clone->setMaxHPValue(getMaxHP(), false);
	clone->_exp = _exp;
	clone->setNAttackValue(getNAttackValue());
	clone->_defense = _defense;
	clone->_level = _level;
	clone->setHPbar();
	clone->_hpBar->getHPBAR()->setScaleX(clone->getHpPercent());

	if (getName() == HeroEnum::RikudoNaruto && cloneTime == 9)
	{
		if (clone->_hpBar)
		{
			clone->_hpBar->setPositionY(120);
		}
		clone->setNAttackValue(1060);
	}
	else if (getName() == HeroEnum::Kakashi)
	{
		clone->setNAttackValue(1060);
	}

	if (hasArmorBroken)
	{
		clone->hasArmorBroken = true;
	}

	if (hasArmor)
	{
		clone->hasArmor = true;
	}

	clone->setFlippedX(isFlip());
	clone->setSkillEffect("smk");
	clone->idle();
	getGameLayer()->_CharacterArray.push_back(clone);
	getGameLayer()->addChild(clone, -clone->getPositionY());
	clone->doAI();

	if (cloneTime > 0)
	{
		clone->scheduleOnce(schedule_selector(Hero::removeClone), cloneTime);
	}
}

void Unit::removeClone(float dt)
{
	dead();
}

void Unit::removeAllClones()
{
	auto &unitArray = getGameLayer()->_CharacterArray;
	for (auto c : unitArray)
	{
		if (c->getMaster() == this)
		{
			std::erase(unitArray, c);
		}
	}
}

void Unit::setMon(const string &monName)
{
	// FIXME: Use in mon master config
	// float monsterStayTime = _attackRangeY;

	auto monster = Monster::create();
	monster->setID(monName, Role::Mon, _group);

	if (_master)
	{
		if (getSecMaster())
		{
			monster->setMaster(this);
			monster->setSecMaster(getSecMaster());
		}
		else
		{
			monster->setMaster(_master);
			monster->setSecMaster(this);
		}
	}
	else
	{
		monster->setMaster(this);
	}

	monster->idle();
	monster->setPosition(Vec2(getPositionX() + (isFlip() ? -32 : 32), _originY ? _originY : getPositionY()));
	monster->setFlippedX(isFlip());

	if (monName == "FakeDeidara" ||
		monName == "FakeKisame" || // DEPRECATED:
		monName == "DeidaraBom" ||
		monName == "ChuiDi" ||
		monName == "SakuraBom" ||
		monName == "Shoryu" ||
		monName == "Stream" || // DEPRECATED:
		monName == "FakeMinato")
	{
		monster->setPosition(Vec2(getPositionX(), _originY ? _originY : getPositionY()));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "LeeBom")
	{
		// monster->setAnchorPoint(Vec2(0.5,0.5f));
		monster->setPosition(getPosition());
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "FakeItachi")
	{
		monster->setPosition(Vec2(getPositionX(), _originY ? _originY : getPositionY() - 4));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "Tenmu")
	{
		monster->setPosition(Vec2(getPositionX(), _originY));
		monster->setAnchorPoint(Vec2(0.5, -0.1f));
		monster->attack(NAttack);
	}
	else if (monName == "Kaiten")
	{
		monster->setPosition(getPosition());
		monster->setAnchorPoint(Vec2(0.5, 0.25f));
		monster->attack(NAttack);
	}
	else if (monName == "Crash" ||
			 monName == "Crash2")
	{
		monster->setPosition(Vec2(getPositionX() + (isFlip() ? -32 : 32), _originY ? _originY : getPositionY()));
		monster->setAnchorPoint(Vec2(0.5, 0.25f));
		monster->attack(NAttack);
	}
	else if (monName == "SansyoRed")
	{
		monster->setPosition(Vec2(isFlip() ? getPositionX() - 240 : getPositionX() + 240, getPositionY() - 32));
		monster->attack(NAttack);
	}
	else if (monName == "SansyoGreen")
	{
		monster->setPosition(Vec2(isFlip() ? getPositionX() - 144 : getPositionX() + 144, getPositionY() - 32 + 1));
		monster->attack(NAttack);
	}
	else if (monName == "SansyoBlue")
	{
		monster->setPosition(Vec2(isFlip() ? getPositionX() - 48 : getPositionX() + 48, getPositionY() - 32 + 2));
		monster->attack(NAttack);
	}
	else if (monName == SummonEnum::SmallSlug)
	{
		if (_monsterArray.size() < 3)
		{
			monster->setSkillEffect("smk");
			_monsterArray.push_back(monster);
			monster->doAI();
		}
		else
		{
			monster = nullptr;
			return;
		}
	}
	else if (monName == "Kuroari")
	{
		monster->setSkillEffect("smk");
		_monsterArray.push_back(monster);
		monster->doAI();
	}
	else if (monName == "PaperRain" ||
			 monName == "Steam")
	{
		monster->setPosition(Vec2(isFlip() ? getPositionX() - 16 : getPositionX() + 16, _originY));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "FireRain")
	{
		monster->setPosition(Vec2(isFlip() ? getPositionX() - 75 : getPositionX() + 75, _originY - 1));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "Tuji" ||
			 monName == "Tuji2" ||
			 monName == "Suiji")
	{
		monster->setPosition(Vec2(getPositionX() + (isFlip() ? -64 : 64),
								  getPositionY() - 24));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "ThunderWave")
	{
		monster->setPosition(Vec2(getPositionX(), getPositionY() - 1));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "Jibaku" ||
			 monName == "JibakuEX" ||
			 monName == "Shenwei")
	{
		monster->setPosition(Vec2(getPositionX() + (isFlip() ? -96 : 96), getPositionY()));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "Bikyu")
	{
		monster->hasArmorBroken = true;
		monster->setPosition(Vec2(getPositionX() + (isFlip() ? -(16 + getContentSize().width) : (16 + getContentSize().width)),
								  getPositionY() - 32));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "Qilin")
	{
		monster->setPosition(Vec2(getPositionX() + (isFlip() ? -4 : 4), getPositionY() - 6));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "Laser") // TODO: New Nagato
	{
		monster->setPosition(Vec2(getPositionX() + (isFlip() ? -100 : 100), getPositionY()));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "MagicDragon") // TODO: New Nagato
	{
		monster->hasArmorBroken = true;
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
		monster->setDirectMove(156, 2.0f, false);
	}
	// TODO: New Nagato
	else if (monName == "Chameleon" ||
			 monName == "Naraka" ||
			 monName == "Roar" ||
			 monName == "Smoke" ||
			 monName == "BannShou" ||
			 monName == "Bull" ||
			 monName == "Raintiger")
	{
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "SuiRyuDan" ||
			 monName == "DotonPillar" ||
			 monName == "Yataikuzu" ||
			 monName == "Yominuma" ||
			 monName == "Dogs" ||
			 monName == "SandHand" ||
			 monName == "KageFeng" ||
			 monName == "Sanbao" ||
			 monName == "SandBall" ||
			 monName == "Sabaku" ||
			 monName == "SandWave" ||
			 monName == "Tsukuyomi" ||
			 monName == "Shark")
	{
		monster->setPosition(Vec2(getPositionX() + (isFlip() ? -48 : 48), getPositionY() - 4));
		monster->attack(NAttack);
	}
	else if (monName == "Suijin" ||
			 monName == "BugPillar")
	{
		monster->setPosition(Vec2(getPositionX() + (isFlip() ? -64 : 64), getPositionY() + 1));
		monster->attack(NAttack);
	}
	else if (monName == "Mine")
	{
		monster->setSkillEffect("smk");
		_monsterArray.push_back(monster);
		monster->doAI();
		if (getGroup() != getGameLayer()->currentPlayer->getGroup())
		{
			monster->setVisible(false);
		}
	}
	else if (monName == "Kage")
	{
		_isCatchOne = true;
		monster->setPosition(Vec2(getPositionX() + (isFlip() ? -getContentSize().width / 2 + 4 : getContentSize().width / 2 - 4),
								  getPositionY()));
		if (isFlip())
		{
			monster->setAnchorPoint(Vec2(1, 0));
		}
		else
		{
			monster->setAnchorPoint(Vec2(0, 0));
		}

		stopAllActions();
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
		monster->doAI();
	}
	else if (monName == "KageHand")
	{
		Vec2 dir = Vec2(isFlip() ? getPositionX() - getContentSize().width : getPositionX() + getContentSize().width,
						getPositionY());
		monster->setPosition(dir);
		stopAllActions();

		if (_master)
			_master->_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "KageHands")
	{
		if (_master)
			_master->_monsterArray.push_back(monster);
		monster->setPosition(getPosition());
		monster->setAnchorPoint(Vec2(0.5f, 0.15f));
		monster->attack(NAttack);
	}
	else if (monName == "QuanRen")
	{
		monster->setPosition(Vec2(isFlip() ? getPositionX() - 64 : getPositionX() + 64, _originY));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else if (monName == "ItachiSusano" ||
			 monName == "SasukeSusano")
	{
		_monsterArray.push_back(monster);
	}
	else if (monName == SkillEnum::HiraishinMark)
	{
		_monsterArray.push_back(monster);
		_isCanSkill1 = true;
	}
	else if (monName == "CircleMark")
	{
		monster->setPosition(getPosition());
		monster->setAnchorPoint(Vec2(0.5f, 0.5f));
		_monsterArray.push_back(monster);
		monster->attack(NAttack);

		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill1Button->setLock();
		}
	}
	else if (monName == "InkDragon")
	{
		monster->setPosition(Vec2(isFlip() ? getPositionX() - 128 : getPositionX() + 128, getPositionY()));
		monster->attack(NAttack);
		monster->setDirectMove(156, 2.0f, false);
	}
	else if (monName == "BugTomado")
	{
		monster->attack(NAttack);
		monster->setDirectMove(128, 2.0f, false);
	}
	else if (monName == "FutonSRK2" ||
			 monName == "FutonSRK")
	{
		monster->setPosition(Vec2(getPositionX() + (isFlip() == true ? -48 : 48), getPositionY()));

		monster->attack(NAttack);
		bool isFollow = false;
		Vec2 moveDirection;
		if (_mainTarget)
		{
			if (_mainTarget->getPositionX() > getPositionX() && !isFlip())
			{
				isFollow = true;
			}
			else if (_mainTarget->getPositionX() <= getPositionX() && isFlip())
			{
				isFollow = true;
			}
		}

		if (isFollow)
		{
			monster->_mainTarget = _mainTarget;
			monster->doAI();
		}
		else
		{
			if (isFlip())
				moveDirection = Vec2(-1, 0).getNormalized();
			else
				moveDirection = Vec2(1, 0).getNormalized();
			monster->setState(State::WALK);
			monster->walk(moveDirection);
		}
	}
	else if (monName == "Kubi")
	{
		monster->attack(NAttack);
		monster->setDirectMove(128, 0.8f, true);
	}
	else if (monName == "Shark2")
	{
		monster->attack(NAttack);
		monster->setEaseIn(224, 3.0f);
	}
	else if (monName == "WaterBullet" ||
			 monName == "BoneBullet" ||
			 monName == "WaterBom")
	{
		monster->attack(NAttack);
		monster->setEaseIn(224, 1.0f);
	}
	else if (monName == "Hasan")
	{
		monster->attack(NAttack);
		monster->setAnchorPoint(Vec2(0.5f, 0.28f));
		monster->setPosition(Vec2(getPositionX() + (isFlip() == true ? -24 : 24), getPositionY()));
		monster->setEaseIn(224, 1.0f);
	}
	else if (monName == "Wave")
	{
		monster->attack(NAttack);
		monster->setAnchorPoint(Vec2(0.5f, 0.1f));
		monster->setPosition(Vec2(getPositionX() + (isFlip() == true ? -24 : 24), getPositionY()));
		monster->setEaseIn(224, 1.0f);
	}
	else if (monName == "InkBird" ||
			 monName == "FakeTobirama" ||
			 monName == "TamaBomb" ||
			 monName == "Shenwei2")
	{
		_monsterArray.push_back(monster);
		monster->attack(NAttack);
	}
	else
	{
		_monsterArray.push_back(monster);
		monster->doAI();
	}

	if (monName == "ItachiSusano")
	{
		monster->setAnchorPoint(Vec2(0.5f, 0));
		monster->setPosition(Vec2(146 / 2 - 10, -40));
		addChild(monster, -1000);
	}
	else if (monName == "SasukeSusano")
	{
		monster->setAnchorPoint(Vec2(0.5f, 0));
		monster->setPosition(Vec2(141 / 2, -6));
		addChild(monster, -1000);
	}
	else if (monName == "CircleMark" ||
			 monName == "Yominuma")
	{
		getGameLayer()->addChild(monster, -5000);
	}
	else
	{
		getGameLayer()->addChild(monster, -monster->getPositionY());
	}
}

void Unit::setMonPer(float dt)
{
	auto monster = Monster::create();

	if (getName() == HeroEnum::Deidara)
	{
		monster->setID("Spider", Role::Mon, _group);
	}
	else if (getName() == HeroEnum::Sai)
	{
		monster->setID("Mouse", Role::Mon, _group);
		setSound("Audio/Sai/ink_mouse.ogg");
	}

	monster->setMaster(this);

	monster->idle();
	monster->setPosition(Vec2(getPositionX() + (isFlip() ? -32 : 32), _originY ? _originY : getPositionY()));
	monster->setFlippedX(isFlip());

	_monsterArray.push_back(monster);
	monster->doAI();

	getGameLayer()->addChild(monster, -monster->getPositionY());
}

void Unit::setTrap(const string &trapName)
{
	if (trapName == "Amaterasu")
	{
		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (getGroup() != hero->getGroup() && hero->isPlayerOrCom() && hero->_state != State::HURT && hero->_state != State::DEAD)
			{
				float distanceX = (hero->getPosition() - getPosition()).x;
				if (distanceX < kAttackRange)
				{
					if (!hero->_isVisable)
					{
						if (hero->getName() == HeroEnum::Konan ||
							hero->getName() == HeroEnum::Deidara)
						{
							hero->unschedule(schedule_selector(Unit::disableBuff));
						}

						hero->setOpacity(255);
						hero->setVisible(true);
						hero->_isVisable = true;

						if (hero->_hpBar)
							hero->_hpBar->setVisible(true);
						if (hero->_shadow)
							hero->_shadow->setVisible(true);
					}
				}
			}
		}

		if (getName() == HeroEnum::ImmortalSasuke)
		{
			Vec2 targetPoint = _mainTarget ? _mainTarget->getPosition() : getPosition();

			for (int z = 0; z < 3; z++)
			{
				if (z == 0)
				{
					auto trap = Bullet::create();
					trap->_master = this;
					trap->setID(trapName, Role::Mon, _group);
					trap->setAnchorPoint(Vec2(0.5, 0));
					trap->setPosition(Vec2(targetPoint.x, targetPoint.y + 32));
					trap->idle();
					trap->attack(NAttack);
					trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 4.0f);
					getGameLayer()->addChild(trap, -trap->getPositionY());
				}
				else if (z == 1)
				{
					for (int i = 0; i < 3; i++)
					{
						auto trap = Bullet::create();
						trap->_master = this;
						trap->setID(trapName, Role::Mon, _group);
						trap->setAnchorPoint(Vec2(0.5, 0));
						trap->setPosition(Vec2(targetPoint.x + (i - 1) * 60, targetPoint.y));
						trap->idle();
						trap->attack(NAttack);
						trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 4.0f);
						getGameLayer()->addChild(trap, -trap->getPositionY());
					}
				}
				else if (z == 2)
				{
					auto trap = Bullet::create();
					trap->_master = this;
					trap->setID(trapName, Role::Mon, _group);
					trap->setAnchorPoint(Vec2(0.5, 0));
					trap->setPosition(Vec2(targetPoint.x, targetPoint.y - 32));
					trap->idle();
					trap->attack(NAttack);
					trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 4.0f);
					getGameLayer()->addChild(trap, -trap->getPositionY());
				}
			}
		}
		else
		{
			for (int z = 0; z < 3; z++)
			{
				if (z == 0)
				{
					for (int i = 0; i < 3; i++)
					{
						auto trap = Bullet::create();
						trap->_master = this;
						trap->setID(trapName, Role::Mon, _group);
						trap->setPosition(Vec2(getPositionX() + (isFlip() ? -112 : 112), getPositionY() + (48 - i * 24)));
						trap->idle();
						trap->attack(NAttack);
						trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 2.5f);
						getGameLayer()->addChild(trap, -trap->getPositionY());
					}
				}
				else if (z == 1)
				{
					for (int i = 0; i < 2; i++)
					{
						auto trap = Bullet::create();
						trap->_master = this;
						trap->setID(trapName, Role::Mon, _group);
						trap->setPosition(Vec2(getPositionX() + (isFlip() ? -80 : 80), getPositionY() + (32 - i * 24)));
						trap->idle();
						trap->attack(NAttack);
						trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 2.5f);
						getGameLayer()->addChild(trap, -trap->getPositionY());
					}
				}
				else
				{
					auto trap = Bullet::create();
					trap->_master = this;
					trap->setID(trapName, Role::Mon, _group);
					trap->setPosition(Vec2(getPositionX() + (isFlip() ? -48 : 48), getPositionY() + 22));
					trap->idle();
					trap->attack(NAttack);
					trap->scheduleOnce(schedule_selector(Bullet::removeSelf), 2.5f);
					getGameLayer()->addChild(trap, -trap->getPositionY());
				}
			}
		}
	}
	else
	{
		onSetTrap(trapName);
	}
}

void Unit::removeSelf(float dt)
{
	dealloc();
}

void Unit::setMonAttack(int skillNum)
{
	for (auto mo : _monsterArray)
	{
		if (mo->getName() != "Traps")
		{
			if (getName() == HeroEnum::Kiba)
			{
				mo->attack(SKILL1);
			}
			else if (getName() == HeroEnum::Kankuro)
			{
				if (mo->getName() == KugutsuEnum::Karasu)
				{
					if (skillNum == 1)
					{
						// mo->attack(SKILL1);
					}
					else if (skillNum == 2)
					{
						mo->attack(SKILL2);
					}
				}
			}
			else if (getName() == HeroEnum::Chiyo)
			{
				if (mo->getName() == KugutsuEnum::Parents)
				{
					if (skillNum == 1 && !mo->_skillChangeBuffValue)
					{
						mo->attack(SKILL1);
					}
					else if (skillNum == 2)
					{
						mo->attack(SKILL2);
					}
				}
			}
			else if (getName() == HeroEnum::Itachi ||
					 getName() == HeroEnum::ImmortalSasuke)
			{
				if (_state == State::NATTACK)
				{
					mo->attack(NAttack);
				}
			}
		}
	}
}

void Unit::setTransform()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "acceptAttack");
	unschedule(schedule_selector(Unit::dehealBuff));

	if (getName() == HeroEnum::Lee ||
		getName() == HeroEnum::RockLee)
	{
		removeBuffEffect("dhBuff");
	}
	else
	{
		if (_skillUPBuffValue)
		{
			unschedule(schedule_selector(Unit::disableBuff));
			disableBuff(0.1f);
		}

		removeBuffEffect("all");
	}

	auto oldNAttackValue = getNAttackValue();
	auto oldMaxHP = getMaxHP();
	auto oldHP = getHP();

	// NOTE: Update HudLayer logic was moved to Hero::setID
	if (getName() == HeroEnum::Naruto)
		setID(HeroEnum::SageNaruto, _role, _group);
	else if (getName() == HeroEnum::SageNaruto)
		setID(HeroEnum::RikudoNaruto, _role, _group);
	else if (getName() == HeroEnum::Jiraiya)
		setID(HeroEnum::SageJiraiya, _role, _group);
	else if (getName() == HeroEnum::Sasuke)
		setID(HeroEnum::ImmortalSasuke, _role, _group);
	else if (getName() == HeroEnum::Lee)
		setID(HeroEnum::RockLee, _role, _group);
	else if (getName() == HeroEnum::RockLee)
		setID(HeroEnum::Lee, _role, _group);
	else if (getName() == HeroEnum::Pain)
		setID(HeroEnum::Nagato, _role, _group);

	setNAttackValue(oldNAttackValue);
	setMaxHPValue(oldMaxHP, false);
	setHPValue(oldHP);

	if (_hpBar)
	{
		_hpBar->setPositionY(getHPBarHeight());
	}

	if (isGearCD)
	{
		_sAttackCD1 -= 5;
		_sAttackCD2 -= 5;
		_sAttackCD3 -= 5;
	}

	if (isPlayer())
		getGameLayer()->setHPLose(getHpPercent());
}

void Unit::attack(ABType type)
{
	if (isPlayer() && type == NAttack)
	{
		if (!getGameLayer()->getSkillFinish() && !_isOnlySkillLocked)
			return;
	}

	switch (type)
	{
	case NAttack:
		_attackValue = getNAttackValue();
		_attackType = _nAttackType;
		_attackRangeX = _nAttackRangeX;
		_attackRangeY = _nAttackRangeY;
		nAttack();
		break;
	case SKILL1:
		if (isPlayer())
		{
			if (_isControlled)
				getGameLayer()->getHudLayer()->skill1Button->click();
		}

		_attackValue = getSAttackValue1();
		_attackType = _sAttackType1;
		_attackRangeX = _sAttackRangeX1;
		_attackRangeY = _sAttackRangeY1;
		sAttack(SKILL1);
		break;
	case SKILL2:
		if (isPlayer())
		{
			if (_isControlled)
				getGameLayer()->getHudLayer()->skill2Button->click();
		}

		_attackValue = getSAttackValue2();
		_attackType = _sAttackType2;
		_attackRangeX = _sAttackRangeX2;
		_attackRangeY = _sAttackRangeY2;
		sAttack(SKILL2);
		break;
	case SKILL3:
		if (isPlayer())
		{
			if (_isControlled)
				getGameLayer()->getHudLayer()->skill3Button->click();
		}

		_attackValue = getSAttackValue3();
		_attackType = _sAttackType3;
		_attackRangeX = _sAttackRangeX3;
		_attackRangeY = _sAttackRangeY3;
		sAttack(SKILL3);
		break;
	case OUGIS1:
		if (isNotPlayer() || _isAI)
		{
			uint32_t ckr = getCKR();
			if (ckr >= 15000)
			{
				ckr -= 15000;
				setCKR(ckr);
			}
			else
			{
				setCKR(0);
			}
			if (ckr < 15000)
			{
				_isCanOugis1 = false;
			}
		}

		_attackValue = getSAttackValue4();
		_attackType = _sAttackType4;
		_attackRangeX = _sAttackRangeX4;
		_attackRangeY = _sAttackRangeY4;
		oAttack(OUGIS1);
		break;
	case OUGIS2:
		if (isNotPlayer() || _isAI)
		{
			uint32_t ckr2 = getCKR2();
			if (ckr2 >= 25000)
			{
				ckr2 -= 25000;
				setCKR2(ckr2);
			}
			else
			{
				setCKR2(0);
			}
			if (ckr2 < 25000)
			{
				_isCanOugis2 = false;
			}
		}

		_attackValue = getSAttackValue5();
		_attackType = _sAttackType5;
		_attackRangeX = _sAttackRangeX5;
		_attackRangeY = _sAttackRangeY5;
		oAttack(OUGIS2);
		break;
	default:
		return;
	}
}

void Unit::nAttack()
{
	if (_state == State::IDLE || _state == State::WALK)
	{
		if (!_isAllAttackLocked || _isOnlySkillLocked)
		{
			if (isPlayer())
			{
				getGameLayer()->setSkillFinish(false);
			}
			if (isNotBullet())
			{
				stopAllActions();
			}
			_state = State::NATTACK;
			runAction(_nAttackAction);
		}
	}
}

void Unit::sAttack(ABType type)
{
	if (_state == State::IDLE || _state == State::WALK || _state == State::NATTACK)
	{
		if (!_isVisable)
		{
			if (getName() == HeroEnum::Konan ||
				getName() == HeroEnum::Deidara)
			{
				unschedule(schedule_selector(Unit::disableBuff));
			}

			setOpacity(255);
			setVisible(true);
			_isVisable = true;

			if (_hpBar)
				_hpBar->setVisible(true);
			if (_shadow)
				_shadow->setVisible(true);
		}

		stopAllActions();

		switch (type)
		{
		case SKILL1:
			if (_isCanSkill1)
			{
				_state = State::SATTACK;
				if (isPlayer())
				{
					getGameLayer()->setSkillFinish(false);
				}
				runAction(_skill1Action);
			}
			_isCanSkill1 = false;

			scheduleOnce(schedule_selector(Unit::enableSkill1), _sAttackCD1);
			break;
		case SKILL2:
			if (_isCanSkill2)
			{
				_state = State::SATTACK;
				if (isPlayer())
				{
					getGameLayer()->setSkillFinish(false);
				}
				runAction(_skill2Action);
			}

			_isCanSkill2 = false;

			scheduleOnce(schedule_selector(Unit::enableSkill2), _sAttackCD2);

			break;
		case SKILL3:
			if (_isCanSkill3)
			{
				_state = State::SATTACK;
				if (isPlayer())
				{
					getGameLayer()->setSkillFinish(false);
				}
				runAction(_skill3Action);
			}
			_isCanSkill3 = false;

			scheduleOnce(schedule_selector(Unit::enableSkill3), _sAttackCD3);
			break;
		default:
			break;
		}
	}
}

void Unit::oAttack(ABType type)
{
	if (_state == State::IDLE || _state == State::WALK || _state == State::NATTACK)
	{
		if (isPlayer())
		{
			getGameLayer()->setSkillFinish(false);
		}
		if (!_isVisable)
		{
			if (getName() == HeroEnum::Konan ||
				getName() == HeroEnum::Deidara)
			{
				unschedule(schedule_selector(Unit::disableBuff));
			}

			setOpacity(255);
			setVisible(true);
			_isVisable = true;

			if (_hpBar)
				_hpBar->setVisible(true);
			if (_shadow)
				_shadow->setVisible(true);
		}

		stopAllActions();
		switch (type)
		{
		case OUGIS1:
			_state = State::OATTACK;
			runAction(_skill4Action);
			break;
		case OUGIS2:
			_state = State::O2ATTACK;
			runAction(_skill5Action);
			break;
		default:
			break;
		}
	}
}

bool Unit::checkHasMovement()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	// DRIVEND BY JOYSTICK
	return false;
#else
	return getGameLayer()->checkHasAnyMovement();
#endif
}

void Unit::idle()
{
	if (_state != State::IDLE && _state != State::DEAD)
	{
		_state = State::IDLE;
		stopAllActions();
		_backY = 0;
		_hurtFromLeft = false;
		_hurtFromRight = false;
		_isHitOne = false;
		_isCatchOne = false;
		_isSticking = false;
		_knockLength = 0;
		_originY = 0;
		_sticker = nullptr;
		_knockDirection = false;

		unschedule(schedule_selector(Unit::stopMove));

		bool _isPlayer = isPlayer();

		if (_isPlayer)
		{
			if (!_isAllAttackLocked && !_isOnlySkillLocked)
			{
				getGameLayer()->setSkillFinish(true);
			}
		}

		if (!getGameLayer()->_isAttackButtonRelease &&
			_isPlayer &&
			!_attackType.empty() &&
			!_isAllAttackLocked)
		{
			getGameLayer()->setSkillFinish(true);
			attack(NAttack);
		}
		else
		{
			if (_isPlayer && checkHasMovement())
				return;

			runAction(_idleAction);
		}
	}
}

void Unit::walk(Vec2 direction)
{
	if (_state == State::IDLE || _state == State::WALK || (_state == State::NATTACK && isNotPlayer()))
	{
		isHurtingTower = false;

		if (_state == State::NATTACK &&
			_isOnlySkillLocked &&
			(getName() == HeroEnum::Suigetsu ||
			 getName() == HeroEnum::Jugo ||
			 getName() == HeroEnum::Hiruzen ||
			 getName() == HeroEnum::Kisame))
		{
			if (isNotPlayer())
			{
				return;
			}
		}
		else if (_state == State::IDLE || _state == State::NATTACK)
		{
			stopAllActions();
			runAction(_walkAction);
		}

		_state = State::WALK;

		// NOTE: FIXED when direction.x is zero but still set to flipped
		if (direction.x != 0)
		{
			auto isFlip = direction.x > 0 ? false : true;
			setFlippedX(isFlip);
			if (_healBuffEffect)
				_healBuffEffect->setFlippedX(isFlip);
		}

		if (getName() == HeroEnum::Itachi ||
			getName() == HeroEnum::ImmortalSasuke ||
			getName() == HeroEnum::Chiyo)
		{
			for (auto mo : _monsterArray)
			{
				if (mo->getName() == "ItachiSusano" ||
					mo->getName() == "SasukeSusano")
				{
					mo->setFlippedX(isFlip());
				}
				else if (mo->getName() == KugutsuEnum::Parents)
				{
					if (mo->_state == State::IDLE)
					{
						mo->setFlippedX(isFlip());
					}
				}
			}
		}

		_velocity = Vec2(direction.x * _walkSpeed * kSpeedBase, direction.y * _walkSpeed * kSpeedBase);
	}
}

bool Unit::hurt()
{
	if (_state != State::SATTACK &&
		_state != State::JUMP &&
		_state != State::OATTACK &&
		_state != State::O2ATTACK &&
		_state != State::FLOAT &&
		_state != State::DEAD &&
		_state != State::KNOCKDOWN &&
		_state != State::AIRHURT &&
		!_isSticking &&
		!_isCatchOne &&
		!_isArmored)
	{
		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (getGroup() == hero->getGroup() &&
				hero->getName() == HeroEnum::Chiyo &&
				hero->_state != State::DEAD &&
				hero->_buffStartTime)
			{
				Vec2 sp = hero->getPosition() - getPosition();
				if (abs(sp.x) <= kAttackRange)
				{
					return false;
				}
			}
		}
		if (getName() == HeroEnum::Chiyo)
		{
			for (auto mo : _monsterArray)
			{
				if (mo->getName() == KugutsuEnum::Parents && !mo->_skillChangeBuffValue && mo->_state != State::SATTACK && mo->_state != State::DEAD)
				{
					Vec2 sp = mo->getPosition() - getPosition();
					if (sp.x <= 48)
					{
						return false;
					}
				}
			}
		}

		if (isPlayer())
		{
			getGameLayer()->setSkillFinish(false);
		}

		_state = State::HURT;
		stopAllActions();
		if (_hurtAction)
		{
			auto call = CallFunc::create(std::bind(&Unit::idle, this));
			auto seq = newSequence(_hurtAction, call);
			runAction(seq);
		}
		return true;
	}
	return false;
}

bool Unit::hardHurt(int delayTime, bool isHurtAction, bool isCatch, bool isStick, bool isStun)
{
	if ((_state != State::JUMP || isStick) &&
		_state != State::O2ATTACK &&
		(_state != State::FLOAT || isStick) &&
		_state != State::DEAD &&
		(_state != State::KNOCKDOWN || isStick) &&
		_state != State::AIRHURT &&
		!_isSticking &&
		!_isCatchOne &&
		!_isArmored)
	{
		if (_state == State::FLOAT ||
			_state == State::AIRHURT ||
			_state == State::JUMP)
		{
			setPositionY(_originY);
			_originY = 0;
			getGameLayer()->reorderChild(this, -getPositionY());
		}

		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (getGroup() == hero->getGroup() &&
				hero->getName() == HeroEnum::Chiyo &&
				hero->_state != State::DEAD &&
				hero->_buffStartTime)
			{
				Vec2 sp = hero->getPosition() - getPosition();
				if (abs(sp.x) <= kAttackRange)
				{
					return false;
				}
			}
		}

		if (getName() == HeroEnum::Chiyo)
		{
			for (auto mo : _monsterArray)
			{
				if (mo->getName() == KugutsuEnum::Parents && !mo->_skillChangeBuffValue && mo->_state != State::SATTACK && mo->_state != State::DEAD)
				{
					Vec2 sp = mo->getPosition() - getPosition();
					if (sp.x <= 48)
					{
						if (mo->_isCanSkill3)
						{
							mo->attack(SKILL3);
						}
						return false;
					}
				}
			}
		}

		if (isPlayer())
		{
			getGameLayer()->setSkillFinish(false);
		}
		if (isStick)
		{
			_sticker = _slayer;
		}

		if (isCatch)
		{
			setVisible(false);
			_isVisable = false;

			if (_shadow)
			{
				_shadow->setVisible(false);
			}
		}

		_state = State::HURT;
		stopAllActions();

		Vector<FiniteTimeAction *> list;
		if (isHurtAction)
		{
			list.pushBack(_hurtAction);
		}
		else
		{
			_isSticking = true;
			string path = getName();
			if (isStick && isStun) // TODO: Use HardHurtState::CatchAir instead
				path += "_AirHurt_02";
			else
				path += "_Hurt_02";

			auto frame = getSpriteFrame(path);
			if (frame == nullptr)
			{
				// Try use xxx_AirHurt_01 instead of xxx_AirHurt_02
				path = getName() + "_AirHurt_01";
				frame = getSpriteFrame(path);

				if (frame == nullptr)
					CCMessageBox(path.c_str(), "Not found hard hurt frame");
			}

			Vector<SpriteFrame *> spriteFrames;
			spriteFrames.pushBack(frame);
			auto tempAnimation = Animation::createWithSpriteFrames(spriteFrames, 0.1f);
			auto tempAction = Animate::create(tempAnimation);
			list.pushBack(tempAction);
		}

		if (isStun)
		{
			auto call = CallFunc::create(std::bind(&Unit::setSkillEffect, this, "stun"));
			list.pushBack(call);
		}

		auto delay = DelayTime::create(delayTime / 1000.0f);
		list.pushBack(delay);

		auto call = CallFunc::create(std::bind(&Unit::idle, this));
		list.pushBack(call);

		auto seq = Sequence::create(list);
		runAction(seq);

		return true;
	}

	return false;
}

void Unit::airHurt()
{
	if (_state == State::FLOAT || _state == State::AIRHURT)
	{
		if (isPlayer())
		{
			getGameLayer()->setSkillFinish(false);
		}

		if (_state == State::AIRHURT)
		{
			getActionManager()->removeAction(_airHurtAction);
			unschedule(schedule_selector(Unit::resumePauseStuff));
		}
		_state = State::AIRHURT;
		runAction(_airHurtAction);
		getActionManager()->pauseTarget(this);
		scheduleOnce(schedule_selector(Unit::resumePauseStuff), 0.2f);
	}
}

void Unit::resumePauseStuff(float dt)
{
	getActionManager()->resumeTarget(this);
}

void Unit::absorb(Vec2 position, bool isImmediate)
{
	if (_state == State::IDLE ||
		_state == State::WALK ||
		_state == State::NATTACK)
	{
		if (_isArmored || _isSticking)
			return;

		if (isPlayer())
		{
			getGameLayer()->setSkillFinish(false);
		}
		_state = State::HURT;

		Vector<FiniteTimeAction *> list;
		if (isImmediate)
		{
			stopAllActions();
			auto mv = MoveTo::create(0.2f, position);
			list.pushBack(_hurtAction);
			runAction(mv);
		}
		else
		{
			Vec2 direction = getPosition() - position;
			position.x = direction.x > 0 ? getPositionX() - 16 : getPositionX() + 16;
			position.y = direction.y > 0 ? getPositionY() - 8 : getPositionY() + 8;
			auto mv = MoveTo::create(0.2f, position);
			list.pushBack(mv);
		}

		auto call = CallFunc::create(std::bind(&Unit::idle, this));
		list.pushBack(call);
		auto seq = Sequence::create(list);
		runAction(seq);
	}
}

void Unit::floatUP(float floatHeight, bool isCancelSkill)
{
	if (_state == State::SATTACK && !isCancelSkill)
	{
		return;
	}

	if (_state != State::JUMP &&
		_state != State::FLOAT &&
		_state != State::O2ATTACK &&
		_state != State::OATTACK &&
		_state != State::AIRHURT &&
		_state != State::DEAD &&
		!_isSticking &&
		!_isCatchOne &&
		!_isArmored)
	{
		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (getGroup() == hero->getGroup() &&
				hero->getName() == HeroEnum::Chiyo &&
				hero->_state != State::DEAD &&
				hero->_buffStartTime)
			{
				Vec2 sp = hero->getPosition() - getPosition();
				if (abs(sp.x) <= kAttackRange)
				{
					return;
				}
			}
		}

		if (getName() == HeroEnum::Chiyo)
		{
			for (auto mo : _monsterArray)
			{
				if (mo->getName() == KugutsuEnum::Parents && !mo->_skillChangeBuffValue && mo->_state != State::SATTACK && mo->_state != State::DEAD)
				{
					Vec2 sp = mo->getPosition() - getPosition();
					if (sp.x <= 48)
					{
						if (mo->_isCanSkill3)
						{
							mo->attack(SKILL3);
						}
						return;
					}
				}
			}
		}

		if (isPlayer())
		{
			getGameLayer()->setSkillFinish(false);
		}
		_state = State::FLOAT;
		stopAllActions();

		float posX = getPositionX();
		float posY = getPositionY();
		_originY = posY;
		ActionInterval *_floatAwayAction;

		if (floatHeight == 64)
			_floatAwayAction = JumpTo::create(0.8f, Vec2(posX + (isFlip() ? 64 : -64), posY), 64, 1);
		else if (floatHeight == 128)
			_floatAwayAction = JumpTo::create(1.0f, Vec2(posX + (isFlip() ? 128 : -128), posY), 64, 1);
		else
			_floatAwayAction = JumpTo::create(0.3f, Vec2(posX + (isFlip() ? 8 : -8), posY), 16, 1);

		auto call = CallFunc::create(std::bind(&Unit::knockdown, this));
		_floatUPAction = newSequence(_floatAwayAction, call);

		runAction(_floatUPAction);
		runAction(_floatAction);
	}
}

void Unit::knockdown()
{
	if (_state != State::KNOCKDOWN && _state != State::DEAD)
	{
		_state = State::KNOCKDOWN;
		stopAllActions();

		runAction(_knockdownAction);
	}
}

void Unit::dead()
{
	getGameModeHandler()->onCharacterDead(this);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "acceptAttack");

	_isHitOne = false;
	_isCatchOne = false;
	_isSticking = false;
	_isInvincible = false;
	_startPoint = Vec2(0, 0);
	_markPoint = Vec2(0, 0);

	_sticker = nullptr;

	setWalkSpeed(224);
	_originSpeed = 224;

	unscheduleUpdate();

	if (_isControlled)
	{
		_isControlled = false;
		if (_controller->isPlayer())
		{
			if (_controller->getName() == HeroEnum::Ino)
			{
				_isAI = true;
				_isControlled = false;
				doAI();

				getGameLayer()->currentPlayer = _controller;
				getGameLayer()->getHudLayer()->updateSkillButtons();
			}

			getGameLayer()->controlChar = nullptr;
		}

		changeGroup();

		if (isPlayer())
		{
			_isAI = false;
			getGameLayer()->getHudLayer()->_isAllButtonLocked = false;
		}

		if (_controller->_state != State::DEAD)
		{
			_controller->unschedule(schedule_selector(Unit::resumeAction));
			_controller->idle();
			_controller->_isArmored = false;
		}

		_controller = nullptr;
	}

	if (getName() == HeroEnum::Minato || getName() == HeroEnum::Nagato)
	{
		setActionResume2();
	}
	else
	{
		setActionResume();
	}

	removeLostBlood(0.1f);
	unschedule(schedule_selector(Unit::stopMove));
	unschedule(schedule_selector(Unit::setAI));
	unschedule(schedule_selector(Unit::disableHpBar));

	if (isPlayer())
	{
		getGameLayer()->setSkillFinish(false);
		getGameLayer()->getHudLayer()->hpLabel->setString("0");
		getGameLayer()->getHudLayer()->status_hpbar->setOpacity(0);
	}

	// kill all buffEffect
	if (isPlayerOrCom())
	{
		unschedule(schedule_selector(Unit::healBuff));
		_buffStartTime = 0;
		unschedule(schedule_selector(Unit::dehealBuff));

		if (getName() != HeroEnum::RockLee &&
			getName() != HeroEnum::Lee)
		{
			removeBuffEffect("all");
		}
		else
		{
			removeBuffEffect("dhBuff");
		}

		if (_isSuicide)
		{
			_isSuicide = false;
			rebornLabelTime = 3;
		}
		else
		{
			rebornLabelTime = 0;
			_deadNum++;

			if (isPlayer())
			{
				auto deadStr = getGameLayer()->getHudLayer()->deadLabel->getString();
				int deads = to_int(deadStr) + 1;
				getGameLayer()->getHudLayer()->deadLabel->setString(to_cstr(deads));
			}
		}

		if (!_isVisable)
		{
			setOpacity(255);
			setVisible(true);
			_isVisable = true;

			if (_hpBar)
				_hpBar->setVisible(true);
			if (_shadow)
				_shadow->setVisible(true);
		}
	}

	if (_hpBar)
	{
		_hpBar->removeFromParent();
		_hpBar = nullptr;
	}

	if (hearts < 1)
	{
		hearts += 1;
	}

	if (_state == State::FLOAT || _state == State::AIRHURT)
	{
		_state = State::DEAD;
		unschedule(schedule_selector(Unit::removeClone));
		schedule(schedule_selector(Unit::checkActionFinish), 0.0f);
		return;
	}
	else if (_state == State::JUMP)
	{
		setPositionY(_originY);
		_originY = 0;
		getGameLayer()->reorderChild(this, -getPositionY());
	}

	stopAllActions();
	_state = State::DEAD;

	if (isPlayerOrCom())
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", this);
	}

	if (isNotClone() && isNotSummon())
	{
		auto call = CallFunc::create(std::bind(&Unit::dealloc, this));

		if (isFlog())
		{
			auto fadeOut = FadeOut::create(0.5f);
			auto seq = newSequence(_deadAction, fadeOut, call);
			runAction(seq);
		}
		else
		{
			auto seq = newSequence(_deadAction, call);
			runAction(seq);
		}
	}
	else
	{
		unschedule(schedule_selector(Unit::removeClone));
		setSkillEffect("smk");
		dealloc();
	}
}

void Unit::checkActionFinish(float dt)
{
	if (getActionManager()->getNumberOfRunningActionsInTarget(this) == 0)
	{
		unschedule(schedule_selector(Unit::checkActionFinish));
		stopAllActions();

		Vector<FiniteTimeAction *> list;
		auto fadeOut = FadeOut::create(0.5f);
		auto call = CallFunc::create(std::bind(&Unit::dealloc, this));
		if (_deadAction)
		{
			list.pushBack(_deadAction);
		}
		if (isFlog())
		{
			list.pushBack(fadeOut);
		}
		list.pushBack(call);
		auto seq = Sequence::create(list);
		runAction(seq);
	}
}

void Unit::dealloc()
{
}

void Unit::reborn(float dt)
{
	getGameModeHandler()->onCharacterReborn(this);
}

void Unit::setAI(float dt)
{
}

void Unit::doAI()
{
	_isAI = true;
	schedule(schedule_selector(Unit::setAI), 0.1f);
}

void Unit::changeSide(Vec2 sp)
{
	if (sp.x > 0)
		setFlippedX(false);
	else
		setFlippedX(true);

	if (getName() == HeroEnum::Itachi || getName() == HeroEnum::ImmortalSasuke)
	{
		for (auto mo : _monsterArray)
		{
			mo->setFlippedX(isFlip());
		}
	}
}

void Unit::changeGroup()
{
	if (isKonohaGroup())
		setGroup(Group::Akatsuki);
	else
		setGroup(Group::Konoha);

	if (_hpBar && isNotPlayer())
	{
		if (getGroup() != getGameLayer()->currentPlayer->getGroup())
		{
			_hpBar->changeBar("hp_bar_r.png");
		}
		else if (isCom())
		{
			_hpBar->changeBar("hp_bar_b.png");
		}
	}

	if (isPlayer())
	{
		changeGroupBy(getGameLayer()->_CharacterArray);
		changeGroupBy(getGameLayer()->_TowerArray);
		changeGroupBy(getGameLayer()->_AkatsukiFlogArray);
		changeGroupBy(getGameLayer()->_KonohaFlogArray);
	}
}

template <typename T>
typename std::enable_if_t<std::is_base_of_v<Unit, T>, void>
Unit::changeGroupBy(const vector<T *> &list)
{
	for (auto target : list)
	{
		if (target->_hpBar == nullptr)
			continue;
		if (_group != target->_group)
		{
			if (target->isFlog())
				target->_hpBar->changeBar("flog_bar_r.png");
			else
				target->_hpBar->changeBar("hp_bar_r.png");
		}
		else
		{
			if (target->isFlog())
				target->_hpBar->changeBar("flog_bar.png");
			else if (target->isTower())
				target->_hpBar->changeBar("hp_bar.png");
			else if (target->isNotPlayer())
				target->_hpBar->changeBar("hp_bar_b.png");
		}
	}
}

void Unit::autoFlip(Unit *attacker)
{
	if (isFlip() == attacker->isFlip())
	{
		if (isFlip())
			setFlippedX(false);
		else
			setFlippedX(true);
	}
}

void Unit::enableItem1(float dt)
{
	_isCanItem1 = true;
}

void Unit::enableSkill1(float dt)
{
	_isCanSkill1 = true;
}

void Unit::enableSkill2(float dt)
{
	_isCanSkill2 = true;
}

void Unit::enableSkill3(float dt)
{
	_isCanSkill3 = true;
}

/**
 * Utilities
 */

void Unit::increaseAllCkrs(uint32_t value, bool enableLv2, bool enableLv4)
{
	if (_level >= 2 && enableLv2)
	{
		uint32_t ckr = MIN(getCKR() + value, 45000);
		setCKR(ckr);

		if (ckr >= 15000)
			_isCanOugis1 = true;

		if (isPlayer())
			getGameLayer()->setCKRLose(false);
	}

	if (_level >= 4 && enableLv4)
	{
		uint32_t ckr2 = MIN(getCKR2() + value, 50000);
		setCKR2(ckr2);

		if (ckr2 >= 25000)
			_isCanOugis2 = true;

		if (isPlayer())
			getGameLayer()->setCKRLose(true);
	}
}

void Unit::increaseHpAndUpdateUI(uint32_t value)
{
	setHPValue(MIN(getHP() + value, getMaxHP()));
}

void Unit::updateHpBar()
{
	if (_hpBar)
		_hpBar->loseHP(getHpPercent());
}

#include "Core/Core/UnitImpl.h"
