#pragma once
#include "Defines.h"
#include "toml.hpp"

#define PARSER_NS_BEGIN  \
	namespace UnitParser \
	{
#define PARSER_NS_END }

PARSER_NS_BEGIN

struct ActionData
{
	using FrameVector = vector<pair<string, string>>;

	ActionFlag flag;
	bool hasData;

	string type;
	bool isDouble;
	u16 value;
	u16 rangeX;
	u16 rangeY;
	u16 cooldown;
	u16 combatPoint;

	FrameVector frames;
};

struct UnitMetadata
{
	string name;
	u32 hp;
	u16 width;
	u16 height;
	u16 speed;

	vector<ActionData> actions;

	bool getAction(ActionFlag flag, ActionData &action) noexcept
	{
		for (auto &actionData : actions)
		{
			if (actionData.flag == flag)
			{
				action = actionData;
				return true;
			}
		}
		return false;
	}
};

DETAIL_NS_BEGIN

// TODO: Make parser metadata cache

static const std::string nullstr;

static void ParseCoreData(const toml::value &v, UnitMetadata &metadata)
{
	metadata.name = toml::find<string>(v, "name");
	metadata.hp = toml::find<uint32_t>(v, "hp");
	metadata.width = toml::find_or<uint16_t>(v, "width", 0);
	metadata.height = toml::find_or<uint16_t>(v, "height", 0);
	metadata.speed = toml::find_or<uint16_t>(v, "speed", 224);
}

static void ParseAction(const toml::value &v, UnitMetadata &metadata)
{
	for (const auto &[key, value] : v.as_table())
	{
		if (key.empty() || !value.is_table() || value.size() == 0)
			continue;
		// parse data
		ActionData data = {
			.flag = ActionConstant::string2ActionFlag(key),
			.type = toml::find_or<string>(value, "type", ""),
			.value = toml::find_or<uint16_t>(value, "value", 0),
			.rangeX = toml::find_or<uint16_t>(value, "rangeX", 0),
			.rangeY = toml::find_or<uint16_t>(value, "rangeY", 0),
			.cooldown = toml::find_or<uint16_t>(value, "cd", 0),
			.combatPoint = toml::find_or<uint16_t>(value, "combatPoint", 0),
		};

		// parse frame
		auto frame = toml::find<vector<string>>(value, "frame");
		if (!frame.empty())
		{
			auto &frameVector = data.frames;
			frameVector.resize(frame.size());
			for (const auto &f : frame)
			{
				auto found = f.find_first_of('=', 1);
				if (found != string::npos) // parse event
				{
					auto eventName = f.substr(0, found);
					auto eventValue = f.substr(found + 1);
					frameVector.push_back(make_pair(eventName, f));
				}
				else
				{
					frameVector.push_back(make_pair(nullstr, f));
				}
			}
		}
		metadata.actions.push_back(data);
	}
}

DETAIL_NS_END

static inline UnitMetadata fromToml(const string &fname)
{
	const auto path = FileUtils::sharedFileUtils()->fullPathForFilename(fname.c_str());
	if (!FileUtils::sharedFileUtils()->isFileExist(path))
	{
		CCLOGERROR("[ERROR] UnitParser::fromToml not found file %s", path.c_str());
		return {};
	}
	const auto data = toml::parse(path);

	UnitMetadata metadata;
	detail::ParseCoreData(data, metadata);
	detail::ParseAction(data, metadata);
	return metadata;
}

PARSER_NS_END

#undef PARSER_NS_BEGIN
#undef PARSER_NS_END
