#pragma once
#include "Data/UnitData.h"
#include "Effect.h"
#include "GameLayer.h"
#include "HudLayer.h"
#include "MyUtils/KTools.h"

enum class State {
	DEAD,
	IDLE,
	WALK,
	NATTACK,
	SATTACK,	// Skills
	OATTACK,	// Ougi 1
	O2ATTACK,	// Ougi 2
	HURT,
	KNOCKDOWN,
	FLOAT,
	JUMP,
	AIRHURT
};

class HPBar;
class Hero;

class CharacterBase : public Sprite
{
friend class CommandSystem;

public:
	CharacterBase();

	virtual void		setID(const string &name, Role role, Group group);
	virtual void		setHPbar();
	virtual void		changeHPbar();
	virtual void		setShadows();

	PROP_String(_name, Name);
	PPROP(Role, _role, Role);
	PPROP(Group, _group, Group);
	VPROP(int, _charId, CharId);

	uint32_t			_deadNum;
	uint32_t			_flogNum;
	PROP_UInt(_killNum, KillNum);
	PROP_UInt(_coin, Coin);


	CharacterBase*		_slayer;
	CharacterBase*		_sticker;
	CharacterBase*		_mainTarget;

	bool				isHurtingTower;

	bool				_isFlipped;
	bool				_isHitOne;
	bool				_isCatchOne;
	bool				_isHealing;
	bool				_isVisable;

	// buff
	uint32_t			_healBuffValue;
	uint32_t			_dehealBuffValue;
	uint32_t			_powerUPBuffValue;
	uint32_t			_skillUPBuffValue;
	uint32_t			_skillChangeBuffValue;


	Sprite*				_heartEffect;
	Effect*				_healBuffEffect;
	Effect*				_powerBuffEffect;
	Effect*				_skillBuffEffect;
	Sprite*				_dehealBuffEffect;
	Effect*				_healItemEffect;
	Effect*				_speedItemEffect;
	float				_buffStartTime;
	float				_debuffStartTime;
	VPROP(int,_knockLength, KnockLength);
	VPROP(bool,_knockDirection, KnockDirection);

	bool				_isAllAttackLocked;
	bool				_isOnlySkillLocked;
	bool				_isInvincible;
	bool				_isTaunt;
	// Armor : 霸体
	bool				_isArmored;
	bool				_isSuicide;

	bool				_isSticking;
	bool				_isPausing;

	Vec2				_markPoint;
	Vec2				_startPoint; // NOTE: Only for Minano

	bool				_isAI;
	bool				_isControlled;

	CC_SYNTHESIZE_RETAIN(CCLabelTTF*,cpLabel,CPLabel);
	PROP_Vector(vector<GearType>,_gearArray,GearArray);

	bool				enableDead	 = true;
	bool				enableReborn = true;
	int					changeCharId = -1; // NOTE: Support for random deathmatch mode

	int					rebornLabelTime;
	int					battleCondiction;
	// True is only has one tower, false otherwise
	bool				isBaseDanger;


	HPBar*				_hpBar;
	Sprite*				_shadow;
	float				_originY;
	float				_backY;
	float				_diretionY;

	int					lbAttackerId = -1;
	uint32_t			lostBloodValue;
	int					gearCKRValue;
	uint32_t			gearRecoverValue;

	// 忍び：Kakuzu ability
	uint32_t			hearts;
	// gear02 ability
	bool				isAttackGainCKR;
	// 口寄せ：Bikyu ability
	// 忍び：Guardian & Naruto-Rikutou & Naruto-Sage ability
	bool				hasArmorBroken;
	// Gear ability
	bool				hasArmor;
	bool				isGearCD;

	bool				_isCanGear00;
	bool				_isCanGear03;
	bool				_isCanGear06;

	VPROP(int,_walkSpeed,WalkSpeed);
	int					_originSpeed;

