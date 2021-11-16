#pragma once
#include "CharacterBase.h"
#include "System/CommandSystem.hpp"

// Detailed implementation of Action module of unit base class

// NOTE: DO NOT FORMAT THIS FILE

#define SET_NATTACK_ACTION_DATA_FN(__Action) \
	_nAttackType = __Action.type;            \
	_nAttackValue = __Action.value;          \
	_nAttackRangeX = __Action.rangeX;        \
	_nAttackRangeY = __Action.rangeY;

#define SET_SKILL_ACTION_DATA_FN(__Id, __Action) \
	_sAttackType##__Id = __Action.type;          \
	_sAttackValue##__Id = __Action.value;        \
	_sAttackRangeX##__Id = __Action.rangeX;      \
	_sAttackRangeY##__Id = __Action.rangeY;      \
	_sAttackCD##__Id = __Action.cooldown;        \
	_sAttackCombatPoint##__Id = __Action.combatPoint;
// _sAttack##__Id##isDouble = __Action.isDouble;

#define SET_SPC_SKILL_ACTION_DATA_FN(__Id, __Action) \
	_spcAttackType##__Id = __Action.type;            \
	_spcAttackValue##__Id = __Action.value;          \
	_spcAttackRangeX##__Id = __Action.rangeX;        \
	_spcAttackRangeY##__Id = __Action.rangeY;        \
	_spcAttackCD##__Id = __Action.cooldown;

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
	case Command::setAttackBox:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setAttackBox, this, value));
		list.pushBack(call);
	}
	break;
	case Command::setSound:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setSound, this, value));
		list.pushBack(call);
	}
	break;
	case Command::setDSound:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setDSound, this, value));
		list.pushBack(call);
	}
	break;
	case Command::setDelay:
	{
		float delayTime = std::stoi(value);
		auto delay = DelayTime::create(delayTime / 100.0f);
		list.pushBack(delay);
	}
	break;
	case Command::setMove:
	{
		int moveLength = std::stoi(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::setMove, this, moveLength));
		list.pushBack(call);
	}
	break;
	case Command::setSkillEffect:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setSkillEffect, this, value));
		list.pushBack(call);
	}
	break;
	case Command::setJump:
	{
		bool jumpDirection = std::stobool(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::setJump, this, jumpDirection));
		list.pushBack(call);
	}
	break;
	case Command::setCharge:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::getCollider, this));
		list.pushBack(call);
		int moveLength = std::stoi(value);
		call = CallFunc::create(std::bind(&CharacterBase::setCharge, this, moveLength));
		list.pushBack(call);
	}
	break;
	case Command::setChargeB:
	{
		int moveLength = std::stoi(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::setChargeB, this, moveLength));
		list.pushBack(call);
	}
	break;
	case Command::setClone:
	{
		int cloneTime = std::stoi(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::setClone, this, cloneTime));
		list.pushBack(call);
	}
	break;
	case Command::setMon:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setMon, this, value));
		list.pushBack(call);
	}
	break;
	case Command::setFont:
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
	case Command::setBuff:
	{
		int buffValue = std::stoi(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::setBuff, this, buffValue));
		list.pushBack(call);
	}
	break;
	case Command::setCmd:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setCommand, this, value));
		list.pushBack(call);
	}
	break;
	case Command::setDestroy:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::dealloc, this));
		list.pushBack(call);
	}
	break;
	case Command::setBullet:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setBullet, this, value));
		list.pushBack(call);
	}
	break;
	case Command::setMonAttack:
	{
		int skillNum = std::stoi(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::setMonAttack, this, skillNum));
		list.pushBack(call);
	}
	break;
	case Command::setTrap:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setTrap, this, value));
		list.pushBack(call);
	}
	break;
	case Command::setActionResume:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setActionResume, this));
		list.pushBack(call);
	}
	break;
	case Command::setActionResume2:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setActionResume2, this));
		list.pushBack(call);
	}
	break;
	case Command::setShadow:
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
	case Command::setTransform:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setTransform, this));
		list.pushBack(call);
	}
	break;
	case Command::setOugis:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setOugis, this));
		list.pushBack(call);
	}
	break;
	case Command::stopJump:
	{
		int stopTime = std::stoi(value);
		auto call = CallFunc::create(std::bind(&CharacterBase::stopJump, this, stopTime));
		list.pushBack(call);
	}
	break;
	case Command::setFlipped:
	{
		auto call = CallFunc::create(std::bind(&CharacterBase::setCharFlip, this));
		list.pushBack(call);
	}
	default:
	{
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

	_actionMap.insert(action.flag, seq);
	// set action data
	if (action.flag >= ActionFlag::NAttack && action.flag <= ActionFlag::Spc03)
	{
		switch (action.flag)
		{
		case ActionFlag::NAttack:
			SET_NATTACK_ACTION_DATA_FN(action);
			break;
		case ActionFlag::Skill01:
			SET_SKILL_ACTION_DATA_FN(1, action);
			break;
		case ActionFlag::Skill02:
			SET_SKILL_ACTION_DATA_FN(2, action);
			break;
		case ActionFlag::Skill03:
			SET_SKILL_ACTION_DATA_FN(3, action);
			break;
		case ActionFlag::Skill04:
			SET_SKILL_ACTION_DATA_FN(4, action);
			break;
		case ActionFlag::Skill05:
			SET_SKILL_ACTION_DATA_FN(5, action);
			break;
		case ActionFlag::Spc01:
			SET_SPC_SKILL_ACTION_DATA_FN(1, action);
			break;
		case ActionFlag::Spc02:
			SET_SPC_SKILL_ACTION_DATA_FN(2, action);
			break;
		case ActionFlag::Spc03:
			SET_SPC_SKILL_ACTION_DATA_FN(3, action);
			break;
		default:
			break;
		}
	}

	// cleanup temp variables
	list.clear();

	__FOREACH_END
}

