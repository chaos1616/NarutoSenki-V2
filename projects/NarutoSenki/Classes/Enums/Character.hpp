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

// Attack button type
enum ABType : uint8_t
{
	NAttack,
	Item1,	  // Item1: Ramen
	GearItem, // Item skill
	GearBtn,  // Gear skill
	SKILL1,
	SKILL2,
	SKILL3,
	OUGIS1,
	OUGIS2,
};

// declare GearButton
enum class GearType : uint8_t
{
	Gear00,
	Gear01,
	Gear02,
	Gear03,
	Gear04,
	Gear05,
	Gear06,
	Gear07,
	Gear08,
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
	None = 0UL,
	// Basic
	Dead = 1UL << 0UL,
	Idle = 1UL << 1UL,
	Walk = 1UL << 2UL,
	Hurt = 1UL << 3UL,
	AirHurt = 1UL << 4UL,
	Knockdown = 1UL << 5UL,
	Float = 1UL << 6UL,
	NAttack = 1UL << 7UL,
	Skill01 = 1UL << 8UL,
	Skill02 = 1UL << 9UL,
	Skill03 = 1UL << 10UL,
	Skill04 = 1UL << 11UL,
	Skill05 = 1UL << 12UL,
	// Custom Actions
	Spc01 = 1UL << 13UL,
	Spc02 = 1UL << 14UL,
	Spc03 = 1UL << 15UL,
	Spc04 = 1UL << 16UL,
	Spc05 = 1UL << 17UL,
	Spc06 = 1UL << 18UL,
	Spc07 = 1UL << 19UL,
	Spc08 = 1UL << 20UL,
	Spc09 = 1UL << 21UL,
	Spc10 = 1UL << 22UL,
	Spc11 = 1UL << 23UL,
	Spc12 = 1UL << 24UL,
	Spc13 = 1UL << 25UL,
	Spc14 = 1UL << 26UL,
	Spc15 = 1UL << 27UL,
	Spc16 = 1UL << 28UL,
	Spc17 = 1UL << 29UL,
	Spc18 = 1UL << 30UL,
	Spc19 = 1UL << 31UL,
	// NOTE: More should be changed to uint64_t
	// uint32_t::max = (1 << 32) - 1 (max count is 31)
	// uint64_t::max = (1 << 64) - 1 (max count is 63)
	//
	// Spc20 = 1ULL << 32ULL,
	// Spc21 = 1ULL << 33ULL,
	// Spc22 = 1ULL << 34ULL,
	// Spc23 = 1ULL << 35ULL,
	// Spc24 = 1ULL << 36ULL,
	// Spc25 = 1ULL << 37ULL,
	// Spc26 = 1ULL << 38ULL,
	// Spc27 = 1ULL << 39ULL,
	// Spc28 = 1ULL << 40ULL,
	// Spc29 = 1ULL << 41ULL,
	// Spc30 = 1ULL << 42ULL,
};

enum class HardHurtState : uint8_t
{
	None,
	Catch,	  // Unit caught on the ground
	CatchAir, // Unit is caught in the air
	Stick,
	Stun,
};
