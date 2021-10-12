#pragma once
#include "Enums/Enums.hpp"

namespace AttackType
{
	mk_const(nAttack);
	mk_const(aAttack);
} // namespace AttackType

namespace HitType
{
	mk_const(n_hit);
	mk_const(b_hit);

	mk_const(l_hit);
	mk_const(f_hit);
	mk_const(f2_hit);
	mk_const(c_hit);
	mk_const(o_hit);
	mk_const(o2_hit);
	mk_const(ob_hit);
	mk_const(ab_hit);
	mk_const(ac_hit);
	mk_const(ct_hit);
	mk_const(ts_hit);
	mk_const(s_hit);

	mk_const(bl_hit);
	mk_const(bc_hit);
	mk_const(bf_hit);
	mk_const(sl_hit);
} // namespace HitType

namespace BuffType
{

} // namespace BuffType

namespace CharacterEnum
{
	// Shinobi
	mk_const(Asuma);
	mk_const(Chiyo);
	mk_const(Choji);
	mk_const(Deidara);
	mk_const(Gaara);
	mk_const(Hidan);
	mk_const(Hinata);
	mk_const(Hiruzen);
	mk_const(Ino);
	mk_const(Itachi);
	mk_const(Jiraiya);
	mk_const(Jugo);
	mk_const(Kakashi);
	mk_const(Kakuzu);
	mk_const(Kankuro);
	mk_const(Karin);
	mk_const(Kiba);
	mk_const(Kisame);
	mk_const(Konan);
	mk_const(Lee);
	mk_const(Minato);
	mk_const(Nagato);
	mk_const(Naruto);
	mk_const(Neji);
	mk_const(Orochimaru);
	// Pain
	mk_const(Pain);
	mk_const(AnimalPath);
	mk_const(AsuraPath);
	mk_const(NarakaPath);

	mk_const(Sai);
	mk_const(Sakura);
	mk_const(Sasuke);
	mk_const(Shikamaru);
	mk_const(Shino);
	mk_const(Suigetsu);
	mk_const(Tenten);
	mk_const(Tobi);
	mk_const(Tobirama);
	mk_const(Tsunade);

	// Bunshin
	mk_const(NarutoClone);
	mk_const(SageNarutoClone);
	mk_const(RikudoNarutoClone);

	// Guardian
	// Han, Roshi
	mk_const(Guardian);

	// Kuchiyose
	mk_const(Akamaru);
	mk_const(Centipede);
	mk_const(DogWall);
	mk_const(Karasu);
	mk_const(Kurama);
	mk_const(Mask);
	mk_const(Parents);
	mk_const(Sanshouuo);
	mk_const(Saso);
	mk_const(Slug);
} // namespace Character

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
} // namespace Flog

namespace Group
{
	// mk_const(Konoha);
	// mk_const(Akatsuki);
} // namespace Monster

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
	SkillSpc06 = 1 << 18,
	SkillSpc07 = 1 << 19,
	SkillSpc08 = 1 << 20,
	SkillSpc09 = 1 << 21,
	SkillSpc10 = 1 << 22,
};

inline ActionFlag operator~(ActionFlag a) { return (ActionFlag) ~(uint32_t)a; }
inline ActionFlag operator|(ActionFlag a, ActionFlag b) { return (ActionFlag)((uint32_t)a | (uint32_t)b); }
inline ActionFlag operator&(ActionFlag a, ActionFlag b) { return (ActionFlag)((uint32_t)a & (uint32_t)b); }
inline ActionFlag operator^(ActionFlag a, ActionFlag b) { return (ActionFlag)((uint32_t)a ^ (uint32_t)b); }
inline ActionFlag &operator|=(ActionFlag &a, ActionFlag b) { return (ActionFlag &)((uint32_t &)a |= (uint32_t)b); }
inline ActionFlag &operator&=(ActionFlag &a, ActionFlag b) { return (ActionFlag &)((uint32_t &)a &= (uint32_t)b); }
inline ActionFlag &operator^=(ActionFlag &a, ActionFlag b) { return (ActionFlag &)((uint32_t &)a ^= (uint32_t)b); }
