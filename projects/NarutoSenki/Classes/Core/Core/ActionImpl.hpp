#pragma once
#include "CharacterBase.h"

// Detailed implementation of Action module of unit base class

#define SET_NATTACK_ACTION_DATA_FN(__Skill) \
	{                                       \
		_nAttackType = __Skill.type;        \
		_nAttackValue = __Skill.value;      \
		_nAttackRangeX = __Skill.rangeX;    \
		_nAttackRangeY = __Skill.rangeY;    \
	}

#define SET_SKILL_ACTION_DATA_FN(__Id, __Skill)          \
	{                                                    \
		_sAttackType##__Id = __Skill.type;               \
		_sAttackValue##__Id = __Skill.value;             \
		_sAttackRangeX##__Id = __Skill.rangeX;           \
		_sAttackRangeY##__Id = __Skill.rangeY;           \
		_sAttackCD##__Id = __Skill.cooldown;             \
		_sAttackCombatPoint##__Id = __Skill.combatPoint; \
		_sAttack##__Id##isDouble = __Skill.isDouble;     \
	}

#define SET_SPC_SKILL_ACTION_DATA_FN(__Id, __Skill) \
	{                                               \
		_spcAttackType##__Id = __Skill.type;        \
		_spcAttackValue##__Id = __Skill.value;      \
		_spcAttackRangeX##__Id = __Skill.rangeX;    \
		_spcAttackRangeY##__Id = __Skill.rangeY;    \
		_spcAttackCD##__Id = __Skill.cooldown;      \
	}

namespace UnitEvent
{

mk_hconst(setActionResume);
mk_hconst(setActionResume2);
mk_hconst(setAttackBox);
mk_hconst(setBuff);
mk_hconst(setBullet);
mk_hconst(setCharge);
mk_hconst(setChargeB);
mk_hconst(setClone);
mk_hconst(setCmd);
mk_hconst(setDelay);
mk_hconst(setDestroy);
mk_hconst(setFlipped);
mk_hconst(setFont);
mk_hconst(setJump);
mk_hconst(stopJump);
mk_hconst(setMon);
mk_hconst(setMonAttack);
mk_hconst(setMove);
mk_hconst(setOugis);
mk_hconst(setShadow);
mk_hconst(setSkillEffect);
mk_hconst(setSound);
mk_hconst(setDSound);
mk_hconst(setTransform);
mk_hconst(setTrap);

} // namespace UnitEvent

