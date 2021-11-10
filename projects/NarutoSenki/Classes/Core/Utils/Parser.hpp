#pragma once
#include "Defines.h"
#include "toml.hpp"

namespace UnitParser
{
	static const std::string _emptystring;
	static const std::string &nullstr = _emptystring;

	struct ActionData
	{
		using FrameVector = vector<pair<string, string>>;

		string name;
		bool hasData;

		string attackType;
		bool isDouble;
		u16 attackValue;
		u16 attackRangeX;
		u16 attackRangeY;
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

		bool getAction(const string &name, ActionData &action)
		{
			for (auto &actionData : actions)
			{
				if (actionData.name == name)
				{
					action = actionData;
					return true;
				}
			}
			return false;
		}
	};

	static void ParseCoreData(const toml::value &v, UnitMetadata &metadata)
	{
		metadata.name = toml::find<string>(v, "name");
		metadata.hp = toml::find<uint32_t>(v, "hp");
		metadata.width = toml::find_or<uint16_t>(v, "width", 0);
		metadata.height = toml::find_or<uint16_t>(v, "height", 0);
		metadata.speed = toml::find_or<uint16_t>(v, "speed", 0);
	}

	static void ParseAction(const toml::value &v, UnitMetadata &metadata)
	{
		for (const auto &[key, value] : v.as_table())
		{
			if (key.empty() || !value.is_table() || value.size() == 0)
				continue;
			auto action = value;
			// parse data
			ActionData data;
			data.name = key;
			data.attackType = toml::find_or<string>(action, "attackType", "");
			data.attackValue = toml::find_or<uint16_t>(action, "attackValue", 0);
			data.attackRangeX = toml::find_or<uint16_t>(action, "attackRangeX", 0);
			data.attackRangeY = toml::find_or<uint16_t>(action, "attackRangeY", 0);
			data.cooldown = toml::find_or<uint16_t>(action, "cooldown", 0);
			data.combatPoint = toml::find_or<uint16_t>(action, "combatPoint", 0);

			// parse frame
			auto frame = toml::find<vector<string>>(action, "frame");
			if (!frame.empty())
			{
				for (const auto &f : frame)
				{
					auto found = f.find_first_of("=", 1);
					if (found != string::npos) // parse event
					{
						auto eventName = f.substr(0, found);
						auto eventValue = f.substr(found + 1);
						data.frames.push_back(make_pair(eventName, f));
					}
					else
					{
						data.frames.push_back(make_pair(nullstr, f));
					}
				}
			}
			metadata.actions.push_back(data);
		}
	}

	static UnitMetadata fromToml(const string &fname)
	{
		const auto data = toml::parse(fname);

		UnitMetadata metadata;
		ParseCoreData(data, metadata);
		ParseAction(data, metadata);
		return metadata;
	}
}
