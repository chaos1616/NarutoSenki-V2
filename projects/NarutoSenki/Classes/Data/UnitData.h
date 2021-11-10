#pragma once
#include "Defines.h"

// Tile size
constexpr int kTileSize = 32;
constexpr int kOneHalfTileSize = kTileSize * 1.5f;

// It was half window width before
constexpr int kAttackRange = kTileSize * 9;

struct HeroData
{
	string name;
	Role role;
	Group group;

	Vec2 spawnPoint;

	bool isInit = false;

	inline void setSpawnPoint(Vec2 &&sp)
	{
		spawnPoint.x = sp.x;
		spawnPoint.y = sp.y;
	}
};

enum class UnitKind
{
	Ninja,
	Flog,
	Tower,
	Skill,	// Old name: Bullet
	Summon, // Old name: Monster
};

// Unit Action Constant

namespace ActionConstant
{
	enum class AnimationType : uint8_t
	{
		Regular,
		Idle,
		Walk,
		Knockdown,
		Skill,
	};

	struct AnimationInfo
	{
		uint16_t fps;
		bool isRepeat;
		bool isReturnToIdle;
	};

	constexpr AnimationInfo Regular = {10, false, false};
	constexpr AnimationInfo Idle = {5, true, false};
	constexpr AnimationInfo Walk = {10, true, false};
	constexpr AnimationInfo Knockdown = {10, false, true};
	constexpr AnimationInfo Skill = {10, false, true};
} // namespace ActionConstant
