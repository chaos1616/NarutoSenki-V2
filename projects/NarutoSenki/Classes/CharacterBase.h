#pragma once
#include "Data/UnitData.h"
#include "Effect.h"
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

class CharacterBase : public CCSprite
{
friend class CommandSystem;

public:
	CharacterBase();
	~CharacterBase();

	virtual void		setID(CCString* character, CCString* role, CCString* group);
	virtual	void		setHPbar();
	virtual	void	   	changeHPbar();
	void				updateDataByLVOnly();
	virtual	void		setShadows();

	VPROP(int,_charNO,CharNO);

	uint32_t			_deadNum;
	uint32_t			_flogNum;
	CC_SYNTHESIZE_RETAIN(CCString*,_killNum,KillNum);
	CC_SYNTHESIZE_RETAIN(CCString*,_coin,Coin);


	CharacterBase*		_slayer;
	CharacterBase*		_sticker;
	CharacterBase*		_mainTarget;

	bool				isHurtingTower;

	bool				_isFlipped;
	bool				_isHitOne;
	bool				_isCatchOne;
	bool				_isHealling;
	bool				_isVisable;

	// buff
	uint32_t			_healBuffValue;
	uint32_t			_dehealBuffValue;
	uint32_t			_powerUPBuffValue;
	uint32_t			_skillUPBuffValue;
	uint32_t			_skillChangeBuffValue;


	CCSprite*			_heartEffect;
	Effect*				_healBuffEffect;
	Effect*				_powerBuffEffect;
	Effect*				_skillBuffEffect;
	CCSprite*			_dehealBuffEffect;
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

	CCPoint				_markPoint;
	CCPoint				_startPoint;

	bool				_isAI;
	bool				_isControlled;

	CC_SYNTHESIZE_RETAIN(CCLabelTTF*,cpLabel,CPLabel);
	//attributes
	CC_SYNTHESIZE_RETAIN(CCString*,_role,Role);
	CC_SYNTHESIZE_RETAIN(CCString*,_group,Group);
	CC_SYNTHESIZE_RETAIN(CCString*,_character,Character);
	PROP_Vector(vector<gearType>,_gearArray,GearArray);

	bool				enableDead	 = true;
	bool				enableReborn = true;
	int8_t				changeCharId = -1; // NOTE: Support for random deathmatch mode

	int 				rebornLabelTime;
	int 				battleCondiction;
	// True is only has one tower, false otherwise
	bool 				isBaseDanger;


	HPBar*				_hpBar;
	CCSprite*			_shadow;
	float				_originY;
	float				_backY;
	float				_diretionY;

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

	VPROP(int,_walkSpeed, WalkSpeed);
	int _originSpeed;

	CC_SYNTHESIZE_RETAIN(CCString*,_maxHP,MaxHP);
	CC_SYNTHESIZE_RETAIN(CCString*,_hp,HP);
	CC_SYNTHESIZE_RETAIN(CCString*,_ckr,CKR);
	CC_SYNTHESIZE_RETAIN(CCString*,_ckr2,CKR2);
	VPROP(float,_gardValue,GP);
	VPROP(float,_exp,EXP);
	VPROP(uint32_t,_level,LV);
	VPROP(int,_height,Height);
	VPROP(int,_rebornTime,RebornTime);
	VPROP(CCPoint,_spawnPoint,SpawnPoint);


