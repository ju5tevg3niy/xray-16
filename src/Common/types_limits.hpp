#pragma once

#include <limits>

template <typename T>
constexpr auto type_max = std::numeric_limits<T>::max();

template <typename T>
constexpr auto type_min = -std::numeric_limits<T>::max();

constexpr float flt_max = type_max<float>;
constexpr float flt_min = type_min<float>;
