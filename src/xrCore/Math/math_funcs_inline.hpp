#pragma once
#include <cmath>
#include "Common/Platform.hpp"
#include "Common/types.hpp"
#include "xrCore/Math/bitwise.hpp"
#include "xrCore/Math/constants.hpp"

inline float _abs(float x) noexcept {
  return fabsf(x);
}

inline float _sqrt(float x) noexcept {
  return sqrtf(x);
}

inline float _sin(float x) noexcept {
  return sinf(x);
}

inline float _cos(float x) noexcept {
  return cosf(x);
}

inline double _abs(double x) noexcept {
  return fabs(x);
}

inline double _sqrt(double x) noexcept {
  return sqrt(x);
}

inline double _sin(double x) noexcept {
  return sin(x);
}

inline double _cos(double x) noexcept {
  return cos(x);
}

// comparisions
inline bool fsimilar(float a, float b, float cmp = EPS) {
  return _abs(a - b) < cmp;
}

inline bool dsimilar(double a, double b, double cmp = EPS) {
  return _abs(a - b) < cmp;
}

inline bool fis_zero(float val, float cmp = EPS_S) noexcept {
  return _abs(val) < cmp;
}

inline bool dis_zero(double val, double cmp = EPS_S) noexcept {
  return _abs(val) < cmp;
}

// degree to radians and vice-versa
constexpr float deg2rad(float val) noexcept {
  return val * M_PI / 180;
}

constexpr double deg2rad(double val) noexcept {
  return val * M_PI / 180;
}

constexpr float rad2deg(float val) noexcept {
  return val * 180 / M_PI;
}

constexpr double rad2deg(double val) noexcept {
  return val * 180 / M_PI;
}

// clamping/snapping
template <class T>
constexpr void clamp(T& val, const T& _low, const T& _high) noexcept {
  if (val < _low)
    val = _low;
  else if (val > _high)
    val = _high;
}

// XXX: Check usages and provide overloads for native types where arguments are
// NOT references.
template <class T>
constexpr T clampr(const T& val, const T& _low, const T& _high) noexcept {
  if (val < _low)
    return _low;
  if (val > _high)
    return _high;
  return val;
}

inline float snapto(float value, float snap) {
  if (snap <= 0.f)
    return value;
  return float(iFloor((value + (snap * 0.5f)) / snap)) * snap;
}

#ifdef abs
#undef abs
#endif

#ifdef _MIN
#undef _MIN
#endif

#ifdef _MAX
#undef _MAX
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

// generic
template <class T>
IC T _min(T a, T b) {
  return a < b ? a : b;
}

template <class T>
IC T _max(T a, T b) {
  return a > b ? a : b;
}

template <class T>
IC T _sqr(T a) {
  return a * a;
}

IC bool _valid(const float x) noexcept {
  // check for: Signaling NaN, Quiet NaN, Negative infinity ( ???INF), Positive
  // infinity (+INF), Negative denormalized, Positive denormalized
#if defined(XR_PLATFORM_WINDOWS) && defined(XR_COMPILER_MSVC)
#if defined(XR_ARCHITECTURE_X64)
  const int cls = _fpclassf(x);
#else
  const int cls = _fpclass(static_cast<double>(x));
#endif  // XR_ARCHITECTURE_X64
  if (cls & (_FPCLASS_SNAN + _FPCLASS_QNAN + _FPCLASS_NINF + _FPCLASS_PINF +
             _FPCLASS_ND + _FPCLASS_PD))
    return false;
#else
  const int cls = std::fpclassify(x);
  switch (cls) {
    case FP_NAN:
    case FP_INFINITE:
    case FP_SUBNORMAL:
      return false;
    default:
      break;
  }

    /* *****other cases are*****
    _FPCLASS_NN Negative normalized non-zero
    _FPCLASS_NZ Negative zero ( ??? 0)
    _FPCLASS_PZ Positive 0 (+0)
    _FPCLASS_PN Positive normalized non-zero
    */
#endif
  return true;
}

// double
IC bool _valid(const double x) {
  // check for: Signaling NaN, Quiet NaN, Negative infinity ( ???INF), Positive
  // infinity (+INF), Negative denormalized, Positive denormalized
#if defined(XR_PLATFORM_WINDOWS) && defined(XR_COMPILER_MSVC)
  const int cls = _fpclass(x);
  if (cls & (_FPCLASS_SNAN + _FPCLASS_QNAN + _FPCLASS_NINF + _FPCLASS_PINF +
             _FPCLASS_ND + _FPCLASS_PD))
    return false;
#else
  const int cls = std::fpclassify(x);
  switch (cls) {
    case FP_NAN:
    case FP_INFINITE:
    case FP_SUBNORMAL:
      return false;
    default:
      break;
  }
    /* *****other cases are*****
    _FPCLASS_NN Negative normalized non-zero
    _FPCLASS_NZ Negative zero ( ??? 0)
    _FPCLASS_PZ Positive 0 (+0)
    _FPCLASS_PN Positive normalized non-zero
    */
#endif
  return true;
}

// XXX: "magic" specializations, that really require profiling to see if they
// are worth this effort. int8
IC s8 _abs(s8 x) {
  return (x >= 0) ? x : s8(-x);
}

IC s8 _min(s8 x, s8 y) {
  return y + ((x - y) & ((x - y) >> (sizeof(s8) * 8 - 1)));
}

IC s8 _max(s8 x, s8 y) {
  return x - ((x - y) & ((x - y) >> (sizeof(s8) * 8 - 1)));
}

// unsigned int8
IC u8 _abs(u8 x) {
  return x;
}

// int16
IC s16 _abs(s16 x) {
  return (x >= 0) ? x : s16(-x);
}

IC s16 _min(s16 x, s16 y) {
  return y + ((x - y) & ((x - y) >> (sizeof(s16) * 8 - 1)));
}

IC s16 _max(s16 x, s16 y) {
  return x - ((x - y) & ((x - y) >> (sizeof(s16) * 8 - 1)));
}

// unsigned int16
IC u16 _abs(u16 x) {
  return x;
}

// int32
IC s32 _abs(s32 x) {
  return (x >= 0) ? x : s32(-x);
}

IC s32 _min(s32 x, s32 y) {
  return y + ((x - y) & ((x - y) >> (sizeof(s32) * 8 - 1)));
}

IC s32 _max(s32 x, s32 y) {
  return x - ((x - y) & ((x - y) >> (sizeof(s32) * 8 - 1)));
}

// int64
IC s64 _abs(s64 x) {
  return (x >= 0) ? x : s64(-x);
}

IC s64 _min(s64 x, s64 y) {
  return y + ((x - y) & ((x - y) >> (sizeof(s64) * 8 - 1)));
}

IC s64 _max(s64 x, s64 y) {
  return x - ((x - y) & ((x - y) >> (sizeof(s64) * 8 - 1)));
}