	CC_SYNTHESIZE(CharacterBase*,_master,Master);
	CC_SYNTHESIZE(CharacterBase*,_controller,Controller);
	CC_SYNTHESIZE(CharacterBase*,_secmaster,SecMaster);

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_nattackValue,nAttackValue);
	PROP_REF(string,_nattackType,nAttackType);
	int				_nattackRangeX;
	int				_nattackRangeY;

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_sattackValue1,sAttackValue1);
	PROP_REF(string,_sattackType1,SAttackType1);
	int				_sattackRangeX1;
	int				_sattackRangeY1;
	uint32_t		_sattackcooldown1;
	bool			_sattack1isDouble;
	int				_sattackCombatPoint1;

	uint32_t		 _attackValue;
	PROP_REF(string,_attackType,AttackType);
	int				_attackRangeX;
	int				_attackRangeY;

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_sattackValue2,sAttackValue2);
	PROP_REF(string,_sattackType2,SAttackType2);
	int				_sattackRangeX2;
	int				_sattackRangeY2;
	uint32_t		_sattackcooldown2;
	bool			_sattack2isDouble;
	int				_sattackCombatPoint2;

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_sattackValue3,sAttackValue3);
	PROP_REF(string,_sattackType3,SAttackType3);
	int				_sattackRangeX3;
	int				_sattackRangeY3;
	uint32_t		_sattackcooldown3;
	bool			_sattack3isDouble;
	int				_sattackCombatPoint3;

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_sattackValue4,sAttackValue4);
	PROP_REF(string,_sattackType4,SAttackType4);
	int				_sattackRangeX4;
	int				_sattackRangeY4;
	uint32_t		_sattackcooldown4;
	bool			_sattack4isDouble;
	int				_sattackCombatPoint4;

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_sattackValue5,sAttackValue5);
	PROP_REF(string,_sattackType5,SAttackType5);
	int				_sattackRangeX5;
	int				_sattackRangeY5;
	uint32_t		_sattackcooldown5;
	int				_sattackCombatPoint5;

	// int totalCombatPoint;
	int enemyCombatPoint;
	int friendCombatPoint;

	CC_SYNTHESIZE_RETAIN(CCString*,_spcattackValue1,spcAttackValue1);
	PROP_REF(string,_spcattackType1,SpcAttack1Type);
	int				_spcattackRangeX1;
	int				_spcattackRangeY1;
	uint32_t		_spcattackcooldown1;

	CC_SYNTHESIZE_RETAIN(CCString*,_spcattackValue2,spcAttackValue2);
	PROP_REF(string,_spcattackType2,SpcAttack2Type);
	int				_spcattackRangeX2;
	int				_spcattackRangeY2;
	uint32_t		_spcattackcooldown2;

	CC_SYNTHESIZE_RETAIN(CCString*,_spcattackValue3,spcAttackValue3);
	PROP_REF(string,_spcattackType3,SpcAttack3Type);
	int				_spcattackRangeX3;
	int				_spcattackRangeY3;
	uint32_t		_spcattackcooldown3;

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_tempAttackValue1,tempAttackValue1);


	PROP(const char*,_effectType,EffectType);
	bool			_hurtFromLeft;
	bool			_hurtFromRight;

	vector<CCLabelBMFont *>	_damageArray;
	uint32_t				damageEffectCount;
	PROP_Vector(vector<CharacterBase *>,_monsterArray,MonsterArray);

	// movement
	PROP(CCPoint,_velocity, Velocity);
	PROP(CCPoint,_desiredPosition, DesiredPosition);

	VPROP(State,_actionState, ActionState);

	// actions
	CC_SYNTHESIZE_RETAIN(CCAction*,_idleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(CCAction*,_nattackAction, NAttackAction);
	CC_SYNTHESIZE_RETAIN(CCAction*,_walkAction, WalkAction);
	CC_SYNTHESIZE_RETAIN(CCAction*,_hurtAction, HurtAction);
	CC_SYNTHESIZE_RETAIN(CCAction*,_knockDownAction, KnockDownAction);
	CC_SYNTHESIZE_RETAIN(CCAction*,_airHurtAction, AirHurtAction);
	CC_SYNTHESIZE_RETAIN(CCAction*,_floatAction, FloatAction);
	CC_SYNTHESIZE_RETAIN(CCAction*,_deadAction, DeadAction); 


	CC_SYNTHESIZE_RETAIN(CCAction*,_skill1Action, Skill1Action);
	CC_SYNTHESIZE_RETAIN(CCAction*,_skill2Action, Skill2Action);
	CC_SYNTHESIZE_RETAIN(CCAction*,_skill3Action, Skill3Action);
	CC_SYNTHESIZE_RETAIN(CCAction*,_skill4Action, Skill4Action);
	CC_SYNTHESIZE_RETAIN(CCAction*,_skill5Action, Skill5Action);


	CC_SYNTHESIZE_RETAIN(CCActionInterval*,_moveAction,MoveAction);
	CC_SYNTHESIZE_RETAIN(CCAction*,_floatUPAction,FloatUPAction);
	CC_SYNTHESIZE_RETAIN(CCActionInterval*,_jumpUPAction,JumpUPAction);


	void				update(float dt);
	void				updateHpBarPosition(float dt);
	void				acceptAttack(CCObject* object);


	inline float		getHpPercent();

	bool				checkHasMovement();

	void				idle();
	void				walk(CCPoint direction);
	void				attack(abType type);
	void				sAttack(abType type);
	void				nAttack();
	void				oAttack(abType type);
	bool				hurt();
	bool				hardHurt(int delayTime, bool isHurtAction, bool isCatch, bool isStick, bool isStun);
	void				absorb(CCPoint position, bool isImmediate);
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

	void				setShadow(CCSpriteFrame *frame);
	void				enableShadow(CCSprite *charN);
	void				disableShadow(CCSprite *charN);

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

	bool				setGear(gearType type);
	void				useGear(gearType type);

	void				setCoinDisplay(int num);
	void				removeCoinDisplay(CCSprite *coinDisplay);
	void				addCoin(int num);
	void				minusCoin(int num);

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

	// TODO: Upgrade cocos2d-x to V4
	inline void			readData(CCArray* tmpData, string &attackType, CCString* &attackValue, int &attackRangeX, int &attackRangeY, uint32_t &cooldown, int &combatPoint)
	{
		CCString *tmpType = nullptr;
		readData(tmpData, tmpType, attackValue, attackRangeX, attackRangeY, cooldown, combatPoint);
		if (tmpType)
		{
			attackType = tmpType->m_sString;
			CC_SAFE_RELEASE(tmpType);
		}
	}
	void				readData(CCArray* tmpData, CCString* &attackType, CCString* &attackValue, int &attackRangeX, int &attackRangeY, uint32_t &cooldown, int &combatPoint);
	CCAction*			createAnimation(CCArray* ationArray, float fps, bool isRepeat, bool isReturn);

	void				setSound(const string &file);
	void				setDSound(const string &file);
	void				setMove(int moveLength);
	void				setCharge(int moveLength);
	void				setChargeB(int moveLength);
	void				getCollider();
	void				getSticker(float dt);
	void				stopMove(float dt);
	void				stopJump(int stopTime);
	void				setAttackBox(const string &data);
	inline void			setDamage(CharacterBase* attacker);
	void				setDamage(CharacterBase *attacker, const char* effectType, int attackValue, bool isFlipped);
	void				setDamgeDisplay(int value, const char* type);

	void				setSkillEffect(const string &type);
	// void				setItemEffect(const string &type);
	void				setDamgeEffect(const char* type);
	void				setMonAttack(int skillNum);
	void				setTransform();
	void				setOugis();

	void				setCharFlip();


	virtual Hero*		createClone(int cloneTime);
	void				setClone(int cloneTime);
	void				setMon(const string &monName);
	void				setMonPer(float dt);
	void				setBullet(const string &bulletName);
	void				setBulletGroup(float dt);
	void				setTrap(const string &trapName);


	void				setBuff(int buffValue);
	void				setCommand(const string &cmd);
	void				setBuffEffect(const char* type);
	void				removeBuffEffect(const char* type);
public:
	void				disableBuff(float dt);
	void				healBuff(float dt);
protected:
	void				dehealBuff(float dt);

	void				removeClone(float dt);
	void				removeSelf(float dt);
	void				setJump(bool jumpDirection);

	CCRect				setHalfBox();
	CCRect				setHitBox();

	void				checkActionFinish(float dt);

	void				setRestore(float dt);


	bool				findEnemy(const char* type, int searchRange, bool masterRange = false);
	bool				findEnemy2(const char* type);
	bool				findTargetEnemy(const char* type, bool isTowerDected);
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
	void				changeSide(CCPoint sp);

	inline void			autoFlip(CharacterBase* attacker);

	void				removeDamageDisplay();

	void				onEnter();
	void				onExit();

public:
	// UI
	inline void 		updateHpBar();
	// character extensions
	inline int			getCoinValue() { return to_int(_coin->getCString()); }
	inline void			setCoinValue(uint32_t var) { setCoin(to_ccstring(var)); }
	inline uint32_t		getCkrValue() { return to_uint(_ckr->getCString()); }
	inline void			setCkrValue(uint32_t var) { setCKR(to_ccstring(var)); }
	inline uint32_t		getCkr2Value() { return to_uint(_ckr2->getCString()); }
	inline void			setCkr2Value(uint32_t var) { setCKR2(to_ccstring(var)); }
	inline uint32_t		getHPValue() { return to_uint(_hp->getCString()); }
	inline void			setHPValue(uint32_t var, bool isUpdateHpBar = true) {
		setHP(to_ccstring(var));
		if (isUpdateHpBar)
			updateHpBar();
	}
	inline uint32_t		getMaxHPValue() { return to_uint(_maxHP->getCString()); }
	inline void			setMaxHPValue(uint32_t var, bool isUpdateHpBar = true) {
		setMaxHP(to_ccstring(var));
		if (isUpdateHpBar)
			updateHpBar();
	}
	inline int			getNAttackValue() { return to_int(_nattackValue->getCString()); }
	inline int			getSAttackValue1() { return to_int(_sattackValue1->getCString()); }
	inline int			getSAttackValue2() { return to_int(_sattackValue2->getCString()); }
	inline int			getSAttackValue3() { return to_int(_sattackValue3->getCString()); }
	inline int			getSAttackValue4() { return to_int(_sattackValue4->getCString()); }
	inline int			getSAttackValue5() { return to_int(_sattackValue5->getCString()); }
	inline int			getSpcAttackValue1() { return to_int(_spcattackValue1->getCString()); }
	inline int			getSpcAttackValue2() { return to_int(_spcattackValue2->getCString()); }
	inline int			getSpcAttackValue3() { return to_int(_spcattackValue3->getCString()); }
	inline int			getTempAttackValue1() { return to_int(_tempAttackValue1->getCString()); }
	inline CCString*	getNAttackValueStr() { return _nattackValue; }
	inline CCString*	getSAttackValue1Str() { return _sattackValue1; }
	inline CCString*	getSAttackValue2Str() { return _sattackValue2; }
	inline CCString*	getSAttackValue3Str() { return _sattackValue3; }
	inline CCString*	getSAttackValue4Str() { return _sattackValue4; }
	inline CCString*	getSAttackValue5Str() { return _sattackValue5; }
	inline CCString*	getSpcAttackValue1Str() { return _spcattackValue1; }
	inline CCString*	getSpcAttackValue2Str() { return _spcattackValue2; }
	inline CCString*	getSpcAttackValue3Str() { return _spcattackValue3; }
	inline CCString*	getTempAttackValue1Str() { return _tempAttackValue1; }
	inline bool			hasTempAttackValue1() { return _tempAttackValue1 != nullptr; }
	inline bool			isCharacter(const string &c) { return _character->m_sString == c; }
	inline bool			isCharacter(const char *c) { return is_same(_character->getCString(), c); }
	inline bool			isCharacter(const char *c1, const char *c2) {
		auto n = _character->getCString();
		return is_same(n, c1) || is_same(n, c2);
	}
	inline bool			isCharacter(const char *c1, const char *c2, const char *c3) {
		auto n = _character->getCString();
		return is_same(n, c1) || is_same(n, c2) || is_same(n, c3);
	}
	inline bool			isCharacter(const char *c1, const char *c2, const char *c3, const char *c4) {
		auto n = _character->getCString();
		return is_same(n, c1) || is_same(n, c2) || is_same(n, c3) || is_same(n, c4);
	}
	inline bool			isCharacter(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5) {
		auto n = _character->getCString();
		return is_same(n, c1) || is_same(n, c2) || is_same(n, c3) || is_same(n, c4) || is_same(n, c5);
	}
	inline bool			isCharacter(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5, const char *c6) {
		auto n = _character->getCString();
		return is_same(n, c1) || is_same(n, c2) || is_same(n, c3) || is_same(n, c4) || is_same(n, c5) || is_same(n, c6);
	}
	inline bool			isCharacter(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5, const char *c6, const char *c7) {
		auto n = _character->getCString();
		return is_same(n, c1) || is_same(n, c2) || is_same(n, c3) || is_same(n, c4) || is_same(n, c5) || is_same(n, c6) || is_same(n, c7);
	}
	inline bool			isCharacter(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5, const char *c6, const char *c7, const char *c8) {
		auto n = _character->getCString();
		return is_same(n, c1) || is_same(n, c2) || is_same(n, c3) || is_same(n, c4) || is_same(n, c5) || is_same(n, c6) || is_same(n, c7) || is_same(n, c8);
	}
	inline bool			isCharacter(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5, const char *c6, const char *c7, const char *c8, const char *c9) {
		auto n = _character->getCString();
		return is_same(n, c1) || is_same(n, c2) || is_same(n, c3) || is_same(n, c4) || is_same(n, c5) || is_same(n, c6) || is_same(n, c7) || is_same(n, c8) || is_same(n, c9);
	}
	inline bool			isCharacter(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5, const char *c6, const char *c7, const char *c8, const char *c9, const char *c10) {
		auto n = _character->getCString();
		return is_same(n, c1) || is_same(n, c2) || is_same(n, c3) || is_same(n, c4) || is_same(n, c5) || is_same(n, c6) || is_same(n, c7) || is_same(n, c8) || is_same(n, c9) || is_same(n, c10);
	}
	inline bool			isNotCharacter(const string &c) { return _character->m_sString != c; }
	inline bool			isNotCharacter(const char *c) { return !is_same(_character->getCString(), c); }
	inline bool			isNotCharacter(const char *c1, const char *c2) { return !isCharacter(c1, c2); }
	inline bool			isNotCharacter(const char *c1, const char *c2, const char *c3) { return !isCharacter(c1, c2, c3); }
	inline bool			isNotCharacter(const char *c1, const char *c2, const char *c3, const char *c4) { return !isCharacter(c1, c2, c3, c4); }
	inline bool			isNotCharacter(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5) { return !isCharacter(c1, c2, c3, c4, c5); }
	inline bool			isNotCharacter(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5, const char *c6) { return !isCharacter(c1, c2, c3, c4, c5, c6); }
	inline bool			isNotCharacter(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5, const char *c6, const char *c7) { return !isCharacter(c1, c2, c3, c4, c5, c6, c7); }
	inline bool			isNotCharacter(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5, const char *c6, const char *c7, const char *c8) { return !isCharacter(c1, c2, c3, c4, c5, c6, c7, c8); }
	inline bool			isNotCharacter(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5, const char *c6, const char *c7, const char *c8, const char *c9) { return !isCharacter(c1, c2, c3, c4, c5, c6, c7, c8, c9); }
	inline bool			isNotCharacter(const char *c1, const char *c2, const char *c3, const char *c4, const char *c5, const char *c6, const char *c7, const char *c8, const char *c9, const char *c10) { return !isCharacter(c1, c2, c3, c4, c5, c6, c7, c8, c9, c10); }
	inline bool			isGuardian() { return isCharacter(kGuardian_Han, kGuardian_Roshi); }
	inline bool			isNotGuardian() { return !isGuardian(); }
	// role extensions
	inline bool			isPlayer() { return is_same(_role->getCString(), kRolePlayer); }
	inline bool			isCom() { return is_same(_role->getCString(), kRoleCom); }
	inline bool			isClone() { return is_same(_role->getCString(), kRoleClone); }
	inline bool			isFlog() { return is_same(_role->getCString(), kRoleFlog); }
	inline bool			isKugutsu() { return is_same(_role->getCString(), kRoleKugutsu); }
	inline bool			isMon() { return is_same(_role->getCString(), kRoleMon); }
	inline bool			isSummon() { return is_same(_role->getCString(), kRoleSummon); }
	inline bool			isTower() { return is_same(_role->getCString(), kRoleTower); }
	inline bool			isBullet() { return is_same(_role->getCString(), kRoleBullet); }
	inline bool			isPlayerOrCom() { return isPlayer() || isCom(); }
	inline bool			isNotPlayer() { return !is_same(_role->getCString(), kRolePlayer); }
	inline bool			isNotCom() { return !is_same(_role->getCString(), kRoleCom); }
	inline bool			isNotClone() { return !is_same(_role->getCString(), kRoleClone); }
	inline bool			isNotFlog() { return !is_same(_role->getCString(), kRoleFlog); }
	inline bool			isNotKugutsu() { return !is_same(_role->getCString(), kRoleKugutsu); }
	inline bool			isNotMon() { return !is_same(_role->getCString(), kRoleMon); }
	inline bool			isNotSummon() { return !is_same(_role->getCString(), kRoleSummon); }
	inline bool			isNotTower() { return !is_same(_role->getCString(), kRoleTower); }
	inline bool			isNotBullet() { return !is_same(_role->getCString(), kRoleBullet); }
	// group extensions
	inline bool			isGroup(const char *group) { return is_same(_group->getCString(), group); }
	inline bool			isSameGroupAs(CharacterBase *c) { return isGroup(c->getGroup()->getCString()); }
	inline bool			isNotSameGroupAs(CharacterBase *c) { return !isSameGroupAs(c); }
	inline bool			isKonohaGroup() { return is_same(_group->getCString(), Konoha); }
	inline bool			isAkatsukiGroup() { return is_same(_group->getCString(), Akatsuki); }
	// monster extensions
	inline bool			hasMonsterArrayAny() { return !_monsterArray.empty(); }
	inline void			removeMon(CharacterBase *mo) {
		if (hasMonsterArrayAny())
			std::erase(_monsterArray, mo);
	}
	// Utilities
	void				increaseAllCkrs(uint32_t value, bool enableLv2 = true, bool enableLv4 = true);
	inline void			increaseHpAndUpdateUI(uint32_t value);
protected:
	// find enemy extensions
	inline bool 		findHero(int searchRange, bool masterRange = false) { return findEnemy(kRoleHero, searchRange, masterRange); }
	inline bool 		findFlog(int searchRange, bool masterRange = false) { return findEnemy(kRoleFlog, searchRange, masterRange); }
	inline bool 		findTower(int searchRange, bool masterRange = false) { return findEnemy(kRoleTower, searchRange, masterRange); }
	inline bool 		notFindHero(int searchRange, bool masterRange = false) { return !findEnemy(kRoleHero, searchRange, masterRange); }
	inline bool 		notFindFlog(int searchRange, bool masterRange = false) { return !findEnemy(kRoleFlog, searchRange, masterRange); }
	inline bool 		notFindTower(int searchRange, bool masterRange = false) { return !findEnemy(kRoleTower, searchRange, masterRange); }
	inline bool 		findHeroHalf() { return findEnemy2(kRoleHero); }
	inline bool 		findFlogHalf() { return findEnemy2(kRoleFlog); }
	inline bool 		findTowerHalf() { return findEnemy2(kRoleTower); }
	inline bool 		notFindHeroHalf() { return !findEnemy2(kRoleHero); }
	inline bool 		notFindFlogHalf() { return !findEnemy2(kRoleFlog); }
	inline bool 		notFindTowerHalf() { return !findEnemy2(kRoleTower); }
	// AI extensions
	inline CCPoint 		getDirByMoveTo(CharacterBase *target) { return ccpNormalize(ccpSub(target->getPosition(), getPosition())); }
	inline CCPoint 		getDistanceToTarget() {
		return _mainTarget->_originY
			? ccpSub(ccp(_mainTarget->getPositionX(), _mainTarget->_originY), getPosition())
			: ccpSub(_mainTarget->getPosition(), getPosition());
	}
	inline CCPoint 		getDistanceToTargetAndIgnoreOriginY() {
		return ccpSub(_mainTarget->getPosition(), getPosition());
	}
public:
	// actoin state extensions

	// Action is State::IDLE or State::WALK or State::NATTACK
	inline bool 		isFreeActionState() {
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