	PROP_UInt(_hp,HP);
	PROP_UInt(_maxHP,MaxHP);
	PROP_UInt(_ckr,CKR);
	PROP_UInt(_ckr2,CKR2);
	VPROP(float,_gardValue,GP);
	VPROP(float,_exp,EXP);
	VPROP(uint32_t,_level,LV);
	VPROP(int,_height,Height);
	VPROP(int,_rebornTime,RebornTime);
	VPROP(Vec2,_spawnPoint,SpawnPoint);


	CC_SYNTHESIZE(CharacterBase*,_master,Master);
	CC_SYNTHESIZE(CharacterBase*,_controller,Controller);
	CC_SYNTHESIZE(CharacterBase*,_secmaster,SecMaster);

	PROP_REF(string,_attackType,AttackType);
	uint32_t		_attackValue;
	int				_attackRangeX;
	int				_attackRangeY;

	// int totalCombatPoint;
	int				enemyCombatPoint;
	int				friendCombatPoint;

	PROP_UInt(_nAttackValue,NAttackValue);
	PROP_REF(string,_nAttackType,NAttackType);
	int				_nAttackRangeX;
	int				_nAttackRangeY;

	PROP_UInt(_sAttackValue1,SAttackValue1);
	PROP_REF(string,_sAttackType1,SAttackType1);
	int				_sAttackRangeX1;
	int				_sAttackRangeY1;
	uint32_t		_sAttackCD1;
	bool			_sAttack1isDouble;
	int				_sAttackCombatPoint1;

	PROP_UInt(_sAttackValue2,SAttackValue2);
	PROP_REF(string,_sAttackType2,SAttackType2);
	int				_sAttackRangeX2;
	int				_sAttackRangeY2;
	uint32_t		_sAttackCD2;
	bool			_sAttack2isDouble;
	int				_sAttackCombatPoint2;

	PROP_UInt(_sAttackValue3,SAttackValue3);
	PROP_REF(string,_sAttackType3,SAttackType3);
	int				_sAttackRangeX3;
	int				_sAttackRangeY3;
	uint32_t		_sAttackCD3;
	bool			_sAttack3isDouble;
	int				_sAttackCombatPoint3;

	PROP_UInt(_sAttackValue4,SAttackValue4);
	PROP_REF(string,_sAttackType4,SAttackType4);
	int				_sAttackRangeX4;
	int				_sAttackRangeY4;
	uint32_t		_sAttackCD4;
	bool			_sAttack4isDouble;
	int				_sAttackCombatPoint4;

	PROP_UInt(_sAttackValue5,SAttackValue5);
	PROP_REF(string,_sAttackType5,SAttackType5);
	int				_sAttackRangeX5;
	int				_sAttackRangeY5;
	uint32_t		_sAttackCD5;
	int				_sAttackCombatPoint5;

	PROP_UInt(_spcAttackValue1,SpcAttackValue1);
	PROP_REF(string,_spcAttackType1,SpcAttack1Type);
	int				_spcAttackRangeX1;
	int				_spcAttackRangeY1;
	uint32_t		_spcAttackCD1;

	PROP_UInt(_spcAttackValue2,SpcAttackValue2);
	PROP_REF(string,_spcAttackType2,SpcAttack2Type);
	int				_spcAttackRangeX2;
	int				_spcAttackRangeY2;
	uint32_t		_spcAttackCD2;

	PROP_UInt(_spcAttackValue3,SpcAttackValue3);
	PROP_REF(string,_spcAttackType3,SpcAttack3Type);
	int				_spcAttackRangeX3;
	int				_spcAttackRangeY3;
	uint32_t		_spcAttackCD3;

	PROP_UInt(_tempAttackValue1,TempAttackValue1);


	PROP_REF(string,_effectType,EffectType);
	bool			_hurtFromLeft;
	bool			_hurtFromRight;

