#pragma once
#include "Defines.h"
#include "Effect.h"
#include "GameLayer.h"
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
public:
	CharacterBase();
	~CharacterBase();

	virtual void		setID(CCString* character,CCString* role,CCString *group);
	virtual	void		setHPbar();
	virtual	void	   	changeHPbar();
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

	// character extension
	inline bool			isCharacter(const char *c) { return strcmp(_character->getCString(), c) == 0; }
	// role extension
	inline bool			isPlayer() { return strcmp(_role->getCString(), ROLE_PLAYER) == 0; }
	inline bool			isCom() { return strcmp(_role->getCString(), ROLE_COM) == 0; }
	inline bool			isClone() { return strcmp(_role->getCString(), ROLE_CLONE) == 0; }
	inline bool			isMon() { return strcmp(_role->getCString(), ROLE_MON) == 0; }
	inline bool			isSummon() { return strcmp(_role->getCString(), ROLE_SUMMON) == 0; }
	inline bool			isPlayerOrCom() { return isPlayer() || isCom(); }
	// group extension
	inline bool			isGroup(const char *group) { return strcmp(_group->getCString(), group) == 0; }
	inline bool			isKonohaGroup() { return strcmp(_group->getCString(), Konoha) == 0; }
	inline bool			isAkatsukiGroup() { return strcmp(_group->getCString(), Akatsuki) == 0; }

	bool				enableDead		= true;
	bool				enableReborn	= true;

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
	// 忍び：Shikamaru ability
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

	CC_SYNTHESIZE_RETAIN(CCString*,_nattackValue,nAttackValue);
	CC_SYNTHESIZE(CCString*,_nattackType,nAttackType);
	int				_nattackRangeX;
	int				_nattackRangeY;


	CC_SYNTHESIZE_RETAIN(CCString*,_sattackValue1,sAttackValue1);
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

	CC_SYNTHESIZE_RETAIN(CCString*,_sattackValue2,sAttackValue2);
	CC_SYNTHESIZE(CCString*,_sattackType2,sAttack2Type);
	int				_sattackRangeX2;
	int				_sattackRangeY2;
	uint32_t		_sattackcoldDown2;
	bool			_sattack2isDouble;
	int				_sattackCombatPoint2;

	CC_SYNTHESIZE_RETAIN(CCString*,_sattackValue3,sAttackValue3);
	CC_SYNTHESIZE(CCString*,_sattackType3,sAttack3Type);
	int				_sattackRangeX3;
	int				_sattackRangeY3;
	uint32_t		_sattackcoldDown3;
	bool			_sattack3isDouble;
	int				_sattackCombatPoint3;

	CC_SYNTHESIZE_RETAIN(CCString*,_sattackValue4,sAttackValue4);
	CC_SYNTHESIZE(CCString*,_sattackType4,sAttack4Type);
	int				_sattackRangeX4;
	int				_sattackRangeY4;
	uint32_t		_sattackcoldDown4;
	bool			_sattack4isDouble;
	int				_sattackCombatPoint4;

	CC_SYNTHESIZE_RETAIN(CCString*,_sattackValue5,sAttackValue5);
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


	CC_SYNTHESIZE_RETAIN(CCString*,_tempAttackValue1,tempAttackValue1);
	int			_tempcoldDown1;


	CC_SYNTHESIZE(CCString*,_tempAttackType,TempAttackType);

	CC_SYNTHESIZE(CCString*,_effectType,EffectType);
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


	float				getHpPercent();

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
	void				setDamage(CCString* effectType,int attackValue,bool isFlipped);
	void				setDamgeDisplay(int value,const char* type);

	void				setItemEffect(CCNode* sender,void* data);
	void				setDamgeEffect(CCString* type);
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
	public: void		disableBuff(float dt);
	void				healBuff(float dt);
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

private:
	bool				_affectedByTower;
};
