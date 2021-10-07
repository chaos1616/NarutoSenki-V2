#pragma once
#include "Effect.h"
#include "GameLayer.h"
#include "Enums/Character.hpp"
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
	ABHURT,
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

	virtual void		setID(CCString* character,CCString* role,CCString *group);
	virtual	void		setHPbar();
	virtual	void	   	changeHPbar();
	void				updateDataByLVOnly();
	virtual	void		setShadows();
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
	//buff


	CC_SYNTHESIZE(int,_charNO,CharNO);

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
	CC_SYNTHESIZE(int,_knockLength, KnockLength);
	CC_SYNTHESIZE(bool,_knockDirection, KnockDirection);
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
	CC_SYNTHESIZE_RETAIN(CCArray*,_gearArray,GearArray);

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

	CC_SYNTHESIZE(int,_walkSpeed, WalkSpeed);
	int _originSpeed;

	CC_SYNTHESIZE_RETAIN(CCString*,_maxHP,MaxHP);
	CC_SYNTHESIZE_RETAIN(CCString*,_hp,HP);

	CC_SYNTHESIZE_RETAIN(CCString*,_ckr,CKR);
	CC_SYNTHESIZE_RETAIN(CCString*,_ckr2,CKR2);
	CC_SYNTHESIZE(float,_gardValue,GP);
	CC_SYNTHESIZE(float,_exp,EXP);
	CC_SYNTHESIZE(uint32_t,_level,LV);
	CC_SYNTHESIZE(int,_height,Height);
	CC_SYNTHESIZE(int,_rebornTime,RebornTime);


	CC_SYNTHESIZE(CCPoint,_spawnPoint,SpawnPoint);


	CC_SYNTHESIZE(CharacterBase*,_master,Master);
	CC_SYNTHESIZE(CharacterBase*,_controller,Controller);
	CC_SYNTHESIZE(CharacterBase*,_secmaster,SecMaster);

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_nattackValue,nAttackValue);
	CC_SYNTHESIZE(CCString*,_nattackType,nAttackType);
	int				_nattackRangeX;
	int				_nattackRangeY;

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_sattackValue1,sAttackValue1);
	CC_SYNTHESIZE(CCString*,_sattackType1,sAttack1Type);
	int				_sattackRangeX1;
	int				_sattackRangeY1;
	uint32_t		_sattackcoldDown1;
	bool			_sattack1isDouble;
	int				_sattackCombatPoint1;

	uint32_t		 _attackValue;
	CC_SYNTHESIZE(CCString*,_attackType,AttackType);
	int				_attackRangeX;
	int				_attackRangeY;

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_sattackValue2,sAttackValue2);
	CC_SYNTHESIZE(CCString*,_sattackType2,sAttack2Type);
	int				_sattackRangeX2;
	int				_sattackRangeY2;
	uint32_t		_sattackcoldDown2;
	bool			_sattack2isDouble;
	int				_sattackCombatPoint2;

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_sattackValue3,sAttackValue3);
	CC_SYNTHESIZE(CCString*,_sattackType3,sAttack3Type);
	int				_sattackRangeX3;
	int				_sattackRangeY3;
	uint32_t		_sattackcoldDown3;
	bool			_sattack3isDouble;
	int				_sattackCombatPoint3;

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_sattackValue4,sAttackValue4);
	CC_SYNTHESIZE(CCString*,_sattackType4,sAttack4Type);
	int				_sattackRangeX4;
	int				_sattackRangeY4;
	uint32_t		_sattackcoldDown4;
	bool			_sattack4isDouble;
	int				_sattackCombatPoint4;

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_sattackValue5,sAttackValue5);
	CC_SYNTHESIZE(CCString*,_sattackType5,sAttack5Type);
	int				_sattackRangeX5;
	int				_sattackRangeY5;
	uint32_t		_sattackcoldDown5;
	int				_sattackCombatPoint5;

	//int totalCombatPoint;
	int enemyCombatPoint;
	int friendCombatPoint;

	CC_SYNTHESIZE_RETAIN(CCString*,_spcattackValue1,spcAttackValue1);
	CC_SYNTHESIZE(CCString*,_spcattackType1,spcAttack1Type);
	int				_spcattackRangeX1;
	int				_spcattackRangeY1;
	uint32_t		_spcattackcoldDown1;

	CC_SYNTHESIZE_RETAIN(CCString*,_spcattackValue2,spcAttackValue2);
	CC_SYNTHESIZE(CCString*,_spcattackType2,spcAttack2Type);
	int				_spcattackRangeX2;
	int				_spcattackRangeY2;
	uint32_t		_spcattackcoldDown2;

	CC_SYNTHESIZE_RETAIN(CCString*,_spcattackValue3,spcAttackValue3);
	CC_SYNTHESIZE(CCString*,_spcattackType3,spcAttack3Type);
	int				_spcattackRangeX3;
	int				_spcattackRangeY3;
	uint32_t		_spcattackcoldDown3;

	CC_SYNTHESIZE_RETAIN_SET_ONLY(CCString*,_tempAttackValue1,tempAttackValue1);
	int			_tempcoldDown1;


	CC_SYNTHESIZE(CCString*,_tempAttackType,TempAttackType);

	PROP(const char*,_effectType,EffectType);
	bool			_hurtFromLeft;
	bool			_hurtFromRight;


	CC_SYNTHESIZE(CCArray*,_damageArray,DamageArray);

	uint32_t		damageEffectCount;
	CC_SYNTHESIZE(CCArray*,_monsterArray,MonsterArray);

	//movement
	CC_SYNTHESIZE(CCPoint,_velocity, Velocity);
	CC_SYNTHESIZE(CCPoint,_desiredPosition, DesiredPosition);

	CC_SYNTHESIZE(State,_actionState, ActionState);
	CC_SYNTHESIZE(GameLayer*,_delegate, Delegate);



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


	CC_SYNTHESIZE_RETAIN(CCActionInterval* ,_moveAction,MoveAction);
	CC_SYNTHESIZE_RETAIN(CCAction* ,_floatUPAction,FloatUPAction);
	CC_SYNTHESIZE_RETAIN(CCActionInterval* ,_jumpUPAction,JumpUPAction);


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
	bool				hardHurt(int delayTime,bool isHurtAction,bool isCatch,bool isStick,bool isStun);
	void				absorb(CCPoint position,bool isImmediate);
	void				jump(){}; // No reference
	void				knockDown();
	virtual void		dead();
	void				floatUP(float floatHeight,bool isCancelSkill);
	void				airHurt();

	virtual void		doAI();


	virtual void		changeAction();
	void				changeAction2();
	void				changeGroup();

	virtual void		resumeAction(float dt);
	virtual void		setActionResume();
	void				setActionResume2();
	void				reCatched(float dt);

	void				setShadow(CCNode* sender,void* data);
	void				disableShadow(CCNode* sender);
	void				enableShadow(CCNode* sender);

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
	void				setSkillEffect(CCNode* sender,void* data);
	virtual void		setRestore2(float dt);

	void				readData(CCArray* tmpData,CCString* &attackType,CCString* &attackValue,int &attackRangeX,int &attackRangeY,uint32_t &coldDown,int &combatPoint);
	CCAction*			createAnimation(CCArray* ationArray,float fps,bool isRepeat,bool isReturn);