	vector<CCLabelBMFont *>	_damageArray;
	uint32_t				damageEffectCount;
	PROP_Vector(vector<CharacterBase *>,_monsterArray,MonsterArray);

	// movement
	PROP(Vec2,_velocity, Velocity);
	PROP(Vec2,_desiredPosition, DesiredPosition);

	VPROP(State,_actionState, ActionState);

	// actions
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_idleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_nAttackAction, NAttackAction);
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_walkAction, WalkAction);
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_hurtAction, HurtAction);
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_knockDownAction, KnockDownAction);
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_airHurtAction, AirHurtAction);
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_floatAction, FloatAction);
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_deadAction, DeadAction); 

	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_skill1Action, Skill1Action);
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_skill2Action, Skill2Action);
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_skill3Action, Skill3Action);
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_skill4Action, Skill4Action);
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_skill5Action, Skill5Action);

	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_moveAction, MoveAction);
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_floatUPAction, FloatUPAction);
	CC_SYNTHESIZE_RETAIN(FiniteTimeAction*,_jumpUPAction, JumpUPAction);


	void				update(float dt);
	void				updateHpBarPosition(float dt);
	void				acceptAttack(Ref* object);

	float				getHpPercent();

	bool				checkHasMovement();

	void				idle();
	void				walk(Vec2 direction);
	void				attack(abType type);
	void				sAttack(abType type);
	void				nAttack();
	void				oAttack(abType type);
	bool				hurt();
	bool				hardHurt(int delayTime, bool isHurtAction, bool isCatch, bool isStick, bool isStun);
	// bool				hardHurt(int delayTime, bool isHurtAction, HardHurtState state);
	void				absorb(Vec2 position, bool isImmediate);
	void				jump(){}; // No reference
	void				knockDown();
	virtual void		dead();
	void				floatUP(float floatHeight, bool isCancelSkill);
	void				airHurt();

	virtual void		doAI();


	virtual void		changeAction();
	void				changeAction2();
	void				changeGroup();
private:
	template <typename T>
	typename std::enable_if<std::is_base_of<CharacterBase, T>::value, void>::type changeGroupBy(const vector<T *> &list);
