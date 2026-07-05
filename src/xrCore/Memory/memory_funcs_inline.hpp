#pragma once
#include <cstddef>
#include <cstring>
#include "Common/types.hpp"

inline void MemFill32(void* dst, u32 value, size_t dstSize) {
  u32* ptr = static_cast<u32*>(dst);
  u32* end = ptr + dstSize;
  while (ptr != end)
    *ptr++ = value;
}

inline void ZeroMemory(void* dst, size_t size) {
  memset(dst, 0, size);
}

inline void CopyMemory(void* dst, const void* src, size_t size) {
  memcpy(dst, src, size);
}

inline void FillMemory(void* dst, size_t size, u8 val) {
  memset(dst, val, size);
}