protected:
	CCDictionary*		callValue;

	void				setSound(CCNode* sender,void* data);
	void				setDSound(CCNode* sender,void* data);
	void				setMove(CCNode* sender,void* data);
	void				setCharge(CCNode* sender,void* data);
	void				setChargeB(CCNode* sender,void* data);
	void				getCollider();
	void				getSticker(float dt);
	void				stopMove(float dt);
	void				stopJump(CCNode* sender,void* data);
	void				setAttackBox(CCNode* sender,void* data);
	void				setDamage(const char* effectType,int attackValue,bool isFlipped);
	void				setDamgeDisplay(int value,const char* type);

	void				setItemEffect(CCNode* sender,void* data);
	void				setDamgeEffect(const char* type);
	void				setMonAttack(CCNode* sender,void* data);
	void				setTransform();
	void				setOugis(CCNode* sender);

	void				setCharFlip();


	virtual Hero*		createClone(int cloneTime);
	void				setClone(CCNode* sender,void* data);
	void				setMon(CCNode* sender,void* data);
	void				setMonPer(float dt);
	void				setBullet(CCNode* sender,void* data);
	void				setBulletGroup(float dt);

	void				setTrap(CCNode* sender,void* data);


	void				setBuff(CCNode* sender,void* data);
	void				setCommand(CCNode* sender,void* data);
	void				setBuffEffect(const char* type);
	void				removeBuffEffect(const char* type);
public:
	void				disableBuff(float dt);
	void				healBuff(float dt);
protected:
	void				dehealBuff(float dt);

	void				removeClone(float dt);
	void				removeSelf(float dt);
	void				setJump(CCNode* sender,void* data);


	void				removeCoinDisplay(CCNode* sender,void* data);

	CCRect				setHalfBox();
	CCRect				setHitBox();

	void				checkActionFinish(float dt);

	void				setRestore(float dt);


	bool				findEnemy(const char* type,int searchRange,bool masterRange = false);
	bool				findEnemy2(const char* type);
	bool				findTargetEnemy(const char* type,bool isTowerDected);
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
	inline bool			hasMonsterArrayAny() { return _monsterArray && _monsterArray->count() > 0; }
protected:
	// Utilities
	void				increaseAllCkrs(uint32_t value, bool enableLv2 = true, bool enableLv4 = true);
	inline void			increaseHpAndUpdateUI(uint32_t value);
	// find enemy extensions
	inline bool 		findHero(int searchRange,bool masterRange = false) { return findEnemy(kRoleHero, searchRange, masterRange); }
	inline bool 		findFlog(int searchRange,bool masterRange = false) { return findEnemy(kRoleFlog, searchRange, masterRange); }
	inline bool 		findTower(int searchRange,bool masterRange = false) { return findEnemy(kRoleTower, searchRange, masterRange); }
	inline bool 		notFindHero(int searchRange,bool masterRange = false) { return !findEnemy(kRoleHero, searchRange, masterRange); }
	inline bool 		notFindFlog(int searchRange,bool masterRange = false) { return !findEnemy(kRoleFlog, searchRange, masterRange); }
	inline bool 		notFindTower(int searchRange,bool masterRange = false) { return !findEnemy(kRoleTower, searchRange, masterRange); }
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
	inline bool 		isFreeActionState() {
		return _actionState == State::IDLE || _actionState == State::WALK || _actionState == State::NATTACK;
	}

private:
	bool	_affectedByTower;
};