public:
	virtual void		resumeAction(float dt);
	virtual void		setActionResume();
	void				setActionResume2();
	void				reCatched(float dt);

	void				setShadow(SpriteFrame *frame);
	void				enableShadow(Sprite *charN);
	void				disableShadow(Sprite *charN);

	void				setItem(abType type);
	void				disableEffect();
	void				disableHpBar(float dt);

	void				disableShack();
	void				disableDebuff(float dt);

	void				enableSkill1(float dt);
	void				enableSkill2(float dt);
	void				enableSkill3(float dt);
	void				enableItem1(float dt);

	void				enableGear00(float dt);
	void				enableGear03(float dt);
	void				enableGear06(float dt);

	void				disableGear1(float dt);
	void				disableGear2(float dt);
	void				disableGear3(float dt);

	bool				setGear(GearType type);
	void				useGear(GearType type);

	void				setCoinDisplay(int num);
	void				removeCoinDisplay(Sprite *coinDisplay);
	void				addCoin(uint32_t num);
	void				minusCoin(uint32_t num);

	bool				_isCanSkill1;
	bool				_isCanSkill2;
	bool				_isCanSkill3;
	bool				_isCanItem1;
	bool				_isCanOugis1;
	bool				_isCanOugis2;

	CCArray*			idleArray;
	CCArray*			walkArray;
	CCArray*			hurtArray;
	CCArray*			airHurtArray;
	CCArray*			knockDownArray;
	CCArray*			floatArray;
	CCArray*			deadArray;
	CCArray*			nattackArray;
	CCArray*			skill1Array;
	CCArray*			skill2Array;
	CCArray*			skill3Array;
	CCArray*			skill4Array;
	CCArray*			skill5Array;

	CCArray*			skillSPC1Array;
	CCArray*			skillSPC2Array;
	CCArray*			skillSPC3Array;
	CCArray*			skillSPC4Array;
	CCArray*			skillSPC5Array;


	virtual void		dealloc();
	virtual void		reborn(float dt);


	void				resumePauseStuff(float dt);

	void				lostBlood(float dt);
	void				removeLostBlood(float dt);

	virtual void		setAI(float dt);
	virtual void		setRestore2(float dt);


	void				readData(CCArray* tmpData, string &attackType, uint32_t &attackValue, int &attackRangeX, int &attackRangeY, uint32_t &cooldown, int &combatPoint);
	FiniteTimeAction*	createAnimation(CCArray* ationArray, float fps, bool isRepeat, bool isReturn);

	void				setSound(const string &file);
	void				setDSound(const string &file);
	void				setMove(int moveLength);
	void				setCharge(int moveLength);
	void				setChargeB(int moveLength);
	void				getCollider();
	void				getSticker(float dt);
	void				stopMove(float dt);
	void				stopJump(int stopTime);
	void				setCharFlip();
	void				setAttackBox(const string &effectType);
	inline void			setDamage(CharacterBase* attacker);
	void				setDamage(CharacterBase *attacker, const string &effectType, int attackValue, bool isFlipped);
	void				setDamgeDisplay(int value, const char* font);

	void				setSkillEffect(const string &type);
	// void				setItemEffect(const string &type);
	void				setDamgeEffect(const string &type);
	void				setMonAttack(int skillNum);
	void				setTransform();
	void				setOugis();

	virtual Hero*		createClone(int cloneTime);
	void				setClone(int cloneTime);
	void				setMon(const string &monName);
	void				setMonPer(float dt);
	void				setBullet(const string &bulletName);
	void				setBulletGroup(float dt);
	void				setTrap(const string &trapName);

	void				removeAllClones();

	void				setBuff(int buffValue);
	void				setCommand(const string &cmd);
	void				setBuffEffect(const string &type);
	void				removeBuffEffect(const string &type);

	void				disableBuff(float dt);
	void				healBuff(float dt);
	void				dehealBuff(float dt);

protected:
	void				removeClone(float dt);
	void				removeSelf(float dt);
	void				setJump(bool jumpDirection);

	Rect				setHalfBox();
	Rect				setHitBox();

	void				checkActionFinish(float dt);

	void				setRestore(float dt);


	bool				findEnemy(Role role, int searchRange, bool masterRange = false);
	bool				findEnemy2(Role role);
	bool				findTargetEnemy(Role role, bool isTowerDected);
	template <typename T>
	typename std::enable_if<std::is_base_of<CharacterBase, T>::value, bool>::type findEnemyBy(const vector<T *> &list, int searchRange, bool masterRange = false);
	template <typename T>
	typename std::enable_if<std::is_base_of<CharacterBase, T>::value, bool>::type findEnemy2By(const vector<T *> &list);
	template <typename T>
	typename std::enable_if<std::is_base_of<CharacterBase, T>::value, bool>::type findTargetEnemyBy(const vector<T *> &list, bool isTowerDected);
	bool				checkBase();

	bool				stepBack();
	bool				stepBack2();
	bool				checkRetri();
	void				stepOn();
	void				changeSide(Vec2 sp);

	inline void			autoFlip(CharacterBase* attacker);

	void				removeDamageDisplay();