void CharacterBase::genActionBy(const UnitMetadata &data)
{
	Vector<SpriteFrame *> spriteFrames;
	Vector<FiniteTimeAction *> list;
	Animation *tempAnimation;
	FiniteTimeAction *tempAction;
	FiniteTimeAction *seq;

	__FOREACH(auto const &action, data.actions)

	const auto fdelay = 1.0f / action.info.fps;
	const auto onlyOneSprite = action.frames.size() == 1 && action.frames.at(0).first.empty();

	__FOREACH(const auto &f, action.frames)

	const string key = f.first;
	const string value = f.second;
	if (key.empty())
	{
		auto frame = getSpriteFrame(value);
		spriteFrames.pushBack(frame);
		continue;
	}
	// else
	// {
	tempAnimation = Animation::createWithSpriteFrames(spriteFrames, fdelay);
	tempAction = Animate::create(tempAnimation);
	list.pushBack(tempAction);

	switch (HashUtils::hash32(key))
	{
	case UnitEvent::setAttackBox:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setAttackBox, this, value));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setSound:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setSound, this, value));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setDSound:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setDSound, this, value));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setDelay:
	{
		float delayTime = std::stoi(value);
		auto delay = DelayTime::create(delayTime / 100.0f);
		list.pushBack(delay);
	}
	break;
	case UnitEvent::setMove:
	{
		int moveLength = std::stoi(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::setMove, this, moveLength));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setSkillEffect:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setSkillEffect, this, value));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setJump:
	{
		bool jumpDirection = std::stobool(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::setJump, this, jumpDirection));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setCharge:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::getCollider, this));
		list.pushBack(call);
		int moveLength = std::stoi(value);
		call = CallFunc::create(std::bind(&CharacterBase::setCharge, this, moveLength));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setChargeB:
	{
		int moveLength = std::stoi(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::setChargeB, this, moveLength));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setClone:
	{
		int cloneTime = std::stoi(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::setClone, this, cloneTime));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setMon:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setMon, this, value));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setFont:
	{
		// const char *split = ",";
		// char *p;
		// char str[] = char[strlen(value)];
		// strcpy(str, value);
		// p = strtok(str, split);
		// vector<string> valueVector;
		// while (p != nullptr)
		// {
		// 	valueVector.push_back(p);
		// 	p = strtok(nullptr, split);
		// }

		// auto call = CallFunc::create(std::bind(&CharacterBase::setFontEffect, this, valueVector));
		// list.pushBack(call);
	}
	break;
	case UnitEvent::setBuff:
	{
		int buffValue = std::stoi(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::setBuff, this, buffValue));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setCmd:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setCommand, this, value));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setDestroy:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::dealloc, this));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setBullet:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setBullet, this, value));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setMonAttack:
	{
		int skillNum = std::stoi(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::setMonAttack, this, skillNum));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setTrap:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setTrap, this, value));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setActionResume:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setActionResume, this));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setActionResume2:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setActionResume2, this));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setShadow:
	{
		if (spriteFrames.size() == 0)
		{
			CCLOGERROR("`setShadow` can only be used after at least one sprite");
		}
		else
		{
			auto frame = spriteFrames.at(spriteFrames.size() - 1);
			auto call = CallFunc::create(std::bind(&CharacterBase::setShadow, this, frame));
			list.pushBack(call);
		}
	}
	break;
	case UnitEvent::setTransform:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setTransform, this));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setOugis:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setOugis, this));
		list.pushBack(call);
	}
	break;
	case UnitEvent::stopJump:
	{
		int stopTime = std::stoi(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::stopJump, this, stopTime));
		list.pushBack(call);
	}
	break;
	case UnitEvent::setFlipped:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setCharFlip, this));
		list.pushBack(call);
	}
	default:
	{
		CCLOGERROR("Does not support UnitEvent %s = %s", key.c_str(), value.c_str());
	}
	break;
	}

	spriteFrames.clear();
	// }

	__FOREACH_END

	if (!spriteFrames.empty())
	{
		tempAnimation = Animation::createWithSpriteFrames(spriteFrames, fdelay);
		tempAction = Animate::create(tempAnimation);
		list.pushBack(tempAction);
		spriteFrames.clear();
	}

	if (action.info.isLoop)
	{
		if (onlyOneSprite)
			seq = Sequence::create(list);
		else
			seq = RepeatForever::create(Sequence::create(list));
	}
	else
	{
		if (action.info.isReturnToIdle)
		{
			auto call = CallFunc::create(std::bind(&CharacterBase::idle, this));
			list.pushBack(call);
		}

		seq = Sequence::create(list);
	}

	_actionFlag |= action.flag;
	_actionMap.insert(action.flag, seq);

	// cleanup temp variables
	list.clear();

	__FOREACH_END

	if (!data.skills.empty())
	{
		_skills = data.skills;
		// set action data
		if (_actionFlag != ActionFlag::None)
			setSkillData(_actionFlag);
	}
}

void CharacterBase::setAction(ActionFlag flags)
{
	if (hasFlag(flags, ActionFlag::Dead)) setDeadAction(_actionMap.at(ActionFlag::Dead));
	if (hasFlag(flags, ActionFlag::Idle)) setIdleAction(_actionMap.at(ActionFlag::Idle));
	if (hasFlag(flags, ActionFlag::Walk)) setWalkAction(_actionMap.at(ActionFlag::Walk));
	if (hasFlag(flags, ActionFlag::Hurt)) setHurtAction(_actionMap.at(ActionFlag::Hurt));
	if (hasFlag(flags, ActionFlag::AirHurt)) setAirHurtAction(_actionMap.at(ActionFlag::AirHurt));
	if (hasFlag(flags, ActionFlag::Knockdown)) setKnockdownAction(_actionMap.at(ActionFlag::Knockdown));
	if (hasFlag(flags, ActionFlag::Float)) setFloatAction(_actionMap.at(ActionFlag::Float));
	if (hasFlag(flags, ActionFlag::NAttack)) setNAttackAction(_actionMap.at(ActionFlag::NAttack));
	if (hasFlag(flags, ActionFlag::Skill01)) setSkill1Action(_actionMap.at(ActionFlag::Skill01));
	if (hasFlag(flags, ActionFlag::Skill02)) setSkill2Action(_actionMap.at(ActionFlag::Skill02));
	if (hasFlag(flags, ActionFlag::Skill03)) setSkill3Action(_actionMap.at(ActionFlag::Skill03));
	if (hasFlag(flags, ActionFlag::Skill04)) setSkill4Action(_actionMap.at(ActionFlag::Skill04));
	if (hasFlag(flags, ActionFlag::Skill05)) setSkill5Action(_actionMap.at(ActionFlag::Skill05));
}

