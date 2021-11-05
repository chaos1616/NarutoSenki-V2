#pragma once
#include "Enums/HeroEnum.h"
#include "Enums/HitType.h"
#include "Enums/KugutsuEnum.h"
#include "Enums/ProjectileEnum.h"
#include "Enums/SkillEnum.h"
#include "Enums/SummonEnum.h"
#include "Enums/TowerEnum.h"

// Roles
#define kRoleCom "Com"
#define kRolePlayer "Player"
#define kRoleTower "Tower"
#define kRoleBullet "Bullet"
// Special
#define kRoleHero "Hero"
// 分身		Clone
#define kRoleClone "Clone"
#define kRoleFlog "Flog"
// 傀儡		Kugutsu
#define kRoleKugutsu "Kugutsu"
#define kRoleMon "Mon"
// 口寄せ	Summon
#define kRoleSummon "Summon"

enum class Role : uint8_t
{
	// Hero of Com
	Com,
	// Hero of Player
	Player,
	// Com & Player
	Hero,
	Flog,
	Tower,
	// Projectile
	Bullet,
	// 分身
	Clone,
	// 傀儡
	Kugutsu,
	Mon,
	// 口寄せ
	Summon,
};

#define cName(varName, varType) "Element/" varType "/" #varName ".plist"

// Flogs
#define kFlog_Kotetsu cName(KotetsuFlog, kRoleFlog)
#define kFlog_Izumo cName(IzumoFlog, kRoleFlog)
#define kFlog_Kakashi cName(KakashiFlog, kRoleFlog)
#define kFlog_FemalePain cName(FemalePainFlog, kRoleFlog)
#define kFlog_Pain cName(PainFlog, kRoleFlog)
#define kFlog_Obito cName(ObitoFlog, kRoleFlog)
// Guardians
#define kGuardian_Roshi "Roshi"
#define kGuardian_Han "Han"

enum abType
{
	NAttack,
	Item1,
	GearItem,
	GearBtn,
	SKILL1,
	SKILL2,
	SKILL3,
	OUGIS1,
	OUGIS2
};

// declare GearButton
enum GearType
{
	gear00,
	gear01,
	gear02,
	gear03,
	gear04,
	gear05,
	gear06,
	gear07,
	gear08,
	None
};

namespace AttackType
{
	mk_const(nAttack);
	mk_const(aAttack);
} // namespace AttackType

namespace BuffType
{

} // namespace BuffType

namespace FlogEnum
{
	// Konoha Flogs
	mk_const(KotetsuFlog); // LV 1
	mk_const(IzumoFlog);   // LV 2
	mk_const(KakashiFlog); // LV 3

	// Akatsuki Flogs
	mk_const(FemalePainFlog); // LV 1
	mk_const(PainFlog);		  // LV 2
	mk_const(ObitoFlog);	  // LV 3
} // namespace FlogEnum

#define kGroupKonoha "Konoha"
#define kGroupAkatsuki "Akatsuki"

enum class Group : uint8_t
{
	Konoha,
	Akatsuki,
};

enum class ActionFlag : uint32_t
{
	Dead = 1 << 0,
	Idle = 1 << 1,
	Walk = 1 << 2,
	Hurt = 1 << 3,
	Airhurt = 1 << 4,
	Knockdown = 1 << 5,
	Float = 1 << 6,
	NAttack = 1 << 7,
	Skill01 = 1 << 8,
	Skill02 = 1 << 9,
	Skill03 = 1 << 10,
	Skill04 = 1 << 11,
	Skill05 = 1 << 12,
	SkillSpc01 = 1 << 13,
	SkillSpc02 = 1 << 14,
	SkillSpc03 = 1 << 15,
	SkillSpc04 = 1 << 16,
	SkillSpc05 = 1 << 17,
	SkillSpc11 = 1 << 18,
	SkillSpc12 = 1 << 19,
	SkillSpc13 = 1 << 20,
	SkillSpc14 = 1 << 21,
	SkillSpc15 = 1 << 22,
};

inline ActionFlag operator~(ActionFlag a) { return (ActionFlag) ~(uint32_t)a; }
inline ActionFlag operator|(ActionFlag a, ActionFlag b) { return (ActionFlag)((uint32_t)a | (uint32_t)b); }
inline ActionFlag operator&(ActionFlag a, ActionFlag b) { return (ActionFlag)((uint32_t)a & (uint32_t)b); }
inline ActionFlag operator^(ActionFlag a, ActionFlag b) { return (ActionFlag)((uint32_t)a ^ (uint32_t)b); }
inline ActionFlag &operator|=(ActionFlag &a, ActionFlag b) { return (ActionFlag &)((uint32_t &)a |= (uint32_t)b); }
inline ActionFlag &operator&=(ActionFlag &a, ActionFlag b) { return (ActionFlag &)((uint32_t &)a &= (uint32_t)b); }
inline ActionFlag &operator^=(ActionFlag &a, ActionFlag b) { return (ActionFlag &)((uint32_t &)a ^= (uint32_t)b); }

enum class HardHurtState : uint8_t
{
	None,
	Catch,	  // Unit caught on the ground
	CatchAir, // Unit is caught in the air
	Stick,
	Stun,
};
