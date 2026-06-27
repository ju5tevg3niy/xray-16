#include <cstddef>
#include <string>
#pragma once
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string_view>
#include "Common/Platform.hpp"
#include "Common/types.hpp"

// return pointer to ".ext"
IC char* strext(const char* S) {
  return (char*)strrchr(S, '.');
}

#ifndef MASTER_GOLD

inline int xr_strcpy(pstr destination,
                     size_t const destination_size,
                     pcstr source) {
  return strcpy_s(destination, destination_size, source);
}

inline int xr_strcat(pstr destination, size_t const buffer_size, pcstr source) {
  return strcat_s(destination, buffer_size, source);
}

inline int __cdecl xr_sprintf(pstr destination,
                              size_t const buffer_size,
                              pcstr format_string,
                              ...) {
  va_list args;
  va_start(args, format_string);
  const int result = vsprintf_s(destination, buffer_size, format_string, args);
  va_end(args);
  return result;
}

template <size_t count>
inline int __cdecl xr_sprintf(char (&destination)[count],
                              pcstr format_string,
                              ...) {
  va_list args;
  va_start(args, format_string);
  const int result = vsprintf_s(destination, count, format_string, args);
  va_end(args);
  return result;
}

#else   // #ifndef MASTER_GOLD

inline int xr_strcpy(pstr destination,
                     size_t const destination_size,
                     pcstr source) {
  return strncpy_s(destination, destination_size, source, destination_size);
}

inline int xr_strcat(pstr destination, size_t const buffer_size, pcstr source) {
  size_t const destination_length = strlen(destination);
  pstr i = destination + destination_length;
  pstr const e = destination + buffer_size - 1;
  if (i > e)
    return 0;

  for (pcstr j = source; *j && (i != e); ++i, ++j)
    *i = *j;

  *i = 0;
  return 0;
}

inline int __cdecl xr_sprintf(pstr destination,
                              size_t const buffer_size,
                              pcstr format_string,
                              ...) {
  va_list args;
  va_start(args, format_string);
  const int result = vsnprintf_s(destination, buffer_size, buffer_size - 1,
                                 format_string, args);
  va_end(args);
  return result;
}

template <int count>
inline int __cdecl xr_sprintf(char (&destination)[count],
                              pcstr format_string,
                              ...) {
  va_list args;
  va_start(args, format_string);
  const int result =
      vsnprintf_s(destination, count, count - 1, format_string, args);
  va_end(args);
  return result;
}
#endif  // #ifndef MASTER_GOLD

template <size_t count>
inline int xr_strcpy(char (&destination)[count], pcstr source) {
  return xr_strcpy(destination, count, source);
}

template <size_t count>
inline int xr_strcat(char (&destination)[count], pcstr source) {
  return xr_strcat(destination, count, source);
}

// source: https://stackoverflow.com/a/46711735
constexpr u32 strhash(const std::string_view data) noexcept {
  uint32_t hash = 5385;
  for (const auto& e : data)
    hash = ((hash << 5) + hash) + e;
  return hash;
}

constexpr u32 operator""_hash(char const* p, size_t size) {
  return strhash({p, size});
}