public:
	inline bool			hasTempAttackValue1() { return getTempAttackValue1() > 0; }
	// UI
	void 				updateHpBar();
	void				updateDataByLVOnly();
	inline void			lockSkill4Button() {
		if (isPlayer())
			getGameLayer()->getHudLayer()->skill4Button->setLock();
	}
	inline void			unlockSkill4Button() {
		if (isPlayer())
			getGameLayer()->getHudLayer()->skill4Button->unLock();
	}
	inline void			lockSkill5Button() {
		if (isPlayer())
			getGameLayer()->getHudLayer()->skill5Button->setLock();
	}
	inline void			unlockSkill5Button() {
		if (isPlayer())
			getGameLayer()->getHudLayer()->skill5Button->unLock();
	}
	inline void			lockOugisButtons() {
		if (isPlayer()) {
			getGameLayer()->getHudLayer()->skill4Button->setLock();
			getGameLayer()->getHudLayer()->skill5Button->setLock();
		}
	}
	inline void			unlockOugisButtons() {
		if (isPlayer()) {
			getGameLayer()->getHudLayer()->skill4Button->unLock();
			getGameLayer()->getHudLayer()->skill5Button->unLock();
		}
	}
	// character extensions
	inline void			setHPValue(uint32_t var, bool isUpdateHpBar = true) {
		setHP(var);
		if (isUpdateHpBar)
			updateHpBar();
	}
	inline void			setMaxHPValue(uint32_t var, bool isUpdateHpBar = true) {
		setMaxHP(var);
		if (isUpdateHpBar)
			updateHpBar();
	}
	inline bool			isGuardian() { return _name == kGuardian_Han || _name == kGuardian_Roshi; }
	inline bool			isNotGuardian() { return !isGuardian(); }
	// role extensions
	inline bool			isCom() { return _role == Role::Com; }
	inline bool			isPlayer() { return _role == Role::Player; }
	inline bool			isPlayerOrCom() { return isPlayer() || isCom(); }
	inline bool			isFlog() { return _role == Role::Flog; }
	inline bool			isTower() { return _role == Role::Tower; }
	inline bool			isBullet() { return _role == Role::Bullet; }
	inline bool			isClone() { return _role == Role::Clone; }
	inline bool			isKugutsu() { return _role == Role::Kugutsu; }
	inline bool			isMon() { return _role == Role::Mon; }
	inline bool			isSummon() { return _role == Role::Summon; }
	inline bool			isNotCom() { return _role != Role::Com; }
	inline bool			isNotPlayer() { return _role != Role::Player; }
	inline bool			isNotFlog() { return _role != Role::Flog; }
	inline bool			isNotTower() { return _role != Role::Tower; }
	inline bool			isNotBullet() { return _role != Role::Bullet; }
	inline bool			isNotClone() { return _role != Role::Clone; }
	inline bool			isNotKugutsu() { return _role != Role::Kugutsu; }
	inline bool			isNotMon() { return _role != Role::Mon; }
	inline bool			isNotSummon() { return _role != Role::Summon; }
	// group extensions
	inline bool			isKonohaGroup() { return _group == Group::Konoha; }
	inline bool			isAkatsukiGroup() { return _group == Group::Akatsuki; }
	// monster extensions
	inline bool			hasMonsterArrayAny() { return !_monsterArray.empty(); }
	inline void			removeMon(CharacterBase *mo) {
		if (hasMonsterArrayAny())
			std::erase(_monsterArray, mo);
	}
	inline void			removeAllMonAndCleanup(const string &name) {
		if (hasMonsterArrayAny()) {
			for (auto mo : _monsterArray)
			{
				if (mo->getName() == name)
				{
					std::erase(_monsterArray, mo);
					mo->removeFromParent();
				}
			}
		}
	}
	// Utilities
	void				increaseAllCkrs(uint32_t value, bool enableLv2 = true, bool enableLv4 = true);
	inline void			increaseHpAndUpdateUI(uint32_t value);
