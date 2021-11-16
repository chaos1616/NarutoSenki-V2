#pragma once

// make a constexpr
#define mk_const(var) constexpr auto var = #var

// make a hash constexpr
#define mk_hconst(var) constexpr auto var = HashUtils::hash32(#var)
