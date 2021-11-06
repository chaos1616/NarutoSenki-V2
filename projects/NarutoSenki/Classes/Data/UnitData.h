#pragma once
#include <Defines.h>

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

struct ActionData
{
	using FrameVector = vector<pair<const char *, const char *>>;

public:
	string name;
	bool hasData;

	string attackType;
	u16 attackValue;
	u16 attackRangeX;
	u16 attackRangeY;
	u16 cooldown;
	u32 combatPoint;

	FrameVector frames;
};

struct UnitMetadata
{
public:
	UnitKind kind;

	string name;
	u32 hp;
	u16 width;
	u16 height;
	u16 speed;

	vector<ActionData> actions;

	static UnitMetadata &Parse(const string &filePath)
	{
		UnitMetadata metadata;

		return metadata;
	}

private:
};
