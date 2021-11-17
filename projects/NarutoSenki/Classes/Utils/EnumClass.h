#pragma once
#include <type_traits>

// NOTE: Enabled bit mask operators for all integer types enums

template <typename T, typename V>
constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>> && std::is_integral_v<V>, V>
operator/(T __lhs, V __rhs) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<_Base>(__lhs) / __rhs;
}

template <typename T, typename V>
constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>> && std::is_integral_v<V>, V>
operator%(T __lhs, V __rhs) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<_Base>(__lhs) % __rhs;
}

template <typename T>
constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T>
operator~(T __lhs) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<T>(~static_cast<_Base>(__lhs));
}

template <typename T>
constexpr std::enable_if_t<std::is_integral_v<std::underlying_type_t<T>>, T>
operator|(T __lhs, T __rhs) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<T>(static_cast<_Base>(__lhs) | static_cast<_Base>(__rhs));
}

template <typename T>
constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T>
operator&(T __lhs, T __rhs) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<T>(static_cast<_Base>(__lhs) & static_cast<_Base>(__rhs));
}

template <typename T>
constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T>
operator^(T __lhs, T __rhs) noexcept
{
	using _Base = std::underlying_type_t<T>;
	return static_cast<T>(static_cast<_Base>(__lhs) ^ static_cast<_Base>(__rhs));
}

template <typename T>
constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T &>
operator|=(T &__lhs, T __rhs) noexcept
{
	return __lhs = __lhs | __rhs;
}

template <typename T>
constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T &>
operator&=(T &__lhs, T __rhs) noexcept
{
	return __lhs = __lhs & __rhs;
}

template <typename T>
constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T &>
operator^=(T &__lhs, T __rhs) noexcept
{
	return __lhs = __lhs ^ __rhs;
}

template <typename T>
constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, bool>
hasFlag(T __lhs, T __rhs) noexcept
{
	return (__lhs & __rhs) != T{};
}

template <typename T>
constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, bool>
hasAllFlags(T __lhs, T flags) noexcept
{
	return (__lhs & flags) == flags;
}

template <typename T>
constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, bool>
notHasFlag(T __lhs, T __rhs) noexcept
{
	return (__lhs & __rhs) == T{};
}

template <typename T>
constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, void>
setFlag(T &__lhs, T __rhs) noexcept
{
	__lhs |= __rhs;
}

template <typename T>
constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, void>
unsetFlag(T &__lhs, T __rhs) noexcept
{
	__lhs &= ~__rhs;
}
