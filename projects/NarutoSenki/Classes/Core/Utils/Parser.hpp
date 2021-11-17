#pragma once
#include "Data/UnitData.h"
#include "Utils/TomlHelper.hpp"

struct ActionData
{
	using FrameVector = vector<pair<string, string>>;

	ActionFlag flag;
	// bool hasData;

	string type;
	u16 value;
	u16 rangeX;
	u16 rangeY;
	u16 cooldown;
	u16 combatPoint;
	// bool isDouble;

	ActionConstant::AnimationInfo info;
	FrameVector frames;
};

struct UnitMetadata
{
	string name;
	u32 hp;
	// u16 width;
	// u16 height;
	u16 speed;

	bool enableHPBar;
	// i16 hpBarX;
	i16 hpBarY;

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

namespace UnitParser
{

class ParserCache
{
private:
	static inline vector<UnitMetadata> _cache;

public:
	static inline void clear() noexcept
	{
		vector<UnitMetadata>().swap(_cache);
	}

	static inline void set(const UnitMetadata &data)
	{
		_cache.push_back(data);
	}

	static inline bool get(const string &name, UnitMetadata &metadata) noexcept
	{
		for (const auto &data : _cache)
		{
			if (data.name == name)
			{
				metadata = data;
				return true;
			}
		}
		return false;
	}
};

namespace detail
{

enum Keyword : char
{
	Override = '@',
};

// TODO: Make parser metadata cache

static const std::string nullstr;

static void ParseCoreData(toml::value &v, UnitMetadata &metadata)
{
	auto &tab = v.as_table();
	const auto end = tab.end();

	tomlex::try_set(tab, "name", metadata.name);
	tomlex::try_set(tab, "hp", metadata.hp);
	// parse hp bar properties
	if (auto hpBarIter = tab.find("hpBar"); hpBarIter != end)
	{
		metadata.enableHPBar = true;
		const auto &hpBar = hpBarIter->second.as_table();
		// tomlex::try_set_or<i16>(hpBar, "x", metadata.hpBarX, 0);
		tomlex::try_set_or<i16>(hpBar, "y", metadata.hpBarY, 0);
		tab.erase(hpBarIter);
	}
	else
	{
		metadata.enableHPBar = false;
	}
	tomlex::try_set_or<u16>(tab, "speed", metadata.speed, kDefaultSpeed);
}

static void ParseAction(toml::value &v, UnitMetadata &metadata)
{
	for (const auto &[key, value] : v.as_table())
	{
		if (key.empty() || !value.is_table() || value.size() == 0)
			continue;
		auto flag = ActionConstant::string2ActionFlag(key);
		if (flag == ActionFlag::None)
		{
			CCLOGERROR("Does not support action `%s`", key.c_str());
			continue;
		}
		// parse data
		const auto &tab = value.as_table();
		const auto end = tab.end();

		ActionData data = {
			.flag = flag,
		};
		tomlex::try_set(tab, "type", data.type);
		tomlex::try_set_or<u16>(tab, "value", data.value, 0);
		tomlex::try_set_or<u16>(tab, "rangeX", data.rangeX, 0);
		tomlex::try_set_or<u16>(tab, "rangeY", data.rangeY, 0);
		tomlex::try_set_or<u16>(tab, "cd", data.cooldown, 0);
		tomlex::try_set_or<u16>(tab, "combatPoint", data.combatPoint, 0);
		// parse animation data
		if (auto animIter = tab.find("anim"); animIter != end)
		{
			const auto &anim = animIter->second.as_table();
			if (auto base = anim.find("base"); base != anim.end())
			{
				auto baseAnimType = ActionConstant::animBaseType2ActionFlag(base->second.as_string());
				if (baseAnimType != ActionFlag::None)
					flag = baseAnimType;
				else
					CCLOGERROR("Does not support override `%s` animation", data.type.c_str());
			}
			const auto &defaultInfo = ActionConstant::getAnimDataByActionFlag(flag);
			tomlex::try_set_or<uint8_t>(anim, "fps", data.info.fps, defaultInfo.fps);
			tomlex::try_set_or<bool>(anim, "loop", data.info.isLoop, defaultInfo.isLoop);
			if (!data.info.isLoop)
				tomlex::try_set_or<bool>(anim, "returnIdle", data.info.isReturnToIdle, defaultInfo.isReturnToIdle);
		}
		else
		{
			// set default animation config
			data.info = ActionConstant::getAnimDataByActionFlag(flag);
		}

		// parse frame data
		if (auto frameIter = tab.find("frame"); frameIter != end)
		{
			const auto &frame = frameIter->second.as_array();
			auto &frameVector = data.frames;
			frameVector.resize(frame.size());
			size_t i = 0;
			for (const auto &_ : frame)
			{
				const string &f = _.as_string();
				auto found = f.find_first_of('=', 1);
				if (found != string::npos) // parse event
				{
					auto eventName = std::trim(f.substr(0, found));
					auto eventValue = std::trim(f.substr(found + 1, f.length() - found - 1));
					frameVector[i++] = make_pair(eventName, eventValue);
				}
				else
				{
					frameVector[i++] = make_pair(nullstr, f);
				}
			}
		}
		metadata.actions.push_back(data);
	}
}

} // namespace detail

static inline bool fromCache(const string &unitName, UnitMetadata &metadata)
{
	return ParserCache::get(unitName, metadata);
}

static inline UnitMetadata fromToml(const string &fname, bool cache = false)
{
	const auto path = FileUtils::sharedFileUtils()->fullPathForFilename(fname.c_str());
	if (!FileUtils::sharedFileUtils()->isFileExist(path))
	{
		CCLOGERROR("[ERROR] UnitParser::fromToml not found file %s", path.c_str());
		return {};
	}
	auto data = toml::parse(path);

	UnitMetadata metadata;
	detail::ParseCoreData(data, metadata);
	detail::ParseAction(data, metadata);
	if (cache)
		ParserCache::set(metadata);
	return metadata;
}

} // namespace UnitParser