void CharacterBase::setAction(ActionFlag flags)
{
	if (hasFlag(flags, ActionFlag::Dead))
		setDeadAction(_actionMap.at(ActionFlag::Dead));
	if (hasFlag(flags, ActionFlag::Idle))
		setIdleAction(_actionMap.at(ActionFlag::Idle));
	if (hasFlag(flags, ActionFlag::Walk))
		setWalkAction(_actionMap.at(ActionFlag::Walk));
	if (hasFlag(flags, ActionFlag::Hurt))
		setHurtAction(_actionMap.at(ActionFlag::Hurt));
	if (hasFlag(flags, ActionFlag::AirHurt))
		setAirHurtAction(_actionMap.at(ActionFlag::AirHurt));
	if (hasFlag(flags, ActionFlag::Knockdown))
		setKnockdownAction(_actionMap.at(ActionFlag::Knockdown));
	if (hasFlag(flags, ActionFlag::Float))
		setFloatAction(_actionMap.at(ActionFlag::Float));
	if (hasFlag(flags, ActionFlag::NAttack))
		setNAttackAction(_actionMap.at(ActionFlag::NAttack));
	if (hasFlag(flags, ActionFlag::Skill01))
		setSkill1Action(_actionMap.at(ActionFlag::Skill01));
	if (hasFlag(flags, ActionFlag::Skill02))
		setSkill2Action(_actionMap.at(ActionFlag::Skill02));
	if (hasFlag(flags, ActionFlag::Skill03))
		setSkill3Action(_actionMap.at(ActionFlag::Skill03));
	if (hasFlag(flags, ActionFlag::Skill04))
		setSkill4Action(_actionMap.at(ActionFlag::Skill04));
	if (hasFlag(flags, ActionFlag::Skill05))
		setSkill5Action(_actionMap.at(ActionFlag::Skill05));
}

// TODO: Impl in header file
// template <ActionFlag from, ActionFlag to>
// inline constexpr void CharacterBase::setActionTo(const SkillData &data)
// {
// 	setActionTo<from, to>();
// 	setSkillData<from, to>();
// }

// TODO: Impl in header file
// template <ActionFlag from, ActionFlag to>
// inline constexpr void CharacterBase::setActionAndDataTo()
// {
// }

// template <ActionFlag from, ActionFlag to>
// constexpr void CharacterBase::setSkillDataTo(const SkillData &data)
// {
// }

#undef SET_NATTACK_ACTION_DATA_FN
#undef SET_SKILL_ACTION_DATA_FN
#undef SET_SPC_SKILL_ACTION_DATA_FN
