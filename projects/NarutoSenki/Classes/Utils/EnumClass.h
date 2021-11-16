#pragma once
#include <type_traits>

// NOTE: Enabled bit mask operators for all integer types enums

template <typename T, typename V>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>> && std::is_integral_v<V>, V>
operator/(T a, V b) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<_Base>(a) / b;
}

template <typename T, typename V>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>> && std::is_integral_v<V>, V>
operator%(T a, V b) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<_Base>(a) % b;
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T>
operator~(T a) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<T>(~static_cast<_Base>(a));
}

template <typename T>
inline constexpr std::enable_if_t<std::is_integral_v<std::underlying_type_t<T>>, T>
operator|(T a, T b) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<T>(static_cast<_Base>(a) | static_cast<_Base>(b));
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T>
operator&(T a, T b) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<T>(static_cast<_Base>(a) & static_cast<_Base>(b));
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T>
operator^(T a, T b) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<T>(static_cast<_Base>(a) ^ static_cast<_Base>(b));
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T &>
operator|=(T &a, T b) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return reinterpret_cast<T &>(reinterpret_cast<_Base &>(a) |= static_cast<_Base>(b));
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T &>
operator&=(T &a, T b) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return reinterpret_cast<T &>(reinterpret_cast<_Base &>(a) &= static_cast<_Base>(b));
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T &>
operator^=(T &a, T b) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return reinterpret_cast<T &>(reinterpret_cast<_Base &>(a) ^= static_cast<_Base>(b));
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, bool>
hasFlag(T a, T b) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<_Base>(a & b) != static_cast<_Base>(0);
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, bool>
notHasFlag(T a, T b) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<_Base>(a & b) == static_cast<_Base>(0);
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, void>
setFlag(T &a, T b) noexcept
{
	a |= b;
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, void>
unsetFlag(T &a, T b) noexcept
{
	a &= ~b;
}