void CharacterBase::setSkillData(ActionFlag flags)
{
	if (hasFlag(flags, ActionFlag::NAttack)) setSkillData(ActionFlag::NAttack, getSkillData(ActionFlag::NAttack));
	if (hasFlag(flags, ActionFlag::Skill01)) setSkillData(ActionFlag::Skill01, getSkillData(ActionFlag::Skill01));
	if (hasFlag(flags, ActionFlag::Skill02)) setSkillData(ActionFlag::Skill02, getSkillData(ActionFlag::Skill02));
	if (hasFlag(flags, ActionFlag::Skill03)) setSkillData(ActionFlag::Skill03, getSkillData(ActionFlag::Skill03));
	if (hasFlag(flags, ActionFlag::Skill04)) setSkillData(ActionFlag::Skill04, getSkillData(ActionFlag::Skill04));
	if (hasFlag(flags, ActionFlag::Skill05)) setSkillData(ActionFlag::Skill05, getSkillData(ActionFlag::Skill05));
	if (hasFlag(flags, ActionFlag::Spc01)) setSkillData(ActionFlag::Spc01, getSkillData(ActionFlag::Spc01));
	if (hasFlag(flags, ActionFlag::Spc02)) setSkillData(ActionFlag::Spc02, getSkillData(ActionFlag::Spc02));
	if (hasFlag(flags, ActionFlag::Spc03)) setSkillData(ActionFlag::Spc03, getSkillData(ActionFlag::Spc03));
}

void CharacterBase::setSkillData(ActionFlag flag, const SkillData &data)
{
	if (flag == ActionFlag::NAttack) SET_NATTACK_ACTION_DATA_FN(data)
	else if (flag == ActionFlag::Skill01) SET_SKILL_ACTION_DATA_FN(1, data)
	else if (flag == ActionFlag::Skill02) SET_SKILL_ACTION_DATA_FN(2, data)
	else if (flag == ActionFlag::Skill03) SET_SKILL_ACTION_DATA_FN(3, data)
	else if (flag == ActionFlag::Skill04) SET_SKILL_ACTION_DATA_FN(4, data)
	else if (flag == ActionFlag::Skill05) SET_SKILL_ACTION_DATA_FN(5, data)
	else if (flag == ActionFlag::Spc01) SET_SPC_SKILL_ACTION_DATA_FN(1, data)
	else if (flag == ActionFlag::Spc02) SET_SPC_SKILL_ACTION_DATA_FN(2, data)
	else if (flag == ActionFlag::Spc03) SET_SPC_SKILL_ACTION_DATA_FN(3, data)
}

void CharacterBase::setSkillDataTo(ActionFlag from, ActionFlag to)
{
	if (from == ActionFlag::NAttack) setSkillData(from, getSkillData(to));
	else if (from == ActionFlag::Skill01) setSkillData(from, getSkillData(to));
	else if (from == ActionFlag::Skill02) setSkillData(from, getSkillData(to));
	else if (from == ActionFlag::Skill03) setSkillData(from, getSkillData(to));
	else if (from == ActionFlag::Skill04) setSkillData(from, getSkillData(to));
	else if (from == ActionFlag::Skill05) setSkillData(from, getSkillData(to));
	else if (from == ActionFlag::Spc01) setSkillData(from, getSkillData(to));
	else if (from == ActionFlag::Spc02) setSkillData(from, getSkillData(to));
	else if (from == ActionFlag::Spc03) setSkillData(from, getSkillData(to));
}

#undef SET_NATTACK_ACTION_DATA_FN
#undef SET_SKILL_ACTION_DATA_FN
#undef SET_SPC_SKILL_ACTION_DATA_FN
