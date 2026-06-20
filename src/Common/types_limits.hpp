#pragma once

#include <limits>

template <typename T>
constexpr auto type_max = std::numeric_limits<T>::max();

template <typename T>
constexpr auto type_min = -std::numeric_limits<T>::max();

template <typename T>
constexpr auto type_zero = std::numeric_limits<T>::min();

template <typename T>
constexpr auto type_epsilon = std::numeric_limits<T>::epsilon();

constexpr int int_max = type_max<int>;
constexpr int int_min = type_min<int>;
constexpr int int_zero = type_zero<int>;

constexpr float flt_max = type_max<float>;
constexpr float flt_min = type_min<float>;
constexpr float flt_zero = type_zero<float>;
constexpr float flt_eps = type_epsilon<float>;

constexpr double dbl_max = type_max<double>;
constexpr double dbl_min = type_min<double>;
constexpr double dbl_zero = type_zero<double>;
constexpr double dbl_eps = type_epsilon<double>;
