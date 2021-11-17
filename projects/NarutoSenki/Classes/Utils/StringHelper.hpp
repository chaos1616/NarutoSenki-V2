#pragma once
#include <string>

namespace std
{

inline std::string trim(const std::string &s)
{
	auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c) { return std::isspace(c); });
	auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c) { return std::isspace(c); })
					  .base();
	return wsback <= wsfront ? s : std::string(wsfront, wsback);
}

// TODO: std::trim_sub

inline bool stobool(const std::string &s)
{
	return s == "true";
}

inline bool stonull(const std::string &s)
{
	return s == "null";
}

} // namespace std
