#pragma once
#include <Defines.h>

// Tile size
static const int kTileSize = 32;
static const int kOneHalfTileSize = kTileSize * 1.5f;

// It was half window width before
static const int kAttackRange = kTileSize * 9;

struct HeroData
{
public:
	string character;
	string role;
	string group;

	CCPoint spawnPoint;

	bool isInit = false;
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
