#pragma once
#include <Defines.h>

struct HeroData
{
public:
	string character;
	string role;
	string group;

	CCPoint spawnPoint;
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

	static UnitMetadata &Parse(const std::string &filePath)
	{
		UnitMetadata metadata;

		return metadata;
	}

private:
};