protected:
	// find enemy extensions
	inline bool			findHero(int searchRange, bool masterRange = false) { return findEnemy(Role::Hero, searchRange, masterRange); }
	inline bool			findFlog(int searchRange, bool masterRange = false) { return findEnemy(Role::Flog, searchRange, masterRange); }
	inline bool			findTower(int searchRange, bool masterRange = false) { return findEnemy(Role::Tower, searchRange, masterRange); }
	inline bool			notFindHero(int searchRange, bool masterRange = false) { return !findEnemy(Role::Hero, searchRange, masterRange); }
	inline bool			notFindFlog(int searchRange, bool masterRange = false) { return !findEnemy(Role::Flog, searchRange, masterRange); }
	inline bool			notFindTower(int searchRange, bool masterRange = false) { return !findEnemy(Role::Tower, searchRange, masterRange); }
	inline bool			findHeroHalf() { return findEnemy2(Role::Hero); }
	inline bool			findFlogHalf() { return findEnemy2(Role::Flog); }
	inline bool			findTowerHalf() { return findEnemy2(Role::Tower); }
	inline bool			notFindHeroHalf() { return !findEnemy2(Role::Hero); }
	inline bool			notFindFlogHalf() { return !findEnemy2(Role::Flog); }
	inline bool			notFindTowerHalf() { return !findEnemy2(Role::Tower); }
	// AI extensions
	void				tryBuyGear(GearType gear1, GearType gear2, GearType gear3) {
		if (getCoin() >= 500 && getGearArray().size() < 3 && !_isControlled && getGameLayer()->_enableGear)
		{
			if (getGearArray().size() == 0)
				setGear(gear1);
			else if (getGearArray().size() == 1)
				setGear(gear2);
			else if (getGearArray().size() == 2)
				setGear(gear3);
		}
	}
	inline void			tryUseGear6() {
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
	}
	bool				needBackToTowerToRestoreHP(bool isNeedBack = true) {
		if (checkRetri() && isNeedBack)
		{
			if (_mainTarget)
			{
				if (stepBack2())
				{
					if (_isCanGear00 && !_isArmored)
						useGear(gear00);
					return true;
				}
			}
			else
			{
				if (_isCanGear00)
					useGear(gear00);

				if (stepBack())
					return true;
			}
		}
		return false;
	}
	bool				needBackToDefendTower(bool isNeedBack = true) {
		if (isBaseDanger && checkBase() && !_isControlled && isNeedBack)
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
				if (_isCanGear00)
					useGear(gear00);

				if (stepBack2())
					return true;
			}
		}
		return false;
	}
	inline bool			checkMove(float x = 32, float y = 32) {
		auto sp = getDistanceToTarget();
		if (abs(sp.x) > x || abs(sp.y) > y)
		{
			auto moveDirection = ccpNormalize(sp);
			walk(moveDirection);
			return true;
		}
		return false;
	}
	inline void			checkHealingState() {
		if (_isHealing && getHpPercent() < 1)
		{
			if (isFreeActionState())
				idle();
		}
		else
		{
			if (_isCanGear00 && !_isArmored)
				useGear(gear00);

			stepOn();
		}
	}
	inline Vec2			getDirByMoveTo(CharacterBase *target) {
		return ccpNormalize(ccpSub(target->getPosition(), getPosition()));
	}
	inline Vec2			getDistanceToTarget() {
		return _mainTarget->_originY
			? ccpSub(Vec2(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition())
			: ccpSub(_mainTarget->getPosition(), getPosition());
	}
	inline Vec2			getDistanceToTargetAndIgnoreOriginY() {
		return ccpSub(_mainTarget->getPosition(), getPosition());
	}
public:
	// actoin state extensions

	// Action is State::IDLE or State::WALK or State::NATTACK
	inline bool			isFreeActionState() {
		return _actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK;
	}

/**
 * Callbacks
 */
protected:
	virtual bool onAcceptAttack(CharacterBase *attacker) { return true; }
	// Returns true will call CharacterBase::setDamage(attacker), false otherwise.
	virtual bool onHit(CharacterBase *attacker) { return true; }
	// Returns true will call CharacterBase::setDamage(attacker), false otherwise.
	virtual bool onBulletHit(CharacterBase *attacker) { return true; }

	virtual void onSetTrap(const string &trapType) { }

private:
	bool			_affectedByTower;
};
